#
# Python Tests
#
sitk_add_python_test( Test.ImageTests
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkImageTests.py" )

sitk_add_python_test( Test.ImageIndexing
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageIndexingTest.py" )

sitk_add_python_test( Test.IOTest
  "${CMAKE_CURRENT_SOURCE_DIR}/IOTest.py"
  "${SimpleITK_TEST_OUTPUT_DIR}")

# Numpy test.
sitk_add_python_test( Test.Numpy
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkNumpyArrayConversionTest.py"
  )

sitk_add_python_test( Test.ProcessObject
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkProcessObjectTest.py"
  )

sitk_add_python_test( Test.ConcurrentImageRead
  "${CMAKE_CURRENT_SOURCE_DIR}/ConcurrentImageRead.py"
  )


if(CMAKE_VERSION VERSION_GREATER "3.3")
  if(TEST Python.Test.ConcurrentImageRead)
    set_tests_properties( Python.Test.ConcurrentImageRead PROPERTIES LABELS "UNSTABLE" )
    endif()
endif()

sitk_add_python_test( Test.ArrayView
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkGetArrayViewFromImageTest.py"
  )

