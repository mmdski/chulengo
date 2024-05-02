#include <gtest/gtest.h>

extern "C"
{
#include <math.h>

#include <chl.h>
}

namespace
{
TEST (ChXSDef, mem)
{
  size_t length      = 43;
  double station[]   = { 0.0,    16.0,   56.0,   59.0,   203.0,  249.0,  394.0,
                         407.0,  410.0,  417.0,  427.0,  433.0,  518.0,  568.0,
                         584.0,  591.0,  597.0,  636.0,  712.0,  732.0,  768.0,
                         787.0,  823.0,  837.0,  863.0,  879.0,  902.0,  925.0,
                         1053.0, 1102.0, 1129.0, 1184.0, 1204.0, 1224.0, 1348.0,
                         1490.0, 1535.0, 1542.0, 1558.0, 1755.0, 1850.0, 1969.0,
                         1988.0 };
  double elevation[] = { 212.8, 212.1, 210.1, 209.3, 209.1, 207.4, 205.8, 205.2,
                         201.0, 199.9, 201.1, 203.5, 209.0, 208.2, 203.9, 198.6,
                         203.8, 207.3, 206.7, 206.1, 205.9, 206.7, 207.7, 207.8,
                         206.8, 206.2, 207.2, 209.0, 210.5, 209.9, 209.7, 209.6,
                         209.0, 208.8, 208.6, 209.1, 209.2, 207.7, 209.3, 209.8,
                         210.0, 212.2, 213.4 };

  size_t n_roughness     = 3;
  double roughness_sta[] = { 0, 394, 518 };
  double roughness[]     = { 0.1, 0.04, 0.1 };

  double bank_stations[] = { 394, 518 };

  ChXSDef *xs_def_ptr = ch_xs_def_new ();
  ch_xs_def_set_coordinates (xs_def_ptr, length, station, elevation);
  ch_xs_def_set_roughness (xs_def_ptr, n_roughness, roughness, roughness_sta);
  ch_xs_def_set_banks (xs_def_ptr, bank_stations[0], bank_stations[1]);

  ch_xs_def_free (xs_def_ptr);
}
}

int
main (int argc, char **argv)
{
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
