cmake_minimum_required(VERSION 3.26)

project(SimpleITKInternalPythonPackage NONE)

#-----------------------------------------------------------------------------
# Install SimpleITK Python "Runtime" components
install(
  CODE
    "
unset(CMAKE_INSTALL_COMPONENT)
set(COMPONENT \"Python\")
include\(\"${CMAKE_CURRENT_SOURCE_DIR}/cmake_install.cmake\")
unset(CMAKE_INSTALL_COMPONENT)
"
)
