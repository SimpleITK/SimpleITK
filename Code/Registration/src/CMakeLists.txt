set( SimpleITKRegistrationSource
  sitkRegistration.cxx
  sitkRegularStepGradientDescentOptimizer.cxx
  sitkTransform.cxx
  )


add_library ( SimpleITKRegistration STATIC ${SimpleITKRegistrationSource} )
target_link_libraries ( SimpleITKRegistration ${ITK_LIBRARIES} SimpleITKCommon )