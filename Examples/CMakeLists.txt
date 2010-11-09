

add_executable ( SimpleGaussian SimpleGaussian.cxx )
include_directories ( ${SimpleITK_INCLUDE_DIR} )

target_link_libraries ( SimpleGaussian ${ITK_LIBRARIES} ${SimpleITK_LIBRARIES} )
