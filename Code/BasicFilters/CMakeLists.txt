
file ( GLOB SimpleITKBasicFiltersSource *.cxx *.h )

include(SourceCodeGenerator.cmake)

include_directories (
 ${CMAKE_CURRENT_SOURCE_DIR}
 ${CMAKE_CURRENT_BINARY_DIR}
 )

add_library ( SimpleITKBasicFilters ${SimpleITKBasicFiltersSource} )
target_link_libraries ( SimpleITKBasicFilters SimpleITKCommon ITKBasicFilters )
