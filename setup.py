from setuptools import setup

name = "chulengo"

about = {}
with open("chulengo/__init__.py") as fp:
    exec(fp.read(), about)
release = about["__release__"]
version = about["__version__"]

dev_status = "Development Status :: 2 - Pre-Alpha"

setup_kwargs = {
    "name": name,
    "version": release,
    "packages": ["chulengo"],
    "license": "License :: OSI Approved :: GNU General Public License v3 (GPLv3)",
    "author": "Marian Domanski",
    "author_email": "shrieks.walnut.0s@icloud.com",
    "description": "Hydraulics",
    "classifiers": [
        dev_status,
        "Intended Audience :: Science/Research",
        "Programming Language :: Python :: 3",
        "Topic :: Scientific/Engineering :: Hydrology",
    ],
    "project_urls": {"Source": "https://github.com/mmdski/chulengo"},
    "install_requires": ["numpy"],
    "python_requires": "~=3.12",
}

setup(**setup_kwargs)
