import json
import os

import matplotlib.pyplot as plt
import numpy as np

from chulengo.xs import XSCoordinates, Subdivision

file_path, _ = os.path.split(__file__)
ex_file_path = os.path.join(file_path, "triangles.json")

with open(ex_file_path, "r") as f:
    xs_data = json.loads(f.read())

station = np.array(xs_data["coordinates"]["station"])
elevation = np.array(xs_data["coordinates"]["elevation"])

xs_coords = XSCoordinates(station, elevation)

ax = xs_coords.plot()

wse = 5
wetted_coords = xs_coords.wetted(wse)

subdiv = Subdivision(0.04, station, elevation)

wse = np.linspace(0, 10, num=11)
area = np.empty_like(wse)
top_width = np.empty_like(wse)

for i, e in enumerate(wse):
    props = subdiv.props(wse[i])
    area[i] = props[2]
    top_width[i] = props[3]

if wetted_coords:
    wetted_coords.plot(ax=ax, color="g", label="Wetted")

fig = plt.figure()
plt.plot(wse, area, label="Area")
plt.xlabel("Water Surface Elevation")
plt.legend()

plt.show()
