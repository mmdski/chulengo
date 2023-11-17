#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "ch_xs_coords.h"

ChXSCoords *
ch_xs_coords_new (size_t size)
{
  assert (size);

  errno = 0;
  ChXSCoords *xs_coords_ptr =
      malloc (sizeof (ChXSCoords) + sizeof (ChXSCoordinate) * size);

  if (!xs_coords_ptr)
    {
      perror ("malloc");
      exit (EXIT_FAILURE);
    }

  xs_coords_ptr->size   = size;
  xs_coords_ptr->length = 0;

  return xs_coords_ptr;
}

ChXSCoords *
ch_xs_coords_new_like (ChXSCoords *xs_coords_ptr)
{
  assert (xs_coords_ptr);

  ChXSCoords *new_xs_coords_ptr = ch_xs_coords_new (xs_coords_ptr->size);

  return new_xs_coords_ptr;
}

ChXSCoords *
ch_xs_coords_copy (ChXSCoords *xs_coords_ptr)
{
  assert (xs_coords_ptr);

  ChXSCoords *xs_coords_copy_ptr = ch_xs_coords_new_like (xs_coords_ptr);

  for (size_t i = 0; i < xs_coords_ptr->length; i++)
    {
      xs_coords_copy_ptr->coords[i].station = xs_coords_ptr->coords[i].station;
      xs_coords_copy_ptr->coords[i].elevation =
          xs_coords_ptr->coords[i].elevation;
    }

  xs_coords_copy_ptr->length = xs_coords_ptr->length;

  return xs_coords_copy_ptr;
}

ChXSCoords *
ch_xs_coords_realloc (ChXSCoords *xs_coords_ptr, size_t size)
{
  assert (xs_coords_ptr);
  assert (size);

  if (size == xs_coords_ptr->size)
    return xs_coords_ptr;

  errno                         = 0;
  ChXSCoords *new_xs_coords_ptr = realloc (
      xs_coords_ptr, sizeof (ChXSCoords) + size * sizeof (ChXSCoordinate));
  if (NULL == new_xs_coords_ptr || errno != 0)
    {
      perror ("realloc");
      exit (EXIT_FAILURE);
    }
  xs_coords_ptr       = new_xs_coords_ptr;
  xs_coords_ptr->size = size;

  if (xs_coords_ptr->length > xs_coords_ptr->size)
    xs_coords_ptr->length = size;

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
                  float       station,
                  float       elevation)
{
  assert (xs_coords_ptr);
  assert (i < xs_coords_ptr->length);
  assert (station && elevation);

  xs_coords_ptr->coords[i].station   = station;
  xs_coords_ptr->coords[i].elevation = elevation;
}

ChXSCoords *
ch_xs_coords_set_arr (ChXSCoords *xs_coords_ptr,
                      size_t      length,
                      float      *station,
                      float      *elevation)
{
  assert (xs_coords_ptr && station && elevation);

  if (length > xs_coords_ptr->size)
    xs_coords_ptr = ch_xs_coords_realloc (xs_coords_ptr, length);

  xs_coords_ptr->length = length;

  for (size_t i = 0; i < xs_coords_ptr->length; i++)
    {
      xs_coords_ptr->coords[i].station   = station[i];
      xs_coords_ptr->coords[i].elevation = elevation[i];
    }

  return xs_coords_ptr;
}

ChXSCoords *
ch_xs_coords_push (ChXSCoords *xs_coords_ptr, float station, float elevation)
{

  assert (xs_coords_ptr);

  size_t length = xs_coords_ptr->length;

  if (length == xs_coords_ptr->size)
    xs_coords_ptr =
        ch_xs_coords_realloc (xs_coords_ptr, 2 * xs_coords_ptr->size);

  xs_coords_ptr->coords[length].station   = station;
  xs_coords_ptr->coords[length].elevation = elevation;
  xs_coords_ptr->length                   = length + 1;

  return xs_coords_ptr;
}

static float
ch_xs_coords_interp_elev (ChXSCoordinate left,
                          ChXSCoordinate right,
                          float          station)
{
  assert (left.station <= right.station);
  return (right.elevation - left.elevation) / (right.station - left.station) *
             (station - left.station) +
         left.elevation;
}

ChXSCoords *
ch_xs_coords_subsect (ChXSCoords *xs_coords_ptr, float left, float right)
{
  assert (xs_coords_ptr);
  assert (left < right);

  assert (ch_xs_coords_validate (xs_coords_ptr));
  size_t length = xs_coords_ptr->length;

  if (right <= xs_coords_ptr->coords[0].station)
    return NULL;

  if (left > xs_coords_ptr->coords[length - 1].station)
    return NULL;

  if (left < xs_coords_ptr->coords[0].station)
    left = xs_coords_ptr->coords[0].station;

  if (right > xs_coords_ptr->coords[length - 1].station)
    right = xs_coords_ptr->coords[length - 1].station;

  size_t i_left, i_right;

  for (size_t i = 0; i < xs_coords_ptr->length; i++)
    {
      i_left = i;
      if (xs_coords_ptr->coords[i].station > left)
        break;
    }

  for (size_t i = xs_coords_ptr->length - 1; i >= 0; i--)
    {
      i_right = i;
      if (xs_coords_ptr->coords[i].station < right)
        break;
    }

  assert (i_left <= i_right);
  ChXSCoords *subsect_ptr = ch_xs_coords_new (i_right - i_left + 3);

  float elevation;
  elevation = ch_xs_coords_interp_elev (
      xs_coords_ptr->coords[i_left - 1], xs_coords_ptr->coords[i_left], left);
  subsect_ptr = ch_xs_coords_push (subsect_ptr, left, elevation);

  for (size_t i = i_left; i <= i_right; i++)
    {
      subsect_ptr =
          ch_xs_coords_push_coord (subsect_ptr, xs_coords_ptr->coords[i]);
    }

  elevation   = ch_xs_coords_interp_elev (xs_coords_ptr->coords[i_right],
                                        xs_coords_ptr->coords[i_right + 1],
                                        right);
  subsect_ptr = ch_xs_coords_push (subsect_ptr, right, elevation);

  return subsect_ptr;
}
