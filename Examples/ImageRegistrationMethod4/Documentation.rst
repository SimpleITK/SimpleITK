Image Registration Method 4
===========================

Overview
--------

.. include:: registrationExamplePrefix.rst

Example Run
-----------

Running the Python code with the following inputs:

``main('BrainProtonDensitySliceBorder20.png', 'BrainProtonDensitySliceShifted13x17y.png', 'displaceMeth4.hdf5')``

produces the text and images below.

Output Text
^^^^^^^^^^^

.. collapse:: Text Output (click triangle to collapse)
    :open:

    .. exec_code::

        # --- hide: start ---

        from example_utils import run_example, plot_image
        args = ['../images/BrainProtonDensitySliceBorder20.png',
                '../images/BrainProtonDensitySliceShifted13x17y.png',
                'displaceMeth4.hdf5',
               ]
        return_dict = run_example('ImageRegistrationMethod4', 'main', args)
        # --- hide: stop ---


.. plot::
   :align: center
   :nofigs:

    from example_utils import run_example, plot_image
    args = ['../images/BrainProtonDensitySliceBorder20.png',
            '../images/BrainProtonDensitySliceShifted13x17y.png',
            'displaceMeth4.hdf5',
           ]
    return_dict = run_example('ImageRegistrationMethod4', 'main', args)
    for key, value in return_dict.items():
        plot_image(value)


Input Images
^^^^^^^^^^^^

.. list-table::

    * - .. figure:: link_ImageRegistrationMethod4_docs-1_00.png
           :scale: 100%

        **Fixed Image**

      - .. figure:: link_ImageRegistrationMethod4_docs-1_01.png
           :scale: 100%

        **Moving Image**

Output Image
^^^^^^^^^^^^

.. figure:: link_ImageRegistrationMethod4_docs-1_02.png
   :scale: 100%

   **Composition Image**

Code
----

.. tabs::

  .. tab:: Python

    .. literalinclude:: ../../Examples/ImageRegistrationMethod4/ImageRegistrationMethod4.py
       :language: python
       :lines: 1,19-88

  .. tab:: R

    .. literalinclude:: ../../Examples/ImageRegistrationMethod4/ImageRegistrationMethod4.R
       :language: R
       :lines: 18-
