#
# Build the documentation
#

option( BUILD_DOXYGEN "Build SimpleITK Doxygen" OFF )
 
if (BUILD_DOXYGEN)

  find_package( Doxygen )

  #
  # Configure the script and the doxyfile, then add target
  #

  option(USE_ITK_DOXYGEN_TAGS "Download ITK's Doxygen tags" ON)

  if (USE_ITK_DOXYGEN_TAGS)

    # Information on how to retrieve the ITK documentation tag file
    SET(ITK_DOXYGEN_TAG_LOCATION "http://public.kitware.com/pub/itk/NightlyDoxygen/InsightDoxygenDocTag")
    SET(ITK_DOXYGEN_COMPRESSED_TAG_FILE ${PROJECT_BINARY_DIR}/Doxygen/InsightDoxygen.tag.gz)
    SET(ITK_DOXYGEN_TAG_FILE ${PROJECT_BINARY_DIR}/Doxygen/InsightDoxygen.tag)

    # Get the ITK documentation tag file
    IF(NOT EXISTS ${ITK_DOXYGEN_COMPRESSED_TAG_FILE})
      FILE( DOWNLOAD
            ${ITK_DOXYGEN_TAG_LOCATION}
            ${ITK_DOXYGEN_COMPRESSED_TAG_FILE}
            TIMEOUT 60
            STATUS statusITKDoxygenTagFile
            SHOW_PROGRESS )
      LIST(GET statusITKDoxygenTagFile 0 statusITKDoxygenTagFile)
      IF(statusITKDoxygenTagFile)
        FILE(REMOVE ${ITK_DOXYGEN_COMPRESSED_TAG_FILE})
      ENDIF()
    ENDIF(NOT EXISTS ${ITK_DOXYGEN_COMPRESSED_TAG_FILE})
      IF(EXISTS ${ITK_DOXYGEN_COMPRESSED_TAG_FILE})
      FIND_PROGRAM(GZIP_TOOL NAMES gzip)
      IF(GZIP_TOOL)
        EXECUTE_PROCESS(COMMAND ${GZIP_TOOL} -df ${ITK_DOXYGEN_COMPRESSED_TAG_FILE})
        SET(DOXYGEN_TAGFILES_PARAMETER "${ITK_DOXYGEN_TAG_FILE}=http://www.itk.org/Doxygen/html/")
      ENDIF()
    ELSE()
      SET(DOXYGEN_TAGFILES_PARAMETER "")
    ENDIF()
  endif()


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
