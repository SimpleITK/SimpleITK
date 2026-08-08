cmake_minimum_required(VERSION 3.23.0...3.31.0)
project(SimpleITKExamples)

if(NOT CMAKE_PROJECT_NAME STREQUAL "SimpleITK")
  find_package(SimpleITK REQUIRED)
endif()

option(
  SimpleITK_TESTING_NOSHOW
  "Disable the Show function in SimpleITK testing."
  ON
)
mark_as_advanced(SimpleITK_TESTING_NOSHOW)

add_executable(SimpleGaussianFunctional SimpleGaussianFunctional.cxx)
target_link_libraries(SimpleGaussianFunctional ${SimpleITK_LIBRARIES})

add_executable(BufferImportExport BufferImportExport.cxx)
target_link_libraries(BufferImportExport ${SimpleITK_LIBRARIES})

# Add subdirectories
add_subdirectory(Segmentation)

if(SimpleITK_USE_ELASTIX)
  add_subdirectory(Elastix)
endif()

# Test data directory
set(TEST_HARNESS_TEMP_DIRECTORY ${SimpleITK_BINARY_DIR}/Testing/Temporary)

# Add example organized sub-directories with multiple languages
add_subdirectory(HelloWorld)
add_subdirectory(FastMarchingSegmentation)
add_subdirectory(SimpleGaussian)
add_subdirectory(SimpleIO)
add_subdirectory(ImageGridManipulation)
add_subdirectory(ImageIOSelection)
add_subdirectory(ImageRegistrationMethod1)
add_subdirectory(ImageRegistrationMethod2)
add_subdirectory(ImageRegistrationMethod3)
add_subdirectory(ImageRegistrationMethod4)
add_subdirectory(ImageRegistrationOptimizerWeights)
add_subdirectory(ImageRegistrationMethodBSpline1)
add_subdirectory(ImageRegistrationMethodBSpline2)
add_subdirectory(ImageRegistrationMethodBSpline3)
add_subdirectory(ImageRegistrationMethodDisplacement1)
add_subdirectory(ImageRegistrationMethodExhaustive)
add_subdirectory(LandmarkRegistration)
add_subdirectory(N4BiasFieldCorrection)
add_subdirectory(DicomSeriesReader)
add_subdirectory(DicomImagePrintTags)
add_subdirectory(DicomSeriesReadModifyWrite)
add_subdirectory(DicomConvert)
add_subdirectory(FilterProgressReporting)
add_subdirectory(DemonsRegistration1)
add_subdirectory(DemonsRegistration2)
add_subdirectory(RawImageReading)
add_subdirectory(CppCMake)
add_subdirectory(CppInPlace)
add_subdirectory(SliceBySliceDecorator)
add_subdirectory(Logging)

# ---------------------------------------------------------------------------
# Generated filter examples
#
# The GenerateFilterExamples target expands Jinja2 templates for every filter
# listed in example_filter_list.yaml and writes the output into
# Examples/<FilterName>/ in the source tree.
#
# Run the target once (or whenever filter YAMLs or templates change) to
# regenerate the files:
#
#   cmake --build <build-dir> --target GenerateFilterExamples
#
# After generation, each filter subdirectory is picked up automatically by
# the add_subdirectory loop below.
# ---------------------------------------------------------------------------

if(CMAKE_PROJECT_NAME STREQUAL "SimpleITK")
  include(sitkGenerateExamples)
  sitk_generate_filter_examples()
endif()

# Add every generated filter example subdirectory that already exists on disk.
set(
  _sitk_example_filter_list
  "${CMAKE_CURRENT_SOURCE_DIR}/example_filter_list.yaml"
)
if(EXISTS "${_sitk_example_filter_list}")
  # Resolve a Python interpreter for YAML parsing (may not be set in standalone mode).
  if(DEFINED SimpleITK_Python_EXECUTABLE)
    set(_sitk_py "${SimpleITK_Python_EXECUTABLE}")
  elseif(DEFINED Python_EXECUTABLE)
    set(_sitk_py "${Python_EXECUTABLE}")
  else()
    find_package(Python 3.9...<4 QUIET COMPONENTS Interpreter)
    set(_sitk_py "${Python_EXECUTABLE}")
  endif()

  execute_process(
    COMMAND
      "${_sitk_py}" -c
      "import sys, yaml\n\
try:\n\
    from yaml import CSafeLoader as Loader\n\
except ImportError:\n\
    from yaml import SafeLoader as Loader\n\
data = yaml.load(open(sys.argv[1]), Loader=Loader)\n\
print(';'.join(str(f) for f in data.get('filters', [])))"
      "${_sitk_example_filter_list}"
    OUTPUT_VARIABLE _sitk_generated_filters
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
  )
  foreach(_sitk_filter IN LISTS _sitk_generated_filters)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${_sitk_filter}/CMakeLists.txt")
      add_subdirectory("${_sitk_filter}")
    endif()
  endforeach()
  unset(_sitk_generated_filters)
  unset(_sitk_filter)
endif()
unset(_sitk_example_filter_list)
unset(_sitk_py)

macro(add_language_subdirectory lang)
  string(TOUPPER ${lang} LANG)
  if(WRAP_${LANG})
    add_subdirectory(${lang})
  endif()
endmacro()

if(BUILD_TESTING)
  add_subdirectory(test)

  add_language_subdirectory( Java )
  add_language_subdirectory( CSharp )
  add_language_subdirectory( Python )
endif()
