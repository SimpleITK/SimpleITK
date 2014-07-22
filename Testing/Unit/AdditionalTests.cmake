
#
# Additional CXX tests
#
sitk_add_test(NAME TransformCompareDriver1
  COMMAND
    $<TARGET_FILE:sitkTransformCompareDriver>
    DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_-13x-17y.mha}
  )

sitk_add_test(NAME TransformCompareDriver2
  COMMAND
    ${CMAKE_COMMAND} -E echo "Running command"
  TRANSFORM_COMPARE
    DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_-13x-17y.mha}
  )


#
# Python Tests
#
sitk_add_python_test( Test.ImageTests
  "${SimpleITK_SOURCE_DIR}/Testing/Unit/sitkImageTests.py" )

sitk_add_python_test( Test.ImageIndexing
  "${SimpleITK_SOURCE_DIR}/Testing/Unit/ImageIndexingTest.py" )

sitk_add_python_test( Test.IOTest
  "${SimpleITK_SOURCE_DIR}/Testing/Unit/IOTest.py"
  "${TEST_HARNESS_TEMP_DIRECTORY}")

# Numpy test.
sitk_add_python_test( Test.Numpy
  "${SimpleITK_SOURCE_DIR}/Testing/Unit/sitkNumpyArrayConversionTest.py"
  )

sitk_add_python_test( Test.ProcessObject
  "${SimpleITK_SOURCE_DIR}/Testing/Unit/sitkProcessObjectTest.py"
  )


#
# Java Tests
#
sitk_add_java_test( ProcessObjectTest
  "${SimpleITK_SOURCE_DIR}/Testing/Unit/sitkProcessObjectTest.java" )


#
# R Tests
#
sitk_add_r_test( Arithmetic
  "--file=${SimpleITK_SOURCE_DIR}/Testing/Unit/RArithmeticTest.R"
  )


#
# CSharp Tests
#
sitk_add_csharp_test( Test.ImageTest
  "${SimpleITK_SOURCE_DIR}/Testing/Unit/CSharpImageTest.cs" )
