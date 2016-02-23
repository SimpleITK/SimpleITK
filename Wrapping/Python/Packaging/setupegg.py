"""
A setup.py script to use setuptools, which gives wheel and egg goodness, etc.
"""
try:
    from setuptools import setup
except ImportError:
    # SimpleITK no longer provides ez_setup, but a copy may be around
    # so we give it a try. It's intended that setuptools be install in
    # a constructed virtualenv during the make process.
    from ez_setup import use_setuptools
    use_setuptools()
import os

from setuptools import setup

fn = os.path.dirname(os.path.realpath(__file__)) + '/setup.py'
exec(open(fn).read())
