import os

import matplotlib.pyplot as plt

from chulengo.ras import RASGeometryInputFile, parse_xs_sta_elev
from chulengo.xs.compound import Coordinates


file_dir, _ = os.path.split(__file__)
g_file_path = os.path.join(file_dir, "CRITCREK.g01")
ras_g_file = RASGeometryInputFile(g_file_path)

rm1_xs_line = 338

xs_coord_data = parse_xs_sta_elev(ras_g_file[rm1_xs_line:])

xs_coords = Coordinates(xs_coord_data["station"], xs_coord_data["elevation"])
wetted_coords = xs_coords.wetted(1756.71)

ax = xs_coords.plot()
wetted_coords.plot(ax=ax, label="Wetted", color="g", linewidth=2, marker=None)

plt.show()
