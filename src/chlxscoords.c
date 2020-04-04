#include "chlmem.h"
#include <chulengo/chlxscoords.h>
#include <math.h>

/**
 * XSCoordinate:
 * @station: lateral value of coordinate
 * @elevation: vertical value of coordinate
 *
 * station, elevation coordinate
 */

typedef struct XSCoordinate
{
  double station;   /* lateral coordinate */
  double elevation; /* elevation coordinate */
} XSCoordinate;

/**
 * xscoord_new:
 * @station: lateral value of coordinate
 * @elevation: vertical value of coordinate
 *
 * Creates a new coordinate with @station and @elevation as the lateral and
 * vertical values, respectively. The resulting coordinate is newly allocated
 * and should be freed with xscoord_free().
 *
 * Returns: a new coordinate
 */
XSCoordinate *
xscoord_new (double station, double elevation)
{
  XSCoordinate *c = chl_alloc (sizeof (XSCoordinate));

  c->station   = station;
  c->elevation = elevation;

  return c;
}

/**
 * xscoord_copy:
 * @c: a #XSCoordinate
 *
 * Creates a new copy of @c. The returned coordinate is newly created and
 * should be freed using coord_free().
 *
 * Returns: a copy of @c
 */
XSCoordinate *
xscoord_copy (XSCoordinate *c)
{
  g_assert (c);
  return xscoord_new ((c->station), (c->elevation));
}

/**
 * xscoord_free:
 * @c: a #XSCoordinate
 *
 * Frees a coordinate
 *
 * Returns: nothing
 */
void
xscoord_free (XSCoordinate *c)
{
  chl_free (c);
}

/**
 * xscoord_eq:
 * @c1: a #XSCoordinate
 * @c2: another #XSCoordinate
 *
 * Returns: 1 if @c1 and @c2 are equal, 0 otherwise
 */
int
xscoord_eq (XSCoordinate *c1, XSCoordinate *c2)
{
  if (c1 == c2)
    return 1;
  /* either coordinate is NULL */
  if (!c1 || !c2)
    return 0;

  if (c1->station == c2->station && c1->elevation == c2->elevation)
    return 1;
  else
    return 0;
}

/**
 * xscoord_interpelevation:
 * @c1: a #XSCoordinate
 * @c2: another #XSCoordinate
 * @station: lateral value
 *
 * Creates a new coordinate with an @elevation that is linearly interpolated
 * using the values of @c1 and @c2 and @elevation. The new coordinate will have
 * a vertical value that is equal to the interpolated value and a lateral value
 * equal to @station. The returned coordinate is newly created and should be
 * freed using @xscoord_free().
 *
 * Returns: an interpolated coordinate
 */
XSCoordinate *
xscoord_interpelevation (XSCoordinate *c1, XSCoordinate *c2, double station)
{
  g_assert (c1 && c2);

  /* assert station is between the two points */
  g_assert ((c1->station <= station && station <= c2->station) ||
            (c2->station <= station && station <= c1->station));

  double slope = (c2->elevation - c1->elevation) / (c2->station - c1->station);
  double elevation = slope * (station - c1->station) + c1->elevation;
  return xscoord_new (station, elevation);
}

/**
 * xscoord_interpstation:
 * @c1: a #XSCoordinate
 * @c2: another #XSCoordinate
 * @elevation: vertical value
 *
 * Creates a new coordinate with a @station that is linearly interpolated using
 * the values of @c1 and @c2 and @elevation. The new coordinate will have a
 * lateral value that is equal to the interpolated value and a vertical value
 * equal to @elevation. The returned coordinate is newly created and should be
 * freed using @coord_free().
 *
 * Returns: an interpolated coordinate
 */
XSCoordinate *
xscoord_interpstation (XSCoordinate *c1, XSCoordinate *c2, double elevation)
{
  g_assert (c1 && c2);

  /* assert z is between the two points */
  g_assert ((c1->elevation <= elevation && elevation <= c2->elevation) ||
            (c2->elevation <= elevation && elevation <= c1->elevation));

  double slope = (c2->station - c1->station) / (c2->elevation - c1->elevation);
  double station = slope * (elevation - c1->elevation) + c1->station;
  return xscoord_new (station, elevation);
}

