#ifndef CH_ARR_DBL_H_
#define CH_ARR_DBL_H_

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "ch_mem.h"

typedef struct
{
  size_t size;
  size_t length;
  double values[];
} ChArrDbl;

static inline ChArrDbl *
ch_arr_dbl_new (size_t size)
{
  assert (size);

  errno             = 0;
  ChArrDbl *arr_ptr = ch_malloc (sizeof (ChArrDbl) + sizeof (double) * size);

  if (NULL == arr_ptr || errno != 0)
    {
      perror ("malloc");
      exit (EXIT_FAILURE);
    }

  arr_ptr->size   = size;
  arr_ptr->length = 0;

  return arr_ptr;
}

static inline ChArrDbl *
ch_arr_dbl_realloc (ChArrDbl *arr_ptr, size_t size)
{
  assert (arr_ptr);
  assert (size);

  if (size == arr_ptr->size)
    return arr_ptr;

  errno = 0;
  ChArrDbl *new_arr_ptr =
      ch_realloc (arr_ptr, sizeof (ChArrDbl) + size * sizeof (double));
  if (NULL == new_arr_ptr || errno != 0)
    {
      perror ("realloc");
      exit (EXIT_FAILURE);
    }

  arr_ptr       = new_arr_ptr;
  arr_ptr->size = size;

  if (arr_ptr->length > arr_ptr->size)
    arr_ptr->length = size;

  return arr_ptr;
}

static inline void
ch_arr_dbl_free (ChArrDbl *arr_ptr)
{
  if (!arr_ptr)
    return;
  ch_free (arr_ptr);
}

double
ch_arr_dbl_get (ChArrDbl *arr_ptr, size_t index)
{
  assert (arr_ptr);
  assert (index < arr_ptr->length);
  return arr_ptr->values[index];
}

void
ch_arr_dbl_set (ChArrDbl *arr_ptr, size_t index, double value)
{
  assert (arr_ptr);
  assert (index < arr_ptr->length);
  arr_ptr->values[index] = value;
}

static inline ChArrDbl *
ch_arr_dbl_push (ChArrDbl *arr_ptr, double value)
{
  assert (arr_ptr);

  size_t length = arr_ptr->length;

  if (length == arr_ptr->size)
    arr_ptr = ch_arr_dbl_realloc (arr_ptr, 2 * arr_ptr->size);

  arr_ptr->values[length] = value;
  arr_ptr->length         = length + 1;

  return arr_ptr;
}

#endif
