#
# R Tests
#
sitk_add_r_test( Arithmetic
  "${CMAKE_CURRENT_SOURCE_DIR}/RArithmeticTest.R"
  )
sitk_add_r_test( PixelIndexing
  "${CMAKE_CURRENT_SOURCE_DIR}/RPixelAccess.R"
  )
sitk_add_r_test( ImageListArguments
  "${CMAKE_CURRENT_SOURCE_DIR}/RImageListArguments.R"
  )
sitk_add_r_test( SwigVectorConversion
  "${CMAKE_CURRENT_SOURCE_DIR}/RSwigVectorConversionTests.R"
  )
sitk_add_r_test( ImageSlicing
  "${CMAKE_CURRENT_SOURCE_DIR}/RImageSlicingTests.R"
  )
sitk_add_r_test( Transform
  "${CMAKE_CURRENT_SOURCE_DIR}/RTransformTests.R"
  )
sitk_add_r_test( Image2Array2Image
  "${CMAKE_CURRENT_SOURCE_DIR}/R2Img2R.R"
  )
sitk_add_r_test( MethodExceptions
  "${CMAKE_CURRENT_SOURCE_DIR}/Rmethodexceptions.R"
  )
