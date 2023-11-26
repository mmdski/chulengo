#ifndef CH_XS_SUBDIV_H_
#define CH_XS_SUBDIV_H_

#include <chlib.h>

#include "ch_xs_coords.h"

struct ChXSSubdiv
{
  double      roughness;
  double      min_elevation;
  ChXSCoords *coords;
  ChXSCoords *wet_coords;
};

#endif
