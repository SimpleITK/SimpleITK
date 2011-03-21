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
