
include_directories ( ${SimpleITK_INCLUDE_DIR} )

# Add individual cxx executables
add_executable ( SimpleGaussian SimpleGaussian.cxx )
target_link_libraries ( SimpleGaussian ${SimpleITK_LIBRARIES} )

add_executable ( SimpleGaussianFunctional SimpleGaussianFunctional.cxx )
target_link_libraries ( SimpleGaussianFunctional ${SimpleITK_LIBRARIES} )

add_executable ( ITKIntegration ITKIntegration.cxx )
target_link_libraries ( ITKIntegration ${SimpleITK_LIBRARIES} )

# Add individual c# executables
if( WRAP_CSHARP )
  csharp_add_executable(
    SimpleGaussianCSharp
    SimpleITKCSharpManaged.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/SimpleGaussian.cs
  )
endif( WRAP_CSHARP )

#
# Go into testing subdirectory
#
add_subdirectory(Segmentation)
