#include <glib.h>

void *
chl_alloc (long nbytes)
{
  return g_malloc (nbytes);
}

void *
chl_calloc (long count, long nbytes)
{
  return g_malloc_n (count, nbytes);
}

void
chl_free (void *ptr)
{
  g_free (ptr);
}
