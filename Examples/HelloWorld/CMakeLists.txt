
add_executable ( HelloWorld HelloWorld.cxx )
target_link_libraries ( HelloWorld ${SimpleITK_LIBRARIES} )


if ( WRAP_CSHARP )
  csharp_add_executable( HelloWorldCS SimpleITKCSharpManaged.dll ${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld.cs )
endif ()
