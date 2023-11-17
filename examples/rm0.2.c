#include <stdio.h>
#include <stdlib.h>

#include <chl.h>

int
main (void)
{

  size_t length          = 8;
  float  station_arr[]   = { 210, 220, 260, 265, 270, 275, 300, 310 };
  float  elevation_arr[] = { 90, 82, 80, 70, 71, 81, 83, 91 };

  ChXSCoords *xs_coords_ptr = ch_xs_coords_new (length);
  xs_coords_ptr =
      ch_xs_coords_set_arr (xs_coords_ptr, length, station_arr, elevation_arr);

  float       left        = 259;
  float       right       = 275;
  ChXSCoords *subsect_ptr = ch_xs_coords_subsect (xs_coords_ptr, left, right);

  if (!subsect_ptr)
    {
      printf ("subsect is NULL\n");
      ch_xs_coords_free (xs_coords_ptr);
      return EXIT_SUCCESS;
    }

  size_t subsect_length = ch_xs_coords_length (subsect_ptr);
  printf ("subsect length: %lu\n", subsect_length);

  printf ("subsect coordinates:\n");
  printf ("%15s,%15s\n", "station", "elevation");
  float station, elevation;
  for (size_t i = 0; i < subsect_length; i++)
    {
      ch_xs_coords_get (subsect_ptr, i, &station, &elevation);
      printf ("%15.2f,%15.2f\n", station, elevation);
    }

  ch_xs_coords_free (subsect_ptr);
  ch_xs_coords_free (xs_coords_ptr);

  return EXIT_SUCCESS;
}
