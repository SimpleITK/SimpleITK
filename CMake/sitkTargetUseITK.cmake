# target_use_itk
#
# This function has the following form: sitk_target_use_itk(<target> <PRIVATE|PUBLIC|INTERFACE> [itk_module [itk_module
# [...]]])
#
# It configures the target, with the require include directories and link libraries to use the list of itk modules
# provided. The keyword to indicate interface of the library is also required.

function(sitk_target_use_itk target_name interface_keyword)

  set(itk_modules ${ARGV})
  list(
    REMOVE_AT
    itk_modules
    0
    1)

  itk_module_config(_itk ${itk_modules})

  if(_itk_LIBRARY_DIRS)
    link_libraries(${_itk_LIBRARY_DIRS})
  endif()

  if(_itk_LIBRARIES)
    target_link_libraries(${target_name} ${interface_keyword} ${_itk_LIBRARIES})
  endif()
  if(_itk_INCLUDE_DIRS)
    target_include_directories(${target_name} ${interface_keyword} ${_itk_INCLUDE_DIRS})
  endif()

endfunction()

function(sitk_target_use_itk_factory target_name factory_name)

  list(
    FIND
    ITK_FACTORY_LIST
    "${factory_name}"
    _index)
  if(_index EQUAL -1)
    message(FATAL_ERROR "Factory \"${factory_name}\" not contained in ITK_FACTORY_LIST: \"${ITK_FACTORY_LIST}\"")
  endif()

  itk_generate_factory_registration(${factory_name})

  string(TOUPPER ${factory_name} factory_uc)

  target_compile_definitions(${target_name} PRIVATE ITK_${factory_uc}_FACTORY_REGISTER_MANAGER)

  target_include_directories(${target_name} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/ITKFactoryRegistration")
endfunction()
