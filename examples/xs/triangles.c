#include <stdio.h>
#include <stdlib.h>

#include <chl.h>

int
main (void)
{
  size_t length          = 5;
  double station_arr[]   = { 0, 5, 10, 15, 20 };
  double elevation_arr[] = { 10, 0, 10, 0, 10 };
  double roughness       = 0.04;
  double props[kChXSNProps];

  ChXSCoords *coords_ptr =
      ch_xs_coords_set_arr (NULL, length, station_arr, elevation_arr);
  ChXSSubdiv *subdiv_ptr = ch_xs_subdiv_new (roughness, coords_ptr);

  for (size_t i = 0; i < 11; i++)
    {
      ch_xs_subdiv_props (subdiv_ptr, (double) i, props);
      printf ("wse = %2lu, area = %8.2f\n", i, props[kChXSArea]);
    }
  ch_xs_subdiv_free (subdiv_ptr);

  return EXIT_SUCCESS;
}
