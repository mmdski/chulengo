=======================
Cross section interface
=======================

Hydraulic cross section interface

Cross section coordinates
=========================

.. c:type:: ChlXSCoords

    .. code-block:: c

        typedef struct ChlXSCoords *ChlXSCoords;
    
    Array containing station, elevation coordinates for hydrualic cross 
    sections. See :c:func:`chl_xscoords_new`.

.. c:function:: ChlXSCoords chl_xscoords_new (int n, double *station, double *elevation, GError **error)

    Creates a new cross section coordinate array of length :c:data:`n`, and 
    station and elevation values of :c:data:`station` and :c:data:`elevation`, 
    respectively. The returned cross section is newly created and should be
    freed by :c:func:`chl_xscoords_free` when no longer in use.

    :c:func:`chl_xscoords_new` sets :c:data:`error` to :c:data:`CHL_ERROR_ARG`
    and returns `NULL` if

        - :c:data:`n` is less than 2,
        - :c:data:`station` is not in ascending order, or if
        - :c:data:`station` or :c:data:`elevation` contain non-finite values.

.. c:function:: void chl_xscoords_free (ChlXSCoords a)

    Frees a :c:type:`ChlXSCoords`.

.. c:function:: int chl_xscoords_equal (ChlXSCoords a1, ChlXSCoords a2)

    Returns 1 if :c:data`a1` and :c:data`a2` are equal and 0 otherwise.
