import matplotlib.pyplot as plt
from matplotlib import animation
import numpy as np


class AnimateResults:

    def __init__(self, results):

        self._times = results.times()
        self._results_array = results.results_array()
        self._x = results.x()

        self._q1_line = None
        self._q2_line = None
        self._axes = None

    def func(self, frame):

        t = self._times[frame]

        q1 = self._results_array[frame, 0, :]
        q2 = self._results_array[frame, 1, :]

        self._q1_line.set_data(self._x, q1)
        self._q2_line.set_data(self._x, q2)

        self._axes[0].set_title('t = {}'.format(t))

        return self._q1_line, self._q2_line

    def func_animation(self, interval=20, step=1):

        n_times = len(self._times)
        frames = range(0, n_times, step)

        fig = self.setup_fig()

        ani = animation.FuncAnimation(fig, self.func, init_func=self.init,
                                      frames=frames, interval=interval,
                                      repeat=False, blit=True)

        return ani

    def setup_fig(self, figsize=None):

        fig, axes = plt.subplots(2, 1, sharex=True, figsize=figsize)

        self._axes = axes

        q1_max = self._results_array[:, 0, :].max()
        q1_min = self._results_array[:, 0, :].min()

        q2_max = self._results_array[:, 1, :].max()
        q2_min = self._results_array[:, 1, :].min()

        margin = 0.25
        u_margin_1 = np.sign(q1_max)*margin
        u_margin_2 = np.sign(q2_max)*margin
        l_margin_1 = np.sign(q1_min)*margin
        l_margin_2 = np.sign(q2_min)*margin

        axes[0].set_ylim(q1_min*(1 - l_margin_1), q1_max*(1 + u_margin_1))
        axes[1].set_ylim(q2_min*(1 - l_margin_2), q2_max*(1 + u_margin_2))

        axes[1].set_xlim((self._x.min(), self._x.max()))

        axes[0].set_title('t = {}'.format(0))
        axes[1].set_xlabel('x')

        axes[0].set_ylabel('$h_0$')
        axes[1].set_ylabel('$h_0u_0$')

        return fig

    def init(self):

        q1_line, = self._axes[0].plot([], [], lw=2)
        q2_line, = self._axes[1].plot([], [], lw=2)

        self._q1_line = q1_line
        self._q2_line = q2_line

        return q1_line, q2_line
