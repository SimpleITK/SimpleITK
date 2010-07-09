

option ( WRAP_LUA "Wrap Lua" ON )
option ( WRAP_PYTHON "Wrap Python" OFF )

if ( WRAP_LUA OR WRAP_PYTHON )
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
  target_link_libraries ( SimpleITKLua SimpleITK SimpleITKLuaModule ${LUA_LIBRARIES} ${ITK_LIBRARIES} )

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
