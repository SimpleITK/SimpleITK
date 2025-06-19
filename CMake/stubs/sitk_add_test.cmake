function(sitk_add_test)
  # gersemi: hints { COMMAND: command_line }
  set(options "")
  set(oneValueArgs "NAME")
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
