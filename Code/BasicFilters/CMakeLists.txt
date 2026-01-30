# Set up code generation
include(sitkGenerateFilterSource)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/src)
generate_filter_source()

set_source_files_properties(
  ${SimpleITKBasicFiltersGeneratedSource}
  PROPERTIES
    GENERATED
      1
)

# _apply_basicfilters_common_properties
# Internal helper function to apply common compile options, features, and export
# settings to BasicFilters libraries
#
function(_apply_basicfilters_common_properties library_name)
  if(BUILD_SHARED_LIBS)
    target_compile_definitions(
      ${library_name}
      PRIVATE
        SimpleITKBasicFilters_EXPORTS
    )
  endif()

  target_compile_options(
    ${library_name}
    PUBLIC
      ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
    PRIVATE
      ${SimpleITK_PRIVATE_COMPILE_OPTIONS}
  )

  target_compile_features(${library_name} PUBLIC cxx_std_17)

  if(SimpleITK_EXPLICIT_INSTANTIATION)
    target_link_libraries(${library_name} PRIVATE SimpleITKExplicit)
  endif()

  sitk_install_exported_target(${library_name})

  cache_list_append(SimpleITK_LIBRARIES ${library_name})
endfunction()

# add_filter_library
# This function is used to apply standard building options for the
# libraries in the basic filters directory given a list of SimpleITK
# source files, and a list of ITK modules.
#
# This method is used to encapsulate the directory properties set when
# using an ITK module
#
function(add_filter_library library_name src_list_var itk_module_list_var)
  add_library(${library_name} ${${src_list_var}})

  target_link_libraries(
    ${library_name}
    PRIVATE
      ITK::${${itk_module_list_var}}Module
      ITK::ITKLabelMapModule
      ITK::ITKImageIntensityModule
  )

  target_link_libraries(
    ${library_name}
    PUBLIC
      SimpleITKCommon
      SimpleITKBasicFilters0
  )

  # Add headers using FILE_SET for automatic include directory management and installation
  # Extract itk_module from library_name (format: SimpleITK_<module>)
  string(REGEX REPLACE "^SimpleITK_" "" itk_module_name "${library_name}")

  # Add generated headers if they exist for this ITK module
  if(DEFINED SimpleITKBasicFiltersGeneratedHeader_${itk_module_name})
    target_sources(
      ${library_name}
      PUBLIC
        FILE_SET HEADERS
          BASE_DIRS
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_BINARY_DIR}/Code/BasicFilters/include
          FILES ${SimpleITKBasicFiltersGeneratedHeader_${itk_module_name}}
    )
  endif()

  # There are some miscellaneous hxx files that need to be included, but not installed
  target_include_directories(
    ${library_name}
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/src
  )

  _apply_basicfilters_common_properties(${library_name})

  # Add dependency to ensure source code is generated before building
  add_dependencies(${library_name} BasicFiltersSourceCode)
endfunction()

# common source which all basic filter libraries need to be linked against
set(SimpleITKBasicFilters0Source src/sitkImageFilter.cxx)

add_library(SimpleITKBasicFilters0 ${SimpleITKBasicFilters0Source})
target_link_libraries(
  SimpleITKBasicFilters0
  PRIVATE
    ITK::ITKCommonModule
  PUBLIC
    SimpleITKCommon
)

# Add headers using FILE_SET for automatic include directory management and installation
target_sources(
  SimpleITKBasicFilters0
  PUBLIC
    FILE_SET HEADERS
      BASE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}/include
      FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkImageFilter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkBasicFilters.h
        ${BasicFiltersGeneratedHeadersFiles}
)

_apply_basicfilters_common_properties(SimpleITKBasicFilters0)

# append this new library to the globally cached list
cache_list_append(SimpleITK_LIBRARIES SimpleITKBasicFilters0 )

# manually written
cache_list_append( SimpleITKBasicFiltersGeneratedSource_ITKCommon
  src/sitkCastImageFilter-2.cxx
  src/sitkCastImageFilter-2l.cxx
  src/sitkCastImageFilter-2v.cxx
  src/sitkCastImageFilter-3.cxx
  src/sitkCastImageFilter-3l.cxx
  src/sitkCastImageFilter-3v.cxx
  src/sitkCastImageFilter-4.cxx
  src/sitkCastImageFilter.cxx
  src/sitkExtractImageFilter.cxx
  src/sitkHashImageFilter.cxx
)

# Manually append headers for ITKCommon module
cache_list_append( SimpleITKBasicFiltersGeneratedHeader_ITKCommon
  ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkCastImageFilter.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkExtractImageFilter.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkHashImageFilter.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/itkHashImageFilter.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/itkHashImageFilter.hxx
)

cache_list_append( SimpleITKBasicFiltersGeneratedSource_ITKTransform
  src/sitkBSplineTransformInitializerFilter.cxx
)

