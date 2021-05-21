Reading and Writing for Images and Transforms
*********************************************

.. _image-io:

Images
======

There are numerous file formats support by SimpleITK's image readers and writers.
Support for a particular format is handled by a specific ITK
`ImageIO <https://itk.org/Doxygen/html/classitk_1_1ImageIOBase.html>`_ class.
By default, the ImageIO is automatically determined for a particular file based
on the file name suffix and/or the contents of the file's header.
Advanced SimpleITK installations can configure or extend which file formats
are supported by SimpleITK. A list of registered ImageIO's can be found using the
``GetRegisteredImageIOs()`` method, but is posted here:

    - `BMPImageIO <https://itk.org/Doxygen/html/classitk_1_1BMPImageIO.html>`_ ( \*.bmp, \*.BMP )
    - `BioRadImageIO <https://itk.org/Doxygen/html/classitk_1_1BioRadImageIO.html>`_ ( \*.PIC, \*.pic )
    - `Bruker2dseqImageIO <https://itk.org/Doxygen/html/classitk_1_1Bruker2dseqImageIO.html>`_
    - `GDCMImageIO <https://itk.org/Doxygen/html/classitk_1_1GDCMImageIO.html>`_
    - `GE4ImageIO <https://itk.org/Doxygen/html/classitk_1_1GE4ImageIO.html>`_
    - `GE5ImageIO <https://itk.org/Doxygen/html/classitk_1_1GE5ImageIO.html>`_
    - `GiplImageIO <https://itk.org/Doxygen/html/classitk_1_1GiplImageIO.html>`_ ( \*.gipl \*.gipl.gz)
    - `HDF5ImageIO <https://itk.org/Doxygen/html/classitk_1_1HDF5ImageIO.html>`_
    - `JPEGImageIO <https://itk.org/Doxygen/html/classitk_1_1JPEGImageIO.html>`_ ( \*.jpg, \*.JPG, \*.jpeg, \*.JPEG )
    - `LSMImageIO <https://itk.org/Doxygen/html/classitk_1_1LSMImageIO.html>`_ ( \*.tif, \*.TIF, \*.tiff, \*.TIFF, \*.lsm, \*.LSM )
    - `MINCImageIO <https://itk.org/Doxygen/html/classitk_1_1MINCImageIO.html>`_ ( \*.mnc, \*.MNC )
    - `MRCImageIO <https://itk.org/Doxygen/html/classitk_1_1MRCImageIO.html>`_ ( \*.mrc, \*.rec )
    - `MetaImageIO <https://itk.org/Doxygen/html/classitk_1_1MetaImageIO.html>`_ ( \*.mha, \*.mhd )
    - `NiftiImageIO <https://itk.org/Doxygen/html/classitk_1_1NiftiImageIO.html>`_ ( \*.nia, \*.nii, \*.nii.gz, \*.hdr, \*.img, \*.img.gz )
    - `NrrdImageIO <https://itk.org/Doxygen/html/classitk_1_1NrrdImageIO.html>`_ ( \*.nrrd, \*.nhdr )
    - `PNGImageIO <https://itk.org/Doxygen/html/classitk_1_1PNGImageIO.html>`_ ( \*.png, \*.PNG )
    - `StimulateImageIO <https://itk.org/Doxygen/html/classitk_1_1StimulateImageIO.html>`_
    - `TIFFImageIO <https://itk.org/Doxygen/html/classitk_1_1TIFFImageIO.html>`_ ( \*.tif, \*.TIF, \*.tiff, \*.TIFF )
    - `VTKImageIO <https://itk.org/Doxygen/html/classitk_1_1VTKImageIO.html>`_ ( \*.vtk )


A read and write example using SimpleITK's `ImageFileReader <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageFileReader.html>`_ and `ImageFileWriter <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageFileWriter.html>`_ classes:

.. tabs::
  .. tab:: C#

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.cs
       :language: csharp
       :lines: 31-38

  .. tab:: C++

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.cxx
       :language: cpp
       :lines: 33-41

  .. tab:: Java

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.java
       :language: java
       :lines: 29-36

  .. tab:: Lua

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.lua
       :language: lua
       :lines: 25-34

  .. tab:: Python

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.py
       :language: python
       :lines: 28-37

  .. tab:: R

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.R
       :language: r
       :lines: 29-38

  .. tab:: Ruby

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.rb
       :language: ruby
       :lines: 24-33

  .. tab:: Tcl

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.tcl
       :language: tcl
       :lines: 24-35

The above example specifies using the PNGImageIO to read the file.
If that line is omitted, SimpleITK would determine which IO to use automatically,
based on the file name's suffix and/or the file's header.

A more compact example using SimpleITK's procedural interface:

.. tabs::
  .. tab:: C#

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.cs
       :language: csharp
       :lines: 42-43

  .. tab:: C++

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.cxx
       :language: cpp
       :lines: 47-49

  .. tab:: Java

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.java
       :language: java
       :lines: 40-41

  .. tab:: Lua

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.lua
       :language: lua
       :lines: 38-41

  .. tab:: Python

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.py
       :language: python
       :lines: 44-47

  .. tab:: R

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.R
       :language: r
       :lines: 42-45

  .. tab:: Ruby

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.rb
       :language: ruby
       :lines: 37-40

  .. tab:: Tcl

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.tcl
       :language: tcl
       :lines: 39-43

Similarly, if the imageIO parameter is omitted, SimpleITK will determine
which IO to use automatically.

.. _transformation-io:

Transformations
===============

In SimpleITK, transformation files can be written in several different formats.
Just as there are numerous IOs for images, there are several for transforms,
including TxtTransformIO, MINCTransformIO, HDF5TransformIO, and MatlabTransformIO
(although this list can be extended as well). These support a variety of file
formats, including .txt, .tfm, .xfm, .hdf and .mat.

Because of the size of displacement fields, writing them may require more careful
attention.  To save a displacement field we recommend using one of the binary
transformation file formats (e.g. .hdf, .mat). Saving it in a text based format
results in significantly larger files and longer IO runtimes. Another option is
to save the displacement field found in a DisplacementFieldTransform object as an
image (.nrrd, .nhdr, .mha, .mhd, .nii, .nii.gz).

Here is a simple example of creating a transformation, writing it to a file,
reading it back, and then comparing the results.

.. tabs::
  .. tab:: C#

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.cs
       :language: csharp
       :lines: 47-55

  .. tab:: C++

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.cxx
       :language: python
       :lines: 55-60

  .. tab:: Java

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.java
       :language: java
       :lines: 45-53

  .. tab:: Lua

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.lua
       :language: lua
       :lines: 45-56

  .. tab:: Python

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.py
       :language: python
       :lines: 54-62

  .. tab:: R

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.R
       :language: r
       :lines: 49-57

  .. tab:: Ruby

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.rb
       :language: ruby
       :lines: 44-55

  .. tab:: Tcl

    .. literalinclude:: ../../Examples/SimpleIO/SimpleIO.tcl
       :language: tcl
       :lines: 47-59

``read_result`` returns an object of the generic ``sitk.Transform()`` class and
``basic_transform`` creates a ``sitk.Euler2DTransform()`` object, but both
represent the same transformation. Although this example only uses a single
SimpleITK transformation, a .tfm file can hold a composite (set of
transformations).
