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
#ifndef sitkImageViewer_h
#define sitkImageViewer_h

#include "sitkImage.h"
#include "sitkIO.h"
#include "sitkProcessObject.h"

namespace itk
{
namespace simple
{

/** \class ImageViewer
  * \brief Display an image in an external viewer (Fiji/ImageJ be default)
  *
  * The ImageViewer class displays an image with an external image display
  * application.  By default the class will search for a Fiji ( https://fiji.sc )
  * or ImageJ ( https://imagej.nih.gov/ij/ ) executable.  The image is written
  * out to a temporary file and then passed to the application.
  *
  * When SimpleITK is first invoked the following environment variables are
  * queried to set up the external viewer:
  *
  * SITK_SHOW_EXTENSION:  file format extension of the temporary image file.
  *   The default is '.nii', the Nifti file format, because it supports the
  *   most vector pixel types.  k
  *
  * SITK_SHOW_COMMAND:  The user can specify an application other than ImageJ
  *   to view images.
  *
  * SITK_SHOW_COLOR_COMMAND:  Specify a different application for color images.
  *
  * SITK_SHOW_3D_COMMAND:  Specify a different application for 3D images.
  *
  * These environment variables are only checked at SimpleITK's launch.
  */
class ImageViewer
{

public:
  ImageViewer();

  /** \brief Set/Get the search path used to find the viewing application
   * @{
   */
  static void SetSearchPath( const std::vector<std::string> & path );
  static const std::vector<std::string> & GetSearchPath();
  /**@}*/

  /** \brief Set/Get name list used to find the viewing application
   * @{
   */
  static void SetExecutableNames( const std::vector<std::string> & names );
  static const std::vector<std::string> & GetExecutableNames();
  /**@}*/

  /** \brief Set/Get the full path to the viewing application.
   *
   * The SetApplication method expects a full path name.  Using
   * this method overrides the default application search.
   * @{
   */
  void SetApplication( const std::string & app );
  const std::string & GetApplication() const;
  /**@}*/

  /** \brief Set/Get command string used to launch the viewing application
   *
   * This command string may include the following %tokens:
   *
   * \li \c '%a' for the image viewing application (Fiji or ImageJ by default)
   * \li \c '%f' for SimpleITK's temporary image file
   *
   *  For example, the default command string on Linux systems is:
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
   *  For another example, the default command string for color images on Mac OS X is:
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
   *  The string after \c '-eval' is an ImageJ macro the opens the file and runs ImageJ's Make Composite
   *  command to display the image in color.
   *
   *  If the \c '%f' token is not found in the command string, the temporary file name is automatically
   *  appended to the command argument list.
   *
   *  Note: Using the ImageViewer::SetCommand method overrides the default command and/or any environment
   *  variable setting such as SITK_SHOW_COMMAND, SITK_SHOW_COLOR_COMMAND and SITK_SHOW_3D_COMMAND.
   * @{
   */
  void SetCommand( const std::string & command );
  const std::string & GetCommand(bool fijiFlag=false, bool colorImage=false, bool threeDImage=false) const;
  /**@}*/

  /** \brief Set/Get file extension of the temporary image file (default='.nii')
   *
   * If the viewing application is Fiji, the default image format is [MetaIO](https://itk.org/Wiki/ITK/MetaIO), '.mha'.
   *
   * If the viewing application is ImaegJ, the default image format is [NifTi](https://nifti.nimh.nih.gov/nifti-1/), '.nii'.  This is because by default ImageJ does not come with the MetaIO plugin.
   * @{
   */
  void SetFileExtension( const std::string & ext );
  const std::string & GetFileExtension() const;
  /**@}*/

  /** \brief Set/Get Debug flag.
   *
   * Turning on the Debug flag produces output showing the command string used to
   * launch the viewing application.
   * @{
   */
  static void SetDebug( const bool dbg );
  static bool GetDebug();
  /**@}*/

  /** \brief Set/Get Process delay, the wait time after launching the viewing application.
   *
   * On Windows the delay is in seconds, default=1sec.
   * On Mac/Linux the delay is in milli-seconds, default=500ms.
   * @{
   */
  static void SetProcessDelay( const unsigned int delay);
  static unsigned int GetProcessDelay();
  /**@}*/

  /** \brief Set/Get Title string on the ImageJ window.
   * @{
   */
  void SetTitle( const std::string & t );
  const std::string & GetTitle() const;
  /**@}*/

  /** \brief Launch the viewing application with to display the given image.
   */
  void Execute ( const Image &image );

  /** \brief Print ourself out to a string.
   */
  std::string ToString() const;


private:

  static int ViewerImageCount;
  static bool AreDefaultsInitialized;
  static std::string DefaultViewCommand;
  static std::string DefaultViewColorCommand;
  static std::string DefaultView3DCommand;
  static std::string DefaultFijiCommand;
  static std::vector<std::string> SearchPath;
  static std::vector<std::string> ExecutableNames;
  static std::string DefaultFileExtension;
  static std::string DefaultApplication;
  static bool DebugOn;
  static unsigned int ProcessDelay;


  std::string viewCommand;
  std::string view3DCommand;
  std::string viewColorCommand;
  std::string fijiCommand;
  std::string customCommand;

  std::string application;

  std::string fileExtension;

  std::string title;

  static void initializeDefaults();

  static std::string FindViewingApplication();
};

}
}
#endif
