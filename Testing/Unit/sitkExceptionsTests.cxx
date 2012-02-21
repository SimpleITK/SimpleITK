/*=========================================================================
*
*  Copyright Insight Software Consortium
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/
#include "sitkMacro.h"

#include "SimpleITKTestHarness.h"

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
    //EXPECT_NE ( std::string ( e.GetLocation() ),  "" ); HACK FIXME
    // exception revision
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
