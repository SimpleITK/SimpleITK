#
# Build the documentation
#

option( BUILD_DOXYGEN "Build SimpleITK Doxygen" OFF )
 
if (BUILD_DOXYGEN)

  find_package( Doxygen )

  #
  # Configure the script and the doxyfile, then add target
  #
  configure_file(${PROJECT_SOURCE_DIR}/Utilities/Doxygen/doxygen.config.in
    ${PROJECT_BINARY_DIR}/Utilities/Doxygen/doxygen.config)

  add_custom_target(Documentation ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Utilities/Doxygen/doxygen.config
    MAIN_DEPENDENCY ${PROJECT_BINARY_DIR}/Utilities/Doxygen/doxygen.config
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/Utilities/Doxygen
    )

  message( STATUS
    "To generate Doxygen's documentation, you need to build the Documentation target"
    )
  
endif (BUILD_DOXYGEN)
