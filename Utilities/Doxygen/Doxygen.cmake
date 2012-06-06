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

  add_custom_command( OUTPUT "${PROJECT_BINARY_DIR}/Documentation/Doxygen/Examples.dox"
    COMMAND ${CMAKE_COMMAND} -D "PROJECT_SOURCE_DIR:PATH=${PROJECT_SOURCE_DIR}"
    -D "OUTPUT_FILE:PATH=${PROJECT_BINARY_DIR}/Documentation/Doxygen/Examples.dox"
    -P "${PROJECT_SOURCE_DIR}/Utilities/Doxygen/GenerateExamplesDox.cmake"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/Examples"
    DEPENDS "${PROJECT_SOURCE_DIR}/Examples" "${PROJECT_SOURCE_DIR}/Utilities/Doxygen/GenerateExamplesDox.cmake"
    )

  add_custom_command( OUTPUT "${PROJECT_BINARY_DIR}/Documentation/Doxygen/FilterCoverage.dox"
    COMMAND ${PYTHON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/Utilities/CSVtoTable.py -d ${PROJECT_SOURCE_DIR}/Utilities/filters.csv ${PROJECT_BINARY_DIR}/Documentation/Doxygen/FilterCoverage.dox
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/Utilities"
    DEPENDS "${PROJECT_SOURCE_DIR}/Utilities/filters.csv" "${PROJECT_SOURCE_DIR}/Utilities/CSVtoTable.py"
    )

  add_custom_target(Documentation ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Utilities/Doxygen/doxygen.config
    MAIN_DEPENDENCY ${PROJECT_BINARY_DIR}/Utilities/Doxygen/doxygen.config
    DEPENDS "${PROJECT_BINARY_DIR}/Documentation/Doxygen/Examples.dox"
    DEPENDS "${PROJECT_BINARY_DIR}/Documentation/Doxygen/FilterCoverage.dox"
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/Utilities/Doxygen
    )

  message( STATUS
    "To generate Doxygen's documentation, you need to build the Documentation target"
    )
  
endif (BUILD_DOXYGEN)
