
#if defined SITK_HAS_STLTR1_TR1_UNORDERED_MAP
#include <tr1/unordered_map>
#elif defined SITK_HAS_STLTR1_UNORDERED_MAP
#include <unordered_map>
#endif

#if defined SITK_HAS_STLTR1_TR1_FUNCTIONAL
#include <tr1/functional>
#elif defined SITK_HAS_STLTR1_FUNCTIONAL
#include <functional>
#else
#error "No system tr1 functional available"
#endif

int dummy(void)
{
  return 1;
}

int main()
{

  std::tr1::unordered_map<int,int> s;
  const std::tr1::unordered_map<int, int> &c_ref = s;

  typedef std::tr1::function<  dummy() > FunctionObjectType;
  return 0;
}
