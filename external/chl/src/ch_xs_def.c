#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "ch_mem.h"
#include "ch_xs.h"

ChXSDef *
ch_xs_def_new (void)
{
  errno               = 0;
  ChXSDef *xs_def_ptr = ch_malloc (sizeof (ChXSDef));
  if (NULL == xs_def_ptr || errno != 0)
    {
      perror ("malloc");
      exit (EXIT_FAILURE);
    }

  xs_def_ptr->n_coordinates = 0;
  xs_def_ptr->station       = NULL;
  xs_def_ptr->elevation     = NULL;

  xs_def_ptr->n_roughness       = 0;
  xs_def_ptr->roughness         = NULL;
  xs_def_ptr->roughness_station = NULL;

  xs_def_ptr->bank_stations[0] = NAN;
  xs_def_ptr->bank_stations[1] = NAN;

  return xs_def_ptr;
}

void
ch_xs_def_free (ChXSDef *xs_def_ptr)
{
  if (!xs_def_ptr)
    return;

  ch_free (xs_def_ptr->station);
  ch_free (xs_def_ptr->elevation);

  ch_free (xs_def_ptr->roughness);
  ch_free (xs_def_ptr->roughness_station);

  ch_free (xs_def_ptr);
}

void
ch_xs_def_set_coordinates (ChXSDef *xs_def_ptr,
                           size_t   n_coords,
                           double  *station,
                           double  *elevation)
{
  assert (xs_def_ptr);
  assert (station);
  assert (elevation);
  assert (n_coords > 0);

  errno = 0;
  if (xs_def_ptr->n_coordinates == 0)
    {
      xs_def_ptr->station = ch_malloc (n_coords * sizeof (double));
      if (NULL == xs_def_ptr->station || errno != 0)
        goto malloc_fail;

      xs_def_ptr->elevation = ch_malloc (n_coords * sizeof (double));
      if (NULL == xs_def_ptr->elevation || errno != 0)
        goto malloc_fail;
    }
  else if (xs_def_ptr->n_coordinates < n_coords)
    {
      double *new_station =
          ch_realloc (xs_def_ptr->station, n_coords * sizeof (double));
      if (NULL == new_station || errno != 0)
        goto realloc_fail;
      xs_def_ptr->station = new_station;

      double *new_elevation =
          ch_realloc (xs_def_ptr->elevation, n_coords * sizeof (double));
      if (NULL == new_elevation || errno != 0)
        goto realloc_fail;
      xs_def_ptr->elevation = new_elevation;
    }

  xs_def_ptr->station[0]   = station[0];
  xs_def_ptr->elevation[0] = elevation[0];

  for (size_t i = 1; i < n_coords; i++)
    {
      assert (xs_def_ptr->station[i - 1] <= station[i]);
      xs_def_ptr->station[i]   = station[i];
      xs_def_ptr->elevation[i] = elevation[i];
    }

  xs_def_ptr->n_coordinates = n_coords;

  return;

malloc_fail:
  perror ("malloc");
  exit (EXIT_FAILURE);

realloc_fail:
  perror ("realloc");
  exit (EXIT_FAILURE);
}

void
ch_xs_def_set_roughness (ChXSDef *xs_def_ptr,
                         size_t   n_roughness,
                         double  *roughness,
                         double  *roughness_sta)
{
  assert (xs_def_ptr);
  assert (roughness);
  assert (roughness_sta);
  assert (n_roughness > 0);

  errno = 0;
  if (xs_def_ptr->n_roughness == 0)
    {
      xs_def_ptr->roughness = ch_malloc (n_roughness * sizeof (double));
      if (NULL == xs_def_ptr->roughness || errno != 0)
        goto malloc_fail;

      xs_def_ptr->roughness_station = ch_malloc (n_roughness * sizeof (double));
      if (NULL == xs_def_ptr->roughness_station || errno != 0)
        goto malloc_fail;
    }
  else if (xs_def_ptr->n_roughness < n_roughness)
    {
      double *new_roughness =
          ch_realloc (xs_def_ptr->roughness, n_roughness * sizeof (double));
      if (NULL == new_roughness || errno != 0)
        goto realloc_fail;
      xs_def_ptr->roughness = new_roughness;

      double *new_roughness_sta = ch_realloc (xs_def_ptr->roughness_station,
                                              n_roughness * sizeof (double));
      if (NULL == new_roughness_sta || errno != 0)
        goto realloc_fail;
      xs_def_ptr->roughness_station = new_roughness_sta;
    }

  xs_def_ptr->roughness[0]         = roughness[0];
  xs_def_ptr->roughness_station[0] = roughness_sta[0];

  for (size_t i = 1; i < n_roughness; i++)
    {
      assert (xs_def_ptr->roughness_station[i - 1] < roughness_sta[i]);
      xs_def_ptr->roughness[i]         = roughness[i];
      xs_def_ptr->roughness_station[i] = roughness_sta[i];
    }

  xs_def_ptr->n_roughness = n_roughness;

  return;

malloc_fail:
  perror ("malloc");
  exit (EXIT_FAILURE);

realloc_fail:
  perror ("realloc");
  exit (EXIT_FAILURE);
}

void
ch_xs_def_set_banks (ChXSDef *xs_def_ptr, double left, double right)
{
  assert (xs_def_ptr);
  assert (left < right);
  xs_def_ptr->bank_stations[0] = left;
  xs_def_ptr->bank_stations[1] = right;
}
