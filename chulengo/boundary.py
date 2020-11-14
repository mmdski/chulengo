class SolidWallLeftBC:

    def __init__(self, n_ghost_nodes):

        self._n_ghost_nodes = int(n_ghost_nodes)

    def apply(self, q):

        n = self._n_ghost_nodes

        for i in range(n + 1):
            q[0, n - i] = q[0, n + i]
            q[1, n - i] = -q[1, n + 1]


class SolidWallRightBC:

    def __init__(self, n_ghost_nodes, n_cells):

        self._n_ghost_nodes = int(n_ghost_nodes)
        self._n_cells = int(n_cells)

    def apply(self, q):

        n = self._n_ghost_nodes
        n_cells = self._n_cells

        for i in range(n + 1):
            q[0, i + n_cells] = q[0, n_cells - 1 - i]
            q[1, i + n_cells] = -q[1, n_cells - 1 - i]


class NonReflectingRightBC:

    def __init__(self, n_ghost_nodes, n_cells):

        self._n_ghost_nodes = int(n_ghost_nodes)
        self._n_cells = int(n_cells)

    def apply(self, q):

        n = self._n_ghost_nodes
        n_cells = self._n_cells

        for i in range(n + 1):
            q[:, i + n_cells] = q[:, n_cells]


class NonReflectingLeftBC:

    def __init__(self, n_ghost_nodes):

        self._n_ghost_nodes = int(n_ghost_nodes)

    def apply(self, q):

        n = self._n_ghost_nodes

        for i in range(n + 1):
            q[:, n - i] = q[:, n + 1]
