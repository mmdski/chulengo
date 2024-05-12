from ctypes import c_double, c_size_t, CDLL, POINTER, Structure
import os
import platform

_file_path, _ = os.path.split(__file__)
if platform.system() == "Windows":
    _chlib_path = os.path.join(_file_path, "lib", "chl.pymem.dll")
elif platform.system() == "Darwin":
    _chlib_path = os.path.join(_file_path, "lib", "libchl.pymem.dylib")

_chlib = CDLL(_chlib_path)


c_double_p = POINTER(c_double)

N_XS_PROPS = 9


class ChXSCoords(Structure):
    pass


ChXSCoordsPtr = POINTER(ChXSCoords)

ch_xs_coords_new = _chlib.ch_xs_coords_new
ch_xs_coords_new.restype = ChXSCoordsPtr
ch_xs_coords_new.argtypes = [c_size_t]

ch_xs_coords_copy = _chlib.ch_xs_coords_copy
ch_xs_coords_copy.restype = ChXSCoordsPtr
ch_xs_coords_copy.argtypes = [ChXSCoordsPtr]

ch_xs_coords_free = _chlib.ch_xs_coords_free
ch_xs_coords_free.restype = None
ch_xs_coords_free.argtypes = [ChXSCoordsPtr]

ch_xs_coords_length = _chlib.ch_xs_coords_length
ch_xs_coords_length.restype = c_size_t
ch_xs_coords_length.argtypes = [ChXSCoordsPtr]

ch_xs_coords_get = _chlib.ch_xs_coords_get
ch_xs_coords_get.restype = None
ch_xs_coords_get.argtypes = [ChXSCoordsPtr, c_size_t, c_double_p, c_double_p]

ch_xs_coords_get_arr = _chlib.ch_xs_coords_get_arr
ch_xs_coords_get_arr.restype = None
ch_xs_coords_get_arr.argtypes = [ChXSCoordsPtr, c_double_p, c_double_p]

ch_xs_coords_set = _chlib.ch_xs_coords_get
ch_xs_coords_set.restype = None
ch_xs_coords_set.argtypes = [ChXSCoordsPtr, c_size_t, c_double_p, c_double_p]

ch_xs_coords_set_arr = _chlib.ch_xs_coords_set_arr
ch_xs_coords_set_arr.restype = ChXSCoordsPtr
ch_xs_coords_set_arr.argtypes = [ChXSCoordsPtr, c_size_t, c_double_p, c_double_p]

ch_xs_coords_push = _chlib.ch_xs_coords_push
ch_xs_coords_push.restype = ChXSCoordsPtr
ch_xs_coords_push.argtypes = [ChXSCoordsPtr, c_double_p, c_double_p]

ch_xs_coords_subsect = _chlib.ch_xs_coords_subsect
ch_xs_coords_subsect.restype = ChXSCoordsPtr
ch_xs_coords_subsect.argtypes = [ChXSCoordsPtr, c_double, c_double, ChXSCoordsPtr]

ch_xs_coords_wetted = _chlib.ch_xs_coords_wetted
ch_xs_coords_wetted.restype = ChXSCoordsPtr
ch_xs_coords_wetted.argtypes = [ChXSCoordsPtr, c_double, ChXSCoordsPtr]


class ChXSSubdiv(Structure):
    pass


ChXSSubdivPtr = POINTER(ChXSSubdiv)

ch_xs_subdiv_new = _chlib.ch_xs_subdiv_new
ch_xs_subdiv_new.restype = ChXSSubdivPtr
ch_xs_subdiv_new.argtypes = [c_double, ChXSCoordsPtr]

ch_xs_subdiv_free = _chlib.ch_xs_subdiv_free
ch_xs_subdiv_free.restype = None
ch_xs_subdiv_free.argtypes = [ChXSSubdivPtr]

ch_xs_subdiv_props = _chlib.ch_xs_subdiv_props
ch_xs_subdiv_props.restype = None
ch_xs_subdiv_props.argtypes = [ChXSSubdivPtr, c_double, c_double_p]

if __name__ == "__main__":
    import numpy as np

    xs_coords_ptr = ch_xs_coords_new(10)
    ch_xs_coords_set_arr(
        xs_coords_ptr, 5, (c_double * 5)(1, 2, 3, 4, 5), (c_double * 5)(1, 0, 0, 0, 1)
    )

    coords_length = ch_xs_coords_length(xs_coords_ptr)

    station = np.empty((coords_length,), dtype=c_double)
    elevation = np.empty((coords_length,), dtype=c_double)

    ch_xs_coords_get_arr(
        xs_coords_ptr,
        station.ctypes.data_as(c_double_p),
        elevation.ctypes.data_as(c_double_p),
    )

    ch_xs_coords_free(xs_coords_ptr)
    xs_coords_ptr = None
