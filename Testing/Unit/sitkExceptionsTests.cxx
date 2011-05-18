#include "SimpleITKTestHarness.h"

#include <SimpleITK.h>

static const char * DESCRIPTION = "We expect this exception";

class sitkExceptionsTest
  : public ::testing::Test
{
public:

  void ThrowsitkException( void )
  {
    sitkExceptionMacro( << DESCRIPTION );
  }
};

TEST_F(sitkExceptionsTest, Test1) {
  ASSERT_THROW( ThrowsitkException(), ::itk::simple::GenericException );

  try
    {
    ThrowsitkException();
    }
  catch ( ::itk::simple::GenericException &e )
    {
    // could do some nifty testing here too
    EXPECT_EQ ( e.GetNameOfClass(), std::string("GenericException") );
    EXPECT_NE ( std::string ( e.GetLocation() ),  "" );
    return;
    }

  // should gotten that exception
  FAIL();
}

TEST_F(sitkExceptionsTest, Test2) {

  // this can only be tested when true, if it was false the file won't compile
  sitkStaticAssert( true, "this is just a test" );

  SUCCEED();
}
