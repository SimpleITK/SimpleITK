#ifndef __sitkExceptionObject_h
#define __sitkExceptionObject_h

#include <string>
#include <stdexcept>

namespace itk
{

// forward declaration for encapsulation
class ExceptionObject;

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
  virtual bool operator==(const GenericException & orig);


  /** Return a description of the error */
  std::string ToString();

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

#endif // __sitkExceptionObject_h
