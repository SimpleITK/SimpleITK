file ( GLOB SimpleITKSource *.cxx *.h )
file ( GLOB SimpleITKAncillarySource Ancillary/*.h Ancillary/*.cxx )

include_directories ( ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Ancillary )
add_library ( SimpleITK ${SimpleITKSource} ${SimpleITKAncillarySource} )
set ( SimpleITK_LIBRARIES SimpleITK )


