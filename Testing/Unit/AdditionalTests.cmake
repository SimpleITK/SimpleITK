
#-----------------------------------------------------------------------------
# SimpleITK wrapper for add_test that automatically adds testing data...

function(sitk_add_test)
  # Add tests with data in the SimpleITKData group.
  ExternalData_add_test(SimpleITKData ${ARGN})

  if("NAME" STREQUAL "${ARGV0}")
    set(_iat_testname ${ARGV1})
  else()
    set(_iat_testname ${ARGV0})
  endif()

endfunction()


set(SITK_DATA_ROOT ${SimpleITK_SOURCE_DIR}/Testing/Data)

#
# Additional CXX tests
#
sitk_add_test(NAME TransformCompareDriver1
  COMMAND
    $<TARGET_FILE:sitkTransformCompareDriver>
    DATA{${SITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
    DATA{${SITK_DATA_ROOT}/Baseline/displacement_-13x-17y.mha}
    DATA{${SITK_DATA_ROOT}/Input/cthead1-Float.mha}
    )



if ( WRAP_PYTHON )

  #
  # This is a function which set up the enviroment for executing python examples and tests
  #
  function(add_python_test name)

    if ( NOT ${BUILD_EXAMPLES} AND "${name}" MATCHES "^Example." )
      return()
    endif()

    set(command "${VIRTUAL_PYTHON_EXECUTABLE}")

    # add extra command which may be needed on some systems
    if(CMAKE_OSX_ARCHITECTURES)
      list(GET CMAKE_OSX_ARCHITECTURES 0 test_arch)
      set(command arch -${test_arch} ${command})
    endif()

    sitk_add_test(NAME Python.${name}
      COMMAND "${ITK_TEST_DRIVER}"
      --add-before-env SITK_NOSHOW "YES"
      ${command}
      ${ARGN}
      )
  endfunction()

  #
  # Python Examples
  #
  add_python_test( Example.SimpleGaussian
    "${SimpleITK_SOURCE_DIR}/Examples/SimpleGaussian.py"
    --compare
      "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussian.nrrd"
      DATA{${SITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd}
    DATA{${SITK_DATA_ROOT}/Input/RA-Short.nrrd}
    "2.0"
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussian.nrrd" )

  add_python_test( Example.SimpleGaussianProcedural
    "${SimpleITK_SOURCE_DIR}/Examples/SimpleGaussianProcedural.py"
    --compare
      "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussianProcedural.nrrd"
      DATA{${SITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd}
    DATA{${SITK_DATA_ROOT}/Input/RA-Short.nrrd}
    "2.0"
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussianProcedural.nrrd" )

  add_python_test( Example.ImageCreateAndSet
    "${SimpleITK_SOURCE_DIR}/Examples/ImageCreateAndSet.py" )

  add_python_test( Example.CannyEdge
    "${SimpleITK_SOURCE_DIR}/Examples/CannyEdge.py"
    DATA{${SITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd} )

  add_python_test( Example.ExtractSlice
    "${SimpleITK_SOURCE_DIR}/Examples/ExtractSlice.py"
    DATA{${SITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
    "30"
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.ExtractSlice.nrrd")

  add_python_test( Example.BoarderSegmentation
    "${SimpleITK_SOURCE_DIR}/Examples/BoarderSegmentation.py"
    DATA{${SITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.BoarderSegmentation.nrrd"
    "5000"
    "150" )

 add_python_test( Example.N4BiasFieldCorrection
    "${SimpleITK_SOURCE_DIR}/Examples/N4BiasFieldCorrection.py"
    DATA{${SITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.Example.N4BiasFieldCorrection.nrrd"
    "1" )

  add_python_test( Example.ReadAndShow
    "${SimpleITK_SOURCE_DIR}/Examples/ReadAndShow.py"
    DATA{${SITK_DATA_ROOT}/Input/VM1111Shrink-RGB.png} )

  add_python_test( Example.GeodesicActiceContourSegmentation
    "${SimpleITK_SOURCE_DIR}/Examples/GeodesicActiceContourSegmentation.py"
    DATA{${SITK_DATA_ROOT}/Input/cthead1.png}
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.Example.GeodesicActiceContourSegmentation.nrrd"
    .3 10 .9 50 55
    )

  add_python_test( Example.FFTConvolution
    "${SimpleITK_SOURCE_DIR}/Examples/FFTConvolution.py"
    DATA{${SITK_DATA_ROOT}/Input/cthead1-Float.mha}
    DATA{${SITK_DATA_ROOT}/Input/Gaussian_1.5.nrrd}
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.Examples.FFTConvolution.nrrd"
    )

  add_python_test( Example.FilterProgressReporting
    "${SimpleITK_SOURCE_DIR}/Examples/FilterProgressReporting.py"
    DATA{${SITK_DATA_ROOT}/Input/RA-Short.nrrd}
    "2.0"
    "${TEST_HARNESS_TEMP_DIRECTORY}/PythonFilterProgressReporting.nrrd"
    )

  add_python_test( Example.DicomSeriesReader
    "${SimpleITK_SOURCE_DIR}/Examples/DicomSeriesReader.py"
    --compare-MD5
    "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader.nrrd"
    "8e65f711d450b6b466c6d76a667ecb72"
      DATA{${SITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
      "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader.nrrd"
    )

  set_tests_properties( Python.Example.FilterProgressReporting
    PROPERTIES PASS_REGULAR_EXPRESSION "DiscreteGaussianImageFilter Progress" )

  add_python_test( Example.Segmentation.ConnectedThresholdImageFilter1
    "${SimpleITK_SOURCE_DIR}/Examples/Segmentation/ConnectedThresholdImageFilter.py"
    --compare-MD5
      "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold1.png"
      "d4ff9c512f9c18a84729677de800db0d"
    DATA{${SITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
    "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold1.png"
    150 180
    60 116
    )

  add_python_test( Example.Segmentation.ConnectedThresholdImageFilter2
    "${SimpleITK_SOURCE_DIR}/Examples/Segmentation/ConnectedThresholdImageFilter.py"
    --compare-MD5
      "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold2.png"
      "a9695df04cde5b9c5481d8c253a5b3aa"
    DATA{${SITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
    "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold2.png"
    210 250
    81 112
    )

  add_python_test( Example.Segmentation.NeighborhoodConnectedImageFilter1
    "${SimpleITK_SOURCE_DIR}/Examples/Segmentation/NeighborhoodConnectedImageFilter.py"
    --compare-MD5
      "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationNeighborhoodConnected1.png"
      "311d9d4b492e1ea625e3b0b295814dce"
    DATA{${SITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
    "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationNeighborhoodConnected1.png"
    150 180
    60 116
    )

  add_python_test( Example.ImageRegistrationMethod1
    "${SimpleITK_SOURCE_DIR}/Examples/ImageRegistrationMethod1.py"
    DATA{${SITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod11Test.hdf5
    )

  add_python_test( Example.ImageRegistrationMethod2
    "${SimpleITK_SOURCE_DIR}/Examples/ImageRegistrationMethod2.py"
    DATA{${SITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod2Test.hdf5
    )

  add_python_test( Example.ImageRegistrationMethod4Test1
    "${SimpleITK_SOURCE_DIR}/Examples/ImageRegistrationMethod4.py"
    DATA{${SITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod4Test1.hdf5
    24 1.0
    )

  add_python_test( Example.ImageRegistrationMethod4Test2
    "${SimpleITK_SOURCE_DIR}/Examples/ImageRegistrationMethod4.py"
    DATA{${SITK_DATA_ROOT}/Input/BrainT1SliceBorder20.png}
    DATA{${SITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod4Test2.hdf5
    24 0.1
    )

  add_python_test( Example.ImageRegistrationMethod4Test3
    "${SimpleITK_SOURCE_DIR}/Examples/ImageRegistrationMethod4.py"
    DATA{${SITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20Mask.png}
    DATA{${SITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20Mask.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod4Test3.hdf5
    5 0.4
    )



  add_python_test(Example.DemonsRegistration1
      "${SimpleITK_SOURCE_DIR}/Examples/DemonsRegistration1.py"
      DATA{${SITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
      DATA{${SITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
      ${TEST_HARNESS_TEMP_DIRECTORY}/PythonDemonsRegistration1Test.hdf5
    )

  add_python_test(Example.DemonsRegistration2
      "${SimpleITK_SOURCE_DIR}/Examples/DemonsRegistration2.py"
      DATA{${SITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
      DATA{${SITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
      DATA{${SITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
      ${TEST_HARNESS_TEMP_DIRECTORY}/PythonDemonsRegistration2Test.hdf5
    )


  #
  # Python Tests
  #
  add_python_test( Test.ImageTests
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/sitkImageTests.py" )
  add_python_test( Test.ImageIndexing
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/ImageIndexingTest.py" )

  add_python_test( Test.IOTest
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/IOTest.py"
    "${TEST_HARNESS_TEMP_DIRECTORY}")

  # Numpy test.
  add_python_test( Test.Numpy
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/sitkNumpyArrayConversionTest.py"
  )

 add_python_test( Test.ProcessObject
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/sitkProcessObjectTest.py"
  )



endif( WRAP_PYTHON )
