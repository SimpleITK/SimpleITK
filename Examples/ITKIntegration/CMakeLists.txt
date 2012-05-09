
find_package(ITK REQUIRED ) 
include(${ITK_USE_FILE})

add_executable ( ITKIntegration ITKIntegration.cxx )
target_link_libraries ( ITKIntegration ${SimpleITK_LIBRARIES} )