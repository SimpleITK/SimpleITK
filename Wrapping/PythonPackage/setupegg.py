"""
A setup.py script to use setuptools, which gives egg goodness, etc.
"""
from ez_setup import use_setuptools
use_setuptools()
import os

execfile(os.path.dirname(os.path.realpath(__file__)) + '/setup.py')
