cmake_minimum_required(VERSION 2.8)
project(SimpleITKExamples)

if(NOT SimpleITK_SOURCE_DIR)
  find_package(SimpleITK REQUIRED)
  include(${SimpleITK_USE_FILE})
endif()

# Add individual cxx executables
add_executable ( SimpleGaussian SimpleGaussian.cxx )
target_link_libraries ( SimpleGaussian ${SimpleITK_LIBRARIES} )

add_executable ( SimpleGaussianFunctional SimpleGaussianFunctional.cxx )
target_link_libraries ( SimpleGaussianFunctional ${SimpleITK_LIBRARIES} )

add_executable ( ITKIntegration ITKIntegration.cxx )
target_link_libraries ( ITKIntegration ${SimpleITK_LIBRARIES} )

add_executable ( BufferImportExport BufferImportExport.cxx )
target_link_libraries ( BufferImportExport ${SimpleITK_LIBRARIES} )

# Add subdirectories
add_subdirectory(Segmentation)
