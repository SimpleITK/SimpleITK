
add_executable ( FilterProgressReporting FilterProgressReporting.cxx )
target_link_libraries ( FilterProgressReporting ${SimpleITK_LIBRARIES} )

if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_test(NAME CXX.Example.FilterProgressReporting
  COMMAND $<TARGET_FILE:FilterProgressReporting>
    DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
    2.0
    "${SimpleITK_TEST_OUTPUT_DIR}/CXX.FilterProgressReporting.nrrd"
  )
set_tests_properties( CXX.Example.FilterProgressReporting
  PROPERTIES PASS_REGULAR_EXPRESSION "DiscreteGaussianImageFilter Progress" )

sitk_add_csharp_test( Example.FilterProgressReporting
  "${CMAKE_CURRENT_SOURCE_DIR}/FilterProgressReporting.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${SimpleITK_TEST_OUTPUT_DIR}/CSharp.FilterProgressReporting.nrrd"
  )
if( WRAP_CSHARP )
  set_tests_properties( CSharp.Example.FilterProgressReporting
    PROPERTIES PASS_REGULAR_EXPRESSION "DiscreteGaussianImageFilter Progress" )
endif()

sitk_add_java_test( Example.FilterProgressReporting
  "${CMAKE_CURRENT_SOURCE_DIR}/FilterProgressReporting.java"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${SimpleITK_TEST_OUTPUT_DIR}/Java.FilterProgressReporting.nrrd"
  )
if( WRAP_JAVA )
  set_tests_properties( Java.Example.FilterProgressReporting
    PROPERTIES PASS_REGULAR_EXPRESSION "DiscreteGaussianImageFilter Progress" )
endif()

sitk_add_python_test( Example.FilterProgressReporting
  "${CMAKE_CURRENT_SOURCE_DIR}/FilterProgressReporting.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${SimpleITK_TEST_OUTPUT_DIR}/PythonFilterProgressReporting.nrrd"
  )
if( WRAP_PYTHON )
  set_tests_properties( Python.Example.FilterProgressReporting
    PROPERTIES PASS_REGULAR_EXPRESSION "DiscreteGaussianImageFilter Progress" )
endif()


sitk_add_r_test( Example.FilterProgressReporting
  "${CMAKE_CURRENT_SOURCE_DIR}/FilterProgressReporting.R"
    DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
    2.0
    "${SimpleITK_TEST_OUTPUT_DIR}/R.FilterProgressReporting.nrrd"
  )
if( WRAP_R )
  set_tests_properties( R.Example.FilterProgressReporting
    PROPERTIES PASS_REGULAR_EXPRESSION "StartEvent" )
endif()

sitk_add_ruby_test( Example.FilterProgressReporting
  "${CMAKE_CURRENT_SOURCE_DIR}/FilterProgressReporting.rb"
    DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
    2.0
    "${SimpleITK_TEST_OUTPUT_DIR}/R.FilterProgressReporting.nrrd"
 )
if( WRAP_RUBY )
  set_tests_properties( Ruby.Example.FilterProgressReporting
    PROPERTIES PASS_REGULAR_EXPRESSION "DiscreteGaussianImageFilter Progress" )
endif()
