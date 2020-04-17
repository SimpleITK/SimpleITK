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

#ifndef sitkImageIOUtilities_h
#define sitkImageIOUtilities_h

#include "sitkMacro.h"
#include "sitkExceptionObject.h"
#include "itkImageIOBase.h"
#include <sstream>
#include <list>

namespace itk {
namespace simple {
namespace ioutils {

void PrintRegisteredImageIOs(std::ostream &out)
{

  std::list<itk::LightObject::Pointer> allobjects =  itk::ObjectFactoryBase::CreateAllInstance("itkImageIOBase");

  for(std::list<itk::LightObject::Pointer>::iterator i = allobjects.begin();
      i != allobjects.end(); ++i)
    {
    const itk::ImageIOBase* const io = dynamic_cast<itk::ImageIOBase*>(i->GetPointer());
    if(io)
      {

      // get the name of the class the remove the IO from the end
      out << "\t" << io->GetNameOfClass();

      const itk::ImageIOBase::ArrayOfExtensionsType &ioExtensions = io->GetSupportedReadExtensions();
      // print the extensions if they are listed
      if ( !ioExtensions.empty() )
        {
        out << " (";
        for (itk::ImageIOBase::ArrayOfExtensionsType::const_iterator j = ioExtensions.begin(); j != ioExtensions.end(); ++j)
          {
          out << " *" << *j << ",";
          }
        out << "\b )";
        }
      out << std::endl;
      }
    }
}

std::vector<std::string> GetRegisteredImageIOs()
{
  std::vector<std::string> out;

  std::list<itk::LightObject::Pointer> allobjects =  itk::ObjectFactoryBase::CreateAllInstance("itkImageIOBase");

  for(std::list<itk::LightObject::Pointer>::iterator i = allobjects.begin();
      i != allobjects.end(); ++i)
    {
    const itk::ImageIOBase* const io = dynamic_cast<itk::ImageIOBase*>(i->GetPointer());
    if(io)
      {

      out.emplace_back(io->GetNameOfClass() );

      }
    }
  return out;

}


itk::SmartPointer<ImageIOBase> CreateImageIOByName(const std::string & ioname)
{
  itk::ImageIOBase::Pointer iobase;
  std::list<itk::LightObject::Pointer> allobjects =  itk::ObjectFactoryBase::CreateAllInstance("itkImageIOBase");
  for(std::list<itk::LightObject::Pointer>::iterator i = allobjects.begin(); i != allobjects.end(); ++i)
    {
    if ((*i)->GetNameOfClass() == ioname)
      {
      iobase = dynamic_cast<itk::ImageIOBase*>(i->GetPointer());
      }
    }
  if ( iobase.IsNull() )
    {
    sitkExceptionMacro("Unable to create ImageIO: \"" << ioname << "\"");
    }
  return iobase;
}

}
}
}

#endif
