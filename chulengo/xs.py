from __future__ import annotations

from ctypes import c_double
from typing import Sequence

import matplotlib.pyplot as plt
import numpy as np

from chulengo.chlib import *


class XSCoordinates:
    def __init__(self, station: Sequence[float], elevation: Sequence[float]):
        np_station = np.array(station, dtype=c_double)
        np_elevation = np.array(elevation, dtype=c_double)

        if np_station.ndim != 1 and np_elevation.ndim != 1:
            raise ValueError("Station and elevation must be one-dimensional")

        if np_station.shape != np_station.shape:
            raise ValueError("The shapes of station and elevation must be equal")

        if not np.all(np_station[:-1] <= np_station[1:]):
            raise ValueError("Station values must be in ascending order")

        length = np_station.shape[0]
        if length <= 0:
            raise ValueError(
                "The lengths of station and elevation must be greater than zero"
            )

        self._length = length

        self._xs_coords_ptr = ch_xs_coords_set_arr(
            None,
            length,
            np_station.ctypes.data_as(c_double_p),
            np_elevation.ctypes.data_as(c_double_p),
        )

    def __copy__(self):
        other = self.__new__(self.__class__)
        other._xs_coords_ptr = ch_xs_coords_copy(self._xs_coords_ptr)
        other._length = int(ch_xs_coords_length(other._xs_coords_ptr))
        return other

    def __del__(self):
        ch_xs_coords_free(self._xs_coords_ptr)

    def coordinates(self):
        station = np.empty((self._length,), dtype=c_double)
        elevation = np.empty((self._length,), dtype=c_double)

        ch_xs_coords_get_arr(
            self._xs_coords_ptr,
            station.ctypes.data_as(c_double_p),
            elevation.ctypes.data_as(c_double_p),
        )

        return station, elevation

    def plot(self, ax=None, color="k", label="Ground"):
        if not ax:
            ax = plt.axes()

        station, elevation = self.coordinates()

        ax.plot(
            station,
            elevation,
            linestyle="-",
            color=color,
            marker=".",
            markerfacecolor=color,
            label=label,
        )
        ax.legend()
        ax.set_xlabel("Station")
        ax.set_ylabel("Elevation")

        return ax

    def subsection(self, left: float, right: float) -> XSCoordinates:
        if left >= right:
            raise ValueError("right must be greater than left")

        left_cf = c_double(left)
        right_cf = c_double(right)

        xs_coords_subsect_ptr = ch_xs_coords_subsect(
            self._xs_coords_ptr, left_cf, right_cf, None
        )

        if ch_xs_coords_length(xs_coords_subsect_ptr) == 0:
            ch_xs_coords_free(xs_coords_subsect_ptr)
            return None

        subsect = self.__new__(self.__class__)
        subsect._xs_coords_ptr = xs_coords_subsect_ptr
        subsect._length = int(ch_xs_coords_length(xs_coords_subsect_ptr))

        return subsect

    def wetted(self, wse: float) -> XSCoordinates:
        wse_cf = c_double(wse)

        wetted_ptr = ch_xs_coords_wetted(self._xs_coords_ptr, wse_cf, None)

        wetted_length = ch_xs_coords_length(wetted_ptr)
        if wetted_length == 0:
            ch_xs_coords_free(wetted_ptr)
            return None

        wetted_coords = self.__new__(self.__class__)
        wetted_coords._xs_coords_ptr = wetted_ptr
        wetted_coords._length = wetted_length

        return wetted_coords
