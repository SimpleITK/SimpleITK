#
# The list of ITK modules on which SimpleITK is dependent. Dependencies
# were obtained using the WhatModulesITK.py script
# (see itk_source_directory/Utilities/Maintenance):
# WhatModulesITK.py itk_source_directory \
# $(find simpleitk_binary_directory/SimpleITK-build/Code \
# -name '*.h' -o -name '*.hxx' -o -name '*.cxx')
#
# Don't do "find simpleitk_binary_directory/SimpleITK-build/Code type -f"
# as this will attempt to analyze all of the object files too.
#
# The script does not list the IO modules as they are indirectly included.
# SimpleITK requires that the ITKReview module be turned on, and ITKReview
# is dependent on most of the IO modules so we only need to force 'review on' to
# ensure that we have the 'IO on' too.
#
list(APPEND _SITK_REQUIRED_ITK_MODULES
  ITKCommon
  ITKDisplacementField
  ITKIOGDCM
  ITKIOImageBase
  ITKIOTransformBase
  ITKImageCompose
  ITKImageIntensity
  ITKLabelMap
  ITKMetricsv4
  ITKOptimizersv4
  ITKRegistrationMethodsv4
  ITKTransform
)

foreach(itkDependency ${_SITK_REQUIRED_ITK_MODULES})
  list(FIND ITK_MODULES_ENABLED ${itkDependency} ITKDependency_FOUND)
  if(ITKDependency_FOUND EQUAL -1)
    message(FATAL_ERROR "SimpleITK requires that the ${itkDependency} module be turned on in ITK")
  endif()
endforeach()
