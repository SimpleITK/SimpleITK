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
#ifndef itkBitwiseNotFunctor_h
#define itkBitwiseNotFunctor_h

#include <cmath>

namespace itk
{
namespace Functor
{
/**
 * \class BitwiseNot
 * \brief Performs the C++ unary bitwise NOT operator.
 */
template< class TInput, class TOutput >
class BitwiseNot
{
public:
  // Use default copy, assigned and destructor
  // BitwiseNot() {} default constructor OK

  bool operator!=(const BitwiseNot &) const
    {
      return false;
    }

  bool operator==(const BitwiseNot & other) const
    {
      return !( *this != other );
    }

  inline TOutput operator()(const TInput & A) const
    {
      return static_cast<TOutput>( ~A );
    }
};
}
}

#endif // itkBitwiseNotFunctor_h
