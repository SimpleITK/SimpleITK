# Include the hand-written and auto-generated code
include_directories (
 ${CMAKE_CURRENT_SOURCE_DIR}/../include
 ${CMAKE_CURRENT_BINARY_DIR}/../include
 )

include(${ITK_USE_FILE})

set_source_files_properties ( ${SimpleITKBasicFiltersGeneratedSource} PROPERTIES GENERATED 1 )
add_library ( SimpleITKBasicFilters STATIC ${SimpleITKBasicFiltersSource} ${SimpleITKBasicFiltersGeneratedSource})
add_dependencies ( SimpleITKBasicFilters BasicFiltersSourceCode)


