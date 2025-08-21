add_executable(ImageGridManipulation ImageGridManipulation.cxx)
target_link_libraries(ImageGridManipulation ${SimpleITK_LIBRARIES})

if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_test(
  NAME CXX.Example.ImageGridManipulation
  COMMAND
    $<TARGET_FILE:ImageGridManipulation>
    DATA{${SimpleITK_DATA_ROOT}/Input/fruit.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/fruit.png}
)

sitk_add_csharp_test(
  Example.ImageGridManipulation
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageGridManipulation.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/fruit.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/fruit.png}
)

sitk_add_java_test(
  Example.ImageGridManipulation
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageGridManipulation.java"
  DATA{${SimpleITK_DATA_ROOT}/Input/fruit.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/fruit.png}
)

sitk_add_python_test(
  Example.ImageGridManipulation
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageGridManipulation.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/fruit.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/fruit.png}
)

sitk_add_r_test(
  Example.ImageGridManipulation
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageGridManipulation.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/fruit.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/fruit.png}
)
