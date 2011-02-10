file ( GLOB SimpleITKCommonSource *.cxx *.h )
file ( GLOB SimpleITKAncillarySource Ancillary/*.h Ancillary/*.cxx )

include_directories ( ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Ancillary )
add_library ( SimpleITKCommon ${SimpleITKCommonSource} ${SimpleITKAncillarySource} )
target_link_libraries ( SimpleITKCommon ITKCommon )



# Add custom command that will delete java files which need to be rebuilt when changes
# are made to Common
if( WRAP_JAVA )
  add_custom_command(
    TARGET SimpleITKCommon
    POST_BUILD
    COMMENT "Cleaning java build..."
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/org/itk/simple/*.java
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/build/org/itk/simple/*.class
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/SimpleITKJAVA_wrap.cxx
  )
endif()

# Clean Lua wrapping
if( WRAP_LUA )
  add_custom_command(
    TARGET SimpleITKCommon
    POST_BUILD
    COMMENT "Cleaning lua wrapping..."
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/SimpleITKLUA_wrap.cxx
  )
endif()

# Clean Python wrapping
if( WRAP_PYTHON )
  add_custom_command(
    TARGET SimpleITKCommon
    POST_BUILD
    COMMENT "Cleaning python wrapping..."
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/SimpleITK.py
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/SimpleITK.pyc
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/SimpleITKPYTHON_wrap.cxx
  )
endif()

# Clean TCL wrapping
if( WRAP_TCL )
  add_custom_command(
    TARGET SimpleITKCommon
    POST_BUILD
    COMMENT "Cleaning tcl wrapping..."
    COMMAND cmake -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/SimpleITKTCL_wrap.cxx
  )
endif()

# Clean CSharp wrapping
if( WRAP_CSHARP )
  # Not sure what needs doing, but put it here if necessary
endif()

# Clean R wrapping
if( WRAP_R )
  add_custom_command(
    TARGET SimpleITKCommon
    POST_BUILD
    COMMENT "Cleaning R wrapping..."
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/SimpleITK.R
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/SimpleITK
  )
endif()

# Clean Ruby wrapping
if( WRAP_RUBY )
  add_custom_command(
    TARGET SimpleITKCommon
    POST_BUILD
    COMMENT "Cleaning ruby wrapping..."
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/SimpleITKRUBY_wrap.cxx
  )
endif()

