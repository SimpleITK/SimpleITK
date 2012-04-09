/*=========================================================================
*
*  Copyright Insight Software Consortium
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/
#ifndef __sitkShow_h
#define __sitkShow_h

#include "sitkImage.h"
#include "sitkIO.h"

namespace itk
{
namespace simple
{

  /** Display an image using ImageJ
   *
   *  This function requires that ImageJ
   *  (http://rsb.info.nih.gov/ij/) be properly installed for Mac
   *  and Windows, and in the user's path for Linux.  ImageJ must have
   *  a plugin for reading Nifti formatted files (http://www.loci.wisc.edu/bio-formats/imagej).
   *
   *  Nifti is the default file format used to export images.  A different
   *  format can by chosen by setting the SITK_SHOW_EXTENSION environment variable.
   *  For example, set SITK_SHOW_EXTENSION to ".png" to use PNG format.
   *
   *  The user can specify an application other than ImageJ to view images via
   *  the SITK_SHOW_COMMAND environment variable.
   *
   *  The user can also select applications specifically for color images or 3D
   *  images using the SITK_SHOW_COLOR_COMMAND and SITK_SHOW_3D_COMMAND environment
   *  variables.
   *
   *  SITK_SHOW_COMMAND, SITK_SHOW_COLOR_COMMAND and SITK_SHOW_3D_COMMAND allow
   *  the following %tokens in their strings.
   *
   *      %a  for the ImageJ application
   *      %f  for SimpleITK's temporary image file
   *      %m  for the ImageJ color-image macro
   *
   *  For example, the default SITK_SHOW_COMMAND string on Linux systems is:
   *
   *      %a -o %f
   *
   *  After token substitution it may become:
   *
   *      ImageJ -o /tmp/Temp-65535-0.nii
   *
   *  For another example, the default SITK_SHOW_COLOR_COMMAND string on Mac OS X is:
   *
   *      open -a %a -n --args -eval %m
   *
   *  After token substitution the string may become:
   *
   *      open -a ImageJ64 -n --args -eval 'open("/tmp/TempFile-20238-0.nii"); run("Make Composite", "display=Composite");'
   *
   * If neither the "%f" or "%m" tokens are found, the temporary file name is automatically appended
   * to the command arguments.
   **/


   void SITKIO_EXPORT Show ( const Image &image, const std::string title = "" );
}
}

#endif
