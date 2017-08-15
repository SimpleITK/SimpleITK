# CMake Module to check for usage of the `template` keyword to
# disambiguate dependent name look ups.
#
# More information can be found about this usage case here:
#  http://en.cppreference.com/w/cpp/language/dependent_name Under the
# heading "The typename disambiguator for dependent names".



try_compile(SITK_HAS_TEMPLATE_DISAMBIGUATOR_DEPENDENT_NAME
  "${PROJECT_BINARY_DIR}"
  "${CMAKE_CURRENT_LIST_DIR}/sitkCheckTemplateDisambiguation.cxx")
