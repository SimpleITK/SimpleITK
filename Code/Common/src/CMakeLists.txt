set ( SimpleITKCommonSource
  sitkImage.cxx
  sitkImageExplicit.cxx
  sitkProcessObject.cxx
  sitkTransform.cxx
  sitkCompositeTransform.cxx
  sitkAffineTransform.cxx
  sitkBSplineTransform.cxx
  sitkDisplacementFieldTransform.cxx
  sitkEuler2DTransform.cxx
  sitkEuler3DTransform.cxx
  sitkScaleTransform.cxx
  sitkScaleSkewVersor3DTransform.cxx
  sitkComposeScaleSkewVersor3DTransform.cxx
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
  sitkLogger.cxx
  sitkInterpolator.cxx
  sitkVersion.cxx
  sitkObjectOwnedBase.cxx
  ../include/Ancillary/hl_sha1.cxx
  )

set(use_itk_modules ITKCommon ITKImageCompose ITKImageIntensity
  ITKLabelMap ITKTransform ITKIOTransformBase ITKDisplacementField )
find_package(ITK COMPONENTS ${use_itk_modules}  REQUIRED)

add_library ( SimpleITKCommon ${SimpleITKCommonSource} ${SimpleITKAncillarySource} )
sitk_target_use_itk (SimpleITKCommon PRIVATE ${use_itk_modules} )
if (SimpleITK_EXPLICIT_INSTANTIATION)
  target_link_libraries ( SimpleITKCommon PRIVATE SimpleITKExplicit )
endif()
target_include_directories ( SimpleITKCommon
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/Common/include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/Code/Common/include>
    $<INSTALL_INTERFACE:${SimpleITK_INSTALL_INCLUDE_DIR}> )
target_compile_options( SimpleITKCommon
  PUBLIC
    ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS} )
target_compile_features( SimpleITKCommon PUBLIC cxx_std_11 )


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
