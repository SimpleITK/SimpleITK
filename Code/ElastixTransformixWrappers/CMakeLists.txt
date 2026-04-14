if(NOT TARGET elastix_lib)
  find_package(Elastix CONFIG REQUIRED)
endif()

add_library(
  SimpleElastix
  src/sitkElastixImageFilter.cxx
  src/sitkElastixImageFilterImpl.cxx
  src/sitkTransformixImageFilter.cxx
  src/sitkTransformixImageFilterImpl.cxx
)

target_sources(
  SimpleElastix
  PUBLIC
    FILE_SET HEADERS
      BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
      FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkElastixImageFilter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkElastixTransformixWrappers.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkTransformixImageFilter.h
  PRIVATE
    FILE_SET private_headers
      TYPE HEADERS
      BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src
      FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sitkElastixImageFilterImpl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sitkTransformixImageFilterImpl.h
)

target_link_libraries(
  SimpleElastix
  PUBLIC
    SimpleITKCommon
  PRIVATE
    SimpleITK_ITKCommon
    transformix_lib
    elastix_lib
)
target_compile_options(
  SimpleElastix
  PUBLIC
    ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS}
)
target_compile_features(SimpleElastix PUBLIC cxx_std_17)
sitk_install_exported_target(SimpleElastix)
