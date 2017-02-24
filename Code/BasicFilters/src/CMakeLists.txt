set_source_files_properties ( ${SimpleITKBasicFiltersGeneratedSource} PROPERTIES GENERATED 1 )

function(add_filter_library library_name src_list_var)

  add_library ( ${library_name} ${${src_list_var}}  )

  target_link_libraries ( ${library_name}
    PUBLIC SimpleITKCommon SimpleITKBasicFilters0 )

  if (SimpleITK_EXPLICIT_INSTANTIATION)
    target_link_libraries ( ${library_name} PRIVATE SimpleITKExplicit )
  endif()

  target_include_directories( ${library_name}
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
    target_compile_definitions( ${library_name}
      PRIVATE
        SimpleITKBasicFilters_EXPORTS )
  endif()
  target_compile_options( ${library_name}
    PUBLIC
      ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
    PRIVATE
      ${SimpleITK_PRIVATE_COMPILE_OPTIONS} )

  add_dependencies ( ${library_name} BasicFiltersSourceCode )


  sitk_install_exported_target( ${library_name} )

  # append this new library to the globaly cached list
  list ( APPEND SimpleITK_LIBRARIES ${library_name} )
  set ( SimpleITK_LIBRARIES ${SimpleITK_LIBRARIES} CACHE INTERNAL "" )

endfunction()


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
if (SimpleITK_EXPLICIT_INSTANTIATION)
  target_link_libraries ( SimpleITKBasicFilters0 PRIVATE SimpleITKExplicit )
endif()
target_include_directories( SimpleITKBasicFilters0
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/BasicFilters/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR} )
target_compile_options( SimpleITKBasicFilters0
  PUBLIC
    ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS} )
sitk_install_exported_target( SimpleITKBasicFilters0 )

# append this new library to the globally cached list
list ( APPEND SimpleITK_LIBRARIES SimpleITKBasicFilters0 )
set ( SimpleITK_LIBRARIES ${SimpleITK_LIBRARIES} CACHE INTERNAL "" )

# manually written
list(APPEND SimpleITKBasicFiltersGeneratedSource_ITKCommon
  sitkCastImageFilter-2.cxx
  sitkCastImageFilter-2l.cxx
  sitkCastImageFilter-2v.cxx
  sitkCastImageFilter-3.cxx
  sitkCastImageFilter-3l.cxx
  sitkCastImageFilter-3v.cxx
  sitkCastImageFilter.cxx
  sitkHashImageFilter.cxx )
set(SimpleITKBasicFiltersGeneratedSource_ITKCommon ${SimpleITKBasicFiltersGeneratedSource_ITKCommon} CACHE INTERNAL "")

list(APPEND SimpleITKBasicFiltersGeneratedSource_ITKTransform
  sitkBSplineTransformInitializerFilter.cxx
  sitkCenteredTransformInitializerFilter.cxx
  sitkCenteredVersorTransformInitializerFilter.cxx
  sitkLandmarkBasedTransformInitializerFilter.cxx )
set(SimpleITKBasicFiltersGeneratedSource_ITKTransform ${SimpleITKBasicFiltersGeneratedSource_ITKTransform} CACHE INTERNAL "")

#
# Module based libraries
#
get_cmake_property( _varNames VARIABLES )
foreach (_varName ${_varNames})
  if(_varName MATCHES "^SimpleITKBasicFiltersGeneratedSource_")
    string(REGEX MATCH  "ITK[A-Za-z0-9]+$"  itk_module ${_varName})
    list(APPEND module_vars ${itk_module})
  endif()

endforeach()

foreach( itk_module ${module_vars} )

  # cmake >= 3.3
  # if( ${itk_module} IN_LIST ITK_MODULES_ENABLED)
  list (FIND ITK_MODULES_ENABLED ${itk_module} _index)
  if (${_index} GREATER -1)
    add_filter_library( SimpleITKBasicFilters_${itk_module} SimpleITKBasicFiltersGeneratedSource_${itk_module} )

    target_link_libraries ( SimpleITKBasicFilters_${itk_module}
      PRIVATE ${${itk_module}_LIBRARIES} )

    list( REMOVE_ITEM SimpleITKBasicFiltersGeneratedSource ${SimpleITKBasicFiltersGeneratedSource_${itk_module}})

  endif()

endforeach()

#
#
#

# sort the list to en-sure the same list across platforms
list ( SORT SimpleITKBasicFiltersGeneratedSource )

# add additional files which may depend on Filters0-N
list ( APPEND SimpleITKBasicFiltersSource ${SimpleITKBasicFiltersGeneratedSource} sitkAdditionalProcedures.cxx )

list ( LENGTH SimpleITKBasicFiltersSource _length )
math( EXPR _end_range "${_length} - 1 " )


# Break all these source files into a bunch of libraries base on every
# n files in the list.
set ( _stride 25 )
set ( _library_i 1 )
foreach ( _start RANGE 0 ${_end_range} ${_stride} )

  math( EXPR _library_i "${_library_i} " )

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

  add_filter_library(SimpleITKBasicFilters${_library_i} SRC )

  target_link_libraries ( SimpleITKBasicFilters${_library_i}
    PRIVATE ${ITK_LIBRARIES} )

  if(_last)

    set(_last_SimpleITK_LIBRARIES ${SimpleITK_LIBRARIES})
    list(REMOVE_ITEM _last_SimpleITK_LIBRARIES SimpleITKBasicFilters${_library_i})
    # the last library include additional cxx files which may depend on
    # other filter libraries
    target_link_libraries ( SimpleITKBasicFilters${_library_i}
      PRIVATE ${_last_SimpleITK_LIBRARIES} )
  endif()


endforeach ()
