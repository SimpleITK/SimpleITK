#
# Packaging
#

if( WRAP_PYTHON )
  add_custom_target( dist.Python
    ${PYTHON_EXECUTABLE} ${SimpleITK_BINARY_DIR}/Wrapping/PythonPackage/setup.py bdist_egg
    COMMENT "Creating Python egg for distribution" )
endif()

# A general packaging target, not built by default, to build packages for each
# language.  This should depend on all language specific targets.
add_custom_target( dist cmake -E echo "Finished generating wrapped packages for distribution..." )
add_dependencies( dist dist.Python )
