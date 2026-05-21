.. _lbl_elastix_examples:

Elastix Examples
================

These examples demonstrate the usage of the SimpleElastix framework for image registration and transformation. SimpleElastix provides access to the powerful `elastix <https://elastix.lumc.nl/>`_ registration toolbox through SimpleITK's `ElastixImageFilter <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ElastixImageFilter.html>`_ and `TransformixImageFilter <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1TransformixImageFilter.html>`_ classes.

The elastix framework is widely used for medical image registration and offers:

* A comprehensive collection of registration algorithms
* Multi-resolution strategies
* A variety of transformation models (rigid, affine, B-spline, etc.)
* Multiple similarity metrics for different imaging modalities
* A `parameter zoo <https://lkeb.ml/modelzoo/>`_ with pre-configured settings for common registration scenarios

.. toctree::
  :maxdepth: 1

  link_ElastixRegistration_docs

See Also
--------

* `elastix documentation <https://elastix.lumc.nl/>`_
* `elastix parameter zoo <https://lkeb.ml/modelzoo/>`_ - Pre-configured parameter files for various registration tasks
* `SimpleITK ElastixImageFilter <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ElastixImageFilter.html>`_
* `SimpleITK TransformixImageFilter <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1TransformixImageFilter.html>`_
