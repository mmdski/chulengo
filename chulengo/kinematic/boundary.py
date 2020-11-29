class PeriodicBC:

    def __init__(self, n_cells, n_ghost):

        self._n_ghost = n_ghost
        self._n_cells = n_cells

    def apply_left(self, h):

        for i in range(1, self._n_ghost + 1):
            from_index = self._n_cells - i + 1
            to_index = 1 - i
            h.set(to_index, h.get(from_index))

    def apply_right(self, h):

        for i in range(1, self._n_ghost + 1):
            from_index = i
            to_index = self._n_cells + i
            h.set(to_index, h.get(from_index))
