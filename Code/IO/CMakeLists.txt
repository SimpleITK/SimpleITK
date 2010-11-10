file ( GLOB SimpleITKIOSource *.cxx *.h )

include_directories ( ${CMAKE_CURRENT_SOURCE_DIR} )
add_library ( SimpleITKIO ${SimpleITKIOSource} )
target_link_libraries ( SimpleITKIO SimpleITKCommon ITKIO )
