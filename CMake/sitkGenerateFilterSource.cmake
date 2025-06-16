include("sitkCheckPythonModuleVersion")

# Find a Python executable for code generation
## If SimpleITK_Python_EXECUTABLE is defined, use it, otherwise use Python_EXECUTABLE or find it.
if (DEFINED SimpleITK_Python_EXECUTABLE)
  # check if the variable is a valid executable
  if (NOT EXISTS "${SimpleITK_Python_EXECUTABLE}" OR NOT IS_EXECUTABLE "${SimpleITK_Python_EXECUTABLE}")
      message(FATAL_ERROR "SimpleITK_Python_EXECUTABLE is set to an invalid executable: ${SimpleITK_Python_EXECUTABLE}")
  endif()
else()
  if (NOT DEFINED Python_EXECUTABLE)
    find_package(Python 3.9...<4 REQUIRED COMPONENTS Interpreter)
  endif()
  set(SimpleITK_Python_EXECUTABLE "${Python_EXECUTABLE}")
endif()

set(SimpleITK_Python_EXECUTABLE
  "${SimpleITK_Python_EXECUTABLE}"
  CACHE FILEPATH
  "Python executable used for code generation."
)

# Check for Python jsonschema module
sitk_check_python_module_version(
  MODULE_NAME jsonschema
  MINIMUM_VERSION 4.0
  MAXIMUM_VERSION 5.0
  PYTHON_EXECUTABLE "${SimpleITK_Python_EXECUTABLE}"
  RESULT_VERSION_VAR SimpleITK_Python_JSONSCHEMA_VERSION
)

sitk_check_python_module_version(
        MODULE_NAME jinja2
        MINIMUM_VERSION 3.1
        MAXIMUM_VERSION 4.0
        PYTHON_EXECUTABLE "${SimpleITK_Python_EXECUTABLE}"
        RESULT_VERSION_VAR SimpleITK_Python_JSONSCHEMA_VERSION
        REQUIRED
)

set(SimpleITK_EXPANSION_SCRIPT "${SimpleITK_SOURCE_DIR}/ExpandTemplateGenerator/ExpandTemplate.py" CACHE INTERNAL
  "Python script used to expand templates." FORCE)

# Sets "out_var" variable name to the value in the json path specified
# to the json file name. If an error is encountered than the variable
# is not updated.
#
function( get_json_path out_var json_file path )


  execute_process(
    COMMAND ${SimpleITK_Python_EXECUTABLE} -c
      "import sys, json; d=json.load(open(sys.argv[1])); v=d;\nfor k in sys.argv[2].split('.'):\n    v = v[k]\nprint(v)"
      ${json_file} ${path}
    OUTPUT_VARIABLE value
    RESULT_VARIABLE ret
    ERROR_VARIABLE error_var
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
  )

  if ( NOT ret )
    set(${out_var} "${value}" PARENT_SCOPE)
  else()
    message( WARNING "ERROR VAR: ${error_var}\n ERROR CODE: ${ret}\n"
      "Unable to find path \"${path}\" in json file \"${json_file}\"." )
  endif()

endfunction()


###############################################################################
# This macro returns the list of template components used by a specific
# template file
#
macro( get_dependent_template_components out_var_name json_file input_dir )

  set(${out_var_name})

  ######
  # Figure out which template file gets used
  ######

  get_json_path( template_code_filename ${json_file} "template_code_filename")

  if(template_code_filename)

    set(template_file_h "${input_dir}/templates/sitk${template_code_filename}Template.h.in")
    set(template_file_cxx "${input_dir}/templates/sitk${template_code_filename}Template.cxx.in")

    ######
    # Get dependencies template files
    ######

    set (${out_var_name} ${${cache_var}} )

  else()
    message(WARNING "Error processing ${json_file}, unable to locate template_code_filename")
  endif()

endmacro()


