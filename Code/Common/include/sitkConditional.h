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
#ifndef sitkConditional_h
#define sitkConditional_h

namespace itk
{
namespace simple
{

/* \brief An object for selection of a type at compile-time.
 * *
 * If VCode is true, then the member Type will be TIfTrue, otherwise
 * the member typedef Type will be equivalent to TIfFalse.
 *
 */
template <bool VCond, class TIfTrue, class TIfFalse> struct Conditional { typedef TIfTrue Type; };
/** \cond SPECIALIZATION_IMPLEMENTATION */
template<class TIfTrue, class TIfFalse>
struct Conditional<false, TIfTrue, TIfFalse> { typedef TIfFalse Type; };

/**\endcond*/

/* \brief An object for selecting an integer value at compile-time.
 *
 *
 * If VCode is true, then the member Value will be TIfTrue, otherwise
 * the member Value  will be equivalent to TIfFalse.
 *
 * This class also contains a typedef for ValueType, which is an the
 * selected integral constant as a type.
 */
template <bool VCond, int TIfTrue, int TIfFalse>
struct ConditionalValue
  : public itk::simple::Conditional<VCond,
                                    nsstd::integral_constant<int, TIfTrue>,
                                    nsstd::integral_constant<int, TIfFalse> >::Type
{
private:
  typedef ConditionalValue Self;
public:
  typedef typename Self::value_type ValueType;
  typedef typename Self::type       Type;

  static const ValueType Value = Self::value;
};

}
}

#endif // sitkConditional_h
