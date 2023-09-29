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
using System;
using System.Diagnostics;
using itk.simple;
using sitk = itk.simple.SimpleITK;


namespace itk.simple.examples {
    class DicomSeriesReader {

static void Main(string[] args) {
  try {
    if (args.Length < 2) {
      Console.WriteLine( "Usage: DicomSeriesReader <input_directory> <output_file>" );
      return;
    }

    Console.WriteLine( "Reading Dicom directory: " + args[0] );
    ImageSeriesReader reader = new ImageSeriesReader();

    VectorString dicom_names = ImageSeriesReader.GetGDCMSeriesFileNames( args[0] );
    reader.SetFileNames( dicom_names );

    Image image = reader.Execute();

    VectorUInt32 size = image.GetSize();
    Console.WriteLine( "Image size: " + size[0] + " " + size[1] + " " + size[2] );

    Console.WriteLine( "Writing image: " + args[1] );
    ImageFileWriter writer = new ImageFileWriter();
    writer.SetFileName( args[1] );
    writer.Execute( image );

    if (Environment.GetEnvironmentVariable("SITK_NOSHOW") == null)
      SimpleITK.Show( image, "Dicom Series" );


  } catch (Exception ex) {
    Console.WriteLine( "Usage: DicomSeriesReader <input_directory> <output_file>" );
    Console.WriteLine( ex );
  }
}

    }
}
