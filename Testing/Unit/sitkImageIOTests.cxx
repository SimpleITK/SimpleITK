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
#include <SimpleITKTestHarness.h>
#include <sitkImageFileReader.h>
#include <sitkImageSeriesReader.h>
#include <sitkImageFileWriter.h>
#include <sitkImageSeriesWriter.h>
#include <sitkHashImageFilter.h>
#include <sitkPhysicalPointImageSource.h>

TEST(IO,ImageFileReader) {

  namespace sitk = itk::simple;

  sitk::HashImageFilter hasher;
  sitk::ImageFileReader reader;

  EXPECT_EQ( reader.GetOutputPixelType(), sitk::sitkUnknown );

  EXPECT_EQ( reader.GetLoadPrivateTags(), false );
  reader.LoadPrivateTagsOn();
  EXPECT_EQ( reader.GetLoadPrivateTags(), true );
  reader.LoadPrivateTagsOff();
  EXPECT_EQ( reader.GetLoadPrivateTags(), false );

  reader.SetLoadPrivateTags(true);
  EXPECT_EQ( reader.GetLoadPrivateTags(), true );

  reader.SetLoadPrivateTags(false);
  EXPECT_EQ( reader.GetLoadPrivateTags(), false );


  typedef std::map<std::string,std::string> MapType;
  MapType mapping;

  // Configure the mapping between filename and MD5 hash
  mapping["Input/RA-Short.nrrd"]            = "a963bd6a755b853103a2d195e01a50d3";
  mapping["Input/RA-Float.nrrd"]            = "3ccccde44efaa3d688a86e94335c1f16";
  mapping["Input/RA-Slice-Short.nrrd"]      = "22cdc0af7d51934a744b9c4fd4748cd1";
  mapping["Input/RA-Slice-Float.nrrd"]      = "999078d36a4491d691cc93d8c3ed29fc";
  mapping["Input/Ramp-Zero-One-Float.nrrd"] = "f47efe1a6f48cb5cfe1aa23232f1168b";
  mapping["Input/Ramp-One-Zero-Float.nrrd"] = "0b18fac85955571d069b3666ff987119";
  mapping["Input/Ramp-Up-Short.nrrd"]       = "86f2ea8a68b3069f33f2271829a30aa2";
  mapping["Input/Ramp-Down-Short.nrrd"]     = "71f5c852a6251069fa1d60f796463343";
  mapping["Input/STAPLE1.png"]              = "095f00a68a84df4396914fa758f34dcc";
  mapping["Input/STAPLE2.png"]              = "301858f5eee39b092d28d9837f008fb8";


  // Loop over the map, load each file, and compare the hash value
  for ( MapType::iterator it = mapping.begin(); it != mapping.end(); ++it ) {
    reader.SetFileName ( dataFinder.GetFile ( it->first ) );
    EXPECT_EQ ( reader.GetFileName(), dataFinder.GetFile ( it->first ) );
    sitk::Image image = reader.Execute();
    ASSERT_TRUE ( image.GetITKBase() != NULL );
    hasher.SetHashFunction ( sitk::HashImageFilter::MD5 );
    EXPECT_EQ ( it->second, hasher.Execute ( image ) ) << " reading " << it->first;
    // Try the functional interface
    EXPECT_EQ ( it->second, hasher.Execute ( sitk::ReadImage ( dataFinder.GetFile ( it->first ) ) ) ) << "Functional interface";
  }

  EXPECT_EQ ( "ImageFileReader", reader.GetName() );
  EXPECT_NO_THROW ( reader.ToString() );

  std::string fileName =  dataFinder.GetFile( "Input/RA-Short.nrrd" );
  sitk::Image image;

  image = sitk::ReadImage( fileName, sitk::sitkInt32 );
  EXPECT_EQ( image.GetPixelID(), sitk::sitkInt32 );
  EXPECT_EQ( sitk::Hash(image), "f1045032b6862753b7e6b71771b552c40b8eaf32") << "Short to " <<  sitk::sitkInt32;

  image = sitk::ReadImage( fileName, sitk::sitkVectorInt16 );
  EXPECT_EQ( image.GetPixelID(), sitk::sitkVectorInt16 );
  EXPECT_EQ( sitk::Hash(image), "126ea8c3ef5573ca1e4e0deece920c2c4a4f38b5") << "Short to " <<  sitk::sitkVectorInt16;

  reader.SetOutputPixelType( sitk::sitkVectorInt32 );
  EXPECT_EQ( reader.GetOutputPixelType(), sitk::sitkVectorInt32 );

  reader.SetFileName( fileName );
  image = reader.Execute();
}

