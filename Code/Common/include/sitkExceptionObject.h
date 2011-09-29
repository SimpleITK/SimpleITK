#ifndef __sitkExceptionObject_h
#define __sitkExceptionObject_h

#include <string>
#include <stdexcept>

namespace itk
{
namespace simple
{

/** \class GenericException
 * \brief The base SimpleITK exception class
 */
class GenericException :
    public std::exception
{
public:
  /** Default constructor.  Needed to ensure the exception object can be
   * copied. */
  GenericException(){}
  GenericException( const GenericException &e ):  std::exception( e ) {}

  /** Constructor. Needed to ensure the exception object can be copied. */
  GenericException(const char *file, unsigned int lineNumber) {}

  /** Constructor. Needed to ensure the exception object can be copied. */
  GenericException(const std::string & file, unsigned int lineNumber) {}

  /** Constructor. Needed to ensure the exception object can be copied. */
  GenericException(const std::string & file,
                        unsigned int lineNumber,
                        const std::string & desc) {}

  /** Virtual destructor needed for subclasses. Has to have empty throw(). */
  virtual ~GenericException() throw( ) {}

  /** Return a description of the error */
  std::string ToString()
  {
    return std::string();
  }

  const char * what() throw()
    {
      return "";
    }


  virtual const char * GetNameOfClass() const
  { return "GenericException"; }
};

}
}

#endif // __sitkExceptionObject_h
