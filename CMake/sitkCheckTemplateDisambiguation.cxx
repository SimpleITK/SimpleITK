template<typename T>
struct A
{
  template <typename U>
  void f() {};
};

template<typename T>
void g()
{
  A<T> obj;

  // The following `template` keyword is required by C++0x, but some
  // compilers don't allow it.
  obj.template f<T>();
}


int main(void)
{
  g<int>();

  return 0;
}
