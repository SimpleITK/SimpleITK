# target_use_itk
#
# This function has the following form:
#   sitk_target_use_itk(<target>
#                       <PRIVATE|PUBLIC|INTERFACE>
#                       [itk_module [itk_module [...]]])
#
#   It configures the target, with the require include directories and
# link libraries to use the list of itk modules provided. The keyword
# to indicate interface of the library is also required.

function(sitk_target_use_itk target_name interface_keyword)
  set(itk_modules ${ARGV})
  list(
    REMOVE_AT
    itk_modules
    0
    1
  )

  # Debug: inspect first ITK module
  list(LENGTH itk_modules num_modules)
  message(STATUS "sitk_target_use_itk: Target: ${target_name}")
  message(STATUS "sitk_target_use_itk: Number of ITK modules: ${num_modules}")
  message(STATUS "sitk_target_use_itk: ITK modules: ${itk_modules}")

  # check if all the interface modules are available
  set(_use_itk_interface_modules 1)
  foreach(module ${itk_modules})
    if(NOT TARGET ITK::${module}Module)
      # Check of the requested module is a factory meta-module
      # Remove ITK prefix from module name to match factory list
      # ITK modules are specified with ITK prefix (e.g., ITKImageIO)
      # but ITK_FACTORY_LIST contains names without prefix (e.g., ImageIO)
      string(REGEX REPLACE "^ITK" "" module_base_name "${module}")
      if(NOT ${module_base_name} IN_LIST ITK_FACTORY_LIST)
        set(_use_itk_interface_modules 0)
        message(
          STATUS
          "ITK Interface Module ${module}Module not found. Falling back to ITK Config Modules."
        )
        break()
      endif()
    endif()
  endforeach()

  if(_use_itk_interface_modules)
    message(STATUS "Using ITK Interface Library Modules")
    foreach(module ${itk_modules})
      string(REGEX REPLACE "^ITK" "" module_base_name "${module}")
      if(NOT ${module_base_name} IN_LIST ITK_FACTORY_LIST)
        set(module "${module}Module")
      endif()

      # Use ITK Interface Library Modules
      target_link_libraries(
        ${target_name}
        ${interface_keyword}
        ${module}
      )
    endforeach()
  else()
    itk_module_config(_itk ${itk_modules})
    if(_itk_LIBRARY_DIRS)
      target_link_directories(
        ${target_name}
        ${interface_keyword}
        ${_itk_LIBRARY_DIRS}
      )
    endif()

    if(_itk_LIBRARIES)
      target_link_libraries(
        ${target_name}
        ${interface_keyword}
        ${_itk_LIBRARIES}
      )
    endif()

    if(_itk_INCLUDE_DIRS)
      target_include_directories(
        ${target_name}
        ${interface_keyword}
        ${_itk_INCLUDE_DIRS}
      )
    endif()
  endif()

  # Add ITK required compiler and linker flags
  if(ITK_REQUIRED_CXX_FLAGS)
    separate_arguments(_itk_cxx_flags UNIX_COMMAND "${ITK_REQUIRED_CXX_FLAGS}")
    target_compile_options(
      ${target_name}
      ${interface_keyword}
      ${_itk_cxx_flags}
    )
  endif()

  if(ITK_REQUIRED_LINK_FLAGS)
    separate_arguments(
      _itk_link_flags
      UNIX_COMMAND
      "${ITK_REQUIRED_LINK_FLAGS}"
    )
    target_link_options(
      ${target_name}
      ${interface_keyword}
      ${_itk_link_flags}
    )
  endif()
endfunction()

function(sitk_target_use_itk_factory target_name factory_name)
  list(FIND ITK_FACTORY_LIST "${factory_name}" _index)
  if(_index EQUAL -1)
    message(
      FATAL_ERROR
      "Factory \"${factory_name}\" not contained in ITK_FACTORY_LIST: \"${ITK_FACTORY_LIST}\""
    )
  endif()

  itk_generate_factory_registration(${factory_name} )

  string(TOUPPER ${factory_name} factory_uc)

  target_compile_definitions(
    ${target_name}
    PRIVATE
      ITK_${factory_uc}_FACTORY_REGISTER_MANAGER
  )

  target_include_directories(
    ${target_name}
    PRIVATE
      "${CMAKE_CURRENT_BINARY_DIR}/ITKFactoryRegistration"
  )
endfunction()

itk_generate_factory_registration()
