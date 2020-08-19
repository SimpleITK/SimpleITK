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
#include <SimpleITKTestHarness.h>
#include <sitkImageFileReader.h>
#include <sitkImageSeriesReader.h>
#include <sitkImageFileWriter.h>
#include <sitkImageSeriesWriter.h>
#include <sitkHashImageFilter.h>
#include <sitkPhysicalPointImageSource.h>
#include <sitkAdditiveGaussianNoiseImageFilter.h>
#include <sitkExtractImageFilter.h>
#include <sitkRegionOfInterestImageFilter.h>

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

  using MapType = std::map<std::string,std::string>;
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
    ASSERT_NE ( image.GetITKBase(), nullptr );
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

  EXPECT_NO_THROW(image=sitk::ReadImage( fileName, sitk::sitkInt32, "NrrdImageIO" ) );
  EXPECT_EQ( image.GetPixelID(), sitk::sitkInt32 );
  EXPECT_EQ( sitk::Hash(image), "f1045032b6862753b7e6b71771b552c40b8eaf32") << "Short to " <<  sitk::sitkInt32;

  EXPECT_THROW(sitk::ReadImage( fileName, sitk::sitkInt32, "DoesNoExistImageIO" ), sitk::GenericException );
  EXPECT_ANY_THROW(sitk::ReadImage( fileName, sitk::sitkInt32, "GDCMImageIO" ));

  reader.SetOutputPixelType( sitk::sitkVectorInt32 );
  EXPECT_EQ( reader.GetOutputPixelType(), sitk::sitkVectorInt32 );

  std::vector<std::string> ios;
  EXPECT_NO_THROW( ios = reader.GetRegisteredImageIOs() );
  EXPECT_TRUE( std::find( ios.begin(), ios.end(), "GDCMImageIO") != ios.end() );

  reader.SetFileName( fileName );
  image = reader.Execute();
}

#ifdef SITK_INT64_PIXELIDS
TEST(IO, ReadWriteInt64){

  namespace sitk = itk::simple;

  sitk::Image img1 = sitk::Image(10,10, sitk::sitkUInt64);
  img1.SetPixelAsUInt64(std::vector<uint32_t>(2,1), 1u);
  img1.SetPixelAsUInt64(std::vector<uint32_t>(2,2), uint64_t(4294967296));

  sitk::Image img2 = sitk::Image(10,10, sitk::sitkInt64);
  img2.SetPixelAsInt64(std::vector<uint32_t>(2,1), 1u);
  img2.SetPixelAsInt64(std::vector<uint32_t>(2,2), int64_t(4294967296));
  img2.SetPixelAsInt64(std::vector<uint32_t>(2,3), -1);
  img2.SetPixelAsInt64(std::vector<uint32_t>(2,4), int64_t(-4294967296));


  const char *extension_list[] = {"mha",
                                  "nii",
                                  "nrrd",
                                  nullptr};

  for (unsigned int i = 0; extension_list[i]; ++i)
    {
    const std::string filename = dataFinder.GetOutputFile("IO.ReadWriteInt64.") + extension_list[i];

    sitk::WriteImage(img1, filename);
    sitk::Image out = sitk::ReadImage(filename);

    EXPECT_EQ( img1.GetPixelID(), out.GetPixelID() ) << "filename : " << filename;
    EXPECT_EQ( sitk::Hash(img1), sitk::Hash(out)) << "filename : " << filename;;

    sitk::WriteImage(img2, filename);
    out = sitk::ReadImage(filename);

    EXPECT_EQ( img2.GetPixelID(), out.GetPixelID() ) << "filename : " << filename;;
    EXPECT_EQ( sitk::Hash(img2), sitk::Hash(out)) << "filename : " << filename;;

    }

}
#endif

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

  std::vector<std::string> ios;
  EXPECT_NO_THROW( ios = writer.GetRegisteredImageIOs() );
  EXPECT_TRUE( std::find( ios.begin(), ios.end(), "GDCMImageIO") != ios.end() );

}

