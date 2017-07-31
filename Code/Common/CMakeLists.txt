
add_subdirectory( src )

# CMake option variable are prefixes with the project name "SimpleITK"
# while C++ preprocess defines only have SITK. These variable need the
# prefix translation.
set( SITK_INT64_PIXELIDS ${SimpleITK_INT64_PIXELIDS} )
set( SITK_4D_IMAGES ${SimpleITK_4D_IMAGES} )
set( SITK_EXPLICIT_INSTANTIATION ${SimpleITK_EXPLICIT_INSTANTIATION} )

include(sitkCheckTemplateDisambiguation)

configure_file( "src/sitkConfigure.h.in" "include/sitkConfigure.h" )
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/sitkConfigure.h"
  DESTINATION "${SimpleITK_INSTALL_INCLUDE_DIR}"
  COMPONENT Development)

configure_file("src/sitkVersionConfig.h.in" "include/sitkVersionConfig.h" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/sitkVersionConfig.h"
  DESTINATION "${SimpleITK_INSTALL_INCLUDE_DIR}"
  COMPONENT Development)
