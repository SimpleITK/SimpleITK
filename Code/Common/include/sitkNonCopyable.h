#ifndef __sitkNonCopyable_h
#define __sitkNonCopyable_h

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
class NonCopyable
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

#endif //  __sitkNonCopyable_h
