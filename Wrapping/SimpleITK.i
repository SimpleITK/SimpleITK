%module SimpleITK

// Remove some warnings
#pragma SWIG nowarn=362,503,401,389,516

// Use STL support
%include <std_vector.i>
%include <std_string.i>
%include <std_map.i>

// Use exceptions
%include "exception.i"

// Include some C# helper files
%include "CSharpTypemapHelper.i"

// This section is copied verbatim into the generated source code.
// Any include files, definitions, etc. need to go here.
%{
#include <SimpleITK.h>
#include <sitkImageOperators.h>
%}


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

// Language Specific Sections
%include CSharp.i
%include Java.i
%include Tcl.i
%include Python.i
%include Lua.i

// Help SWIG handle std vectors
%include "std_vector.i"
namespace std
{
  %template(VectorUInt) vector<unsigned int>;
  %template(VectorInt) vector<int>;
  %template(VectorUShort) vector<unsigned short>;
  %template(VectorShort) vector<short>;
  %template(VectorULong) vector<unsigned long>;
  %template(VectorLong) vector<long>;
  %template(VectorFloat) vector<float>;
  %template(VectorDouble) vector<double>;
  %template(VectorUIntList) vector< vector<unsigned int> >;
}

// ignore the ITK Integrate interface when wrapping
%ignore itk::simple::Image::GetImageBase;

// This helps SWIG wrap long long, as returned by Width, Height, and Depth
typedef unsigned long long uint64_t;

// Help swig wrap 32 bit integers
typedef unsigned int uint32_t;

// Any new classes need to have an "%include" statement to be wrapped.
%include "sitkPixelIDValues.h"
%include "sitkImage.h"
%include "sitkImageFilter.h"
%include "sitkImageFileWriter.h"
%include "sitkImageFileReader.h"
%include "sitkHashImageFilter.h"
%include "sitkStatisticsImageFilter.h"
%include "sitkExtractImageFilter.h"
%include "sitkCastImageFilter.h"
%include "sitkPixelContainer.h"

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