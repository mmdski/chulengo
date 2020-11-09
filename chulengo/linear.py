import numpy as np
from numpy.linalg import eig, inv


class GodunovsMethod:

    def __init__(self, h0, u0, g, dx, clf=0.9):

        c0 = np.sqrt(h0*g)

        A = np.array([[0, 1], [-u0**2+c0**2, 2*u0]])

        w, v = eig(A)

        lambda_plus = np.zeros_like(A)
        lambda_minus = np.zeros_like(A)

        for i, l in enumerate(w):
            lambda_plus[i, i] = np.maximum(l, 0)
            lambda_minus[i, i] = np.minimum(l, 0)

        a_plus = np.matmul(v, np.matmul(lambda_plus, inv(v)))
        a_minus = np.matmul(v, np.matmul(lambda_minus, inv(v)))

        self._a_plus = a_plus
        self._a_minus = a_minus
        self._dx = float(dx)

        self._n_left_nodes = 1
        self._n_right_nodes = 1

        self._dt = clf*dx/np.abs(w).max()

    def dt(self):
        return self._dt

    def flux(self, q):

        m = q.shape[0]
        n_cells = q.shape[1] - self._n_left_nodes - self._n_right_nodes

        dq_left = np.empty((m, n_cells))
        dq_right = np.empty((m, n_cells))

        for i in range(n_cells):
            i_q = i + self._n_left_nodes
            dq_left[:, i] = q[:, i_q] - q[:, i_q - 1]
            dq_right[:, i] = q[:, i_q + 1] - q[:, i_q]

        flux = (np.dot(self._a_plus, dq_left) +
                np.dot(self._a_minus, dq_right))/self._dx

        return flux

    def n_ghost_nodes(self):

        return self._n_left_nodes, self._n_right_nodes
