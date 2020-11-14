import numpy as np


class SpatialDomain:

    def __init__(self, dx, num):

        x_center = dx*np.arange(num, dtype=np.float)

        x_edge = np.empty((x_center.shape[0] + 1, ))
        x_edge[0] = x_center[0] - dx/2
        x_edge[1:] = x_center + dx/2

        self._x_center = x_center
        self._x_edge = x_edge
        self._dx = dx

    def center(self, i=None):

        if i is None:
            return self._x_center.copy()
        else:
            return self._x_center[i]

    def dx(self):

        return self._dx

    def edge(self, i=None):

        if i is None:
            return self._x_edge.copy()
        else:
            return self._x_edge[i]
