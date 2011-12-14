#ifndef __sitkExceptionObject_h
#define __sitkExceptionObject_h

#include "itkMacro.h"
#include "itkExceptionObject.h"

namespace itk
{
namespace simple
{

/** \class GenericException
 * \brief The base SimpleITK exception class
 */
class GenericException :
    public ::itk::ExceptionObject
{
public:
  /** Default constructor.  Needed to ensure the exception object can be
   * copied. */
  GenericException():ExceptionObject() {}

  /** Constructor. Needed to ensure the exception object can be copied. */
  GenericException(const char *file, unsigned int lineNumber):ExceptionObject(file, lineNumber) {}

  /** Constructor. Needed to ensure the exception object can be copied. */
  GenericException(const std::string & file, unsigned int lineNumber):ExceptionObject(file, lineNumber) {}

  /** Constructor. Needed to ensure the exception object can be copied. */
  GenericException(const std::string & file,
                        unsigned int lineNumber,
                        const std::string & desc,
                        const std::string & loc):ExceptionObject(file, lineNumber, desc, loc) {}

  /** Virtual destructor needed for subclasses. Has to have empty throw(). */
  virtual ~GenericException()
  throw( ) {}

  /** Return a description of the error */
  std::string ToString()
  {
  std::ostringstream out;
  Print ( out );
  return out.str();
  }


  virtual const char * GetNameOfClass() const
  { return "GenericException"; }
};

}
}

#endif // __sitkExceptionObject_h
