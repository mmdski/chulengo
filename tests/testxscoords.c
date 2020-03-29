#include <chulengo.h>
#include <glib.h>

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

int
main (int argc, char *argv[])
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/chl/xscoords/new/success", test_xscoarray_new);

  return g_test_run ();
}
