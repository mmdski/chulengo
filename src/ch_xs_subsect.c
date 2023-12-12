#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <chlib.h>

#include "ch_arr_dbl.h"
#include "ch_xs.h"

ChXSSubSect *
ch_xs_subsect_new (ChXSCoords *coords_ptr,
                   size_t      n_roughness,
                   double     *roughness,
                   double     *roughness_sta,
                   bool        main_channel)
{

  assert (coords_ptr);
  assert (n_roughness);
  assert (roughness);
  assert (ch_xs_coords_validate (coords_ptr));

#ifndef NDEBUG
  assert (roughness[0] > 0);
  for (size_t i = 1; i < n_roughness; i++)
    {
      assert (roughness[i] > 0);
      assert (roughness_sta[i - 1] < roughness_sta[i]);
    }
#endif

  assert (roughness[0] <= coords_ptr->coords[0].station);

  ChArrDbl *rough_arr_ptr = ch_arr_dbl_new (5);
  ChArrDbl *sta_arr_ptr   = ch_arr_dbl_new (5);

  // find the left-most roughness that applies to the subsection coordinates
  size_t i_roughness = n_roughness - 1;
  while (i_roughness < n_roughness &&
         roughness_sta[i_roughness] > coords_ptr->coords[0].station)
    i_roughness--;

  rough_arr_ptr = ch_arr_dbl_push (rough_arr_ptr, roughness[i_roughness]);
  sta_arr_ptr   = ch_arr_dbl_push (sta_arr_ptr, coords_ptr->coords[0].station);
  i_roughness++;

  size_t coords_len = coords_ptr->length;

  while (i_roughness < n_roughness &&
         roughness_sta[i_roughness] <
             coords_ptr->coords[coords_len - 1].station)
    {
      rough_arr_ptr = ch_arr_dbl_push (rough_arr_ptr, roughness[i_roughness]);
      sta_arr_ptr   = ch_arr_dbl_push (sta_arr_ptr, roughness_sta[i_roughness]);
      i_roughness++;
    }

  // add infinity to the last station for subdividing later
  sta_arr_ptr = ch_arr_dbl_push (sta_arr_ptr, INFINITY);

  size_t n_subdivs = rough_arr_ptr->length;

  errno                    = 0;
  ChXSSubSect *subsect_ptr = malloc (sizeof (ChXSSubSect));
  if (NULL == subsect_ptr || errno != 0)
    {
      perror ("malloc");
      exit (EXIT_FAILURE);
    }
  subsect_ptr->main_channel = main_channel;
  subsect_ptr->n_subdivs    = n_subdivs;

  subsect_ptr->subdivs = malloc (n_subdivs * sizeof (ChXSSubdiv *));
  if (NULL == subsect_ptr->subdivs || errno != 0)
    {
      perror ("malloc");
      exit (EXIT_FAILURE);
    }

  ChXSCoords *subdiv_coords_ptr;
  ChXSSubdiv *subdiv_ptr;

  for (size_t i = 0; i < n_subdivs; i++)
    {
      subdiv_coords_ptr = ch_xs_coords_subsect (
          coords_ptr, sta_arr_ptr->values[i], sta_arr_ptr->values[i + 1], NULL);
      subdiv_ptr =
          ch_xs_subdiv_new (rough_arr_ptr->values[i], subdiv_coords_ptr);
      subsect_ptr->subdivs[i] = subdiv_ptr;
    }

  ch_xs_coords_free (coords_ptr);
  ch_arr_dbl_free (rough_arr_ptr);
  ch_arr_dbl_free (sta_arr_ptr);

  return subsect_ptr;
}

void
ch_xs_subsect_free (ChXSSubSect *subsect_ptr)
{
  if (!subsect_ptr)
    return;

  for (size_t i = 0; i < subsect_ptr->n_subdivs; i++)
    {
      ch_xs_subdiv_free (subsect_ptr->subdivs[i]);
    }

  free (subsect_ptr->subdivs);
  free (subsect_ptr);
}
