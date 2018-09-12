#
# CMake Module to check for TR1 and C++11 features
#
# SITK_HAS_CXX11_STATIC_ASSERT    - True if "static_assert" keyword is supported
# SITK_HAS_CXX11_FUNCTIONAL       - True if functional header has C++11 features
# SITK_HAS_CXX11_TYPE_TRAITS
# SITK_HAS_CXX11_UNORDERED_MAP
# SITK_HAS_CXX11_NULLPTR          - True if "nullptr" keyword is supported
# SITK_HAS_CXX11_UNIQUE_PTR
# SITK_HAS_CXX11_ALIAS_TEMPLATE   - Able to use alias templates
#
# SITK_HAS_TR1_SUB_INCLUDE
#
# SITK_HAS_TR1_FUNCTIONAL
# SITK_HAS_TR1_TYPE_TRAITS
# SITK_HAS_TR1_UNORDERED_MAP

include(CMakePushCheckState)

#
# Function to wrap try compiles on the aggregate cxx test file1
#
function(sitkCXX11Test VARIABLE)

  if(NOT DEFINED ${VARIABLE})
    message(STATUS "Performing Test ${VARIABLE}")

    if(NOT POLICY CMP0067)
      if(DEFINED CMAKE_CXX_STANDARD)
        set(cmake_flags "${cmake_flags} -DCMAKE_CXX_STANDARD:STRING:=${CMAKE_CXX_STANDARD}")
      endif()
      if(DEFINED CMAKE_CXX_STANDARD_REQUIRED)
        set(cmake_flags "${cmake_flags} -DCMAKE_CXX_STANDARD_REQUIRED:STRING:=${CMAKE_CXX_STANDARD_REQUIRED}")
      endif()
      if(DEFINED CMAKE_CXX_EXTENSIONS)
        set(cmake_flags "${cmake_flags} -DCMAKE_CXX_EXTENSIONS:STRING:=${CMAKE_CXX_EXTENSIONS}")
      endif()
    endif()

    try_compile(${VARIABLE}
      "${PROJECT_BINARY_DIR}"
      "${CMAKE_CURRENT_LIST_DIR}/sitk_check_cxx11.cxx"
      CMAKE_FLAGS ${cmake_flags}
      COMPILE_DEFINITIONS "-D${VARIABLE}" ${CMAKE_REQUIRED_DEFINITIONS}
      OUTPUT_VARIABLE output)

    set(${cache_var} ${${VARIABLE}} CACHE INTERNAL "hashed flags with  try_compile results")

    if(${VARIABLE})
      message(STATUS "Performing Test ${VARIABLE} - Success")
    else()
      message(STATUS "Performing Test ${VARIABLE} - Failed")
      file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeError.log
                 "Performing Test ${VARIABLE} failed with the following output:\n"
                 "${OUTPUT}\n")
    endif()
   endif()
endfunction()

cmake_push_check_state(RESET)

#
# Check for CXX11 Features
#
sitkCXX11Test(SITK_HAS_CXX11_STATIC_ASSERT)
sitkCXX11Test(SITK_HAS_CXX11_FUNCTIONAL)
sitkCXX11Test(SITK_HAS_CXX11_TYPE_TRAITS)
sitkCXX11Test(SITK_HAS_CXX11_UNORDERED_MAP)
sitkCXX11Test(SITK_HAS_CXX11_NULLPTR)
sitkCXX11Test(SITK_HAS_CXX11_UNIQUE_PTR)
sitkCXX11Test(SITK_HAS_CXX11_ALIAS_TEMPLATE)



# Microsoft Visual Studio 2008sp1,2010,2012 don't need tr1 as a path
# prefix to tr1 headers, while libc++
sitkCXX11Test(SITK_HAS_TR1_SUB_INCLUDE)

if (SITK_HAS_TR1_SUB_INCLUDE)
  list(APPEND CMAKE_REQUIRED_DEFINITIONS "-DHAS_TR1_SUB_INCLUDE")
endif()

#
# Check for TR1 features
#
sitkCXX11Test(SITK_HAS_TR1_FUNCTIONAL)
sitkCXX11Test(SITK_HAS_TR1_TYPE_TRAITS)
sitkCXX11Test(SITK_HAS_TR1_UNORDERED_MAP)

# restore variable
cmake_pop_check_state()


if ( (NOT SITK_HAS_TR1_FUNCTIONAL AND NOT SITK_HAS_CXX11_FUNCTIONAL)
    OR
    (NOT SITK_HAS_TR1_TYPE_TRAITS AND NOT SITK_HAS_CXX11_TYPE_TRAITS)
    )
  if (MSVC)
    message( FATAL_ERROR
      "SimpleITK requires usage of C++11 or C++ Technical Report 1 (TR1).\n"
      "It may be available as an optional download for your compiler or difference CXX_FLAGS."
      "Please see the FAQs for details."
      "http://simpleitk.readthedocs.io/en/master/Documentation/docs/source/faq.html#do-i-need-to-download-an-option-package-for-tr1-support\n")
  else()
      message( FATAL_ERROR
        "SimpleITK requires usage of C++11 or C++ Technical Report 1 "
        "(TR1), but were neither able to detect TR1 nor automatically "
        "enable C++11. Please review your configuration settings and "
        "enable C++11.\n")

  endif()
endif ()
