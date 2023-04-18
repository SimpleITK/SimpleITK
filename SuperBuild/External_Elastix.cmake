set( proj Elastix )

# Set dependency list
set(${proj}_DEPENDENCIES "ITK")


file( WRITE "${CMAKE_CURRENT_BINARY_DIR}/${proj}-build/CMakeCacheInit.txt" "${ep_common_cache}" )

set( ELASTIX_GIT_REPOSITORY ${git_protocol}://github.com/SuperElastix/elastix )
set( ELASTIX_GIT_TAG 3b27d01340f37de78918de723412aa4e743a9270)

if( NOT ${BUILD_SHARED_LIBS} )
  list( APPEND ep_elastix_args
    "-DCMAKE_C_VISIBILITY_PRESET:STRING=hidden"
    "-DCMAKE_CXX_VISIBILITY_PRESET:STRING=hidden"
    "-DITK_TEMPLATE_VISIBILITY_DEFAULT:BOOL=OFF" )
endif()

if (NOT DEFINED CMAKE_CXX_STANDARD)
  list( APPEND ep_elastix_args "-DCMAKE_CXX_STANDARD:STRING=17")
endif()

ExternalProject_Add( ${proj}
  GIT_REPOSITORY ${ELASTIX_GIT_REPOSITORY}
  GIT_TAG ${ELASTIX_GIT_TAG}
  UPDATE_COMMAND ""
  SOURCE_DIR ${proj}
  BINARY_DIR ${proj}-build
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
  -DCMAKE_TOOLCHAIN_FILE:FILEPATH=${CMAKE_TOOLCHAIN_FILE}
  --no-warn-unused-cli
  -C "${CMAKE_CURRENT_BINARY_DIR}/${proj}-build/CMakeCacheInit.txt"
  ${ep_common_args}
  ${ep_elastix_args}
  -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
  -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=ON
  -DBUILD_TESTING:BOOL=OFF
  -DELASTIX_BUILD_EXECUTABLE:BOOL=OFF
  -DELASTIX_USE_OPENMP:BOOL=${SimpleITK_ELASTIX_USE_OPENMP}
  -DELASTIX_USE_OPENCL:BOOL=${SimpleITK_ELASTIX_USE_OPENCL}
  -DBUILD_SHARED_LIBS:BOOL=${BUILD_SHARED_LIBS}
  -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
  -DITK_DIR:PATH=${ITK_DIR}
  -DELASTIX_IMAGE_2D_PIXELTYPES:STRING=float
  -DELASTIX_IMAGE_3D_PIXELTYPES:STRING=float
  -DELASTIX_IMAGE_4D_PIXELTYPES:STRING=float
  -DUSE_AdaptiveStochasticGradientDescent:BOOL=ON
  -DUSE_AdvancedAffineTransformElastix:BOOL=ON
  -DUSE_AdvancedBSplineTransform:BOOL=ON
  -DUSE_AdvancedKappaStatisticMetric:BOOL=ON
  -DUSE_AdvancedMattesMutualInformationMetric:BOOL=ON
  -DUSE_AdvancedMeanSquaresMetric:BOOL=ON
  -DUSE_AdvancedNormalizedCorrelationMetric:BOOL=ON
  -DUSE_AffineDTITransformElastix:BOOL=ON
  -DUSE_AffineLogStackTransform:BOOL=ON
  -DUSE_AffineLogTransformElastix=ON
  -DUSE_BSplineInterpolator:BOOL=ON
  -DUSE_BSplineInterpolatorFloat:BOOL=ON
  -DUSE_BSplineResampleInterpolator:BOOL=ON
  -DUSE_BSplineResampleInterpolatorFloat:BOOL=ON
  -DUSE_BSplineStackTransform:BOOL=ON
  -DUSE_BSplineTransformWithDiffusion:BOOL=OFF
  -DUSE_CMAEvolutionStrategy:BOOL=OFF
  -DUSE_CUDAResampler:BOOL=OFF
  -DUSE_ConjugateGradient:BOOL=OFF
  -DUSE_ConjugateGradientFRPR:BOOL=OFF
  -DUSE_CorrespondingPointsEuclideanDistanceMetric:BOOL=ON
  -DUSE_DeformationFieldTransform:BOOL=ON
  -DUSE_DisplacementMagnitudePenalty:BOOL=ON
  -DUSE_DistancePreservingRigidityPenalty:BOOL=OFF
  -DUSE_EulerTransformElastix:BOOL=ON
  -DUSE_FiniteDifferenceGradientDescent:BOOL=OFF
  -DUSE_FixedGenericPyramid:BOOL=ON
  -DUSE_FixedRecursivePyramid:BOOL=ON
  -DUSE_FixedShrinkingPyramid:BOOL=ON
  -DUSE_FixedSmoothingPyramid:BOOL=ON
  -DUSE_FullSampler:BOOL=OFF
  -DUSE_FullSearch:BOOL=OFF
  -DUSE_GradientDifferenceMetric:BOOL=OFF
  -DUSE_GridSampler:BOOL=ON
  -DUSE_KNNGraphAlphaMutualInformationMetric:BOOL=OFF
  -DUSE_LinearInterpolator:BOOL=ON
  -DUSE_LinearResampleInterpolator:BOOL=ON
  -DUSE_MissingStructurePenalty:BOOL=OFF
  -DUSE_MovingGenericPyramid:BOOL=ON
  -DUSE_MovingRecursivePyramid:BOOL=ON
  -DUSE_MovingShrinkingPyramid:BOOL=ON
  -DUSE_MovingSmoothingPyramid:BOOL=ON
  -DUSE_MultiBSplineTransformWithNormal:BOOL=OFF
  -DUSE_MultiInputRandomCoordinateSampler:BOOL=ON
  -DUSE_MultiMetricMultiResolutionRegistration:BOOL=ON
  -DUSE_MultiResolutionRegistration:BOOL=ON
  -DUSE_MultiResolutionRegistrationWithFeatures:BOOL=ON
  -DUSE_MutualInformationHistogramMetric:BOOL=ON
  -DUSE_MyStandardResampler:BOOL=ON
  -DUSE_OpenCLFixedGenericPyramid:BOOL=${SimpleITK_ELASTIX_USE_OPENCL}
  -DUSE_OpenCLMovingGenericPyramid:BOOL=${SimpleITK_ELASTIX_USE_OPENCL}
  -DUSE_OpenCLResampler:BOOL=${SimpleITK_ELASTIX_USE_OPENCL}
  -DUSE_NearestNeighborInterpolator:BOOL=ON
  -DUSE_NearestNeighborResampleInterpolator:BOOL=ON
  -DUSE_NormalizedGradientCorrelationMetric:BOOL=ON
  -DUSE_NormalizedMutualInformationMetric:BOOL=ON
  -DUSE_PCAMetric:BOOL=ON
  -DUSE_PCAMetric2:BOOL=ON
  -DUSE_PatternIntensityMetric:BOOL=OFF
  -DUSE_PolydataDummyPenalty:BOOL=OFF
  -DUSE_Powell:BOOL=OFF
  -DUSE_QuasiNewtonLBFGS:BOOL=ON
  -DUSE_RSGDEachParameterApart:BOOL=OFF
  -DUSE_RandomCoordinateSampler:BOOL=ON
  -DUSE_RandomSampler:BOOL=ON
  -DUSE_RandomSamplerSparseMask:BOOL=ON
  -DUSE_RayCastInterpolator:BOOL=OFF
  -DUSE_RayCastResampleInterpolator:BOOL=OFF
  -DUSE_ReducedDimensionBSplineInterpolator:BOOL=ON
  -DUSE_ReducedDimensionBSplineResampleInterpolator:BOOL=ON
  -DUSE_RegularStepGradientDescent:BOOL=OFF
  -DUSE_SimilarityTransformElastix:BOOL=ON
  -DUSE_Simplex:BOOL=OFF
  -DUSE_SimultaneousPerturbation:BOOL=OFF
  -DUSE_SplineKernelTransform:BOOL=ON
  -DUSE_StandardGradientDescent:BOOL=ON
  -DUSE_StatisticalShapePenalty:BOOL=OFF
  -DUSE_TransformBendingEnergyPenanalty:BOOL=ON
  -DUSE_TransformRigidityPenalty:BOOL=ON
  -DUSE_TranslationTransformElastix:BOOL=ON
  -DUSE_VarianceOverLastDimensionMetric:BOOL=ON
  -DUSE_ViolaWellsMutualInformationMetric:BOOL=OFF
  -DUSE_WeightedCombinationTransformElastix:BOOL=ON
  BUILD_COMMAND ${BUILD_COMMAND_STRING}
  DEPENDS
      ${${proj}_DEPENDENCIES}
  ${External_Project_USES_TERMINAL}
)

ExternalProject_Get_Property( ${proj} install_dir )
set( Elastix_DIR "${install_dir}/lib/cmake/elastix")
