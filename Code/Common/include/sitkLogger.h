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
#ifndef sitkLogger_h
#define sitkLogger_h


#include "sitkCommon.h"
#include "sitkObjectOwnedBase.h"
#include "sitkProcessObjectDeleter.h"

#include <memory>


namespace itk
{

class OutputWindow;

namespace simple
{

class ITKLogger;

/** \brief A base class to handle SimpleITK and ITK messages and logging.
 *
 * In ITK this function is implemented by the itk::OutputWindow, but in SimpleITK it is called a logger.
 *
 * Provides a base class for SimpleITK to provide the "DisplayText" methods similar to the itk::OutputWindow. Derived
 * instances of LoggerBase are used by an internal adaptor derived from the itk::OutputWindow so that this object
 * instances can be used in ITK.
 *
 * \sa itk::OutputWindow
 */
class SITKCommon_EXPORT LoggerBase : public ObjectOwnedBase
{
public:
  LoggerBase();

  ~LoggerBase() override;

  virtual void
  DisplayText(const char * t)
#ifndef SWIGR
    = 0
#endif
    ;

  virtual void
  DisplayErrorText(const char * t);
  virtual void
  DisplayWarningText(const char * t);


  virtual void
  DisplayGenericOutputText(const char * t);

  virtual void
  DisplayDebugText(const char * t);

  virtual void
  DisplayErrorText(const char * message,
                   const char * file,
                   unsigned int line,
                   const char * className,
                   const void * objectAddress);


  virtual void
  DisplayWarningText(const char * message,
                     const char * file,
                     unsigned int line,
                     const char * className,
                     const void * objectAddress);


  virtual void
  DisplayGenericOutputText(const char * message, const char * file, unsigned int line);


  virtual void
  DisplayDebugText(const char * message,
                   const char * file,
                   unsigned int line,
                   const char * className,
                   const void * objectAddress);


  std::string
  GetName() const override;
  void
  SetName(const std::string & n) override;

  /** Set this logger instance to the ITK output window.
   *
   * After calling this method, all ITK and SimpleITK display, warning and error texts will be handled by this object's
   * methods.
   *
   * @return An ITKLogger object holding the previous itk::OutputWindow instance. The returned object can be used to
   * restore the original instance.
   */
  virtual ITKLogger
  SetAsGlobalITKLogger();

  /** Get the current logger used by ITK.
   *
   * @return
   */
  static ITKLogger
  GetGlobalITKLogger();
};

#if defined(SWIG)
#  define SITK_FINAL
#else
#  define SITK_FINAL final
#endif

/** A class to hold itk::OutputWindows instances.
 *
 * All "DisplayText" methods are forwarded to the held OutputWindow instance.
 *
 * Neither the ownership nor callback functionality of the ObjectOwnedBase is supported.
 */
class SITKCommon_EXPORT ITKLogger SITK_FINAL : public LoggerBase
{
public:
  explicit ITKLogger(itk::OutputWindow *);
  ~ITKLogger() override;

  ITKLogger();
  ITKLogger(const ITKLogger &);
  ITKLogger & operator=(ITKLogger);

  void
  DisplayText(const char * t) override;

  void
  DisplayErrorText(const char * t) override;

  void
  DisplayErrorText(const char * message,
                   const char * file,
                   unsigned int line,
                   const char * className,
                   const void * objectAddress) override;

  void
  DisplayWarningText(const char * t) override;

  void
  DisplayWarningText(const char * message,
                     const char * file,
                     unsigned int line,
                     const char * className,
                     const void * objectAddress) override;

  void
  DisplayGenericOutputText(const char * t) override;

  void
  DisplayGenericOutputText(const char * message, const char * file, unsigned int line) override;

  void
  DisplayDebugText(const char * t) override;

  void
  DisplayDebugText(const char * message,
                   const char * file,
                   unsigned int line,
                   const char * className,
                   const void * objectAddress) override;

  /** Set the ITK logger to the ITK OutputWindow instance held.
   *
   * Overrides the base functionality to eliminate the creation of the intermediary adaptor class.
   *
   * @return The previous logger.
   */
  ITKLogger
  SetAsGlobalITKLogger() override;


private:
  std::unique_ptr<itk::OutputWindow, ProcessObjectDeleter> m_OutputWindow;
};

} // namespace simple
} // namespace itk

#endif
