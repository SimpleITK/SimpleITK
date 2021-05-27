Java Image Buffer
=================

This example demonstrate efficient access to the Image's buffer in SimpleITK with Java. The SimpleITK Image class has the
`java.nio.Buffer Image::getBufferAsBuffer(void) method. The `java.ni.Buffer` class has derived types for Java's signed
integers, float, and double types. These derived buffer type are returned, when the SimpleITK Image's pixel type as
scalar, vector, or complex corresponds. Additionally, the `UInt16` types are returned as a `CharBuffer`, other wise a
`ByteBuffer` is returned. The returned buffer is the Image's buffer and no copy has occurred. However, SimpleITK's copy
on write policies are followed, and `Image::MakeUnique` is called.

Overview
--------


Code
----

.. literalinclude:: ../../Examples/Java/ImageGetSetBuffer.java
   :language: Java
   :lines: 18-
