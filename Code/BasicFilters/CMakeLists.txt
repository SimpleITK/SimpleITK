
file ( GLOB SimpleITKBasicFiltersSource *.cxx *.h )

include(SourceCodeGenerator.cmake)

include_directories (
 ${CMAKE_CURRENT_SOURCE_DIR}
 ${CMAKE_CURRENT_BINARY_DIR}
 )

add_library ( SimpleITKBasicFilters ${SimpleITKBasicFiltersSource} )
target_link_libraries ( SimpleITKBasicFilters SimpleITKCommon ITKBasicFilters ITKReview )


# Add custom command that will delete java files which need to be rebuilt when changes
# are made to BasicFilters
if( WRAP_JAVA )
  add_custom_command(
    TARGET SimpleITKBasicFilters
    POST_BUILD
    COMMENT "Cleaning java build..."
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/org/itk/simple/*.java
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/build/org/itk/simple/*.class
  )
endif()
