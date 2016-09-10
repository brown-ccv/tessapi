#!/usr/bin/env python

from setuptools import setup, Extension

tessapi = Extension("tessapi",
                    language="c++",
                    extra_compile_args=["-std=c++11"],
                    include_dirs=["tessapi"],
                    libraries=["tesseract", "lept"],
                    sources=["tessapi/tessapi.cpp"])

setup(
    name="tessapi",
    version="0.0.1",
    url="https://bitbucket.org/brown-data-science/tessapi",
    description="Tesseract API bindings for Python",
    classifiers=[
        "Programming Language :: Python :: 2",
        "Programming Language :: Python :: 2.7"],
    provides=["tessapi"],
    ext_modules=[tessapi],
    install_requires=["pybind11>=1.8.1"]
)
