#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "ch_xs_coords.h"

ChXSCoords *
ch_xs_coords_new (size_t size)
{
  errno = 0;
  ChXSCoords *xs_coords_ptr =
      malloc (sizeof (ChXSCoords) + sizeof (ChXSCoordinate) * size);

  if (NULL == xs_coords_ptr)
    {
      perror ("malloc");
      exit (EXIT_FAILURE);
    }

  xs_coords_ptr->size   = size;
  xs_coords_ptr->length = 0;

  return xs_coords_ptr;
}

void
ch_xs_coords_free (ChXSCoords *xs_coords_ptr)
{
  if (!xs_coords_ptr)
    return;
  free (xs_coords_ptr);
}

size_t
ch_xs_coords_length (ChXSCoords *xs_coords_ptr)
{
  assert (xs_coords_ptr);
  return xs_coords_ptr->length;
}

void
ch_xs_coords_get (ChXSCoords *xs_coords_ptr,
                  size_t      i,
                  float      *station,
                  float      *elevation)
{
  assert (xs_coords_ptr);
  assert (i < xs_coords_ptr->length);

  *station   = xs_coords_ptr->coords[i].station;
  *elevation = xs_coords_ptr->coords[i].elevation;
}

void
ch_xs_coords_get_arr (ChXSCoords *xs_coords_ptr,
                      float      *station,
                      float      *elevation)
{
  assert (xs_coords_ptr);
  assert (station && elevation);

  for (size_t i = 0; i < xs_coords_ptr->length; i++)
    {
      station[i]   = xs_coords_ptr->coords[i].station;
      elevation[i] = xs_coords_ptr->coords[i].elevation;
    }
}

void
ch_xs_coords_set (ChXSCoords *xs_coords_ptr,
                  size_t      i,
                  float      *station,
                  float      *elevation)
{
  assert (xs_coords_ptr);
  assert (i < xs_coords_ptr->length);
  assert (station && elevation);

  xs_coords_ptr->coords[i].station   = *station;
  xs_coords_ptr->coords[i].elevation = *elevation;
}

void
ch_xs_coords_set_arr (ChXSCoords *xs_coords_ptr,
                      size_t      length,
                      float      *station,
                      float      *elevation)
{
  assert (xs_coords_ptr && station && elevation);
  assert (length <= xs_coords_ptr->size);
  xs_coords_ptr->length = length;

  for (size_t i = 0; i < length; i++)
    {
      xs_coords_ptr->coords[i].station   = station[i];
      xs_coords_ptr->coords[i].elevation = elevation[i];
    }
}
