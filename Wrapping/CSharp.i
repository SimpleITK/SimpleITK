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
// CSharp wrapping definitions

#if SWIGCSHARP
%include "enumtypesafe.swg" // csharp/enums.swg can not parse the templated code in PixelIDValueEnum
%include "arrays_csharp.i"
%include "std_string.i"
%include "CSharpTypemapHelper.i"

%CSharpPointerTypemapHelper( itk::DataObject*, IntPtr )
%CSharpPointerTypemapHelper( itk::Object::Pointer, IntPtr )
%CSharpPointerTypemapHelper( itk::Optimizer::Pointer, IntPtr )
%CSharpPointerTypemapHelper( itk::SingleValuedCostFunction::Pointer, IntPtr )
%CSharpPointerTypemapHelper( itk::TransformBase::Pointer, IntPtr )

%CSharpTypemapHelper( int8_t*, IntPtr )
%CSharpTypemapHelper( uint8_t*, IntPtr )
%CSharpTypemapHelper( int16_t*, IntPtr )
%CSharpTypemapHelper( uint16_t*, IntPtr )
%CSharpTypemapHelper( int32_t*, IntPtr )
%CSharpTypemapHelper( uint32_t*, IntPtr )
%CSharpTypemapHelper( float*, IntPtr )
%CSharpTypemapHelper( double*, IntPtr )

// Add override to ToString method
%csmethodmodifiers ToString "public override";

// Handle PermuteAxes DefaultOrder
// TODO:
//%apply unsigned int INOUT[] {unsigned int DefaultOrder[3]}

#endif // End of C# specific sections
