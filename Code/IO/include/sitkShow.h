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
#ifndef sitkShow_h
#define sitkShow_h

#include "sitkImage.h"
#include "sitkIO.h"

namespace itk
{
namespace simple
{

  /** Display an image using Fiji, ImageJ or another application.
   *
   *  This function requires that Fiji ( https://fiji.sc ) or ImageJ
   *  (http://rsb.info.nih.gov/ij/) be properly installed for Mac
   *  and Windows, and in the user's path for Linux.  ImageJ must have
   *  a plugin for reading Nifti formatted files (http://www.loci.wisc.edu/bio-formats/imagej).
   *
   *  Nifti is the default file format used to export images.  A different
   *  format can be chosen by setting the SITK_SHOW_EXTENSION environment variable.
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
   *      \li \c "%a"  for the ImageJ application
   *      \li \c "%f"  for SimpleITK's temporary image file
   *
   *  For example, the default SITK_SHOW_COMMAND string on Linux systems is:
   *
   *  \code
   *  %a -o %f
   *  \endcode
   *
   *  After token substitution it may become:
   *
   *  \code
   *  ImageJ -o /tmp/Temp-65535-0.nii
   *  \endcode
   *
   *  For another example, the default SITK_SHOW_COLOR_COMMAND string on Mac OS X is:
   *
   *  \code
   *  open -a %a -n --args -eval \'open(\"%f\"); run(\"Make Composite\", \"display=Composite\"); \'
   *  \endcode
   *
   *  After token substitution the string may become:
   *
   *  \code
   *  open -a ImageJ64 -n --args -eval 'open("/tmp/TempFile-20238-0.nii"); run("Make Composite", "display=Composite");'
   *  \endcode
   *
   *  The string after \c "-eval" is an ImageJ macro the opens the file and runs ImageJ's Make Composite
   *  command to display the image in color.
   *
   *  If the \c "%f" token is not found in the command string, the temporary file name is automatically
   *  appended to the command argument list.
   *
   *
   *  When invoked, Show searches for Fiji first, and then ImageJ.   Fiji is the most update-to-date
   *  version of ImageJ and includes a lot of plugins which facilitate scientific image analysis.
   *  By default, for a 64-bit build of SimpleITK on Macs, sitkShow searches for ImageJ64.app.
   *  For a 32-bit Mac build, sitkShow searches for ImageJ.app.  If the user prefers a different
   *  version of ImageJ (or a different image viewer altogether), it can be specified using
   *  the SITK_SHOW_COMMAND environment variable.
   *
   *  The boolean parameter debugOn prints the search path Show uses to find ImageJ, the full path
   *  to the ImageJ it found, and the full command line used to invoke ImageJ.
   *
   **/


   void SITKIO_EXPORT Show ( const Image &image, const std::string& title = "", const bool debugOn=false );
}
}

#endif
