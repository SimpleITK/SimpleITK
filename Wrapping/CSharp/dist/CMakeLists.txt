
#
# CSharp Packaging
#
if( Java_JAR_EXECUTABLE )

  set(_files "")
  list( APPEND _files
    ${SimpleITK_DOC_FILES}
    "${CSHARP_BINARY_DIRECTORY}/SimpleITKCSharpManaged.dll"
    )

  if(NOT DEFINED SimpleITK_CSHARP_ARCH)
    if(MSVC)
      if (CMAKE_CL_64)
        set(SimpleITK_CSHARP_ARCH "win64")
      else()
        set(SimpleITK_CSHARP_ARCH "win32")
      endif()
    else()
      set(SimpleITK_CSHARP_ARCH "unknown")
    endif()

    if(CSHARP_PLATFORM)
      set(SimpleITK_CSHARP_ARCH "${SimpleITK_CSHARP_ARCH}-${CSHARP_PLATFORM}")
    endif()
  endif()

  set( CSHARP_PACKAGE_STAGE_DIR "SimpleITK-${SimpleITK_VERSION}-CSharp-${SimpleITK_CSHARP_ARCH}")

  add_custom_target( dist.CSharp
    COMMENT "Creating CSharp package ${CSHARP_PACKAGE_STAGE_DIR}.zip"
    DEPENDS SimpleITKCSharpManaged
    )

  add_custom_command( TARGET dist.CSharp
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CSHARP_PACKAGE_STAGE_DIR}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CSHARP_PACKAGE_STAGE_DIR}"
    COMMENT "Creating CSharp staging directory..."
    )

  foreach(_f ${_files})
    get_filename_component(_f_name ${_f} NAME )
    add_custom_command( TARGET dist.CSharp
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different "${_f}" "${CSHARP_PACKAGE_STAGE_DIR}/${_f_name}"
      COMMENT "Copying ${_f_name} to CSharp stage..."
    )
  endforeach()

  add_custom_command( TARGET dist.CSharp
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:${SWIG_MODULE_SimpleITKCSharpNative_TARGET_NAME}>" "${CSHARP_PACKAGE_STAGE_DIR}"
    COMMENT "Copying $<TARGET_FILE:${SWIG_MODULE_SimpleITKCSharpNative_TARGET_NAME}> to CSharp stage..."
#    COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:SimpleITKCSharpManaged>" "${CSHARP_PACKAGE_STAGE_DIR}"
#    COMMENT "Copying $<TARGET_FILE:${SimpleITKCSharpManaged}> to CSharp stage..."

    SimpleITKCSharpManaged
    COMMAND ${Java_JAR_EXECUTABLE} cfM "${CSHARP_PACKAGE_STAGE_DIR}.zip" "${CSHARP_PACKAGE_STAGE_DIR}"
    COMMENT "Packaging CSHARP distribution..."
    )

  add_dependencies( dist dist.CSharp )

endif()
