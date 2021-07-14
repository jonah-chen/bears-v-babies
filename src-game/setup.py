"""
set up the python module for bears vs babies
"""

from distutils.core import setup, Extension
import glob
import os.system
module = Extension("bearsvbabies", sources=glob.glob("*.cpp"), language="c++", extra_compile_args=["-std=c++2a"])

setup(name="bearsvbabies",
        description="server for bears versus babies game",
        version="0.1",
        ext_modules=[module]
        )

system("mv build/bearsvbabies.cpython-39-x86_64-linux-gnu.so ../server/bearsvbabies.cpython-39-x86_64-linux-gnu.so")
