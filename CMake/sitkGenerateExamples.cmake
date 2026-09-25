include_guard(GLOBAL)

# ---------------------------------------------------------------------------
# sitkGenerateExamples.cmake
#
# Provides sitk_generate_filter_examples(), which reads
# Examples/example_filter_list.yaml and registers add_custom_command rules
# that expand every Jinja2 template in
# ExpandTemplateGenerator/templates/examples/ for each listed filter.
#
# A custom target "GenerateFilterExamples" is created that depends on all
# generated files.  The generated files are written into the source tree
# (Examples/<FilterName>/) so that they can be reviewed and committed.
#
# Requirements:
#   - SimpleITK_Python_EXECUTABLE must be set (or findable via find_package).
#   - SimpleITK_EXPANSION_SCRIPT must be set (or derivable from this file's
#     location relative to ExpandTemplateGenerator/).
#   - The pyyaml and jinja2 Python packages must be installed.
# ---------------------------------------------------------------------------

# --- Locate Python ----------------------------------------------------------

if(NOT DEFINED SimpleITK_Python_EXECUTABLE)
  if(DEFINED Python_EXECUTABLE)
    set(SimpleITK_Python_EXECUTABLE "${Python_EXECUTABLE}")
  else()
    find_package(Python 3.9...<4 REQUIRED COMPONENTS Interpreter)
    set(SimpleITK_Python_EXECUTABLE "${Python_EXECUTABLE}")
  endif()
  set(
    SimpleITK_Python_EXECUTABLE
    "${SimpleITK_Python_EXECUTABLE}"
    CACHE FILEPATH
    "Python executable used for code generation."
  )
endif()

# --- Locate the expansion script --------------------------------------------

if(NOT DEFINED SimpleITK_EXPANSION_SCRIPT)
  # CMAKE_CURRENT_LIST_DIR is <src>/CMake/; sibling dir holds the script.
  get_filename_component(
    _sitk_source_root
    "${CMAKE_CURRENT_LIST_DIR}/.."
    ABSOLUTE
  )
  set(
    SimpleITK_EXPANSION_SCRIPT
    "${_sitk_source_root}/ExpandTemplateGenerator/ExpandTemplate.py"
    CACHE INTERNAL
    "Python script used to expand templates."
    FORCE
  )
endif()

if(NOT EXISTS "${SimpleITK_EXPANSION_SCRIPT}")
  message(
    FATAL_ERROR
    "sitkGenerateExamples: ExpandTemplate.py not found at "
    "'${SimpleITK_EXPANSION_SCRIPT}'. "
    "Set SimpleITK_EXPANSION_SCRIPT to its location."
  )
endif()