TEST(IO,ImageFileWriter_Compression)
{
  namespace sitk = itk::simple;

  sitk::Image generatedImage = sitk::Image(10, 10, sitk::sitkUInt8);

  generatedImage = sitk::AdditiveGaussianNoise(generatedImage, 32.0, 0.0, 99u);
  const std::string expectedHash = sitk::Hash(generatedImage);

  std::string filename = dataFinder.GetOutputFile("IO.ImageFileWriter_Compression.nrrd");

  sitk::ImageFileWriter writer;

  EXPECT_EQ(writer.GetCompressor(), "");
  EXPECT_EQ(writer.GetCompressionLevel(), -1);

  writer.UseCompressionOn();

  writer.SetFileName(filename);
  writer.SetCompressor("does_not_exist");
  writer.SetCompressionLevel(10);
  EXPECT_NO_THROW(writer.Execute(generatedImage));
  EXPECT_EQ(expectedHash, sitk::Hash(sitk::ReadImage(filename)));
  EXPECT_EQ("does_not_exist", writer.GetCompressor());
  EXPECT_EQ(10, writer.GetCompressionLevel());

  writer.SetCompressor("gzip");
  writer.SetCompressionLevel(9);
  EXPECT_NO_THROW(writer.Execute(generatedImage));
  EXPECT_EQ(expectedHash, sitk::Hash(sitk::ReadImage(filename)));

  writer.SetCompressor("gzip");
  writer.SetCompressionLevel(1);
  EXPECT_NO_THROW(writer.Execute(generatedImage));
  EXPECT_EQ(expectedHash, sitk::Hash(sitk::ReadImage(filename)));

  filename = dataFinder.GetOutputFile("IO.ImageFileWriter_Compression.tiff");

  writer.SetFileName(filename);

  writer.SetCompressor("JPEG");
  writer.SetCompressionLevel(50);
  EXPECT_NO_THROW(writer.Execute(generatedImage));
  // No hash comparison due to lossy compression
  // EXPECT_EQ(expectedHash, sitk::Hash(sitk::ReadImage(filename)));

  writer.SetCompressor("packbits");
  writer.SetCompressionLevel(1);
  EXPECT_NO_THROW(writer.Execute(generatedImage));
  EXPECT_EQ(expectedHash, sitk::Hash(sitk::ReadImage(filename)));
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
  ASSERT_NE ( image.GetITKBase(), nullptr );
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
  ASSERT_NE ( image.GetITKBase(), nullptr );

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
  ASSERT_NE ( image.GetITKBase(), nullptr );

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
  ASSERT_NE ( image.GetITKBase(), nullptr );
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
  EXPECT_EQ ( 3u, reader.GetFileNames().size() );
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

  std::vector<std::string> ios;
  EXPECT_NO_THROW( ios = reader.GetRegisteredImageIOs() );
  EXPECT_TRUE( std::find( ios.begin(), ios.end(), "GDCMImageIO") != ios.end() );

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


  EXPECT_FALSE( reader.GetMetaDataDictionaryArrayUpdate() );
  reader.MetaDataDictionaryArrayUpdateOn();
  EXPECT_TRUE( reader.GetMetaDataDictionaryArrayUpdate() );

  image = reader.Execute();
  EXPECT_EQ( 3u, image.GetSize()[2] );
  for (unsigned int i = 0; i <  image.GetSize()[2]; ++i)
    {
      std::vector<std::string> keys = reader.GetMetaDataKeys(0);
      EXPECT_EQ( 95u, keys.size() );

      for(unsigned int j = 0; j < keys.size(); ++j )
        {
        EXPECT_TRUE( reader.HasMetaDataKey(i, keys[j]) );
        EXPECT_NO_THROW( reader.GetMetaData(i, keys[j]) );
        }
    }
  EXPECT_FALSE( reader.HasMetaDataKey(0, "nothing" ) );
  EXPECT_ANY_THROW( reader.GetMetaDataKeys(99) );
  EXPECT_ANY_THROW( reader.HasMetaDataKey(99, "nothing") );
  EXPECT_ANY_THROW( reader.GetMetaData(99, "nothing") );
}


