function(sitk_add_tcl_test name)
  # gersemi: hints { COMMAND: command_line }
  set(options "")
  set(oneValueArgs "")
  set(multiValueArgs "")
  cmake_parse_arguments(
    "_"
    "${options}"
    "${oneValueArgs}"
    "${multiValueArgs}"
    ${ARGN}
  )
endfunction()
