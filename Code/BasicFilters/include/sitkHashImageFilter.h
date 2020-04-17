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
#ifndef sitkHashImageFilter_h
#define sitkHashImageFilter_h

#include "sitkMacro.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkImage.h"
#include "sitkBasicFilters.h"
#include "sitkImageFilter.h"
#include "sitkProcessObject.h"

namespace itk {
  namespace simple {

    /** \class HashImageFilter
     * \brief Compute the sha1 or md5 hash of an image
     *
     * \sa itk::simple::Hash for the procedural interface
     */
    class SITKBasicFilters_EXPORT HashImageFilter
      : public ProcessObject {
    public:
      using Self = HashImageFilter;

      // function pointer type
      typedef std::string (Self::*MemberFunctionType)( const Image& );

      // this filter works with all itk::Image and itk::VectorImage types.
      typedef typelist::Append<
        typelist::Append< BasicPixelIDTypeList, ComplexPixelIDTypeList>::Type,
        VectorPixelIDTypeList >::Type PixelIDTypeList;

      ~HashImageFilter() override;

      HashImageFilter();

      enum HashFunction { SHA1, MD5 };
      SITK_RETURN_SELF_TYPE_HEADER SetHashFunction ( HashFunction hashFunction );
      HashFunction GetHashFunction () const;

      /** Name of this class */
      std::string GetName() const override { return std::string ( "Hash"); }

      // Print ourselves out
      std::string ToString() const override;

      std::string Execute ( const Image& );


    private:
      HashFunction m_HashFunction;

      template <class TImageType> std::string ExecuteInternal ( const Image& image );
      template <class TImageType> std::string ExecuteInternalLabelImage ( const Image& image );

      // friend to get access to executeInternal member
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      friend struct detail::ExecuteInternalLabelImageAddressor<MemberFunctionType>;

      std::unique_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;
    };

    SITKBasicFilters_EXPORT std::string Hash ( const Image& image, HashImageFilter::HashFunction function = HashImageFilter::SHA1 );
  }
}
#endif
