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

#include "sitkExceptionObject.h"
#include "itkMacro.h"

#if defined(_MSC_VER)
#pragma warning ( disable : 4297 )
#endif


namespace itk
{
namespace simple
{

GenericException::GenericException() noexcept
  : m_PimpleException( nullptr )
{}

GenericException::GenericException( const GenericException &e ) noexcept

  : std::exception( e )
{
  try
    {
    if ( e.m_PimpleException != nullptr )
      {
      m_PimpleException =  new itk::ExceptionObject( *e.m_PimpleException );
      }
    }
  catch(...) // prevent exception from leaving constructor
    {
    this->m_PimpleException = nullptr;
    }
}

GenericException::GenericException(const char *file, unsigned int lineNumber) noexcept
{
  try
    {
    m_PimpleException =  new itk::ExceptionObject( file, lineNumber );
    }
  catch(...) // prevent exception from leaving constructor
    {
    this->m_PimpleException = nullptr;
    }
}

/** Constructor. Needed to ensure the exception object can be copied. */
GenericException::GenericException(const std::string & file, unsigned int lineNumber) noexcept
{
  try
    {
    m_PimpleException =  new itk::ExceptionObject( file, lineNumber );
    }
  catch(...) // prevent exception from leaving constructor
    {
    this->m_PimpleException = nullptr;
    }
}

/** Constructor. Needed to ensure the exception object can be copied. */
GenericException::GenericException(const std::string & file,
                                   unsigned int lineNumber,
                                   const std::string & desc) noexcept
{
  try
    {
    m_PimpleException =  new itk::ExceptionObject( file, lineNumber, desc );
    }
  catch(...) // prevent exception from leaving constructor
    {
    this->m_PimpleException = nullptr;
    }
}

GenericException::~GenericException() noexcept
{
  delete this->m_PimpleException;
}


GenericException & GenericException::operator=(const GenericException & orig)
{
  if ( this != &orig )
    this->m_PimpleException = orig.m_PimpleException;
  return *this;
}

bool GenericException::operator==(const GenericException & orig) const
{
  if ( this->m_PimpleException && orig.m_PimpleException)
    {
    return this->m_PimpleException == orig.m_PimpleException;
    }
  else if (  this->m_PimpleException == nullptr &&
             orig.m_PimpleException == nullptr )
    {
    return true;
    }
  return false;
}

/** Return a description of the error */
std::string GenericException::ToString() const
{
  if ( this->m_PimpleException )
    {
    std::ostringstream out;
    this->m_PimpleException->Print( out );
    return std::string();
    }

  return std::string("No pimple exception");
}

const char * GenericException::what() const noexcept
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
