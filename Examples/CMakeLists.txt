
include_directories ( ${SimpleITK_INCLUDE_DIR} )

add_executable ( SimpleGaussian SimpleGaussian.cxx )
target_link_libraries ( SimpleGaussian ${ITK_LIBRARIES} ${SimpleITK_LIBRARIES} )

add_executable ( Add Add.cxx )
target_link_libraries ( Add ${ITK_LIBRARIES} ${SimpleITK_LIBRARIES} )

add_executable ( BinaryThreshold BinaryThreshold.cxx )
target_link_libraries ( BinaryThreshold ${ITK_LIBRARIES} ${SimpleITK_LIBRARIES} )


if( WRAP_CSHARP )
  csharp_add_executable(
    SimpleGaussianCSharp
    SimpleITKCSharpManaged.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/SimpleGaussian.cs
  )
endif( WRAP_CSHARP )
