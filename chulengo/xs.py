from ctypes import c_float
from typing import Sequence

import numpy as np

from chulengo.chlib import *


class XSCoordinates:
    def __init__(self, station: Sequence[float], elevation: Sequence[float]):
        np_station = np.array(station, dtype=c_float)
        np_elevation = np.array(elevation, dtype=c_float)

        if np_station.ndim != 1 and np_elevation.ndim != 1:
            raise ValueError("Station and elevation must be one-dimensional")

        if np_station.shape != np_station.shape:
            raise ValueError("The shapes of station and elevation must be equal")

        length = np_station.shape[0]
        if length <= 0:
            raise ValueError(
                "The lengths of station and elevation must be greater than zero"
            )

        self._length = length
        self._xs_coords = ch_xs_coords_new(length)

        ch_xs_coords_set_arr(
            self._xs_coords,
            length,
            np_station.ctypes.data_as(c_float_p),
            np_elevation.ctypes.data_as(c_float_p),
        )

    def __del__(self):
        ch_xs_coords_free(self._xs_coords)
