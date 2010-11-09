file ( GLOB SimpleITKCommonSource *.cxx *.h )
file ( GLOB SimpleITKAncillarySource Ancillary/*.h Ancillary/*.cxx )

include_directories ( ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Ancillary )
add_library ( SimpleITKCommon ${SimpleITKCommonSource} ${SimpleITKAncillarySource} )
target_link_libraries ( SimpleITKCommon ITKCommon )
