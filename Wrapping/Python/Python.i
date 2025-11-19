/*=========================================================================
*
*  Copyright NumFOCUS
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/
#if SWIGPYTHON

%begin %{
#include "sitkPython.h"
// Needed by SWIG, but not in Stable Python API.
// https://github.com/swig/swig/pull/2856
#define NOMINMAX
#include "stdlib.h"
#include "sitkImageBuffer.h"
%}

%{
#include "sitkPyCommand.h"
%}

%init %{
    // Initialize the ImageBuffer type when the module loads
    if (InitImageBufferType(m) < 0) {
#if PY_VERSION_HEX >= 0x03000000
        return NULL;
#else
        return;
#endif
    }
%}

%include "PythonDocstrings.i"
%include "sitkPathType.i"
 //%feature("autodoc", "1");

// ignore overload methods of int type when there is an enum
%ignore itk::simple::CastImageFilter::SetOutputPixelType( PixelIDValueType pixelID );
%ignore itk::simple::GetPixelIDValueAsString( PixelIDValueType type );

%ignore itk::simple::Resample;
%ignore itk::simple::ReadImage;
%ignore itk::simple::WriteImage;
%ignore itk::simple::SmoothinRecursiveGaussian;
%ignore itk::simple::DiscreteGaussian;


// Make __str__ transparent by renaming ToString to __str__
%rename(__str__) ToString;

%include sitkImage.i
%include sitkTransform.i

// This is included inline because SwigMethods (SimpleITKPYTHON_wrap.cxx)
// is declared static.
%{
#include "sitkNumpyArrayConversion.cxx"

// Helper function to extract sitk::Image* from a SWIG-wrapped PyObject
// This function is used by sitkImageBuffer.cxx
itk::simple::Image* sitk_GetImagePointerFromPyObject(PyObject* pyImage)
{
    if (!pyImage) {
        return nullptr;
    }

    void* voidImage;
    int res = SWIG_ConvertPtr(pyImage, &voidImage, SWIGTYPE_p_itk__simple__Image, 0);
    if (!SWIG_IsOK(res)) {
        return nullptr;
    }

    return reinterpret_cast<itk::simple::Image*>(voidImage);
}

%}
// Numpy array conversion support
%native(_GetMemoryViewFromImage) PyObject *sitk_GetMemoryViewFromImage( PyObject *self, PyObject *args );
%native(_SetImageFromArray) PyObject *sitk_SetImageFromArray( PyObject *self, PyObject *args );

// Enable Python classes derived from Command Execute method to be
// called from C++
%feature("director") itk::simple::Command;

%extend itk::simple::ProcessObject {
 int AddCommand( itk::simple::EventEnum e, PyObject *obj )
 {
   if (!PyCallable_Check(obj))
     {
     return 0;
     }
   itk::simple::PyCommand *cmd = NULL;
   try
     {
       cmd = new itk::simple::PyCommand();
       cmd->SetCallbackPyCallable(obj);
       int ret = self->AddCommand(e,*cmd);
       cmd->OwnedByObjectsOn();
       return ret;
     }
   catch(...)
     {
       delete cmd;
       throw;
     }
 }
};

%feature("director") itk::simple::LoggerBase;



%pythonappend itk::simple::ImageRegistrationMethod::Execute(const Image &, const Image &)
{
  val = val.Downcast()
};

%pythonappend itk::simple::LandmarkBasedTransformInitializerFilter::Execute(const Transform &)
{
  val = val.Downcast()
};

%pythonappend itk::simple::LandmarkBasedTransformInitializer
{
  val = val.Downcast()
};

%pythonappend itk::simple::CenteredTransformInitializerFilter::Execute
{
  val = val.Downcast()
};

%pythonappend itk::simple::CenteredTransformInitializer
{
  val = val.Downcast()
};

#endif
