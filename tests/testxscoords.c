#include <chulengo.h>
#include <glib.h>
#include <math.h>

void
test_xscoords_new (void)
{
  int    n           = 4;
  double station[]   = { 0, 1, 2, 3 };
  double elevation[] = { 0, 1, 2, 3 };

  GError *error = NULL;

  ChlXSCoords ca = chl_xscoords_new (n, station, elevation, &error);

  g_assert_nonnull (ca);
  g_assert_null (error);

  chl_xscoords_free (ca);
  ca = NULL;

  // one coordinate
  ca = chl_xscoords_new (1, station, elevation, &error);
  g_assert_null (error);
  g_assert_nonnull (ca);
  chl_xscoords_free (ca);
  ca = NULL;

  // zero coordinates
  ca = chl_xscoords_new (0, NULL, NULL, &error);
  g_assert_null (error);
  g_assert_nonnull (ca);
  chl_xscoords_free (ca);
  ca = NULL;

  // negative n
  ca = chl_xscoords_new (-1, NULL, NULL, &error);
  g_assert_null (ca);
  g_assert_nonnull (&error);
  g_assert_true (g_error_matches (error, CHL_ERROR, CHL_ERROR_ARG));
  g_clear_error (&error);

  // non-ascending station
  station[0] = 1;
  station[1] = 0;
  ca         = chl_xscoords_new (n, station, elevation, &error);
  g_assert_null (ca);
  g_assert_nonnull (&error);
  g_assert_true (g_error_matches (error, CHL_ERROR, CHL_ERROR_ARG));
  g_clear_error (&error);

  // non-finite station
  station[1] = NAN;
  ca         = chl_xscoords_new (n, station, elevation, &error);
  g_assert_null (ca);
  g_assert_nonnull (&error);
  g_assert_true (g_error_matches (error, CHL_ERROR, CHL_ERROR_ARG));
  g_clear_error (&error);

  // non-finite elevation
  station[1]   = 1;
  elevation[1] = NAN;
  ca           = chl_xscoords_new (n, station, elevation, &error);
  g_assert_null (ca);
  g_assert_nonnull (&error);
  g_assert_true (g_error_matches (error, CHL_ERROR, CHL_ERROR_ARG));
  g_clear_error (&error);

  // non-finite station and elevation
  station[1]   = NAN;
  elevation[1] = NAN;
  ca           = chl_xscoords_new (n, station, elevation, &error);
  g_assert_null (ca);
  g_assert_nonnull (&error);
  g_assert_true (g_error_matches (error, CHL_ERROR, CHL_ERROR_ARG));
  g_clear_error (&error);
}

void
test_xscoords_equal (void)
{
  int    n1   = 4;
  int    n4   = 2;
  double y1[] = { 0, 1, 2, 3 };
  double z1[] = { 0, 1, 2, 3 };
  double y2[] = { 4, 5, 6, 7 };
  double z2[] = { 4, 5, 6, 7 };

  GError *error = NULL;

  ChlXSCoords ca1 = chl_xscoords_new (n1, y1, z1, &error);
  g_assert_null (error);

  ChlXSCoords ca2 = chl_xscoords_new (n1, y1, z1, &error);
  g_assert_null (error);

  ChlXSCoords ca3 = chl_xscoords_new (n1, y2, z2, &error);
  g_assert_null (error);

  ChlXSCoords ca4 = chl_xscoords_new (n4, y2, z2, &error);

  g_assert_cmpint (chl_xscoords_equal (ca1, ca1), ==, 1);
  g_assert_cmpint (chl_xscoords_equal (ca1, ca2), ==, 1);
  g_assert_cmpint (chl_xscoords_equal (ca1, ca3), ==, 0);
  g_assert_cmpint (chl_xscoords_equal (ca1, ca4), ==, 0);

  chl_xscoords_free (ca1);
  chl_xscoords_free (ca2);
  chl_xscoords_free (ca3);
  chl_xscoords_free (ca4);
}

void
test_xscoords_length (void)
{
  int    n           = 4;
  double station[]   = { 0, 1, 2, 3 };
  double elevation[] = { 0, 1, 2, 3 };

  GError *error = NULL;

  ChlXSCoords ca = chl_xscoords_new (n, station, elevation, &error);
  g_assert_null (error);

  g_assert_cmpint (chl_xscoords_length (ca), ==, n);

  chl_xscoords_free (ca);
}

