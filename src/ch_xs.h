#ifndef CH_XS_H_
#define CH_XS_H_

#include <assert.h>
#include <math.h>
#include <stdbool.h>

#include <chlib.h>

typedef struct
{
  double station;
  double elevation;
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

  for (size_t i = 0; i < length; i++)
    {
      if (i > 0)
        {
          if (xs_coords_ptr->coords[i - 1].station >
              xs_coords_ptr->coords[i].station)
            return false;
        }

      if (!(isfinite (xs_coords_ptr->coords[i].station) &&
            isfinite (xs_coords_ptr->coords[i].elevation)))
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

struct ChXSSubdiv
{
  double      roughness;
  double      min_elevation;
  ChXSCoords *coords;
  ChXSCoords *wet_coords;
};

struct ChXSSubSect
{
  bool         main_channel;
  size_t       n_subdivs;
  ChXSSubdiv **subdivs;
};

struct ChXSDef
{
  size_t  n_coordinates;
  double *station;
  double *elevation;

  size_t  n_roughness;
  double *roughness;
  double *roughness_station;

  double bank_stations[2];
};

#endif
