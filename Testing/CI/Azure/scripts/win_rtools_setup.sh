
# This script is for setting up the rtools40 libraries required to
# build SimpleITK under windows.
# pacman needs to be run from the rtools msys2 shell.
# The Azure windows bash also appears to be msys2 based and
# it is important to avoid mixing them up
# The MSYSTEM variable needs to be set to MSYS to
# force the correct behaviour
#
pacman -Sy
pacman --noconfirm -S mingw-w64-{i686,x86_64}-intel-tbb
