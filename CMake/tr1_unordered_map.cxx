#if defined SITK_HAS_STLTR1_TR1_UNORDERED_MAP
#include <tr1/unordered_map>
#elif defined SITK_HAS_STLTR1_UNORDERED_MAP
#include <unordered_map>
#endif

int main()
{
  // On OSX with gcc 4.0, there is an internal const correctness issue
  // in the following.
  std::tr1::unordered_map<int,int> s;
  const std::tr1::unordered_map<int, int> &c_ref = s;
  c_ref.find(1); // Problem is here.
  return 0;
}
