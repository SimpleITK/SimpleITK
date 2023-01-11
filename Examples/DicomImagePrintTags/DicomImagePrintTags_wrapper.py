# --- hide: start ---
# DicomImagePrintTags_wrapper is called in the Documentation.rst to run the DicomImagePrintTags.py script
# from within the Sphinx documentation system to produce sample output.
# The "hide:" directives are necessary to keep this code from being displayed in the documentation.
import sys
sys.path.append('../Examples/DicomImagePrintTags')

from DicomImagePrintTags import main

args = ['Dicom_script', 'images/Image0075.dcm']
main(args)
# --- hide: stop ---
