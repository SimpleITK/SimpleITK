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
// CSharp wrapping definitions

#if SWIGCSHARP
%include "enumtypesafe.swg" // csharp/enums.swg can not parse the templated code in PixelIDValueEnum
%include "arrays_csharp.i"
%include "std_string.i"
%include "CSharpTypemapHelper.i"


// Enable CSharp classes derived from Command Execute method to be
// called from C++
%feature("director") itk::simple::Command;

%CSharpPointerTypemapHelper( itk::DataObject*, System.IntPtr )
%CSharpPointerTypemapHelper( itk::Object::Pointer, System.IntPtr )
%CSharpPointerTypemapHelper( itk::Optimizer::Pointer, System.IntPtr )
%CSharpPointerTypemapHelper( itk::SingleValuedCostFunction::Pointer, System.IntPtr )
%CSharpPointerTypemapHelper( itk::TransformBase::Pointer, System.IntPtr )

%CSharpTypemapHelper( int8_t*, System.IntPtr )
%CSharpTypemapHelper( uint8_t*, System.IntPtr )
%CSharpTypemapHelper( int16_t*, System.IntPtr )
%CSharpTypemapHelper( uint16_t*, System.IntPtr )
%CSharpTypemapHelper( int32_t*, System.IntPtr )
%CSharpTypemapHelper( uint32_t*, System.IntPtr )
%CSharpTypemapHelper( int64_t*, System.IntPtr )
%CSharpTypemapHelper( uint64_t*, System.IntPtr )
%CSharpTypemapHelper( float*, System.IntPtr )
%CSharpTypemapHelper( double*, System.IntPtr )
%CSharpTypemapHelper( void*, System.IntPtr )


// CSharp does not hadle overloaded const methods. So they are
// explicitly renamed to enable their explicit usage. These methods
// assume that the buffer will not be modified, so MakeUnique is
// not call.
%rename("GetConstBufferAsInt8")   itk::simple::Image::GetBufferAsInt8( ) const;
%rename("GetConstBufferAsUInt8")  itk::simple::Image::GetBufferAsUInt8( ) const;
%rename("GetConstBufferAsInt16")  itk::simple::Image::GetBufferAsInt16( ) const;
%rename("GetConstBufferAsUInt16") itk::simple::Image::GetBufferAsUInt16( ) const;
%rename("GetConstBufferAsInt32")  itk::simple::Image::GetBufferAsInt32( ) const;
%rename("GetConstBufferAsUInt32") itk::simple::Image::GetBufferAsUInt32( ) const;
%rename("GetConstBufferAsInt64")  itk::simple::Image::GetBufferAsInt64( ) const;
%rename("GetConstBufferAsUInt64") itk::simple::Image::GetBufferAsUInt64( ) const;
%rename("GetConstBufferAsFloat")  itk::simple::Image::GetBufferAsFloat( ) const;
%rename("GetConstBufferAsDouble") itk::simple::Image::GetBufferAsDouble( ) const;
%rename("GetConstBufferAsVoid") itk::simple::Image::GetBufferAsVoid( ) const;



// Add override to ToString method
%csmethodmodifiers ToString "public override";

// Handle PermuteAxes DefaultOrder
// TODO:
//%apply unsigned int INOUT[] {unsigned int DefaultOrder[3]}

