#!/usr/bin/env bash


GROOVEY="/usr/bin/groovy"
SIMPLEITK="${HOME}/src/SimpleITK"
ITK_XML="${HOME}/temp/xml"


${GROOVEY} "${SIMPLEITK}/Utilities/GenerateDocumentation.groovy" "$1"  ${ITK_XML}
python "${SIMPLEITK}/Utilities/JSONBeautify.py" $1
