
# FindR is stored in the current source path, it needs to be included.
set(CMAKE_MODULE_PATH "${SimpleITK_SOURCE_DIR}/Wrapping;${PROJECT_SOURCE_DIR}/Wrapping/CSharpModules" )


macro(check_PIC_flag Language)
  if ( UNIX )
    if ( NOT ${CMAKE_CXX_FLAGS} MATCHES "-fPIC")
      message ( WARNING "${Language} wrapping requires CMAKE_CXX_FLAGS (or equivalent) to include -fPIC and ITK built with this flag" )
    endif()
  endif()
endmacro()


#
# Setup the option for each laguage
#
option ( WRAP_LUA "Wrap Lua" ON )

find_package ( PythonLibs )
find_package ( PythonInterp )
if ( ${PYTHONLIBS_FOUND} AND ${PYTHONINTERP_FOUND} )
  set( WRAP_PYTHON_DEFAULT ON )
else ( ${PYTHONLIBS_FOUND} AND ${PYTHONINTERP_FOUND} )
  set( WRAP_PYTHON_DEFAULT OFF )
endif ( ${PYTHONLIBS_FOUND} AND ${PYTHONINTERP_FOUND} )
check_PIC_flag ( Python )
option( WRAP_PYTHON "Wrap Python" ${WRAP_PYTHON_DEFAULT} )

find_package ( Java COMPONENTS Development Runtime)
find_package ( JNI  )
if ( ${JAVA_FOUND} AND ${JNI_FOUND} )
  set( WRAP_JAVA_DEFAULT ON )
else ( ${JAVA_FOUND} AND ${JNI_FOUND} )
  set( WRAP_JAVA_DEFAULT OFF )
endif ( ${JAVA_FOUND} AND ${JNI_FOUND} )
check_PIC_flag ( Java )
option ( WRAP_JAVA "Wrap Java" ${WRAP_JAVA_DEFAULT} )

find_package ( TCL )
if ( ${TCL_FOUND} )
  set ( WRAP_TCL_DEFAULT ON )
else ( ${TCL_FOUND} )
  set ( WRAP_TCL_DEFAULT OFF )
endif ( ${TCL_FOUND} )
option ( WRAP_TCL "Wrap Tcl" ${WRAP_TCL_DEFAULT} )

find_package ( Ruby )
if ( ${RUBY_FOUND} )
  set ( WRAP_RUBY_DEFAULT ON )
else ( ${RUBY_FOUND} )
  set ( WRAP_RUBY_DEFAULT OFF )
endif ( ${RUBY_FOUND} )
check_PIC_flag ( Ruby )
option ( WRAP_RUBY "Wrap Ruby" ${WRAP_RUBY_DEFAULT} )

#
# Below here are the 2nd tier languages they are not enable automatically if detected
#

# TODO FindCSharp does not conform to the expected behavior:
# http://www.cmake.org/cmake/help/cmake-2-8-docs.html#command:find_package
# specifically CSHARP_FOUND is not defined, and the script fails on non-windows systems
if( WIN32 )
  option ( WRAP_CSHARP "Wrap C#" OFF )
  mark_as_advanced( WRAP_CSHARP )
endif( WIN32 )

# TODO FindR does not conform to the expected behavior:
# http://www.cmake.org/cmake/help/cmake-2-8-docs.html#command:find_package
# specifically R_FOUND is not defined. Additionally, the defined variables are not marked as advanced.
option ( WRAP_R "Wrap R" OFF )
mark_as_advanced( WRAP_R )


