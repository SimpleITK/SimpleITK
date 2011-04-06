
###############################################################################
# This macro expands the .h and .cxx files for a given input template
#
macro( expand_template FILENAME input_dir output_dir library_name )

  # Set common variables
  set ( expand_template_script ${SimpleITK_SOURCE_DIR}/Utilities/ExpandTemplate.lua )
  set ( template_include_dir ${SimpleITK_SOURCE_DIR}/CMake/TemplateComponents )
  set ( output_h "${output_dir}/sitk${FILENAME}ImageFilter.h" )
  set ( output_cxx "${output_dir}/sitk${FILENAME}ImageFilter.cxx" )

  set ( input_json_file ${input_dir}/json/${FILENAME}.json )
  set ( template_file_h ${input_dir}/templates/sitkImageFilterTemplate.h.in )
  set ( template_file_cxx ${input_dir}/templates/sitkImageFilterTemplate.cxx.in )

  # Make a global list of ImageFilter template filters
  set ( IMAGE_FILTER_LIST ${IMAGE_FILTER_LIST} ${FILENAME} CACHE INTERNAL "" )

  add_custom_command (
    OUTPUT "${output_h}" "${output_cxx}"
    COMMAND lua ${expand_template_script} code ${input_json_file} ${input_dir}/templates/sitk ${template_include_dir} Template.h.in ${output_h}
    COMMAND lua ${expand_template_script} code ${input_json_file} ${input_dir}/templates/sitk ${template_include_dir} Template.cxx.in ${output_cxx}
    DEPENDS ${input_json_file} ${template_file_h} ${template_file_cxx}
    )
  set ( ${library_name}GeneratedSource ${${library_name}GeneratedSource} "${output_h}" CACHE INTERNAL "" )
  set ( ${library_name}GeneratedSource ${${library_name}GeneratedSource} "${output_cxx}" CACHE INTERNAL "" )

  # Make the list visible at the global scope
  set ( GENERATED_FILTER_LIST ${GENERATED_FILTER_LIST} ${FILENAME} CACHE INTERNAL "" )
endmacro()



###############################################################################
# Macro to do all code generation for a given directory
#
macro(generate_filter_source)

  # Get the name of the current directory
  get_filename_component(directory_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

  ######
  # Perform template expansion
  ######

  # Set input and output directories corresponding to this Code directory
  set(generated_code_input_path ${CMAKE_CURRENT_SOURCE_DIR})
  set(generated_code_output_path ${SimpleITK_BINARY_DIR}/Code/${directory_name}/include)

  # Glob all json files in the current directory
  file ( GLOB json_config_files ${generated_code_input_path}/json/*.json)

  # Loop through json files and expand each one
  foreach ( f ${json_config_files} )
    get_filename_component ( class ${f} NAME_WE )
    expand_template ( ${class}
                      ${generated_code_input_path}
                      ${generated_code_output_path}
                      SimpleITK${directory_name} )

  endforeach()


  ######
  # Make target for generated code
  ######
  add_custom_target(${directory_name}SourceCode ALL DEPENDS ${SimpleITK${directory_name}GeneratedSource})
  if (BUILD_DOXYGEN)
    add_dependencies(Documentation ${directory_name}SourceCode)
  endif (BUILD_DOXYGEN)




  ######
  # Create list of generated headers
  ######

  # clear the include files
  file ( WRITE ${generated_code_output_path}/SimpleITK${directory_name}GeneratedHeaders.h "" )
  file ( WRITE ${generated_code_output_path}/SimpleITK${directory_name}GeneratedHeaders.i "" )

  set(generated_headers_h ${generated_code_output_path}/SimpleITK${directory_name}GeneratedHeaders.h)
  set(generated_headers_i ${generated_code_output_path}/SimpleITK${directory_name}GeneratedHeaders.i)

  # Add ifndefs
  file ( APPEND ${generated_headers_h} "#ifndef __SimpleITK${directory_name}GeneratedHeaders_h\n")
  file ( APPEND ${generated_headers_h} "#define __SimpleITK${directory_name}GeneratedHeaders_h\n")

  foreach ( filter ${GENERATED_FILTER_LIST} )
    file ( APPEND ${generated_headers_h} "#include \"sitk${filter}ImageFilter.h\"\n" )
    file ( APPEND ${generated_headers_i} "%include \"sitk${filter}ImageFilter.h\"\n" )
  endforeach()

  file ( APPEND ${generated_headers_h} "#endif\n")



endmacro()
