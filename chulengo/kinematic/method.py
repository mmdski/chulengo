import numpy as np

from chulengo.array import Array


class ScalarNonLinear:

    def __init__(self, manning, slope, dx):

        if self.__class__ is ScalarNonLinear:
            raise NotImplementedError

        self._manning = manning
        self._slope = slope

        self._dx = dx

        self._f_const = 1/manning * np.sqrt(slope)
        self._f_prime_const = 5/3 * 1/manning * np.sqrt(slope)

        self._n_ghost = None

    def _f(self, h):
        return self._f_const * h**(5/3)

    def _f_prime(self, h):

        return self._f_prime_const * h**(2/3)

    def dt(self, s, clf=0.9):

        return clf*self._dx/s.max_abs()

    def flux_diff(self, h, s, dt, f_x):

        _, hi = h.limits()

        dx = self._dx

        for i in range(1, hi - self._n_ghost + 1):

            s_left = s.get(i - 1)
            s_right = s.get(i)

            s_plus = np.max([s_left, 0])
            s_minus = np.min([s_right, 0])

            h_left = h.get(i - 1)
            h_cell = h.get(i)
            h_right = h.get(i + 1)

            dh_left = h_cell - h_left
            dh_right = h_right - h_cell

            f_x.set(i, (s_plus*dh_left + s_minus*dh_right)/dx)

        return f_x

    def n_ghost(self):
        return self._n_ghost

    def new_f_x(self, h):

        lo, hi = h.limits()

        return Array(lo + self._n_ghost, hi - self._n_ghost)

    def new_h(self, h_0):

        n_cells = h_0.shape[0]
        n_ghost = self._n_ghost
        h = Array(1 - n_ghost, n_cells + n_ghost)

        for i in range(n_cells):
            h.set(i + n_ghost, h_0[i])

        return h

    def new_s(self, h):

        lo, hi = h.limits()
        s = Array(lo, hi - 1)

        return s

    def wave_speed(self, h, s):

        lo, hi = h.limits()

        for i in range(lo + 1, hi + 1):
            h_lo = h.get(i - 1)
            h_hi = h.get(i)
            if h_hi == h_lo:
                s.set(i - 1, self._f_prime(h_hi))
            else:
                s.set(i - 1, (self._f(h_hi) - self._f(h_lo))/(h_hi - h_lo))

        return s


class UpwindMethod(ScalarNonLinear):

    def __init__(self, *args):

        super().__init__(*args)
        self._n_ghost = 1
