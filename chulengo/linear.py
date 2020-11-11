import numpy as np
from numpy.linalg import eig, inv


class LinearMethod:

    def __init__(self, h0, u0, g, dx, clf=0.9):

        if self.__class__ is LinearMethod:
            raise NotImplementedError("This class is not implemented")

        c0 = np.sqrt(h0*g)

        lambda_1 = u0 - c0  # eigenvalue 1
        right_eig_1 = np.array([1, u0 - c0])  # right eigenvector 1

        lambda_2 = u0 + c0  # eigenvalue 2
        right_eig_2 = np.array([1, u0 + c0])  # right eigenvector 2

        self._dx = float(dx)

        self._dt = clf*dx/(max(np.abs([lambda_1, lambda_2])))

        self._lambda = np.array([lambda_1, lambda_2])
        self._lambda_plus = np.maximum(self._lambda, [0, 0])
        self._lambda_minus = np.minimum(self._lambda, [0, 0])
        self._right_eig = np.stack([right_eig_1, right_eig_2], axis=1)
        self._left_eig = inv(self._right_eig)

    def _alpha(self, q):

        m = q.shape[0]
        total_cells = q.shape[1]

        alpha = np.empty((m, total_cells - 1))

        for i in range(1, total_cells):

            dq = q[:, i] - q[:, i - 1]

            for p in range(m):

                alpha[p, i - 1] = np.dot(self._left_eig[p, :], dq)

        return alpha

    def _wave(self, alpha):

        m = alpha.shape[0]
        n = alpha.shape[1]

        wave = np.empty((m, m, n))

        for i in range(n):

            for p in range(m):

                wave[p, :, i] = alpha[p, i] * self._right_eig[:, p]

        return wave

    def dt(self):

        return self._dt

    def flux(self, *args):

        raise NotImplementedError

    def n_ghost_nodes(self):

        return self._n_left_nodes, self._n_right_nodes


class GodunovsMethod(LinearMethod):

    def __init__(self, *args, **kwargs):

        super().__init__(*args, **kwargs)
        self._n_left_nodes = 1
        self._n_right_nodes = 1

    @staticmethod
    def _phi(*args, **kwargs):

        return 0

    def flux(self, q):

        m = q.shape[0]
        total_cells = q.shape[1]
        n_cells = total_cells - self._n_left_nodes - self._n_right_nodes

        flux = np.empty((m, n_cells))

        alpha = self._alpha(q)
        wave = self._wave(alpha)

        for i in range(n_cells):

            i_q = i + self._n_left_nodes

            f_left = 0
            f_right = 0

            for p in range(m):
                f_left += self._lambda_plus[p]*wave[p, :, i_q - 1]
                f_right += self._lambda_minus[p]*wave[p, :, i_q]

            flux[:, i] = (f_left + f_right)/self._dx

        return flux
