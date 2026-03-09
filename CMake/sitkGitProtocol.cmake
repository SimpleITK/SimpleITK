#-----------------------------------------------------------------------------
# Set the default GIT protocol for fetching dependencies.

find_package(Git)
set(_SimpleITK_GIT_PROTOCOL_default "https")
if(GIT_VERSION_STRING VERSION_LESS "1.7.10")
  # minimum version for https support
  set(_SimpleITK_GIT_PROTOCOL_default "git")
endif()
set(
  SimpleITK_GIT_PROTOCOL
  ${_SimpleITK_GIT_PROTOCOL_default}
  CACHE STRING
  "Set the default GIT protocol for fetching dependencies."
)
mark_as_advanced(SimpleITK_GIT_PROTOCOL)
set_property(
  CACHE
    SimpleITK_GIT_PROTOCOL
  PROPERTY
    STRINGS
      "https;http;git"
)
set(git_protocol ${SimpleITK_GIT_PROTOCOL})
