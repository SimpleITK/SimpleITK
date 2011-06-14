#ifndef __sitkConditional_h
#define __sitkConditional_h

namespace itk
{
namespace simple
{

/* \brief This is an implementation of the enable if idiom.
 *
 * This template enables specialization of a templated function based
 * on some traits or concepts. It is implemented with SFINAE.
 *
 * If VCode is true, then the member Type will be TIfTrue, otherwise
 * the member typedef Type will be equivalent to TIfFalse.
 *
 */
template <bool VCond, class TIfTrue, class TIfFalse> struct Conditional { typedef TIfTrue Type; };
/** \cond SPECIALIZATION_IMPLEMENTATION */
template<class TIfTrue, class TIfFalse>
struct Conditional<false, TIfTrue, TIfFalse> { typedef TIfFalse Type; };

/**\endcond*/


}
}

#endif // __sitkConditional_h
