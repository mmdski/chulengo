#ifndef CHLIB_H_
#define CHLIB_H_

#include <stdbool.h>
#include <stdlib.h>

#ifndef __STDC_LIB_EXT1__
typedef int errno_t;
#endif

#define ch_const_mann_k() 1.486

typedef enum
{
  kChXSWSE,
  kChXSDepth,
  kChXSArea,
  kChXSTopWidth,
  kChXSWetPerim,
  kChXSHydDepth,
  kChXSHydRadius,
  kChXSConveyance,
  kChXSVelCoeff,
  kChXSNProps
} ChXSProp;

typedef struct ChXSCoords ChXSCoords;

ChXSCoords *ch_xs_coords_new (size_t size);
ChXSCoords *ch_xs_coords_new_like (ChXSCoords *xs_coords_ptr);
ChXSCoords *ch_xs_coords_copy (ChXSCoords *xs_coords_ptr);
void        ch_xs_coords_free (ChXSCoords *xs_coords_ptr);
size_t      ch_xs_coords_length (ChXSCoords *xs_coords_ptr);
void        ch_xs_coords_get (ChXSCoords *xs_coords_ptr,
                              size_t      i,
                              double     *station,
                              double     *elevation);
void        ch_xs_coords_get_arr (ChXSCoords *xs_coords_ptr,
                                  double     *station,
                                  double     *elevation);
void        ch_xs_coords_set (ChXSCoords *xs_coords_ptr,
                              size_t      i,
                              double      station,
                              double      elevation);
ChXSCoords *ch_xs_coords_set_arr (ChXSCoords *xs_coords_ptr,
                                  size_t      length,
                                  double     *station,
                                  double     *elevation);
ChXSCoords *
ch_xs_coords_push (ChXSCoords *xs_coords_ptr, double station, double elevation);
ChXSCoords *ch_xs_coords_subsect (ChXSCoords *xs_coords_ptr,
                                  double      left,
                                  double      right,
                                  ChXSCoords *subdiv_ptr);
ChXSCoords *ch_xs_coords_wetted (ChXSCoords *xs_coords_ptr,
                                 double      wse,
                                 ChXSCoords *wetted_ptr);

typedef struct ChXSSubdiv ChXSSubdiv;

ChXSSubdiv *ch_xs_subdiv_new (double roughness, ChXSCoords *coords_ptr);
void        ch_xs_subdiv_free (ChXSSubdiv *subdiv_ptr);
void ch_xs_subdiv_props (ChXSSubdiv *subdiv_ptr, double wse, double *props);

#endif
