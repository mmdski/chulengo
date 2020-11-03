=======================
Shallow water equations
=======================

The non-linear shallow water equations are

.. math:: \begin{bmatrix} h \\ hu \end{bmatrix}_t +
    \begin{bmatrix} uh \\ hu^2 + \tfrac{1}{2}gh^2 \end{bmatrix}_x = 0.

Linear form
===========
The linearized system of equations in conservation form is

.. math:: q_t + Aq_x = 0,

where

.. math:: q = \begin{bmatrix} h - h_0 \\ hu - h_0u_0 \end{bmatrix},

.. math:: q_0 = \begin{bmatrix} h_0 \\ h_0u_0 \end{bmatrix},

and

.. math:: A = \begin{bmatrix} 0 & 1 \\ -u_0^2 + c_0^2 & 2u_0 \end{bmatrix}.

The eigenvalues of :math:`A` are

.. math:: \lambda_0^1 = u_0 - c_0

and

.. math:: \lambda_0^2 = u_0 + c_0

Here, :math:`c_0=\sqrt{gh_0}`. The eigenvectors are

.. math:: r_1 = \begin{bmatrix}1 \\ u_0 - c_0\end{bmatrix}

and

.. math:: r_2 = \begin{bmatrix}1 \\ u_0 + c_0\end{bmatrix}
