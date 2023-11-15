#include <gtest/gtest.h>

extern "C"
{
#include <chl.h>
}

namespace
{

TEST (ch_xs, coords_mem)
{
  ChXSCoords *xs_coords_ptr = ch_xs_coords_new (10);
  ch_xs_coords_free (xs_coords_ptr);
}

TEST (ch_xs, coords_length)
{
  ChXSCoords *xs_coords_ptr = ch_xs_coords_new (50);
  ASSERT_EQ (ch_xs_coords_length (xs_coords_ptr), 0);
  ch_xs_coords_free (xs_coords_ptr);
}

TEST (ch_xs, coords_set_get)
{
  ChXSCoords *xs_coords_ptr = ch_xs_coords_new (10);

  float station, elevation;

  size_t length          = 8;
  float  station_arr[]   = { 210, 220, 260, 265, 270, 275, 300, 310 };
  float  elevation_arr[] = { 90, 82, 80, 70, 71, 81, 83, 91 };

  ch_xs_coords_set_arr (xs_coords_ptr, length, station_arr, elevation_arr);

  ASSERT_EQ (ch_xs_coords_length (xs_coords_ptr), length);

  for (size_t i = 0; i < length; i++)
    {
      ch_xs_coords_get (xs_coords_ptr, i, &station, &elevation);
      ASSERT_EQ (station, station_arr[i]);
      ASSERT_EQ (elevation, elevation_arr[i]);
    }

  ch_xs_coords_free (xs_coords_ptr);
}

TEST (ch_xs, coords_push)
{
  ChXSCoords *xs_coords_ptr = ch_xs_coords_new (1);

  float station, elevation;

  size_t length          = 8;
  float  station_arr[]   = { 210, 220, 260, 265, 270, 275, 300, 310 };
  float  elevation_arr[] = { 90, 82, 80, 70, 71, 81, 83, 91 };

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
}

int
main (int argc, char **argv)
{
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
