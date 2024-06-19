#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ch_ras.h"

size_t
read_line (char *s, char *line, size_t pos, size_t max_line)
{
  size_t i = 0;
  while (s[i + pos] != '\n' && s[i + pos] != '\0' && i < max_line)
    {
      line[i] = s[i + pos];
      ++i;
    }

  if (i > 0 && line[i - 1] == '\r')
    {
      line[i - 1] = '\0';
    }
  else
    line[i] = '\0';

  return i + 1;
}

int
main (void)
{

  errno   = 0;
  FILE *f = fopen ("BEAVCREK.g01", "r");

  if (!f || errno != 0)
    {
      perror ("fopen");
      return EXIT_FAILURE;
    }

  ChFileContents *fc_ptr = ch_ras_file_read (f);
  fclose (f);

  if (!fc_ptr)
    {
      fprintf (stderr, "ch_ras_file_read failed.\n");
      return EXIT_FAILURE;
    }

  ChRASGeom *geom_ptr = ch_ras_geom_parse (fc_ptr);
  if (!geom_ptr)
    {
      char err_msg[CH_ERR_MSG_CHARS];
      ch_cpy_err_msg (err_msg);
      fprintf (stderr, "%s\n", err_msg);
      return EXIT_FAILURE;
    }

  printf ("Geom Title=%s\n", geom_ptr->title);

  //   free (geom_ptr);
  ch_ras_geom_free (geom_ptr);
  free (fc_ptr);

  ChRASGeomReach *reach = malloc (sizeof (ChRASGeomReach));
  printf ("%lu\n", sizeof (reach->reach_name) / sizeof (char));

  return EXIT_SUCCESS;
}
