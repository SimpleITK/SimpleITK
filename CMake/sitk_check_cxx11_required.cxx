#include <iostream>
#if __cplusplus >= 201103L
#else
#if defined _LIBCPP_VERSION
#error "libc++ is not supported without C++11"
#endif
#endif


int main(void)
{
std::cout << "__cplusplus:" << __cplusplus << std::endl;
return 0;
}
