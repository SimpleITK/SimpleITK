%module SimpleITK

// Remove some warnings
#pragma SWIG nowarn=362,503,401,389,516,511

// Use STL support
%include <std_vector.i>
%include <std_string.i>
%include <std_map.i>

// Use C99 int support
%include <stdint.i>

// Use exceptions
%include "exception.i"

// Customize exception handling
%exception {
  try {
    $action
  } catch( std::exception &ex ) {
    char error_msg[1024];
// TODO this should be replaces with some try compile stuff

%#ifdef _MSC_VER
    _snprintf_s( error_msg, 1024, 1024, "Exception thrown in SimpleITK $symname: %s", ex.what() );
%#else
    snprintf( error_msg, 1024, "Exception thrown in SimpleITK $symname: %s", ex.what() );
%#endif

    SWIG_exception( SWIG_RuntimeError, error_msg );
  } catch( ... ) {
    SWIG_exception( SWIG_UnknownError, "Unknown exception thrown in SimpleITK $symname" );
  }
}

// Global Tweaks to sitk::Image
%ignore itk::simple::Image::GetITKBase( void );
%ignore itk::simple::Image::GetITKBase( void ) const;


// This section is copied verbatim into the generated source code.
// Any include files, definitions, etc. need to go here.
%{
#include <SimpleITK.h>
#include <sitkImageOperators.h>
%}

// Language Specific Sections
%include CSharp.i
%include Java.i
%include Tcl.i
%include Python.i
%include Lua.i
%include R.i

// Help SWIG handle std vectors
namespace std
{
  %template(VectorBool) vector<bool>;
  %template(VectorUInt8) vector<uint8_t>;
  %template(VectorInt8) vector<int8_t>;
  %template(VectorUInt16) vector<uint16_t>;
  %template(VectorInt16) vector<int16_t>;
  %template(VectorUInt32) vector<uint32_t>;
  %template(VectorInt32) vector<int32_t>;
  %template(VectorUInt64) vector<uint64_t>;
  %template(VectorInt64) vector<int64_t>;
  %template(VectorFloat) vector<float>;
  %template(VectorDouble) vector<double>;
  %template(VectorOfImage) vector< itk::simple::Image >;
  %template(VectorUIntList) vector< vector<unsigned int> >;
  %template(VectorString) vector< std::string >;

  // Support for LabelStatisticsImageFilter/MeasurementMap
  %template(BasicMeasurementMap) map<std::string, double>;
}



// Any new classes need to have an "%include" statement to be wrapped.
%include "sitkPixelIDValues.h"
%include "sitkImage.h"
%include "sitkShow.h"
%include "sitkImageFilter.h"
%include "sitkImageFileWriter.h"
%include "sitkImageSeriesReader.h"
%include "sitkImageFileReader.h"
%include "sitkHashImageFilter.h"
%include "sitkStatisticsImageFilter.h"
%include "sitkJoinSeriesImageFilter.h"
%include "sitkMeasurementMap.h"
%include "sitkLabelStatisticsImageFilter.h"

%include "sitkCastImageFilter.h"
%include "sitkVersion.h"

// Registration classes

// Auto-generated headers
%include "SimpleITKBasicFiltersGeneratedHeaders.i"
