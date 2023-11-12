#ifndef CHL_H_
#define CHL_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct ChXSCoords ChXSCoords;

ChXSCoords *ch_xs_coords_new (size_t size);
void        ch_xs_coords_free (ChXSCoords *xs_coords_ptr);
size_t      ch_xs_coords_length (ChXSCoords *xs_coords_ptr);
void        ch_xs_coords_get (ChXSCoords *xs_coords_ptr,
                              size_t      i,
                              float      *station,
                              float      *elevation);
void        ch_xs_coords_get_arr (ChXSCoords *xs_coords_ptr,
                                  float      *station,
                                  float      *elevation);
void        ch_xs_coords_set (ChXSCoords *xs_coords_ptr,
                              size_t      i,
                              float      *station,
                              float      *elevation);
void        ch_xs_coords_set_arr (ChXSCoords *xs_coords_ptr,
                                  size_t      length,
                                  float      *station,
                                  float      *elevation);
#endif
