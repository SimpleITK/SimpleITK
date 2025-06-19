function(sitk_add_ruby_test name)
  # gersemi: hints { COMMAND: command_line }
  set(options "")
  set(oneValueArgs "")
  set(
    multiValueArgs
    COMMAND
    TRANSFORM_COMPARE
    IMAGE_COMPARE
    IMAGE_MD5_COMPARE
  )
  cmake_parse_arguments(
    "_"
    "${options}"
    "${oneValueArgs}"
    "${multiValueArgs}"
    ${ARGN}
  )
endfunction()
