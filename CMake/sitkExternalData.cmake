get_filename_component(_SimpleITKExternalData_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

include(ExternalData)

if(NOT ExternalData_OBJECT_STORES)
  # Use ExternalData_OBJECT_STORES from environment as default.
  set(ExternalData_OBJECT_STORES_DEFAULT "")
  if(DEFINED "ENV{ExternalData_OBJECT_STORES}")
    file(TO_CMAKE_PATH "$ENV{ExternalData_OBJECT_STORES}" ExternalData_OBJECT_STORES_DEFAULT)
  endif()
endif()

set(ExternalData_OBJECT_STORES "${ExternalData_OBJECT_STORES_DEFAULT}" CACHE STRING
  "Semicolon-separated list of local directories holding data objects in the layout %(algo)/%(hash).")
mark_as_advanced(ExternalData_OBJECT_STORES)
if(NOT ExternalData_OBJECT_STORES)
  set(ExternalData_OBJECT_STORES "${CMAKE_BINARY_DIR}/ExternalData/Objects")
  file(MAKE_DIRECTORY "${ExternalData_OBJECT_STORES}")
endif()
if (DEFINED SimpleITK_SOURCE_DIR AND EXISTS "${SimpleITK_SOURCE_DIR}/.ExternalData")
  # Add source directory path
  list(APPEND ExternalData_OBJECT_STORES
          "${SimpleITK_SOURCE_DIR}/.ExternalData"
    )
endif()

set(ExternalData_BINARY_ROOT ${CMAKE_BINARY_DIR}/ExternalData)

set(ExternalData_SOURCE_ROOT ${SimpleITK_SOURCE_DIR})

set(ExternalData_URL_TEMPLATES "" CACHE STRING
  "Additional URL templates for the ExternalData CMake script to look for testing data. E.g.
file:///var/bigharddrive/%(algo)/%(hash)")
mark_as_advanced(ExternalData_URL_TEMPLATES)
if(NOT SimpleITK_FORBID_DOWNLOADS)
  list(APPEND ExternalData_URL_TEMPLATES

    # Data mirrored from SimpleITKExternalData repository
    "https://simpleitk.s3.amazonaws.com/public/%(algo)/%(hash)"

    # Data published on GitHub Pages
    "https://simpleitk.org/SimpleITKExternalData/%(algo)/%(hash)"

    # Data published on Girder
    "https://data.kitware.com:443/api/v1/file/hashsum/%(algo)/%(hash)/download"

    # Data published by developers using git-gerrit-push.
    "https://insightsoftwareconsortium.github.io/ITKTestingData/%(algo)/%(hash)"
    "https://itk.org/files/ExternalData/%(algo)/%(hash)"
    )
endif()
# Tell ExternalData commands not to transform raw files to content links.
#set(ExternalData_LINK_CONTENT MD5)

# Match series of the form <base>.<ext>, <base>.<n>.<ext> such that <base> may
# end in a (test) number that is not part of any series numbering.
set(ExternalData_SERIES_PARSE "()(\\.[^./]*)$")
set(ExternalData_SERIES_MATCH "(\\.[0-9]+)?")
