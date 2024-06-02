#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <chl.h>

#include "ch_ras.h"

static int  ch_err_no = 0;
static char ch_err_message[CH_ERR_MSG_CHARS];
static char ch_err_line[CH_RAS_LINE_MAX_CHARS];

typedef struct
{
  size_t length;
  char   s[CH_RAS_LINE_MAX_CHARS + 1];
} ChFileLine;

void
ch_cpy_err_msg (char *dst)
{
  strlcpy (dst, ch_err_message, CH_ERR_MSG_CHARS);
}

size_t
ch_ras_file_read_line (ChFileContents *fc_ptr, ChFileLine *line_ptr)
{
  assert (fc_ptr);
  assert (line_ptr);

  size_t i = 0;
  while (fc_ptr->pos < fc_ptr->length &&
         fc_ptr->contents[fc_ptr->pos] != '\n' &&
         fc_ptr->contents[fc_ptr->pos] != '\0' && i < line_ptr->length - 1)
    {
      line_ptr->s[i] = fc_ptr->contents[fc_ptr->pos];
      i++;
      fc_ptr->pos++;
    }

  if (i > 0 && line_ptr->s[i - 1] == '\r')
    {
      line_ptr->s[i - 1] = '\0';
      i--;
    }
  else
    line_ptr->s[i] = '\0';

  fc_ptr->pos++;
  fc_ptr->line_no++;

  return i;
}

ChFileContents *
ch_ras_file_read (FILE *f)
{

  fseek (f, 0, SEEK_END);

  errno         = 0;
  size_t length = (size_t) ftell (f);
  if (f < 0 || errno != 0)
    {
      perror ("ftell");
      return NULL;
    }

  fseek (f, 0, SEEK_SET);

  errno = 0;
  ChFileContents *file_contents =
      malloc (sizeof (ChFileContents) + (length + 1) * sizeof (char));
  if (!file_contents)
    {
      perror ("malloc");
      return NULL;
    }

  size_t nob_read = fread (file_contents->contents, 1, length, f);
  if (nob_read != length)
    {
      free (file_contents);
      return NULL;
    }

  file_contents->contents[length] = '\0';

  file_contents->length = length;
  file_contents->pos    = 0;

  return file_contents;
}

static void
ch_ras_geom_reach_free (ChRASGeomReach *reach)
{
  if (!reach)
    return;
}

ChRASGeom *
ch_ras_geom_parse (ChFileContents *fc_ptr)
{
  assert (fc_ptr);

  if (fc_ptr->contents[fc_ptr->length] != '\0')
    return NULL;

  ch_err_message[0] = '\0';

  ChFileLine *line_ptr = NULL;
  ChRASGeom  *geom_ptr = NULL;

  fc_ptr->line_no = 1;
  fc_ptr->pos     = 0;

  errno    = 0;
  line_ptr = malloc (sizeof (ChFileLine));
  if (!line_ptr || errno != 0)
    {
      perror ("malloc");
      goto parse_fail;
    }

  geom_ptr = malloc (sizeof (ChRASGeom));
  if (!geom_ptr || errno != 0)
    {
      perror ("malloc");
      goto parse_fail;
    }
  geom_ptr->reach = NULL;

  size_t fail_line_no = 0;

  /* read the geometry title */
  size_t n_read = ch_ras_file_read_line (fc_ptr, line_ptr);
  if (n_read == 0)
    {
      fail_line_no = fc_ptr->line_no - 1;
      goto parse_fail;
    }

  if (strncmp ("Geom Title=", line_ptr->s, 11) != 0)
    {
      fail_line_no = fc_ptr->line_no - 1;
      goto parse_fail;
    }

  size_t i = 11;
  while (i < CH_RAS_LINE_MAX_CHARS && line_ptr->s[i] != '\0')
    {
      geom_ptr->title[i - 11] = line_ptr->s[i];
      i++;
    }
  geom_ptr->title[i - 11] = '\0';

  /* program version */
  n_read = ch_ras_file_read_line (fc_ptr, line_ptr);
  if (n_read == 0)
    {
      fail_line_no = fc_ptr->line_no - 1;
      goto parse_fail;
    }
  if (strncmp ("Program Version=", line_ptr->s, 16) != 0)
    {
      fail_line_no = fc_ptr->line_no - 1;
      goto parse_fail;
    }

  /* viewing rectangle */
  n_read = ch_ras_file_read_line (fc_ptr, line_ptr);
  if (n_read == 0)
    {
      fail_line_no = fc_ptr->line_no - 1;
      goto parse_fail;
    }
  if (strncmp ("Viewing Rectangle=", line_ptr->s, 18) != 0)
    {
      fail_line_no = fc_ptr->line_no - 1;
      goto parse_fail;
    }

  /* blank line */
  n_read = ch_ras_file_read_line (fc_ptr, line_ptr);
  if (n_read != 0)
    {
      fail_line_no = fc_ptr->line_no - 1;
      goto parse_fail;
    }

  /* next line could be the beginning of a reach description */
  /* or other things that we're not prepared to parse yet */
  n_read = ch_ras_file_read_line (fc_ptr, line_ptr);
  if (strncmp ("River Reach=", line_ptr->s, 12) == 0)
    {
      puts ("Found river reach");
    }
  else
    {
      fail_line_no = fc_ptr->line_no - 1;
      goto parse_fail;
    }

  free (line_ptr);

  return geom_ptr;

parse_fail:
  if (fail_line_no > 0)
    {
      snprintf (ch_err_message,
                CH_ERR_MSG_CHARS,
                "Failed to parse line %lu of HEC-RAS geometry file",
                fail_line_no);
      ch_err_no = 1;
    }

  free (line_ptr);
  free (geom_ptr);
  return NULL;
}

void
ch_ras_geom_free (ChRASGeom *geom)
{
  if (!geom)
    return;

  ChRASGeomReach *reach, *next_reach;
  reach = geom->reach;
  while (reach)
    {
      next_reach = reach->next;
      ch_ras_geom_reach_free (reach);
      reach = next_reach;
    }
}
