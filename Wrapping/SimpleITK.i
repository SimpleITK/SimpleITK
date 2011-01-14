%module SimpleITK

// Remove some warnings
#pragma SWIG nowarn=362,503,401,389,516

// Use STL support
%include <std_vector.i>
%include <std_string.i>
%include <std_map.i>

// Use exceptions
%include "exception.i"

// Tell SWIG that any time Execute is called, this creates a new SWIG-owned object
// %newobject *::Execute;

// Include some C# helper files
%include "CSharpTypemapHelper.i"


// This section is copied verbatim into the generated source code.
// Any include files, definitions, etc. need to go here.
%{
#include <SimpleITK.h>

// This is required because SWIG does not properly add namespaces to typedefs
using namespace itk::simple;
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

// CSharp
#if SWIGCSHARP
//%CSharpTypemapHelper( SimpleImageBase::Pointer, IntPtr )
%CSharpPointerTypemapHelper( itk::simple::SimpleImageBase::Pointer, IntPtr )
//%rename(ToString) toString; // TODO: Fix compilation error
#endif  // End of C# specific sections

// Java
#if SWIGJAVA
%include "carrays.i"
%array_class(int8_t, int8Array);
%array_class(uint8_t, uint8Array);
%array_class(int16_t, int16Array);
%array_class(uint16_t, uint16Array);
%array_class(int32_t, int32Array);
%array_class(uint32_t, uint32Array);
%array_class(float, floatArray);
%array_class(double, doubleArray);
%pragma(java) jniclasscode=%{
  static {
    System.loadLibrary ( "SimpleITKJava" );
  }
%}

// Make Java method names follow the naming conventions
// See the swig.swg file, and ruby.swg for details on how this works
// Documented in: http://www.swig.org/Doc2.0/SWIG.html#SWIG_advanced_renaming
%rename("%(firstlowercase)s", %$isfunction ) "";

#endif // End of Java specific sections

#if SWIGTCL
// Code to rebuild tclsh
%include "tclsh.i"
#endif

// These definitions help SWIG to properly wrap smart pointers.
%include "itkSmartPointer.h"
%template(SmartPointerImage) itk::SmartPointer<itk::simple::Image>;

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
%include "sitkImageHashFilter.h"
%include "sitkStatisticsImageFilter.h"
%include "sitkRecursiveGaussianImageFilter.h"
%include "sitkExtractImageFilter.h"
%include "sitkCastImageFilter.h"
%include "sitkIndex.h"
%include "sitkSize.h"

// Auto-generated headers
%include "SimpleITKBasicFiltersGeneratedHeaders.i"
