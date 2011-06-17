find_package(LATEX)

if(NOT PDFLATEX_COMPILER)
  message(FATAL_ERROR "pdflatex compiler was not found. Please pass to advanced mode and provide its full path")
endif()

add_subdirectory(Short)
add_subdirectory(Medium)
