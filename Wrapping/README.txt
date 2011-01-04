
This README provides brief instructions on how to use SimpleITK from each of
the wrapped languages


== Java ==

- SimpleITK java applications must have access to the org.itk.simple package
- There are two methods for accessing the org.itk.simple package
  - 1) After building SimpleITK, run "make install"
    - This target will install the org.itk.simple.jar file into the extensions
      directory of the local jvm
    - This will often require admin permissions since the jvm typically lives
      in a write protected directory
    - Once installed as an extension, all java applications will have access 
      to the package
  - 2) Add org.itk.simple.jar to the java classpath when compiling
    - Note that this is the same as adding the directory containing
      org.itk.simple.java to the classpath
    - The simplest way to do this is to copy org.itk.simple.jar from
      $SIMPLE_ITK_BUILD_DIR/Wrapping to the directory containing the target
      application

======================
$ cp $SIMPLE_ITK_BUILD_DIR/Wrapping/org.itk.simple.jar .
$ javac -classpath ./org.itk.simple.jar MySimpleITKJavaApplication.java
======================

- Once the org.itk.simple package has been properly set up, classes must be
  imported in the java code
- This can be done either by importing the entire package or by importing 
  individual classes

======================
// Import the entire package at once
import org.itk.simple.*

// Import individual classes
import org.itk.simple.ImageFileReader;
import org.itk.simple.RecursiveGaussianImageFilter;
import org.itk.simple.ImageFileWriter;
import org.itk.simple.SmartPointerImage;
======================

