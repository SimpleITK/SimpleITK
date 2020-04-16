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

// This one header will include all SimpleITK filters and external
// objects.
#include <SimpleITK.h>
#include <iostream>
#include <stdlib.h>
#include <iomanip>

// create convenient namespace alias
namespace sitk = itk::simple;

// Create A Command Callback to be registered with the ProcessObject
// on the ProgressEvent
//
// Internally we maintain a reference to the ProcessObject passed
// during construction. Therefore, it would be an error to execute the
// Execute method after the ProcessObject is delete. But this class
// can be created on the stack, with out issue.
class ProgressUpdate
  : public sitk::Command
{
public:
  ProgressUpdate(const sitk::ProcessObject &po)
    : m_Process(po)
    {}

  void Execute( ) override
    {
      // stash the stream state
      std::ios  state(NULL);
      state.copyfmt(std::cout);
      std::cout << std::fixed << std::setw( 3 ) << std::setprecision( 2 );

      // Print the Progress "Active Measurement"
      std::cout << m_Process.GetName()<< " Progress: " << m_Process.GetProgress() << std::endl;

      std::cout.copyfmt(state);
    }
private:
  const sitk::ProcessObject &m_Process;
};


int main ( int argc, char* argv[] ) {

  if ( argc < 4 ) {
    std::cerr << "Usage: " << argv[0] << " <input> <variance> <output>\n";
    return 1;
  }

  // Read the image file
  sitk::ImageFileReader reader;
  reader.SetFileName ( std::string ( argv[1] ) );
  sitk::Image image = reader.Execute();

  // This filters perform a gaussian bluring with sigma in physical
  // space. The output image will be of real type.
  sitk::DiscreteGaussianImageFilter gaussian;
  gaussian.SetVariance ( atof ( argv[2] ) );

  // Construct our custom command on the stack
  ProgressUpdate cmd(gaussian);
  // register it with the filter for the ProgressEvent
  gaussian.AddCommand( sitk::sitkProgressEvent, cmd );

  sitk::Image blurredImage = gaussian.Execute ( image );

  // Covert the real output image back to the original pixel type, to
  // make writing easier, as many file formats don't support real
  // pixels.
  sitk::CastImageFilter caster;
  caster.SetOutputPixelType( image.GetPixelID() );
  sitk::Image outputImage = caster.Execute( blurredImage );

  // write the image
  sitk::ImageFileWriter writer;
  writer.SetFileName ( std::string ( argv[3] ) );

  //! [cpp lambda command]
  writer.AddCommand(sitk::sitkStartEvent, [] {std::cout << "Writting..." << std::flush;});
  writer.AddCommand(sitk::sitkEndEvent, [] {std::cout << "done" << std::endl;});
  //! [cpp lambda command]

  writer.Execute ( outputImage );

  return 0;
}
