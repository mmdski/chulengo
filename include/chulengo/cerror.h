#ifndef __CHL_ERROR_H__
#define __CHL_ERROR_H__

#if !defined(__CHL_H_INSIDE__) && !defined(CHL_COMPILATION)
#error "Only <chulengo.h> can be included directly."
#endif

#include <glib.h>

#define CHL_ERROR chl_error_quark ()

extern GQuark chl_error_quark (void);

enum ChlError
{
  CHL_ERROR_ARG
};

#endif
