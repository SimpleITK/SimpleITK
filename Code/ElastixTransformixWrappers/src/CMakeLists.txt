
find_package(Elastix REQUIRED)

# included for the "transformix_lib" library
include(${ELASTIX_CONFIG_TARGETS_FILE})


set(use_itk_modules ITKCommon ITKImageGrid ITKImageIO ITKRegistrationCommon ITKIOMeshBase)
find_package(ITK COMPONENTS REQUIRED ${use_itk_modules} )

add_library( ElastixImageFilter sitkElastixImageFilter.cxx  sitkElastixImageFilterImpl.cxx )
target_include_directories( ElastixImageFilter
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/ElastixTransformixWrappers/include>
    $<INSTALL_INTERFACE:${SimpleITK_INSTALL_INCLUDE_DIR}>
  PRIVATE
    ${ELASTIX_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries( ElastixImageFilter
  PUBLIC
    SimpleITKCommon
    SimpleITK_ITKCommon
    ${ELASTIX_LIBRARIES} )
target_compile_options( ElastixImageFilter PUBLIC ${SimpleITK_PUBLIC_COMPILE_OPTIONS} PRIVATE ${SimpleITK_PRIVATE_COMPILE_OPTIONS} )
target_compile_features( ElastixImageFilter PUBLIC cxx_std_17 )
sitk_target_use_itk ( ElastixImageFilter PRIVATE ${use_itk_modules} )
sitk_install_exported_target( ElastixImageFilter )


add_library( TransformixImageFilter sitkTransformixImageFilter.cxx sitkTransformixImageFilterImpl.h  sitkTransformixImageFilterImpl.cxx )
target_include_directories( TransformixImageFilter
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/ElastixTransformixWrappers/include>
    $<INSTALL_INTERFACE:${SimpleITK_INSTALL_INCLUDE_DIR}>
  PRIVATE
    ${ELASTIX_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries( TransformixImageFilter
  PUBLIC
    SimpleITKCommon
    SimpleITK_ITKCommon
    ${ELASTIX_LIBRARIES} )
target_compile_options( TransformixImageFilter PUBLIC ${SimpleITK_PUBLIC_COMPILE_OPTIONS} PRIVATE ${SimpleITK_PRIVATE_COMPILE_OPTIONS} )
target_compile_features( TransformixImageFilter PUBLIC cxx_std_17 )
sitk_target_use_itk ( TransformixImageFilter PRIVATE ${use_itk_modules} )
sitk_install_exported_target( TransformixImageFilter )
