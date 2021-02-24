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
%}

%{
#include "sitkPyCommand.h"
%}

%include "PythonDocstrings.i"
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

#endif
