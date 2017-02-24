
include(sitkSITKLegacyNaming)

#-----------------------------------------------------------------------------
# Forbid downloading resources from the network during a build. This helps
# when building on systems without network connectivity to determine which
# resources much be obtained manually and made available to the build.
option(SimpleITK_FORBID_DOWNLOADS "Do not download source code or data from the network" OFF)
mark_as_advanced(SimpleITK_FORBID_DOWNLOADS)
sitk_legacy_naming(SimpleITK_FORBID_DOWNLOADS)

macro(sitk_enforce_forbid_downloads _name)
  if(SimpleITK_FORBID_DOWNLOADS)
    message(SEND_ERROR "Attempted to download ${_name} when SimpleITK_FORBID_DOWNLOADS is ON")
  endif()
endmacro()
