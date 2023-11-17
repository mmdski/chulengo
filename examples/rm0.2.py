import json
import os

import matplotlib.pyplot as plt
import numpy as np

from chulengo.xs import XSCoordinates

file_path, _ = os.path.split(__file__)
ex_file_path = os.path.join(file_path, "EX1.RM0.2.yaml")

with open(ex_file_path, "r") as f:
    xs_data = json.loads(f.read())

station = np.array(xs_data["coordinates"]["station"])
elevation = np.array(xs_data["coordinates"]["elevation"])

xs_coords = XSCoordinates(station, elevation)

left = 240
right = 280

subsect = xs_coords.subsection(left, right)

ax = xs_coords.plot()
subsect.plot(ax=ax, color="g", label="Subsection")

plt.show()
