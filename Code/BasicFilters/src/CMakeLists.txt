


# Include the hand-written and auto-generated code
include_directories (
 ${CMAKE_CURRENT_SOURCE_DIR}/../include
 )

include(${ITK_USE_FILE})

add_library ( SimpleITKBasicFilters STATIC ${SimpleITKBasicFiltersSource} ${SimpleITKBasicFiltersGeneratedSource})
add_dependencies ( SimpleITKBasicFilters BasicFiltersSourceCode)

