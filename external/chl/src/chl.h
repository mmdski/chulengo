#ifndef CHL_H_
#define CHL_H_

#include <stdbool.h>
#include <stdlib.h>

#ifndef __STDC_LIB_EXT1__
typedef int errno_t;
#endif

#define ch_const_mann_k() 1.486

typedef enum {
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
} ChXSHydraulicProps;

typedef struct ChXSCoords ChXSCoords;

ChXSCoords *ch_xs_coords_new(size_t size);
ChXSCoords *ch_xs_coords_new_like(ChXSCoords *xs_coords_ptr);
ChXSCoords *ch_xs_coords_copy(ChXSCoords *xs_coords_ptr);
void ch_xs_coords_free(ChXSCoords *xs_coords_ptr);
size_t ch_xs_coords_length(ChXSCoords *xs_coords_ptr);
void ch_xs_coords_get(ChXSCoords *xs_coords_ptr, size_t i, double *station,
                      double *elevation);
void ch_xs_coords_get_arr(ChXSCoords *xs_coords_ptr, double *station,
                          double *elevation);
void ch_xs_coords_set(ChXSCoords *xs_coords_ptr, size_t i, double station,
                      double elevation);
ChXSCoords *ch_xs_coords_set_arr(ChXSCoords *xs_coords_ptr, size_t length,
                                 double *station, double *elevation);
ChXSCoords *ch_xs_coords_push(ChXSCoords *xs_coords_ptr, double station,
                              double elevation);
ChXSCoords *ch_xs_coords_subsect(ChXSCoords *xs_coords_ptr, double left,
                                 double right, ChXSCoords *subsect_ptr);
ChXSCoords *ch_xs_coords_wetted(ChXSCoords *xs_coords_ptr, double wse,
                                ChXSCoords *wetted_ptr);

typedef struct ChXSSubdiv ChXSSubdiv;

ChXSSubdiv *ch_xs_subdiv_new(double roughness, ChXSCoords *coords_ptr);
void ch_xs_subdiv_free(ChXSSubdiv *subdiv_ptr);
void ch_xs_subdiv_props(ChXSSubdiv *subdiv_ptr, double wse, double *props);

typedef struct ChXSSubSect ChXSSubSect;

ChXSSubSect *ch_xs_subsect_new(ChXSCoords *coords_ptr, size_t n_roughness,
                               double *roughness, double *roughness_sta,
                               bool main_channel);
void ch_xs_subsect_free(ChXSSubSect *subsect_ptr);

typedef struct ChXSDef ChXSDef;

ChXSDef *ch_xs_def_new(void);
void ch_xs_def_free(ChXSDef *xs_def_ptr);
void ch_xs_def_set_coordinates(ChXSDef *xs_def_ptr, size_t n_coords,
                               double *station, double *elevation);
void ch_xs_def_set_roughness(ChXSDef *xs_def_ptr, size_t n_roughness,
                             double *roughness, double *roughness_sta);
void ch_xs_def_set_banks(ChXSDef *xs_def_ptr, double left, double right);

#endif
