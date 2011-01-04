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
%newobject *::Execute;

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
%pragma(java) jniclasscode=%{
  static {
    System.loadLibrary ( "SimpleITKJava" );
  }
%}
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
%include "sitkIndex.h"
%include "sitkSize.h"

// Auto-generated headers
%include "SimpleITKBasicFiltersGeneratedHeaders.i"
