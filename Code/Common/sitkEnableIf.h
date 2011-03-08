#ifndef __sitkEnableIf_h
#define __sitkEnableIf_h

namespace itk
{
namespace simple
{

/* \brief This is an implementation of the enable if idiom.
 *
 * This template enables specialization of a templated function based
 * on some traits or concepts. It is implemented with SFINAE.
 *
 * If the parameter V is true then the Type trait is the second
 * template parameter, otherwise an implementation does not exist and
 * with SFIANE another implementation may be choosen.
 *
 * Example:
 * \code
 * template<class TImageType>
 * typename EnableIf<IsBasic<TImageType>::Value>::Type
 * AllocateInternal ( unsigned int Width, unsigned int Height, unsigned int Depth );
 *
 * template<class TImageType>
 * typename EnableIf<IsVector<TImageType>::Value>::Type
 * AllocateInternal ( unsigned int Width, unsigned int Height, unsigned int Depth );
 * \endcode
 *
 */
template <bool V, class T = void> struct EnableIf {};
/** \cond SPECIALIZATION_IMPLEMENTATION */
template <class T> struct EnableIf<true, T> { typedef T Type; };
/**\endcond*/



/* \brief An implementation of the negation of the enable if idiom.
 *
 * \sa EnableIf
 */
template <bool V, class T = void> struct DisableIf {};
/** \cond SPECIALIZATION_IMPLEMENTATION */
template <class T> struct DisableIf<false, T> { typedef T Type; };
/**\endcond*/

}
}

#endif // __sitkEnableIf_h
