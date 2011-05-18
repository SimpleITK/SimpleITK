
# Glob non-generated BasicFilters and add to cache
file ( GLOB SimpleITKBasicFiltersSource include/*.txx src/*.cxx )
set ( SimpleITKBasicFiltersSource ${SimpleITKBasicFiltersSource} CACHE INTERNAL "" )

# Set up code generation
include(${SimpleITK_SOURCE_DIR}/CMake/generate_filter_source.cmake)
generate_filter_source()


# Include the hand-written and auto-generated code
include_directories (
 ${CMAKE_CURRENT_SOURCE_DIR}/include
 ${CMAKE_CURRENT_BINARY_DIR}/include
 )


add_library ( SimpleITKBasicFilters STATIC ${SimpleITKBasicFiltersSource} ${SimpleITKBasicFiltersGeneratedSource})
target_link_libraries ( SimpleITKBasicFilters SimpleITKCommon ${ITK_LIBRARIES} )


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
