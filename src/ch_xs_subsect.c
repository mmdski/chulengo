#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>

#include "ch_xs_coords.h"
#include "ch_xs_subsect.h"

ChXSSubSect *
ch_xs_subsect_new (double roughness, ChXSCoords *coords_ptr)
{
  assert (roughness > 0 && isfinite (roughness));
  assert (coords_ptr);
  assert (ch_xs_coords_validate (coords_ptr));

  errno                    = 0;
  ChXSSubSect *subsect_ptr = malloc (sizeof (ChXSSubSect));
  if (subsect_ptr == NULL || errno != 0)
    {
      perror ("malloc");
      exit (EXIT_FAILURE);
    }

  subsect_ptr->roughness  = roughness;
  subsect_ptr->coords     = coords_ptr;
  subsect_ptr->wet_coords = NULL;

  subsect_ptr->min_elevation = coords_ptr->coords[0].elevation;

  for (size_t i = 1; i < coords_ptr->length; i++)
    {
      if (subsect_ptr->min_elevation > coords_ptr->coords[i].elevation)
        subsect_ptr->min_elevation = coords_ptr->coords[i].elevation;
    }

  return subsect_ptr;
}

void
ch_xs_subsect_free (ChXSSubSect *subsect_ptr)
{
  if (NULL == subsect_ptr)
    return;

  ch_xs_coords_free (subsect_ptr->coords);
  ch_xs_coords_free (subsect_ptr->wet_coords);
  free (subsect_ptr);
}

void
ch_xs_subsect_props (ChXSSubSect *subsect_ptr, double wse, double *props)
{
  assert (subsect_ptr);
  assert (props);

  if (wse <= subsect_ptr->min_elevation)
    {
      props[kChXSWSE]        = wse;
      props[kChXSDepth]      = 0;
      props[kChXSArea]       = 0;
      props[kChXSTopWidth]   = 0;
      props[kChXSWetPerim]   = 0;
      props[kChXSHydDepth]   = NAN;
      props[kChXSHydRadius]  = NAN;
      props[kChXSConveyance] = 0;
      props[kChXSVelCoeff]   = NAN;
      return;
    }
  else if (!isfinite (wse))
    {
      props[kChXSWSE]        = wse;
      props[kChXSDepth]      = NAN;
      props[kChXSArea]       = NAN;
      props[kChXSTopWidth]   = NAN;
      props[kChXSWetPerim]   = NAN;
      props[kChXSHydDepth]   = NAN;
      props[kChXSHydRadius]  = NAN;
      props[kChXSConveyance] = NAN;
      props[kChXSVelCoeff]   = NAN;
      return;
    }

  double area      = 0;
  double perimeter = 0;
  double top_width = 0;
  double hydraulic_radius;

  /* depth for c1 and c2 */
  double d1;
  double d2;

  /* distances for perimeter */
  double dy;
  double dz;

  double y1;
  double z1;

  double y2;
  double z2;

  subsect_ptr->wet_coords =
      ch_xs_coords_wetted (subsect_ptr->coords, wse, subsect_ptr->wet_coords);

  ChXSCoords *wet_coords = subsect_ptr->wet_coords;

  for (size_t i = 1; i < wet_coords->length; i++)
    {
      if (isnan (wet_coords->coords[i].station) ||
          isnan (wet_coords->coords[i - 1].station))
        continue;

      y1 = wet_coords->coords[i - 1].elevation;
      z1 = wet_coords->coords[i - 1].station;

      y2 = wet_coords->coords[i].elevation;
      z2 = wet_coords->coords[i].station;

      d1 = wse - y1;
      d2 = wse - y2;
      area += 0.5 * (d1 + d2) * (z2 - z1);

      dy = y2 - y1;
      dz = z2 - z1;
      perimeter += sqrt (dy * dy + dz * dz);

      top_width += z2 - z1;
    }

  hydraulic_radius       = area / perimeter;
  props[kChXSWSE]        = wse;
  props[kChXSDepth]      = wse - subsect_ptr->min_elevation;
  props[kChXSArea]       = area;
  props[kChXSTopWidth]   = top_width;
  props[kChXSWetPerim]   = perimeter;
  props[kChXSHydDepth]   = area / top_width;
  props[kChXSHydRadius]  = hydraulic_radius;
  props[kChXSConveyance] = ch_const_mann_k () / subsect_ptr->roughness * area *
                           pow (hydraulic_radius, 2.0 / 3.0);
  props[kChXSVelCoeff] = 1;
}
