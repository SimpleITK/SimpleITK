###############################################################################
# This macro returns the list of template components used by a specific
# template file
#
macro( get_dependent_template_components out_var_name json_file input_dir )

  set(${out_var_name})

  ######
  # Figure out which template file gets used
  ######

  # Get the line from the json file that indicates the correct template
  file(STRINGS ${json_file} template_line REGEX ".*template_code_filename.*")
  string(REGEX MATCH ":.*\".*ImageFilter" first_strip ${template_line})

  # Only continue if we found something for first_strip
  if(first_strip)

    # Strip down to just the name and then fill out full path
    string(REGEX MATCH "[^\"]*ImageFilter" template_name ${first_strip})
    set(template_file_h ${input_dir}/templates/sitk${template_name}Template.h.in)
    set(template_file_cxx ${input_dir}/templates/sitk${template_name}Template.cxx.in)

    ######
    # Get dependencies template files
    ######

    # Get the contents of the file
    file(READ ${template_file_h} h_contents)
    file(READ ${template_file_cxx} cxx_contents)

    # For each component, see if it appears in the body of the template file
    foreach(component ${template_components})

      # Get the filename without the path
      get_filename_component( filename ${component} NAME )

      if("${h_contents}" MATCHES ".*${filename}.*")
        set(${out_var_name} ${${out_var_name}} ${component})
      endif()
      if("${cxx_contents}" MATCHES ".*${filename}.*")
        set(${out_var_name} ${${out_var_name}} ${component})
      endif()

    endforeach(component)

  else()
    message(WARNING "No template name found for ${json_file}")

  endif()

endmacro()


###############################################################################
# This macro expands the .h and .cxx files for a given input template
#
macro( expand_template FILENAME input_dir output_dir library_name )

  # Set common variables
  set ( expand_template_script ${SimpleITK_SOURCE_DIR}/Utilities/ExpandTemplate.lua )
  set ( template_include_dir ${SimpleITK_SOURCE_DIR}/TemplateComponents )
  set ( output_h "${output_dir}/include/sitk${FILENAME}ImageFilter.h" )
  set ( output_cxx "${output_dir}/src/sitk${FILENAME}ImageFilter.cxx" )

  set ( input_json_file ${input_dir}/json/${FILENAME}.json )
  set ( template_file_h ${input_dir}/templates/sitkImageFilterTemplate.h.in )
  set ( template_file_cxx ${input_dir}/templates/sitkImageFilterTemplate.cxx.in )

  # Get the list of template component files for this template
  get_dependent_template_components(template_deps ${input_json_file} ${input_dir})

  # Make a global list of ImageFilter template filters
  set ( IMAGE_FILTER_LIST ${IMAGE_FILTER_LIST} ${FILENAME} CACHE INTERNAL "" )

  add_custom_command (
    OUTPUT "${output_h}"
    COMMAND lua ${expand_template_script} code ${input_json_file} ${input_dir}/templates/sitk ${template_include_dir} Template.h.in ${output_h}
    DEPENDS ${input_json_file} ${template_deps} ${template_file_h} ${template_file_cxx}
    )

  add_custom_command (
    OUTPUT "${output_cxx}"
    COMMAND lua ${expand_template_script} code ${input_json_file} ${input_dir}/templates/sitk ${template_include_dir} Template.cxx.in ${output_cxx}
    DEPENDS ${input_json_file} ${template_deps} ${template_file_h} ${template_file_cxx}
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

  # Clear out the GeneratedSource list in the cache
  set (SimpleITK${directory_name}GeneratedSource "" CACHE INTERNAL "")

  ######
  # Perform template expansion
  ######

  # Set input and output directories corresponding to this Code directory
  set(generated_code_input_path ${CMAKE_CURRENT_SOURCE_DIR})
  set(generated_code_output_path ${SimpleITK_BINARY_DIR}/Code/${directory_name}/)

  # Make sure include and src directories exist
  if (NOT EXISTS ${generated_code_output_path}/include)
    file(MAKE_DIRECTORY ${generated_code_output_path}/include)
  endif()
  if (NOT EXISTS ${generated_code_output_path}/src)
    file(MAKE_DIRECTORY ${generated_code_output_path}/src)
  endif()

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
  if (BUILD_DOXYGEN)
    add_dependencies(Documentation ${SimpleITK${directory_name}GeneratedSource} )
  endif (BUILD_DOXYGEN)




  ######
  # Create list of generated headers
  ######

  # clear the include files
  file ( WRITE ${generated_code_output_path}/include/SimpleITK${directory_name}GeneratedHeaders.h "" )
  file ( WRITE ${generated_code_output_path}/include/SimpleITK${directory_name}GeneratedHeaders.i "" )

  set(generated_headers_h ${generated_code_output_path}/include/SimpleITK${directory_name}GeneratedHeaders.h)
  set(generated_headers_i ${generated_code_output_path}/include/SimpleITK${directory_name}GeneratedHeaders.i)

  # Add ifndefs
  file ( APPEND ${generated_headers_h} "#ifndef __SimpleITK${directory_name}GeneratedHeaders_h\n")
  file ( APPEND ${generated_headers_h} "#define __SimpleITK${directory_name}GeneratedHeaders_h\n")

  foreach ( filter ${GENERATED_FILTER_LIST} )
    file ( APPEND ${generated_headers_h} "#include \"sitk${filter}ImageFilter.h\"\n" )
    file ( APPEND ${generated_headers_i} "%include \"sitk${filter}ImageFilter.h\"\n" )
  endforeach()

  file ( APPEND ${generated_headers_h} "#endif\n")



endmacro()
