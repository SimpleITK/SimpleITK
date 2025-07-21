# The ITK factories are already compiled into the SimpleITK
# libraries. So they are not needed again, additionally using ITK this
# way will not cause the headers to be generated, so the managers
# should not be used.

# set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
foreach(_f ${ITK_FACTORY_LIST})
  string(TOUPPER ${_f} _f)
  set(ITK_NO_${_f}_FACTORY_REGISTER_MANAGER 1)
endforeach()
include(${ITK_USE_FILE})

# Test data directory
set(TEST_HARNESS_TEMP_DIRECTORY ${SimpleITK_BINARY_DIR}/Testing/Temporary)
set(TEST_HARNESS_DATA_DIRECTORY ${ExternalData_BINARY_ROOT}/Testing/Data)

add_subdirectory(TestBase)

include(sitkUseGTest)
include(sitkGenerateFilterSource) # Include for get_config_path function

# Find tests generated in the binary directory
# To add a new file, just add it to this list.  Any GoogleTests inside will be automatically
# added to ctest.
set(
  SimpleITKUnitTestSource
  sitkImageTests.cxx
  sitkCommonTests.cxx
  sitkImageRegistrationMethodTests.cxx
  sitkImageIOTests.cxx
  sitkTypeListsTests.cxx
  sitkBasicFiltersTests.cxx
  sitkLabelStatisticsTest.cxx
  sitkTransformToDisplacementFieldFilterTest.cxx
  sitkTransformGeometryImageFilterTest.cxx
  sitkOperatorTests.cxx
  sitkExceptionsTests.cxx
  sitkTransformTests.cxx
  sitkImportImageTest.cxx
  itkHashImageFilterTest.cxx
  itkSliceImageFilterTest.cxx
  sitkImageViewerTest.cxx
  sitkDemonsRegistrationTests.cxx
)

if(SimpleITK_MAX_DIMENSION GREATER_EQUAL 4)
  list(APPEND SimpleITKUnitTestSource sitkImage4DTests.cxx)
endif()

if("SimpleITKFilters" IN_LIST ITK_MODULES_ENABLED)
  list(APPEND SimpleITKUnitTestSource sitkSimpleITKFiltersTests.cxx)
endif()

if(SimpleITK_USE_ELASTIX)
  list(
    APPEND
    SimpleITKUnitTestSource
    sitkParameterMapTests.cxx
    sitkElastixImageFilterTests.cxx
    sitkTransformixImageFilterTests.cxx
  )
endif()

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/sitkImageViewerTest.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/sitkImageViewerTest.h
  ESCAPE_QUOTES
)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CTest)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/PythonTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/LuaTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/TclTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/RTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/RubyTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/JavaTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CSharpTests)

# Adjust Python to run in the virtualenv
set(
  PythonVirtualenvHome
  ${SimpleITK_BINARY_DIR}/Testing/Installation/PythonVirtualenv
)

add_executable(
  SimpleITKUnitTestDriver0
  SimpleITKUnitTestDriver.cxx
  ${SimpleITKUnitTestSource}
)
target_include_directories(
  SimpleITKUnitTestDriver0
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
target_link_libraries(
  SimpleITKUnitTestDriver0
  GTest::GTest
  SimpleITKUnitTestBase
  ${SimpleITK_LIBRARIES}
  ${ITK_LIBRARIES}
)
target_compile_options(
  SimpleITKUnitTestDriver0
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS}
)

#
# Glob for necessary template files up front, before the foreach loop over
# the filters:
#
set(CXX_TEMPLATE_FILE sitkImageFilterTestTemplate.cxx.jinja)
set(LUA_TEMPLATE_FILE ImageFilterTestTemplate.lua.jinja)
set(PYTHON_TEMPLATE_FILE ImageFilterTestTemplate.py.jinja)
set(TCL_TEMPLATE_FILE ImageFilterTestTemplate.tcl.jinja)
set(R_TEMPLATE_FILE ImageFilterTestTemplate.R.jinja)
set(RUBY_TEMPLATE_FILE ImageFilterTestTemplate.rb.jinja)
set(JAVA_TEMPLATE_FILE ImageFilterTestTemplate.java.jinja)
set(CSHARP_TEMPLATE_FILE ImageFilterTestTemplate.cs.jinja)

