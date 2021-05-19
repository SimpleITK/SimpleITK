Setting Up Eclipse and Visual Studio
************************************

.. _setup-java:

Java
====

Java and SimpleITK are a natural fit. Like the bindings of other languages wrapped by SimpleITK, SimpleITK's Java bindings have a language-specific component (traditional Jar file), and a native component (native shared library). This combination requires a little more setup, but is largely transparent to the developer.

Build/Install SimpleITK
-----------------------
For Windows, you have two options:

 - :ref:`Download <installation-binaries>` the binary for SimpleITK
 - :doc:`Build <buildingWindows>` the binary

For any other OS, you must build the binaries yourself.

Set Up Eclipse
---------------
Download `Eclipse <http://www.eclipse.org/>`_ on your platform of choice. Eclipse is a commonly used integrated development environment (IDE) used for Java because it makes development, debugging and deployment streamlined.

Then, create a new project in Eclipse. Choose *File --> New --> Project...*, choosing Java Project in the Eclipse project wizard dialog, and name the project as you like. In this example, our project is called SimpleITK Demo. Create a new class by choosing *File --> New --> Class*, or simply copy the code below and paste into the project item in the Package Explorer view and Eclipse will automatically create the class and hierarchy for you.

GaussianExample
---------------

Here is our first class *Code/GaussianExample.java*:

.. code-block :: Java

	package org.itk.simple.example;

	import org.itk.simple.Image;
	import org.itk.simple.SimpleITK;

	public class GaussianExample {

		/**
		 * @param args
		 */
		public static void main(String[] args) {

			if (args.length < 2) {
				System.err.println("Usage: 'Gaussian <input> <output>'");
				System.exit(1);
			}
			System.out.println("Starting to blur " + args[0]);
			// Grab a file (there will be an error if the image is not scalar)
			Image image = SimpleITK.readImage(args[0]);
			Image output = SimpleITK.discreteGaussian(image);
			SimpleITK.writeImage(output, args[1]);
			System.out.println("Finished blurring, writing to " + args[1]);

		}

	}

If Eclipse is working as expected, you should see errors on lines 16-20. These errors occurs because we have not told Eclipse where to find SimpleITK's jar file.

Add SimpleITK to the Build Path
-------------------------------
Right click on the project in the *Package Explorer* view and choose *Build Path --> Configure Build Path...*

.. figure:: ../images/EclipseConfigureBuildPath.jpg
   :scale: 60%
   :align: center
   :alt: Build Path Option

In the *Properties* dialog, click on *Java Build Path* and *Add External JARs...* then navigate to the SimpleITK jar file. When selected, click the down arrow to expose the options for the jar.

.. figure:: ../images/BuildPathConfiguration.jpg
   :scale: 70%
   :align: center
   :alt: Build Path Configuration

The three options of interest are: *Source attachment*, *Javdoc location* and *Native library location*. The *Source attachment* specifies where the source code for the SimpleITK jar file resides. In our case, it is distributed as *simpleitk-source.x.x.x.jar* where *x.x.x* is the version number of SimpleITK. The source attachment is useful for debugging the SimpleITK library, if necessary, because it allows the debugger to step through classes provided in the SimpleITK jar file. This setting is optional.

The *Javadoc location* is also optional, but extremely helpful in developing with Java. Having Javadoc available provides Eclipse with in-line documentation for each function, if provided. We highly recommend supplying the Javadoc location to Eclipse.

The last option, *Native library location* is required. Because SimpleITK is a C++ library, all functionality is provided through the *JNI (Java Native Interface)* specification. When the SimpleITK classes are loaded, a static block loads the native library to provide all the functionality to Java. This option tells Eclipse where to search for the library; without it a *UnsatisfiedLinkError* is thrown:

::

	Exception in thread "main" java.lang.UnsatisfiedLinkError: no SimpleITKJava in java.library.path
			at java.lang.ClassLoader.loadLibrary(ClassLoader.java:1758)
			at java.lang.Runtime.loadLibrary0(Runtime.java:823)
			at java.lang.System.loadLibrary(System.java:1045)
			at org.itk.simple.SimpleITKJNI.<clinit>(SimpleITKJNI.java:62)
			at org.itk.simple.SimpleITK.readImage(SimpleITK.java:33)
			at org.itk.simple.example.GaussianExample.main(GaussianExample.java:19)

