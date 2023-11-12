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

#endif
