file ( GLOB SimpleITKIOSource *.cxx *.h )

include_directories ( ${CMAKE_CURRENT_SOURCE_DIR} )
add_library ( SimpleITKIO STATIC ${SimpleITKIOSource} )
target_link_libraries ( SimpleITKIO SimpleITKCommon ${ITK_LIBRARIES} )



# Add custom command that will delete java files which need to be rebuilt when changes
# are made to IO
if( WRAP_JAVA )
  add_custom_command(
    TARGET SimpleITKIO
    POST_BUILD
    COMMENT "Cleaning java build..."
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/org/itk/simple/*.java
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/build/org/itk/simple/*.class
  )
endif()
