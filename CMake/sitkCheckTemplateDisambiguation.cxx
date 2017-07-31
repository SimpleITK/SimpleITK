template<typename T>
struct A
{
  template <typename U>
  void operator()( ) {};
};


template<typename T>
void g( )
{
  A<T> obj;

  // The following `template` keyword is required by C++. But with
  // MSVC <VS15 appears to have a bug when used with operator()
  obj.template operator()<T>();
}


int main(void)
{
  g<int>();

  return 0;
}
