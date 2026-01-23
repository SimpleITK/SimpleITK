set(
  SimpleITKExplicitSource
  src/sitkExplicitITKComposeImageFilter.cxx
  src/sitkExplicitITKDefaultPixelAccessor.cxx
  src/sitkExplicitITKDefaultVectorPixelAccessor.cxx
  src/sitkExplicitITKImageBase.cxx
  src/sitkExplicitITKImage.cxx
  src/sitkExplicitITKImageRegion.cxx
  src/sitkExplicitITKImageSource.cxx
  src/sitkExplicitITKImageToImageFilter.cxx
  src/sitkExplicitITKImportImageContainer.cxx
  src/sitkExplicitITKInPlaceImageFilter.cxx
  src/sitkExplicitITKLabelMap.cxx
  src/sitkExplicitITKVectorImage.cxx
  src/sitkExplicitITKVectorIndexSelectionCastImageFilter.cxx
  src/sitkExplicitITKImageConstIterator.cxx
  src/sitkExplicitITKImageRegionConstIterator.cxx
  src/sitkExplicitITKImageScanlineConstIterator.cxx
  src/sitkExplicitITKImageScanlineIterator.cxx
)

set(
  use_itk_modules
  ITK::ITKCommonModule
  ITK::ITKImageComposeModule
  ITK::ITKImageIntensityModule
  ITK::ITKLabelMapModule
)

if(MSVC AND SITK_BUILD_SHARED_LIBS)
  set(SimpleITKExplicit_FORCE_LIBRARY_TYPE "STATIC")
endif()
add_library(
  SimpleITKExplicit
  ${SimpleITKExplicit_FORCE_LIBRARY_TYPE}
  ${SimpleITKExplicitSource}
)
if(SITK_BUILD_SHARED_LIBS)
  set_target_properties(
    SimpleITKExplicit
    PROPERTIES
      CXX_VISIBILITY_PRESET
        default
  )
endif()
target_link_libraries(SimpleITKExplicit PUBLIC ${use_itk_modules})

# Add headers using FILE_SET for automatic include directory management and installation
target_sources(
  SimpleITKExplicit
  PUBLIC
    FILE_SET HEADERS
      BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
      FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExplicit.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExplicitITK.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExplicitITKComposeImageFilter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExplicitITKDefaultPixelAccessor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExplicitITKDefaultVectorPixelAccessor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExplicitITKImage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExplicitITKImageBase.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExplicitITKImageConstIterator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExplicitITKImageRegion.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExplicitITKImageRegionConstIterator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExplicitITKImageScanlineConstIterator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExplicitITKImageScanlineIterator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExplicitITKImageSource.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExplicitITKImageToImageFilter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExplicitITKImportImageContainer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExplicitITKInPlaceImageFilter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExplicitITKLabelMap.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExplicitITKVectorImage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExplicitITKVectorIndexSelectionCastImageFilter.h
)

# FILE_SET automatically adds BASE_DIRS to INCLUDE_DIRECTORIES and INTERFACE_INCLUDE_DIRECTORIES
# Also need to add Common include directories for dependencies
target_include_directories(
  SimpleITKExplicit
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/Common/include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/Code/Common/include>
)

target_compile_definitions(SimpleITKExplicit PUBLIC SITK_USE_EXPLICITITK)
target_compile_options(
  SimpleITKExplicit
  PUBLIC
    ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS}
)
target_compile_features(SimpleITKExplicit PUBLIC cxx_std_17)

sitk_install_exported_target( SimpleITKExplicit )
