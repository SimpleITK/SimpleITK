set(
  SimpleITKRegistrationSource
  src/sitkImageRegistrationMethod.cxx
  src/sitkImageRegistrationMethod_CreateOptimizer.cxx
  src/sitkImageRegistrationMethod_CreateMetric.cxx
)

set(
  use_itk_modules
  ITK::ITKCommonModule
  ITK::ITKLabelMapModule
  ITK::ITKOptimizersv4Module
  ITK::ITKMetricsv4Module
  ITK::ITKRegistrationMethodsv4Module
)
if("GenericLabelInterpolator" IN_LIST ITK_MODULES_ENABLED)
  list(APPEND use_itk_modules ITK::GenericLabelInterpolatorModule)
endif()

add_library(SimpleITKRegistration ${SimpleITKRegistrationSource})
target_link_libraries(SimpleITKRegistration PRIVATE ${use_itk_modules})

# The BasicFiltersLibrary is needed of the Cast filter
target_link_libraries(
  SimpleITKRegistration
  PUBLIC
    SimpleITKCommon
    SimpleITK_ITKCommon
)
if(SimpleITK_EXPLICIT_INSTANTIATION)
  target_link_libraries(SimpleITKRegistration PRIVATE SimpleITKExplicit)
endif()

# Add headers using FILE_SET for automatic include directory management and installation
target_sources(
  SimpleITKRegistration
  PUBLIC
    FILE_SET HEADERS
      BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
      FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkImageRegistrationMethod.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkRegistration.h
)
target_sources(
  SimpleITKRegistration
  PRIVATE
    FILE_SET private_headers
      TYPE HEADERS
      BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src
      FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sitkImageRegistrationMethod_CreateMetric.hxx
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sitkImageRegistrationMethod_CreateParametersAdaptor.hxx
)

# FILE_SET automatically adds BASE_DIRS to INCLUDE_DIRECTORIES and INTERFACE_INCLUDE_DIRECTORIES
# PRIVATE file sets are not installed but provide IDE integration and automatic include paths

target_compile_options(
  SimpleITKRegistration
  PUBLIC
    ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS}
)
target_compile_features(SimpleITKRegistration PUBLIC cxx_std_17)

sitk_install_exported_target( SimpleITKRegistration )
