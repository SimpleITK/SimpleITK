# Install a pre-commit hook to bootstrap commit hooks.
if(EXISTS "${SimpleITK_SOURCE_DIR}/.git/config" AND
    NOT EXISTS "${SimpleITK_SOURCE_DIR}/.git/hooks/pre-commit")
  # Silently ignore the error if the hooks directory is read-only.
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy ${SimpleITK_SOURCE_DIR}/CMake/pre-commit
                                     ${SimpleITK_SOURCE_DIR}/.git/hooks/pre-commit
    OUTPUT_VARIABLE _output
    ERROR_VARIABLE  _output
    RESULT_VARIABLE _result
    )
  if(_result AND NOT "${_output}" MATCHES "Error copying file")
    message("${_output}")
  endif()
endif()
