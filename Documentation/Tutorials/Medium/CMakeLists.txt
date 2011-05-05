project(SimpleITKMediumTutorial)

#
# This adds a custom target that generates the output document
# This target depends on the list of copied files created
# with the custom command above and the Plots target.
#
add_custom_target(MediumTutorial ALL
   COMMAND ${PDFLATEX_COMPILER}
        ${SimpleITKMediumTutorial_SOURCE_DIR}/SimpleITKMediumTutorial.tex
        -output-directory ${SimpleITKMediumTutorial_BINARY_DIR}
   COMMAND ${PDFLATEX_COMPILER}
        ${SimpleITKMediumTutorial_SOURCE_DIR}/SimpleITKMediumTutorial.tex
        -output-directory ${SimpleITKMediumTutorial_BINARY_DIR}
   DEPENDS ${COPY_RESULTS} ${REPORT_ELEMENTS}
   WORKING_DIRECTORY ${SimpleITKMediumTutorial_BINARY_DIR}
   )

