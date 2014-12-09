
set( SimpleITKRegistration
  sitkImageRegistrationMethod.cxx
  sitkImageRegistrationMethod_CreateOptimizer.cxx
  )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

# these files are the instantiated ITK filter, but they do not do IO,
# so we don't need to register the IO factories here.
set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include(${ITK_USE_FILE})

add_library ( SimpleITKRegistration ${SimpleITKRegistration} )
# The BasicFiltersLibrary is needed of the Cast filter
target_link_libraries ( SimpleITKRegistration ${ITK_LIBRARIES} SimpleITKCommon SimpleITKBasicFilters1 )
set_target_properties( SimpleITKRegistration PROPERTIES SKIP_BUILD_RPATH TRUE )

sitk_install_exported_target( SimpleITKRegistration )
