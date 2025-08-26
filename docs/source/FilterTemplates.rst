Developer
*********

Image Filter Templates ReadMe
=============================

This section outlines the system used to generate SimpleITK  source code using an "Expand Template Generator" system. It uses `Jinja <https://jinja.palletsprojects.com/>`_ as a template engine with
YAML configuration files, template files for .h and .cxx files.

..
    .. contents:: On this page
        :local:
        :backlinks: none

Overview
========

In order to create a uniform body of image filters, we use an automated
code generation system to wrap existing ITK filters into SimpleITK
filters. The development process consists of writing a YAML configuration file
which specifies the information needed to fill in the fields of the
template file. During the SimpleITK build process, each .yaml files are parsed
using a `Jinja <https://jinja.palletsprojects.com/>`_ template engine, with a header (.h) and a implementation (.cxx). Additionally, for each enabled language and C++, there is a test `Jinja <https://jinja.palletsprojects.com/>`_  template that is used to generate testing source code.


Available Templates
-------------------

The following template types are available in ``Code/BasicFilters/templates/`` for generating SimpleITK filters:

-  **ImageFilter**: The standard template for most image filters with a single input image type or template. This is the most commonly used template and supports filters that take one input image and produce one output image.

-  **BinaryFunctorFilter**: Template for filters that perform pixel-wise operations between two input images using a functor (mathematical operation). Examples include arithmetic operations like addition, subtraction, multiplication, etc.

-  **MultiInputImageFilter**: Template for filters that accepts a variable number of input images. This template provides support for a variable number of inputs and a vector of images as input.

-  **ImageSource**: Template for filters that generate images without requiring input images. These are source filters that create images from parameters or mathematical functions.

-  **DualImageFilter**: Template that instantiates filters with combinations of different pixel types. This template should be used with caution as it can significantly increase compilation time and binary size due to the combinatorial explosion of type instantiations.



YAML Schema
===========

YAML (YAML Ain't Markup Language) is a human-readable data serialization format that is often used for configuration files and data exchange between languages with different data structures. For the purposes of SimpleITK, a yaml file consists of a single document which contains key-value pairs, lists, and nested structures.

The schema used for SimpleITK filter generation is defined in the ``ExpandTemplateGenerator/simpleitk_filter_description.schema.json`` file. This Schema document provides formal validation rules and documentation for all the fields that can be used in YAML filter description files.


The schema defines the structure for filter descriptions including required fields, optional parameters, data types, and validation constraints. It serves as both documentation and validation for YAML filter files used in the code generation process.


.. literalinclude:: ../../ExpandTemplateGenerator/simpleitk_filter_description.schema.json
   :language: json
   :caption: SimpleITK Filter Description Schema
