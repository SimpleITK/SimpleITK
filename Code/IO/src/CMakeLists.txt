
set( SimpleITKIOSource
  sitkImageFileReader.cxx
  sitkImageFileWriter.cxx
  sitkImageReaderBase.cxx
  sitkImageSeriesReader.cxx
  sitkImportImageFilter.cxx
  sitkShow.cxx
  )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

include(${ITK_USE_FILE})

add_library ( SimpleITKIO ${SimpleITKIOSource} )
target_link_libraries ( SimpleITKIO ${ITK_LIBRARIES} SimpleITKCommon )
set_target_properties( SimpleITKIO PROPERTIES SKIP_BUILD_RPATH TRUE )

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
