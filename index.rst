Welcome to SimpleITK 
=====================

SimpleITK is an image-analysis toolkit, providing a simplified programming interface to the algorithms and data structures of the Insight Segmentation and Registration Toolkit. It supports image operations on 2D, 3D and 4D multi-channel images. The toolkit is available in eight programming languages including Python, R, Java, C#, C++, Lua, Ruby, and TCL.

SimpleITK includes several hundred classes providing a broad set of tools required for image analysis. The toolkit provides extensive support for image input and output, supporting more than 20 image file formats. A large number of filtering operations are also available, from basic image analysis operations such as edge detection, binary and grayscale morphological operations, and distance transformations to MRI bias field correction. Additionally, a variety of traditional operators used for image segmentation are available including region growing, connected component labelling, and the watershed transformation. Finally, the toolkit includes a robust registration framework, readily enabling one to align intra and inter modality images, supporting both rigid and non-rigid transformation models.

SimpleITK is widely used by researchers from various domains requiring images analysis capabilities. Amongst others these include analysis of anatomical structures imaged with CT,MR, and PET, and analysis of cellular structures imaged using dual photon microscopy, focused ion beam scanning electron microscopy and focal plane array microscopy. Additionally, the toolkit has been used at a number of academic institutions as a tool for teaching medical image analysis.

Binary distributions of SimpleITK are currently available for all three major operating systems
(Linux, OS X, and Windows). The code is copyrighted by the Insight Software Consortium and is distributed under the Apache 2.0 License. 

.. toctree::
   :maxdepth: 1
   :caption: Table of Contents
   :hidden:

   Documentation/docs/source/installation
   Documentation/docs/source/fundamentalConcepts
   Documentation/docs/source/registrationOverview
   Documentation/docs/source/conventions
   Documentation/docs/source/IO
   Documentation/docs/source/filters
   Documentation/docs/source/building
   Documentation/docs/source/setUp
   Documentation/docs/source/tutorialsAndCourses
   Documentation/docs/source/faq
   Examples/index


Relevant Resources
------------------

* `Doxygen API documentation <https://itk.org/SimpleITKDoxygen/html/>`_.
* :ref:`Concise examples <lbl_examples>`.
* Long examples and image analysis workflows using `Jupyter Notebooks in Python and R <https://github.com/InsightSoftwareConsortium/SimpleITK-Notebooks>`_.
* `ITK forum <https://discourse.itk.org/>`_ for discussions and questions.
* `Issue tracker <https://github.com/SimpleITK/SimpleITK/issues>`_ for reporting bugs and feature requests.  

How to Cite
-----------

If you find SimpleITK useful in your research, support our efforts by citing
the relevant publication(s):

R. Beare, B. C. Lowekamp, Z. Yaniv, "Image Segmentation, Registration and Characterization in R with SimpleITK", *J Stat Softw*, 86(8), https://doi.org/10.18637/jss.v086.i08, 2018.

Z. Yaniv, B. C. Lowekamp, H. J. Johnson, R. Beare, "SimpleITK Image-Analysis Notebooks: a Collaborative Environment for Education and Reproducible Research", *J Digit Imaging.*, https://doi.org/10.1007/s10278-017-0037-8, 31(3): 290-303, 2018.

B. C. Lowekamp, D. T. Chen, L. Ibáñez, D. Blezek, "The Design of SimpleITK", *Front. Neuroinform.*, 7:45. https://doi.org/10.3389/fninf.2013.00045, 2013.

