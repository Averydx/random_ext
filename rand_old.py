import ctypes

import ctypes
import numpy as np
from scipy.stats import norm
import matplotlib.pyplot as plt

rand = ctypes.CDLL("./librand.dylib")

class PCG(ctypes.Structure):
    _fields_ = [("state", ctypes.c_uint64),
                ("increment", ctypes.c_uint64),
                ("multiplier",ctypes.c_uint64)]
    
class Generator:
    gen:PCG

    def __init__(self,seed):
        rand.PCG_init.argtypes = []
        rand.PCG_init.restype = ctypes.POINTER(PCG)
        self.gen = rand.PCG_init(seed)


    def standard_normal(self,size):
        rand.standard_normal.argtypes = [ctypes.c_size_t,ctypes.POINTER(PCG)]
        rand.standard_normal.restype = ctypes.POINTER(ctypes.c_double)
        arr = rand.standard_normal(size,self.gen)
        return arr[:size]





