%module SimpleITK

// Remove some warnings
#pragma SWIG nowarn=362,503,401

// Use STL support
%include <std_vector.i>
%include <std_string.i>
%include <std_map.i>

// Use exceptions
%include "exception.i"

// Include some C# helper files
%include "CSharpTypemapHelper.i"

%{
#include "SimpleITK.h"

// This is required because SWIG does not properly add namespaces to typedefs
using namespace itk::simple;
%}

// CSharp
#if SWIGCSHARP
//%CSharpTypemapHelper( SimpleImageBase::Pointer, IntPtr )
%CSharpPointerTypemapHelper( itk::simple::SimpleImageBase::Pointer, IntPtr )
//%rename(ToString) toString; // TODO: Fix compilation error

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
#endif

%include "itkSmartPointer.h"
%template(SmartPointerImage) itk::SmartPointer<itk::simple::Image>;

%include "simpleITKMacro.h"
%include "simpleImage.h"
%include "simpleImageFileReader.h"
%include "simpleImageFileWriter.h"
%include "simpleGaussian.h"
%include "simpleImageHash.h"

// Java
#if SWIGJAVA
%pragma(java) jniclasscode=%{
  static {
    try {
        LoadSimpleITK.load();
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library failed to load. \n" + e);
      System.exit(1);
    }
  }
%}
#endif