void
test_xscoords_isempty (void)
{
  int    n           = 4;
  double station[]   = { 0, 1, 2, 3 };
  double elevation[] = { 0, 1, 2, 3 };

  GError *error = NULL;

  ChlXSCoords ca = chl_xscoords_new (n, station, elevation, &error);
  g_assert_null (error);
  g_assert_cmpint (chl_xscoords_isempty (ca), ==, 0);
  chl_xscoords_free (ca);
  ca = NULL;

  ca = chl_xscoords_new (0, NULL, NULL, &error);
  g_assert_null (error);
  g_assert_nonnull (ca);
  g_assert_cmpint (chl_xscoords_isempty (ca), ==, 1);
  chl_xscoords_free (ca);
}

void
test_xscoords_copy (void)
{
  int    n           = 4;
  double station[]   = { 0, 1, 2, 3 };
  double elevation[] = { 0, 1, 2, 3 };

  GError *error = NULL;

  ChlXSCoords a = chl_xscoords_new (n, station, elevation, &error);
  ChlXSCoords b = chl_xscoords_copy (a);
  g_assert_cmpint (chl_xscoords_equal (a, b), ==, 1);

  chl_xscoords_free (a);
  chl_xscoords_free (b);
}

void
test_xscoords_elevation (void)
{
  int    n           = 4;
  double station[]   = { 0, 1, 2, 3 };
  double elevation[] = { 4, 5, 6, 7 };

  double s;

  GError *error = NULL;

  ChlXSCoords a = chl_xscoords_new (n, station, elevation, &error);
  g_assert_null (error);

  for (int i = 0; i < n; i++)
    {
      g_assert_cmpfloat (
          chl_xscoords_elevation (a, i, &error), ==, elevation[i]);
      g_assert_null (error);
    }

  s = chl_xscoords_elevation (a, -1, &error);
  g_assert_true (isinf (s));
  g_assert_cmpfloat (s, <, 0);
  g_assert_true (g_error_matches (error, CHL_ERROR, CHL_ERROR_INDEX));
  g_clear_error (&error);

  s = chl_xscoords_elevation (a, 5, &error);
  g_assert_true (isinf (s));
  g_assert_cmpfloat (s, <, 0);
  g_assert_true (g_error_matches (error, CHL_ERROR, CHL_ERROR_INDEX));
  g_clear_error (&error);

  chl_xscoords_free (a);
}

void
test_xscoords_station (void)
{
  int    n           = 4;
  double station[]   = { 0, 1, 2, 3 };
  double elevation[] = { 4, 5, 6, 7 };

  double s;

  GError *error = NULL;

  ChlXSCoords a = chl_xscoords_new (n, station, elevation, &error);
  g_assert_null (error);

  for (int i = 0; i < n; i++)
    {
      g_assert_cmpfloat (chl_xscoords_station (a, i, &error), ==, station[i]);
      g_assert_null (error);
    }

  s = chl_xscoords_station (a, -1, &error);
  g_assert_true (isinf (s));
  g_assert_cmpfloat (s, <, 0);
  g_assert_true (g_error_matches (error, CHL_ERROR, CHL_ERROR_INDEX));
  g_clear_error (&error);

  s = chl_xscoords_station (a, 5, &error);
  g_assert_true (isinf (s));
  g_assert_cmpfloat (s, <, 0);
  g_assert_true (g_error_matches (error, CHL_ERROR, CHL_ERROR_INDEX));
  g_clear_error (&error);

  chl_xscoords_free (a);
}

void
test_xscoords_max_elev (void)
{
  int    n           = 5;
  double station[]   = { 0, 1, 2, 3, 4 };
  double elevation[] = { 4, 3, 0, 2, 3 };

  GError *error = NULL;

  ChlXSCoords a = chl_xscoords_new (n, station, elevation, &error);
  g_assert_null (error);

  g_assert_cmpfloat (chl_xscoords_max_elev (a), ==, 4);
  chl_xscoords_free (a);
}

void
test_xscoords_min_elev (void)
{
  int    n           = 5;
  double station[]   = { 0, 1, 2, 3, 4 };
  double elevation[] = { 4, 3, 0, 2, 3 };

  GError *error = NULL;

  ChlXSCoords a = chl_xscoords_new (n, station, elevation, &error);
  g_assert_null (error);

  g_assert_cmpfloat (chl_xscoords_min_elev (a), ==, 0);
  chl_xscoords_free (a);
}

