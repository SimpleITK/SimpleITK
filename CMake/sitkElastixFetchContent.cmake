#-----------------------------------------------------------------------------
# Get and build Elastix using FetchContent

include(FetchContent)

# Set policy to allow normal variable to override set CACHE variables
set(CMAKE_POLICY_DEFAULT_CMP0126 NEW)

# Set Elastix Git repository and tag (shared)
include("${CMAKE_CURRENT_LIST_DIR}/sitkElastixGitOptions.cmake")

# Configure Elastix-specific options that need to be set before FetchContent_Declare
if(NOT ${BUILD_SHARED_LIBS})
  set(CMAKE_C_VISIBILITY_PRESET "hidden" CACHE STRING "" FORCE)
  set(CMAKE_CXX_VISIBILITY_PRESET "hidden" CACHE STRING "" FORCE)
  set(ITK_TEMPLATE_VISIBILITY_DEFAULT OFF CACHE BOOL "" FORCE)
endif()

# Elastix build configuration
set(ELASTIX_BUILD_EXECUTABLE OFF)
set(ELASTIX_USE_OPENMP "${SimpleITK_ELASTIX_USE_OPENMP}")
set(ELASTIX_USE_OPENCL "${SimpleITK_ELASTIX_USE_OPENCL}")

set(ELASTIX_USE_VTK OFF)

set(ELASTIX_IMAGE_2D_PIXELTYPES "float")
set(ELASTIX_IMAGE_3D_PIXELTYPES "float")
set(ELASTIX_IMAGE_4D_PIXELTYPES "float")

set(BUILD_TESTING OFF)
set(BUILD_EXAMPLES OFF)

# Elastix component options — enabled
foreach(
  _component
  USE_AdaptiveStochasticGradientDescent
  USE_AdvancedAffineTransformElastix
  USE_AdvancedBSplineTransform
  USE_AdvancedKappaStatisticMetric
  USE_AdvancedMattesMutualInformationMetric
  USE_AdvancedMeanSquaresMetric
  USE_AdvancedNormalizedCorrelationMetric
  USE_AffineDTITransformElastix
  USE_AffineLogStackTransform
  USE_AffineLogTransformElastix
  USE_BSplineInterpolator
  USE_BSplineInterpolatorFloat
  USE_BSplineResampleInterpolator
  USE_BSplineResampleInterpolatorFloat
  USE_BSplineStackTransform
  USE_CorrespondingPointsEuclideanDistanceMetric
  USE_DeformationFieldTransform
  USE_DisplacementMagnitudePenalty
  USE_EulerTransformElastix
  USE_FixedGenericPyramid
  USE_FixedRecursivePyramid
  USE_FixedShrinkingPyramid
  USE_FixedSmoothingPyramid
  USE_GridSampler
  USE_LinearInterpolator
  USE_LinearResampleInterpolator
  USE_MovingGenericPyramid
  USE_MovingRecursivePyramid
  USE_MovingShrinkingPyramid
  USE_MovingSmoothingPyramid
  USE_MultiInputRandomCoordinateSampler
  USE_MultiMetricMultiResolutionRegistration
  USE_MultiResolutionRegistration
  USE_MultiResolutionRegistrationWithFeatures
  USE_MutualInformationHistogramMetric
  USE_MyStandardResampler
  USE_NearestNeighborInterpolator
  USE_NearestNeighborResampleInterpolator
  USE_NormalizedGradientCorrelationMetric
  USE_NormalizedMutualInformationMetric
  USE_PCAMetric
  USE_PCAMetric2
  USE_QuasiNewtonLBFGS
  USE_RandomCoordinateSampler
  USE_RandomSampler
  USE_RandomSamplerSparseMask
  USE_ReducedDimensionBSplineInterpolator
  USE_ReducedDimensionBSplineResampleInterpolator
  USE_SimilarityTransformElastix
  USE_SplineKernelTransform
  USE_StandardGradientDescent
  USE_TransformBendingEnergyPenanalty
  USE_TransformRigidityPenalty
  USE_TranslationTransformElastix
  USE_VarianceOverLastDimensionMetric
  USE_WeightedCombinationTransformElastix
)
  set(${_component} ON)
endforeach()

# Elastix component options — disabled
foreach(
  _component
  USE_BSplineTransformWithDiffusion
  USE_CMAEvolutionStrategy
  USE_CUDAResampler
  USE_ConjugateGradient
  USE_ConjugateGradientFRPR
  USE_DistancePreservingRigidityPenalty
  USE_FiniteDifferenceGradientDescent
  USE_FullSampler
  USE_FullSearch
  USE_GradientDifferenceMetric
  USE_KNNGraphAlphaMutualInformationMetric
  USE_MissingStructurePenalty
  USE_MultiBSplineTransformWithNormal
  USE_PatternIntensityMetric
  USE_PolydataDummyPenalty
  USE_Powell
  USE_RSGDEachParameterApart
  USE_RayCastInterpolator
  USE_RayCastResampleInterpolator
  USE_RegularStepGradientDescent
  USE_Simplex
  USE_SimultaneousPerturbation
  USE_StatisticalShapePenalty
  USE_ViolaWellsMutualInformationMetric
)
  set(${_component} OFF)
endforeach()

# OpenCL-conditional components
foreach(
  _component
  USE_OpenCLFixedGenericPyramid
  USE_OpenCLMovingGenericPyramid
  USE_OpenCLResampler
)
  set(${_component} "${SimpleITK_ELASTIX_USE_OPENCL}")
endforeach()

FetchContent_Declare(
  Elastix
  GIT_REPOSITORY "${ELASTIX_GIT_REPOSITORY}"
  GIT_TAG "${ELASTIX_GIT_TAG}"
  EXCLUDE_FROM_ALL
  FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(Elastix)

# Check if FetchContent used find_package() or fetched from source
FetchContent_GetProperties(Elastix)
if(elastix_SOURCE_DIR)
  message(STATUS "Elastix fetched from repository and built from source")
  message(STATUS "  Source directory: ${elastix_SOURCE_DIR}")
  message(STATUS "  Binary directory: ${elastix_BINARY_DIR}")

  set(Elastix_DIR "${elastix_BINARY_DIR}")
  # Include the real ElastixConfig.cmake to populate ELASTIX_INCLUDE_DIRS,
  # ELASTIX_LIBRARIES, ELASTIX_CONFIG_TARGETS_FILE, etc. The config's own
  # guard (NOT TARGET elastix_lib) prevents re-importing already-defined targets.
  include("${elastix_BINARY_DIR}/ElastixConfig.cmake")
elseif(DEFINED Elastix_FOUND)
  message(STATUS "Elastix found via find_package()")
  # Elastix_DIR should already be set by find_package()
else()
  message(FATAL_ERROR "Elastix configuration failed - no targets available")
endif()

# Allow a user's cache variable to be respected.
unset(BUILD_TESTING)
unset(BUILD_EXAMPLES)
