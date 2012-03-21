# Include the hand-written and auto-generated code
include_directories (
 ${CMAKE_CURRENT_SOURCE_DIR}/../include
 ${CMAKE_CURRENT_BINARY_DIR}/../include
 )

set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER )
include(${ITK_USE_FILE})

set_source_files_properties ( ${SimpleITKBasicFiltersGeneratedSource} PROPERTIES GENERATED 1 )
add_library ( SimpleITKBasicFilters ${SimpleITKBasicFiltersSource} ${SimpleITKBasicFiltersGeneratedSource} )
target_link_libraries ( SimpleITKBasicFilters SimpleITKCommon ${ITK_LIBRARIES} )
add_dependencies ( SimpleITKBasicFilters BasicFiltersSourceCode)

sitk_install_exported_target( SimpleITKBasicFilters )
install( FILES ${CMAKE_CURRENT_BINARY_DIR}/../include/SimpleITKBasicFiltersGeneratedHeaders.h
  DESTINATION ${SimpleITK_INSTALL_INCLUDE_DIR}
  COMPONENT Development )