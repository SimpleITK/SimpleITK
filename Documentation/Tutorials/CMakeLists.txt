find_package(LATEX)

if(NOT PDFLATEX_COMPILER)
  message("pdflatex compiler was not found. Please pass to advanced mode and provide its full path" FATAL_ERROR)
endif()

add_subdirectory(Short)
add_subdirectory(Medium)