#
# General SWIG configuration
#
if ( WRAP_LUA OR WRAP_PYTHON OR WRAP_JAVA OR WRAP_CSHARP OR WRAP_TCL OR WRAP_R OR WRAP_RUBY )
  find_package ( SWIG 2 REQUIRED )
  include ( "UseSWIGLocal.cmake" )
  set_source_files_properties ( SimpleITK.i PROPERTIES CPLUSPLUS ON )
  file ( GLOB SWIG_HEADERS ${SimpleITK_SOURCE_DIR}/Code/*/*.h)

  set ( DEPENDANT_GENERATED_HEADERS "" )
  foreach ( filter ${GENERATED_FILTER_LIST} )
    set ( DEPENDANT_GENERATED_HEADERS ${DEPENDANT_GENERATED_HEADERS} ${SimpleITK_BINARY_DIR}/Code/BasicFilters/include/sitk${filter}ImageFilter.h )
  endforeach()


  set ( SWIG_HEADERS ${SWIG_HEADERS} ${SimpleITK_BINARY_DIR}/Code/BasicFilters/include/SimpleITKBasicFiltersGeneratedHeaders.i
    ${SimpleITK_BINARY_DIR}/Code/BasicFilters/include/SimpleITKBasicFiltersGeneratedHeaders.h
    ${CMAKE_CURRENT_SOURCE_DIR}/CSharp.i
    ${CMAKE_CURRENT_SOURCE_DIR}/CSharpTypemapHelper.i
    ${CMAKE_CURRENT_SOURCE_DIR}/Java.i
    ${CMAKE_CURRENT_SOURCE_DIR}/Lua.i
    ${CMAKE_CURRENT_SOURCE_DIR}/Python.i
    ${CMAKE_CURRENT_SOURCE_DIR}/Tcl.i
    ${DEPENDANT_GENERATED_HEADERS} )



  # check if uint64_t is the same as unsigned long
  try_compile(SITK_ULONG_SAME_AS_UINT64
    ${SimpleITK_BINARY_DIR}/CMakeTmp
    ${SimpleITK_SOURCE_DIR}/CMake/same_uint64_ulong.cxx )

  # when "-DSWIGWORDSIZE64" is defined SWIG used unsigned long for uint64_t types
  if(${SITK_ULONG_SAME_AS_UINT64} )
    set ( CMAKE_SWIG_GLOBAL_FLAGS "-DSWIGWORDSIZE64" )
  endif()

  set ( SWIG_MODULE_SimpleITK_EXTRA_DEPS ${SWIG_HEADERS} )

endif()

#
# lua SWIG configuration
#
if ( WRAP_LUA )
  option ( USE_SYSTEM_LUA "Use a system provided lua" OFF )

  if ( USE_SYSTEM_LUA )
    find_package ( Lua51 REQUIRED )
    include_directories ( ${LUA_INCLUDE_DIR} )
    set ( LUA_LIB ${LUA_LIBRARIES} )
  else()
    set ( LUA_LIB lua5 )
    include_directories ( ${SimpleITK_SOURCE_DIR}/Utilities/lua-5.1.4/src )
  endif()


  # Run swig
  set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_GLOBAL_FLAGS})
  set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
  set(SWIG_MODULE_SimpleITKLua_EXTRA_DEPS SimpleITKCommon SimpleITKBasicFilters SimpleITKIO ${SWIG_HEADERS})
  SWIG_module_initialize ( SimpleITKLua lua )
  SWIG_add_source_to_module ( SimpleITKLua swig_generated_source SimpleITK.i ${SWIG_HEADERS} )
  set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/SimpleITKLUA_wrap.cxx COMPILE_FLAGS "-w")

  add_executable ( SimpleITKLua SimpleITKLuaMain.cxx SimpleITKLUA_wrap.cxx )
  target_link_libraries ( SimpleITKLua ${SimpleITK_LIBRARIES} ${LUA_LIB} ${ITK_LIBRARIES} )

  if ( UNIX )
    target_link_libraries ( SimpleITKLua curses )
  endif()

endif()

#
# python SWIG configuration
#
if ( WRAP_PYTHON )
  find_package ( PythonLibs REQUIRED )
  find_package ( PythonInterp REQUIRED )
  include_directories ( ${PYTHON_INCLUDE_DIR} )

  # Run swig
  set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_GLOBAL_FLAGS})
  set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
  set(SWIG_MODULE_SimpleITK_EXTRA_DEPS SimpleITKCommon SimpleITKBasicFilters SimpleITKIO ${SWIG_HEADERS})
  SWIG_add_module ( SimpleITK python SimpleITK.i SimpleITKPYTHON_wrap.cxx )
  SWIG_link_libraries ( SimpleITK ${SimpleITK_LIBRARIES} ${PYTHON_LIBRARIES} ${ITK_LIBRARIES})
  set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/SimpleITKPYTHON_wrap.cxx COMPILE_FLAGS "-w")

endif()

#
# ruby SWIG configuration
#
if ( WRAP_RUBY )
  find_package ( Ruby REQUIRED )
  include_directories ( ${RUBY_INCLUDE_DIRS} )

  # Run swig
  set(CMAKE_SWIG_FLAGS -autorename -module simpleitk ${CMAKE_SWIG_GLOBAL_FLAGS})
  set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
  set(SWIG_MODULE_simpleitk_EXTRA_DEPS SimpleITKCommon SimpleITKBasicFilters SimpleITKIO ${SWIG_HEADERS})
  SWIG_MODULE_INITIALIZE ( SimpleITK ruby )

  SWIG_add_module ( simpleitk ruby SimpleITK.i SimpleITKRUBY_wrap.cxx )
  SWIG_link_libraries ( simpleitk ${SimpleITK_LIBRARIES} ${RUBY_LIBRARY} ${ITK_LIBRARIES})
  set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/SimpleITKRUBY_wrap.cxx COMPILE_FLAGS "-w")

endif()


#
# JAVA SWIG configuration
#
if ( WRAP_JAVA )
  find_package ( Java REQUIRED )
  find_package ( JNI REQUIRED )
  include_directories ( ${JAVA_INCLUDE_PATH} ${JNI_INCLUDE_DIRS} )

  # Make sure the nested directory structure exists
  set(JAVA_SOURCE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/org/itk/simple)
  set(JAVA_BINARY_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build)
  file(MAKE_DIRECTORY ${JAVA_SOURCE_DIRECTORY})
  file(MAKE_DIRECTORY ${JAVA_BINARY_DIRECTORY})

  # Nicely write the bridge code in org/itk/simple
  set(CMAKE_SWIG_OUTDIR ${JAVA_SOURCE_DIRECTORY})
  set(CMAKE_SWIG_FLAGS -package "org.itk.simple" ${CMAKE_SWIG_GLOBAL_FLAGS})
  set(SWIG_MODULE_SimpleITKJava_EXTRA_DEPS SimpleITKCommon SimpleITKBasicFilters SimpleITKIO)
  SWIG_add_module ( SimpleITKJava java SimpleITK.i SimpleITKJAVA_wrap.cxx)
  SWIG_link_libraries(SimpleITKJava ${SimpleITK_LIBRARIES})
  set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/SimpleITKJAVA_wrap.cxx COMPILE_FLAGS "-w")

  # Add target for org.itk.simple.jar
  add_custom_target(org_itk_simple_jar ALL DEPENDS org.itk.simple.jar)

  # Add custom command and target to compile the generated files and put them in a jar file
  # Make sure the commands depend on the output library from SWIG
  add_custom_command(
    OUTPUT org.itk.simple.jar
    COMMENT "Creating jar file..."
    COMMAND ${Java_JAVAC_EXECUTABLE} -d ${JAVA_BINARY_DIRECTORY} ${JAVA_SOURCE_DIRECTORY}/*.java
    COMMAND ${Java_JAR_EXECUTABLE} cf ${CMAKE_CURRENT_BINARY_DIR}/org.itk.simple.jar -C ${JAVA_BINARY_DIRECTORY} org
    DEPENDS ${SWIG_MODULE_SimpleITK_REAL_NAME} SimpleITKJava SimpleITKCommon SimpleITKBasicFilters SimpleITKIO
    )

  # Get the location of the extension directory
  string(REGEX REPLACE "include"  "jre/lib/ext" JAVA_EXTENSION_DIR ${JAVA_INCLUDE_PATH} )

  # Add the install target
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/org.itk.simple.jar DESTINATION ${JAVA_EXTENSION_DIR})

endif()


#
# C# SWIG configuration
#
if ( WRAP_CSHARP )

  # Find C#
  find_package( CSharp REQUIRED )
  include( ${CSHARP_USE_FILE} )

  # Run swig
  set( CMAKE_SWIG_FLAGS "-dllimport \"SimpleITKCSharpNative\" -namespace \"itk.simple\"" ${CMAKE_SWIG_GLOBAL_FLAGS})
  set( CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR}/SwigCSharp )
  set(SWIG_MODULE_SimpleITKCSharpNative_EXTRA_DEPS SimpleITKCommon SimpleITKBasicFilters SimpleITKIO ${SWIG_HEADERS})
  swig_add_module( SimpleITKCSharpNative csharp SimpleITK.i )
  swig_link_libraries( SimpleITKCSharpNative ${ITK_LIBRARIES} SimpleITK )
  set_target_properties( SimpleITKCSharpNative PROPERTIES PREFIX "../" )

  # Create AssemblyInfo.cs
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/AssemblyInfo.cs.in
    ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs
    @ONLY
  )

  # Add managed wrapper
  csharp_add_library(
    SimpleITKCSharpManaged
    ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs
    ${CMAKE_CURRENT_BINARY_DIR}/SwigCSharp/*.cs
  )

endif()

# Find Tcl
if ( WRAP_TCL )
  find_package ( TCL REQUIRED )
  include_directories ( ${TCL_INCLUDE_PATH} )

  # Run swig
  set(CMAKE_SWIG_FLAGS "-nosafe" ${CMAKE_SWIG_GLOBAL_FLAGS})
  set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
  set(SWIG_MODULE_SimpleITKTcl_EXTRA_DEPS SimpleITKCommon SimpleITKBasicFilters SimpleITKIO ${SWIG_HEADERS})
  SWIG_add_module ( SimpleITKTcl tcl SimpleITK.i SimpleITKTCL_wrap.cxx )
  SWIG_link_libraries ( SimpleITKTcl ${SimpleITK_LIBRARIES} ${TCL_LIBRARY} ${ITK_LIBRARIES})
  set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/SimpleITKTCL_wrap.cxx COMPILE_FLAGS "-w")
  add_executable ( SimpleITKTclsh SimpleITKTCL_wrap.cxx )
  target_link_libraries ( SimpleITKTclsh ${SimpleITK_LIBRARIES} ${TCL_LIBRARY} ${ITK_LIBRARIES})

endif()

# Find R
if ( WRAP_R )
  find_package ( R REQUIRED )
  include_directories ( ${R_INCLUDE_DIR} )

  # Run swig
  set(CMAKE_SWIG_FLAGS "")
  set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
  set(SWIG_MODULE_SimpleITK_EXTRA_DEPS SimpleITKCommon SimpleITKBasicFilters SimpleITKIO ${SWIG_HEADERS})
  SWIG_add_module ( SimpleITK r SimpleITK.i SimpleITKR_wrap.cxx )
  SWIG_link_libraries ( SimpleITK ${SimpleITK_LIBRARIES} ${R_LIBRARIES} ${ITK_LIBRARIES})

endif()

