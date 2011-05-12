%module SimpleITK

// Remove some warnings
#pragma SWIG nowarn=362,503,401,389,516

// Use STL support
%include <std_vector.i>
%include <std_string.i>
%include <std_map.i>

// Use C99 int support
%include <stdint.i>

// Use exceptions
%include "exception.i"

// Include some C# helper files
%include "CSharpTypemapHelper.i"



// Customize exception handling
%exception {
  try {
    $action
  } catch( itk::ExceptionObject &ex ) {
    char error_msg[256];
    sprintf( error_msg, "Exception thrown in SimpleITK $symname: %s", ex.what() );
    SWIG_exception( SWIG_RuntimeError, error_msg );
  } catch( ... ) {
    SWIG_exception( SWIG_UnknownError, "Unknown exception thrown in SimpleITK $symname" );
  }
}

// Global Tweaks to sitk::Image
%ignore itk::simple::Image::GetImageBase( void );
%ignore itk::simple::Image::GetImageBase( void ) const;

// Language Specific Sections
%include CSharp.i
%include Java.i
%include Tcl.i
%include Python.i
%include Lua.i

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
  %template(VectorUIntList) vector< vector<unsigned int> >;
  %template(VectorString) vector< std::string >;
}


// This section is copied verbatim into the generated source code.
// Any include files, definitions, etc. need to go here.
%{
#include <SimpleITK.h>
#include <sitkImageOperators.h>
%}

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
%include "sitkExtractImageFilter.h"
%include "sitkCastImageFilter.h"

// Registration classes
%include "sitkTransform.h"
%include "sitkAffineTransform.h"
%include "sitkInterpolate.h"
%include "sitkLinearInterpolate.h"
%include "sitkMetric.h"
%include "sitkMattesMutualInformationMetric.h"
%include "sitkOptimizer.h"
%include "sitkRegularStepGradientDescentOptimizer.h"
%include "sitkRegistration.h"


// Auto-generated headers
%include "SimpleITKBasicFiltersGeneratedHeaders.i"
