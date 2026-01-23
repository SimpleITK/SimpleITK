set(
  SimpleITKIOSource
  src/sitkImageFileReader.cxx
  src/sitkImageFileWriter.cxx
  src/sitkImageReaderBase.cxx
  src/sitkImageSeriesReader.cxx
  src/sitkImageSeriesWriter.cxx
  src/sitkImportImageFilter.cxx
  src/sitkShow.cxx
  src/sitkImageIOUtilities.cxx
  src/sitkImageViewer.cxx
)

set(
  use_itk_modules
  ITK::ITKCommonModule
  ITK::ITKLabelMapModule
  ITK::ITKImageComposeModule
  ITK::ITKImageIntensityModule
  ITK::ITKIOImageBaseModule
  ITK::ITKIOTransformBaseModule
  ITK::ITKIOGDCMModule
)

add_library(SimpleITKIO ${SimpleITKIOSource})
target_link_libraries(
  SimpleITKIO
  PRIVATE
    ${use_itk_modules}
    ITK::ITKImageIO
)
target_link_libraries(SimpleITKIO PUBLIC SimpleITKCommon)
if(SimpleITK_EXPLICIT_INSTANTIATION)
  target_link_libraries(SimpleITKIO PRIVATE SimpleITKExplicit)
endif()

# Add headers using FILE_SET for automatic include directory management and installation
target_sources(
  SimpleITKIO
  PUBLIC
    FILE_SET HEADERS
      TYPE HEADERS
      BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
      FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkIO.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkImageFileReader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkImageFileWriter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkImageReaderBase.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkImageSeriesReader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkImageSeriesWriter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkImageViewer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkImportImageFilter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkShow.h
)
target_sources(
  SimpleITKIO
  PRIVATE
    FILE_SET private_headers
      TYPE HEADERS
      BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src
      FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sitkImageIOUtilities.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sitkMetaDataDictionaryCustomCast.hxx
)

# FILE_SET automatically adds BASE_DIRS to INCLUDE_DIRECTORIES and INTERFACE_INCLUDE_DIRECTORIES
# PRIVATE file sets are not installed but provide IDE integration and automatic include paths

target_compile_options(
  SimpleITKIO
  PUBLIC
    ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS}
)
target_compile_features(SimpleITKIO PUBLIC cxx_std_17)

sitk_install_exported_target( SimpleITKIO )

# Add custom command that will delete java files which need to be rebuilt when changes
# are made to IO
if(WRAP_JAVA)
  add_custom_command(
    TARGET SimpleITKIO
    POST_BUILD
    COMMENT "Cleaning java build..."
    COMMAND
      ${CMAKE_COMMAND} -E remove -f
      ${SimpleITK_BINARY_DIR}/Wrapping/org/itk/simple/*.java
    COMMAND
      ${CMAKE_COMMAND} -E remove -f
      ${SimpleITK_BINARY_DIR}/Wrapping/build/org/itk/simple/*.class
  )
endif()