# Manually append headers for ITKTransform module
cache_list_append( SimpleITKBasicFiltersGeneratedHeader_ITKTransform
  ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkBSplineTransformInitializerFilter.h
)

cache_list_append( SimpleITKBasicFiltersGeneratedSource_SimpleITKFilters
  src/sitkDICOMOrientImageFilter_Support.cxx
)

cache_list_append( SimpleITKBasicFiltersGeneratedSource_ITKImageGrid
  src/sitkPasteImageFilter.cxx
)

# Manually append headers for ITKImageGrid module
cache_list_append( SimpleITKBasicFiltersGeneratedHeader_ITKImageGrid
  ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkPasteImageFilter.h
)

cache_list_append( SimpleITKBasicFiltersGeneratedSource_ITKRegistrationCommon
  src/sitkCenteredTransformInitializerFilter.cxx
  src/sitkCenteredVersorTransformInitializerFilter.cxx
  src/sitkLandmarkBasedTransformInitializerFilter.cxx
)

# Manually append headers for ITKRegistrationCommon module
cache_list_append( SimpleITKBasicFiltersGeneratedHeader_ITKRegistrationCommon
  ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkCenteredTransformInitializerFilter.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkCenteredVersorTransformInitializerFilter.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkLandmarkBasedTransformInitializerFilter.h
)

#
# Module based libraries
#
get_cmake_property(_varNames CACHE_VARIABLES)
foreach(_varName ${_varNames})
  if(_varName MATCHES "^SimpleITKBasicFiltersGeneratedSource_")
    string(REGEX MATCH "[A-Za-z0-9]+$" itk_module ${_varName})
    list(APPEND module_vars ${itk_module})
  endif()
endforeach()

foreach(itk_module ${module_vars})
  if(${itk_module} IN_LIST ITK_MODULES_ENABLED)
    add_filter_library( SimpleITK_${itk_module}
                        SimpleITKBasicFiltersGeneratedSource_${itk_module}
                        itk_module
    )
  endif()

  if(SimpleITKBasicFiltersGeneratedSource_${itk_module})
    list(
      REMOVE_ITEM
      SimpleITKBasicFiltersGeneratedSource
      ${SimpleITKBasicFiltersGeneratedSource_${itk_module}}
    )
  endif()
endforeach()

# We should have dealt with all generated source files
list(SORT SimpleITKBasicFiltersGeneratedSource)
list(LENGTH SimpleITKBasicFiltersGeneratedSource _len)
if(_len GREATER 0)
  message(
    WARNING
    "Did not find module for source code: ${SimpleITKBasicFiltersGeneratedSource}"
  )
endif()

#
# Deal with files which may depend on any or all other filters.
#

# add additional files which may depend on other modules
list(
  APPEND
  SimpleITKBasicFilters1Source
  ${SimpleITKBasicFiltersGeneratedSource}
  src/sitkAdditionalProcedures.cxx
)

set(PREV_SimpleITK_LIBRARIES ${SimpleITK_LIBRARIES})

# Create SimpleITKBasicFilters1 manually (not using add_filter_library)
# because it needs FILE_SET to be added before export
add_library(SimpleITKBasicFilters1 ${SimpleITKBasicFilters1Source})

target_link_libraries(
  SimpleITKBasicFilters1
  PUBLIC
    SimpleITKCommon
    SimpleITKBasicFilters0
  PRIVATE
    ${PREV_SimpleITK_LIBRARIES}
    ITK::ITKLabelMapModule
    ITK::ITKImageIntensityModule
)

# Add headers using FILE_SET for automatic include directory management and installation
target_sources(
  SimpleITKBasicFilters1
  PUBLIC
    FILE_SET HEADERS
      BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
      FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkAdditionalProcedures.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sitkImageOperators.h
)

_apply_basicfilters_common_properties(SimpleITKBasicFilters1)
#add_dependencies(SimpleITKBasicFilters1 BasicFiltersSourceCode)
# Manual dependency needed to run the Cast filter
target_link_libraries(
  SimpleITK_ITKImageIntensity
  PRIVATE
    SimpleITK_ITKImageFilterBase
)

if(GenericLabelInterpolator IN_LIST ITK_MODULES_ENABLED)
  target_link_libraries(
    SimpleITK_ITKImageGrid
    PRIVATE
      ITK::GenericLabelInterpolatorModule
  )
endif()

target_link_libraries(SimpleITK_ITKFFT PRIVATE ITK::ITKFFTImageFilterInit)
target_link_libraries(
  SimpleITK_ITKConvolution
  PRIVATE
    ITK::ITKFFTImageFilterInit
)
target_link_libraries(
  SimpleITK_ITKDeconvolution
  PRIVATE
    ITK::ITKFFTImageFilterInit
)
