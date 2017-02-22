if (SimpleITK_EXPLICIT_INSTANTIATION)
  add_subdirectory(Explicit)
endif()
add_subdirectory(Common)

add_subdirectory(BasicFilters)
add_subdirectory(IO)
add_subdirectory(Registration)
