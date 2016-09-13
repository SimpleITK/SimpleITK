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
#ifndef itkDivideFloorFunctor_h
#define itkDivideFloorFunctor_h

#include <cmath>

namespace itk
{
namespace Functor
{
/**
 * \class DivFloor
 * \brief Cast arguments to double, performs division then takes the floor.
 */
template< class TInput1, class TInput2, class TOutput >
class DivFloor
{
public:
  // Use default copy, assigned and destructor
  // DivFloor() {} default constructor OK

  bool operator!=(const DivFloor &) const
    {
      return false;
    }

  bool operator==(const DivFloor & other) const
    {
      return !( *this != other );
    }

  inline TOutput operator()(const TInput1 & A, const TInput2 & B) const
    {
      if ( B != (TInput2)0 )
        {
        return static_cast<TOutput>( std::floor( double(A) / double(B) ) );
        }
      else
        {
        return NumericTraits< TOutput >::max( static_cast<TOutput>(A) );
        }
    }
};
}
}

#endif // itkDivisionFloorImageFilter_h
