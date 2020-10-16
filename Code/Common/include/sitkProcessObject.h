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
#ifndef sitkProcessObject_h
#define sitkProcessObject_h

#include "sitkCommon.h"
#include "sitkNonCopyable.h"
#include "sitkTemplateFunctions.h"
#include "sitkEvent.h"
#include "sitkImage.h"
#include "sitkImageConvert.h"

#include <iostream>
#include <list>

namespace itk {

#ifndef SWIG

  template< typename T, unsigned int NVectorDimension > class Vector;

  class ProcessObject;
  class Command;
  class EventObject;
#endif

  namespace simple {

  class Command;


  /** \class ProcessObject
   * \brief Base class for SimpleITK classes based on ProcessObject
   *
   */
  class SITKCommon_EXPORT ProcessObject:
      protected NonCopyable
  {
    public:
      using Self = ProcessObject;

      /**
       * Default Constructor that takes no arguments and initializes
       * default parameters
       */
      ProcessObject();

      /**
       * Default Destructor
       */
      virtual ~ProcessObject();

      // Print ourselves out
      virtual std::string ToString() const;

      /** return user readable name for the filter */
      virtual std::string GetName() const = 0;

      /** Turn debugging output on/off.
       *
       * Enabling debugging prints additional information to stdout
       * about the execution of the internal filters.
       * @{
       */
      virtual void DebugOn();
      virtual void DebugOff();
      /**@}*/

      /** Get the value of the debug flag.
       * @{
       */
      virtual bool GetDebug() const;
      virtual void SetDebug(bool debugFlag);
      /**@}*/

      /** Turn default debugging output value on/off.
       *
       * This is the initial values used for new classes and
       * procedural methods.
       */
      static void GlobalDefaultDebugOn();
      static void GlobalDefaultDebugOff();
      /**@}*/

      /** Get the value of the default debug flag.  */
      static bool GetGlobalDefaultDebug();
      static void SetGlobalDefaultDebug(bool debugFlag);
      /**@}*/

      /** Manage warnings produced by ITK.
       *
       * Enabled by default, this parameter may enable printing
       * of warnings indicating unstable state or parameters during
       * execution. It is a global value set for all ITK filters and
       * processes.
       * @{
       */
      static void GlobalWarningDisplayOn();
      static void GlobalWarningDisplayOff();
      static void SetGlobalWarningDisplay(bool flag);
      static bool GetGlobalWarningDisplay();
      /**@}*/

      /** \brief Access the global tolerance to determine congruent spaces.
       *
       * The default tolerance is governed by the
       * GlobalDefaultCoordinateTolerance and the
       * GlobalDefaultDirectionTolerance properties, defaulting to
       * 1.0e-6. The default tolerance for spatial comparison is then
       * scaled by the voxelSpacing for coordinates (i.e. the
       * coordinates must be the same to within one part per
       * million). For the direction cosines the values must be within
       * the current absolute tolerance.
       * @{
       */
      static double GetGlobalDefaultCoordinateTolerance();
      static void SetGlobalDefaultCoordinateTolerance(double );

      static double GetGlobalDefaultDirectionTolerance();
      static void SetGlobalDefaultDirectionTolerance(double);
      /**@}*/


      /** \brief Set/Get the default threader used for process objects.
       *
       * The possible available multi-threaders are:
       *  - "POOL" itk::PoolMultiThreader
       *  - "TBB" itk::TBBThreader (optional)
       *  - "PLATFORM" itk::PlatformMultiThreader
       *
       * The default and the available multi-threaders are
       * dependent upon ITK's configuration. See the ITK
       * documentation for more details about the behavior of the
       * multi-threaders.
       *
       * The environment variable "ITK_GLOBAL_DEFAULT_THREADER" can be
       * used to initialize this value.
       *
       * The set method returns true when the threader string is valid
       * and ITK's default is updated, otherwise false is returned. The
       * threader argument is not case sensitive.
       *
       * \sa itk::MultiThreaderBase itk::PoolMultiThreader
       * itk::TBBThreader itk::PlatformMultiThreader
       * @{
       */
      static bool SetGlobalDefaultThreader(const std::string &threader);
      static std::string GetGlobalDefaultThreader();
      /**@{*/

      /** Set the number of threads with which new process objects are
       *  initialized.
       *
       * If the environment variable
       * "ITK_GLOBAL_DEFAULT_NUMBER_OF_THREADS" is defined, then this
       * value is initialized as defined in the
       * environment. Otherwise, the value will be initialized with
       * the number of virtual CPUs on the system.
       *
       * \note After the "POOL" multi-thread initially constructs the
       * thread pool, this value will has no effect on the thread pool.
       * @{
       */
      static void SetGlobalDefaultNumberOfThreads(unsigned int n);
      static unsigned int GetGlobalDefaultNumberOfThreads();
      /**@}*/

      /** The number of threads used when executing a filter if the
       * filter is multi-threaded.
       *
       * With ITK version 5, this parameter now corresponds to
       * itk::MultiThreaderBase::SetMaximumNumberOfThreads and the
       * corresponding get method. The is clamped to be limited by the
       * "global" maximum.
       *
       * \note The "POOL" multi-threader cannot reduce the number of
       * threads. As the "POOL" multi-threader  has a single instance
       * of a thread pool, the number of threads will increased for
       * subsequent processes.
       * @{
       */
      virtual void SetNumberOfThreads(unsigned int n);
      virtual unsigned int GetNumberOfThreads() const;
      /**@}*/

      /** The work (image) is requested to be divided into this number
       * of sub-tasks.
       *
       * If zero then, the default number from the process object and
       * the multi-threader will be used.
       *
       * \note The "PLATFORM" multi-threader set the number of threads
       * equal to the number of work units.
       * @{
       */
      virtual void SetNumberOfWorkUnits(unsigned int n);
      virtual unsigned int GetNumberOfWorkUnits() const;
      /**@}*/


      /** \brief Add a Command Object to observer the event.
       *
       * The Command object's Execute method will be invoked when the
       * internal ITK Object has the event. These events only occur
       * during this ProcessObject's Execute method when the ITK
       * filter is running. The command occurs in the same thread as
       * this objects Execute methods was called in.
       *
       * An internal reference is made between the Command and this
       * ProcessObject which enable automatic removal of the command
       * when deleted. This enables both object to exist as stack
       * based object and be automatically cleaned up.
       *
       * Unless specified otherwise, it's safe to get any value during
       * execution. "Measurements" will have valid values only after
       * the Execute method has returned. "Active Measurements" will
       * have valid values during events, and access the underlying
       * ITK object.
       *
       * Deleting a command this object has during a command call-back
       * will produce undefined behavior.
       *
       * For more information see the page \ref CommandPage.
       *
       * \note The return value is reserved for latter usage.
       */
      virtual int AddCommand(itk::simple::EventEnum event, itk::simple::Command &cmd);

      #ifndef SWIG
      /** \brief Directly add a callback to observe an event.
       *
       * This overloaded method can take a C++ lambda function as a
       * second argument.
       */
      virtual int AddCommand(itk::simple::EventEnum event, const std::function<void()> &func);
      #endif

      /** \brief Remove all registered commands.
       *
       * Calling when this object is invoking anther command will
       * produce undefined behavior.
       */
      virtual void RemoveAllCommands();

      /** \brief Query of this object has any registered commands for event. */
      virtual bool HasCommand( itk::simple::EventEnum event ) const;


      /** \brief An Active Measurement of the progress of execution.
       *
       * Get the execution progress of the current process object. The
       * progress is a floating number in [0,1] with 0 meaning no progress and 1
       * meaning the filter has completed execution (or aborted).
       *
       * This is an Active Measurement so it can be accessed during
       * Events during the execution.
       */
      virtual float GetProgress( ) const;

      /** Sets an abort flag on the active process.
       *
       * Requests the current active process to abort. Additional,
       * progress or iteration event may occur. If aborted then, an
       * AbortEvent should occur. The Progress should be set to 1.0
       * after aborting.
       *
       * The expected behavior is that not exception should be throw
       * out of this processes Execute method. Additionally, the
       * results returned are valid but undefined content. The
       * content may be only partially updated, uninitialized or the a
       * of size zero.
       *
       * If there is no active process the method has no effect.
       */
      virtual void Abort();

    protected:

      #ifndef SWIG

      struct EventCommand
      {
        EventCommand(EventEnum e, Command *c)
          : m_Event(e), m_Command(c), m_ITKTag(std::numeric_limits<unsigned long>::max())
          {}
        EventEnum     m_Event;
        Command *     m_Command;

        // set to max if currently not registered
        unsigned long m_ITKTag;

        inline bool operator==(const EventCommand &o) const
          { return m_Command == o.m_Command; }
        inline bool operator<(const EventCommand &o) const
          { return m_Command < o.m_Command; }
      };

      // method called before filter update to set parameters and
      // connect commands.
      virtual void PreUpdate( itk::ProcessObject *p );

      // overridable method to add a command, the return value is
      // placed in the m_ITKTag of the EventCommand object.
      virtual unsigned long AddITKObserver(const itk::EventObject &, itk::Command *);

      // overridable method to remove a command
      virtual void RemoveITKObserver( EventCommand &e );

      // Create an ITK EventObject from the SimpleITK enumerated type.
      static const itk::EventObject &GetITKEventObject(EventEnum e);

      // returns the current active process, if no active process then
      // an exception is throw.
      virtual itk::ProcessObject *GetActiveProcess( );

      // overridable callback when the active process has completed
      virtual void OnActiveProcessDelete( );

      friend class itk::simple::Command;
      // method call by command when it's deleted, maintains internal
      // references between command and process objects.
      virtual void onCommandDelete(const itk::simple::Command *cmd) noexcept;
      #endif


      template< class TImageType >
        static typename TImageType::ConstPointer CastImageToITK( const Image &img )
      {
        typename TImageType::ConstPointer itkImage =
          dynamic_cast < const TImageType* > ( img.GetITKBase() );

        if ( itkImage.IsNull() )
          {
          sitkExceptionMacro("Failure to convert SimpleITK image of dimension: "
                             << img.GetDimension() << " and pixel type: \""
                             << img.GetPixelIDTypeAsString() << "\" to ITK image of dimension: "
                             << TImageType::GetImageDimension() << " and pixel type: \""
                             << GetPixelIDValueAsString(ImageTypeToPixelIDValue<TImageType>::Result)
                             << "\"!" )
          }
        return itkImage;
      }

      template< class TImageType >
        static Image CastITKToImage( TImageType *img )
      {
        return Image(img);
      }

#ifndef SWIG
      template< class TPixelType, unsigned int VImageDimension, unsigned int  VLength,
                template<typename, unsigned int> class TVector >
        static Image CastITKToImage( itk::Image< TVector< TPixelType, VLength >, VImageDimension> *img )
      {
        // The implementation defined int sitkImageConvert.hxx needs
        // to be manually included when this method is used.
        auto out = GetVectorImageFromImage(img, true);

        return Image(out.GetPointer());
      }
#endif

      /**
       * Output operator to os with conversion to a printable type.
       *
       * That is char types are presumed to be numbers, and converted
       * to int.
       * @{
       */
      template <typename T>
      static std::ostream & ToStringHelper(std::ostream &os, const T &v)
      {
        os << v;
        return os;
      }
      static std::ostream & ToStringHelper(std::ostream &os, const char &v);
      static std::ostream & ToStringHelper(std::ostream &os, const signed char &v);
      static std::ostream & ToStringHelper(std::ostream &os, const unsigned char &v);
      /**@}*/

    private:

      // Add command to active process object, the EventCommand's
      // ITKTag must be unset as max or else an exception is
      // thrown. The EventCommand's ITKTag is updated to the command
      // registered to ITK's ProcessObject. It's assumed that there is
      // an current active process
      unsigned long AddObserverToActiveProcessObject( EventCommand &e );

      // Remove the command from the active processes. Its is assumed
      // that an active process exists. The tag is set to max after it
      // is removed.
      void RemoveObserverFromActiveProcessObject( EventCommand &e );

      bool m_Debug;

      unsigned int m_NumberOfThreads;
      unsigned int m_NumberOfWorkUnits;

      std::list<EventCommand> m_Commands;

      itk::ProcessObject *m_ActiveProcess;

      //
      float m_ProgressMeasurement;
    };


  }
}
#endif
