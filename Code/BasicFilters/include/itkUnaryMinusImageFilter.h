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
#ifndef itkUnaryMinusFunctor_h
#define itkUnaryMinusFunctor_h

namespace itk
{
namespace Functor
{
/**
 * \class UnaryMinus
 * \brief
 * \ingroup ITKImageIntensity
 */
template< class TInput1, class TOutput = TInput1 >
class UnaryMinus
{
public:
  UnaryMinus() {}
  ~UnaryMinus() {}
  bool operator!=(const UnaryMinus &) const
  {
    return false;
  }

  bool operator==(const UnaryMinus & other) const
  {
    return !( *this != other );
  }

  inline TOutput operator()(const TInput1 & A ) const
  { return (TOutput)( -A ); }
};
}
}

#endif // itkUnaryMinusFunctor_h
