User Guide
**********

Here is a guide on SimpleITK.

You can download the source code/jupyter notebook for each of the guides
using the links at the bottom of the guide. However, to make code readable,
code for :doc:`downloading <user_guide/downloaddata>` and 
:doc:`plotting <user_guide/myshow>` the images has been extracted into
separate python files. You need to download them before running the guides.

.. Note::

    Please download the zipped files required to run the code below from 
    `here <_static/sitk_download_plot.zip>`_ and extract it to your 
    python environment (usually, directory in which you are running the code).

Basics of Image
===============

.. galleryitem:: /user_guide/image_guide.py

.. raw:: html

    <div style='clear:both'></div>

Visualizing Images
==================

.. galleryitem:: /user_guide/visualization/visimage_guide.py
.. galleryitem:: /user_guide/visualization/vis3dimage_guide.py
.. galleryitem:: /user_guide/visualization/visseg_guide.py

.. raw:: html

    <div style='clear:both'></div>

Transforms
==========

.. galleryitem:: /user_guide/transforms/interpolation_guide.py
.. galleryitem:: /user_guide/transforms/transforms_guide.py
.. galleryitem:: /user_guide/transforms/moretransforms_guide.py

.. raw:: html

    <div style='clear:both'></div>


Segmentation
============

Image segmentation filters process an image to partition it into (hopefully) 
meaningful regions. The output is commonly an image of integers where each 
integer can represent an object. The value 0 is commonly used for the 
background, and 1 ( sometimes 255) for a foreground object.

.. galleryitem:: /user_guide/segmentation/threshold_guide.py
.. galleryitem:: /user_guide/segmentation/region_growing_guide.py


.. raw:: html

    <div style='clear:both'></div>