TEST(IO,ImageFileWriter) {
  namespace sitk = itk::simple;

  sitk::ImageFileWriter writer;

  sitk::Image img = sitk::Image(10,10, sitk::sitkUInt16);

  std::string filename = dataFinder.GetOutputFile ( "IO.ImageFileWriter1.mha" );
  writer.SetFileName(filename);

  ProgressUpdate progressCmd(writer);
  writer.AddCommand(sitk::sitkProgressEvent, progressCmd);

  CountCommand abortCmd(writer);
  writer.AddCommand(sitk::sitkAbortEvent, abortCmd);

  CountCommand deleteCmd(writer);
  writer.AddCommand(sitk::sitkDeleteEvent, deleteCmd);

  CountCommand endCmd(writer);
  writer.AddCommand(sitk::sitkEndEvent, endCmd);

  CountCommand iterCmd(writer);
  writer.AddCommand(sitk::sitkIterationEvent, iterCmd);

  CountCommand startCmd(writer);
  writer.AddCommand(sitk::sitkStartEvent, startCmd);

  CountCommand userCmd(writer);
  writer.AddCommand(sitk::sitkUserEvent, userCmd);

  EXPECT_NO_THROW ( writer.Execute(img) );

  EXPECT_EQ ( 1.0, progressCmd.m_Progress );
  EXPECT_EQ ( 0, abortCmd.m_Count );
  EXPECT_EQ ( 1, deleteCmd.m_Count );
  EXPECT_EQ ( 1, endCmd.m_Count );
  EXPECT_EQ ( 0, iterCmd.m_Count );
  EXPECT_EQ ( 1, startCmd.m_Count );
  EXPECT_EQ ( 0, userCmd.m_Count );

  EXPECT_EQ ( "ImageFileWriter", writer.GetName() );
  EXPECT_NO_THROW ( writer.ToString() );
}

TEST(IO,ReadWrite) {
  namespace sitk = itk::simple;
  sitk::HashImageFilter hasher;
  sitk::ImageFileReader reader;
  sitk::ImageFileWriter writer;

  // From the command line utility
  std::string md5 = "a963bd6a755b853103a2d195e01a50d3";
  std::string sha1 = "126ea8c3ef5573ca1e4e0deece920c2c4a4f38b5";


  ProgressUpdate progressCmd(reader);
  reader.AddCommand(sitk::sitkProgressEvent, progressCmd);

  CountCommand abortCmd(reader);
  reader.AddCommand(sitk::sitkAbortEvent, abortCmd);

  CountCommand deleteCmd(reader);
  reader.AddCommand(sitk::sitkDeleteEvent, deleteCmd);

  CountCommand endCmd(reader);
  reader.AddCommand(sitk::sitkEndEvent, endCmd);

  CountCommand iterCmd(reader);
  reader.AddCommand(sitk::sitkIterationEvent, iterCmd);

  CountCommand startCmd(reader);
  reader.AddCommand(sitk::sitkStartEvent, startCmd);

  CountCommand userCmd(reader);
  reader.AddCommand(sitk::sitkUserEvent, userCmd);


  sitk::Image image = reader.SetFileName ( dataFinder.GetFile ( "Input/RA-Short.nrrd" ) ).Execute();
  ASSERT_TRUE ( image.GetITKBase() != NULL );
  hasher.SetHashFunction ( sitk::HashImageFilter::MD5 );
  EXPECT_EQ ( md5, hasher.Execute ( image ) );
  hasher.SetHashFunction ( sitk::HashImageFilter::SHA1 );
  EXPECT_EQ ( sha1, hasher.Execute ( image ) );
  // JIRA SIMPLEITK-459 reader does not report any progress
  //EXPECT_EQ ( 1.0, progressCmd.m_Progress );
  EXPECT_EQ ( 0, abortCmd.m_Count );
  EXPECT_EQ ( 1, deleteCmd.m_Count );
  EXPECT_EQ ( 1, endCmd.m_Count );
  EXPECT_EQ ( 0, iterCmd.m_Count );
  EXPECT_EQ ( 1, startCmd.m_Count );
  EXPECT_EQ ( 0, userCmd.m_Count );


  // Write it out
  std::string filename = dataFinder.GetOutputFile ( "IO.ReadWrite.nrrd" );
  writer.SetFileName ( filename ).Execute ( image );
  ASSERT_TRUE ( dataFinder.FileExists ( filename ) );

  image = reader.SetFileName ( filename ).Execute();
  ASSERT_TRUE ( image.GetITKBase() != NULL );

  // Make sure we wrote and read the file correctly
  hasher.SetHashFunction ( sitk::HashImageFilter::MD5 );
  EXPECT_EQ ( md5, hasher.Execute ( image ) );
  hasher.SetHashFunction ( sitk::HashImageFilter::SHA1 );
  EXPECT_EQ ( sha1, hasher.Execute ( image ) );

  // Again, with the functional interface
  filename = dataFinder.GetOutputFile ( "IO.ReadWrite-Functional.nrrd" );
  sitk::WriteImage ( image, filename );
  ASSERT_TRUE ( dataFinder.FileExists ( filename ) );

  image = reader.SetFileName ( filename ).Execute();
  ASSERT_TRUE ( image.GetITKBase() != NULL );

  // Make sure we wrote and read the file correctly
  hasher.SetHashFunction ( sitk::HashImageFilter::MD5 );
  EXPECT_EQ ( md5, hasher.Execute ( image ) );
  hasher.SetHashFunction ( sitk::HashImageFilter::SHA1 );
  EXPECT_EQ ( sha1, hasher.Execute ( image ) );

}


