
add_subdirectory( src )

# CMake option variable are prefixes with the project name "SimpleITK"
# while C++ preprocess defines only have SITK. These variable need the
# prefix translation.
set( SITK_INT64_PIXELIDS ${SimpleITK_INT64_PIXELIDS} )
set( SITK_EXPLICIT_INSTANTIATION ${SimpleITK_EXPLICIT_INSTANTIATION} )
set( SITK_USE_ELASTIX ${SimpleITK_USE_ELASTIX} )
set( SITK_GENERIC_LABEL_INTERPOLATOR OFF)
if (GenericLabelInterpolator IN_LIST ITK_MODULES_ENABLED)
  set( SITK_GENERIC_LABEL_INTERPOLATOR ON)
endif()

include(sitkCheckTemplateDisambiguation)

configure_file( "src/sitkConfigure.h.in" "include/sitkConfigure.h" )
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/sitkConfigure.h"
  DESTINATION "${SimpleITK_INSTALL_INCLUDE_DIR}"
  COMPONENT Development)

configure_file("src/sitkVersionConfig.h.in" "include/sitkVersionConfig.h" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/sitkVersionConfig.h"
  DESTINATION "${SimpleITK_INSTALL_INCLUDE_DIR}"
  COMPONENT Development)
