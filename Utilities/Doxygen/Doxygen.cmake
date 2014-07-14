#
# Build the documentation
#

option( BUILD_DOXYGEN "Build SimpleITK Doxygen" OFF )

if (BUILD_DOXYGEN)

  find_package( Doxygen )

  #
  # Add option to use ITK tags, will download during configuration
  # time if needed.
  #

  option(USE_ITK_DOXYGEN_TAGS "Download ITK's Doxygen tags" ON)

  if (USE_ITK_DOXYGEN_TAGS)
    add_custom_command( OUTPUT "${PROJECT_BINARY_DIR}/Documentation/Doxygen/InsightDoxygen.tag"
      COMMAND ${CMAKE_COMMAND} -D "PROJECT_SOURCE_DIR:PATH=${PROJECT_SOURCE_DIR}"
      -D "OUTPUT_PATH:PATH=${PROJECT_BINARY_DIR}/Documentation/Doxygen"
      -P "${PROJECT_SOURCE_DIR}/Utilities/Doxygen/ITKDoxygenTags.cmake"
      DEPENDS "${PROJECT_SOURCE_DIR}/Utilities/Doxygen/ITKDoxygenTags.cmake"
      )
    set(DOXYGEN_TAGFILES_PARAMETER "${PROJECT_BINARY_DIR}/Documentation/Doxygen/InsightDoxygen.tag=http://www.itk.org/Doxygen/html/")
  endif()

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
    DEPENDS "${PROJECT_BINARY_DIR}/Documentation/Doxygen/InsightDoxygen.tag"
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/Utilities/Doxygen
    )

  message( STATUS
    "To generate Doxygen's documentation, you need to build the Documentation target"
    )

endif (BUILD_DOXYGEN)
