#include <gtest/gtest.h>

extern "C"
{
#include <math.h>

#include <chlib.h>
}

namespace
{

TEST (ChXSSubSect, mem)
{
  size_t      length          = 4;
  double      station_arr[]   = { 0, 0, 1, 1 };
  double      elevation_arr[] = { 1, 0, 0, 1 };
  ChXSCoords *coords_ptr =
      ch_xs_coords_set_arr (NULL, length, station_arr, elevation_arr);

  ChXSSubSect *subsect_ptr = ch_xs_subsect_new (0.040, coords_ptr);
  ASSERT_TRUE (subsect_ptr);

  ch_xs_subsect_free (subsect_ptr);
}

TEST (ChXSSubSect, props)
{
  size_t      length          = 4;
  double      station_arr[]   = { 0, 0, 1, 1 };
  double      elevation_arr[] = { 1, 0, 0, 1 };
  ChXSCoords *coords_ptr =
      ch_xs_coords_set_arr (NULL, length, station_arr, elevation_arr);

  ChXSSubSect *subsect_ptr = ch_xs_subsect_new (0.040, coords_ptr);
  ASSERT_TRUE (subsect_ptr);

  double props[kChXSNProps];

  ch_xs_subsect_props (subsect_ptr, 0.1, props);

  ch_xs_subsect_free (subsect_ptr);
}
}

int
main (int argc, char **argv)
{
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
