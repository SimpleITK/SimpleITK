.. _lbl_image_registration_method_bspline1:

Image Registration Method BSpline 1
===================================

Overview
--------

.. include:: registrationExamplePrefix.rst

Example Run
-----------

Running the Python code with the following inputs:

``main('BrainProtonDensitySliceBorder20.png', 'BrainProtonDensitySliceBSplined10.png', 'ImageRegistrationMethodBSpline1.hdf5')``

produces the text and images below.

Output Text
^^^^^^^^^^^

.. collapse:: Text Output (click triangle to collapse)
    :open:

    .. exec_code::

        # --- hide: start ---
        from example_utils import run_example, save_image
        args = ['../images/BrainProtonDensitySliceBorder20.png',
                '../images/BrainProtonDensitySliceBSplined10.png',
                'ImageRegistrationMethodBSpline1.hdf5',
               ]
        return_dict = run_example('ImageRegistrationMethodBSpline1', 'main', args)
        for key, value in return_dict.items():
            save_image(value, f"ImageRegistrationMethodBSpline1_{key}")
        # --- hide: stop ---


Input Images
^^^^^^^^^^^^

.. list-table::

    * - .. figure:: ../images/ImageRegistrationMethodBSpline1_fixed.png
           :scale: 100%

        **Fixed Image**

      - .. figure:: ../images/ImageRegistrationMethodBSpline1_moving.png
           :scale: 100%

        **Moving Image**

Output Image
^^^^^^^^^^^^

.. figure:: ../images/ImageRegistrationMethodBSpline1_composition.png
   :scale: 100%

   **Composition Image**


Code
----

.. tabs::

  .. tab:: C++

    .. literalinclude:: ../../Examples/ImageRegistrationMethodBSpline1/ImageRegistrationMethodBSpline1.cxx
       :language: c++
       :lines: 18-

  .. tab:: Python

    .. literalinclude:: ../../Examples/ImageRegistrationMethodBSpline1/ImageRegistrationMethodBSpline1.py
       :language: python
       :lines: 1,19-

  .. tab:: R

    .. literalinclude:: ../../Examples/ImageRegistrationMethodBSpline1/ImageRegistrationMethodBSpline1.R
       :language: R
       :lines: 18-
