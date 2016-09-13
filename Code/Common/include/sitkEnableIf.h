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
#ifndef sitkEnableIf_h
#define sitkEnableIf_h

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

#endif // sitkEnableIf_h