TEST(IO, ImageSeriesWriter )
{

  sitk::ImageSeriesWriter writer;

  EXPECT_FALSE(writer.GetUseCompression());
  writer.UseCompressionOn();
  EXPECT_TRUE(writer.GetUseCompression());
  writer.UseCompressionOff();
  EXPECT_FALSE(writer.GetUseCompression());

  EXPECT_EQ(writer.GetCompressor(), "");
  EXPECT_EQ(writer.GetCompressionLevel(), -1);

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

  std::vector<std::string> ios;
  EXPECT_NO_THROW( ios = writer.GetRegisteredImageIOs() );
  EXPECT_TRUE( std::find( ios.begin(), ios.end(), "GDCMImageIO") != ios.end() );

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

TEST(IO, ImageFileReader_ImageInformation )
{
  const std::string dicomFile1 = dataFinder.GetDirectory( ) + "/Input/DicomSeries/Image0075.dcm";
  const std::string file2 = dataFinder.GetDirectory( ) + "/Input/fruit.png";

  sitk::ImageFileReader reader;
  reader.SetFileName(dicomFile1);
  EXPECT_EQ(reader.GetPixelID(), sitk::sitkUnknown);
  EXPECT_EQ(reader.GetPixelIDValue(), sitk::sitkUnknown);
  EXPECT_EQ(reader.GetDimension(), 0u);
  EXPECT_EQ(reader.GetNumberOfComponents(), 0u);
  EXPECT_VECTOR_DOUBLE_NEAR(reader.GetOrigin(), std::vector<double>(), 1e-8);
  EXPECT_VECTOR_DOUBLE_NEAR(reader.GetSpacing(), std::vector<double>(), 1e-8);
  EXPECT_VECTOR_DOUBLE_NEAR(reader.GetDirection(), std::vector<double>(), 1e-8);
  EXPECT_VECTOR_NEAR(reader.GetSize(), std::vector<int>(), 1e-10);
  EXPECT_ANY_THROW( reader.GetMetaDataKeys() );
  EXPECT_ANY_THROW( reader.HasMetaDataKey("nothing") );
  EXPECT_ANY_THROW( reader.GetMetaData("nothing") );


  sitk::Image image = sitk::ReadImage(dicomFile1);
  reader.ReadImageInformation();

  EXPECT_EQ(reader.GetPixelID(), sitk::sitkInt16);
  EXPECT_EQ(reader.GetPixelID(), image.GetPixelID());
  EXPECT_EQ(reader.GetPixelIDValue(), sitk::sitkInt16);
  EXPECT_EQ(reader.GetPixelIDValue(), image.GetPixelIDValue());
  EXPECT_EQ(reader.GetDimension(), 3u);
  EXPECT_EQ(reader.GetDimension(), image.GetDimension());
  EXPECT_EQ(reader.GetNumberOfComponents(), 1u);
  EXPECT_EQ(reader.GetNumberOfComponents(), image.GetNumberOfComponentsPerPixel());
  EXPECT_VECTOR_DOUBLE_NEAR(reader.GetOrigin(), v3(-112, -21.687999, 126.894000 ), 1e-6);
  EXPECT_VECTOR_DOUBLE_NEAR(reader.GetOrigin(), image.GetOrigin(), 1e-6);
  EXPECT_VECTOR_DOUBLE_NEAR(reader.GetSpacing(), v3(0.859375, 0.8593899, 1.600000 ), 1e-6);
  EXPECT_VECTOR_DOUBLE_NEAR(reader.GetSpacing(), image.GetSpacing(), 1e-6);
  EXPECT_VECTOR_DOUBLE_NEAR(reader.GetDirection(), v9(1, 0, -0,
                                                      0,  0.46665081166793676, 0.88444164305490258,
                                                      0, -0.88444164305490258, 0.46665081166793676 ), 1e-8);
  EXPECT_VECTOR_DOUBLE_NEAR(reader.GetDirection(), image.GetDirection(), 1e-16);
  EXPECT_VECTOR_NEAR(reader.GetSize(), v3(256.0, 256.0, 1.0), 1e-10);

  std::vector<std::string> keys = reader.GetMetaDataKeys();
  for(unsigned int i = 0; i < keys.size(); ++i )
    {
    EXPECT_TRUE( reader.HasMetaDataKey(keys[i]) );
    EXPECT_TRUE( image.HasMetaDataKey(keys[i]) );
    EXPECT_NO_THROW( reader.GetMetaData( keys[i]) );
    }
  EXPECT_EQ(reader.GetMetaData( "0008|0031"), "153128");

  // Checks that a  reader updates exiting information
  reader.SetFileName(file2);
  reader.Execute();

  EXPECT_EQ(reader.GetPixelID(), sitk::sitkVectorUInt8);
  EXPECT_EQ(reader.GetPixelIDValue(), sitk::sitkVectorUInt8);
  EXPECT_EQ(reader.GetDimension(), 2u);
  EXPECT_EQ(reader.GetNumberOfComponents(), 3u);
  EXPECT_VECTOR_DOUBLE_NEAR(reader.GetOrigin(), v2(0.0, 0.0), 1e-8);
  EXPECT_VECTOR_DOUBLE_NEAR(reader.GetSpacing(), v2(1.0, 1.0 ), 1e-8);
  EXPECT_VECTOR_DOUBLE_NEAR(reader.GetDirection(), v4(1.0, 0.0, 0.0, 1.0 ), 1e-8);
  EXPECT_VECTOR_NEAR(reader.GetSize(), v2( 179.0, 240.0), 1e-10);
  EXPECT_EQ( reader.GetMetaDataKeys().size(), 0u);
}


TEST(IO, ImageFileReader_SetImageIO )
{
  namespace sitk = itk::simple;

  sitk::HashImageFilter hasher;
  sitk::ImageFileReader reader;
  sitk::Image image;

  EXPECT_EQ( "", reader.GetImageIO());

  reader.SetFileName ( dataFinder.GetFile ( "Input/RA-Slice-Short.png" ) );

  reader.SetImageIO("SomethingThatDoesNotExist");
  EXPECT_ANY_THROW( reader.ReadImageInformation() );
  EXPECT_ANY_THROW( reader.Execute() );
  EXPECT_EQ( "SomethingThatDoesNotExist", reader.GetImageIO());

  reader.SetImageIO("MetaImageIO");
  EXPECT_ANY_THROW( reader.Execute() );
  EXPECT_ANY_THROW( reader.ReadImageInformation() );

  reader.SetImageIO("PNGImageIO");
  EXPECT_EQ( "PNGImageIO", reader.GetImageIO());
  EXPECT_NO_THROW( reader.ReadImageInformation() );

  EXPECT_VECTOR_NEAR( v2(64,64), reader.GetSize(), 0.0 );
  EXPECT_EQ ( 2u, reader.GetDimension() );
  EXPECT_EQ ( 1u, reader.GetNumberOfComponents() );



  EXPECT_NO_THROW( image = reader.Execute() );
  EXPECT_EQ( "PNGImageIO", reader.GetImageIO());
  EXPECT_EQ ( "bf0f7bae60b0322222e224941c31f37a981901aa", hasher.Execute ( image ) );


  ASSERT_NE ( image.GetITKBase(), nullptr );
  EXPECT_EQ ( 2u, image.GetDimension() );
  EXPECT_EQ ( 64u, image.GetWidth() );
  EXPECT_EQ ( 64u, image.GetHeight() );
  EXPECT_EQ ( 0u, image.GetDepth() );

}


TEST(IO, ImageFileReader_GetImageIOFromFileName )
{
  namespace sitk = itk::simple;

  std::string imageio;

  const std::string filename1 = dataFinder.GetFile ( "Input/RA-Slice-Short.png" );
  EXPECT_EQ( "PNGImageIO" , sitk::ImageFileReader::GetImageIOFromFileName( filename1 ) );

  const std::string filename2 =  dataFinder.GetFile( "Input/cthead1-Float.mha" );
  EXPECT_EQ( "MetaImageIO" , sitk::ImageFileReader::GetImageIOFromFileName( filename2 ) );

  EXPECT_NO_THROW( imageio = sitk::ImageFileReader::GetImageIOFromFileName( "file_does_not_exist" ) );
  EXPECT_EQ( "", imageio);
}


TEST(IO, ImageFileReader_Extract1 )
{

  sitk::ImageFileReader reader;
  EXPECT_EQ( reader.GetExtractIndex(), std::vector<int>() );

  EXPECT_EQ( reader.GetExtractSize(), std::vector<unsigned int>() );

  reader.SetFileName( dataFinder.GetFile( "Input/cthead1-Float.mha" ) );

  ASSERT_NO_THROW ( reader.ReadImageInformation() );

  const std::vector<uint64_t> fullSize64 = reader.GetSize();

  sitk::Image fullImage = reader.Execute();

  EXPECT_VECTOR_NEAR( reader.GetSize(), fullImage.GetSize(), 1e-10 );

  std::vector<unsigned int> extractSize(fullSize64.size());
  for ( size_t i = 0; i < extractSize.size(); ++i )
    {
    extractSize[i] = std::max(1u, static_cast<unsigned int>(fullSize64[i]/2));
    }

  reader.SetExtractSize(extractSize);
  EXPECT_EQ( extractSize, reader.GetExtractSize() );

  sitk::Image extractImage1 = reader.Execute();

  EXPECT_EQ( fullSize64, reader.GetSize() );
  EXPECT_EQ( extractSize, extractImage1.GetSize() );
  EXPECT_EQ( fullImage.GetOrigin(), reader.GetOrigin() );
  EXPECT_EQ( fullImage.GetOrigin(), extractImage1.GetOrigin() );
  EXPECT_EQ( fullImage.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ),
             extractImage1.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ));
  EXPECT_EQ( fullImage.GetPixelAsFloat( std::vector<uint32_t>( 2, 13 ) ),
             extractImage1.GetPixelAsFloat( std::vector<uint32_t>( 2, 13 ) ));

  std::vector<int> extractIndex(fullSize64.size());
  std::fill( extractIndex.begin(), extractIndex.end(), 2);

  reader.SetExtractIndex( extractIndex );
  EXPECT_EQ( extractIndex, reader.GetExtractIndex() );

  sitk::Image extractImage2 = reader.Execute();

  EXPECT_EQ( fullSize64, reader.GetSize() );
  EXPECT_EQ( extractSize, extractImage1.GetSize() );
  EXPECT_EQ( fullImage.GetOrigin(), reader.GetOrigin() );
  EXPECT_NE( fullImage.GetOrigin(), extractImage2.GetOrigin() );
  EXPECT_EQ( fullImage.GetPixelAsFloat( std::vector<uint32_t>( 2, 2 ) ),
             extractImage2.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ));
  EXPECT_EQ( fullImage.GetPixelAsFloat( std::vector<uint32_t>( 2, 15 ) ),
             extractImage2.GetPixelAsFloat( std::vector<uint32_t>( 2, 13 ) ));
}


