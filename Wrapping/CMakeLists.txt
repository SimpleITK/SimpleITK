

option ( WRAP_LUA "Wrap Lua" ON )
option ( WRAP_PYTHON "Wrap Python" OFF )
option ( WRAP_JAVA "Wrap Java" OFF )
option ( WRAP_TCL "Wrap Tcl" OFF )
option ( WRAP_CSHARP "Wrap C#" OFF )
option ( WRAP_R "Wrap R" OFF )

set(CMAKE_MODULE_PATH ${SimpleITK_SOURCE_DIR}/Wrapping)

if ( WRAP_LUA OR WRAP_PYTHON OR WRAP_JAVA OR WRAP_CSHARP OR WRAP_TCL OR WRAP_R )
  find_package ( SWIG REQUIRED )
  include ( ${SWIG_USE_FILE} )
  set_source_files_properties ( SimpleITK.i PROPERTIES CPLUSPLUS ON )
  file ( GLOB SWIG_HEADERS ${SimpleITK_SOURCE_DIR}/Code/*/*.h)

  set ( DEPENDANT_GENERATED_HEADERS "" )
  foreach ( filter ${GENERATED_FILTER_LIST} )
    set ( DEPENDANT_GENERATED_HEADERS ${DEPENDANT_GENERATED_HEADERS} ${SimpleITK_BINARY_DIR}/Code/BasicFilters/sitk${filter}ImageFilter.h )
  endforeach()


  set ( SWIG_HEADERS ${SWIG_HEADERS} ${SimpleITK_BINARY_DIR}/Code/BasicFilters/SimpleITKBasicFiltersGeneratedHeaders.i 
    ${SimpleITK_BINARY_DIR}/Code/BasicFilters/SimpleITKBasicFiltersGeneratedHeaders.h
    ${DEPENDANT_GENERATED_HEADERS} )

  include_directories ( ${SimpleITK_SOURCE_DIR}/Code/Common ${SimpleITK_SOURCE_DIR}/Code/BasicFilters ${SimpleITK_SOURCE_DIR}/Code/IO )

  set ( CMAKE_SWIG_FLAGS "" )
  set ( SWIG_MODULE_SimpleITK_EXTRA_DEPS ${SWIG_HEADERS} )

endif()


# Find lua
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
  set(CMAKE_SWIG_FLAGS "")
  SWIG_module_initialize ( SimpleITKLua lua )
  SWIG_add_source_to_module ( SimpleITKLua swig_generated_source SimpleITK.i ${SWIG_HEADERS} )

  add_executable ( SimpleITKLua SimpleITKLuaMain.cxx SimpleITKLUA_wrap.cxx )
  target_link_libraries ( SimpleITKLua ${SimpleITK_LIBRARIES} ${LUA_LIB} ${ITK_LIBRARIES} )

  find_program (SimpleITKLua NAMES SimpleITKLua SimpleITKLua.exe PATHS ${EXECUTABLE_OUTPUT_PATH} ${EXECUTABLE_OUTPUT_PATH}/Release ${EXECUTABLE_OUTPUT_PATH}/Debug NO_DEFAULT_PATH NO_SYSTEM_ENVIRONMENT_PATH)

  if ( UNIX )
    target_link_libraries ( SimpleITKLua curses )
  endif()

endif()

# Find Python
if ( WRAP_PYTHON )
  find_package ( PythonLibs REQUIRED )
  find_package ( PythonInterp REQUIRED )
  include_directories ( ${PYTHON_INCLUDE_DIR} )

  # Run swig
  set(CMAKE_SWIG_FLAGS "")
  SWIG_add_module ( SimpleITK python SimpleITK.i SimpleITKPYTHON_wrap.cxx )
  SWIG_link_libraries ( SimpleITK ${SimpleITK_LIBRARIES} ${PYTHON_LIBRARIES} ${ITK_LIBRARIES})

endif()

# Find Java
if ( WRAP_JAVA )
  find_package ( Java REQUIRED )
  find_package ( JNI REQUIRED )
  include_directories ( ${JAVA_INCLUDE_PATH} ${JNI_INCLUDE_DIRS} )
  
  set(CMAKE_SWIG_FLAGS -package "org.itk.simple")
  SWIG_add_module ( SimpleITKJava java SimpleITK.i SimpleITKJAVA_wrap.cxx )
  SWIG_link_libraries(SimpleITKJava ${SimpleITK_LIBRARIES})

  # Make sure the nested directory structure exists
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/org/itk/simple)
  
  # Add custom command and target to compile the generated files and put them in a jar file
  # Make sure the commands depend on the output library from SWIG
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/SimpleITK.class
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/SimpleITK.java
    COMMAND ${Java_JAVAC_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/*.java
    COMMENT "Compiling java files..."
    DEPENDS ${SWIG_MODULE_SimpleITK_REAL_NAME}
  )
  
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/org.itk.simple.jar
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/SimpleITK.class
    COMMENT "Creating jar file..."
    COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/*.class ${CMAKE_CURRENT_BINARY_DIR}/org/itk/simple
    COMMAND jar cf ${CMAKE_CURRENT_BINARY_DIR}/org.itk.simple.jar -C ${CMAKE_CURRENT_BINARY_DIR} org
    DEPENDS ${SWIG_MODULE_SimpleITK_REAL_NAME}
    )

  add_custom_target(org_itk_simple_jar ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/org.itk.simple.jar)
  
  # Get the location of the extension directory
  string(REGEX REPLACE "include"  "jre/lib/ext" JAVA_EXTENSION_DIR ${JAVA_INCLUDE_PATH} )
  
  # Add the install target
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/org.itk.simple.jar DESTINATION ${JAVA_EXTENSION_DIR})
  
endif()

# Find C#
if ( WRAP_CSHARP )

  # Find C#
  set( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/Wrapping/CSharpModules )
  find_package( CSharp REQUIRED )
  include( ${CSHARP_USE_FILE} )

  # Run swig
  set( CMAKE_SWIG_FLAGS "-dllimport \"SimpleITKCSharpNative\" -namespace \"itk.simple\"" )
  set( CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR}/SwigCSharp )
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
  include_directories ( ${TCL_INCLUDE_DIR} )

  # Run swig
  set(CMAKE_SWIG_FLAGS "-nosafe")
  SWIG_add_module ( SimpleITKTcl tcl SimpleITK.i SimpleITKTCL_wrap.cxx )
  SWIG_link_libraries ( SimpleITKTcl ${SimpleITK_LIBRARIES} ${TCL_LIBRARY} ${ITK_LIBRARIES})
  add_executable ( SimpleITKTclsh SimpleITKTCL_wrap.cxx )
  target_link_libraries ( SimpleITKTclsh ${SimpleITK_LIBRARIES} ${TCL_LIBRARY} ${ITK_LIBRARIES})

endif()

# Find R
if ( WRAP_R )
  find_package ( R REQUIRED )
  include_directories ( ${R_INCLUDE_DIR} )

  # Run swig
  set(CMAKE_SWIG_FLAGS "")
  SWIG_add_module ( SimpleITK r SimpleITK.i SimpleITKR_wrap.cxx )
  SWIG_link_libraries ( SimpleITK ${SimpleITK_LIBRARIES} ${R_LIBRARIES} ${ITK_LIBRARIES})

endif()