Set the *Native library location* to the directory containing the platform specific JNI library, i.e. *libSimpleITKJava.jnilib* on Mac OSX, *libSimpleITKJava.so* on Linux and *SimpleITKJava.dll* on Windows. After providing the library location, our example code runs correctly. When running this example from the command line, the native library location needs to be specified to the JVM, e.g. :literal:`-Djava.library.path=/path/to/SimpleITKRuntime`.

SimpleITK Java Conventions
--------------------------
The SimpleITK Java bindings closely follow the C++ conventions, i.e. each class contains the public member functions. However, the functional interface is handled differently in Java. In particular, every static Java function must belong to a class, unlike C++. In SimpleITK, the functional interface is contained in a class called *org.itk.simple.SimpleITK*. This class contains the functional interfaces as static member functions, i.e. *org.itk.simple.SimpleITK.readImage* as shown in `GaussianExample`_. The naming conventions for all SimpleITK classes follows the C++ conventions, but member functions and the function interface follow the Java conventions of using *CamelCase* with the first letter lowercase. In Java, the C++ function *itk::simple::ReadImage* becomes *org.itk.simple.SimpleITK.readImage*.


.. _setup-csharp:

C#
==

This guide will show how to set up a C# project in Microsoft Visual Studio 2017 using SimpleITK binaries. The same steps should apply for all other versions of Visual Studio.

Building SimpleITK
------------------
For Windows, you have two options:

 - :ref:`Download <installation-binaries>` the binary for SimpleITK in your Documents
 - :doc:`Build <building>` the binary

 .. figure:: ../images/SimpleITKCSharpUnzip.jpg
   :scale: 45%
   :align: center
   :alt: Unzipped SimpleITK package

For any other OS, you must build the binaries yourself.

Set Up Visual Studio
--------------------
Download `Visual Studio <https://visualstudio.microsoft.com/downloads/>`_ if you don't have it.

Then, create a new project in Visual Studio. Choose *File --> New --> Project...*, then select "Visual C#" and "Console App".

.. figure:: ../images/NewVisualStudioProject.jpg
   :scale: 45%
   :align: center
   :alt: New Visual Studio Project

Select Architecture
-------------------
The SimpleITK binary only supports a single architecture platform. Your project should be configured to match that same platform. By default, in the Toolbar "Debug" is selected for the Solution Configuration and "Any CPU" is selected for the Solution Platform, this needs to be changed.

 - Bring up the "Configuration Manager" dialog from the menu *BUILD->Configuration Manger...*
 - The architecture of the SimpleITK binary needs to be added, and the "Any CPU" architecture needs to be removed. This needs to be done for both the "Active solution platforms" and the "Platform".

 .. figure:: ../images/VisualStudioConfigurationManager.jpg
   :scale: 45%
   :align: center
   :alt: Visual Studio Configuration Manager

Add Managed Library
-------------------
 - From the menu bar select *PROJECT->Add Reference...* to bring up the Reference Manager. Click *Browse...* and navigate the file system to unzip "SimpleITKCSharpManaged.dll" from the binary download, then click OK to add.

 .. figure:: ../images/ManagedLibrary.jpg
   :scale: 45%
   :align: center
   :alt: Add Managed Library

Add Native Library
------------------
 - From the menu bar select *PROJECT->Add Existing Item...* Select "Executable Files" for the extension type. Then navigate the file system to the unzipped "SimpleITKCSharpNative.dll" file from the binary download. **IMPORTANT** in the "Add" button's pull down menu select "Add As Link".
 - In the Solution Explorer right click on the "SimpleITKCSharpNative.dll", and select "Properties".
 - Then for "Build Action", choose "Content", and "Copy to OutputDirectory" choose "Copy always".

.. figure:: ../images/NativeLibraryProperties.jpg
   :scale: 50%
   :align: center
   :alt: Native Library Properties

Building an Example
-------------------
Now that we have configured the project, let up copy a basic SimpleITK example to compile and run. The :doc:`SimpleGaussian in C# <link_SimpleGaussian_docs>` is a simple one to test our configuration. This can just be copied and pasted into the code editor.

Then click *Build -> Build Solution*. Assuming you have followed all of the steps thus far, you should have an executable you can run from the command line or from Visual Studio by adding command line arguments in *Project -> ConsoleApp1 Properties... -> Debug*.

.. figure:: ../images/VisualStudioExample.jpg
   :scale: 60%
   :align: center
   :alt: Visual Studio Example Build
