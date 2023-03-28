set_source_files_properties ( ${SimpleITKBasicFiltersGeneratedSource} PROPERTIES GENERATED 1 )

# add_filter_library
# This function is used to apply standard building options for the
# libraries in the basic filters directory given a list of SimpleITK
# source files, and a list of ITK modules.
#
# This method is used to encapsulate the directory properties set when
# using an ITK module
#
function(add_filter_library library_name src_list_var itk_module_list_var)

  add_library ( ${library_name} ${${src_list_var}}  )

  sitk_target_use_itk( ${library_name} PRIVATE ${${itk_module_list_var}}
    ITKLabelMap ITKImageIntensity)

  target_link_libraries ( ${library_name}
    PUBLIC
      SimpleITKCommon
      SimpleITKBasicFilters0 )

  if (SimpleITK_EXPLICIT_INSTANTIATION)
    target_link_libraries ( ${library_name} PRIVATE SimpleITKExplicit )
  endif()

  target_include_directories( ${library_name}
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/BasicFilters/include>
      $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/Code/BasicFilters/include>
      $<INSTALL_INTERFACE:${SimpleITK_INSTALL_INCLUDE_DIR}>
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
  target_compile_features( ${library_name} PUBLIC cxx_std_17 )

  add_dependencies ( ${library_name} BasicFiltersSourceCode )


  sitk_install_exported_target( ${library_name} )

  # append this new library to the globaly cached list
  cache_list_append(SimpleITK_LIBRARIES ${library_name} )

endfunction()


find_package(ITK COMPONENTS ITKCommon REQUIRED OPTIONAL_COMPONENTS ITKFFT )


# common source which all basic filter libraries need to be linked against
set ( SimpleITKBasicFilters0Source
  sitkImageFilter.cxx
)

add_library ( SimpleITKBasicFilters0 ${SimpleITKBasicFilters0Source} )
sitk_target_use_itk( SimpleITKBasicFilters0 PRIVATE ITKCommon)
target_link_libraries ( SimpleITKBasicFilters0
  PUBLIC
    SimpleITKCommon)
if (SimpleITK_EXPLICIT_INSTANTIATION)
  target_link_libraries ( SimpleITKBasicFilters0 PRIVATE SimpleITKExplicit )
endif()
target_include_directories( SimpleITKBasicFilters0
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/BasicFilters/include>
    $<INSTALL_INTERFACE:${SimpleITK_INSTALL_INCLUDE_DIR}>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR} )
target_compile_options( SimpleITKBasicFilters0
  PUBLIC
    ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS} )
target_compile_features( SimpleITKBasicFilters0 PUBLIC cxx_std_17 )
sitk_install_exported_target( SimpleITKBasicFilters0 )

# append this new library to the globally cached list
cache_list_append(SimpleITK_LIBRARIES SimpleITKBasicFilters0 )

# manually written
cache_list_append( SimpleITKBasicFiltersGeneratedSource_ITKCommon
  sitkCastImageFilter-2.cxx
  sitkCastImageFilter-2l.cxx
  sitkCastImageFilter-2v.cxx
  sitkCastImageFilter-3.cxx
  sitkCastImageFilter-3l.cxx
  sitkCastImageFilter-3v.cxx
  sitkCastImageFilter-4.cxx
  sitkCastImageFilter.cxx
  sitkExtractImageFilter.cxx
  sitkHashImageFilter.cxx )

cache_list_append( SimpleITKBasicFiltersGeneratedSource_ITKTransform
  sitkBSplineTransformInitializerFilter.cxx )

cache_list_append( SimpleITKBasicFiltersGeneratedSource_SimpleITKFilters
  sitkDICOMOrientImageFilter_Support.cxx)

cache_list_append( SimpleITKBasicFiltersGeneratedSource_ITKImageGrid
  sitkPasteImageFilter.cxx)

cache_list_append( SimpleITKBasicFiltersGeneratedSource_ITKRegistrationCommon
  sitkCenteredTransformInitializerFilter.cxx
  sitkCenteredVersorTransformInitializerFilter.cxx
  sitkLandmarkBasedTransformInitializerFilter.cxx )


#
# Module based libraries
#
get_cmake_property( _varNames CACHE_VARIABLES )
foreach (_varName ${_varNames})
  if(_varName MATCHES "^SimpleITKBasicFiltersGeneratedSource_")
    string(REGEX MATCH  "[A-Za-z0-9]+$"  itk_module ${_varName})
    list(APPEND module_vars ${itk_module})
  endif()

endforeach()

foreach( itk_module ${module_vars} )

  if( ${itk_module} IN_LIST ITK_MODULES_ENABLED)
    add_filter_library( SimpleITK_${itk_module}
                        SimpleITKBasicFiltersGeneratedSource_${itk_module}
                        itk_module )
  endif()

  if (SimpleITKBasicFiltersGeneratedSource_${itk_module})
      list( REMOVE_ITEM SimpleITKBasicFiltersGeneratedSource ${SimpleITKBasicFiltersGeneratedSource_${itk_module}})
  endif()

endforeach()


# We should have dealt with all generated source files
list ( SORT SimpleITKBasicFiltersGeneratedSource )
list(LENGTH SimpleITKBasicFiltersGeneratedSource _len)
if(_len GREATER 0)
  message(WARNING "Did not find module for source code: ${SimpleITKBasicFiltersGeneratedSource}")
endif()

#
# Deal with files which may depend on any or all other filters.
#

# add additional files which may depend on other modules
list(APPEND SimpleITKBasicFilters1Source ${SimpleITKBasicFiltersGeneratedSource} sitkAdditionalProcedures.cxx)

set(PREV_SimpleITK_LIBRARIES ${SimpleITK_LIBRARIES})

# No dependencies on ITK modules just SimpleITK
add_filter_library(SimpleITKBasicFilters1 SimpleITKBasicFilters1Source no_itk_deps)

target_link_libraries ( SimpleITKBasicFilters1
  PRIVATE ${PREV_SimpleITK_LIBRARIES} )

sitk_target_use_itk_factory( SimpleITK_ITKFFT FFTImageFilterInit )
sitk_target_use_itk_factory( SimpleITK_ITKConvolution FFTImageFilterInit )
sitk_target_use_itk_factory( SimpleITK_ITKDeconvolution FFTImageFilterInit )
