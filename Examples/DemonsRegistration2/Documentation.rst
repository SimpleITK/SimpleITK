.. _lbl_demons_registration2:

DemonsRegistration2
===================


Overview
--------

This example illustrates how to use the `fast symmetric forces Demons algorithm
<https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1FastSymmetricForcesDemonsRegistrationFilter.html>`_.
As the name implies, unlike the classical algorithm, the forces are symmetric.

The underlying assumption of the demons framework is that the intensities of
homologous points are equal. The example uses histogram matching to make the two
images similar prior to registration. This is relevant for registration of MR
images where the assumption is not valid. For other imaging modalities where the
assumption is valid, such as CT, this step is not necessary. Additionally, the
command design pattern is used to monitor registration progress. The resulting
deformation field is written to file.


See also: :ref:`lbl_demons_registration1`.


Code
----

.. tabs::

  .. tab:: C++

    .. literalinclude:: ../../Examples/DemonsRegistration2/DemonsRegistration2.cxx
       :language: c++
       :lines: 18-

  .. tab:: Python

    .. literalinclude:: ../../Examples/DemonsRegistration2/DemonsRegistration2.py
       :language: python
       :lines: 1,19-

  .. tab:: R

    .. literalinclude:: ../../Examples/DemonsRegistration2/DemonsRegistration2.R
       :language: R
       :lines: 18-
