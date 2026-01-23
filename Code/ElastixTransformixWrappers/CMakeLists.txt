find_package(Elastix REQUIRED)

# included for the "transformix_lib" library
include(${ELASTIX_CONFIG_TARGETS_FILE})

set(
  use_itk_modules
  ITK::ITKCommonModule
  ITK::ITKImageGridModule
  ITK::ITKRegistrationCommonModule
  ITK::ITKIOMeshBaseModule
)

add_library(
  ElastixImageFilter
  src/sitkElastixImageFilter.cxx
  src/sitkElastixImageFilterImpl.cxx
)

# Add headers using FILE_SET for automatic include directory management and installation
target_sources(
  ElastixImageFilter
  PUBLIC
    FILE_SET HEADERS
      BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
      FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkElastixImageFilter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkElastixTransformixWrappers.h
  PRIVATE
    FILE_SET private_headers
      TYPE HEADERS
      BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src
      FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/sitkElastixImageFilterImpl.h
)

# FILE_SET automatically adds BASE_DIRS to INCLUDE_DIRECTORIES and INTERFACE_INCLUDE_DIRECTORIES
# Additional private includes for Elastix
target_include_directories(ElastixImageFilter PRIVATE ${ELASTIX_INCLUDE_DIRS})

target_link_libraries(
  ElastixImageFilter
  PUBLIC
    SimpleITKCommon
  PRIVATE
    SimpleITK_ITKCommon
    ${ELASTIX_LIBRARIES}
)
target_compile_options(
  ElastixImageFilter
  PUBLIC
    ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS}
)
target_compile_features(ElastixImageFilter PUBLIC cxx_std_17)
target_link_libraries(ElastixImageFilter PRIVATE ${use_itk_modules})
sitk_install_exported_target( ElastixImageFilter )

add_library(
  TransformixImageFilter
  src/sitkTransformixImageFilter.cxx
  src/sitkTransformixImageFilterImpl.cxx
)

# Add headers using FILE_SET for automatic include directory management and installation
target_sources(
  TransformixImageFilter
  PUBLIC
    FILE_SET HEADERS
      BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
      FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkTransformixImageFilter.h
  PRIVATE
    FILE_SET private_headers
      TYPE HEADERS
      BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src
      FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/sitkTransformixImageFilterImpl.h
)

# FILE_SET automatically adds BASE_DIRS to INCLUDE_DIRECTORIES and INTERFACE_INCLUDE_DIRECTORIES
# Additional private includes for Elastix
target_include_directories(
  TransformixImageFilter
  PRIVATE
    ${ELASTIX_INCLUDE_DIRS}
)

target_link_libraries(
  TransformixImageFilter
  PUBLIC
    SimpleITKCommon
    SimpleITK_ITKCommon
    ${ELASTIX_LIBRARIES}
)
target_compile_options(
  TransformixImageFilter
  PUBLIC
    ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS}
)
target_compile_features(TransformixImageFilter PUBLIC cxx_std_17)
target_link_libraries(TransformixImageFilter PRIVATE ${use_itk_modules})
sitk_install_exported_target( TransformixImageFilter )
