set ( SimpleITKCommonSource
  sitkImage.cxx
  sitkPixelIDValues.cxx
  ../include/Ancillary/hl_md5.cxx
  ../include/Ancillary/hl_sha1.cxx
  # NOTE: THIS IS A HACK AND NEEDS TO BE CHANGED
  ../../Registration/sitkAffineTransform.cxx
  ../../Registration/sitkMattesMutualInformationMetric.cxx
  ../../Registration/sitkLinearInterpolate.cxx
  ../../Registration/sitkRegistration.cxx

  )

add_library ( SimpleITKCommon STATIC ${SimpleITKCommonSource} ${SimpleITKAncillarySource} )
target_link_libraries ( SimpleITKCommon ${ITK_LIBRARIES} )

# Add custom command that will delete java files which need to be rebuilt when changes
# are made to Common
if( WRAP_JAVA )
  add_custom_command(
    TARGET SimpleITKCommon
    POST_BUILD
    COMMENT "Cleaning java build..."
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/org/itk/simple/*.java
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/build/org/itk/simple/*.class
  )
endif()
