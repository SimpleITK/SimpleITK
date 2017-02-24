
#
# JAVA Packaging
#
set(_files "")
list( APPEND _files
  ${SimpleITK_DOC_FILES}
  ${SimpleITK_Java_BINARY_DIR}/${JAR_FILE}
  ${SimpleITK_Java_BINARY_DIR}/${JAVA_SOURCE_FILE}
  ${SimpleITK_Java_BINARY_DIR}/${JAVADOC_FILE}
  )

if(NOT DEFINED SimpleITK_JAVA_ARCH)
  if(MSVC)
    if (CMAKE_CL_64)
      set(SimpleITK_JAVA_ARCH "win64")
    else()
      set(SimpleITK_JAVA_ARCH "win32")
    endif()
  elseif(APPLE)
    # assemble macosx-OSX_DEPLOYMENT_TARGET-OSX_ARCHITECTURE
    set(SimpleITK_JAVA_ARCH "macosx")
    if(CMAKE_OSX_DEPLOYMENT_TARGET)
      set(SimpleITK_JAVA_ARCH "${SimpleITK_JAVA_ARCH}-${CMAKE_OSX_DEPLOYMENT_TARGET}")
    endif()
    if(CMAKE_OSX_ARCHITECTURES MATCHES "i386" AND CMAKE_OSX_ARCHITECTURES MATCHES "x86_64")
      if (CMAKE_OSX_ARCHITECTURES MATCHES "ppc")
        set(SimpleITK_JAVA_ARCH "${SimpleITK_JAVA_ARCH}-universal")
      else()
        set(SimpleITK_JAVA_ARCH "${SimpleITK_JAVA_ARCH}-intel")
        set(_OSX_ARCHITECTURES "intel")
      endif()
    elseif(CMAKE_OSX_ARCHITECTURES)
      string(REPLACE ";" "_" _OSX_ARCHITECTURES "${CMAKE_OSX_ARCHITECTURES}")
      set(SimpleITK_JAVA_ARCH "${SimpleITK_JAVA_ARCH}-${_OSX_ARCHITECTURES}")
    else()
      set(SimpleITK_JAVA_ARCH "${SimpleITK_JAVA_ARCH}-unknown")
    endif()
  else()
    set(SimpleITK_JAVA_ARCH "unknown")
  endif()
endif()

set( JAVA_PACKAGE_STAGE_DIR "SimpleITK-${SimpleITK_VERSION}-Java-${SimpleITK_JAVA_ARCH}")

add_custom_target( dist.Java
  COMMENT "Creating Java package ${JAVA_PACKAGE_STAGE_DIR}.zip"
  DEPENDS org_itk_simple_jar
  )

add_custom_command( TARGET dist.Java
  PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E remove_directory "${JAVA_PACKAGE_STAGE_DIR}"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${JAVA_PACKAGE_STAGE_DIR}"
  COMMENT "Creating Java staging directory..."
  )

foreach(_f ${_files})
  get_filename_component(_f_name ${_f} NAME )
  add_custom_command( TARGET dist.Java
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${_f}" "${JAVA_PACKAGE_STAGE_DIR}/${_f_name}"
    COMMENT "Copying ${_f_name} to Java stage..."
    )
endforeach()

add_custom_command( TARGET dist.Java
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:${SWIG_MODULE_SimpleITKJava_TARGET_NAME}>" "${JAVA_PACKAGE_STAGE_DIR}"
  COMMENT "Copying $<TARGET_FILE:${SWIG_MODULE_SimpleITKJava_TARGET_NAME}> to Java stage..."
  COMMAND ${Java_JAR_EXECUTABLE} cfM "${JAVA_PACKAGE_STAGE_DIR}.zip" "${JAVA_PACKAGE_STAGE_DIR}"
  COMMENT "Packaging JAVA distribution..."
  )

add_dependencies( dist dist.Java )
