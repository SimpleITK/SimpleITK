cmake_minimum_required(VERSION 2.8)
project(SimpleITKSegmentationExamples)

if(NOT SimpleITK_SOURCE_DIR)
  find_package(SimpleITK REQUIRED)
  include(${SimpleITK_USE_FILE})
endif()

# Add executable example targets
add_executable ( ConnectedThresholdImageFilter ConnectedThresholdImageFilter.cxx )
target_link_libraries ( ConnectedThresholdImageFilter ${SimpleITK_LIBRARIES} )

add_executable ( NeighborhoodConnectedImageFilter NeighborhoodConnectedImageFilter.cxx )
target_link_libraries ( NeighborhoodConnectedImageFilter ${SimpleITK_LIBRARIES} )
