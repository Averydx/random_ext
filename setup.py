from distutils.core import setup, Extension
import numpy as np

module = Extension("Rand",sources = ['/Users/averydrennan/random_lib/src/c_extension/rand_pyext.c','/Users/averydrennan/random_lib/src/c_extension/PCG.c'])

setup(name="PackageName",
      version="0.0.1",
      description="Module for the computation of random numbers using PCG",
      ext_modules=[module],
      include_dirs=[np.get_include()])