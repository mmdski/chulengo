import json
import os

import matplotlib.pyplot as plt
import numpy as np

from chulengo.xs.compound import Coordinates

file_path, _ = os.path.split(__file__)
ex_file_path = os.path.join(file_path, "EX1.RM0.2.json")

with open(ex_file_path, "r") as f:
    xs_data = json.loads(f.read())

station = np.array(xs_data["coordinates"]["station"])
elevation = np.array(xs_data["coordinates"]["elevation"])

xs_coords = Coordinates(station, elevation)

ax = xs_coords.plot()

left = 211
right = 219

subsect = xs_coords.subsection(left, right)

subsect.plot(ax=ax, color="b", label="Subsection")

wse = 75
wetted_coords = xs_coords.wetted(wse)

if wetted_coords:
    wetted_coords.plot(ax=ax, color="g", label="Wetted")

plt.show()
