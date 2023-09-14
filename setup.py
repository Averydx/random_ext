from distutils.core import setup, Extension
import numpy as np

module = Extension("Rand",sources = ['./src/c_extension/rand_pyext.c',
                                     './src/c_extension/PCG.c'],
                   extra_compile_args=['-O3'],
                   )

setup(name="Rand",
      version="0.0.1",
      description="Module for the computation of random numbers using PCG",
      ext_modules=[module],
      include_dirs=[np.get_include()],
      package_data={'': ['*.so', '*.pyi','*.pyd']})