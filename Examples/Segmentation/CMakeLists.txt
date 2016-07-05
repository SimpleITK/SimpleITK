
# Add executable example targets
add_executable ( ConnectedThresholdImageFilter ConnectedThresholdImageFilter.cxx )
target_link_libraries ( ConnectedThresholdImageFilter ${SimpleITK_LIBRARIES} )

add_executable ( NeighborhoodConnectedImageFilter NeighborhoodConnectedImageFilter.cxx )
target_link_libraries ( NeighborhoodConnectedImageFilter ${SimpleITK_LIBRARIES} )
