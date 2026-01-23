# CMake option variable are prefixes with the project name "SimpleITK"
# while C++ preprocess defines only have SITK. These variable need the
# prefix translation.
set(SITK_INT64_PIXELIDS ${SimpleITK_INT64_PIXELIDS})
set(SITK_EXPLICIT_INSTANTIATION ${SimpleITK_EXPLICIT_INSTANTIATION})
set(SITK_USE_ELASTIX ${SimpleITK_USE_ELASTIX})
set(SITK_GENERIC_LABEL_INTERPOLATOR OFF)
if(GenericLabelInterpolator IN_LIST ITK_MODULES_ENABLED)
  set(SITK_GENERIC_LABEL_INTERPOLATOR ON)
endif()

include(sitkCheckTemplateDisambiguation)

configure_file("src/sitkConfigure.h.in" "include/sitkConfigure.h")
configure_file("src/sitkVersionConfig.h.in" "include/sitkVersionConfig.h" @ONLY)

# SimpleITKCommon library sources
set(
  SimpleITKCommonSource
  src/sitkImage.cxx
  src/sitkImageExplicit.cxx
  src/sitkProcessObject.cxx
  src/sitkTransform.cxx
  src/sitkCompositeTransform.cxx
  src/sitkAffineTransform.cxx
  src/sitkBSplineTransform.cxx
  src/sitkDisplacementFieldTransform.cxx
  src/sitkEuler2DTransform.cxx
  src/sitkEuler3DTransform.cxx
  src/sitkScaleTransform.cxx
  src/sitkScaleSkewVersor3DTransform.cxx
  src/sitkComposeScaleSkewVersor3DTransform.cxx
  src/sitkScaleVersor3DTransform.cxx
  src/sitkSimilarity2DTransform.cxx
  src/sitkSimilarity3DTransform.cxx
  src/sitkTranslationTransform.cxx
  src/sitkVersorTransform.cxx
  src/sitkVersorRigid3DTransform.cxx
  src/sitkCommand.cxx
  src/sitkFunctionCommand.cxx
  src/sitkPixelIDValues.cxx
  src/sitkExceptionObject.cxx
  src/sitkKernel.cxx
  src/sitkEvent.cxx
  src/sitkLogger.cxx
  src/sitkInterpolator.cxx
  src/sitkVersion.cxx
  src/sitkObjectOwnedBase.cxx
  src/sitkProcessObjectDeleter.cxx
  include/Ancillary/hl_sha1.cxx
)

set(
  use_itk_modules
  ITK::ITKCommonModule
  ITK::ITKImageComposeModule
  ITK::ITKImageIntensityModule
  ITK::ITKLabelMapModule
  ITK::ITKTransformModule
  ITK::ITKIOTransformBaseModule
  ITK::ITKDisplacementFieldModule
)

if("GenericLabelInterpolator" IN_LIST ITK_MODULES_ENABLED)
  list(APPEND use_itk_modules ITK::GenericLabelInterpolatorModule)
endif()

add_library(
  SimpleITKCommon
  ${SimpleITKCommonSource}
  ${SimpleITKAncillarySource}
)

target_link_libraries(
  SimpleITKCommon
  PRIVATE
    ${use_itk_modules}
    ITK::ITKTransformIO
)
if(SimpleITK_EXPLICIT_INSTANTIATION)
  target_link_libraries(SimpleITKCommon PRIVATE SimpleITKExplicit)
endif()

# Add headers using FILE_SET for automatic include directory management and installation
target_sources(
  SimpleITKCommon
  PUBLIC
    FILE_SET HEADERS
      BASE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}/include
      FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/SimpleITK.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/itkHolderCommand.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkAffineTransform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkBSplineTransform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkCommand.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkCommon.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkComposeScaleSkewVersor3DTransform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkCompositeTransform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkConditional.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkCreateInterpolator.hxx
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkDetail.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkDisplacementFieldTransform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkDualMemberFunctionFactory.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkDualMemberFunctionFactory.hxx
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkEuler2DTransform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkEuler3DTransform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkEvent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExceptionObject.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkFunctionCommand.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkImage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkImageConvert.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkImageConvert.hxx
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkInterpolator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkKernel.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkLogger.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkMacro.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkMemberFunctionFactory.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkMemberFunctionFactory.hxx
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkMemberFunctionFactoryBase.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkNonCopyable.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkObjectOwnedBase.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkPathType.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkPixelIDTokens.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkPixelIDTypeLists.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkPixelIDTypes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkPixelIDValues.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkProcessObject.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkProcessObjectDeleter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkRandomSeed.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkScaleSkewVersor3DTransform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkScaleTransform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkScaleVersor3DTransform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkSimilarity2DTransform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkSimilarity3DTransform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkTemplateFunctions.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkTransform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkTranslationTransform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkVersion.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkVersorRigid3DTransform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkVersorTransform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Ancillary/FunctionTraits.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Ancillary/hl_sha1.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Ancillary/type_list2.h
        ${CMAKE_CURRENT_BINARY_DIR}/include/sitkConfigure.h
        ${CMAKE_CURRENT_BINARY_DIR}/include/sitkVersionConfig.h
)
target_sources(
  SimpleITKCommon
  PRIVATE
    FILE_SET private_headers
      TYPE HEADERS
      BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src
      FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sitkImage.hxx
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sitkPimpleImageBase.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sitkPimpleImageBase.hxx
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sitkPimpleTransform.hxx
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sitkTransformHelper.hxx
)

# FILE_SET automatically adds BASE_DIRS to INCLUDE_DIRECTORIES and INTERFACE_INCLUDE_DIRECTORIES
# PRIVATE file sets are not installed but provide IDE integration and automatic include paths
target_compile_options(
  SimpleITKCommon
  PUBLIC
    ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS}
)
target_compile_features(SimpleITKCommon PUBLIC cxx_std_17)

sitk_install_exported_target( SimpleITKCommon )

# Add custom command that will delete java files which need to be rebuilt when changes
# are made to Common
if(WRAP_JAVA)
  add_custom_command(
    TARGET SimpleITKCommon
    POST_BUILD
    COMMENT "Cleaning java build..."
    COMMAND
      ${CMAKE_COMMAND} -E remove -f
      ${SimpleITK_BINARY_DIR}/Wrapping/org/itk/simple/*.java
    COMMAND
      ${CMAKE_COMMAND} -E remove -f
      ${SimpleITK_BINARY_DIR}/Wrapping/build/org/itk/simple/*.class
  )
endif()
