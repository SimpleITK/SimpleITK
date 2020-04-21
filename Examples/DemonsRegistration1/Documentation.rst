.. _lbl_demons_registration1:

DemonsRegistration1
===================


Overview
--------

This example illustrates how to use the `classic Demons registration algorithm
<https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1DemonsRegistrationFilter.html>`_.
The user supplied parameters for the algorithm are the number of iterations and
the standard deviations for the Gaussian smoothing of the total displacement
field. Additional methods which control regularization, total field smoothing
for elastic model or update field smoothing for viscous model are available.

The underlying assumption of the demons framework is that the intensities of
homologous points are equal. The example uses histogram matching to make the two
images similar prior to registration. This is relevant for registration of MR
images where the assumption is not valid. For other imaging modalities where the
assumption is valid, such as CT, this step is not necessary. Additionally, the
command design pattern is used to monitor registration progress. The resulting
deformation field is written to file.

See also: :ref:`lbl_demons_registration2`.

Code
----

.. tabs::

  .. tab:: C++

    .. literalinclude:: ../../Examples/DemonsRegistration1/DemonsRegistration1.cxx
       :language: c++
       :lines: 18-

  .. tab:: Python

    .. literalinclude:: ../../Examples/DemonsRegistration1/DemonsRegistration1.py
       :language: python
       :lines: 1,19-

  .. tab:: R

    .. literalinclude:: ../../Examples/DemonsRegistration1/DemonsRegistration1.R
       :language: R
       :lines: 18-
