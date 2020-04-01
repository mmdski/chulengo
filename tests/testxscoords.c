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
  g_assert_cmpint (isinf (s), ==, -1);
  g_assert_true (g_error_matches (error, CHL_ERROR, CHL_ERROR_INDEX));
  g_clear_error (&error);

  s = chl_xscoords_elevation (a, 5, &error);
  g_assert_cmpint (isinf (s), ==, -1);
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
  g_assert_cmpint (isinf (s), ==, -1);
  g_assert_true (g_error_matches (error, CHL_ERROR, CHL_ERROR_INDEX));
  g_clear_error (&error);

  s = chl_xscoords_station (a, 5, &error);
  g_assert_cmpint (isinf (s), ==, -1);
  g_assert_true (g_error_matches (error, CHL_ERROR, CHL_ERROR_INDEX));
  g_clear_error (&error);

  chl_xscoords_free (a);
}

int
main (int argc, char *argv[])
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/chl/xscoords/new", test_xscoords_new);
  g_test_add_func ("/chl/xscoords/eq", test_xscoords_equal);
  g_test_add_func ("/chl/xscoords/copy", test_xscoords_copy);
  g_test_add_func ("/chl/xscoords/elevation", test_xscoords_elevation);
  g_test_add_func ("/chl/xscoords/station", test_xscoords_station);

  return g_test_run ();
}
