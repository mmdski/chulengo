====================
Finite volume method
====================

The :math:`i` th grid cell is represented by

.. math:: \mathscr{C}_i = \left(x_{i-1/2},x_{i+1/2}\right).

:math:`Q^n_i` approximates the average value of :math:`q` in the :math:`i` th
grid cell so that

.. math:: Q^n_i
    \approx \frac{1}{\Delta x}\int_{x_{i-1/2}}^{x_{i+1/2}}q\left(x,t_n\right)dx
    \equiv \frac{1}{\Delta x}\int_{\mathscr{C}_i}q\left(x,t_n\right)dx

The integral form gives

.. math:: \frac{d}{dt}\int_{\mathscr{C}_i}q\left(x,t\right) =
    f\left(q\left(x_{i-1/2},t\right)\right) -
    f\left(q\left(x_{i+1/2},t\right)\right).

.. math:: Q^{n+1}_i = Q^n_i - \frac{\Delta t}{\Delta x}
    \left(F^n_{i+1/2} - F^n_{i-1/2}\right)

Where :math:`F^n_{i-1/2}` is an approximation of the average flux along
:math:`x=x_{i-1/2}`

.. math:: F^n_{i-1/2} \approx
    \frac{1}{\Delta t} \int_{t_n}^{t_{n+1}} f\left(q\left(x_{i-1/2},t\right)\right)dt

.. math:: F^n_{i-1/2} = \mathscr{F}\left(Q^n_{i-1},Q^n_{i}\right)

:math:`\mathscr{F}` is a numerical flux function

.. math:: Q^{n+1}_i = Q^n_i - \frac{\Delta t}{\Delta x}
    \left[\mathscr{F}\left(Q^n_i,Q^n_{i+1}\right) -
    \mathscr{F}\left(Q^n_{i-1},Q^n_i\right)\right]

-------------
REA algorithm
-------------

- 1. **Reconstruct**

    Reconstruct a piecewise polynomial function :math:`\tilde{q}`

    .. math:: \tilde{q}\left(x,t_n\right) = Q^n_i \forall x \in \mathscr{C}_i

- 2. **Evolve**

    Evolve to obtain :math:`\tilde{q}\left(x,t_{n+1}\right)` for a time
    :math:`\Delta t` later.

- 3. **Average**

    Average :math:`\tilde{q}` over each grid cell

    .. math:: Q^{n+1}_i = \frac{1}{\Delta x}\int_{\mathscr{C}_i}
        \tilde{q}^n\left(x,t_{n+1}\right)dx.

---------------------
Wave propagation form
---------------------

.. math:: Q^{n+1}_i = Q^n_i - \frac{\Delta t}{\Delta x}
    \left(\mathscr{A}^+\Delta Q_{i-1/2} + \mathscr{A}^-\Delta Q_{i+1/2}\right)

.. math:: \Delta Q_{i-1/2} = Q_i - Q_{i-1}


.. toctree::
   :maxdepth: 2

   linear
   nonlinear
   limiters
