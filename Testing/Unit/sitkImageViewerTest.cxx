/*=========================================================================
*
*  Copyright NumFOCUS
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

#include "sitkImageViewer.h"
#include "SimpleITK.h"
#include "sitkImageViewerTest.h"
#include <SimpleITKTestHarness.h>
#include <itksys/SystemTools.hxx>




namespace sitk = itk::simple;

// returns true of two word lists are the same
//
bool compare_word_lists(std::vector<std::string> a, std::vector<std::string> b)
  {
  if ( a.size() != b.size() )
    {
    return false;
    }

  unsigned int i;
  for (i=0; i< a.size(); i++)
    {
    if (a[i].compare(b[i]))
      return false;
    }
  return true;
  }

TEST(ImageViewerTest,Methods)
  {
  std::string cmd( "SITK_SHOW_COMMAND=testpath" );
  itksys::SystemTools::PutEnv( cmd );

  itk::simple::ImageViewer iv;

  std::cout << iv.ToString() << std::endl;

  EXPECT_EQ( iv.GetCommand(), "testpath" );

  iv.SetTitle("ImageViewerTest");
  EXPECT_EQ( iv.GetTitle(), "ImageViewerTest" );

  EXPECT_EQ( iv.GetName(), "ImageViewer" );

  iv.SetFileExtension( ".png" );
  EXPECT_EQ( iv.GetFileExtension(), ".png" );

  iv.SetApplication( "testapp", "testcommand" );
  EXPECT_EQ( iv.GetApplication(), "testapp" );
  EXPECT_EQ( iv.GetCommand(), "testcommand" );


  unsigned int delay;
  delay = iv.GetProcessDelay();

#ifdef _WIN32
  EXPECT_EQ( delay, 1u );
#else
  EXPECT_EQ( delay, 500u );
#endif
  iv.SetProcessDelay( delay );
  }

TEST(ImageViewerTest,GlobalDefaults)
  {
  itk::simple::ImageViewer iv;

  std::vector<std::string> words;
  words.emplace_back("alpha" );
  words.emplace_back("beta" );

  std::vector<std::string> path;
  iv.SetGlobalDefaultSearchPath( words );
  path = iv.GetGlobalDefaultSearchPath();
  EXPECT_EQ( compare_word_lists(words, path), true );

  std::vector<std::string> names;
  iv.SetGlobalDefaultExecutableNames( words );
  names = iv.GetGlobalDefaultExecutableNames();
  EXPECT_EQ( compare_word_lists(words, names), true );

  //
  iv.SetGlobalDefaultDebug( true );
  EXPECT_EQ( iv.GetGlobalDefaultDebug(), true );

  iv.SetGlobalDefaultDebugOff();
  EXPECT_EQ( iv.GetGlobalDefaultDebug(), false );
  iv.SetGlobalDefaultDebugOn();
  EXPECT_EQ( iv.GetGlobalDefaultDebug(), true );

  iv.SetGlobalDefaultFileExtension( ".mha" );
  EXPECT_EQ( iv.GetGlobalDefaultFileExtension(), ".mha" );

  iv.SetGlobalDefaultApplication( "testapp" );
  EXPECT_EQ( iv.GetGlobalDefaultApplication(), "testapp" );
  }

TEST(ImageViewerTest,Execute)
  {
  itk::simple::ImageViewer iv;
  itk::simple::Image img( 10,10, itk::simple::sitkUInt8 );

  iv.SetGlobalDefaultDebug( true );
  iv.SetCommand( CMAKE_COMMAND  " -E md5sum" );
  iv.SetTitle( "test" );
  iv.SetFileExtension( ".png" );
  iv.Execute( img );

  // strings to exercise the command conversion code
  itk::simple::ImageViewer iv2;
  iv2.SetTitle( "" );
  iv2.SetFileExtension( "" );
  iv2.SetApplication( "nilla_wafers", "\"banana pudding\" %a %f %% %t \'%" );
  EXPECT_THROW( iv2.Execute(img), sitk::GenericException );
  }
