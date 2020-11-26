==============
Linear systems
==============

A linear conservation law in differental form follows the form

.. math:: q_t + Aq_x = 0

where :math:`A` is a constant (over :math:`x` and :math:`t`) :math:`m\times m`
matrix, with :math:`m` being the number of elements in the vector :math:`q`.

.. math:: Q^{n+1}_i = Q^n_i - \frac{\Delta t}{\Delta x}
    \left(\mathscr{A}^+\Delta Q_{i-1/2} + \mathscr{A}^-\Delta Q_{i+1/2}\right)

.. math:: \mathscr{A}^+ = A^+

.. math:: \mathscr{A}^- = A^-

.. math:: A^+ = R\Lambda^+R^{-1}

.. math:: A^- = R\Lambda^-R^{-1}

.. math:: \Lambda^+ = \begin{bmatrix}
    \left(\lambda^1\right)^+ & & & \\
    & \left(\lambda^2\right)^+ & & \\
    & & \ddots & \\
    & & & \left(\lambda^m\right)^+
    \end{bmatrix}

.. math:: \Lambda^- = \begin{bmatrix}
    \left(\lambda^1\right)^- & & & \\
    & \left(\lambda^2\right)^- & & \\
    & & \ddots & \\
    & & & \left(\lambda^m\right)^-
    \end{bmatrix}

.. math:: \left(\lambda^p\right)^+ = \max{\left(\lambda^p, 0\right)}

.. math:: \left(\lambda^p\right)^- = \min{\left(\lambda^p, 0\right)}

.. math:: R = \begin{bmatrix}r^1\vert r^2\vert\dotsc\vert r^m\end{bmatrix}

Direct form
===========

.. math:: Q^{n+1}_i = Q_i -
    \frac{\Delta t}{\Delta x}\left(A^{+}\Delta Q_{i-1/2} + A^{-}\Delta Q_{i+1/2}\right) -
    \frac{\Delta t}{\Delta x}\left(\tilde{F}_{i+1/2}-\tilde{F}_{i-1/2}\right)

.. math:: A^+\Delta Q_{i-1/2} =
    \sum^m_{p=1}\left(\lambda^p\right)^+\mathscr{W}^p_{i-1/2}

.. math:: A^-\Delta Q_{i-1/2} =
    \sum^m_{p=1}\left(\lambda^p\right)^-\mathscr{W}^p_{i-1/2}

.. math:: \tilde{F}_{i-1/2} =
    \frac{1}{2}\sum^m_{p=1}\lvert\lambda^p\rvert
    \left(1 - \frac{\Delta t}{\Delta x}\lvert\lambda^p\rvert\right)
    \tilde{\mathscr{W}}^p_{i-1/2}

.. math:: \alpha^p_{i-1/2} = \ell^p\left(Q_i - Q_{i-1}\right)

--------------------
Linear shallow water
--------------------

.. math:: \ell^1 = \frac{1}{2c_0}\begin{bmatrix}u_0 + c_0 & -1\end{bmatrix}

.. math:: \ell^2 = \frac{1}{2c_0}\begin{bmatrix}-u_0 + c_0 & 1\end{bmatrix}

.. math:: Q_i - Q_{i-1} =
    \begin{bmatrix} q^1_i - q^2_{i-1} \\ q^2_i - q^2_{i-1} \end{bmatrix} =
    \begin{bmatrix} \Delta q^1_{i-1/2} \\ \Delta q^2_{i-1/2} \end{bmatrix}

.. math:: \alpha^1_{i-1/2} =
    \frac{\Delta q^1_{i-1/2}\left(u_0 + c_0\right) - \Delta q^2_{i-1/2}}{2c_0}

.. math:: \alpha^2_{i-1/2} =
    \frac{\Delta q^1_{i-1/2}\left(- u_0 + c_0\right) - \Delta q^2_{i-1/2}}{2c_0}

.. math:: \mathscr{W}^p_{i-1/2} = \alpha^p_{i-1/2}r^p

.. math:: \tilde{\mathscr{W}}^p_{i-1/2} = \tilde{\alpha}^p_{i-1/2}r^p

.. math:: \tilde{\alpha}^p_{i-1/2} =
    \alpha^p_{i-1/2}\phi\left(\theta^p_{i-1/2}\right)

.. math:: \theta^p_{i-1/2} = \frac{\alpha^p_{I-1/2}}{\alpha^p_{i-1/2}}
    \text{  with } I = \begin{cases}
        i - 1& \text{if $\lambda^p > 0$}, \\
        i + 1& \text{if $\lambda^p < 0$},
    \end{cases}

Limiters
========

Linear methods
--------------

upwind
++++++

.. math:: \phi\left(\theta\right) = 0

High-resolution limiters
------------------------

Monotizonized central-difference limiter
++++++++++++++++++++++++++++++++++++++++

MC limiter

.. math:: \phi\left(\theta\right) =
    \max{\left(0, \min{\left(\frac{1 + \theta}{2}, 2, 2\theta\right)}\right)}
