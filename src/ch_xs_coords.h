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

  for (size_t i = 1; i < xs_coords_ptr->length; i++)
    {
      if (xs_coords_ptr->coords[i - 1].station >
          xs_coords_ptr->coords[i].station)
        return false;
    }

  return true;
}

#endif
