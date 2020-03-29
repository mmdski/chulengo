#include <chulengo.h>
#include <glib.h>
#include <math.h>

void
test_xscoarray_new (void)
{
  int    n   = 4;
  double y[] = { 0, 1, 2, 3 };
  double z[] = { 0, 1, 2, 3 };

  GError **error = NULL;

  ChlXSCoords ca = chl_xscoords_new (n, y, z, error);

  g_assert_nonnull (ca);
  g_assert_null (error);

  chl_xscoords_free (ca);
}

void
test_xscoarray_new_argerror (void)
{
  int    n           = 4;
  double station[]   = { 1, 0, 2, 3 };
  double elevation[] = { 0, 1, 2, 3 };

  GError *error = NULL;

  ChlXSCoords ca = NULL;

  // one coordinate
  ca = chl_xscoords_new (1, station, elevation, &error);
  g_assert_null (ca);
  g_assert_nonnull (&error);
  g_assert_true (g_error_matches (error, CHL_ERROR, CHL_ERROR_ARG));
  g_clear_error (&error);

  // non-ascending station
  ca = chl_xscoords_new (n, station, elevation, &error);
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

int
main (int argc, char *argv[])
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/chl/xscoords/new/success", test_xscoarray_new);
  g_test_add_func ("/chl/xscoords/new/argerror", test_xscoarray_new_argerror);

  return g_test_run ();
}
