%module SimpleITK

// Remove some warnings
#pragma SWIG nowarn=362,503,401

// Use STL support
%include <std_vector.i>
%include <std_string.i>
%include <std_map.i>

%{
#include "SimpleITK.h"

// This is required because SWIG does not properly add namespaces to typedefs
using namespace itk::simple;
%}

%include "itkSmartPointer.h"
%template(SmartPointerImage) itk::SmartPointer<itk::simple::Image>;

%include "simpleImage.h"
%include "simpleImageFileReader.h"
%include "simpleImageFileWriter.h"
%include "simpleGaussian.h"
%include "simpleImageHash.h"
