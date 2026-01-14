include_guard(GLOBAL)
include("sitkCheckPythonModuleVersion")

# Find a Python executable for code generation
## If SimpleITK_Python_EXECUTABLE is defined, use it, otherwise use Python_EXECUTABLE or find it.
if(DEFINED SimpleITK_Python_EXECUTABLE)
  # check if the variable is a valid executable
  if(NOT EXISTS "${SimpleITK_Python_EXECUTABLE}")
    message(
      FATAL_ERROR
      "SimpleITK_Python_EXECUTABLE is set to an invalid executable: ${SimpleITK_Python_EXECUTABLE}"
    )
  endif()
  # Additional check for CMake 3.29+ using IS_EXECUTABLE
  if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.29")
    if(NOT (IS_EXECUTABLE "${SimpleITK_Python_EXECUTABLE}"))
      message(
        FATAL_ERROR
        "SimpleITK_Python_EXECUTABLE is set to a non-executable file: ${SimpleITK_Python_EXECUTABLE}"
      )
    endif()
  endif()
else()
  if(NOT DEFINED Python_EXECUTABLE)
    find_package(Python 3.9...<4 REQUIRED COMPONENTS Interpreter)
  endif()
  set(SimpleITK_Python_EXECUTABLE "${Python_EXECUTABLE}")
endif()

set(
  SimpleITK_Python_EXECUTABLE
  "${SimpleITK_Python_EXECUTABLE}"
  CACHE FILEPATH
  "Python executable used for code generation."
)

# Check for Python jsonschema module (used to validate YAML config files)
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
        RESULT_VERSION_VAR SimpleITK_Python_JINJA2_VERSION
        REQUIRED
)

# Check for PyYAML module
sitk_check_python_module_version(
        MODULE_NAME pyyaml
        MINIMUM_VERSION 5.0
        MAXIMUM_VERSION 7.0
        PYTHON_EXECUTABLE "${SimpleITK_Python_EXECUTABLE}"
        RESULT_VERSION_VAR SimpleITK_Python_PYYAML_VERSION
        REQUIRED
)

set(
  SimpleITK_EXPANSION_SCRIPT
  "${SimpleITK_SOURCE_DIR}/ExpandTemplateGenerator/ExpandTemplate.py"
  CACHE INTERNAL
  "Python script used to expand templates."
  FORCE
)

# clear cache variable _SITK_JINJA_FILES
unset(_SITK_JINJA_FILES CACHE)

# Sets "out_var" variable name to the value in the config path specified
# to the yaml file name. If an error is encountered than the variable
# is not updated.
#
function(get_config_path out_var config_file path)
  get_filename_component(extension ${config_file} EXT)
  string(TOLOWER "${extension}" ext_lower)

  if("${ext_lower}" STREQUAL ".yaml" OR "${ext_lower}" STREQUAL ".yml")
    execute_process(
      COMMAND
        ${SimpleITK_Python_EXECUTABLE} -c
        [=[
import sys
import yaml
try:
    from yaml import CSafeLoader as Loader
except ImportError:
    from yaml import SafeLoader as Loader

d = yaml.load(open(sys.argv[1]), Loader=Loader)
v = d
for k in sys.argv[2].split('.'):
    v = v[k]
print(v)
]=]
        ${config_file} ${path}
      OUTPUT_VARIABLE value
      RESULT_VARIABLE ret
      ERROR_VARIABLE error_var
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_STRIP_TRAILING_WHITESPACE
    )
  else()
    message(
      WARNING
      "Unsupported configuration file format: ${extension}. Only YAML files are supported."
    )
    return()
  endif()

  if(NOT ret)
    set(${out_var} "${value}" PARENT_SCOPE)
  else()
    message(
      WARNING
      "ERROR VAR: ${error_var}\n ERROR CODE: ${ret}\n"
      "Unable to find path \"${path}\" in configuration file \"${config_file}\"."
    )
  endif()
endfunction()

###############################################################################
# This macro returns the list of template components used by a specific
# template file
#
macro(get_dependent_template_components out_var_name config_file input_dir)
  set(${out_var_name})

  ######
  # Figure out which template file gets used
  ######

  get_config_path( template_code_filename ${config_file} "template_code_filename")

  if(template_code_filename)
    set(
      template_file_h
      "${input_dir}/templates/sitk${template_code_filename}Template.h.in"
    )
    set(
      template_file_cxx
      "${input_dir}/templates/sitk${template_code_filename}Template.cxx.in"
    )

    ######
    # Get dependencies template files
    ######

    set(${out_var_name} ${${cache_var}})
  else()
    message(
      WARNING
      "Error processing ${config_file}, unable to locate template_code_filename"
    )
  endif()
endmacro()

###############################################################################
# Internal function to get jinja include directory
#
function(_sitk_get_jinja_include_dir out_var)
  set(
    ${out_var}
    "${SimpleITK_SOURCE_DIR}/ExpandTemplateGenerator/templates"
    PARENT_SCOPE
  )