#
# Generate code for the tests in different languages
#
# Break all these source files into a bunch of separate executables
# base on every n files in the list.
message(STATUS "Generating tests...")
set(_stride 50)
set(_exec_i 1) # exec 0 is the manual tests
set(_i 0)

# Initialize the list of all config file extensions we support
set(
  CONFIG_EXTENSIONS
  ".json"
  ".yaml"
  ".yml"
)

foreach(FILTERNAME ${GENERATED_FILTER_LIST})
  if(NOT _i LESS _stride)
    add_executable(
      SimpleITKUnitTestDriver${_exec_i}
      SimpleITKUnitTestDriver.cxx
      ${GENERATED_TEST_SOURCE}
    )
    target_link_libraries(
      SimpleITKUnitTestDriver${_exec_i}
      GTest::GTest
      SimpleITKUnitTestBase
      ${SimpleITK_LIBRARIES}
    )
    target_compile_options(
      SimpleITKUnitTestDriver${_exec_i}
      PRIVATE
        ${SimpleITK_PRIVATE_COMPILE_OPTIONS}
    )

    math(EXPR _exec_i "${_exec_i}+1")
    set(GENERATED_TEST_SOURCE "")
    set(_i 0)
  endif()

  # Set up some convenience variables - check for either JSON or YAML file
  # Define supported file extensions in order of preference
  set(
    CONFIG_EXTENSIONS
    ".json"
    ".yaml"
    ".yml"
  )

  # Initialize config file variable
  set(filter_config_file "")

  # Check for each extension in order of preference
  foreach(ext ${CONFIG_EXTENSIONS})
    set(
      potential_file
      ${SimpleITK_SOURCE_DIR}/Code/BasicFilters/json/${FILTERNAME}${ext}
    )
    if(EXISTS ${potential_file})
      set(filter_config_file ${potential_file})
      break()
    endif()
  endforeach()

  # For compatibility with existing code
  set(filter_json_file ${filter_config_file})

  ######
  # Figure out which template file gets used
  ######

  # Skip if the config file doesn't exist
  if(NOT EXISTS ${filter_json_file})
    message(
      STATUS
      "Skipping ${FILTERNAME} - no JSON or YAML configuration file found"
    )
    continue()
  endif()

  # Get the attribute from the config file that indicates the correct template
  get_config_path(template_name ${filter_json_file} "template_test_filename")

  if(template_name)
    set(
      OUTPUT_TEST_FILENAME
      "${SimpleITK_BINARY_DIR}/Testing/Unit/CTest/${FILTERNAME}.cmake"
    )
    file(REMOVE "${OUTPUT_TEST_FILENAME}")
    set(
      cmd
      ${SimpleITK_Python_EXECUTABLE}
      ${SimpleITK_EXPANSION_SCRIPT}
      ${filter_json_file}
      -D
      ${SimpleITK_SOURCE_DIR}/Testing/Unit/
      ImageFilterCTestTemplate.cmake.jinja
      "${OUTPUT_TEST_FILENAME}"
    )
    execute_process(COMMAND ${cmd} RESULT_VARIABLE failed ERROR_VARIABLE error)
    if(failed)
      string(REPLACE ";" " " cmd "${cmd}")
      message(
        FATAL_ERROR
        "Failed to generate \"${OUTPUT_TEST_FILENAME}\"\nCOMMAND: ${cmd} \n${error}"
      )
    endif()
    include("${OUTPUT_TEST_FILENAME}")

    set(
      OUTPUT_TEST_FILENAME
      "${SimpleITK_BINARY_DIR}/Testing/Unit/sitk${FILTERNAME}Test.cxx"
    )
    add_custom_command(
      OUTPUT
        ${OUTPUT_TEST_FILENAME}
      COMMAND
        ${SimpleITK_Python_EXECUTABLE} ${SimpleITK_EXPANSION_SCRIPT}
        ${filter_json_file} -D ${SimpleITK_SOURCE_DIR}/Testing/Unit/
        ${CXX_TEMPLATE_FILE} "${OUTPUT_TEST_FILENAME}"
      DEPENDS
        ${filter_json_file}
        ${CXX_TEMPLATE_FILE}
    )
    add_test(
      NAME BasicFilters.${FILTERNAME}
      COMMAND
        SimpleITKUnitTestDriver${_exec_i}
        --gtest_filter=BasicFilters.${FILTERNAME}:BasicFilters.${FILTERNAME}_*
    )
    set(
      GENERATED_TEST_SOURCE
      ${GENERATED_TEST_SOURCE}
      ${OUTPUT_TEST_FILENAME}
    )

    if(WRAP_LUA)
      set(
        OUTPUT_TEST_FILENAME
        "${SimpleITK_BINARY_DIR}/Testing/Unit/LuaTests/${FILTERNAME}Test.lua"
      )
      add_custom_command(
        OUTPUT
          "${OUTPUT_TEST_FILENAME}"
        COMMAND
          ${SimpleITK_Python_EXECUTABLE} ${SimpleITK_EXPANSION_SCRIPT}
          ${filter_json_file} -D ${SimpleITK_SOURCE_DIR}/Testing/Unit/
          ${LUA_TEMPLATE_FILE} "${OUTPUT_TEST_FILENAME}"
        DEPENDS
          ${filter_json_file}
          ${LUA_TEMPLATE_FILE}
      )
      set(
        WRAPPED_GENERATED_TEST_SOURCE
        ${WRAPPED_GENERATED_TEST_SOURCE}
        ${OUTPUT_TEST_FILENAME}
      )
    endif()

    if(WRAP_PYTHON)
      set(
        OUTPUT_TEST_FILENAME
        "${SimpleITK_BINARY_DIR}/Testing/Unit/PythonTests/${FILTERNAME}Test.py"
      )
      add_custom_command(
        OUTPUT
          "${OUTPUT_TEST_FILENAME}"
        COMMAND
          ${SimpleITK_Python_EXECUTABLE} ${SimpleITK_EXPANSION_SCRIPT}
          ${filter_json_file} -D ${SimpleITK_SOURCE_DIR}/Testing/Unit/
          ${PYTHON_TEMPLATE_FILE} "${OUTPUT_TEST_FILENAME}"
        DEPENDS
          ${filter_json_file}
          ${PYTHON_TEMPLATE_FILE}
      )
      set(
        WRAPPED_GENERATED_TEST_SOURCE
        ${WRAPPED_GENERATED_TEST_SOURCE}
        ${OUTPUT_TEST_FILENAME}
      )
    endif()

    if(WRAP_TCL)
      set(
        OUTPUT_TEST_FILENAME
        "${SimpleITK_BINARY_DIR}/Testing/Unit/TclTests/${FILTERNAME}Test.tcl"
      )
      add_custom_command(
        OUTPUT
          "${OUTPUT_TEST_FILENAME}"
        COMMAND
          ${SimpleITK_Python_EXECUTABLE} ${SimpleITK_EXPANSION_SCRIPT}
          ${filter_json_file} -D ${SimpleITK_SOURCE_DIR}/Testing/Unit/
          ${TCL_TEMPLATE_FILE} "${OUTPUT_TEST_FILENAME}"
        DEPENDS
          ${filter_json_file}
          ${TCL_TEMPLATE_FILE}
      )
      set(
        WRAPPED_GENERATED_TEST_SOURCE
        ${WRAPPED_GENERATED_TEST_SOURCE}
        ${OUTPUT_TEST_FILENAME}
      )
    endif()

    if(WRAP_R)
      set(
        OUTPUT_TEST_FILENAME
        "${SimpleITK_BINARY_DIR}/Testing/Unit/RTests/${FILTERNAME}Test.R"
      )
      add_custom_command(
        OUTPUT
          "${OUTPUT_TEST_FILENAME}"
        COMMAND
          ${SimpleITK_Python_EXECUTABLE} ${SimpleITK_EXPANSION_SCRIPT}
          ${filter_json_file} -D ${SimpleITK_SOURCE_DIR}/Testing/Unit/
          ${R_TEMPLATE_FILE} "${OUTPUT_TEST_FILENAME}"
        DEPENDS
          ${filter_json_file}
          ${R_TEMPLATE_FILE}
      )
      set(
        WRAPPED_GENERATED_TEST_SOURCE
        ${WRAPPED_GENERATED_TEST_SOURCE}
        ${OUTPUT_TEST_FILENAME}
      )
    endif()

    if(WRAP_RUBY)
      set(
        OUTPUT_TEST_FILENAME
        "${SimpleITK_BINARY_DIR}/Testing/Unit/RubyTests/${FILTERNAME}Test.rb"
      )
      add_custom_command(
        OUTPUT
          "${OUTPUT_TEST_FILENAME}"
        COMMAND
          ${SimpleITK_Python_EXECUTABLE} ${SimpleITK_EXPANSION_SCRIPT}
          ${filter_json_file} -D ${SimpleITK_SOURCE_DIR}/Testing/Unit/
          ${RUBY_TEMPLATE_FILE} "${OUTPUT_TEST_FILENAME}"
        DEPENDS
          ${filter_json_file}
          ${RUBY_TEMPLATE_FILE}
      )
      set(
        WRAPPED_GENERATED_TEST_SOURCE
        ${WRAPPED_GENERATED_TEST_SOURCE}
        ${OUTPUT_TEST_FILENAME}
      )
    endif()

    # Java Tests
    if(WRAP_JAVA)
      set(
        OUTPUT_TEST_FILENAME
        "${SimpleITK_BINARY_DIR}/Testing/Unit/JavaTests/${FILTERNAME}Test.java"
      )
      add_custom_command(
        OUTPUT
          "${OUTPUT_TEST_FILENAME}"
        COMMAND
          ${CMAKE_COMMAND} -E remove -f "${OUTPUT_TEST_FILENAME}"
        COMMAND
          ${SimpleITK_Python_EXECUTABLE} ${SimpleITK_EXPANSION_SCRIPT}
          ${filter_json_file} -D ${SimpleITK_SOURCE_DIR}/Testing/Unit/
          ${JAVA_TEMPLATE_FILE} "${OUTPUT_TEST_FILENAME}"
        DEPENDS
          ${filter_json_file}
          ${JAVA_TEMPLATE_FILE}
          ${SWIG_MODULE_SimpleITKJava_TARGET_NAME}
      )
      set(
        WRAPPED_GENERATED_TEST_SOURCE
        ${WRAPPED_GENERATED_TEST_SOURCE}
        ${OUTPUT_TEST_FILENAME}
      )
    endif()

    # C# Tests
    if(WRAP_CSHARP)
      set(
        OUTPUT_TEST_FILENAME
        "${SimpleITK_BINARY_DIR}/Testing/Unit/CSharpTests/${FILTERNAME}Test.cs"
      )
      add_custom_command(
        OUTPUT
          "${OUTPUT_TEST_FILENAME}"
        COMMAND
          ${CMAKE_COMMAND} -E remove -f "${OUTPUT_TEST_FILENAME}"
        COMMAND
          ${SimpleITK_Python_EXECUTABLE} ${SimpleITK_EXPANSION_SCRIPT}
          ${filter_json_file} -D ${SimpleITK_SOURCE_DIR}/Testing/Unit/
          ${CSHARP_TEMPLATE_FILE} "${OUTPUT_TEST_FILENAME}"
        DEPENDS
          ${filter_json_file}
          ${CSHARP_TEMPLATE_FILE}
      )
      set(
        WRAPPED_GENERATED_TEST_SOURCE
        ${WRAPPED_GENERATED_TEST_SOURCE}
        ${OUTPUT_TEST_FILENAME}
      )
    endif()
  endif() # if template_name
  math(EXPR _i "${_i}+1")
