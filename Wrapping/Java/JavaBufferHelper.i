/*
 * void * typemap for returning ByteBuffer from Image::GetBufferAsVoid
 */
%typemap(jni) void * "jobject"
%typemap(jtype) void * "java.nio.ByteBuffer"
%typemap(jstype) void * "java.nio.ByteBuffer"
%typemap(javaout) void * {
  return $jnicall;
}
%typemap(out) void * {
  const size_t size = arg1->GetNumberOfPixels()*arg1->GetNumberOfComponentsPerPixel()*arg1->GetSizeOfPixelComponent();
  $result = JCALL2(NewDirectByteBuffer, jenv, $1, size);
 }
