from chulengo.array import Array


class Solver:

    def __init__(self, h_initial, left_bc, right_bc, method):

        self._method = method
        self._left_bc = left_bc
        self._right_bc = right_bc

        self._n_cells = h_initial.shape[0]

        # pre-allocate memory
        self._h = method.new_h(h_initial)
        self._f_x = method.new_f_x(self._h)
        self._s = method.new_s(self._h)

        self._left_bc(self._h)
        self._right_bc(self._h)

        self._t = 0

    def step(self):

        s = self._method.wave_speed(self._h, self._s)
        dt = self._method.dt(self._s)
        f_x = self._method.flux_diff(self._h, s, dt, self._f_x)

        self._t += dt

        for i in range(1, self._n_cells + 1):
            self._h.set(i, self._h.get(i) - dt*f_x.get(i))

        self._left_bc(self._h)
        self._right_bc(self._h)

        return self._t, self._h.array(1, self._n_cells)

    def t(self):
        return self._t
