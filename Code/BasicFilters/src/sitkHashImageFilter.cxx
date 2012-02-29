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

#include "sitkHashImageFilter.h"
#include "itkHashImageFilter.h"
#include "itkVectorImage.h"

#include <string>

namespace itk {
  namespace simple {
    HashImageFilter::HashImageFilter () {
      this->m_HashFunction = SHA1;

      this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

      this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
      this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2 > ();
    }

    std::string HashImageFilter::ToString() const {
      std::ostringstream out;
      out << "itk::simple::HashImageFilter\n";
      out << "HashFunction: ";
      switch ( this->m_HashFunction )
        {
        case SHA1:
          out << "SHA1";
          break;
        case MD5:
          out << "MD5";
          break;
        }
      out << "\n";
      return out.str();
    }

    HashImageFilter::HashFunction HashImageFilter::GetHashFunction()
    {
      return this->m_HashFunction;
    }

    HashImageFilter& HashImageFilter::SetHashFunction ( HashImageFilter::HashFunction hashFunction )
      {
      this->m_HashFunction = hashFunction;
      return *this;
      }

    std::string HashImageFilter::Execute ( const Image& image ) {

      PixelIDValueType type = image.GetPixelIDValue();
      unsigned int dimension = image.GetDimension();

      return this->m_MemberFactory->GetMemberFunction( type, dimension )( image );
    }

    template <class TImageType>
    std::string HashImageFilter::ExecuteInternal ( const Image& inImage )
    {
      typedef TImageType                                   InputImageType;

      typename InputImageType::ConstPointer image =
        dynamic_cast <const InputImageType*> ( inImage.GetITKBase() );

      typedef itk::HashImageFilter<InputImageType> HashFilterType;
      typename HashFilterType::Pointer hasher = HashFilterType::New();
      hasher->SetInput( image );
      hasher->InPlaceOff(); // pointless copy of data needed

      switch ( this->GetHashFunction() )
        {
        case SHA1:
          hasher->SetHashFunction( HashFilterType::SHA1 );
          break;
        case MD5:
          hasher->SetHashFunction( HashFilterType::MD5 );
          break;
        }

      hasher->Update();

      return hasher->GetHash();
    }
    std::string Hash ( const Image& image, HashImageFilter::HashFunction function ) {
      return HashImageFilter().SetHashFunction ( function ).Execute ( image );
    }
  }
}
