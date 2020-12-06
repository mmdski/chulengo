===================
Nonlinear equations
===================

.. math:: q_t + f\left(q\right)_x = 0

Quasi-linear form

.. math:: q_t + f'\left(q\right)q_x = 0

Scalar equation
===============

.. math:: Q^{n+1}_i = Q_i -
    \frac{\Delta t}{\Delta x}\left(\mathscr{A}^{+}\Delta Q_{i-1/2}
    + \mathscr{A}^{-}\Delta Q_{i+1/2}\right) -
    \frac{\Delta t}{\Delta x}\left(\tilde{F}_{i+1/2}-\tilde{F}_{i-1/2}\right)

.. math:: \mathscr{A}^+\Delta Q_{i-1/2} = s_{1-1/2}^+\mathscr{W}_{i-1/2}

.. math:: \mathscr{A}^-\Delta Q_{i-1/2} = s_{1-1/2}^-\mathscr{W}_{i-1/2}

.. math:: \tilde{F}_{i-1/2} =
    \frac{1}{2}\lvert s_{1-1/2}\rvert
    \left(1 - \frac{\Delta t}{\Delta x}\lvert s_{1-1/2}\rvert\right)
    \tilde{\mathscr{W}}_{i-1/2}

.. math:: \mathscr{W}_{i-1/2} = Q_i - Q_{i-1} = \Delta Q_{i-1/2}

.. math:: s_{i-1/2} = \begin{cases}
    \left[f\left(Q_i\right) - f\left(Q_{i-1}\right)\right]/
    \left(Q_i - Q_{i-1}\right) & \text{if $Q_{i-1} \ne Q_i$},\\
    f'\left(Q_i\right) & \text{if $Q_{i-1} = Q_i$}
    \end{cases}

.. math:: \tilde{\mathscr{W}}_{i-1/2} =
    \mathscr{W}_{i-1/2}\phi\left(\theta_{i-1/2}\right)

.. math:: \theta_{i-1/2} = \frac{\Delta Q_{I-1/2}}{\Delta Q_{i-1/2}}
    \text{  with } I = \begin{cases}
        i - 1& \text{if $s_{i-1/2} > 0$}, \\
        i + 1& \text{if $s_{i-1/2} < 0$},
    \end{cases}