TEST(IO, ImageFileReader_Extract2 )
{

  sitk::Image generatedImage(100,100,100, sitk::sitkInt16);
  generatedImage.SetOrigin(v3(2.0, 4.0, 6.0));
  generatedImage.SetSpacing(v3(1.0, 2.0, 3.0));

  generatedImage = sitk::AdditiveGaussianNoise(generatedImage, 256.0, 0.0, 99u);

  generatedImage.SetMetaData( "MyKey", "my_value" );

  const ::testing::TestInfo *info = ::testing::UnitTest::GetInstance()->current_test_info();
  std::string filename = std::string(info->test_case_name()) + "." + info->name() + ".mha";
  filename = dataFinder.GetOutputFile(filename);

  sitk::WriteImage(generatedImage, filename);

  std::vector<int> extractIndex(0);
  std::vector<unsigned int> extractSize(0);

  sitk::ImageFileReader reader;

  //
  // Test extraction with zero sized extract properties
  //
  reader.SetFileName(filename);
  reader.SetExtractIndex(extractIndex);
  reader.SetExtractSize(extractSize);

  sitk::Image result;
  EXPECT_NO_THROW( result = reader.Execute() );
  EXPECT_EQ( sitk::Hash(generatedImage), sitk::Hash(result) );
  EXPECT_TRUE( reader.HasMetaDataKey("MyKey") );
  EXPECT_EQ( "my_value", reader.GetMetaData("MyKey") );
  EXPECT_TRUE( result.HasMetaDataKey("MyKey") );
  EXPECT_EQ( "my_value", result.GetMetaData("MyKey") );
  EXPECT_EQ( generatedImage.GetOrigin(), result.GetOrigin() );
  EXPECT_EQ( generatedImage.GetSpacing(), result.GetSpacing() );

  extractIndex.resize(3);
  extractSize.resize(3);

  //
  // Test extraction with a 3d roi
  //
  extractIndex[0] = 1;
  extractIndex[1] = 2;
  extractIndex[2] = 3;

  extractSize[0] = 2;
  extractSize[1] = 3;
  extractSize[2] = 5;

  reader.SetExtractIndex(extractIndex);
  EXPECT_EQ( extractIndex, reader.GetExtractIndex() );
  reader.SetExtractSize(extractSize);
  EXPECT_EQ( extractSize, reader.GetExtractSize() );

  EXPECT_NO_THROW( result = reader.Execute() );
  EXPECT_EQ( sitk::Hash(sitk::RegionOfInterest( generatedImage, extractSize, extractIndex )),
             sitk::Hash(result) );
  EXPECT_TRUE( reader.HasMetaDataKey("MyKey") );
  EXPECT_EQ( "my_value", reader.GetMetaData("MyKey") );
  EXPECT_TRUE( result.HasMetaDataKey("MyKey") );
  EXPECT_EQ( "my_value", result.GetMetaData("MyKey") );
  EXPECT_EQ( generatedImage.GetSpacing(), result.GetSpacing() );
  EXPECT_EQ( v3(3.0, 8.0, 15.0), result.GetOrigin() );
  EXPECT_EQ( 3u, result.GetDimension() );
  EXPECT_EQ( extractSize, result.GetSize() );


  //
  // Test extraction with collapsing x-dim
  //
  extractIndex[0] = 2;
  extractIndex[1] = 3;
  extractIndex[2] = 4;

  extractSize[0] = 0;
  extractSize[1] = 1;
  extractSize[2] = 2;

  reader.SetExtractIndex(extractIndex);
  EXPECT_EQ( extractIndex, reader.GetExtractIndex() );
  reader.SetExtractSize(extractSize);
  EXPECT_EQ( extractSize, reader.GetExtractSize() );

  result = reader.Execute();

  EXPECT_EQ( sitk::Hash(sitk::Extract( generatedImage, extractSize, extractIndex )),
             sitk::Hash(result) );
  EXPECT_TRUE( reader.HasMetaDataKey("MyKey") );
  EXPECT_EQ( "my_value", reader.GetMetaData("MyKey") );
  EXPECT_TRUE( result.HasMetaDataKey("MyKey") );
  EXPECT_EQ( "my_value", result.GetMetaData("MyKey") );
  EXPECT_EQ( v2(2.0, 3.0), result.GetSpacing() );
  EXPECT_EQ( v2(10.0, 18.0), result.GetOrigin() );
  EXPECT_EQ( 2u, result.GetDimension() );
  EXPECT_EQ( 1u, result.GetSize()[0] );
  EXPECT_EQ( 2u, result.GetSize()[1] );

  //
  // Test extraction with collapsing y-dim
  //
  extractIndex[0] = 2;
  extractIndex[1] = 5;
  extractIndex[2] = 7;

  extractSize[0] = 3;
  extractSize[1] = 0;
  extractSize[2] = 5;

  reader.SetExtractIndex(extractIndex);
  EXPECT_EQ( extractIndex, reader.GetExtractIndex() );
  reader.SetExtractSize(extractSize);
  EXPECT_EQ( extractSize, reader.GetExtractSize() );

  EXPECT_NO_THROW(result = reader.Execute());

  EXPECT_EQ( sitk::Hash(sitk::Extract( generatedImage, extractSize, extractIndex )),
             sitk::Hash(result) );
  EXPECT_TRUE( reader.HasMetaDataKey("MyKey") );
  EXPECT_EQ( "my_value", reader.GetMetaData("MyKey") );
  EXPECT_TRUE( result.HasMetaDataKey("MyKey") );
  EXPECT_EQ( "my_value", result.GetMetaData("MyKey") );
  EXPECT_EQ( v2(1.0, 3.0), result.GetSpacing() );
  EXPECT_EQ( v2(4.0, 27.0), result.GetOrigin() );
  EXPECT_EQ( 2u, result.GetDimension() );
  EXPECT_EQ( 3u, result.GetSize()[0] );
  EXPECT_EQ( 5u, result.GetSize()[1] );

  //
  // Test extraction with collapsing z-dim
  //
  extractIndex[0] = 1;
  extractIndex[1] = 3;
  extractIndex[2] = 5;

  extractSize[0] = 3;
  extractSize[1] = 5;
  extractSize[2] = 0;

  reader.SetExtractIndex(extractIndex);
  EXPECT_EQ( extractIndex, reader.GetExtractIndex() );
  reader.SetExtractSize(extractSize);
  EXPECT_EQ( extractSize, reader.GetExtractSize() );

  EXPECT_NO_THROW(result = reader.Execute());

  EXPECT_EQ( sitk::Hash(sitk::Extract( generatedImage, extractSize, extractIndex )),
             sitk::Hash(result) );
  EXPECT_TRUE( reader.HasMetaDataKey("MyKey") );
  EXPECT_EQ( "my_value", reader.GetMetaData("MyKey") );
  EXPECT_TRUE( result.HasMetaDataKey("MyKey") );
  EXPECT_EQ( "my_value", result.GetMetaData("MyKey") );
  EXPECT_EQ( v2(1.0, 2.0), result.GetSpacing() );
  EXPECT_EQ( v2(3.0, 10.0), result.GetOrigin() );
  EXPECT_EQ( 2u, result.GetDimension() );
  EXPECT_EQ( 3u, result.GetSize()[0] );
  EXPECT_EQ( 5u, result.GetSize()[1] );
}


