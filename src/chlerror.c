#include <glib.h>

GQuark
chl_error_quark (void)
{
  return g_quark_from_static_string ("chl-error-quark");
}
