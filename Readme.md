SimpleITK
=========

|  | CircleCI | ReadTheDocs |
|:-------:|:---------:|:-------------:|
| release | [![CircleCI](https://circleci.com/gh/SimpleITK/SimpleITK/tree/release.svg?style=shield)](https://circleci.com/gh/SimpleITK/SimpleITK/tree/release) | [![ReadTheDoc](https://readthedocs.org/projects/simpleitk/badge/?version=release)](http://simpleitk.readthedocs.io/en/release/) |
| master | [![CircleCI](https://circleci.com/gh/SimpleITK/SimpleITK/tree/master.svg?style=shield)](https://circleci.com/gh/SimpleITK/SimpleITK/tree/master) | [![ReadTheDoc](https://readthedocs.org/projects/simpleitk/badge/?version=master)](http://simpleitk.readthedocs.io/en/master/) |
| next | [![CircleCI](https://circleci.com/gh/SimpleITK/SimpleITK/tree/next.svg?style=shield)](https://circleci.com/gh/SimpleITK/SimpleITK/tree/next) | [![ReadTheDoc](https://readthedocs.org/projects/simpleitk/badge/?version=next)](http://simpleitk.readthedocs.io/en/next/)  |


SimpleITK is an image analysis toolkit with a large number of components supporting general filtering operations, image segmentation and registration. It is built on top of the Insight Segmentation and Registration Toolkit [ITK](https://www.itk.org) with the intent of providing a simplified interface to ITK. SimpleITK itself is written in C++ but is available for a large number of programming languages. Currently these include:

* [Python](http://www.python.org)
* [R](https://www.r-project.org)
* [Java](http://www.java.com)
* [C#](http://msdn.microsoft.com/en-us/vcsharp/default.aspx)
* [Lua](http://www.lua.org)
* [TCL](https://www.tcl.tk/)
* [Ruby](https://www.ruby-lang.org/en/)


Wrapping of the C++ code is accomplished through [SWIG](http://www.swig.org), in principle, any language wrapped by SWIG should be applicable to SimpleITK.

Unlike ITK's support of n-dimensional spatio-temporal images, SimpleITK supports 2D, 3D and optionally 3D+time. The dimensionality refers to spatio-temporal dimensions, the voxels can be n-dimensional vectors.

SimpleITK is licensed under the [Apache License](http://www.opensource.org/licenses/apache2.0.php) in the [same way as ITK](https://www.itk.org/Wiki/ITK_Release_4/Licensing).

How to Cite
--------

If you found SimpleITK useful in your research, support our efforts by citing
the relevant publication(s):

Z. Yaniv, B. C. Lowekamp, H. J. Johnson, R. Beare, "SimpleITK Image-Analysis Notebooks: a Collaborative Environment for Education and Reproducible Research", *J Digit Imaging.*, https://doi.org/10.1007/s10278-017-0037-8, 2017.

B. C. Lowekamp, D. T. Chen, L. Ibáñez, D. Blezek, "The Design of SimpleITK", *Front. Neuroinform.*, 7:45. https://doi.org/10.3389/fninf.2013.00045, 2013.

Documentation
-------------
With massive libraries like SimpleITK, good documentation is a must. The documentation for SimpleITK is split up into multiple levels:
1. [API Documentation](https://itk.org/SimpleITKDoxygen/html/) - This contains class and function documentation. The descriptions for functions and classes are primarily borrowed from the original ITK classes.
2. [SimpleITK Documentation](http://simpleitk.readthedocs.io/en/next/) - This contains higher-level guides, installing toolkit's binary distributions, building the toolkit as well as examples specific to SimpleITK. This documentation will be valid for each language that SimpleITK supports. The examples will also include code in each language.
    * [SimpleITK Wiki](https://itk.org/Wiki/SimpleITK) - This is the old SimpleITK documentation page which was replaced by ReadTheDocs. The information may be outdated.
3. Notebooks Repositories - This documentation is similar to the SimpleITK documentation except it contains examples on how to utilize **multiple** classes in SimpleITK to facilitate solving a broader image processing problem.
    * [Python/Jupyter Notebook](http://insightsoftwareconsortium.github.io/SimpleITK-Notebooks/)

Support
-------

SimpleITK provides access to most of the ITK components, but not all. If you are looking for something specific and can't find it, open an issue on GitHub or ask for support on the [forum](https://discourse.itk.org).

Report an Issue
---------------

Help us improve SimpleITK by reporting issues you encounter. When you report an error, you allow us to address your specific problem, but more importantly you are helping all of the SimpleITK community.

**Thank you for helping making SimpleITK better!**

All issues are reported and managed on the [project's GitHub issue tracker](https://github.com/SimpleITK/SimpleITK/issues). When reporting an issue, please provide as much information as possible to enable us to reproduce the problem.

The following information will allow us to address your issue in a timely manner:
1. Error message (copy & pasted) and focused description of the problem.
2. Operating system, and version (e.g. OSX 10.11.6).
3. Programming language, and version (e.g. Python 2.7.14, R 3.2.3).
4. Version of SimpleITK (e.g. 1.1.0), just invoke the SimpleITK Version() function.
5. How did you install SimpleITK, binary distribution (e.g. conda install -c simpleitk simpleitk), or built it from source (e.g. devtools::install_github("SimpleITK/SimpleITKRInstaller")).
6. A minimal working example which causes the error.
7. If your code requires input, possibly point to a minimal sized input image.
