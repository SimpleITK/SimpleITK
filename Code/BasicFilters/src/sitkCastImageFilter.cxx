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
#include "sitkCastImageFilter.h"


namespace itk
{
namespace simple
{


//----------------------------------------------------------------------------


CastImageFilter::~CastImageFilter() = default;

//
// Default constructor that initializes parameters
//
CastImageFilter::CastImageFilter()
{
  this->m_OutputPixelType = sitkFloat32;

  m_DualMemberFactory = std::make_unique<detail::DualMemberFunctionFactory<MemberFunctionType>>( this );

  this->RegisterMemberFactory2();
  this->RegisterMemberFactory2v();
  this->RegisterMemberFactory2l();
  this->RegisterMemberFactory3();
  this->RegisterMemberFactory3v();
  this->RegisterMemberFactory3l();

  this->RegisterMemberFactory4();

}

//
// ToString
//
std::string CastImageFilter::ToString() const
{
  std::ostringstream out;
  out << "itk::simple::CastImageFilter\n"
      << "\tOutputPixelType: " << this->m_OutputPixelType << std::endl;
  out << ProcessObject::ToString();
  return out.str();
}

//
// Set/Get Methods for output pixel type
//

CastImageFilter::Self& CastImageFilter::SetOutputPixelType( PixelIDValueEnum pixelID )
{
  this->m_OutputPixelType = pixelID;
  return *this;
}

PixelIDValueEnum CastImageFilter::GetOutputPixelType( ) const
{
  return this->m_OutputPixelType;
}


//
// Execute
//
Image CastImageFilter::Execute ( const Image& image )
{

  const PixelIDValueEnum inputType = image.GetPixelID();
  const PixelIDValueEnum outputType = this->m_OutputPixelType;
  const unsigned int dimension = image.GetDimension();

  if (this->m_DualMemberFactory->HasMemberFunction( inputType, outputType,  dimension ) )
    {
    return this->m_DualMemberFactory->GetMemberFunction( inputType, outputType, dimension )( image );
    }

  sitkExceptionMacro( << "Filter does not support casting from casting " << itk::simple::GetPixelIDValueAsString (inputType) << " to "
                      << itk::simple::GetPixelIDValueAsString (outputType) );

}


//----------------------------------------------------------------------------


Image Cast ( const Image& image, PixelIDValueEnum pixelID ) {
  CastImageFilter filter;
  filter.SetOutputPixelType( pixelID );
  return filter.Execute ( image );
}


} // end namespace simple
} // end namespace itk
