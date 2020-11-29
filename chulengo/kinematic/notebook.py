import matplotlib.pyplot as plt
from matplotlib import animation
import numpy as np


class AnimateResults:

    def __init__(self, results):

        self._times = results.times()
        self._results_array = results.array()
        self._x = results.x()

        self._q1_line = None
        self._axes = None

    def func(self, frame):

        t = self._times[frame]

        q1 = self._results_array[frame, :]

        self._q1_line.set_data(self._x, q1)

        self._axes.set_title('t = {}'.format(t))

        return [self._q1_line]

    def func_animation(self, interval=20, step=1):

        n_times = len(self._times)
        frames = range(0, n_times, step)

        fig = self.setup_fig()

        ani = animation.FuncAnimation(fig, self.func, init_func=self.init,
                                      frames=frames, interval=interval,
                                      repeat=False, blit=True)

        return ani

    def setup_fig(self, figsize=None):

        fig, axes = plt.subplots(1, 1, figsize=figsize)

        self._axes = axes

        q1_max = self._results_array[:, :].max()
        q1_min = self._results_array[:, :].min()

        h = q1_max - q1_min

        margin = 0.25

        axes.set_ylim((q1_min - margin*h, q1_max + margin*h))

        axes.set_xlim((self._x.min(), self._x.max()))

        axes.set_title('t = {}'.format(0))
        axes.set_xlabel('x')

        axes.set_ylabel('h')

        return fig

    def init(self):

        q1_line, = self._axes.plot([], [], lw=2)

        self._q1_line = q1_line

        return [q1_line]
