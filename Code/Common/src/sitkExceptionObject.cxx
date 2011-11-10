
#include "sitkExceptionObject.h"
#include "itkMacro.h"

namespace itk
{
namespace simple
{

GenericException::GenericException() throw()
  : m_PimpleException( NULL )
{}

GenericException::GenericException( const GenericException &e ) throw()
try
  : std::exception( e ),
    m_PimpleException( new itk::ExceptionObject( *e.m_PimpleException ) )
{
}
catch(...) // catch exception from initialization list
  {
  this->m_PimpleException = NULL;
  }

GenericException::GenericException(const char *file, unsigned int lineNumber) throw()
try
  : m_PimpleException( new itk::ExceptionObject( file, lineNumber ) )
{
}
catch(...) // catch exception from initialization list
  {
  this->m_PimpleException = NULL;
  }

/** Constructor. Needed to ensure the exception object can be copied. */
GenericException::GenericException(const std::string & file, unsigned int lineNumber) throw()
try
  : m_PimpleException( new itk::ExceptionObject( file, lineNumber ) )
{
}
catch(...) // catch exception from initialization list
  {
  this->m_PimpleException = NULL;
  }

/** Constructor. Needed to ensure the exception object can be copied. */
GenericException::GenericException(const std::string & file,
                                   unsigned int lineNumber,
                                   const std::string & desc) throw()
try
  : m_PimpleException( new itk::ExceptionObject( file, lineNumber, desc ) )
{
}
catch(...) // catch exception from initialization list
  {
  this->m_PimpleException = NULL;
  }

GenericException::~GenericException() throw( )
{
  delete this->m_PimpleException;
}


GenericException & GenericException::operator=(const GenericException & orig)
{
  if ( this != &orig )
    this->m_PimpleException = orig.m_PimpleException;
  return *this;
}

bool GenericException::operator==(const GenericException & orig)
{
  if ( this->m_PimpleException && orig.m_PimpleException)
    {
    return this->m_PimpleException == orig.m_PimpleException;
    }
  else if (  this->m_PimpleException == NULL &&
             orig.m_PimpleException == NULL )
    {
    return true;
    }
  return false;
}

/** Return a description of the error */
std::string GenericException::ToString()
{
  if ( this->m_PimpleException )
    {
    std::ostringstream out;
    this->m_PimpleException->Print( out );
    return std::string();
    }

  return std::string("No pimple exception");
}

const char * GenericException::what() const throw()
{
  if ( this->m_PimpleException )
    return this->m_PimpleException->what();
  return "No pimple Exception!";
}


const char * GenericException::GetNameOfClass() const
{
  return "GenericException";
}


const char * GenericException::GetLocation() const
{
  if ( this->m_PimpleException )
    return this->m_PimpleException->GetLocation();
  return "No pimple Exception!";
}

const char * GenericException::GetDescription() const
{
  if ( this->m_PimpleException )
    return this->m_PimpleException->GetDescription();
  return "No pimple Exception!";
}

/** What file did the exception occur in? */
const char * GenericException::GetFile()    const
{
  if ( this->m_PimpleException )
    return this->m_PimpleException->GetFile();
  return "No pimple Exception!";
}

/** What line did the exception occur in? */
unsigned int GenericException::GetLine() const
{
  if ( this->m_PimpleException )
    return this->m_PimpleException->GetLine();
  return 0;
}

}
}
