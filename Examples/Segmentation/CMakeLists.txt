
include_directories ( ${SimpleITK_INCLUDE_DIR} )

# Add executable example targets
add_executable ( ConnectedThresholdImageFilter ConnectedThresholdImageFilter.cxx )
target_link_libraries ( ConnectedThresholdImageFilter ${ITK_LIBRARIES} ${SimpleITK_LIBRARIES} )

add_executable ( NeighborhoodConnectedImageFilter NeighborhoodConnectedImageFilter.cxx )
target_link_libraries ( NeighborhoodConnectedImageFilter ${ITK_LIBRARIES} ${SimpleITK_LIBRARIES} )
