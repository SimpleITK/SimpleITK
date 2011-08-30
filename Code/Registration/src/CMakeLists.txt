set( SimpleITKRegistrationSource
  sitkAffineTransform.cxx
  sitkMattesMutualInformationMetric.cxx
  sitkLinearInterpolate.cxx
  sitkRegistration.cxx
  sitkRegularStepGradientDescentOptimizer.cxx
  sitkTransform.cxx
  sitkResampleImageFilter.cxx
  )


add_library ( SimpleITKRegistration STATIC ${SimpleITKRegistrationSource} )
target_link_libraries ( SimpleITKRegistration ${ITK_LIBRARIES} SimpleITKCommon )