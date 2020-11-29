import matplotlib.pyplot as plt
import numpy as np


class Results:

    def __init__(self, spatial_domain, t_initial, q_initial):

        self._x = spatial_domain.center()
        self._results = {t_initial: q_initial}
        self._n_cells = q_initial.shape[0]

    def add_results(self, t, q):

        self._results[t] = q

    def results_array(self):

        results = np.empty((self.n_times(), 1, self.n_cells()))
        times = self.times()

        for i, t in enumerate(times):
            results[i, :, :] = self._results[t]

        return results

    def times(self):

        keys = list(self._results.keys())
        keys.sort()

        return np.array(keys, dtype=np.float)

    def n_times(self):

        return len(self._results)

    def n_cells(self):

        return self._n_cells

    def plot(self, t=None, axes=None):

        if axes is None:

            axes = plt.axes()

        if t is None:

            t = max(k for k in self._results.keys())

        q = self._results[t]

        axes.plot(self._x, q)

        axes.set_title('t = {}'.format(t))
        axes.set_xlabel('x')

        axes.set_ylabel('$h$')

        return axes

    def x(self):

        return self._x.copy()
