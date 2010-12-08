
include_directories ( ${SimpleITK_INCLUDE_DIR} )

add_executable ( ConnectedThresholdImageFilter ConnectedThresholdImageFilter.cxx )
target_link_libraries ( ConnectedThresholdImageFilter ${ITK_LIBRARIES} ${SimpleITK_LIBRARIES} )
