#
# Usage: cmake -D "PROJECT_SOURCE_DIR:PATH=${PROJECT_SOURCE_DIR}" -D
# "OUTPUT_FILE:PATH=${PROJECT_BINARY_DIR}/Examples.dox" -P GenerateExamplesDox.cmake

# This cmake script gets a lists of examples for the project and generates a file suitable for doxygen. The file is a
# list of "\examples filename", where doxygen will search for fileanme in it's example path. Doxygen should then
# generate an examples page with the referenced files.

# glob the examples for each language
file(
  GLOB_RECURSE EXAMPLES_LIST
  RELATIVE "${PROJECT_SOURCE_DIR}/Examples"
  "*.cxx"
  "*.py"
  "*.java"
  "*.tcl"
  "*.rb"
  "*.R"
  "*.cs")

# remove the file before we begin appending
file(REMOVE ${OUTPUT_FILE})

# begin comment
file(APPEND ${OUTPUT_FILE} "namespace sitk = itk::simple;/**\n")

foreach(f IN LISTS EXAMPLES_LIST)
  file(APPEND ${OUTPUT_FILE} "\\example ${f}\n")
endforeach()

# end comment
file(APPEND ${OUTPUT_FILE} "*/\n")
