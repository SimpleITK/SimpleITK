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

// Add override to ToString method
%csmethodmodifiers ToString "public override";

// Handle PermuteAxes DefaultOrder
// TODO:
//%apply unsigned int INOUT[] {unsigned int DefaultOrder[3]}

#endif  // End of C# specific sections
