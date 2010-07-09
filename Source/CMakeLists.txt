file ( GLOB SimpleITKSource *.cxx *.h )

include_directories ( ${CMAKE_CURRENT_SOURCE_DIR} )
add_library ( SimpleITK ${SimpleITKSource} )
set ( SimpleITK_LIBRARIES SimpleITK )


