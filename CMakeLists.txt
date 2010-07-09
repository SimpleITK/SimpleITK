project ( SimpleITK )
cmake_minimum_required ( VERSION 2.8 )

find_package(ITK REQUIRED)
if(ITK_FOUND)
  include(${ITK_USE_FILE})
endif()

set ( SimpleITK_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Source)
set ( SimpleITK_LIBRARIES SimpleITK ${ITK_LIBRARIES} )
subdirs ( Source Wrapping Examples )
