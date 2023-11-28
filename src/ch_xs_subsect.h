#ifndef CH_XS_SUBSECT_H_
#define CH_XS_SUBSECT_H_

#include <stdbool.h>

#include <chlib.h>

struct ChXSSubSect
{
  bool         main_channel;
  size_t       n_subdivs;
  ChXSSubdiv **subdivs;
};

#endif