void
test_xscoords_sub_station_simple_error (void)
{
  int    n           = 5;
  double station[]   = { 0, 0, 0.5, 1, 1 };
  double elevation[] = { 1, 0, 0, 0, 1 };

  GError *error = NULL;

  ChlXSCoords ca = chl_xscoords_new (n, station, elevation, &error);
  g_assert_null (error);

  ChlXSCoords sa =
      chl_xscoords_sub_station (ca, station[0], station[4], &error);
  g_assert_null (error);

  g_assert_true (chl_xscoords_equal (ca, sa) == 1);

  chl_xscoords_free (sa);
  sa = NULL;

  sa = chl_xscoords_sub_station (ca, -1, 1, &error);
  g_assert_null (sa);
  g_assert_nonnull (error);
  g_assert_true (g_error_matches (error, CHL_ERROR, CHL_ERROR_ARG));
  g_clear_error (&error);

  sa = chl_xscoords_sub_station (ca, 0, 2, &error);
  g_assert_null (sa);
  g_assert_nonnull (error);
  g_assert_true (g_error_matches (error, CHL_ERROR, CHL_ERROR_ARG));
  g_clear_error (&error);

  sa = chl_xscoords_sub_station (ca, -10, 10, &error);
  g_assert_null (sa);
  g_assert_nonnull (error);
  g_assert_true (g_error_matches (error, CHL_ERROR, CHL_ERROR_ARG));
  g_clear_error (&error);

  sa = chl_xscoords_sub_station (ca, 1, 0, &error);
  g_assert_null (sa);
  g_assert_nonnull (error);
  g_assert_true (g_error_matches (error, CHL_ERROR, CHL_ERROR_ARG));
  g_clear_error (&error);

  chl_xscoords_free (ca);
}

void
test_xscoords_sub_station_double_triangle ()
{
  int    n           = 9;
  double station[]   = { 0, 0.25, 0.5, 0.75, 1, 1.25, 1.5, 1.75, 2 };
  double elevation[] = { 1, 0.5, 0, 0.5, 1, 0.5, 0, 0.5, 1 };
  double stat_exp1[] = { 0, 0.25, 0.5, 0.75, 1 };
  double elev_exp1[] = { 1, 0.5, 0, 0.5, 1 };
  double stat_exp2[] = { 1, 1.25, 1.5, 1.75, 2 };
  double elev_exp2[] = { 1, 0.5, 0, 0.5, 1 };

  GError *error = NULL;

  ChlXSCoords ca = chl_xscoords_new (n, station, elevation, &error);
  g_assert_null (error);

  ChlXSCoords expected1 = chl_xscoords_new (5, stat_exp1, elev_exp1, &error);
  g_assert_null (error);
  ChlXSCoords sa1 = chl_xscoords_sub_station (ca, 0, 1, &error);
  g_assert_null (error);

  g_assert_true (chl_xscoords_equal (expected1, sa1) == 1);
  chl_xscoords_free (sa1);
  chl_xscoords_free (expected1);

  ChlXSCoords expected2 = chl_xscoords_new (5, stat_exp2, elev_exp2, &error);
  g_assert_null (error);
  ChlXSCoords sa2 = chl_xscoords_sub_station (ca, 1, 2, &error);
  g_assert_null (error);

  g_assert_true (chl_xscoords_equal (expected2, sa2) == 0);
  chl_xscoords_free (sa2);
  chl_xscoords_free (expected2);

  chl_xscoords_free (ca);
}

void
test_xscoords_sub_station (void)
{
  test_xscoords_sub_station_simple_error ();
  test_xscoords_sub_station_double_triangle ();
}

int
main (int argc, char *argv[])
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/chl/xscoords/new", test_xscoords_new);
  g_test_add_func ("/chl/xscoords/eq", test_xscoords_equal);
  g_test_add_func ("/chl/xscoords/length", test_xscoords_length);
  g_test_add_func ("/chl/xscoords/isempty", test_xscoords_isempty);
  g_test_add_func ("/chl/xscoords/copy", test_xscoords_copy);
  g_test_add_func ("/chl/xscoords/elevation", test_xscoords_elevation);
  g_test_add_func ("/chl/xscoords/station", test_xscoords_station);
  g_test_add_func ("/chl/xscoords/max elev", test_xscoords_max_elev);
  g_test_add_func ("/chl/xscoords/min elev", test_xscoords_min_elev);
  g_test_add_func ("/chl/xscoords/sub station", test_xscoords_sub_station);

  return g_test_run ();
}
