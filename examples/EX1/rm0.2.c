#include <stdio.h>
#include <stdlib.h>

#include <chlib.h>

int
main (void)
{

  size_t length          = 8;
  double station_arr[]   = { 210, 220, 260, 265, 270, 275, 300, 310 };
  double elevation_arr[] = { 90, 82, 80, 70, 71, 81, 83, 91 };

  ChXSCoords *xs_coords_ptr = ch_xs_coords_new (length);
  xs_coords_ptr =
      ch_xs_coords_set_arr (xs_coords_ptr, length, station_arr, elevation_arr);

  double station, elevation;

  ChXSCoords *subsect_ptr = NULL;
  ChXSCoords *wetted_ptr  = NULL;

  double left  = 220;
  double right = 260;
  subsect_ptr  = ch_xs_coords_subsect (xs_coords_ptr, left, right, subsect_ptr);

  if (!subsect_ptr)
    {
      printf ("subsect is NULL\n");
      goto exit;
    }

  size_t subsect_length = ch_xs_coords_length (subsect_ptr);
  printf ("subsect length: %lu\n", subsect_length);

  printf ("subsect coordinates:\n");
  printf ("%15s,%15s\n", "station", "elevation");
  for (size_t i = 0; i < subsect_length; i++)
    {
      ch_xs_coords_get (subsect_ptr, i, &station, &elevation);
      printf ("%15.2f,%15.2f\n", station, elevation);
    }

  double wse = 75;
  wetted_ptr = ch_xs_coords_wetted (xs_coords_ptr, wse, wetted_ptr);

  if (!wetted_ptr)
    {
      printf ("wetted coords is NULL\n");
      goto exit;
    }

  size_t wetted_length = ch_xs_coords_length (wetted_ptr);
  printf ("wetted length: %lu\n", wetted_length);

  if (wetted_length == 0)
    goto exit;

  printf ("wetted coordinates:\n");
  printf ("%15s,%15s\n", "station", "elevation");
  for (size_t i = 0; i < wetted_length; i++)
    {
      ch_xs_coords_get (wetted_ptr, i, &station, &elevation);
      printf ("%15.2f,%15.2f\n", station, elevation);
    }

exit:
  ch_xs_coords_free (wetted_ptr);
  ch_xs_coords_free (subsect_ptr);
  ch_xs_coords_free (xs_coords_ptr);

  return EXIT_SUCCESS;
}
