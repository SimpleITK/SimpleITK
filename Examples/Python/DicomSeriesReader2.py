#!/usr/bin/env python

# =========================================================================
#
#  Copyright NumFOCUS
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0.txt
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
# =========================================================================


#
#  This example shows how to read a specific series from a Dicom directory that
#  may contain more than one series.  The script scans for all series.  If an
#  output name is given, it writes out the requested series.  If no specific
#  series name is given, the first series found is written.
#

from __future__ import print_function

import sys
import getopt
import SimpleITK as sitk

target_series = ""
output_image = ""


def usage():
    print("\nUsage: %s [-s series_name] input_directory [output_image]\n"
          % (sys.argv[0]))


# Parse command line options
try:
    opts, args = getopt.getopt(sys.argv[1:], "s:", ["series"])
except getopt.GetoptError:
    usage()
    sys.exit(1)

for o, a in opts:
    if o in ("-s", "--series"):
        target_series = a
    else:
        assert False, "unhandled options"

# Get input/output names
if len(args) < 1:
    print(args)
    usage()
    sys.exit(1)

input_directory = args[0]
if len(args) > 1:
    output_image = args[1]

# Find the Dicom series
reader = sitk.ImageSeriesReader()
written = False

series_found = reader.GetGDCMSeriesIDs(input_directory)

# Process each Dicom series
if len(series_found):

    for serie in series_found:

        print("\nSeries:", serie)

        # Get the Dicom filename corresponding to the current series
        dicom_names = reader.GetGDCMSeriesFileNames(input_directory, serie)

        print("\nFiles in series: ", dicom_names)

        if len(dicom_names):
            reader.SetFileNames(dicom_names)
            image = reader.Execute()
            print("\nImage size: ", image.GetSize())

            if (output_image != "") and not written:
                if (target_series == "" or target_series == serie):
                    print("\nWriting", output_image)
                    sitk.WriteImage(image, output_image)
                    written = True
else:
    sys.exit(1)

print()
