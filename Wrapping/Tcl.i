/*=========================================================================
*
*  Copyright Insight Software Consortium
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

#if SWIGTCL
// Code to rebuild tclsh
%include "tclsh.i"
%include "tclinterp.i"

// ignore overload methods of int type when there is an enum
%ignore itk::simple::CastImageFilter::SetOutputPixelType( PixelIDValueType pixelID );
%ignore itk::simple::GetPixelIDValueAsString( PixelIDValueType type );

%extend itk::simple::ProcessObject {
  int AddCommand( itk::simple::EventEnum e, Tcl_Obj *obj, Tcl_Interp *interp )
 {
   std::cout << "AddCommand called with an obj.\n";
   Tcl_GlobalEvalObj(interp, obj);
   return 0;
 }

 }

#endif
