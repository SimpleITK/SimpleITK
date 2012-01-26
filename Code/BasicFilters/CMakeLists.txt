

# Set up code generation
include(${SimpleITK_SOURCE_DIR}/CMake/generate_filter_source.cmake)
generate_filter_source()

# Glob non-generated BasicFilters and add to cache
file ( GLOB SimpleITKBasicFiltersSource src/*.cxx )

add_subdirectory( src )

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


