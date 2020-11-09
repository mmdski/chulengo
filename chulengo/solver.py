import numpy as np


class Solver:

    def __init__(self, q_initial, left_bc, right_bc, method):

        m_variables = q_initial.shape[0]

        n_left, n_right = method.n_ghost_nodes()
        n_cells = q_initial.shape[1]

        q = np.empty((m_variables, n_left + n_cells + n_right), dtype=np.float)

        i_start = n_left  # beginning of computational domain
        i_end = i_start + n_cells  # end of computational domain

        q[:, i_start:i_end] = q_initial

        self._q = q
        self._method = method
        self._m_variables = m_variables
        self._n_cells = n_cells
        self._i_start = i_start
        self._i_end = i_end
        self._l_bc = left_bc
        self._r_bc = right_bc

        self._t = 0

    def step(self):

        self._l_bc.apply(self._q)
        self._r_bc.apply(self._q)

        dt = self._method.dt()

        self._t += dt

        q_next = self._q[:, self._i_start:self._i_end] - \
            dt*self._method.flux(self._q)

        self._q[:, self._i_start:self._i_end] = q_next

        return q_next

    def t(self):

        return self._t