TEST(IO, ImageFileReader_5DExtract )
{
  const std::string file = dataFinder.GetDirectory( ) + "/Input/points_5d.mha";

  sitk::ImageFileReader reader;
  reader.SetFileName(file);

  reader.ReadImageInformation();

  EXPECT_EQ(reader.GetPixelID(), sitk::sitkVectorFloat32);
  EXPECT_EQ(reader.GetPixelIDValue(), sitk::sitkVectorFloat32);
  EXPECT_EQ(reader.GetDimension(), 5u);
  EXPECT_EQ(reader.GetNumberOfComponents(), 5u);
  EXPECT_VECTOR_DOUBLE_NEAR(reader.GetOrigin(), v5(0.0, 0.0, 0.0, 0.0, 0.0), 1e-8);
  EXPECT_VECTOR_DOUBLE_NEAR(reader.GetSpacing(), v5(1.0, 1.0, 1.0, 1.0, 1.0), 1e-6);
  std::vector<double> direction_i5(25u, 0.0);
  for (unsigned int i = 0; i < 5; ++i)
    direction_i5[i*5+i] = 1.0;
  EXPECT_VECTOR_DOUBLE_NEAR(reader.GetDirection(), direction_i5, 1e-8);
  EXPECT_VECTOR_NEAR(reader.GetSize(), v5(5.0, 5.0, 5.0, 5.0, 5.0), 1e-10);

  if ( SITK_MAX_DIMENSION < 5 )
    {
    EXPECT_ANY_THROW(reader.Execute());
    }
  else
    {
    sitk::Image output;
    EXPECT_NO_THROW(output = reader.Execute());
    EXPECT_VECTOR_DOUBLE_NEAR(output.GetOrigin(), reader.GetOrigin(), 1e-10);
    EXPECT_VECTOR_DOUBLE_NEAR(output.GetSpacing(), reader.GetSpacing(), 1e-10);
    EXPECT_VECTOR_DOUBLE_NEAR(output.GetDirection(), reader.GetDirection(), 1e-8);
    }

  std::vector<unsigned int> extractSize(5);
  std::vector<int> extractIndex(5, 0);

  // extract first 3d region
  extractSize[0]=5u;
  extractSize[1]=5u;
  extractSize[2]=5u;
  extractSize[3]=0u;
  extractSize[4]=0u;

  reader.SetExtractSize(extractSize);
  reader.SetExtractIndex(extractIndex);
  sitk::Image output = reader.Execute();

  EXPECT_EQ(output.GetSize(), std::vector<unsigned int>(3u, 5u));
  EXPECT_VECTOR_DOUBLE_NEAR(output.GetOrigin(), v3(0.0, 0.0, 0.0), 1e-10);
  EXPECT_VECTOR_DOUBLE_NEAR(output.GetSpacing(), v3(1.0, 1.0, 1.0), 1e-10);
  EXPECT_VECTOR_DOUBLE_NEAR(output.GetDirection(), v9(1.0, 0.0, 0.0,
                                                      0.0, 1.0, 0.0,
                                                      0.0, 0.0, 1.0), 1e-8);
  EXPECT_VECTOR_NEAR(output.GetPixelAsVectorFloat32(std::vector< uint32_t >(3u,0u)),
                     v5(0.0, 0.0, 0.0, 0.0, 0.0), 1e-10);
  EXPECT_VECTOR_NEAR(output.GetPixelAsVectorFloat32(std::vector< uint32_t >(3u,4u)),
                            v5(4.0, 4.0, 4.0, 0.0, 0.0), 1e-10);


  // extract  2d region
  extractSize[0]=0u;
  extractSize[1]=3u;
  extractSize[2]=0u;
  extractSize[3]=3u;
  extractSize[4]=0u;

  extractIndex[0]=1;
  extractIndex[1]=1;
  extractIndex[2]=2;
  extractIndex[3]=2;
  extractIndex[4]=4;


  reader.SetExtractSize(extractSize);
  reader.SetExtractIndex(extractIndex);
  output = reader.Execute();

  EXPECT_EQ(output.GetSize(), std::vector<unsigned int>(2u, 3u));
  EXPECT_VECTOR_DOUBLE_NEAR(output.GetOrigin(), v2(1.0, 2.0), 1e-10);
  EXPECT_VECTOR_DOUBLE_NEAR(output.GetSpacing(), v2(1.0, 1.0), 1e-10);
  EXPECT_VECTOR_DOUBLE_NEAR(output.GetDirection(), v4(1.0, 0.0,
                                                      0.0, 1.0), 1e-8);
  EXPECT_VECTOR_NEAR(output.GetPixelAsVectorFloat32(std::vector< uint32_t >(2u,0u)),
                     v5(1.0, 1.0, 2.0, 2.0, 4.0), 1e-10);
  EXPECT_VECTOR_NEAR(output.GetPixelAsVectorFloat32(std::vector< uint32_t >(2u,1u)),
                            v5(1.0, 2.0, 2.0, 3.0, 4.0), 1e-10);


  // Try some error cases
  extractSize =  std::vector<unsigned int>(5u, 1u);
  extractIndex = std::vector<int>(5u, 5u);
  reader.SetExtractSize(extractSize);
  reader.SetExtractIndex(extractIndex);
  EXPECT_ANY_THROW(reader.Execute());

  extractSize[0] = 1u;
  reader.SetExtractSize(extractSize);
  reader.SetExtractIndex(extractIndex);
  EXPECT_ANY_THROW(reader.Execute());

  extractSize[0] = 1u;
  extractSize[1] = 6u;
  reader.SetExtractSize(extractSize);
  reader.SetExtractIndex(extractIndex);
  EXPECT_ANY_THROW(reader.Execute());

  extractSize =  std::vector<unsigned int>(5u, 0u);
  extractSize[0] = 1u;
  extractSize[1] = 1u;
  extractIndex[4] = -1;
  reader.SetExtractSize(extractSize);
  reader.SetExtractIndex(extractIndex);
  EXPECT_ANY_THROW(reader.Execute());

  extractIndex[4] = 5;
  reader.SetExtractSize(extractSize);
  reader.SetExtractIndex(extractIndex);
  EXPECT_ANY_THROW(reader.Execute());
}
