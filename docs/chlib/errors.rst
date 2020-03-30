===============
Chulengo errors
===============

Library level errors

See `GLib Error Reporting <https://developer.gnome.org/glib/stable/glib-Error-Reporting.html>`_
for more information on handling errors.

.. c:var:: CHL_ERROR

    Domain of chl level errors.

    .. code-block:: c

        #define CHL_ERROR chl_error_quark ()

        GQuark chl_error_quark (void)

.. c:type:: ChlError

    Enumeration of chl errors.

    .. code-block:: c

        enum ChlError
        {
            CHL_ERROR_ARG
        };

.. c:var:: CHL_ERROR_ARG

    Error set when invalid arguments are passed to a function.