endforeach()

message(STATUS "Generating tests...Done")

add_executable(
  SimpleITKUnitTestDriver${_exec_i}
  SimpleITKUnitTestDriver.cxx
  ${GENERATED_TEST_SOURCE}
)
target_link_libraries(
  SimpleITKUnitTestDriver${_exec_i}
  GTest::GTest
  SimpleITKUnitTestBase
  ${SimpleITK_LIBRARIES}
)
target_compile_options(
  SimpleITKUnitTestDriver${_exec_i}
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS}
)

add_custom_target(
  WrappedGeneratedTests
  ALL
  DEPENDS
    ${WRAPPED_GENERATED_TEST_SOURCE}
)

if(MSVC_VERSION EQUAL 1700)
  # Tuples are limited by _VARIADIC_MAX in VS11. The variadic
  # templates are not deep enough by default. We are not currently
  # using the GTest features which require tuple, so just disable them
  # and hope that upstream permanently addresses the problem, without
  # required more CMake core for compiler issues.
  add_definitions(-DGTEST_HAS_TR1_TUPLE=0)
endif()

add_executable(sitkShowTest sitkShowTest.cxx)
target_link_libraries(
  sitkShowTest
  GTest::GTest
  ${SimpleITK_LIBRARIES}
  SimpleITKUnitTestBase
)
target_compile_options(
  sitkShowTest
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS}
)

