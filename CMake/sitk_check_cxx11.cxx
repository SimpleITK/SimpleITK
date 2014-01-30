
//-------------------------------------
#ifdef SITK_HAS_CXX11_STATIC_ASSERT

int main(void)
{
  static_assert( true, "this should compile with C++0x static_assert keyword support");
  return 0;
}
#else
#error
#endif // SITK_HAS_CXX11_STATIC_ASSERT
