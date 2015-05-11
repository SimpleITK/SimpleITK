import sys

if not(sys.modules.get("wheel")):
    from setuptools.command import easy_install
    easy_install.main(["wheel"])
