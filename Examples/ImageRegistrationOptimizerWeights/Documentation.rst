Image Registration Optimizer Weights
====================================

.. include:: registrationExamplePrefix.rst

Overview
--------
The image registration framework allows us to disable subsets of the
transformation parameters so that we can use a lower dimensional
transformation. In some cases, if we have some better prior knowledge we
can weigh the parameters accordingly (this is much harder to utilize to get a desired effect than disabling parameters).

In this example, we work with a 3D rigid transformation
using the Euler parameterization, but we only allow rotation around the `z`
axis. As there is no transformation that represents this subspace of rigid
transformations, we use the `SetOptimizerWeights` method to disable
rotations around the `x` and `y` axes. The order of the weights in the weights
parameter matches the order of parameters returned from the transformation
`GetParameters` method. For the Euler3DTransform the order is
`[angleX, angleY, angleZ, tx, ty, tz]`, so our weights vector is `[0,0,1,1,1,1]`.


Code
----

.. tabs::

  .. tab:: Python

    .. literalinclude:: ../../Examples/ImageRegistrationOptimizerWeights/ImageRegistrationOptimizerWeights.py
       :language: python
       :lines: 1,19-

  .. tab:: R

    .. literalinclude:: ../../Examples/ImageRegistrationOptimizerWeights/ImageRegistrationOptimizerWeights.R
       :language: r
       :lines:  18-
