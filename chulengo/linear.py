import numpy as np
from numpy.linalg import eig, inv


class GodunovsMethod:

    def __init__(self, h0, u0, g, dx, clf=0.9):

        c0 = np.sqrt(h0*g)

        lambda_1 = u0 - c0  # eigenvalue 1
        right_eig_1 = np.array([1, u0 - c0])  # right eigenvector 1

        lambda_2 = u0 + c0  # eigenvalue 2
        right_eig_2 = np.array([1, u0 + c0])  # right eigenvector 2

        self._dx = float(dx)

        self._n_left_nodes = 1
        self._n_right_nodes = 1

        self._dt = clf*dx/(max(np.abs([lambda_1, lambda_2])))

        self._lambda = np.array([lambda_1, lambda_2])
        self._lambda_plus = np.maximum(self._lambda, [0, 0])
        self._lambda_minus = np.minimum(self._lambda, [0, 0])
        self._right_eig = np.stack([right_eig_1, right_eig_2], axis=1)
        self._left_eig = inv(self._right_eig)

    def dt(self):
        return self._dt

    def flux(self, q):

        m = q.shape[0]
        n_cells = q.shape[1] - self._n_left_nodes - self._n_right_nodes

        flux = np.empty((m, n_cells))

        for i in range(n_cells):
            i_q = i + self._n_left_nodes
            dq_left = q[:, i_q] - q[:, i_q - 1]
            dq_right = q[:, i_q + 1] - q[:, i_q]

            f_left = 0
            f_right = 0

            for p in range(m):
                a_left = np.dot(self._left_eig[p, :], dq_left)
                w_left = a_left*self._right_eig[:, p]
                f_left += self._lambda_plus[p]*w_left

                a_right = np.dot(self._left_eig[p, :], dq_right)
                w_right = a_right*self._right_eig[:, p]
                f_right += self._lambda_minus[p]*w_right

            flux[:, i] = (f_left + f_right)/self._dx

        return flux

    def n_ghost_nodes(self):

        return self._n_left_nodes, self._n_right_nodes
