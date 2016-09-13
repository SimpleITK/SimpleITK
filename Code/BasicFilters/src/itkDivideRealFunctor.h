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
#ifndef itkDivideRealFunctor_h
#define itkDivideRealFunctor_h

#include <itkNumericTraits.h>

namespace itk
{
namespace Functor
{
/**
 * \class DivReal
 * \brief Promotes arguments to real type and performs division
 */
template< class TInput1, class TInput2, class TOutput >
class DivReal
{
public:
  // Use default copy, assigned and destructor
  bool operator!=(const DivReal &) const
  {
    return false;
  }

  bool operator==(const DivReal & other) const
  {
    return !( *this != other );
  }

  inline TOutput operator()(const TInput1 & A, const TInput2 & B) const
  {
    if ( B != (TInput2)0 )
      {
      return static_cast<TOutput>( static_cast<typename NumericTraits<TInput1>::RealType>(A)
                                   /
                                   static_cast<typename NumericTraits<TInput2>::RealType >(B) );
      }
    else
      {
      return NumericTraits< TOutput >::max( static_cast<TOutput>(A) );
      }
  }
};
}
}

#endif // itkDivisionRealImageFilter_h
