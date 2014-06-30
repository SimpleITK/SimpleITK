
# Information on how to retrieve the ITK documentation tag file
set(ITK_DOXYGEN_TAG_LOCATION "http://public.kitware.com/pub/itk/NightlyDoxygen/InsightDoxygenDocTag")
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
  list(GET statusITKDoxygenTagFile 0 statusITKDoxygenTagFile)
  if(statusITKDoxygenTagFile)
    file(REMOVE ${ITK_DOXYGEN_COMPRESSED_TAG_FILE})
  endif()
endif(NOT EXISTS ${ITK_DOXYGEN_COMPRESSED_TAG_FILE})

# Uncompress the ITK tag file
if(EXISTS ${ITK_DOXYGEN_COMPRESSED_TAG_FILE})
  find_program(GZIP_TOOL NAMES gzip)
  if(GZIP_TOOL)
    message("Decompressing ITK tag file")
    # Note the "-k" option, which doesn't exist in older versions of gzip
    execute_process(COMMAND ${GZIP_TOOL} -dkf ${ITK_DOXYGEN_COMPRESSED_TAG_FILE})
    set(DOXYGEN_TAGFILES_PARAMETER "${ITK_DOXYGEN_TAG_FILE}=http://www.itk.org/Doxygen/html/")
  endif()
else()
  set(DOXYGEN_TAGFILES_PARAMETER "")
endif()
