#include "SimpleITKTestHarness.h"

#include <SimpleITK.h>

#if defined(WRAP_JAVA)
TEST_F(Java,SimpleGaussian) {

  const std::string Script = dataFinder.GetSourceDirectory() + "/Examples/SimpleGaussian.java";

  std::string Classpath = dataFinder.GetBuildDirectory() + "/Wrapping/org.itk.simple.jar";
  const std::string JavaPath = dataFinder.GetExecutableDirectory();

  const std::string Class = "SimpleGaussian";

  // compile java program
  {
  std::vector<std::string> CommandLine;
  CommandLine.push_back ( JAVAC_EXECUTABLE_PATH );
  CommandLine.push_back ( "-classpath" );
  CommandLine.push_back ( Classpath );
  CommandLine.push_back ( "-d" );
  CommandLine.push_back ( dataFinder.GetBuildDirectory() + "/Examples" );
  CommandLine.push_back ( Script );

  RunExecutable ( CommandLine, true );
  }

  // add the new class path too
  Classpath += dataFinder.GetPathSeparator() + dataFinder.GetBuildDirectory() + "/Examples";

  // Run the simple gaussian command line program
  std::vector<std::string> CommandLine;

  std::string output = dataFinder.GetOutputFile ( "Java-SimpleGaussian.nrrd" );
  // Make sure the output is wiped
  EXPECT_NO_THROW ( itk::simple::WriteImage( itk::simple::Image ( 1,1,1,itk::simple::sitkUInt8 ), output ) ) << "Failed to overwrite";

  CommandLine.push_back ( dataFinder.GetJavaExecutable() );
  CommandLine.push_back ( "-classpath" );
  CommandLine.push_back ( Classpath );
  CommandLine.push_back ( "-Djava.library.path=" + JavaPath );
  CommandLine.push_back ( Class );
  CommandLine.push_back ( dataFinder.GetFile ( "Input/RA-Short.nrrd" ).c_str() );
  CommandLine.push_back ( "2.0" );
  CommandLine.push_back ( output );


  // Run it!
  RunExecutable ( CommandLine, true );

  this->CheckImageHash( output, "02ce020f462cf05f3c354bc33a7834603d65b906" );

}


TEST_F(Java,ImageConnection) {

  const std::string Script = dataFinder.GetSourceDirectory() + "/Examples/ImageConnection.java";

  std::string Classpath = dataFinder.GetBuildDirectory() + "/Wrapping/org.itk.simple.jar";
  const std::string JavaPath = dataFinder.GetExecutableDirectory();

  const std::string Class = "SimpleGaussian";

  // compile java program
  {
  std::vector<std::string> CommandLine;
  CommandLine.push_back ( JAVAC_EXECUTABLE_PATH );
  CommandLine.push_back ( "-classpath" );
  CommandLine.push_back ( Classpath );
  CommandLine.push_back ( "-d" );
  CommandLine.push_back ( dataFinder.GetBuildDirectory() + "/Examples" );
  CommandLine.push_back ( Script );

  RunExecutable ( CommandLine, true );
  }

  // add the new class path too
  Classpath += dataFinder.GetPathSeparator() + dataFinder.GetBuildDirectory() + "/Examples";

  // Run the simple gaussian command line program
  std::vector<std::string> CommandLine;
  CommandLine.push_back ( dataFinder.GetJavaExecutable() );
  CommandLine.push_back ( "-classpath" );
  CommandLine.push_back ( Classpath );
  CommandLine.push_back ( "-Djava.library.path=" + JavaPath );
  CommandLine.push_back ( Class );


  // Run it!
  RunExecutable ( CommandLine, true );


}

#endif
