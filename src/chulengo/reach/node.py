from chulengo import GRAVITY


class SimpleNode:
    def __init__(self, xs, invert_elev, expansion=0.0, contraction=0.0):
        self._xs = xs
        self._invert = float(invert_elev)
        self._expansion = float(expansion)
        self._contraction = float(contraction)

    def cc(self):
        """Contraction loss coefficient"""
        return self._contraction

    def ce(self):
        """Expansion loss coefficient"""
        return self._expansion

    def sqrt_sf(self, wse, q):
        """Square root of the friction slope"""
        h = wse - self._invert
        conveyance = self._xs.conveyance(h)
        return q / conveyance

    def velocity(self, wse, q):
        """Mean cross-section velocity"""
        h = wse - self._invert
        area = self._xs.flow_area(h)
        return q / area

    def velocity_head(self, wse, q):
        """Velocity head"""
        h = wse - self._invert
        velocity = self.velocity(h, q)
        alpha = self._xs.alpha(h)
        return alpha * velocity**2 / (2 * GRAVITY)
