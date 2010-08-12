

option ( WRAP_LUA "Wrap Lua" ON )
option ( WRAP_PYTHON "Wrap Python" OFF )
option ( WRAP_JAVA "Wrap Java" OFF )

if ( WRAP_LUA OR WRAP_PYTHON OR WRAP_JAVA )
  find_package ( SWIG REQUIRED )
  include ( ${SWIG_USE_FILE} )
  set_source_files_properties ( SimpleITK.i PROPERTIES CPLUSPLUS ON )
  file ( GLOB SWIG_HEADERS ${SimpleITK_SOURCE_DIR}/Source/*.h )
  include_directories ( ${SimpleITK_SOURCE_DIR}/Source )

  set ( CMAKE_SWIG_FLAGS "" )
  set ( SWIG_MODULE_SimpleITK_EXTRA_DEPS ${SWIG_HEADERS} )

endif()


# Find lua
if ( WRAP_LUA )
  find_package ( Lua51 REQUIRED )
  include_directories ( ${LUA_INCLUDE_DIR} )

  # Run swig
  SWIG_module_initialize ( SimpleITK lua )
  SWIG_add_source_to_module ( SimpleITK swig_generated_source SimpleITK.i ${SWIG_HEADERS} )

  add_library ( SimpleITKLuaModule SimpleITKLUA_wrap.cxx )
  add_executable ( SimpleITKLua SimpleITKLuaMain.cxx )
  target_link_libraries ( SimpleITKLua SimpleITKLuaModule ${SimpleITK_LIBRARIES} ${LUA_LIBRARIES} ${ITK_LIBRARIES} )

  if ( UNIX )
    target_link_libraries ( SimpleITKLua readline curses )
  endif()

endif()

# Find Python
if ( WRAP_PYTHON )
  find_package ( PythonLibs REQUIRED )
  include_directories ( ${PYTHON_INCLUDE_DIR} )

  # Run swig
  SWIG_add_module ( SimpleITK python SimpleITK.i SimpleITKPYTHON_wrap.cxx )

  # SWIG_module_initialize ( SimpleITK python )
  # SWIG_add_source_to_module ( SimpleITK swig_generated_source SimpleITK.i ${SWIG_HEADERS} )

  # add_library ( SimpleITKPythonModule SimpleITKPYTHON_wrap.cxx )
  # add_executable ( SimpleITKPython SimpleITKPythonMain.cxx )
  # target_link_libraries ( SimpleITKPython SimpleITK SimpleITKPythonModule ${PYTHON_LIBRARIES} ${ITK_LIBRARIES} )
  SWIG_link_libraries ( SimpleITK ${PYTHON_LIBRARIES} ${ITK_LIBRARIES} SimpleITK)
endif()

# Find Java
if ( WRAP_JAVA )
  find_package ( Java REQUIRED )
  find_package ( JNI REQUIRED )
  include_directories ( ${JAVA_INCLUDE_PATH} ${JNI_INCLUDE_DIRS} )
  
  set(CMAKE_SWIG_FLAGS -package "simpleitk")
  SWIG_add_module ( SimpleITKJava java SimpleITK.i SimpleITKJAVA_wrap.cxx )

  SWIG_link_libraries ( SimpleITKJava ${JAVA_LIBRARIES} ${ITK_LIBRARIES} SimpleITK)
  
  # Configure the library loader file
  CONFIGURE_FILE(${SimpleITK_SOURCE_DIR}/Wrapping/LoadSimpleITK.java.in
    ${SimpleITK_BINARY_DIR}/Wrapping/LoadSimpleITK.java)
  
  # Make sure the simpleitk directory exists
  if ( NOT IS_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/simpleitk )
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/simpleitk)
  endif()
  
  # Add custom command and target to compile the generated files and put them in a jar file
  add_custom_target(simpleitk_jar ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/SimpleITK.java)
  add_custom_command(
    TARGET simpleitk_jar
    COMMAND javac ${CMAKE_CURRENT_BINARY_DIR}/*.java
    COMMAND mv ${CMAKE_CURRENT_BINARY_DIR}/*.class ${CMAKE_CURRENT_BINARY_DIR}/simpleitk
    COMMAND jar cf ${CMAKE_CURRENT_BINARY_DIR}/simpleitk.jar -C ${CMAKE_CURRENT_BINARY_DIR} simpleitk
    )
  
  
  # Get the location of the extension directory
  string(REGEX REPLACE "include"  "jre/lib/ext" JAVA_EXTENSION_DIR ${JAVA_INCLUDE_PATH} )
  
  # Add the install target
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/simpleitk.jar DESTINATION ${JAVA_EXTENSION_DIR})
  
  
endif()







