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
#ifndef __sitkProcessObject_h
#define __sitkProcessObject_h

#include "sitkMacro.h"
#include "sitkBasicFilters.h"
#include "sitkNonCopyable.h"
#include "sitkObserverBase.h"

namespace itk {

#ifndef SWIG
  class ProcessObject;
#endif

  namespace simple {

  /** \class ProcessObject
   * \brief Base class for SimpleITK classes based on ProcessObject
   *
   */
  class SITKBasicFilters0_EXPORT ProcessObject:
      protected NonCopyable
  {
    public:
      typedef ProcessObject Self;

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
      virtual std::string ToString() const = 0;

      /** return user readable name fo the filter */
      virtual std::string GetName() const = 0;

      /** Turn debugging output on/off.
       *
       * Enabling debugging prints additional information to stdout
       * about the execution of the internal filters.
       */
      virtual void DebugOn();
      virtual void DebugOff();

      /** Get the value of the debug flag. */
      virtual bool GetDebug() const;
      virtual void SetDebug(bool debugFlag);

      /** Turn default debugging output value on/off.
       *
       * This is the initial values used for new classes and
       * procedural methods.
       */
      static void GlobalDefaultDebugOn();
      static void GlobalDefaultDebugOff();

      /** Get the value of the default debug flag.  */
      static bool GetGlobalDefaultDebug();
      static void SetGlobalDefaultDebug(bool debugFlag);

      /** Set the number of threads that all new process objects are
       *  initialized with. */
      static void SetGlobalDefaultNumberOfThreads(unsigned int n);
      static unsigned int GetGlobalDefaultNumberOfThreads();

      /** The number of threads used when executing a filter if the
      * filter is multi-threaded */
      void SetNumberOfThreads(unsigned int n);
      unsigned int GetNumberOfThreads() const;


    protected:

      #ifndef SWIG
      virtual void PreUpdate( itk::ProcessObject *p );
      #endif

      /**
       * Output operator to os with conversion to a printable type.
       *
       * That is char types are presumed to be numbers, and converted
       * to int.
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

    private:

      bool m_Debug;
      unsigned int m_NumberOfThreads;

    };


  }
}
#endif
