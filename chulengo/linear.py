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


class MCMethod(LinearMethod):

    def __init__(self, *args, **kwargs):

        super().__init__(*args, **kwargs)
        self._lambda_abs = np.abs(self._lambda)
        self._n_left_nodes = 2
        self._n_right_nodes = 2

    def _alpha_lim(self, alpha):

        m = alpha.shape[0]
        n = alpha.shape[1] - 2

        theta = self._theta(alpha)
        phi = self._phi(theta)

        alpha_lim = np.empty((m, n))

        for i in range(n):
            for p in range(m):
                alpha_lim[p, i] = alpha[p, i + 1]*phi[p, i]

        return alpha_lim

    def _lim_flux(self, alpha):

        alpha_lim = self._alpha_lim(alpha)
        m, n = alpha_lim.shape

        wave_lim = self._wave(alpha_lim)

        flux_lim = np.zeros((m, n))

        dt = self._dt
        dx = self._dx
        abs_lambda = self._lambda_abs

        for i in range(n):
            for p in range(m):
                flux_lim[:, i] += 0.5*abs_lambda[p] * \
                    (1 - dt/dx*abs_lambda[p])*wave_lim[p, :, i]

        return flux_lim

    @staticmethod
    def _phi(theta):

        m, n = theta.shape
        phi = np.empty_like(theta)

        for i in range(n):
            for p in range(m):
                r = (1 + theta[p, i])/2
                phi[p, i] = max(0, min(r, 2, 2*theta[p, i]))

        return phi

    def _theta(self, alpha):

        m = alpha.shape[0]
        n = alpha.shape[1] - 2

        theta = np.zeros((m, n))

        for i in range(n):

            i_alpha = i + 1

            for p in range(m):

                if alpha[p, i_alpha] == 0:

                    continue

                if self._lambda[p] > 0:
                    theta[p, i] = alpha[p, i_alpha - 1]/alpha[p, i_alpha]

                elif self._lambda[p] < 0:
                    theta[p, i] = alpha[p, i_alpha + 1]/alpha[p, i_alpha]

        return theta

    def flux(self, q):

        m = q.shape[0]
        total_cells = q.shape[1]
        n_cells = total_cells - self._n_left_nodes - self._n_right_nodes

        flux = np.empty((m, n_cells))

        alpha = self._alpha(q)
        wave = self._wave(alpha)

        flux_lim = self._lim_flux(alpha)

        for i in range(n_cells):

            i_q = i + self._n_left_nodes

            left = 0
            right = 0

            for p in range(m):
                left += self._lambda_plus[p]*wave[p, :, i_q - 1]
                right += self._lambda_minus[p]*wave[p, :, i_q]

            flux[:, i] = (left + right)/self._dx - \
                (flux_lim[:, i + 1] - flux_lim[:, i])/self._dx

        return flux