struct ChlXSCoords
{
  int            length;        /* number of coordinates in this array */
  double         max_elevation; /* maximum elevation in coarray */
  double         min_elevation; /* minimum elevation in coarray */
  XSCoordinate **coordinates;   /* array of coordinates */
};

ChlXSCoords
chl_xscoords_new (int n, double *station, double *elevation, GError **error)
{

  g_return_val_if_fail (station != NULL || elevation != NULL, NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (n < 2)
    {
      g_set_error (error,
                   CHL_ERROR,
                   CHL_ERROR_ARG,
                   "n must be greater than or equal to 2");
      return NULL;
    }

  // check that station points are in ascending order before allocating any
  // memory on the heap
  for (int i = 0; i < n; i++)
    {
      if (i > 0)
        {
          if (*(station + i - 1) > *(station + i))
            {
              g_set_error (error,
                           CHL_ERROR,
                           CHL_ERROR_ARG,
                           "station must be in ascending order");
              return NULL;
            }
        }
      if (!isfinite (*(station + i)) || !isfinite (*(elevation + i)))
        {
          g_set_error (error,
                       CHL_ERROR,
                       CHL_ERROR_ARG,
                       "station and elevation values must be finite");
          return NULL;
        }
    }

  double max_y = -INFINITY;
  double min_y = INFINITY;

  ChlXSCoords a;
  NEW (a);

  XSCoordinate **coords = chl_calloc (sizeof (XSCoordinate *), n);

  for (int i = 0; i < n; i++)
    {
      *(coords + i) = xscoord_new (*(station + i), *(elevation + i));

      if (*(station + i) > max_y)
        max_y = *(station + i);
      if (*(station + i) < min_y)
        min_y = *(station + i);
    }

  a->length        = n;
  a->coordinates   = coords;
  a->max_elevation = max_y;
  a->min_elevation = min_y;

  return a;
}

static ChlXSCoords
chl_xscoords_from_array (int n, XSCoordinate **array)
{
  g_assert (array);
  g_assert (n > 2);

  XSCoordinate * c;
  XSCoordinate **coordinates = chl_calloc (n, sizeof (XSCoordinate *));
  double         max_elev    = -INFINITY;
  double         min_elev    = INFINITY;

  for (int i = 0; i < n; i++)
    {
      c                  = *(array + i);
      *(coordinates + i) = c;
      if (c)
        {
          if (c->elevation > max_elev)
            max_elev = c->elevation;
          if (c->elevation < min_elev)
            min_elev = c->elevation;
        }
    }

  ChlXSCoords a;
  NEW (a);
  a->coordinates   = coordinates;
  a->length        = n;
  a->max_elevation = max_elev;
  a->min_elevation = min_elev;

  return a;
}

void
chl_xscoords_free (ChlXSCoords a)
{
  g_return_if_fail (a != NULL);

  int           length = a->length;
  XSCoordinate *c;
  for (int i = 0; i < length; i++)
    {
      c = *(a->coordinates + i);
      xscoord_free (c);
    }

  chl_free (a->coordinates);

  FREE (a);
}

int
chl_xscoords_equal (ChlXSCoords a1, ChlXSCoords a2)
{

  g_return_val_if_fail (a1 != NULL && a2 != NULL, -1);

  if (a1 == a2)
    return 1;

  if (a1->length != a2->length)
    return 0;

  int n = a1->length;

  for (int i = 0; i < n; i++)
    {
      if (!xscoord_eq (*(a1->coordinates + i), *(a2->coordinates + i)))
        return 0;
    }

  if (a1->max_elevation != a2->max_elevation)
    return 0;
  if (a1->min_elevation != a2->min_elevation)
    return 0;

  return 1;
}

ChlXSCoords
chl_xscoords_copy (ChlXSCoords a)
{
  g_return_val_if_fail (a != NULL, NULL);

  int n = a->length;

  XSCoordinate **coordinates = chl_calloc (n, sizeof (XSCoordinate *));

  for (int i = 0; i < n; i++)
    *(coordinates + i) = xscoord_copy (*(a->coordinates + i));

  ChlXSCoords b = chl_xscoords_from_array (n, coordinates);
  chl_free (coordinates);

  return b;
}

double
chl_xscoords_elevation (ChlXSCoords a, int i, GError **error)
{
  g_assert_nonnull (a);
  g_return_val_if_fail (error == NULL || *error == NULL, -INFINITY);

  if (i < 0 || a->length - 1 < i)
    {
      g_set_error (
          error, CHL_ERROR, CHL_ERROR_INDEX, "Index out of bounds: %i", i);
      return -INFINITY;
    }

  XSCoordinate *c = *(a->coordinates + i);

  if (c)
    return c->elevation;
  else
    return NAN;
}

double
chl_xscoords_station (ChlXSCoords a, int i, GError **error)
{
  g_assert_nonnull (a);
  g_return_val_if_fail (error == NULL || *error == NULL, -INFINITY);

  if (i < 0 || a->length - 1 < i)
    {
      g_set_error (
          error, CHL_ERROR, CHL_ERROR_INDEX, "Index out of bounds: %i", i);
      return -INFINITY;
    }

  XSCoordinate *c = *(a->coordinates + i);

  if (c)
    return c->station;
  else
    return NAN;
}

double
chl_xscoords_max_elev (ChlXSCoords a)
{
  g_return_val_if_fail (a != NULL, -INFINITY);

  return a->max_elevation;
}

double
chl_xscoords_min_elev (ChlXSCoords a)
{
  g_return_val_if_fail (a != NULL, -INFINITY);

  return a->min_elevation;
}

/* helper functions for chl_xscoords_sub_station */
static int
find_stat_lo_idx (ChlXSCoords a, int lo, int hi, double stat_lo)
{
  if (lo == hi)
    {
      while (lo > 0 && a->coordinates[lo - 1]->station >= stat_lo)
        {
          lo--;
        }
      return a->coordinates[lo]->station <= stat_lo ? lo : -1;
    }

  int mid = (hi + lo) / 2;

  if (stat_lo < a->coordinates[mid]->station)
    return find_stat_lo_idx (a, lo, mid, stat_lo);

  int ret = find_stat_lo_idx (a, mid + 1, hi, stat_lo);

  return ret == -1 ? mid : ret;
}

static int
find_stat_hi_idx (ChlXSCoords a, int n, int lo, int hi, double stat_hi)
{
  if (lo == hi)
    {
      while (hi < n - 1 && a->coordinates[hi + 1]->station <= stat_hi)
        {
          hi++;
        }
      return a->coordinates[hi]->station >= stat_hi ? hi : -1;
    }

  int mid = (hi + lo) / 2;

  if (stat_hi <= a->coordinates[mid]->station)
    return find_stat_hi_idx (a, n, lo, mid, stat_hi);

  int ret = find_stat_hi_idx (a, n, mid + 1, hi, stat_hi);

  return ret == -1 ? mid : ret;
}

ChlXSCoords
chl_xscoords_sub_station (ChlXSCoords a,
                          double      left,
                          double      right,
                          GError **   error)
{
  g_return_val_if_fail (a != NULL, NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  int n = a->length;

  if (right <= left)
    {
      g_set_error (
          error, CHL_ERROR, CHL_ERROR_ARG, "right must be greater than left");
      return NULL;
    }

  if (left < a->coordinates[0]->station ||
      a->coordinates[n - 1]->station < right)
    {
      g_set_error (error,
                   CHL_ERROR,
                   CHL_ERROR_ARG,
                   "left and right must be within the range of the stations of "
                   "the corrdinate array");
      return NULL;
    }

  int i  = find_stat_lo_idx (a, 0, n, left);
  int j  = 0;
  int hi = find_stat_hi_idx (a, n, 0, n, right);

  XSCoordinate * c0;
  XSCoordinate * c1;
  XSCoordinate **array = chl_calloc (n, sizeof (XSCoordinate *));

  c0 = a->coordinates[i];
  c1 = a->coordinates[i + 1];

  double eps = 1e-10;

  if (fabs (c1->station - c0->station) <= eps)
    array[j++] = xscoord_copy (c0);
  else
    array[j++] = xscoord_interpelevation (c0, c1, left);

  while (++i < hi)
    array[j++] = xscoord_copy (a->coordinates[i]);

  c0 = a->coordinates[i - 1];
  c1 = a->coordinates[i];
  if (fabs (c1->station - c0->station) <= eps)
    array[j++] = xscoord_copy (c1);
  else
    array[j++] = xscoord_interpelevation (c0, c1, right);

  ChlXSCoords sa = chl_xscoords_from_array (j, array);
  chl_free (array);

  return sa;
}
