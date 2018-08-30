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
  * \brief Display an image in an external viewer (Fiji by default)
  *
  * The ImageViewer class displays an image with an external image display
  * application.  By default the class will search for a Fiji ( https://fiji.sc )
  * executable.  The image is written out to a temporary file and then passed
  * to the application.
  *
  * When SimpleITK is first invoked the following environment variables are
  * queried to set up the external viewer:
  *
  * SITK_SHOW_EXTENSION:  file format extension of the temporary image file.
  * The default is '.mha', the [MetaIO](https://itk.org/Wiki/ITK/MetaIO)
  * file format.
  *
  * SITK_SHOW_COMMAND:  The user can specify an application other than Fiji
  * to view images.
  *
  * These environment variables are only checked at SimpleITK's launch.
  */
class SITKIO_EXPORT ImageViewer
{

public:
  ImageViewer();

  /** \brief Set/Get the search path used to find the viewing application
   * @{
   */
  static void SetGlobalDefaultSearchPath( const std::vector<std::string> & path );
  static const std::vector<std::string> & GetGlobalDefaultSearchPath();
  /**@}*/

  /** \brief Set/Get name list used to find the viewing application
   * @{
   */
  static void SetGlobalDefaultExecutableNames( const std::vector<std::string> & names );
  static const std::vector<std::string> & GetGlobalDefaultExecutableNames();
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
   * \li \c '%a' for the image viewing application (Fiji by default)
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
   *  /opt/Fiji.app/ImageJ-linux64 -o /tmp/Temp-65535-0.mha
   *  \endcode
   *
   *  For another example, the default command string on Mac OS X is:
   *
   *  \code
   *  open -a %a -n --args -eval \'open(\"%f\"); rename(\"%t\"); \'
   *  \endcode
   *
   *  After token substitution the string may become:
   *
   *  \code
   *  open -a /Applications/Fiji.app -n --args -eval 'open("/tmp/TempFile-29696-0.mha"); rename("/tmp/TempFile-29696-0.mha");'
   *  \endcode
   *
   *  The string after \c '-eval' is an ImageJ macro the opens the file and sets the title of the window.
   *
   *  If the \c '%f' token is not found in the command string, the temporary file name is automatically
   *  appended to the command argument list.
   *
   *  Note: Using the ImageViewer::SetCommand method overrides the default command and/or the
   *  SITK_SHOW_COMMAND environment variable.
   * @{
   */
  void SetCommand( const std::string & command );
  const std::string & GetCommand() const;
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
  static void SetGlobalDebug( const bool dbg );
  static bool GetGlobalDebug();
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

  // hidden, no accessors
  static int m_GlobalViewerImageCount;
  static bool m_GlobalAreDefaultsInitialized;

  // global only
  static std::vector<std::string> m_GlobalDefaultSearchPath;
  static std::vector<std::string> m_GlobalDefaultExecutableNames;
  static unsigned int m_GlobalProcessDelay;

  static std::string m_GlobalDefaultViewCommand;
  static std::string m_GlobalDefaultFileExtension;
  static std::string m_GlobalDefaultApplication;


  static bool m_GlobalDebug;

  std::string viewCommand;
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
