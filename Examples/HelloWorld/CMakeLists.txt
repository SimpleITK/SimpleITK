
add_executable ( HelloWorld HelloWorld.cxx )
target_link_libraries ( HelloWorld ${SimpleITK_LIBRARIES} )


if ( NOT BUILD_TESTING )
  return ()
endif ()

if ( NOT SimpleITK_TESTING_NOSHOW )

  sitk_add_test( NAME CXX.Example.HelloWorld
    COMMAND $<TARGET_FILE:HelloWorld>
    )

  sitk_add_csharp_test( Example.HelloWorld
    "${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld.cs"
    )

  sitk_add_java_test( Example.HelloWorld
    "${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld.java"
    )

  sitk_add_lua_test( Example.HelloWorld
    "${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld.lua"
    )

  sitk_add_python_test( Example.HelloWorld
    "${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld.py"
    )

  sitk_add_r_test( Example.HelloWorld
    "${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld.R"
    )

  sitk_add_ruby_test( Example.HelloWorld
    "${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld.rb"
    )

  sitk_add_tcl_test( Example.HelloWorld
    "${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld.tcl"
    )

endif ()
