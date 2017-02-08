cmake_minimum_required ( VERSION 2.8.1 FATAL_ERROR )

project( SimpleITK_Java )

include(../../CMake/sitkProjectLanguageCommon.cmake NO_POLICY_SCOPE)

find_package ( Java REQUIRED )
find_package ( JNI REQUIRED )
include_directories ( ${SimpleITK_INCLUDE_DIRS} )

set(JAR_FILE "simpleitk-${SimpleITK_VERSION}.jar")
set(JAVADOC_FILE "simpleitk-javadoc-${SimpleITK_VERSION}.jar")
set(JAVA_SOURCE_FILE "simpleitk-source-${SimpleITK_VERSION}.jar")

set_source_files_properties ( SimpleITK.i PROPERTIES CPLUSPLUS ON )

FIND_PROGRAM(Java_JAVADOC_EXECUTABLE
  NAMES javadoc
  HINTS ${_JAVA_HINTS}
  PATHS ${_JAVA_PATHS}
  )

# Make sure the nested directory structure exists
set(JAVA_SOURCE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/)
set(JAVA_BINARY_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build)
file(MAKE_DIRECTORY ${JAVA_SOURCE_DIRECTORY})
file(MAKE_DIRECTORY ${JAVA_BINARY_DIRECTORY})

# Nicely write the bridge code in org/itk/simple
set(CMAKE_SWIG_OUTDIR ${JAVA_SOURCE_DIRECTORY}/org/itk/simple/)
set(CMAKE_SWIG_FLAGS -I${CMAKE_CURRENT_SOURCE_DIR} -package "org.itk.simple" ${CMAKE_SWIG_GLOBAL_FLAGS})
set(SWIG_MODULE_SimpleITKJava_EXTRA_DEPS ${SWIG_EXTRA_DEPS} ${CMAKE_CURRENT_SOURCE_DIR}/Java.i ${CMAKE_CURRENT_SOURCE_DIR}/JavaDoc.i)
SWIG_add_module ( SimpleITKJava java SimpleITK.i )
target_link_libraries( ${SWIG_MODULE_SimpleITKJava_TARGET_NAME} ${SimpleITK_LIBRARIES})
target_include_directories( ${SWIG_MODULE_SimpleITKJava_TARGET_NAME}
  PRIVATE
     ${JAVA_INCLUDE_PATH} ${JNI_INCLUDE_DIRS} )
set_source_files_properties(${swig_generated_file_fullname} PROPERTIES COMPILE_FLAGS "-w")
sitk_strip_target( ${SWIG_MODULE_SimpleITKJava_TARGET_NAME} )

set(JAVA_SOURCE_CODE "${JAVA_SOURCE_DIRECTORY}/org/itk/simple/*.java")

# Oracle Java 1.8 javadoc treats linting errors as build errors by default
# so linting should be opt-in for this version. OpenJDK is not as
# consistent with the 1.8.0 versions, so we execute at look for a
# invalid flag error.
execute_process(COMMAND "${Java_JAVADOC_EXECUTABLE}" "-Xdoclint:none" ERROR_VARIABLE err OUTPUT_VARIABLE err)
string(REGEX MATCH "javadoc.*invalid flag" invalid_flag_match "${err}")
if(invalid_flag_match STREQUAL "")
  mark_as_advanced( Java_JAVADOC_LINTING )
  option( Java_JAVADOC_LINTING "Enable javadoc linting for Java 1.8" OFF )
  if( Java_JAVADOC_LINTING )
    set( Java_JAVADOC_LINTING_CMD "-Xdoclint:all" )
  else()
    set( Java_JAVADOC_LINTING_CMD "-Xdoclint:none" )
  endif()
endif()

# Add custom command and target to compile the generated files and put them in a jar file
# Make sure the commands depend on the output library from SWIG
add_custom_command(
  OUTPUT ${JAR_FILE}
  COMMENT "Creating jar file..."
  COMMAND ${Java_JAVAC_EXECUTABLE} -d ${JAVA_BINARY_DIRECTORY} ${JAVA_SOURCE_CODE}
  COMMAND ${Java_JAR_EXECUTABLE} cf ${CMAKE_CURRENT_BINARY_DIR}/${JAR_FILE} -C ${JAVA_BINARY_DIRECTORY} org
  COMMAND ${Java_JAVADOC_EXECUTABLE} ${Java_JAVADOC_LINTING_CMD} -quiet -d ${JAVA_BINARY_DIRECTORY}/javadoc -sourcepath ${JAVA_SOURCE_DIRECTORY} org.itk.simple
  COMMAND ${Java_JAR_EXECUTABLE} cf ${CMAKE_CURRENT_BINARY_DIR}/${JAVADOC_FILE} -C ${JAVA_BINARY_DIRECTORY}/javadoc org
  COMMAND ${Java_JAR_EXECUTABLE} cf ${CMAKE_CURRENT_BINARY_DIR}/${JAVA_SOURCE_FILE} org
  DEPENDS ${SWIG_MODULE_SimpleITKJava_TARGET_NAME}
  )

# Add target for org.itk.simple.jar
add_custom_target(org_itk_simple_jar ALL DEPENDS ${JAR_FILE})


# Get the location of the extension directory
string(REGEX REPLACE "include"  "jre/lib/ext" JAVA_EXTENSION_DIR ${JAVA_INCLUDE_PATH} )

# TODO: add new target to install simpleitk java
# Add the install target
# install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${JAR_FILE} DESTINATION ${JAVA_EXTENSION_DIR})

add_subdirectory(dist)
