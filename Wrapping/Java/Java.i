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
// Java
#if SWIGJAVA

%pragma(java) jniclasscode=%{
  static {
    System.loadLibrary ( "SimpleITKJava" );
  }
%}

%include "JavaDoc.i"

// Make Java method names follow the naming conventions
// See the swig.swg file, and ruby.swg for details on how this works
// Documented in: http://www.swig.org/Doc2.0/SWIG.html#SWIG_advanced_renaming
%rename("%(firstlowercase)s", %$isfunction ) "";

//
// void * typemap for returning ByteBuffer from Image::GetBufferAsVoid
//
%typemap(jni) void * itk::simple::Image::GetBufferAsVoid() "jobject"
%typemap(jtype) void * itk::simple::Image::GetBufferAsVoid() "java.nio.ByteBuffer"
%typemap(jstype) void * itk::simple::Image::GetBufferAsVoid() "java.nio.ByteBuffer"
%typemap(javaout) void * itk::simple::Image::GetBufferAsVoid() {
  return $jnicall;
}
%typemap(out) void * itk::simple::Image::GetBufferAsVoid() {
  const size_t size = arg1->GetNumberOfPixels()*arg1->GetNumberOfComponentsPerPixel()*arg1->GetSizeOfPixelComponent();
  $result = JCALL2(NewDirectByteBuffer, jenv, $1, size);
}

%ignore itk::simple::Image::GetBufferAsInt8();
%ignore itk::simple::Image::GetBufferAsUInt8();
%ignore itk::simple::Image::GetBufferAsInt16();
%ignore itk::simple::Image::GetBufferAsUInt16();
%ignore itk::simple::Image::GetBufferAsInt32();
%ignore itk::simple::Image::GetBufferAsUInt32();
%ignore itk::simple::Image::GetBufferAsInt64();
%ignore itk::simple::Image::GetBufferAsUInt64();
%ignore itk::simple::Image::GetBufferAsFloat();
%ignore itk::simple::Image::GetBufferAsDouble();

%ignore itk::simple::Image::GetBufferAsVoid( ) const;



%rename( getBufferAsByteBuffer ) itk::simple::Image::GetBufferAsVoid;


%extend itk::simple::Image {
  long long GetBufferAsNativePointer() { return reinterpret_cast<long long>(self->GetBufferAsVoid()); }
}

%typemap(javacode) itk::simple::Image %{
  /** Return a Buffer object for the Image's buffer.
   *
   * If the image's pixel component type is available in Java, then the return object
   * is the appropriate derived object from the Buffer class.
   */
  public java.nio.Buffer getBufferAsBuffer()
    {
      java.nio.ByteBuffer b = getBufferAsByteBuffer();
      if (getPixelID() == PixelIDValueEnum.sitkInt16 ||
          getPixelID() == PixelIDValueEnum.sitkVectorInt16)
        {
          return b.asShortBuffer();
        }
      if (getPixelID() == PixelIDValueEnum.sitkUInt16 ||
          getPixelID() == PixelIDValueEnum.sitkVectorUInt16)
        {
          return b.asCharBuffer();
        }
      if (getPixelID() == PixelIDValueEnum.sitkInt32 ||
          getPixelID() == PixelIDValueEnum.sitkVectorInt32)
        {
          return b.asIntBuffer();
        }
      if (getPixelID() == PixelIDValueEnum.sitkFloat32 ||
          getPixelID() == PixelIDValueEnum.sitkComplexFloat32 ||
          getPixelID() == PixelIDValueEnum.sitkVectorFloat32)
        {
          return b.asFloatBuffer();
        }
      if (getPixelID() == PixelIDValueEnum.sitkFloat64 ||
          getPixelID() == PixelIDValueEnum.sitkComplexFloat64 ||
          getPixelID() == PixelIDValueEnum.sitkVectorFloat64)
        {
          return b.asDoubleBuffer();
        }
       // sitkInt8 and sitkVectorInt8 are returned as ByteBuffer too.
       return b;
    }
%}


// Enable Java classes derived from Command Execute method to be
// called from C++
%feature("director") itk::simple::Command;


#endif // End of Java specific sections
