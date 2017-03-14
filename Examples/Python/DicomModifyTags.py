#=========================================================================
#
#  Copyright Insight Software Consortium
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
#=========================================================================

from __future__ import print_function

import SimpleITK as sitk

import sys, time

if len( sys.argv ) < 3:
    print( "Usage: python " + __file__ + " <input_image> <output_image>" )
    sys.exit ( 1 )

# Read the image, single 3D DICOM slice
image = sitk.ReadImage( sys.argv[1] )

# Modify the image (mean)
mean_image = sitk.BoxMean( image, [3,3,1] )

# Save the modified image:
# We do not provide a method that copies all keys blindly. Our intent is
# to force us to remember that we always need to modify the meta-data dicitonary
# keys when we save processed images in DICOM format.
# In case of the DICOM format, amongst other keys we need to set the Image Type (0008,0008),
# the Series Date (0008,0021), and Series Time (0008,0021). Obviously we need to set a
# different series number (0020,0011), series instance UID (0020,000E), etc. - we don't do
# that here.
# Please see the DICOM standard (http://dicom.nema.org/standard.html) for complete details on
# how to create valid DICOM images.

all_keys = image.GetMetaDataKeys()
for key in all_keys:
    mean_image.SetMetaData( key, image.GetMetaData( key ) )
mean_image.SetMetaData( "0008|0008", "DERIVED\SECONDARY" )
modification_time = time.strftime("%H%M%S")
modification_date = time.strftime("%Y%m%d")
mean_image.SetMetaData( "0008|0031", modification_time )
mean_image.SetMetaData( "0008|0021", modification_date )

sitk.WriteImage( mean_image, sys.argv[2] )

# Finally, read the image back and see that changes were made
# Note that the image type (0008|0008) can contain additional spaces. The requirement is that
# the string have an even length (ftp://dicom.nema.org/medical/DICOM/2013/output/chtml/part05/sect_6.2.html).
# Where spaces are added is not specified and thus may vary ("DERIVED\SECONDARY ", "DERIVED\ SECONDARY" are
# equivalent).
modified_image = sitk.ReadImage( sys.argv[2] )
if modified_image.GetMetaData( "0008|0008" ).replace(" ","") != "DERIVED\SECONDARY" or \
   modified_image.GetMetaData( "0008|0031" ) != modification_time or \
   modified_image.GetMetaData( "0008|0021" ) != modification_date:
    sys.exit(1)

sys.exit( 0 )
