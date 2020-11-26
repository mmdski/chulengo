===================
Nonlinear equations
===================

Scalar equation
===============

.. math:: q_t + f\left(q\right)_x = 0

Quasi-linear form

.. math:: q_t + f\left(q\right)'q_x = 0

Direct form
===========

.. math:: Q^{n+1}_i = Q_i -
    \frac{\Delta t}{\Delta x}\left(\mathscr{A}^{+}\Delta Q_{i-1/2} 
    + \mathscr{A}^{-}\Delta Q_{i+1/2}\right) -
    \frac{\Delta t}{\Delta x}\left(\tilde{F}_{i+1/2}-\tilde{F}_{i-1/2}\right)

.. math:: \mathscr{A}^+\Delta Q_{i-1/2} =
    \sum^m_{p=1}\left(s^p_{1-1/2}\right)^+\mathscr{W}^p_{i-1/2}

.. math:: \mathscr{A}^-\Delta Q_{i-1/2} =
    \sum^m_{p=1}\left(s^p_{1-1/2}\right)^-\mathscr{W}^p_{i-1/2}

.. math:: \tilde{F}_{i-1/2} =
    \frac{1}{2}\sum^m_{p=1}\lvert s^p_{1-1/2}\rvert
    \left(1 - \frac{\Delta t}{\Delta x}\lvert s^p_{1-1/2}\rvert\right)
    \tilde{\mathscr{W}}^p_{i-1/2}
