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
#ifndef sitkNonCopyable_h
#define sitkNonCopyable_h

#include "sitkCommon.h"

namespace itk
{
namespace simple
{

/** \class NonCopyable
* \brief An inheratable class to disable copying of a class
*
* This class disable the implicit implementations of the assignment
* and copy constructor for derived classes. The instantiation of the
* default implementation for either method in a derived class will
* result in a compile-time error because they are private in this
* class. However, this policy is not absolute for derived classes
* because explicit implementation of these methods could be
* implemented.
*
* An advatange this apporach has is the class heiarchy makes it
* obvious what the intent is, as compared to other appoaches.
*
* For example you should not be able to copy singleton object, because
* there should only be one of them. To utilize this class just derive
* from it:
* \code
* class Singleton
*  : protected NonCopyable {...};
* \endcode
*
*/
class SITKCommon_EXPORT NonCopyable
{
protected:
  NonCopyable() {}
private:
  NonCopyable &operator=( const NonCopyable & ); // Not implemented on purpose
  NonCopyable( const NonCopyable & ); // Not implemented on purpose
};

#if SITK_EXPLICIT_DEFAULT_DELETE_FUNCTIONS

// see other implementation for doxygen
struct NonCopyable
{
  NonCopyable() = default;
  NonCopyable &operator=( const NonCopyable & ) = delete;
  NonCopyable( const NonCopyable & ) = delete;
};

#endif


} // end namespace simple
} // end namespace itk

#endif //  sitkNonCopyable_h
