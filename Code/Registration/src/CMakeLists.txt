
set( SimpleITKRegistration
  sitkImageRegistrationMethod.cxx
  sitkImageRegistrationMethod_CreateOptimizer.cxx
  sitkImageRegistrationMethod_CreateMetric.cxx
  )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

# these files are the instantiated ITK filter, but they do not do IO,
# so we don't need to register the IO factories here.
set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
find_package(ITK COMPONENTS ITKCommon  ITKLabelMap ITKOptimizersv4 ITKMetricsv4 ITKRegistrationMethodsv4 REQUIRED)
include(${ITK_USE_FILE})

add_library ( SimpleITKRegistration ${SimpleITKRegistration} )
# The BasicFiltersLibrary is needed of the Cast filter
target_link_libraries ( SimpleITKRegistration
  PUBLIC SimpleITKCommon SimpleITKBasicFilters1
  PRIVATE  ${ITK_LIBRARIES} )
if (SITK_EXPLICIT_INSTANTIATION)
  target_link_libraries ( SimpleITKRegistration PRIVATE SimpleITKExplicit )
endif()

sitk_install_exported_target( SimpleITKRegistration )
