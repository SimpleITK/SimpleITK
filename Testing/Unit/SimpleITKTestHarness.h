#ifndef __SimpleITKTestHarness_h
#define __SimpleITKTestHarness_h

#include <string>

// Class to help us find test data
class DataFinder {
 public:
  DataFinder () { mDirectory = "NotFoundAnywhere"; };
  void setDirectory ( const char* dir ) {
    mDirectory = dir;
  };
  void setDirectory ( std::string dir ) {
    mDirectory = dir;
  };
  void setOutputDirectory ( std::string dir ) {
    mOutputDirectory = dir;
  };
  std::string getDirectory () { return mDirectory; };
  std::string getOutputDirectory () { return mOutputDirectory; };
  std::string getOutputFile ( std::string filename ) { return mOutputDirectory + "/" + filename; };
  std::string getFile ( std::string filename ) {
    return mDirectory + "/" + filename;
  };

  
 protected:
  std::string mDirectory;
  std::string mOutputDirectory;
};

extern DataFinder dataFinder;

#endif
