#include "SimpleITKTestHarness.h"

#include <SimpleITK.h>

#if defined(WRAP_LUA)
TEST_F(Lua,SimpleGaussian) {
  // Run the simple gaussian command line program
  std::string Script = dataFinder.GetSourceDirectory() + "/Examples/SimpleGaussian.lua";
  std::string output = dataFinder.GetOutputFile ( "Lua.SimpleGaussian.nrrd" );
  std::vector<std::string> CommandLine;

  CommandLine.push_back ( dataFinder.GetLuaExecutable() );
  CommandLine.push_back ( Script );
  CommandLine.push_back ( dataFinder.GetFile ( "Input/RA-Short.nrrd" ).c_str() );
  CommandLine.push_back ( "2.0" );
  CommandLine.push_back ( output );

  // Run it!
  RunExecutable ( CommandLine, true );

  this->CheckImageHash( output, "02ce020f462cf05f3c354bc33a7834603d65b906" );

}
#endif
