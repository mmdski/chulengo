#ifndef CH_XS_SUBSECT_H_
#define CH_XS_SUBSECT_H_

#include <chlib.h>

#include "ch_xs_coords.h"

struct ChXSSubSect
{
  double      roughness;
  double      min_elevation;
  ChXSCoords *coords;
  ChXSCoords *wet_coords;
};

#endif
