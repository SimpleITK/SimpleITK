
set( SimpleITKIOSource
  sitkImageFileReader.cxx
  sitkImageFileWriter.cxx
  sitkImageReaderBase.cxx
  sitkImageSeriesReader.cxx
  sitkImageSeriesWriter.cxx
  sitkImportImageFilter.cxx
  sitkShow.cxx
  )

set(use_itk_modules  ITKCommon ITKLabelMap ITKImageCompose
  ITKImageIntensity ITKIOImageBase ITKIOTransformBase ITKIOGDCM )
foreach( mod IN LISTS ITK_MODULES_ENABLED)
  if( ${mod} MATCHES "IO")
    list(APPEND use_itk_modules ${mod})
  endif()
endforeach()

find_package(ITK COMPONENTS ${use_itk_modules} )
include(${ITK_USE_FILE})
add_library ( SimpleITKIO ${SimpleITKIOSource} )
sitk_target_use_itk ( SimpleITKIO PRIVATE ${use_itk_modules} )
target_link_libraries ( SimpleITKIO
  PUBLIC  SimpleITKCommon )
if (SimpleITK_EXPLICIT_INSTANTIATION)
  target_link_libraries ( SimpleITKIO PRIVATE SimpleITKExplicit )
endif()
target_include_directories ( SimpleITKIO
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/IO/include>
    $<INSTALL_INTERFACE:${SimpleITK_INSTALL_INCLUDE_DIR}>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR} )
target_compile_options( SimpleITKIO
  PUBLIC
    ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS} )


sitk_install_exported_target( SimpleITKIO )

# Add custom command that will delete java files which need to be rebuilt when changes
# are made to IO
if( WRAP_JAVA )
  add_custom_command(
    TARGET SimpleITKIO
    POST_BUILD
    COMMENT "Cleaning java build..."
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/org/itk/simple/*.java
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/build/org/itk/simple/*.class
  )
endif()
