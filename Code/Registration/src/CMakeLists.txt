set( SimpleITKRegistrationSource
  sitkMetric.cxx
  sitkRegistration.cxx
  sitkRegularStepGradientDescentOptimizer.cxx
  sitkTransform.cxx
  )

include(${ITK_USE_FILE})

add_library ( SimpleITKRegistration STATIC ${SimpleITKRegistrationSource} )
target_link_libraries ( SimpleITKRegistration ${ITK_LIBRARIES} SimpleITKCommon )