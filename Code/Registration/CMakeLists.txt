set ( LIBNAME SimpleITKRegistration )
file ( GLOB ${LIBNAME}Headers *.h )
set ( MASTERHEADER ${SimpleITK_BINARY_DIR}/include/${LIBNAME}.h )
CreateLibMasterHeader( "${LIBNAME}" "${MASTERHEADER}"  "${${LIBNAME}Headers}")

file ( GLOB SimpleITKRegistrationSource *.cxx *.h )

include_directories ( ${CMAKE_CURRENT_SOURCE_DIR} )
add_library ( SimpleITKRegistration ${SimpleITKRegistrationSource} )
target_link_libraries ( SimpleITKRegistration SimpleITKBasicFilters ${ITK_LIBRARIES} )

# Add custom command that will delete java files which need to be rebuilt when changes
# are made to Common
if( WRAP_JAVA )
  add_custom_command(
    TARGET SimpleITKRegistration
    POST_BUILD
    COMMENT "Cleaning java build..."
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/org/itk/simple/*.java
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/build/org/itk/simple/*.class
  )
endif()
