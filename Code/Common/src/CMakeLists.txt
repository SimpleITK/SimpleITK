set ( SimpleITKCommonSource
  sitkImage.cxx
  sitkImageExplicit.cxx
  sitkProcessObject.cxx
  sitkTransform.cxx
  sitkAffineTransform.cxx
  sitkBSplineTransform.cxx
  sitkDisplacementFieldTransform.cxx
  sitkEuler2DTransform.cxx
  sitkEuler3DTransform.cxx
  sitkScaleTransform.cxx
  sitkScaleSkewVersor3DTransform.cxx
  sitkScaleVersor3DTransform.cxx
  sitkSimilarity2DTransform.cxx
  sitkSimilarity3DTransform.cxx
  sitkTranslationTransform.cxx
  sitkVersorTransform.cxx
  sitkVersorRigid3DTransform.cxx
  sitkCommand.cxx
  sitkFunctionCommand.cxx
  sitkPixelIDValues.cxx
  sitkExceptionObject.cxx
  sitkKernel.cxx
  sitkEvent.cxx
  sitkInterpolator.cxx
  sitkVersion.cxx
  ../include/Ancillary/hl_md5.cxx
  ../include/Ancillary/hl_sha1.cxx
  )

set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include(${ITK_USE_FILE})

add_library ( SimpleITKCommon ${SimpleITKCommonSource} ${SimpleITKAncillarySource} )
target_link_libraries ( SimpleITKCommon ${ITK_LIBRARIES} )
if (SITK_EXPLICIT_INSTANTIATION)
  target_link_libraries ( SimpleITKCommon SimpleITKExplicit )
endif()
set_target_properties( SimpleITKCommon PROPERTIES SKIP_BUILD_RPATH TRUE )

sitk_install_exported_target( SimpleITKCommon )

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
