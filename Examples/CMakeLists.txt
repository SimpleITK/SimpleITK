
# remove me
include(${ITK_USE_FILE})

include_directories ( ${SimpleITK_INCLUDE_DIRS} )

# Add individual cxx executables
add_executable ( SimpleGaussian SimpleGaussian.cxx )
target_link_libraries ( SimpleGaussian ${SimpleITK_LIBRARIES} )

add_executable ( SimpleGaussianFunctional SimpleGaussianFunctional.cxx )
target_link_libraries ( SimpleGaussianFunctional ${SimpleITK_LIBRARIES} )

add_executable ( ITKIntegration ITKIntegration.cxx )
target_link_libraries ( ITKIntegration ${SimpleITK_LIBRARIES} )

add_executable ( BufferImportExport BufferImportExport.cxx )
target_link_libraries ( BufferImportExport ${SimpleITK_LIBRARIES} )

# Add individual C# executables
if( WRAP_CSHARP )
  csharp_add_executable(
    ExampleSimpleGaussian
    SimpleITKCSharpManaged.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/SimpleGaussian.cs
  )
  add_dependencies(ExampleSimpleGaussian SimpleITKCSharpManaged)
endif( WRAP_CSHARP )

# Add subdirectories
add_subdirectory(Segmentation)
