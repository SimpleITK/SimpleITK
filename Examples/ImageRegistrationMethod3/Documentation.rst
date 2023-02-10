Image Registration Method 3
===========================

Overview
--------

.. include:: registrationExamplePrefix.rst

Example Run
-----------

Running the Python code with the following inputs:

``main('BrainProtonDensitySliceBorder20.png', 'BrainProtonDensitySliceShifted13x17y.png', 'displaceMeth3.hdf5')``

produces the text and images below.

Output Text
^^^^^^^^^^^

.. collapse:: Text Output (click triangle to collapse)
    :open:

    .. exec_code::

        # --- hide: start ---
        import os
        import sys

        # The exec_code extension isn't looking at the sys.path set in conf.py
        # and for some reason is running in docs instead of docs/source.
        sys.path.insert(0,os.path.abspath('./source'))
        sys.path.insert(0,os.path.abspath('../Examples'))

        from example_utils import run_example, plot_image
        args = ['../docs/images/BrainProtonDensitySliceBorder20.png',
                '../docs/images/BrainProtonDensitySliceShifted13x17y.png',
                'displaceMeth3.hdf5',
               ]
        return_dict = run_example('ImageRegistrationMethod3', 'main', args)
        # --- hide: stop ---


.. plot::
   :align: center
   :nofigs:

    import os
    import sys

    from example_utils import run_example, plot_image
    args = ['../../docs/images/BrainProtonDensitySliceBorder20.png',
            '../../docs/images/BrainProtonDensitySliceShifted13x17y.png',
            'displaceMeth3.hdf5',
           ]
    return_dict = run_example('ImageRegistrationMethod3', 'main', args)
    for key, value in return_dict.items():
        plot_image(value)


Input Images
^^^^^^^^^^^^

.. list-table::

    * - .. figure:: link_ImageRegistrationMethod3_docs-1_00.png
           :scale: 100%

           **Fixed Image**

      - .. figure:: link_ImageRegistrationMethod3_docs-1_01.png
           :scale: 100%

           **Moving Image**

Output Image
^^^^^^^^^^^^

.. figure:: link_ImageRegistrationMethod3_docs-1_02.png
   :scale: 100%

   **Composition Image**

Code
----

.. tabs::

  .. tab:: Python

    .. literalinclude:: ../../Examples/ImageRegistrationMethod3/ImageRegistrationMethod3.py
       :language: python
       :lines: 1,20-95

  .. tab:: R

    .. literalinclude:: ../../Examples/ImageRegistrationMethod3/ImageRegistrationMethod3.R
       :language: R
       :lines: 18-
