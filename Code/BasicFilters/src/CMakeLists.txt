set_source_files_properties ( ${SimpleITKBasicFiltersGeneratedSource} PROPERTIES GENERATED 1 )

# these files are the instantiated ITK filter, but they do not do IO,
# so we don't need to register the IO factoried here.
set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
set ( REQUIRED_ITK_MODULES
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
find_package(ITK COMPONENTS ${REQUIRED_ITK_MODULES} REQUIRED)
include(${ITK_USE_FILE})

# common source which all basic filter libraries need to be linked against
set ( SimpleITKBasicFilters0Source
  sitkImageFilter.cxx
)

add_library ( SimpleITKBasicFilters0 ${SimpleITKBasicFilters0Source} )
target_link_libraries ( SimpleITKBasicFilters0
  PUBLIC SimpleITKCommon
  PRIVATE ${ITK_LIBRARIES} )
if (SITK_EXPLICIT_INSTANTIATION)
  target_link_libraries ( SimpleITKBasicFilters0 PRIVATE SimpleITKExplicit )
endif()
target_include_directories( SimpleITKBasicFilters0
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/BasicFilters/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR} )

sitk_install_exported_target( SimpleITKBasicFilters0 )

# append this new library to the globally cached list
list ( APPEND SimpleITK_LIBRARIES SimpleITKBasicFilters0 )
set ( SimpleITK_LIBRARIES ${SimpleITK_LIBRARIES} CACHE INTERNAL "" )

# Source files in the SimpleITKBasicFilters1 library are manually
# handled for special dependency requirements
set ( SimpleITKBasicFilters1Source
  # These generate files have dependecies which required them to be in
  # the same library
  sitkMinimumMaximumImageFilter.cxx
  sitkLabelStatisticsImageFilter.cxx
  # Manually written
  sitkCastImageFilter-2.cxx
  sitkCastImageFilter-2l.cxx
  sitkCastImageFilter-2v.cxx
  sitkCastImageFilter-3.cxx
  sitkCastImageFilter-3l.cxx
  sitkCastImageFilter-3v.cxx
  sitkCastImageFilter.cxx
  sitkHashImageFilter.cxx
  sitkBSplineTransformInitializerFilter.cxx
  sitkCenteredTransformInitializerFilter.cxx
  sitkCenteredVersorTransformInitializerFilter.cxx
  sitkLandmarkBasedTransformInitializerFilter.cxx
)

add_library ( SimpleITKBasicFilters1 ${SimpleITKBasicFilters1Source} )
target_link_libraries ( SimpleITKBasicFilters1
  PUBLIC SimpleITKCommon SimpleITKBasicFilters0
  PRIVATE ${ITK_LIBRARIES} )
if (SITK_EXPLICIT_INSTANTIATION)
  target_link_libraries ( SimpleITKBasicFilters1 PRIVATE SimpleITKExplicit )
endif()
target_include_directories( SimpleITKBasicFilters1
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/BasicFilters/include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/Code/BasicFilters/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR} )

add_dependencies ( SimpleITKBasicFilters1 BasicFiltersSourceCode )
sitk_install_exported_target( SimpleITKBasicFilters1 )
list ( APPEND SimpleITK_LIBRARIES SimpleITKBasicFilters1 )


# sort the list to en-sure the same list across platforms
list ( SORT SimpleITKBasicFiltersGeneratedSource )

# Manually remove dependent files explicitly added first
list ( REMOVE_ITEM SimpleITKBasicFiltersGeneratedSource
                   "${CMAKE_CURRENT_BINARY_DIR}/sitkMinimumMaximumImageFilter.cxx"
                   "${CMAKE_CURRENT_BINARY_DIR}/sitkLabelStatisticsImageFilter.cxx" )

# add additional files which may depend on Filters0-N
list ( APPEND SimpleITKBasicFiltersSource ${SimpleITKBasicFiltersGeneratedSource} sitkAdditionalProcedures.cxx )

list ( LENGTH SimpleITKBasicFiltersSource _length )
math( EXPR _end_range "${_length} - 1 " )


# Break all these source files into a bunch of libraries base on every
# n files in the list.
set ( _stride 25 )
set ( _library_i 1 )
foreach ( _start RANGE 0 ${_end_range} ${_stride} )

  math( EXPR _library_i "${_library_i} + 1 " )

  # compute the end of the range ensuring that the inclusive range
  # [_start, _end] is all valid indexes
  math( EXPR _end "${_start} + ${_stride} - 1" )
  if ( ${_end} VERSION_GREATER ${_end_range} OR
      ${_end} VERSION_EQUAL ${_end_range} )
    math( EXPR _end "${_end_range}" )
    set(_last 1)
  endif()

  # extract out the range into SRC
  set ( SRC "" )
  foreach( _j RANGE ${_start} ${_end} )
    list ( GET SimpleITKBasicFiltersSource ${_j} _v )
    list ( APPEND SRC ${_v} )
  endforeach()

  add_library ( SimpleITKBasicFilters${_library_i} ${SRC} )
  target_link_libraries ( SimpleITKBasicFilters${_library_i}
    PUBLIC SimpleITKCommon SimpleITKBasicFilters0
    PRIVATE ${ITK_LIBRARIES} )
  if (SITK_EXPLICIT_INSTANTIATION)
    target_link_libraries ( SimpleITKBasicFilters${_library_i} PRIVATE SimpleITKExplicit )
  endif()
  if(_last)
    # the last library include additional cxx files which may depend on
    # other filter libraries
    target_link_libraries ( SimpleITKBasicFilters${_library_i}
      PRIVATE ${SimpleITK_LIBRARIES} )
  endif()
  target_include_directories( SimpleITKBasicFilters${_library_i}
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/BasicFilters/include>
      $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/Code/BasicFilters/include>
      $<INSTALL_INTERFACE:include>
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR} )
  if(BUILD_SHARED_LIBS)
    # These other filters are split into files. They all use the
    # following for export their interface. There must not be and
    # inter-filter include.
    target_compile_definitions(
      PRIVATE
        SimpleITKBasicFilters_EXPORTS )
  endif()

  add_dependencies ( SimpleITKBasicFilters${_library_i} BasicFiltersSourceCode )

  # append this new library to the globaly cached list
  list ( APPEND SimpleITK_LIBRARIES SimpleITKBasicFilters${_library_i} )
  set ( SimpleITK_LIBRARIES ${SimpleITK_LIBRARIES} CACHE INTERNAL "" )

  sitk_install_exported_target( SimpleITKBasicFilters${_library_i} )

endforeach ()
