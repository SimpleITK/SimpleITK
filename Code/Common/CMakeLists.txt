
add_subdirectory( src )

configure_file( "src/sitkConfigure.h.in" "include/sitkConfigure.h" )
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/sitkConfigure.h"
  DESTINATION "${SimpleITK_INSTALL_INCLUDE_DIR}"
  COMPONENT Development)

configure_file("src/sitkVersionConfig.h.in" "include/sitkVersionConfig.h" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/sitkVersionConfig.h"
  DESTINATION "${SimpleITK_INSTALL_INCLUDE_DIR}"
  COMPONENT Development)
