import numpy as np


class Array:

    def __init__(self, lo_index, hi_index):

        self._lo_index = lo_index
        self._hi_index = hi_index

        length = self._hi_index - self._lo_index + 1

        self._array = np.empty((length, ), dtype=float)

    def __len__(self):

        return len(self._array)

    def array(self, lo_index, hi_index):
        return self._array[lo_index - self._lo_index:hi_index - self._hi_index]

    @ classmethod
    def empty_like(cls, other):

        res = cls.__new__(cls)
        res._lo_index = other._lo_index
        res._hi_index = other._hi_index
        res._array = np.empty_like(other._array)

        return res

    def fill(self, a):

        if self._array.shape != a.shape:
            raise ValueError("Array must be same shape")

        self._array = a.copy()

    def get(self, i):

        if i > self._hi_index or i < self._lo_index:
            lo = self._lo_index
            hi = self._hi_index
            raise ValueError("Index {} is out of bounds for ".format(i) +
                             "array with limits {}, {}".format(lo, hi))

        return self._array[i - self._lo_index]

    def max_abs(self):

        return np.abs(self._array).max()

    def limits(self):

        return self._lo_index, self._hi_index

    def set(self, i, value):

        if i > self._hi_index or i < self._lo_index:
            lo = self._lo_index
            hi = self._hi_index
            raise ValueError("i-index {} is out of bounds for ".format(i) +
                             "array with limits {}, {}".format(lo, hi))

        self._array[i - self._lo_index] = value
