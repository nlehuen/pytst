import distutils
from distutils.core import setup, Extension

setup(name = "TST for Python",
      version = "2.2",
      py_modules = ["tst"],
      ext_modules = [Extension("_tst", ["tst_wrap.cxx"],extra_compile_args=['-x c++'])],
    )
