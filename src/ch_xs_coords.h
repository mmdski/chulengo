#ifndef CH_XS_COORDS_H_
#define CH_XS_COORDS_H_

#include <chl.h>

typedef struct
{
  float station;
  float elevation;
} ChXSCoordinate;

struct ChXSCoords
{
  size_t         length;
  size_t         size;
  ChXSCoordinate coords[];
};

static inline bool
ch_xs_coords_validate (ChXSCoords *xs_coords_ptr)
{

  assert (xs_coords_ptr);

  size_t length = xs_coords_ptr->length;

  if (length < 2)
    return false;

  for (size_t i = 1; i < length; i++)
    {
      if (xs_coords_ptr->coords[i - 1].station >
          xs_coords_ptr->coords[i].station)
        return false;
    }

  // test for a vertical line
  if (xs_coords_ptr->coords[0].station ==
      xs_coords_ptr->coords[length - 1].station)
    return false;

  return true;
}

static inline ChXSCoords *
ch_xs_coords_push_coord (ChXSCoords *xs_coords_ptr, ChXSCoordinate coordinate)
{
  return ch_xs_coords_push (
      xs_coords_ptr, coordinate.station, coordinate.elevation);
}

#endif
