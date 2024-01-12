from typing import Optional

import numpy as np
import numpy.typing as npt

from chulengo import MANNING_K
from chulengo.typing import *


class SimpleRect:
    """Simple rectangular cross section"""

    def __init__(
        self,
        width: float,
        n: float,
        left_ineff_sta: Optional[float] = None,
        right_ineff_sta: Optional[float] = None,
    ):
        width = float(width)
        if width <= 0:
            raise ValueError("width must be greater than 0")

        self._n = float(n)

        if left_ineff_sta:
            left_ineff_sta = float(left_ineff_sta)
            if left_ineff_sta < 0:
                raise ValueError("left_ineff_sta must be greater than 0")
            if left_ineff_sta > width:
                raise ValueError("left_ineff_sta must be less than width")
            self._left_ineff_sta = left_ineff_sta
        else:
            self._left_ineff_sta = 0.0

        if right_ineff_sta:
            right_ineff_sta = float(right_ineff_sta)
            if right_ineff_sta < 0:
                raise ValueError("right_ineff_sta must be greater than 0")
            if right_ineff_sta > width:
                raise ValueError("right_ineff_sta must be less than width")
            self._right_ineff_sta = right_ineff_sta
        else:
            self._right_ineff_sta = width

        if right_ineff_sta < left_ineff_sta:
            raise ValueError(
                "right_ineff_sta must be greater than or equal to left_ineff_sta"
            )

        self._width = width

        left_ineff_width = self._left_ineff_sta
        right_ineff_width = self._width - self._right_ineff_sta
        self._eff_width = width - left_ineff_width - right_ineff_width

    @staticmethod
    def _zero_values(h, xs_prop):
        if h.ndim > 0:
            xs_prop[h < 0] = 0
        elif h < 0:
            xs_prop.put(0, 0)
        return xs_prop

    def act_tw(self, h: npt.ArrayLike) -> NDArrayF64:
        """Effective top width"""
        tw = np.full_like(h, self._eff_width)
        return self._zero_values(h, tw)

    def area(self, h: ArrayLikeFloat) -> NDArrayF64:
        """Cross-section area"""
        h = np.asarray(h, dtype=np.float64)
        area = h * self._width
        return self._zero_values(h, area)

    def conveyance(self, h: ArrayLikeFloat) -> NDArrayF64:
        """Conveyance"""
        h = np.asarray(h, dtype=np.float64)
        conv = np.empty_like(h, dtype=np.float64)
        flow_area = self.flow_area(h)
        if h.ndim > 0:
            conv[h < 0] = np.nan
            # radius = flow_area / wp
            # since flow_area = h * flow_width and flow_width is wp, radius = h
            conv[h > 0] = MANNING_K / self._n * h[h > 0] ** (2 / 3) * flow_area[h > 0]
        elif h < 0:
            conv.put(0, np.nan)
        else:
            conv.put(0, MANNING_K / self._n * h ** (2 / 3) * flow_area)
        return conv

    def flow_area(self, h: npt.ArrayLike) -> NDArrayF64:
        """Effective cross-section area"""
        h = np.asarray(h, dtype=np.float64)
        area = h * self._eff_width
        return self._zero_values(h, area)

    def tw(self, h: npt.ArrayLike) -> NDArrayF64:
        """Top width"""
        tw = np.full_like(h, self._width)
        return self._zero_values(h, tw)

    def vel_coeff(self, h: npt.ArrayLike) -> NDArrayF64:
        """Velocity coefficient"""
        h = np.asarray(h, dtype=np.float64)
        coeff = np.ones_like(h, dtype=np.float64)
        if coeff.ndim > 0:
            coeff[h < 0] = np.nan
        elif h < 0:
            coeff.put(0, np.nan)
        return coeff

    def wp(self, h: npt.ArrayLike) -> NDArrayF64:
        """Wetted perimeter"""
        h = np.asarray(h, dtype=np.float64)
        if self._left_ineff_sta < 0:
            l = h
        else:
            l = 0.0

        if self._right_ineff_sta > self._width:
            r = h
        else:
            r = 0.0

        wp = l + r + self.eff_tw(h)
        return self._zero_values(h, wp)
