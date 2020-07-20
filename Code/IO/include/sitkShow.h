/*=========================================================================
*
*  Copyright NumFOCUS
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
#include "sitkProcessObject.h"

namespace itk
{
namespace simple
{

  /** Display an image in an external viewer (Fiji by default)
   *
   *  The Show function displays an image with an external image display
   *  application.  By default Show will search for a Fiji ( https://fiji.sc )
   *  executable.  The image is written out to a temporary file and then passed
   *  to the application.
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
   *  Note that the environment variables are only checked when SimpleITK is first launched.
   *  This behavior is different than previous versions of SimpleITK, where the variables
   *  were checked every time Show was called.
   *
   *  If the \c "%f" token is not found in the command string, the temporary file name is automatically
   *  appended to the command argument list.
   *
   *  The boolean parameter debugOn prints the search path Show uses to find Fiji, the full path
   *  to the Fiji it found, and the full command line used to invoke it.
   *
   **/
   void SITKIO_EXPORT Show ( const Image &image, const std::string& title = "", const bool debugOn=ProcessObject::GetGlobalDefaultDebug() );
}
}

#endif
