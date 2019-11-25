set ( SimpleITKExplicitSource
  sitkExplicitITKComposeImageFilter.cxx
  sitkExplicitITKDefaultPixelAccessor.cxx
  sitkExplicitITKDefaultVectorPixelAccessor.cxx
  sitkExplicitITKImageBase.cxx
  sitkExplicitITKImage.cxx
  sitkExplicitITKImageRegion.cxx
  sitkExplicitITKImageSource.cxx
  sitkExplicitITKImageToImageFilter.cxx
  sitkExplicitITKImportImageContainer.cxx
  sitkExplicitITKInPlaceImageFilter.cxx
  sitkExplicitITKLabelMap.cxx
  sitkExplicitITKVectorImage.cxx
  sitkExplicitITKVectorIndexSelectionCastImageFilter.cxx
  sitkExplicitITKImageConstIterator.cxx
  sitkExplicitITKImageRegionConstIterator.cxx
  sitkExplicitITKImageScanlineConstIterator.cxx
  sitkExplicitITKImageScanlineIterator.cxx

  )


set(use_itk_modules ITKCommon ITKImageCompose ITKImageIntensity ITKLabelMap)
find_package(ITK COMPONENTS ${use_itk_modules} REQUIRED)
include(${ITK_USE_FILE})

if ( MSVC AND SITK_BUILD_SHARED_LIBS )
  set( SimpleITKExplicit_FORCE_LIBRARY_TYPE "STATIC" )
endif()
add_library ( SimpleITKExplicit ${SimpleITKExplicit_FORCE_LIBRARY_TYPE} ${SimpleITKExplicitSource} )
if( SITK_BUILD_SHARED_LIBS )
  set_target_properties(SimpleITKExplicit PROPERTIES CXX_VISIBILITY_PRESET default)
endif()
sitk_target_use_itk( SimpleITKExplicit PUBLIC ${use_itk_modules} )
target_include_directories ( SimpleITKExplicit
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/Explicit/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/Common/include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/Code/Common/include>
    $<INSTALL_INTERFACE:${SimpleITK_INSTALL_INCLUDE_DIR}> )
target_compile_definitions( SimpleITKExplicit
  PUBLIC
    SITK_USE_EXPLICITITK )
target_compile_options( SimpleITKExplicit
  PUBLIC
    ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS} )
target_compile_features( SimpleITKExplicit PUBLIC cxx_std_11 )

sitk_install_exported_target( SimpleITKExplicit )
