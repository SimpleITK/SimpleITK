#include <SimpleITKTestHarness.h>

#include <SimpleITK.h>


TEST( ConditionalTest, ConditionalTest1 ) {

  // a quick check to make sure the conditional works
  typedef itk::simple::Conditional<true, int, float>::Type IntType;
  typedef itk::simple::Conditional<false, int, float>::Type FloatType;


  EXPECT_EQ ( typeid( IntType ).name(), typeid( int ).name() );
  EXPECT_EQ ( typeid( FloatType ).name(), typeid( float ).name() );

  return;

}
