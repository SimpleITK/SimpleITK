

# Set up code generation
include(${SimpleITK_SOURCE_DIR}/CMake/generate_filter_source.cmake)
generate_filter_source()

add_subdirectory( src )