TEST(IO,2DFormats) {
  itk::simple::HashImageFilter hasher;
  itk::simple::ImageFileReader reader;

  itk::simple::Image image = reader.SetFileName ( dataFinder.GetFile ( "Input/RA-Slice-Short.png" ) ).Execute();
  ASSERT_TRUE ( image.GetITKBase() != NULL );
  hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 );
  EXPECT_EQ ( "bf0f7bae60b0322222e224941c31f37a981901aa", hasher.Execute ( image ) );
  ASSERT_EQ ( 2u, image.GetDimension() );
  EXPECT_EQ ( 64u, image.GetWidth() );
  EXPECT_EQ ( 64u, image.GetHeight() );
  EXPECT_EQ ( 0u, image.GetDepth() );

}

namespace sitk = itk::simple;

TEST(IO, SeriesReader) {

  std::vector< std::string > fileNames;
  fileNames.push_back( dataFinder.GetFile ( "Input/BlackDots.png" ) );
  fileNames.push_back( dataFinder.GetFile ( "Input/BlackDots.png" ) );
  fileNames.push_back( dataFinder.GetFile ( "Input/BlackDots.png" ) );

  sitk::ImageSeriesReader reader;

  EXPECT_THROW( reader.Execute(), sitk::GenericException );

  EXPECT_EQ( reader.GetOutputPixelType(), sitk::sitkUnknown );
  EXPECT_EQ( 0u, reader.GetFileNames().size());

  ProgressUpdate progressCmd(reader);
  reader.AddCommand(sitk::sitkProgressEvent, progressCmd);

  CountCommand abortCmd(reader);
  reader.AddCommand(sitk::sitkAbortEvent, abortCmd);

  CountCommand deleteCmd(reader);
  reader.AddCommand(sitk::sitkDeleteEvent, deleteCmd);

  CountCommand endCmd(reader);
  reader.AddCommand(sitk::sitkEndEvent, endCmd);

  CountCommand iterCmd(reader);
  reader.AddCommand(sitk::sitkIterationEvent, iterCmd);

  CountCommand startCmd(reader);
  reader.AddCommand(sitk::sitkStartEvent, startCmd);

  CountCommand userCmd(reader);
  reader.AddCommand(sitk::sitkUserEvent, userCmd);

  sitk::Image image = reader.SetFileNames ( fileNames ).Execute();
  EXPECT_EQ ( "b13c0a17109e3a5058e8f225c9ef2dbcf79ac240", sitk::Hash( image ) );
  EXPECT_EQ( 3u, reader.GetFileNames().size());
  EXPECT_EQ ( 3u, image.GetDimension() );
  EXPECT_EQ ( 256u, image.GetWidth() );
  EXPECT_EQ ( 256u, image.GetHeight() );
  EXPECT_EQ ( 3u, image.GetDepth() );
  EXPECT_EQ ( 1.0, progressCmd.m_Progress );
  EXPECT_EQ ( 0, abortCmd.m_Count );
  EXPECT_EQ ( 1, deleteCmd.m_Count );
  EXPECT_EQ ( 1, endCmd.m_Count );
  EXPECT_EQ ( 0, iterCmd.m_Count );
  EXPECT_EQ ( 1, startCmd.m_Count );
  EXPECT_EQ ( 0, userCmd.m_Count );


  fileNames.push_back( dataFinder.GetFile ( "Input/WhiteDots.png" ));
  image = sitk::ReadImage( fileNames );
  EXPECT_EQ ( "62fff5903956f108fbafd506e31c1e733e527820", sitk::Hash( image ) );
  EXPECT_EQ ( 4u, image.GetDepth() );

  fileNames.resize(0);
  fileNames.push_back( dataFinder.GetFile ( "Input/VM1111Shrink-RGB.png" ) );
  fileNames.push_back( dataFinder.GetFile ( "Input/VM1111Shrink-RGB.png" ) );
  fileNames.push_back( dataFinder.GetFile ( "Input/VM1111Shrink-RGB.png" ) );
  reader.SetFileNames ( fileNames );
  image = reader.Execute();
  EXPECT_EQ ( 3u, image.GetDepth() );
  EXPECT_EQ ( "bb42b8d3991132b4860adbc4b3f6c38313f52b4c", sitk::Hash( image ) );

  EXPECT_EQ ( "ImageSeriesReader", reader.GetName() );
  EXPECT_NO_THROW( reader.ToString() );

  reader.SetOutputPixelType(sitk::sitkUInt8);
  EXPECT_EQ(reader.GetOutputPixelType(), sitk::sitkUInt8);
  image = reader.Execute();
  EXPECT_EQ ( 3u, image.GetDepth() );
  EXPECT_EQ ( "a51361940fdf6c33cf700e1002e5f5ca5b88cc42", sitk::Hash( image ) );

  fileNames.resize(0);
  reader.SetFileNames ( fileNames );
  EXPECT_THROW( reader.Execute(), sitk::GenericException );
}


