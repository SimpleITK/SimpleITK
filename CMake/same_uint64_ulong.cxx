#include <stdint.h>

// This program compiles when unsignedlong and uint64_t are the same type

template <typename T, typename U > struct IsSame;
template< typename T >
struct IsSame<T, T> { };

int main( void )
{
  IsSame<unsigned long, uint64_t> FailsWhenNotSameTypes;
  return 0;
}
