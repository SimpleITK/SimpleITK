
# Information on how to retrieve the ITK documentation tag file
set(ITK_DOXYGEN_TAG_LOCATION "http://public.kitware.com/pub/itk/NightlyDoxygen/InsightDoxygenDocTag.gz")
set(ITK_DOXYGEN_COMPRESSED_TAG_FILE ${OUTPUT_PATH}/InsightDoxygen.tag.gz)
set(ITK_DOXYGEN_TAG_FILE ${OUTPUT_PATH}/InsightDoxygen.tag)


# Get the compressed ITK documentation tag file
if(NOT EXISTS ${ITK_DOXYGEN_COMPRESSED_TAG_FILE})
  message("Download ITK tag file")
  file( DOWNLOAD
        ${ITK_DOXYGEN_TAG_LOCATION}
        ${ITK_DOXYGEN_COMPRESSED_TAG_FILE}
        TIMEOUT 60
        STATUS statusITKDoxygenTagFile
        SHOW_PROGRESS )
  list(GET statusITKDoxygenTagFile 0 statusVal)
  list(GET statusITKDoxygenTagFile 1 statusMessage)
  if(statusVal)
    message(WARNING "Warning: failed to download ITK tag file.")
    message("Message: " ${statusMessage} )
    file(REMOVE ${ITK_DOXYGEN_COMPRESSED_TAG_FILE})
  endif()
endif(NOT EXISTS ${ITK_DOXYGEN_COMPRESSED_TAG_FILE})

# Uncompress the ITK tag file
if(EXISTS ${ITK_DOXYGEN_COMPRESSED_TAG_FILE})
  find_program(GZIP_TOOL NAMES gzip)
  if(GZIP_TOOL)
    message("Decompressing ITK tag file")
    execute_process(COMMAND ${GZIP_TOOL} -df ${ITK_DOXYGEN_COMPRESSED_TAG_FILE} RESULT_VARIABLE GZIP_OUT)
    if (${GZIP_OUT} )
        MESSAGE(WARNING "gzip result message: " ${GZIP_OUT})
    endif()
    set(DOXYGEN_TAGFILES_PARAMETER "${ITK_DOXYGEN_TAG_FILE}=https://www.itk.org/Doxygen/html/")
  endif()
else()
  set(DOXYGEN_TAGFILES_PARAMETER "")
endif()
