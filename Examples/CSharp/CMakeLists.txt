
if(NOT BUILD_TESTING)
  return()
endif()

#
# CSharp Examples
#

sitk_add_csharp_test( Example.ImageGetBuffer
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageGetBuffer.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd})
set_tests_properties( CSharp.Example.ImageGetBuffer
  PROPERTIES PASS_REGULAR_EXPRESSION "total: 1009713" )