endfunction()

###############################################################################
# Internal function to get jinja template dependencies (cached)
#
function(_sitk_get_jinja_dependencies out_var)
  # Check if we've already cached the jinja files
  if(NOT DEFINED CACHE{_SITK_JINJA_FILES})
    _sitk_get_jinja_include_dir(_sitk_jinja_include_dir)
    file(GLOB_RECURSE _sitk_jinja_files "${_sitk_jinja_include_dir}/*.jinja")
    set(
      _SITK_JINJA_FILES
      "${_sitk_jinja_files}"
      CACHE INTERNAL
      "Cached list of jinja template files"
    )
  endif()
  set(${out_var} "${_SITK_JINJA_FILES}" PARENT_SCOPE)
endfunction()

###############################################################################
# This macro expands the .h and .cxx files for a given input template
#
function(expand_template input_config_file input_dir output_dir library_name)
  get_filename_component(FILENAME ${input_config_file} NAME_WE)

  # Get jinja template dependencies and include directory
  _sitk_get_jinja_include_dir(_sitk_jinja_include_dir)
  _sitk_get_jinja_dependencies(_sitk_jinja_files)

  set(output_h "${output_dir}/include/sitk${FILENAME}.h")
  set(output_cxx "${output_dir}/src/sitk${FILENAME}.cxx")

  # Check if YAML file exists
  if(NOT EXISTS ${input_config_file})
    message(WARNING "No YAML configuration file found for ${FILENAME}")
    return()
  endif()

  set(template_file_h ${input_dir}/templates/sitkImageFilterTemplate.h.in)
  set(template_file_cxx ${input_dir}/templates/sitkImageFilterTemplate.cxx.in)

  # Get the list of template component files for this template
  get_dependent_template_components(template_deps ${input_config_file} ${input_dir})

  # header
  add_custom_command(
    OUTPUT
      "${output_h}"
      ${JSON_VALIDATE_COMMAND}
    COMMAND
      ${SimpleITK_Python_EXECUTABLE} ${SimpleITK_EXPANSION_SCRIPT}
      ${input_config_file} -D ${input_dir}/templates -D
      ${_sitk_jinja_include_dir} sitk${template_code_filename}Template.h.jinja
      -o ${output_h}
    DEPENDS
      ${input_config_file}
      ${template_deps}
      ${_sitk_jinja_files}
      ${input_dir}/templates/sitk${template_code_filename}Template.h.jinja
  )

  # impl
  add_custom_command(
    OUTPUT
      "${output_cxx}"
    COMMAND
      ${SimpleITK_Python_EXECUTABLE} ${SimpleITK_EXPANSION_SCRIPT}
      ${input_config_file} -D ${input_dir}/templates -D
      ${_sitk_jinja_include_dir} sitk${template_code_filename}Template.cxx.jinja
      -o ${output_cxx}
    DEPENDS
      ${input_config_file}
      ${template_deps}
      ${_sitk_jinja_files}
      ${input_dir}/templates/sitk${template_code_filename}Template.cxx.jinja
  )

  set(
    ${library_name}GeneratedHeader
    ${${library_name}GeneratedHeader}
    "${output_h}"
    CACHE INTERNAL
    ""
  )

  set(
    ${library_name}GeneratedSource
    ${${library_name}GeneratedSource}
    "${output_cxx}"
    CACHE INTERNAL
    ""
  )

  get_config_path( itk_module ${input_config_file} itk_module)
  if(NOT "${itk_module}" STREQUAL "")
    cache_list_append(${library_name}GeneratedSource_${itk_module}  ${output_cxx})
  endif()
endfunction()

