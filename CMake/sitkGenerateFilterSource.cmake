
# Find a Lua executable
#
if ( NOT SimpleITK_LUA_EXECUTABLE )
  set ( SAVE_LUA_EXECUTABLE ${LUA_EXECUTABLE} )
  get_property( SAVE_LUA_EXECUTABLE_TYPE CACHE LUA_EXECUTABLE PROPERTY TYPE )
  get_property( SAVE_LUA_EXECUTABLE_DOCSTRING CACHE LUA_EXECUTABLE PROPERTY HELPSTRING )

  find_package( LuaInterp REQUIRED 5.1 )
  set( SimpleITK_LUA_EXECUTABLE ${LUA_EXECUTABLE} CACHE PATH "Lua executable used for code generation." )

  if (DEFINED SAVE_LUA_EXECUTABLE)
    set( LUA_EXECUTABLE ${SAVE_LUA_EXECUTABLE}
      CACHE
       ${SAVE_LUA_EXECUTABLE_TYPE}
       ${SAVE_LUA_EXECUTABLE_DOCSTRING}
       FORCE
       )
  else()
    unset( LUA_EXECUTABLE CACHE )
  endif()
endif()

# Get the Lua version
#
execute_process(
  COMMAND ${SimpleITK_LUA_EXECUTABLE} -v
  OUTPUT_VARIABLE
    SimpleITK_LUA_EXECUTABLE_VERSION_STRING
  ERROR_VARIABLE
    SimpleITK_LUA_EXECUTABLE_VERSION_STRING
  RESULT_VARIABLE
    SITK_LUA_VERSION_RESULT_VARIABLE
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_STRIP_TRAILING_WHITESPACE
  )

# Check that the Lua version is acceptable
#
if( NOT SITK_LUA_VERSION_RESULT_VARIABLE )
  string( REGEX MATCH "([0-9]*)([.])([0-9]*)([.]*)([0-9]*)"
    SimpleITK_LUA_EXECUTABLE_VERSION
    ${SimpleITK_LUA_EXECUTABLE_VERSION_STRING} )
endif()

if( SITK_LUA_VERSION_RESULT_VARIABLE
      OR
    NOT ${SimpleITK_LUA_EXECUTABLE_VERSION} VERSION_GREATER "5.1"
      OR
    NOT ${SimpleITK_LUA_EXECUTABLE_VERSION} VERSION_LESS "5.2" )
  message(SEND_ERROR "Lua version 5.1 is required for SimpleITK_LUA_EXECUTABLE_VERSION.")
endif()

# Sets "out_var" variable name to the value in the json path specified
# to the json file name. If an error is encountered than the variable
# is not updated.
#
function( get_json_path out_var json_file path )

  execute_process(COMMAND ${SimpleITK_LUA_EXECUTABLE}
     ${SimpleITK_SOURCE_DIR}/ExpandTemplateGenerator/JSONQuery.lua
     ${json_file}
     ${path}
     OUTPUT_VARIABLE value
     RESULT_VARIABLE ret
     ERROR_VARIABLE error_var)


   if ( NOT ${ret} )
     string(REGEX MATCH ":.*\"([^\"]+)\"" _out "${value}" )

     if(_out)
       set(${out_var} "${CMAKE_MATCH_1}" PARENT_SCOPE)
     endif()

   else()
     message( WARNING ${error_var} )
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
    message(WARNING "Error processing ${json_file}, unable to locate template_code_filename")
  endif()

endmacro()


###############################################################################
# This macro expands the .h and .cxx files for a given input template
#
function( expand_template FILENAME input_dir output_dir library_name )


  # Set common variables
  set ( expand_template_script ${SimpleITK_SOURCE_DIR}/ExpandTemplateGenerator/ExpandTemplate.lua )
  set ( template_include_dir ${SimpleITK_SOURCE_DIR}/ExpandTemplateGenerator/Components )
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

  # validate json files if python is available
  if ( PYTHON_EXECUTABLE AND NOT PYTHON_VERSION_STRING VERSION_LESS 2.6 )
    set ( JSON_VALIDATE_COMMAND COMMAND "${PYTHON_EXECUTABLE}" "${SimpleITK_SOURCE_DIR}/Utilities/JSON/JSONValidate.py" "${input_json_file}" )
  endif ()

  # header
  add_custom_command (
    OUTPUT "${output_h}"
    ${JSON_VALIDATE_COMMAND}
    COMMAND ${CMAKE_COMMAND} -E remove -f ${output_h}
    COMMAND ${SimpleITK_LUA_EXECUTABLE} ${expand_template_script} code ${input_json_file} ${input_dir}/templates/sitk ${template_include_dir} Template.h.in ${output_h}
    DEPENDS ${input_json_file} ${template_deps} ${template_file_h}
    )
  # impl
  add_custom_command (
    OUTPUT "${output_cxx}"
    COMMAND ${CMAKE_COMMAND} -E remove -f ${output_cxx}
    COMMAND ${SimpleITK_LUA_EXECUTABLE} ${expand_template_script} code ${input_json_file} ${input_dir}/templates/sitk ${template_include_dir} Template.cxx.in ${output_cxx}
    DEPENDS ${input_json_file} ${template_deps} ${template_file_cxx}
    )

  set ( ${library_name}GeneratedHeader ${${library_name}GeneratedHeader}
    "${output_h}" CACHE INTERNAL "" )

  set ( ${library_name}GeneratedSource ${${library_name}GeneratedSource}
    "${output_cxx}" CACHE INTERNAL "" )

  if (NOT "${itk_module}" STREQUAL "")
    list(APPEND ${library_name}GeneratedSource_${itk_module}  ${output_cxx} )
    set(${library_name}GeneratedSource_${itk_module} ${${library_name}GeneratedSource_${itk_module}} CACHE INTERNAL "")
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
      unset(${varName} CACHE)
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
  file ( WRITE "${tmp_generated_headers_h}" "#ifndef __SimpleITK${directory_name}GeneratedHeaders_h\n")
  file ( APPEND "${tmp_generated_headers_h}" "#define __SimpleITK${directory_name}GeneratedHeaders_h\n")

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
