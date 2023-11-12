from ctypes import c_float, c_size_t, CDLL, POINTER, Structure
import os

_file_path, _ = os.path.split(__file__)
_chlib_path = os.path.join(_file_path, "..", "build", "libchlib.dylib")
_chlib = CDLL(_chlib_path)


class ChXSCoords(Structure):
    pass


ch_xs_coords_new = _chlib.ch_xs_coords_new
ch_xs_coords_new.restype = POINTER(ChXSCoords)
ch_xs_coords_new.argtypes = [c_size_t]

ch_xs_coords_free = _chlib.ch_xs_coords_free
ch_xs_coords_free.restype = None
ch_xs_coords_free.argtypes = [POINTER(ChXSCoords)]

ch_xs_coords_length = _chlib.ch_xs_coords_length
ch_xs_coords_length.restype = c_size_t
ch_xs_coords_length.argtypes = [POINTER(ChXSCoords)]

ch_xs_coords_get = _chlib.ch_xs_coords_get
ch_xs_coords_get.restype = None
ch_xs_coords_get.argtypes = [
    POINTER(ChXSCoords),
    c_size_t,
    POINTER(c_float),
    POINTER(c_float),
]

ch_xs_coords_get_arr = _chlib.ch_xs_coords_get_arr
ch_xs_coords_get_arr.restype = None
ch_xs_coords_get_arr.argtypes = [
    POINTER(ChXSCoords),
    POINTER(c_float),
    POINTER(c_float),
]

ch_xs_coords_set = _chlib.ch_xs_coords_get
ch_xs_coords_set.restype = None
ch_xs_coords_set.argtypes = [
    POINTER(ChXSCoords),
    c_size_t,
    POINTER(c_float),
    POINTER(c_float),
]

ch_xs_coords_init = _chlib.ch_xs_coords_init
ch_xs_coords_init.restype = None
ch_xs_coords_init.argtypes = [
    POINTER(ChXSCoords),
    c_size_t,
    POINTER(c_float),
    POINTER(c_float),
]

if __name__ == "__main__":
    import numpy as np

    xs_coords_ptr = ch_xs_coords_new(10)
    ch_xs_coords_init(
        xs_coords_ptr, 5, (c_float * 5)(1, 2, 3, 4, 5), (c_float * 5)(1, 0, 0, 0, 1)
    )

    coords_length = ch_xs_coords_length(xs_coords_ptr)

    print(ch_xs_coords_length(xs_coords_ptr))

    station = np.empty((coords_length,), dtype=c_float)
    elevation = np.empty((coords_length,), dtype=c_float)

    station = np.empty((15,), dtype=c_float)
    elevation = np.empty((15,), dtype=c_float)

    c_float_p = POINTER(c_float)

    ch_xs_coords_get_arr(
        xs_coords_ptr,
        station.ctypes.data_as(c_float_p),
        elevation.ctypes.data_as(c_float_p),
    )

    ch_xs_coords_free(xs_coords_ptr)
    xs_coords_ptr = None
