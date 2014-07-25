
//-------------------------------------

#ifdef SITK_HAS_CXX11_STATIC_ASSERT

int main(void)
{
  static_assert( true, "this should compile with C++0x static_assert keyword support");
  return 0;
}

#endif


//-------------------------------------

#ifdef SITK_HAS_CXX11_NULLPTR

struct C {
  void func();
};

int main(void)
{
  int *x = nullptr;
  char *c = nullptr;
  void (C::*pmf)() = nullptr;
  if (nullptr==c) {}
  if (nullptr==pmf) {}
  return 0;
}

#endif

//-------------------------------------

#ifdef SITK_HAS_CXX11_FUNCTIONAL

#include <functional>

void f(int,int) {}

int main(void)
{
std::function<void(int,int)> g(f);
using namespace std::placeholders;
std::function<void(int)> h = std::bind(g,0,_1);
return 0;
}

#endif


//-------------------------------------

#ifdef SITK_HAS_TR1_FUNCTIONAL

#ifdef HAS_TR1_SUB_INCLUDE
#include <tr1/functional>
#else
#include <functional>
#endif

void f(int,int) {}

int main(void)
{
  std::tr1::function<void(int,int)> g(f);
  using namespace std::tr1::placeholders;
  std::tr1::function<void(int)> h = std::tr1::bind(g,0,_1);
  return 0;
}

#endif

//-------------------------------------

#ifdef SITK_HAS_CXX11_TYPE_TRAITS

#include <type_traits>

int main(void)
{
  std::integral_constant<int, 0> a;
  std::true_type b;
  std::false_type c;
  std::is_same<int,int>::type d;
  return 0;
}

#endif

//-------------------------------------

#ifdef SITK_HAS_TR1_TYPE_TRAITS

#ifdef HAS_TR1_SUB_INCLUDE
#include <tr1/type_traits>
#else
#include <type_traits>
#endif

int main(void)
{
  std::tr1::integral_constant<int, 0> a;
  std::tr1::true_type b;
  std::tr1::false_type c;
  std::tr1::is_same<int,int>::type d;
  return 0;
}

#endif

//-------------------------------------

#ifdef SITK_HAS_CXX11_UNORDERED_MAP

#include <unordered_map>

int main(void)
{
  // On OSX with gcc 4.0, there is an internal const correctness issue
  // in the following.
  std::unordered_map<int,int> s;
  const std::unordered_map<int, int> &c_ref = s;
  c_ref.find(1); // Problem is here.
  return 0;
}

#endif

//-------------------------------------

#ifdef SITK_HAS_TR1_UNORDERED_MAP


#ifdef HAS_TR1_SUB_INCLUDE
#include <tr1/unordered_map>
#else
#include <unordered_map>
#endif

int main(void)
{
  // On OSX with gcc 4.0, there is an internal const correctness issue
  // in the following.
  std::tr1::unordered_map<int,int> s;
  const std::tr1::unordered_map<int, int> &c_ref = s;
  c_ref.find(1); // Problem is here.
  return 0;
}

#endif

//-------------------------------------

#ifdef SITK_HAS_TR1_SUB_INCLUDE

#include <tr1/functional>
#include <tr1/type_traits>
#include <tr1/unordered_map>

int main(void) { return 0; }

#endif
