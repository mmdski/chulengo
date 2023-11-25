#include <gtest/gtest.h>

extern "C"
{
#include <math.h>

#include <chlib.h>
}

namespace
{

TEST (ChXSCoords, mem)
{
  ChXSCoords *xs_coords_ptr = ch_xs_coords_new (10);
  ch_xs_coords_free (xs_coords_ptr);
}

TEST (ChXSCoords, length)
{
  ChXSCoords *xs_coords_ptr = ch_xs_coords_new (50);
  ASSERT_EQ (ch_xs_coords_length (xs_coords_ptr), 0);
  ch_xs_coords_free (xs_coords_ptr);
}

TEST (ChXSCoords, set_arr)
{
  double station, elevation;

  size_t length          = 8;
  double station_arr[]   = { 210, 220, 260, 265, 270, 275, 300, 310 };
  double elevation_arr[] = { 90, 82, 80, 70, 71, 81, 83, 91 };

  ChXSCoords *xs_coords_ptr =
      ch_xs_coords_set_arr (NULL, length, station_arr, elevation_arr);

  ASSERT_EQ (ch_xs_coords_length (xs_coords_ptr), length);

  for (size_t i = 0; i < length; i++)
    {
      ch_xs_coords_get (xs_coords_ptr, i, &station, &elevation);
      ASSERT_EQ (station, station_arr[i]);
      ASSERT_EQ (elevation, elevation_arr[i]);
    }

  ch_xs_coords_free (xs_coords_ptr);
}

TEST (ChXSCoords, push)
{
  ChXSCoords *xs_coords_ptr = ch_xs_coords_new (1);

  double station, elevation;

  size_t length          = 8;
  double station_arr[]   = { 210, 220, 260, 265, 270, 275, 300, 310 };
  double elevation_arr[] = { 90, 82, 80, 70, 71, 81, 83, 91 };

  for (size_t i = 0; i < length; i++)
    {
      xs_coords_ptr =
          ch_xs_coords_push (xs_coords_ptr, station_arr[i], elevation_arr[i]);
    }

  for (size_t i = 0; i < length; i++)
    {
      ch_xs_coords_get (xs_coords_ptr, i, &station, &elevation);
      ASSERT_EQ (station, station_arr[i]);
      ASSERT_EQ (elevation, elevation_arr[i]);
    }

  ch_xs_coords_free (xs_coords_ptr);
}

TEST (ChXSCoords, subsect)
{
  size_t length          = 8;
  double station_arr[]   = { 210, 220, 260, 265, 270, 275, 300, 310 };
  double elevation_arr[] = { 90, 82, 80, 70, 71, 81, 83, 91 };

  ChXSCoords *xs_coords_ptr = ch_xs_coords_new (length);

  xs_coords_ptr =
      ch_xs_coords_set_arr (xs_coords_ptr, 8, station_arr, elevation_arr);

  // left and right are outside of the stations of the array
  ChXSCoords *subsect_ptr = NULL;
  subsect_ptr =
      ch_xs_coords_subsect (xs_coords_ptr, -INFINITY, INFINITY, subsect_ptr);

  ASSERT_TRUE (subsect_ptr);

  double station, elevation;

  for (size_t i = 0; i < length; i++)
    {
      ch_xs_coords_get (subsect_ptr, i, &station, &elevation);
      ASSERT_EQ (station, station_arr[i]);
      ASSERT_EQ (elevation, elevation_arr[i]);
    }

  // left and right are too far to the left
  subsect_ptr = ch_xs_coords_subsect (xs_coords_ptr, 0, 10, subsect_ptr);
  ASSERT_EQ (ch_xs_coords_length (subsect_ptr), 0);

  // left and right are too far to the right
  subsect_ptr = ch_xs_coords_subsect (xs_coords_ptr, 350, 400, subsect_ptr);
  ASSERT_EQ (ch_xs_coords_length (subsect_ptr), 0);

  // left and right are equal to stations and elevations in the array
  size_t i_left  = 2;
  size_t i_right = 5;

  subsect_ptr = ch_xs_coords_subsect (
      xs_coords_ptr, station_arr[i_left], station_arr[i_right], subsect_ptr);
  for (size_t i = i_left; i <= i_right; i++)
    {
      ch_xs_coords_get (subsect_ptr, i - i_left, &station, &elevation);
      ASSERT_EQ (station, station_arr[i]);
      ASSERT_EQ (elevation, elevation_arr[i]);
    }

  ch_xs_coords_free (subsect_ptr);
  ch_xs_coords_free (xs_coords_ptr);
}

TEST (ChXSCoords, wetted)
{
  size_t length          = 5;
  double station_arr[]   = { 0, 5, 10, 15, 20 };
  double elevation_arr[] = { 10, 0, 10, 0, 10 };

  ChXSCoords *xs_coords_ptr =
      ch_xs_coords_set_arr (NULL, length, station_arr, elevation_arr);

  size_t wetted_length      = 7;
  double wetted_station[]   = { 2.5, 5, 7.5, NAN, 12.5, 15, 17.5 };
  double wetted_elevation[] = { 5, 0, 5, NAN, 5, 0, 5 };

  double station, elevation;

  double      wse               = 5;
  ChXSCoords *wetted_coords_ptr = NULL;
  wetted_coords_ptr =
      ch_xs_coords_wetted (xs_coords_ptr, wse, wetted_coords_ptr);

  ASSERT_EQ (wetted_length, ch_xs_coords_length (wetted_coords_ptr));

  for (size_t i = 0; i < wetted_length; i++)
    {
      ch_xs_coords_get (wetted_coords_ptr, i, &station, &elevation);
      if (isnan (wetted_station[i]))
        {
          ASSERT_TRUE (isnan (station));
          ASSERT_TRUE (isnan (elevation));
        }
      else
        {
          ASSERT_DOUBLE_EQ (station, wetted_station[i]);
          ASSERT_DOUBLE_EQ (elevation, wetted_elevation[i]);
        }
    }

  wetted_coords_ptr =
      ch_xs_coords_wetted (xs_coords_ptr, -INFINITY, wetted_coords_ptr);
  ASSERT_EQ (ch_xs_coords_length (wetted_coords_ptr), 0);

  ch_xs_coords_free (wetted_coords_ptr);
  ch_xs_coords_free (xs_coords_ptr);
}
}

int
main (int argc, char **argv)
{
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
