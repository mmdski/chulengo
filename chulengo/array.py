import numpy as np


class Array:

    def __init__(self, lo_index, hi_index):

        if lo_index >= hi_index:
            raise ValueError("lo_index must be less than hi_index")

        self._lo_index = int(lo_index)
        self._hi_index = int(hi_index)

        length = self._hi_index - self._lo_index + 1

        self._array = np.empty((length,), dtype=float)

    def __len__(self):

        return len(self._array)

    @classmethod
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

    def get(self, index):

        if not isinstance(index, int):
            raise TypeError("Index must be an int")

        if index > self._hi_index or index < self._lo_index:
            lo = self._lo_index
            hi = self._hi_index
            raise ValueError("Index {} is out of bounds for ".format(index) +
                             "array with limits {}, {}".format(lo, hi))

        return self._array[index - self._lo_index]

    def max_abs(self):

        return np.abs(self._array).max()

    def limits(self):

        return self._lo_index, self._hi_index

    def set(self, index, value):

        if not isinstance(index, int):
            raise TypeError("Index must be an int")

        if index > self._hi_index or index < self._lo_index:
            lo = self._lo_index
            hi = self._hi_index
            raise ValueError("Index {} is out of bounds for ".format(index) +
                             "array with limits {}, {}".format(lo, hi))

        self._array[index - self._lo_index] = float(value)
