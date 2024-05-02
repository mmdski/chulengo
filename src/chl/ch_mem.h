#ifndef CH_MEM_H_
#define CH_MEM_H_

#include <stdlib.h>

#ifdef PY_BUILD
#define PY_SSIZE_T_CLEAN
#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

static inline void *
ch_malloc (size_t size)
{
  return PyMem_RawMalloc (size);
}

static inline void *
ch_realloc (void *ptr, size_t size)
{
  return PyMem_RawRealloc (ptr, size);
}

static inline void
ch_free (void *ptr)
{
  PyMem_RawFree (ptr);
}

#else

static inline void *
ch_malloc (size_t size)
{
  return malloc (size);
}

static inline void *
ch_realloc (void *ptr, size_t size)
{
  return realloc (ptr, size);
}

static inline void
ch_free (void *ptr)
{
  free (ptr);
}
#endif

#endif