TEST(IO,Write_BadName) {

  sitk::Image image = sitk::ReadImage( dataFinder.GetFile ( "Input/BlackDots.png" ) );
  EXPECT_EQ ( "0188164c9932359b3f33f176d0d73661c4dc04a8", sitk::Hash( image ) );

  ASSERT_THROW(sitk::WriteImage( image, dataFinder.GetOutputFile ( "this.isafilenamewithnoimageio" ) ),  std::exception ) << "Checking for assert on bad output image name.";
}


TEST(IO, DicomSeriesReader) {

  std::vector< std::string > fileNames;
  std::vector< std::string > seriesIDs;
  std::string dicomDir;

  sitk::ImageSeriesReader reader;

  dicomDir = dataFinder.GetDirectory( ) + "/Input/DicomSeries";

  seriesIDs = reader.GetGDCMSeriesIDs( dicomDir );

  ASSERT_FALSE ( seriesIDs.empty() );
  EXPECT_EQ( "1.2.840.113619.2.133.1762890640.1886.1055165015.999", seriesIDs[0] );

  fileNames = reader.GetGDCMSeriesFileNames( dicomDir );

  reader.SetFileNames( fileNames );
  sitk::Image image = reader.Execute();
  EXPECT_EQ( "f5ad2854d68fc87a141e112e529d47424b58acfb", sitk::Hash( image ) );

  fileNames = reader.GetGDCMSeriesFileNames( dicomDir, "1.2.840.113619.2.133.1762890640.1886.1055165015.999" );
  EXPECT_EQ( 3u, fileNames.size() );

  // When reading a series each slice has its own meta-data dictionary
  // so the user has to decide on how to combine them, our image will
  // return an empty dictionary.
  std::vector< std::string > metaDataKeys = image.GetMetaDataKeys();
  EXPECT_EQ( 0u, metaDataKeys.size() );
}


