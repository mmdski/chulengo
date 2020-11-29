import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import interp1d


class ResultsRecorder:

    def __init__(self, spatial_domain, t_initial, q_initial):

        self._x = spatial_domain.center()
        self._results = {t_initial: q_initial}
        self._n_cells = q_initial.shape[0]

    def add_results(self, t, q):

        self._results[t] = q

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

    def results_array(self):

        results = np.empty((self.n_times(), self.n_cells()))
        times = self.times()

        for i, t in enumerate(times):
            results[i, :] = self._results[t]

        return results

    def times(self):

        keys = list(self._results.keys())
        keys.sort()

        return np.array(keys, dtype=np.float)

    def n_times(self):

        return len(self._results)

    def n_cells(self):

        return self._n_cells

    def x(self):

        return self._x.copy()


class ComputationResults:

    def __init__(self, results_recorder, dt):

        recorded_results = results_recorder.results_array()
        recorded_times = results_recorder.times()

        total_time = recorded_times[-1] - recorded_times[0]
        n_times = int(total_time/dt)

        times = dt*np.arange(n_times, dtype=float) + recorded_times[0]

        interp_func = interp1d(recorded_times, recorded_results, axis=0)
        results_array = interp_func(times)

        self._dt = dt
        self._x = results_recorder.x()
        self._times = times
        self._array = results_array

    def array(self):
        return self._array.copy()

    def dt(self):
        return self._dt

    def times(self):
        return self._times.copy()

    def x(self):
        return self._x.copy()