add_executable(sitkSystemInformationTest sitkSystemInformationTest.cxx)
target_link_libraries(
  sitkSystemInformationTest
  ${SimpleITK_LIBRARIES}
  ${ITK_LIBRARIES}
)
add_test(
  NAME sitkSystemInformationTest
  COMMAND
    sitkSystemInformationTest ${CMAKE_BINARY_DIR}
)
target_compile_options(
  sitkSystemInformationTest
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS}
)

add_test(
  NAME sitkCMakeCacheTest
  COMMAND
    ${CMAKE_COMMAND} -E echo
    "Attaching file: \"${SimpleITK_BINARY_DIR}/CMakeCache.txt\""
)
set_tests_properties(
  sitkCMakeCacheTest
  PROPERTIES
    ATTACHED_FILES
      "${SimpleITK_BINARY_DIR}/CMakeCache.txt"
)

# CMake 3.10 added this method, to avoid configure time introspection
if(NOT CMAKE_CROSSCOMPILING)
  gtest_discover_tests(SimpleITKUnitTestDriver0 DISCOVERY_TIMEOUT 180)
else()
  gtest_add_tests(
    SimpleITKUnitTestDriver0
    ""
    ${SimpleITKUnitTestSource}
  )
endif()

ExternalData_Expand_Arguments(
  SimpleITKData
  unused_argument
  DATA{${SimpleITK_DATA_ROOT}/Input/xforms/affine_i_3.txt}
  DATA{${SimpleITK_DATA_ROOT}/Input/xforms/displacement_-13x-17y.txt}
  DATA{${SimpleITK_DATA_ROOT}/Input/xforms/quaternion_rigid_i_3.txt}
  DATA{${SimpleITK_DATA_ROOT}/Input/xforms/scale_logarithmic_i_3.txt}
  DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_i_3.txt}
  DATA{${SimpleITK_DATA_ROOT}/Input/xforms/composite_i_3.txt}
  DATA{${SimpleITK_DATA_ROOT}/Input/xforms/i_3.txt}
  DATA{${SimpleITK_DATA_ROOT}/Input/xforms/scale_i_3.txt}
  DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
  DATA{${SimpleITK_DATA_ROOT}/Input/xforms/versor_i_3.txt}
  DATA{${SimpleITK_DATA_ROOT}/Baseline/BasicFilters_TransformToDisplacementFieldFilter_defaults.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Baseline/BasicFilters_TransformToDisplacementFieldFilter_32.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Baseline/BasicFilters_TransformGeometryImageFilter_defaults.nrrd}
)

ExternalData_Expand_Arguments(
  SimpleITKData
  unused_argument
  DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.mha}
  DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/points_5d.mha}
  DATA{${SimpleITK_DATA_ROOT}/Input/4D.nii.gz}
  DATA{${SimpleITK_DATA_ROOT}/Input/BlackDots.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/cthead1-Float.mha}
  DATA{${SimpleITK_DATA_ROOT}/Input/cthead1.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Float.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Slice-Short.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/VM1111Shrink-RGB.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/WhiteDots.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
)

add_subdirectory(Python)
add_subdirectory(R)
add_subdirectory(Java)
add_subdirectory(CSharp)
