
# include cmake macros for code generation
include(${SimpleITK_SOURCE_DIR}/Code/CodeGeneration/expand_template.cmake)


###############################################################################
# Macro to do all code generation for a given directory
#
macro(generate_filter_source)

  # Get the name of the current directory
  get_filename_component(directory_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

  ######
  # Perform template expansion
  ######

  # Set output directory corresponding to this input directory
  set(generated_code_output_path ${SimpleITK_BINARY_DIR}/Code/${directory_name})

  # Glob all json files in the current directory
  file ( GLOB json_config_files *.json)

  # Loop through json files and expand each one
  foreach ( f ${json_config_files} )
    get_filename_component ( class ${f} NAME_WE )
    expand_template ( ${class}
                      ${image_filter_template}
                      ${CMAKE_CURRENT_SOURCE_DIR}
                      ${generated_code_output_path}
                      SimpleITK${directory_name} )

  endforeach()


  ######
  # Make target for generated code
  ######
  add_custom_target(${directory_name}SourceCode ALL DEPENDS ${SimpleITK${directory_name}Source})
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
