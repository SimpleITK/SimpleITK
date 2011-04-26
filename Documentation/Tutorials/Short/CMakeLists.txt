project(SimpleITKShortTutorial)

#
# This adds a custom target that generates the output document
# This target depends on the list of copied files created
# with the custom command above and the Plots target.
#
add_custom_target(ShortTutorial ALL
   COMMAND ${PDFLATEX_COMPILER}
        ${SimpleITKShortTutorial_SOURCE_DIR}/SimpleITKShortTutorial.tex
        -output-directory ${SimpleITKShortTutorial_BINARY_DIR}
   COMMAND ${PDFLATEX_COMPILER}
        ${SimpleITKShortTutorial_SOURCE_DIR}/SimpleITKShortTutorial.tex
        -output-directory ${SimpleITKShortTutorial_BINARY_DIR}
   DEPENDS ${COPY_RESULTS} ${REPORT_ELEMENTS}
   WORKING_DIRECTORY ${SimpleITKShortTutorial_BINARY_DIR}
   )

