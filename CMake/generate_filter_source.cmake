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

  # strip down to what in between the "" after the :
  string(REGEX MATCH ":.*\"([^\"]+)\"" _out ${template_line})
  set(template_name "${CMAKE_MATCH_1}" )

  if(_out)

    set(template_file_h "${input_dir}/templates/sitk${template_name}Template.h.in")
    set(template_file_cxx "${input_dir}/templates/sitk${template_name}Template.cxx.in")

    ######
    # Get dependencies template files
    ######

    set(cache_var "_${template_file_h}_${template_file_cxx}_components_cache")
    if ( NOT ${cache_var} )

      # Get the contents of the file
      file(READ ${template_file_h} h_contents)
      file(READ ${template_file_cxx} cxx_contents)

      # For each component, see if it appears in the body of the template file
      foreach(component ${template_components})

        # Get the filename without the path
        get_filename_component( filename ${component} NAME )

        if("${h_contents}" MATCHES ".*${filename}.*" OR
            "${cxx_contents}" MATCHES ".*${filename}.*")
          set(${cache_var} ${${cache_var}} ${component})
        endif()

      endforeach(component)
    endif()
    set (${out_var_name} ${${cache_var}} )

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
  set ( output_h "${output_dir}/include/sitk${FILENAME}.h" )
  set ( output_cxx "${output_dir}/src/sitk${FILENAME}.cxx" )

  set ( input_json_file ${input_dir}/json/${FILENAME}.json )
  set ( template_file_h ${input_dir}/templates/sitkImageFilterTemplate.h.in )
  set ( template_file_cxx ${input_dir}/templates/sitkImageFilterTemplate.cxx.in )

  # Get the list of template component files for this template
  get_dependent_template_components(template_deps ${input_json_file} ${input_dir})

  # Make a global list of ImageFilter template filters
  set ( IMAGE_FILTER_LIST ${IMAGE_FILTER_LIST} ${FILENAME} CACHE INTERNAL "" )

  # header
  add_custom_command (
    OUTPUT "${output_h}"
    COMMAND ${CMAKE_COMMAND} -E remove -f ${output_h}
    COMMAND lua ${expand_template_script} code ${input_json_file} ${input_dir}/templates/sitk ${template_include_dir} Template.h.in ${output_h}
    DEPENDS ${input_json_file} ${template_deps} ${template_file_h}
    )
  # impl
  add_custom_command (
    OUTPUT "${output_cxx}"
    COMMAND ${CMAKE_COMMAND} -E remove -f ${output_cxx}
    COMMAND lua ${expand_template_script} code ${input_json_file} ${input_dir}/templates/sitk ${template_include_dir} Template.cxx.in ${output_cxx}
    DEPENDS ${input_json_file} ${template_deps} ${template_file_cxx}
    )

 set ( ${library_name}GeneratedHeader ${${library_name}GeneratedHeader}
    "${output_h}" CACHE INTERNAL "" )

  set ( ${library_name}GeneratedSource ${${library_name}GeneratedSource}
    "${output_cxx}" CACHE INTERNAL "" )

  set_source_files_properties ( ${${library_name}GeneratedSource} PROPERTIES GENERATED 1 )
  set_source_files_properties ( ${${library_name}GeneratedHeader} PROPERTIES GENERATED 1 )

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
  set (SimpleITK${directory_name}GeneratedHeader "" CACHE INTERNAL "")

  ######
  # Perform template expansion
  ######

  # Set input and output directories corresponding to this Code directory
  set(generated_code_input_path ${CMAKE_CURRENT_SOURCE_DIR})
  set(generated_code_output_path ${SimpleITK_BINARY_DIR}/Code/${directory_name})

  # Make sure include and src directories exist
  if (NOT EXISTS ${generated_code_output_path}/include)
    file(MAKE_DIRECTORY ${generated_code_output_path}/include)
  endif()
  if (NOT EXISTS ${generated_code_output_path}/src)
    file(MAKE_DIRECTORY ${generated_code_output_path}/src)
  endif()


  message( STATUS "Processing json files..." )

  # Glob all json files in the current directory
  file ( GLOB json_config_files ${generated_code_input_path}/json/[a-zA-Z]*.json)

  # Loop through json files and expand each one
  foreach ( f ${json_config_files} )
    get_filename_component ( class ${f} NAME_WE )
    expand_template ( ${class}
                      ${generated_code_input_path}
                      ${generated_code_output_path}
                      SimpleITK${directory_name} )

  endforeach()

  message( STATUS "Processing json files...done" )

  ######
  # Make target for generated source and headers
  ######
  add_custom_target(${directory_name}SourceCode ALL DEPENDS
    ${SimpleITK${directory_name}GeneratedHeader}
    ${SimpleITK${directory_name}GeneratedSource} )
  if (BUILD_DOXYGEN)
    add_dependencies(Documentation ${directory_name}SourceCode)
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
    file ( APPEND ${generated_headers_h} "#include \"sitk${filter}.h\"\n" )
    file ( APPEND ${generated_headers_i} "%include \"sitk${filter}.h\"\n" )
  endforeach()

  file ( APPEND ${generated_headers_h} "#endif\n")



endmacro()
