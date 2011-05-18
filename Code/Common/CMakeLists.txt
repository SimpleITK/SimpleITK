file ( GLOB SimpleITKCommonSource *.cxx *.h ../Registration/*.h ../Registration/*.cxx)
file ( GLOB SimpleITKAncillarySource Ancillary/*.h Ancillary/*.cxx )

include_directories ( ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Ancillary )
add_library ( SimpleITKCommon STATIC ${SimpleITKCommonSource} ${SimpleITKAncillarySource} )
target_link_libraries ( SimpleITKCommon ${ITK_LIBRARIES} )



# Add custom command that will delete java files which need to be rebuilt when changes
# are made to Common
if( WRAP_JAVA )
  add_custom_command(
    TARGET SimpleITKCommon
    POST_BUILD
    COMMENT "Cleaning java build..."
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/org/itk/simple/*.java
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/build/org/itk/simple/*.class
  )
endif()
