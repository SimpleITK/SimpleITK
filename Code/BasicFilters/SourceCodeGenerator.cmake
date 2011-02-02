set ( IMAGE_FILTER_LIST "" CACHE INTERNAL "" )
set ( REGION_GROWING_FILTER_LIST "" CACHE INTERNAL "" )
set ( GENERATED_FILTER_LIST "" CACHE INTERNAL "" )

file ( GLOB TEMPLATE_FILES "sitk*Template*" )

macro( expand_template FILENAME )
  # Do this in one massive custom command.  Will result in code re-generating from time to time, but that is OK (hopefully!)

  # Set common variables
  set ( expand_template_script ${SimpleITK_SOURCE_DIR}/Utilities/ExpandTemplate.lua )
  set ( output_h "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.h" )
  set ( output_cxx "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.cxx" )

  # Use the ImageFilterTemplate if specified
  if ( ${TEMPLATE_TYPE} EQUAL ${image_filter_template} )
    set ( input_json_file ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.json )
    set ( template_file_h ${CMAKE_CURRENT_SOURCE_DIR}/sitkImageFilterTemplate.h.in )
    set ( template_file_cxx ${CMAKE_CURRENT_SOURCE_DIR}/sitkImageFilterTemplate.cxx.in )
    # Make a global list of ImageFilter template filters
    set ( IMAGE_FILTER_LIST ${IMAGE_FILTER_LIST} ${FILENAME} CACHE INTERNAL "" )

  # Use the RegionGrowingImageFilterTemplate if specified
  elseif ( ${TEMPLATE_TYPE} EQUAL ${region_growing_image_filter_template} )
    set ( input_json_file ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}_RegionGrowing.json )
    set ( template_file_h ${CMAKE_CURRENT_SOURCE_DIR}/sitkRegionGrowingImageFilterTemplate.h.in )
    set ( template_file_cxx ${CMAKE_CURRENT_SOURCE_DIR}/sitkRegionGrowingImageFilterTemplate.cxx.in )
    # Make a global list of RegionGrowingImageFilter template filters
    set ( REGION_GROWING_FILTER_LIST ${REGION_GROWING_FILTER_LIST} ${FILENAME} CACHE INTERNAL "" )
  endif()

  add_custom_command (
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.h" "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.cxx"
    COMMAND lua ${SimpleITK_SOURCE_DIR}/Utilities/ExpandTemplate.lua code ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.json ${CMAKE_CURRENT_SOURCE_DIR}/sitk  Template.h.in    ${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.h
    COMMAND lua ${SimpleITK_SOURCE_DIR}/Utilities/ExpandTemplate.lua code ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.json ${CMAKE_CURRENT_SOURCE_DIR}/sitk  Template.cxx.in  ${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.cxx
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.json ${TEMPLATE_FILES}
    )
  set ( SimpleITKBasicFiltersSource ${SimpleITKBasicFiltersSource} "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.h" )
  set ( SimpleITKBasicFiltersSource ${SimpleITKBasicFiltersSource} "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.cxx" )

  # Make the list visible at the global scope
  set ( GENERATED_FILTER_LIST ${GENERATED_FILTER_LIST} ${FILENAME} CACHE INTERNAL "" )
endmacro()

file ( GLOB JSON_CONFIG_FILES *.json)

foreach ( f ${JSON_CONFIG_FILES} )
  get_filename_component ( class ${f} NAME_WE )

  # Detect other template types
  string(REGEX MATCH ".*_RegionGrowing" region_growing_match ${class})
  set(region_growing_match ${region_growing_match}false)
  string(COMPARE NOTEQUAL ${region_growing_match} "false" found_region_growing)

  # if a region growing method is found, use the right template
  if ( ${found_region_growing} )
    # strip out "_RegionGrowing"
    string( REGEX REPLACE "_RegionGrowing" "" new_class ${class} )
    expand_template ( ${new_class} ${region_growing_image_filter_template} )
  else()
    expand_template ( ${class} ${image_filter_template})
  endif()

endforeach()

# Make target for generated code
add_custom_target(generate_filter_source_code ALL DEPENDS ${SimpleITKBasicFiltersSource})
add_dependencies(Documentation generate_filter_source_code)

# clear the include files
file ( WRITE ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.h "" )
file ( WRITE ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.i "" )

# Add ifndefs
file ( APPEND ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.h "#ifndef __SimpleITKBasicFiltersGeneratedHeaders_h\n")
file ( APPEND ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.h "#define __SimpleITKBasicFiltersGeneratedHeaders_h\n")

foreach ( filter ${GENERATED_FILTER_LIST} )
  file ( APPEND ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.h "#include \"sitk${filter}ImageFilter.h\"\n" )
  file ( APPEND ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.i "%include \"sitk${filter}ImageFilter.h\"\n" )
endforeach()

file ( APPEND ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.h "#endif\n")
