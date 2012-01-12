#ifndef __sitkConditional_h
#define __sitkConditional_h

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
                                    std::tr1::integral_constant<int, TIfTrue>,
                                    std::tr1::integral_constant<int, TIfFalse> >::Type
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

#endif // __sitkConditional_h
