cmake_minimum_required(VERSION 3.14)

project(sitk_example)

find_package(SimpleITK)
add_executable ( sitk_example sitk_example.cxx )
target_link_libraries ( sitk_example ${SimpleITK_LIBRARIES} )
