class RASGeometryInputFile:
    def __init__(self, file_path):
        with open(file_path, "r") as f:
            self._lines = f.readlines()

    def __getitem__(self, key):
        return self._lines[key]


def parse_xs_sta_elev(input_lines):
    if input_lines[0][0:10] != "#Sta/Elev=":
        raise ValueError("Unrecognized input")

    n_coords = int(input_lines[0][10:13])
    n_lines = n_coords // 5 + 1

    xs_coords_lines = input_lines[1 : n_lines + 1]

    coords = []
    for line in xs_coords_lines:
        [coords.append(float(v)) for v in line.strip().split()]

    station = coords[::2]
    elevation = coords[1::2]

    # make sure lengths line up
    assert n_coords == len(station)
    assert len(station) == len(elevation)

    coordinates = {"length": n_coords, "station": station, "elevation": elevation}

    return coordinates
