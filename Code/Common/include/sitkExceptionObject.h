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
#ifndef sitkExceptionObject_h
#define sitkExceptionObject_h

#include "sitkMacro.h"
#include "sitkCommon.h"

#ifndef sitkMacro_h
#error "sitkMacro.h must be included before sitkExceptionObject.h"
#endif // sitkMacro_h
#ifndef sitkCommon_h
#error "sitkCommon.h must be included before sitkExceptionObject.h"
#endif // sitkCommon_h


namespace itk
{

// forward declaration for encapsulation
class ExceptionObject;

namespace simple
{

/** \class GenericException
 * \brief The base SimpleITK exception class
 */
class SITKCommon_EXPORT GenericException :
    public std::exception
{
public:
  /** Default constructor.  Needed to ensure the exception object can be
   * copied. */
  GenericException()  throw();
  GenericException( const GenericException &e )  throw();

  /** Constructor. Needed to ensure the exception object can be copied. */
  GenericException(const char *file, unsigned int lineNumber) throw();

  /** Constructor. Needed to ensure the exception object can be copied. */
  GenericException(const std::string & file, unsigned int lineNumber) throw();

  /** Constructor. Needed to ensure the exception object can be copied. */
  GenericException(const std::string & file,
                   unsigned int lineNumber,
                   const std::string & desc) throw();

  /** Virtual destructor needed for subclasses. Has to have empty throw(). */
  virtual ~GenericException() throw( );

  /** Assignment operator. */
  GenericException & operator=(const GenericException & orig);

  /** Equivalence operator. */
  virtual bool operator==(const GenericException & orig) const;


  /** Return a description of the error */
  std::string ToString() const;

  const char * what() const throw();

  virtual const char * GetNameOfClass() const;

  virtual const char * GetLocation()    const;

  virtual const char * GetDescription() const;

  /** What file did the exception occur in? */
  virtual const char * GetFile()    const;

  /** What line did the exception occur in? */
  virtual unsigned int GetLine() const;

private:
  const ExceptionObject *m_PimpleException;
};

}
}

#endif // sitkExceptionObject_h
