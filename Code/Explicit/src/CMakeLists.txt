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


# these files are the instantiated ITK filter, but they do not do IO,
# so we don't need to register the IO factoried here.
set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include(${ITK_USE_FILE})

if ( MSVC AND SITK_BUILD_SHARED_LIBS )
  set( SimpleITKExplicit_FORCE_LIBRARY_TYPE "STATIC" )
endif()

add_library ( SimpleITKExplicit ${SimpleITKExplicit_FORCE_LIBRARY_TYPE} ${SimpleITKExplicitSource} )
target_link_libraries ( SimpleITKExplicit ${ITK_LIBRARIES} )
set_target_properties( SimpleITKExplicit PROPERTIES SKIP_BUILD_RPATH TRUE )
sitk_install_exported_target( SimpleITKExplicit )
