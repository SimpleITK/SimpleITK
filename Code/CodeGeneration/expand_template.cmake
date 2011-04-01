
###############################################################################
# This macro expands the .h and .cxx files for a given input template
#
macro( expand_template FILENAME input_dir output_dir library_name )

  # Set common variables
  set ( expand_template_script ${SimpleITK_SOURCE_DIR}/Utilities/ExpandTemplate.lua )
  set ( output_h "${output_dir}/sitk${FILENAME}ImageFilter.h" )
  set ( output_cxx "${output_dir}/sitk${FILENAME}ImageFilter.cxx" )

  set ( input_json_file ${input_dir}/${FILENAME}.json )
  set ( template_file_h ${input_dir}/sitkImageFilterTemplate.h.in )
  set ( template_file_cxx ${input_dir}/sitkImageFilterTemplate.cxx.in )

  # Make a global list of ImageFilter template filters
  set ( IMAGE_FILTER_LIST ${IMAGE_FILTER_LIST} ${FILENAME} CACHE INTERNAL "" )

  add_custom_command (
    OUTPUT "${output_h}" "${output_cxx}"
    COMMAND lua ${expand_template_script} code ${input_json_file} ${input_dir}/sitk Template.h.in ${output_h}
    COMMAND lua ${expand_template_script} code ${input_json_file} ${input_dir}/sitk Template.cxx.in ${output_cxx}
    DEPENDS ${input_json_file} ${template_file_h} ${template_file_cxx}
    )
  set ( ${library_name}Source ${${library_name}Source} "${output_h}" CACHE INTERNAL "" )
  set ( ${library_name}Source ${${library_name}Source} "${output_cxx}" CACHE INTERNAL "" )

  # Make the list visible at the global scope
  set ( GENERATED_FILTER_LIST ${GENERATED_FILTER_LIST} ${FILENAME} CACHE INTERNAL "" )
endmacro()

