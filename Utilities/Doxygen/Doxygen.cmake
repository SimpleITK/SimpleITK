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
    set(ITK_DOXYGEN_TAGFILE "" CACHE PATH "ITK Doxygen tag file location. Empty string automatically downloads." )

    if ("${ITK_DOXYGEN_TAGFILE}" STREQUAL "")
      sitk_enforce_forbid_downloads("InsightDoxygen.tag")
      set(ITK_DOXYGEN_TAGFILE "${PROJECT_BINARY_DIR}/Documentation/Doxygen/InsightDoxygen.tag")
      add_custom_command( OUTPUT "${ITK_DOXYGEN_TAGFILE}"
        COMMAND ${CMAKE_COMMAND} -D "PROJECT_SOURCE_DIR:PATH=${PROJECT_SOURCE_DIR}"
        -D "OUTPUT_PATH:PATH=${PROJECT_BINARY_DIR}/Documentation/Doxygen"
        -P "${CMAKE_CURRENT_LIST_DIR}/ITKDoxygenTags.cmake"
        DEPENDS "${CMAKE_CURRENT_LIST_DIR}/ITKDoxygenTags.cmake"
        )
    endif()

    set(ITK_DOXYGEN_ROOT_URL "https://www.itk.org/Doxygen/html/" CACHE STRING "URL for the ITK Doxygen web root")
    set(DOXYGEN_TAGFILES_PARAMETER "${ITK_DOXYGEN_TAGFILE}=${ITK_DOXYGEN_ROOT_URL}")

  endif()

  set(DOXYGEN_MATHJAX_RELPATH
    "https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/"
    CACHE STRING "The destination or URL to contain the MathJax.js script")

  set(SIMPLEITK_DOXYGEN_TAGFILE "${PROJECT_BINARY_DIR}/Utilities/Doxygen/SimpleITKDoxygen.tag")

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

  if (USE_ITK_DOXYGEN_TAGS)
    set(TAGS_DEPENDS DEPENDS ${ITK_DOXYGEN_TAGFILE})
  endif ()

  add_custom_target(Documentation
    COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Utilities/Doxygen/doxygen.config
    MAIN_DEPENDENCY ${PROJECT_BINARY_DIR}/Utilities/Doxygen/doxygen.config
    DEPENDS "${PROJECT_BINARY_DIR}/Documentation/Doxygen/Examples.dox"
    DEPENDS "${PROJECT_BINARY_DIR}/Documentation/Doxygen/FilterCoverage.dox"
    ${TAGS_DEPENDS}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/Utilities/Doxygen
    )

  # Create a "datetime.txt" file for a time stamp of the code
  # generation. The time stamp in dynamically inserted into the HTML
  # with javascript, to reduce the code change churn with regular
  # updates.
  add_custom_command(
    TARGET Documentation
    POST_BUILD
    WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/Documentation/html"
    COMMAND ${PYTHON_EXECUTABLE} "${CMAKE_CURRENT_LIST_DIR}/datetime.py"
    )

  message( STATUS
    "To generate Doxygen's documentation, you need to build the Documentation target"
    )

endif (BUILD_DOXYGEN)
