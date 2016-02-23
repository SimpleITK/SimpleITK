"""
A setup.py script to use setuptools, which gives egg goodness, etc.
"""
from ez_setup import use_setuptools
use_setuptools()
import os

fn = os.path.dirname(os.path.realpath(__file__)) + '/setup.py'
exec(open(fn).read())