###############################################################################
# This macro expands the .h and .cxx files for a given input template
#
function( expand_template FILENAME input_dir output_dir library_name )


  # Set common variables
  set ( jinja_include_dir ${SimpleITK_SOURCE_DIR}/ExpandTemplateGenerator/templates )
  set ( output_h "${output_dir}/include/sitk${FILENAME}.h" )
  set ( output_cxx "${output_dir}/src/sitk${FILENAME}.cxx" )

  set ( input_json_file ${input_dir}/json/${FILENAME}.json )
  set ( template_file_h ${input_dir}/templates/sitkImageFilterTemplate.h.in )
  set ( template_file_cxx ${input_dir}/templates/sitkImageFilterTemplate.cxx.in )

  get_json_path( itk_module ${input_json_file} itk_module)

  list (FIND ITK_MODULES_ENABLED "${itk_module}" _index)

  if("${itk_module}" STREQUAL "")
    message(WARNING "Missing \"itk_module\" field in ")
  elseif (NOT "${itk_module}" STREQUAL "" AND ${_index} EQUAL -1)
    # required module is not enabled, don't process
    return()
  endif()

  # Get the list of template component files for this template
  get_dependent_template_components(template_deps ${input_json_file} ${input_dir})

  # Make a global list of ImageFilter template filters
  set ( IMAGE_FILTER_LIST ${IMAGE_FILTER_LIST} ${FILENAME} CACHE INTERNAL "" )

  # validate json files if requirements available
  if ( SimpleITK_Python_JSONSCHEMA_VERSION )
    set ( JSON_SCHEMA_FILE "${SimpleITK_SOURCE_DIR}/ExpandTemplateGenerator/simpleitk_filter_description.schema.json" )
    set ( JSON_VALIDATE_COMMAND COMMAND "${SimpleITK_Python_EXECUTABLE}" "${SimpleITK_SOURCE_DIR}/Utilities/JSON/JSONValidate.py" "${JSON_SCHEMA_FILE}" "${input_json_file}" )
  endif ()

  # glob on jinja files in ${jinja_include_dir}
  file(GLOB_RECURSE jinja_files "${jinja_include_dir}/*.jinja")

  # header
  add_custom_command (
    OUTPUT "${output_h}"
    ${JSON_VALIDATE_COMMAND}
    COMMAND ${CMAKE_COMMAND} -E remove -f ${output_h}
    COMMAND ${SimpleITK_Python_EXECUTABLE} ${SimpleITK_EXPANSION_SCRIPT} ${input_json_file} -D ${input_dir}/templates -D ${jinja_include_dir} sitk${template_code_filename}Template.h.jinja ${output_h}
    DEPENDS ${input_json_file} ${template_deps}  ${jinja_files} ${input_dir}/templates/sitk${template_code_filename}Template.h.jinja
  )

  # impl
  add_custom_command (
    OUTPUT "${output_cxx}"
    COMMAND ${CMAKE_COMMAND} -E remove -f ${output_cxx}
    COMMAND ${SimpleITK_Python_EXECUTABLE} ${SimpleITK_EXPANSION_SCRIPT} ${input_json_file} -D ${input_dir}/templates -D ${jinja_include_dir} sitk${template_code_filename}Template.cxx.jinja ${output_cxx}
    DEPENDS ${input_json_file} ${template_deps}  ${jinja_files} ${input_dir}/templates/sitk${template_code_filename}Template.cxx.jinja
    )

  set ( ${library_name}GeneratedHeader ${${library_name}GeneratedHeader}
    "${output_h}" CACHE INTERNAL "" )

  set ( ${library_name}GeneratedSource ${${library_name}GeneratedSource}
    "${output_cxx}" CACHE INTERNAL "" )

  if (NOT "${itk_module}" STREQUAL "")
    cache_list_append(${library_name}GeneratedSource_${itk_module}  ${output_cxx} )
  endif()


  # Make the list visible at the global scope
  set ( GENERATED_FILTER_LIST ${GENERATED_FILTER_LIST} ${FILENAME} CACHE INTERNAL "" )
endfunction()



###############################################################################
# Macro to do all code generation for a given directory
#
macro(generate_filter_source)

  # Get the name of the current directory
  get_filename_component(directory_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

  # Clear out the GeneratedSource list in the cache
  set (SimpleITK${directory_name}GeneratedSource "" CACHE INTERNAL "")
  set (SimpleITK${directory_name}GeneratedHeader "" CACHE INTERNAL "")
  get_cmake_property( _varNames VARIABLES )
  foreach (_varName ${_varNames})
    if(_varName MATCHES "^SimpleITKBasicFiltersGeneratedSource_")
      unset(${_varName} CACHE)
    endif()
  endforeach()

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

  set(generated_headers_h ${generated_code_output_path}/include/SimpleITK${directory_name}GeneratedHeaders.h)
  set(generated_headers_i ${generated_code_output_path}/include/SimpleITK${directory_name}GeneratedHeaders.i)
  set(tmp_generated_headers_h ${CMAKE_CURRENT_BINARY_DIR}/CMakeTmp/SimpleITK${directory_name}GeneratedHeaders.h)
  set(tmp_generated_headers_i ${CMAKE_CURRENT_BINARY_DIR}/CMakeTmp/include/SimpleITK${directory_name}GeneratedHeaders.i)

  file ( WRITE ${generated_headers_i} "")

  # Add ifndefs
  file ( WRITE "${tmp_generated_headers_h}" "#ifndef SimpleITK${directory_name}GeneratedHeaders_h\n")
  file ( APPEND "${tmp_generated_headers_h}" "#define SimpleITK${directory_name}GeneratedHeaders_h\n")

  foreach ( filter ${GENERATED_FILTER_LIST} )
    file ( APPEND "${tmp_generated_headers_h}" "#include \"sitk${filter}.h\"\n" )
    file ( APPEND "${tmp_generated_headers_i}" "%include \"sitk${filter}.h\"\n" )
  endforeach()

  file ( APPEND "${tmp_generated_headers_h}" "#endif\n")

  configure_file( "${tmp_generated_headers_h}" "${generated_headers_h}" COPYONLY )
  configure_file( "${tmp_generated_headers_i}" "${generated_headers_i}" COPYONLY )

  install(FILES
    ${SimpleITK${directory_name}GeneratedHeader}
    ${generated_headers_h}
    ${generated_headers_i}
  DESTINATION ${SimpleITK_INSTALL_INCLUDE_DIR}
  COMPONENT Development)


endmacro()
