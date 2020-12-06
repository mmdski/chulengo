========
Limiters
========

--------------
Linear methods
--------------

upwind
======

.. math:: \phi\left(\theta\right) = 0

------------------------
High-resolution limiters
------------------------

Monotizonized central-difference limiter
========================================

MC limiter

.. math:: \phi\left(\theta\right) =
    \max{\left(0, \min{\left(\frac{1 + \theta}{2}, 2, 2\theta\right)}\right)}
