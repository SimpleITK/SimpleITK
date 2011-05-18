# Generate the SimpleITKConfig.cmake file in the build tree.  Also configure
# one for installation.  The file tells external projects how to use
# SimpleITK.


#-----------------------------------------------------------------------------
# Settings specific to the build tree.

# Library directory.
set(SimpleITK_LIBRARY_DIRS_CONFIG ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# Determine the include directories needed.
set(SimpleITK_INCLUDE_DIRS_CONFIG
  ${SimpleITK_INCLUDE_DIR}
)

# The "use" file.
set(SimpleITK_USE_FILE ${SimpleITK_BINARY_DIR}/UseSimpleITK.cmake)

#-----------------------------------------------------------------------------
# Configure SimpleITKConfig.cmake for the build tree.
configure_file(${SimpleITK_SOURCE_DIR}/SimpleITKConfig.cmake.in
               ${SimpleITK_BINARY_DIR}/SimpleITKConfig.cmake @ONLY IMMEDIATE)

