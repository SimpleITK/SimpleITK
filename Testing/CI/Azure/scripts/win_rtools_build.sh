

# This is the build script, that needs to be executed in the rtools40 MINGW64 shell
# Selecting the correct shell is via the MSYSTEM variable (should be MINGW64)
set -x

which gcc
which git
which cmake

cmake --version
#which ninja
echo ${RHOME}

export CC=/mingw64/bin/gcc.exe
export CXX=/mingw64/bin/g++.exe
export FC=/mingw64/bin/gfortran.exe

#LP=$(cygpath "${AGENT_BUILDDIRECTORY}")
#export VERBOSE=1
#export LD_LIBRARY_PATH=${LP}/ITK-build/lib:${LP}/SimpleITK-build/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}

#echo $LD_LIBRARY_PATH
ctest --debug-find -S ${BUILD_SOURCESDIRECTORY}/Testing/CI/Azure/azure.cmake -VV -j 3
echo "Exit status $?"


#/c/Program\ Files/CMake/bin/cmake.exe -G 'MSYS Makefiles' -DCMAKE_CXX_COMPILER=${RTO}/g++.exe \
#-DCMAKE_C_COMPILER=${RTO}/gcc.exe -DCMAKE_FORTRAN_COMPILER=${RTO}/gfortran.exe -DWRAP_DEFAULT=OFF \
#-DWRAP_R=ON  -DEXTERNAL_ITK_Module_ITKTBB:BOOL=ON \
#-DR_COMMAND="${RHOME}/bin/x64/R.exe" \
#-DCMAKE_VERBOSE_MAKEFILE:BOOL=ON  ../SimpleITK/Superbuild

#make -j2