// Extend Image class
%typemap(cscode) itk::simple::Image %{

  #region Unary operators

  ///<summary>Unary negation operator calls SimpleITK.UnaryMinus.</summary>
  public static Image operator -(Image img1) {
    return SimpleITK.UnaryMinus(img1);
  }

  ///<summary>Unary addition operator returns self.</summary>
  public static Image operator +(Image img1) {
    return img1;
  }

  ///<summary>Logical negation operator calls SimpleITK.Not.</summary>
  public static Image operator !(Image img1) {
    return SimpleITK.Not(img1);
  }

  ///<summary>Bitwise complement operator calls SimpleITK.BitwiseNot.</summary>
  public static Image operator ~(Image img1) {
    return SimpleITK.BitwiseNot(img1);
  }

  ///<summary>True operator provided to keep compiler happy. Always returns true.</summary>
  public static bool operator true(Image img1) {
    return true;
  }

  ///<summary>False operator provided to keep compiler happy. Always returns false.</summary>
  public static bool operator false(Image img1) {
    return false;
  }

  #endregion

  #region Binary mathematical operators

  ///<summary>Binary addition operator calls SimpleITK.Add.</summary>
  public static Image operator +(Image img1, Image img2) {
    return SimpleITK.Add(img1, img2);
  }

  ///<summary>Binary addition operator calls SimpleITK.Add.</summary>
  public static Image operator +(Image img1, double constant) {
    return SimpleITK.Add(img1, constant);
  }

  ///<summary>Binary addition operator calls SimpleITK.Add.</summary>
  public static Image operator +(double constant, Image img1) {
    return SimpleITK.Add(constant, img1);
  }

  ///<summary>Binary subtraction operator calls SimpleITK.Subtract.</summary>
  public static Image operator -(Image img1, Image img2) {
    return SimpleITK.Subtract(img1, img2);
  }

  ///<summary>Binary subtraction operator calls SimpleITK.Subtract.</summary>
  public static Image operator -(Image img1, double constant) {
    return SimpleITK.Subtract(img1, constant);
  }

  ///<summary>Binary subtraction operator calls SimpleITK.Subtract.</summary>
  public static Image operator -(double constant, Image img1) {
    return SimpleITK.Subtract(constant, img1);
  }

  ///<summary>Binary multiply operator calls SimpleITK.Multiply.</summary>
  public static Image operator *(Image img1, Image img2) {
    return SimpleITK.Multiply(img1, img2);
  }

  ///<summary>Binary multiply operator calls SimpleITK.Multiply.</summary>
  public static Image operator *(Image img1, double constant) {
    return SimpleITK.Multiply(img1, constant);
  }

  ///<summary>Binary multiply operator calls SimpleITK.Multiply.</summary>
  public static Image operator *(double constant, Image img1) {
    return SimpleITK.Multiply(constant, img1);
  }

  ///<summary>Binary division operator calls SimpleITK.Divide.</summary>
  public static Image operator /(Image img1, Image img2) {
    return SimpleITK.Divide(img1, img2);
  }

  ///<summary>Binary division operator calls SimpleITK.Divide.</summary>
  public static Image operator /(Image img1, double constant) {
    return SimpleITK.Divide(img1, constant);
  }

  ///<summary>Binary division operator calls SimpleITK.Divide.</summary>
  public static Image operator /(double constant, Image img1) {
    return SimpleITK.Divide(constant, img1);
  }

  #endregion

  #region Binary bitwise operators

  ///<summary>Binary bitwise AND operator calls SimpleITK.And.</summary>
  public static Image operator &(Image img1, Image img2) {
    return SimpleITK.And(img1, img2);
  }

  ///<summary>Binary bitwise AND operator calls SimpleITK.And.</summary>
  public static Image operator &(Image img1, int constant) {
    return SimpleITK.And(img1, constant);
  }

  ///<summary>Binary bitwise AND operator calls SimpleITK.And.</summary>
  public static Image operator &(int constant, Image img1) {
    return SimpleITK.And(constant, img1);
  }

  ///<summary>Binary bitwise OR operator calls SimpleITK.Or.</summary>
  public static Image operator |(Image img1, Image img2) {
    return SimpleITK.Or(img1, img2);
  }

  ///<summary>Binary bitwise OR operator calls SimpleITK.Or.</summary>
  public static Image operator |(Image img1, int constant) {
    return SimpleITK.Or(img1, constant);
  }

  ///<summary>Binary bitwise OR operator calls SimpleITK.Or.</summary>
  public static Image operator |(int constant,Image img1) {
    return SimpleITK.Or(constant, img1);
  }

  ///<summary>Binary bitwise XOR operator calls SimpleITK.Xor.</summary>
  public static Image operator ^(Image img1, Image img2) {
    return SimpleITK.Xor(img1, img2);
  }

  ///<summary>Binary bitwise XOR operator calls SimpleITK.Xor.</summary>
  public static Image operator ^(Image img1, int constant) {
    return SimpleITK.Xor(img1, constant);
  }

  ///<summary>Binary bitwise XOR operator calls SimpleITK.Xor.</summary>
  public static Image operator ^(int constant, Image img1) {
    return SimpleITK.Xor(constant, img1);
  }

  #endregion

  #region Comparison operators

  ///<summary>Less than operator calls SimpleITK.Less.</summary>
  public static Image operator <(Image img1, Image img2) {
    return SimpleITK.Less(img1, img2);
  }

  ///<summary>Less than operator calls SimpleITK.Less.</summary>
  public static Image operator <(Image img1, double constant) {
    return SimpleITK.Less(img1, constant);
  }

  ///<summary>Less than operator calls SimpleITK.Less.</summary>
  public static Image operator <(double constant, Image img1) {
    return SimpleITK.Less(constant, img1);
  }

  ///<summary>Greater than operator calls SimpleITK.Greater.</summary>
  public static Image operator >(Image img1, Image img2) {
    return SimpleITK.Greater(img1, img2);
  }

  ///<summary>Greater than operator calls SimpleITK.Greater.</summary>
  public static Image operator >(Image img1, double constant) {
    return SimpleITK.Greater(img1, constant);
  }

  ///<summary>Greater than operator calls SimpleITK.Greater.</summary>
  public static Image operator >(double constant, Image img1) {
    return SimpleITK.Greater(constant, img1);
  }

  ///<summary>Less than or equal to operator calls SimpleITK.LessEqual.</summary>
  public static Image operator <=(Image img1, Image img2) {
    return SimpleITK.LessEqual(img1, img2);
  }

  ///<summary>Less than or equal to operator calls SimpleITK.LessEqual.</summary>
  public static Image operator <=(Image img1, double constant) {
    return SimpleITK.LessEqual(img1, constant);
  }

  ///<summary>Less than or equal to operator calls SimpleITK.LessEqual.</summary>
  public static Image operator <=(double constant,Image img1) {
    return SimpleITK.LessEqual(constant, img1);
  }

  ///<summary>Greater than or equal to operator calls SimpleITK.GreaterEqual.</summary>
  public static Image operator >=(Image img1, Image img2) {
    return SimpleITK.GreaterEqual(img1, img2);
  }

  ///<summary>Greater than or equal to operator calls SimpleITK.GreaterEqual.</summary>
  public static Image operator >=(Image img1, double constant) {
    return SimpleITK.GreaterEqual(img1, constant);
  }

  ///<summary>Greater than or equal to operator calls SimpleITK.GreaterEqual.</summary>
  public static Image operator >=(double constant, Image img1) {
    return SimpleITK.GreaterEqual(constant, img1);
  }

  #endregion

%}

#endif // End of C# specific sections
