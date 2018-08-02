
foreach(p
    CMP0064 # CMake 3.4
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()


#
# Java Tests
#
sitk_add_java_test( ProcessObjectTest
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkProcessObjectTest.java" )

sitk_add_java_test( ImageTests
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkImageTests.java" )
