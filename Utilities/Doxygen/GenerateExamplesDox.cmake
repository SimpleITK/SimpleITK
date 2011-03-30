#
# Usage: cmake -D "PROJECT_SOURCE_DIR:PATH=${PROJECT_SOURCE_DIR}" 
#              -D "OUTPUT_FILE:PATH=${PROJECT_BINARY_DIR}/Examples.dox"
#              -P GenerateExamplesDox.cmake 

# This cmake script gets a lists of example for the project and
# generate a file suitable for doxygen. The file is a  list of
# "\examples filename", where doxygen will search for fileanme in it's
# example path. Doxygen should then generate an examples page with the
# referenced files.

# glob the examples for each language
file( GLOB_RECURSE EXAMPLES_CXX RELATIVE "${PROJECT_SOURCE_DIR}/Examples" "*.cxx"  )
file( GLOB_RECURSE EXAMPLES_PYTHON RELATIVE "${PROJECT_SOURCE_DIR}/Examples" "*.py"  )
file( GLOB_RECURSE EXAMPLES_JAVA RELATIVE "${PROJECT_SOURCE_DIR}/Examples" "*.java"  )
file( GLOB_RECURSE EXAMPLES_TCL RELATIVE "${PROJECT_SOURCE_DIR}/Examples" "*.tcl"  )
file( GLOB_RECURSE EXAMPLES_RUBY RELATIVE "${PROJECT_SOURCE_DIR}/Examples" "*.rb"  )
file( GLOB_RECURSE EXAMPLES_R RELATIVE "${PROJECT_SOURCE_DIR}/Examples" "*.R"  )

# append the lists together
set( EXAMPLES_LIST "${EXAMPLES_CXX};${EXAMPLES_PYTHON};${EXAMPLES_JAVA};${EXAMPLES_TCL};${EXAMPLES_RUBY};${EXAMPLES_R}" )

# remove the file before we begin appending
file( REMOVE ${OUTPUT_FILE} )

# begin comment
file( APPEND ${OUTPUT_FILE} "/*\n")

FOREACH( f IN LISTS EXAMPLES_LIST )
  file( APPEND ${OUTPUT_FILE}  "\\example ${f}\n" )
ENDFOREACH( f IN LIST EXAMPLES_LIST )

# end comment
file( APPEND ${OUTPUT_FILE}  "*/\n" )