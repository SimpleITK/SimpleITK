
# The example code and CMakeLists.txt file is in the Source
# subdirectory to have a plain CMakeLists.txt file.  This
# CMakeList.txt file is to compile sitk_example.cxx for the
# SimpleITK tests.  Source/CMakeLists.txt is not automatically
# tested.

add_executable ( sitk_example Source/sitk_example.cxx )
target_link_libraries ( sitk_example ${SimpleITK_LIBRARIES} )


if ( NOT BUILD_TESTING )
  return ()
endif ()

if ( NOT SimpleITK_TESTING_NOSHOW )

  sitk_add_test( NAME CXX.Example.sitk_example
    COMMAND $<TARGET_FILE:sitk_example>
    )

endif ()
