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

#if SWIGPYTHON
// Make __str__ transparent by renaming ToString to __str__
%rename(__str__) ToString;
#endif

#if SWIGLUA
#endif


// These definitions help SWIG to properly wrap smart pointers.
%include "itkSmartPointer.h"
%template(SmartPointerImage) itk::SmartPointer<itk::simple::Image>;
%template(SmartPointerPixelContainer) itk::SmartPointer<itk::simple::PixelContainer>;

// Help SWIG handle std vectors
%include "std_vector.i"
namespace std
{
  %template(VectorUInt) vector<unsigned int>;
  %template(VectorUIntList) vector< vector<unsigned int> >;
}

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
%include "sitkRecursiveGaussianImageFilter.h"
%include "sitkExtractImageFilter.h"
%include "sitkCastImageFilter.h"
%include "sitkPixelContainer.h"

// Auto-generated headers
%include "SimpleITKBasicFiltersGeneratedHeaders.i"

// Constructors for Image must be overridden to return SmartPointers
// Step 1: rename the Image constructor
%rename(Image) InternalConstructImage;

// Step 2: for each defined constructor, create a new version of InternalConstructImage
// Step 3: make sure to UnRegister the smart pointer before returnning (o.t.w. it will have a ref count of 2)
%inline %{
itk::simple::Image::Pointer InternalConstructImage( uint64_t Width, uint64_t Height, itk::simple::PixelIDValueEnum ValueEnum ) {
  itk::simple::Image::Pointer p = new itk::simple::Image (Width,Height,ValueEnum);
  p->UnRegister();
  return p;
};
itk::simple::Image::Pointer InternalConstructImage( uint64_t Width, uint64_t Height, uint64_t Depth, itk::simple::PixelIDValueEnum ValueEnum ) {
  itk::simple::Image::Pointer p = new itk::simple::Image( Width, Height, Depth, ValueEnum );
  p->UnRegister();
  return p;
};
%}


%inline %{
struct ShortImageAdapter {
       short* data;
       bool isValid;
       };
%};
// Extend the image class
%extend ShortImageAdapter {
        short getItem ( size_t idx ) { if ( self->isValid ) { return self->data[idx]; } else { return 0; } }
        ShortImageAdapter ( itk::simple::Image::Pointer image ) {
          ShortImageAdapter *a = new ShortImageAdapter();
          a->isValid = false; a->data = NULL;
          if ( image->GetPixelIDValue() == itk::simple::sitkInt16 ) {
            a->isValid = true;
            a->data = (short*)image->GetPixelContainer()->GetBufferAsInt16();
          }
          return a;
       }
};


