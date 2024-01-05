#!/usr/bin/env python
# coding=utf-8

import os
import sys

from setuptools import find_packages, setup

here = os.path.abspath(os.path.dirname(__file__))
sys.path.append(here)

import versioneer  # noqa: E402

with open(os.path.join(here, "README.md"), encoding="utf-8") as f:
    long_description = f.read()


setup(
    name="fast_frechet",
    description="Comparison of different (fast) discrete Frechet distance implementations",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/avitase/fast_frechet",
    author="Nis Meinert",
    author_email="nis.meinert@dlr.de",
    version=versioneer.get_version(),
    cmdclass=versioneer.get_cmdclass(),
    packages=find_packages(exclude=["tests"]),
    python_requires=">=3.10",
    install_requires=[
        "numpy",
        "numba",
    ],
    extras_require={
        "dev": [
            "pre-commit",
            "pytest",
            "pytest-cov",
        ],
    },
)