###############################################################################
# Macro: generate_filter_list
#
# Description:
#   This macro is used to generate the list of usage configuration files for the project.
#   If a filter configuration file exists in repository but the ITK module is not enabled it will not be in the output list.
#
# Usage:
#   generate_filter_list()
#
# Arguments:
#   None.
#
# Outputs:
#   Sets GENERATED_CONFIG_LIST as a cache variable.
#
macro(generate_filter_list)
  set(GENERATED_CONFIG_LIST "")

  message(CHECK_START "Processing configuration files")

  set(generated_code_input_path ${SimpleITK_SOURCE_DIR}/Code/BasicFilters)

  set(
    JSON_SCHEMA_FILE
    "${SimpleITK_SOURCE_DIR}/ExpandTemplateGenerator/simpleitk_filter_description.schema.json"
  )

  # Glob all yaml files in the current directory
  file(
    GLOB yaml_config_files
    ${generated_code_input_path}/yaml/[a-zA-Z]*.yaml
    ${generated_code_input_path}/yaml/[a-zA-Z]*.yml
  )

  # Use only YAML config files
  set(config_files ${yaml_config_files})

  # Loop through config files and expand each one
  foreach(input_config_file IN LISTS config_files)
    get_config_path( itk_module ${input_config_file} itk_module)

    list(FIND ITK_MODULES_ENABLED "${itk_module}" _index)
    if("${itk_module}" STREQUAL "")
      message(WARNING "Missing \"itk_module\" field in ${input_config_file}")
    elseif(NOT "${itk_module}" STREQUAL "" AND ${_index} EQUAL -1)
      # required module is not enabled, don't process
    else()
      # validate YAML config files if requirements available
      if(SimpleITK_Python_JSONSCHEMA_VERSION AND 0)
        set(
          VALIDATE_COMMAND
          "${SimpleITK_Python_EXECUTABLE}"
          "${SimpleITK_SOURCE_DIR}/Utilities/JSON/ConfigValidate.py"
          "${JSON_SCHEMA_FILE}"
          "${input_config_file}"
        )

        execute_process(
          COMMAND
            ${VALIDATE_COMMAND}
          RESULT_VARIABLE failed
          ERROR_VARIABLE error
        )
        if(failed)
          message(
            SEND_ERROR
            "Faild to validate filter configuration file ${input_config_file}\n${error}"
          )
        endif()
      endif()

      get_filename_component(FILENAME ${input_config_file} NAME_WE)
      # Make the list visible at the global scope
      list(APPEND GENERATED_CONFIG_LIST ${input_config_file})
    endif()
  endforeach()

  set(GENERATED_CONFIG_LIST ${GENERATED_CONFIG_LIST} CACHE INTERNAL "" FORCE)

  message(CHECK_PASS "done")
endmacro(generate_filter_list)

###############################################################################
# Macro to do all code generation for a given directory
#
macro(generate_filter_source)
  # Get the name of the current directory
  get_filename_component(directory_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

  # Clear out the GeneratedSource list in the cache
  unset(SimpleITK${directory_name}GeneratedSource CACHE)
  unset(SimpleITK${directory_name}GeneratedHeader CACHE)
  get_cmake_property(_varNames VARIABLES)
  foreach(_varName IN LISTS _varNames)
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

  message(CHECK_START "Configuring C++ file generation")

  # Loop through config files and expand each one
  foreach(f IN LISTS GENERATED_CONFIG_LIST)
    expand_template( ${f}
                      ${generated_code_input_path}
                      ${generated_code_output_path}
                      SimpleITK${directory_name}
    )
  endforeach()

  ######
  # Make target for generated source and headers
  ######
  add_custom_target(
    ${directory_name}SourceCode
    ALL
    DEPENDS
      ${SimpleITK${directory_name}GeneratedHeader}
      ${SimpleITK${directory_name}GeneratedSource}
  )
  if(BUILD_DOXYGEN)
    add_dependencies(Documentation ${directory_name}SourceCode)
  endif(BUILD_DOXYGEN)

  ######
  # Create list of generated headers
  ######

  set(
    generated_headers_h
    ${generated_code_output_path}/include/SimpleITK${directory_name}GeneratedHeaders.h
  )
  set(
    generated_headers_i
    ${generated_code_output_path}/include/SimpleITK${directory_name}GeneratedHeaders.i
  )
  set(
    tmp_generated_headers_h
    ${CMAKE_CURRENT_BINARY_DIR}/CMakeTmp/SimpleITK${directory_name}GeneratedHeaders.h
  )
  set(
    tmp_generated_headers_i
    ${CMAKE_CURRENT_BINARY_DIR}/CMakeTmp/include/SimpleITK${directory_name}GeneratedHeaders.i
  )

  #delete tmp files
  file(
    REMOVE
    "${tmp_generated_headers_h}"
    "${tmp_generated_headers_i}"
  )

  # Add ifndefs
  file(
    WRITE
    "${tmp_generated_headers_h}"
    "#ifndef SimpleITK${directory_name}GeneratedHeaders_h\n"
    "#define SimpleITK${directory_name}GeneratedHeaders_h\n"
  )

  foreach(config_file IN LISTS GENERATED_CONFIG_LIST)
    get_filename_component(filtername ${config_file} NAME_WE)
    file(
      APPEND
      "${tmp_generated_headers_h}"
      "#include \"sitk${filtername}.h\"\n"
    )
    file(
      APPEND
      "${tmp_generated_headers_i}"
      "%include \"sitk${filtername}.h\"\n"
    )
  endforeach()

  file(APPEND "${tmp_generated_headers_h}" "#endif\n")

  configure_file("${tmp_generated_headers_h}" "${generated_headers_h}" COPYONLY)
  configure_file("${tmp_generated_headers_i}" "${generated_headers_i}" COPYONLY)

  install(
    FILES
      ${SimpleITK${directory_name}GeneratedHeader}
      ${generated_headers_h}
      ${generated_headers_i}
    DESTINATION ${SimpleITK_INSTALL_INCLUDE_DIR}
    COMPONENT Development
  )
  message(CHECK_PASS "done")
endmacro()

# Process yaml files to produce the GENERATED_CONFIG_LIST cache variable
generate_filter_list()
