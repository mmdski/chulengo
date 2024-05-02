#include <math.h>
#include <stdlib.h>

#include <chl.h>

int
main (void)
{
  size_t length          = 8;
  double station_arr[]   = { 210, 220, 260, 265, 270, 275, 300, 310 };
  double elevation_arr[] = { 90, 82, 80, 70, 71, 81, 83, 91 };

  size_t n_roughness     = 3;
  double roughness_sta[] = { 210, 260, 275 };
  double roughness[]     = { 0.07, 0.04, 0.07 };

  ChXSCoords *coords_ptr =
      ch_xs_coords_set_arr (NULL, length, station_arr, elevation_arr);

  ChXSCoords *lob_coords_ptr =
      ch_xs_coords_subsect (coords_ptr, -INFINITY, 260, NULL);
  ChXSSubSect *lob_subsect = ch_xs_subsect_new (
      lob_coords_ptr, n_roughness, roughness, roughness_sta, false);

  ChXSCoords *main_coords_ptr =
      ch_xs_coords_subsect (coords_ptr, 260, 275, NULL);
  ChXSSubSect *main_subsect = ch_xs_subsect_new (
      main_coords_ptr, n_roughness, roughness, roughness_sta, true);

  ch_xs_coords_free (coords_ptr);

  ch_xs_subsect_free (lob_subsect);

  ch_xs_subsect_free (main_subsect);

  return EXIT_SUCCESS;
}