# ---------------------------------------------------------------------------
# sitk_generate_filter_examples()
#
# Reads Examples/example_filter_list.yaml, then for every filter name listed
# creates add_custom_command rules to expand all example Jinja2 templates.
# All generated files are placed in Examples/<FilterName>/ inside the source
# tree so they can be committed alongside hand-written examples.
#
# A single custom target "GenerateFilterExamples" is created that depends on
# every output file.
#
# Optional keyword arguments
#   FILTER_LIST_YAML  <path>   Override the default filter list YAML location.
#   YAML_DIR          <path>   Override the default Code/BasicFilters/yaml/ dir.
#   TEMPLATE_DIR      <path>   Override the default templates/examples/ dir.
#   OUTPUT_BASE       <path>   Override the default Examples/ output directory.
# ---------------------------------------------------------------------------
function(sitk_generate_filter_examples)
  cmake_parse_arguments(
    _GFE
    ""
    "FILTER_LIST_YAML;YAML_DIR;TEMPLATE_DIR;OUTPUT_BASE"
    ""
    ${ARGN}
  )

  # Resolve source root relative to this file.
  get_filename_component(_src_root "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)

  # Apply defaults for any arguments not provided.
  if(NOT _GFE_FILTER_LIST_YAML)
    set(_GFE_FILTER_LIST_YAML "${_src_root}/Examples/example_filter_list.yaml")
  endif()
  if(NOT _GFE_YAML_DIR)
    set(_GFE_YAML_DIR "${_src_root}/Code/BasicFilters/yaml")
  endif()
  if(NOT _GFE_TEMPLATE_DIR)
    set(
      _GFE_TEMPLATE_DIR
      "${_src_root}/ExpandTemplateGenerator/templates/examples"
    )
  endif()
  if(NOT _GFE_OUTPUT_BASE)
    set(_GFE_OUTPUT_BASE "${_src_root}/Examples")
  endif()

  # --- Read the filter list from YAML at configure time --------------------

  execute_process(
    COMMAND
      "${SimpleITK_Python_EXECUTABLE}" -c
      "import sys, yaml\n\
try:\n\
    from yaml import CSafeLoader as Loader\n\
except ImportError:\n\
    from yaml import SafeLoader as Loader\n\
data = yaml.load(open(sys.argv[1]), Loader=Loader)\n\
filters = data.get('filters', [])\n\
print(';'.join(str(f) for f in filters))"
      "${_GFE_FILTER_LIST_YAML}"
    OUTPUT_VARIABLE _filter_names
    RESULT_VARIABLE _ret
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
  )

  if(_ret)
    message(
      FATAL_ERROR
      "sitkGenerateExamples: Failed to parse filter list from "
      "'${_GFE_FILTER_LIST_YAML}'."
    )
  endif()

  if(NOT _filter_names)
    message(
      WARNING
      "sitkGenerateExamples: No filters found in '${_GFE_FILTER_LIST_YAML}'."
    )
    return()
  endif()

  # --- Template → output filename table ------------------------------------
  #
  # Pairs of (template_file  output_filename_pattern).
  # The pattern may use '*' as a placeholder for the filter name.
  # ---------------------------------------------------------------------------

  set(
    _template_output_pairs
    "ExampleTemplate.py.jinja"
    "*.py"
    "ExampleTemplate.cxx.jinja"
    "*.cxx"
    "ExampleTemplate.cs.jinja"
    "*.cs"
    "ExampleTemplate.java.jinja"
    "*.java"
    "ExampleTemplate.lua.jinja"
    "*.lua"
    "ExampleTemplate.R.jinja"
    "*.R"
    "ExampleTemplate.rb.jinja"
    "*.rb"
    "ExampleDocumentation.rst.jinja"
    "Documentation.rst"
    "ExampleCMakeLists.cmake.jinja"
    "CMakeLists.txt"
  )

  # Collect all .jinja files for use as blanket DEPENDS.
  file(GLOB _all_jinja_files "${_GFE_TEMPLATE_DIR}/*.jinja")

  # --- Create custom commands per filter × template ------------------------

  set(_all_outputs)

  foreach(_filter IN LISTS _filter_names)
    set(_config_file "${_GFE_YAML_DIR}/${_filter}.yaml")

    if(NOT EXISTS "${_config_file}")
      message(
        WARNING
        "sitkGenerateExamples: No YAML file found for '${_filter}' "
        "at '${_config_file}'. Skipping."
      )
      continue()
    endif()

    set(_out_dir "${_GFE_OUTPUT_BASE}/${_filter}")

    # Iterate over template/output pairs (step 2 through the list).
    list(LENGTH _template_output_pairs _pair_list_len)
    math(EXPR _last_idx "${_pair_list_len} - 1")

    foreach(_i RANGE 0 ${_last_idx} 2)
      list(GET _template_output_pairs "${_i}" _template_file)
      math(EXPR _j "${_i} + 1")
      list(GET _template_output_pairs "${_j}" _output_pattern)

      # Replace '*' wildcard with the filter name.
      string(REPLACE "*" "${_filter}" _output_name "${_output_pattern}")
      set(_output_file "${_out_dir}/${_output_name}")

      add_custom_command(
        OUTPUT
          "${_output_file}"
        COMMAND
          "${CMAKE_COMMAND}" -E make_directory "${_out_dir}"
        COMMAND
          "${SimpleITK_Python_EXECUTABLE}" "${SimpleITK_EXPANSION_SCRIPT}"
          "${_config_file}" "${_template_file}" -D "${_GFE_TEMPLATE_DIR}" -o
          "${_output_file}"
        DEPENDS
          "${_config_file}"
          "${_GFE_TEMPLATE_DIR}/${_template_file}"
          "${SimpleITK_EXPANSION_SCRIPT}"
          "${_GFE_FILTER_LIST_YAML}"
          ${_all_jinja_files}
        COMMENT "Generating example for ${_filter}: ${_output_name}"
        VERBATIM
      )

      list(APPEND _all_outputs "${_output_file}")
    endforeach()
  endforeach()

  # --- Top-level target ------------------------------------------------------

  add_custom_target(
    GenerateFilterExamples
    DEPENDS
      ${_all_outputs}
    COMMENT "Generating all filter example files"
  )
endfunction()