TEST(IO, ImageSeriesWriter )
{

  sitk::ImageSeriesWriter writer;

  EXPECT_FALSE(writer.GetUseCompression());
  writer.UseCompressionOn();
  EXPECT_TRUE(writer.GetUseCompression());
  writer.UseCompressionOff();
  EXPECT_FALSE(writer.GetUseCompression());

  EXPECT_NO_THROW ( writer.ToString() );



  std::vector< std::string > fileNames;
  fileNames.push_back( dataFinder.GetOutputDirectory()+"/ImageSeriesWriter_1.png" );
  fileNames.push_back( dataFinder.GetOutputDirectory()+"/ImageSeriesWriter_2.png" );
  fileNames.push_back( dataFinder.GetOutputDirectory()+"/ImageSeriesWriter_3.png" );

  std::vector<unsigned int> size;
  size.push_back(10);
  size.push_back(10);
  size.push_back(3);

  sitk::Image image( size, sitk::sitkUInt8 );

  EXPECT_ANY_THROW(writer.Execute(image));

  writer.SetFileNames( fileNames );

  EXPECT_EQ( writer.GetFileNames().size(), 3u );

  EXPECT_NO_THROW( writer.Execute( image ) );

  fileNames.push_back( dataFinder.GetOutputDirectory()+"/ImageSeriesWriter_4.png" );
  EXPECT_ANY_THROW( sitk::WriteImage( image, fileNames ) );

  fileNames.pop_back();
  fileNames.pop_back();

  EXPECT_ANY_THROW( sitk::WriteImage( image, fileNames ) );

  fileNames.resize(0);
  writer.SetFileNames( fileNames );
  EXPECT_ANY_THROW(writer.Execute(image));

  // Check writing DICOM series throws an exception
  fileNames.clear();
  fileNames.push_back( dataFinder.GetOutputDirectory()+"/ImageSeriesWriter_1.dcm" );
  fileNames.push_back( dataFinder.GetOutputDirectory()+"/ImageSeriesWriter_2.dcm" );
  fileNames.push_back( dataFinder.GetOutputDirectory()+"/ImageSeriesWriter_3.dcm" );

  EXPECT_ANY_THROW( sitk::WriteImage( image, fileNames ) );

  writer.SetFileNames(fileNames);
  EXPECT_ANY_THROW(writer.Execute(image));

  fileNames.clear();
  fileNames.push_back( dataFinder.GetOutputDirectory()+"/ImageSeriesWriter_1.DICOM" );
  fileNames.push_back( dataFinder.GetOutputDirectory()+"/ImageSeriesWriter_2.DICOM" );
  fileNames.push_back( dataFinder.GetOutputDirectory()+"/ImageSeriesWriter_3.DICOM" );

  EXPECT_ANY_THROW( sitk::WriteImage( image, fileNames ) );
}


TEST(IO, VectorImageSeriesWriter )
{


  std::vector< std::string > fileNames;
  fileNames.push_back( dataFinder.GetOutputDirectory()+"/VectorImageSeriesWriter_1.png" );
  fileNames.push_back( dataFinder.GetOutputDirectory()+"/VectorImageSeriesWriter_2.png" );
  fileNames.push_back( dataFinder.GetOutputDirectory()+"/VectorImageSeriesWriter_3.png" );

  std::vector<unsigned int> size;
  size.push_back(10);
  size.push_back(10);
  size.push_back(3);

  sitk::Image image = sitk::PhysicalPointSource(sitk::sitkVectorUInt8, size);

  sitk::ImageSeriesWriter writer;
  writer.SetFileNames( fileNames );

  EXPECT_NO_THROW( writer.Execute( image ) );


  sitk::Image result = sitk::ReadImage(fileNames[0]);

  EXPECT_EQ ( "1729319806705e94181c9b9f4bd5e0ac854935db", sitk::Hash( result ) );
}
