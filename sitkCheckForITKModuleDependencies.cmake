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
list(APPEND SITK_REQUIRED_ITK_MODULES
  ITKAnisotropicSmoothing
  ITKAntiAlias
  ITKBiasCorrection
  ITKBinaryMathematicalMorphology
  ITKClassifiers
  ITKColormap
  ITKCommon
  ITKConnectedComponents
  ITKConvolution
  ITKCurvatureFlow
  ITKDeconvolution
  ITKDenoising
  ITKDisplacementField
  ITKDistanceMap
  ITKFFT
  ITKFastMarching
  ITKImageAdaptors
  ITKImageCompare
  ITKImageCompose
  ITKImageFeature
  ITKImageFilterBase
  ITKImageFusion
  ITKImageGradient
  ITKImageGrid
  ITKImageIntensity
  ITKImageLabel
  ITKImageNoise
  ITKImageSources
  ITKImageStatistics
  ITKLabelMap
  ITKLabelVoting
  ITKLevelSets
  ITKMathematicalMorphology
  ITKPDEDeformableRegistration
  ITKRegionGrowing
  ITKReview
  ITKSmoothing
  ITKStatistics
  ITKThresholding
  ITKTransform
  ITKWatersheds
)

foreach(itkDependency ${SITK_REQUIRED_ITK_MODULES})
  list(FIND ITK_MODULES_ENABLED ${itkDependency} ITKDependency_FOUND)
  if(ITKDependency_FOUND EQUAL -1)
    message(FATAL_ERROR "SimpleITK requires that the ${itkDependency} module be turned on in ITK")
  endif()
endforeach(itkDependency)
