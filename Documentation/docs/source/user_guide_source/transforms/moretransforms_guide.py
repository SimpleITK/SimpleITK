"""
More details about Transforms
*****************************


This guide introduces the transformation types supported by SimpleITK and 
illustrates how to "promote" transformations from a lower to higher parameter 
space (e.g. 3D translation to 3D rigid).

.. contents:: On this Page
    :local:
    :backlinks: none

**SimpleITK Transformation Types**


+----------------------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| `TranslationTransform <http://www.itk.org/Doxygen/html/classitk_1_1TranslationTransform.html>`__               | 2D or 3D, translation                                                                                                                                                                                  |
+----------------------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| `VersorTransform <http://www.itk.org/Doxygen/html/classitk_1_1VersorTransform.html>`__                         | 3D, rotation represented by a versor                                                                                                                                                                   |
+----------------------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| `VersorRigid3DTransform <http://www.itk.org/Doxygen/html/classitk_1_1VersorRigid3DTransform.html>`__           | 3D, rigid transformation with rotation represented by a versor                                                                                                                                         |
+----------------------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| `Euler2DTransform <http://www.itk.org/Doxygen/html/classitk_1_1Euler2DTransform.html>`__                       | 2D, rigid transformation with rotation represented by a Euler angle                                                                                                                                    |
+----------------------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| `Euler3DTransform <http://www.itk.org/Doxygen/html/classitk_1_1Euler3DTransform.html>`__                       | 3D, rigid transformation with rotation represented by Euler angles                                                                                                                                     |
+----------------------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| `Similarity2DTransform <http://www.itk.org/Doxygen/html/classitk_1_1Similarity2DTransform.html>`__             | 2D, composition of isotropic scaling and rigid transformation with rotation represented by a Euler angle                                                                                               |
+----------------------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| `Similarity3DTransform <http://www.itk.org/Doxygen/html/classitk_1_1Similarity3DTransform.html>`__             | 3D, composition of isotropic scaling and rigid transformation with rotation represented by a versor                                                                                                    |
+----------------------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| `ScaleTransform <http://www.itk.org/Doxygen/html/classitk_1_1ScaleTransform.html>`__                           | 2D or 3D, anisotropic scaling                                                                                                                                                                          |
+----------------------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| `ScaleVersor3DTransform <http://www.itk.org/Doxygen/html/classitk_1_1ScaleVersor3DTransform.html>`__           | 3D, rigid transformation and anisotropic scale is added to the rotation matrix part (not composed as one would expect)                                                                                 |
+----------------------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| `ScaleSkewVersor3DTransform <http://www.itk.org/Doxygen/html/classitk_1_1ScaleSkewVersor3DTransform.html>`__   | 3D, rigid transformation with anisotropic scale and skew matrices added to the rotation matrix part (not composed as one would expect)                                                                 |
+----------------------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| `AffineTransform <http://www.itk.org/Doxygen/html/classitk_1_1AffineTransform.html>`__                         | 2D or 3D, affine transformation.                                                                                                                                                                       |
+----------------------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| `BSplineTransform <http://www.itk.org/Doxygen/html/classitk_1_1BSplineTransform.html>`__                       | 2D or 3D, deformable transformation represented by a sparse regular grid of control points.                                                                                                            |
+----------------------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| `DisplacementFieldTransform <http://www.itk.org/Doxygen/html/classitk_1_1DisplacementFieldTransform.html>`__   | 2D or 3D, deformable transformation represented as a dense regular grid of vectors.                                                                                                                    |
+----------------------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| `Transform <http://www.itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1Transform.html>`__                  | A generic transformation. Can represent any of the SimpleITK transformations, and a **composite transformation** (stack of transformations concatenated via composition, last added, first applied).   |
+----------------------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


"""

import SimpleITK as sitk
import numpy as np
import matplotlib.pyplot as plt


##############################################################################
# Points in SimpleITK
# ===================
#
# Utility functions
# -----------------
# Let's write some functions that deal with point data in a uniform manner.
#
# Print Point
# ^^^^^^^^^^^
# Format a point for printing, based on specified precision with trailing
# zeros.

def point2str(point, precision=1):
    format_str = '.{0}f'.format(precision)
    return ' '.join(format(c, format_str) for c in point)

##############################################################################
# Generate Random Cloud of points
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#
# Generate random (uniform withing bounds) nD point cloud.
# Dimension is based on the number of pairs in the bounds input.


def uniform_random_points(bounds, num_points):
    internal_bounds = [sorted(b) for b in bounds]
    # Generate rows for each of the coordinates according to
    # the given bounds, stack into an array, and split into
    # a list of points.
    mat = np.vstack([np.random.uniform(b[0], b[1], num_points)
                     for b in internal_bounds])
    return list(mat[:len(bounds)].T)

##############################################################################
# Compute Registration Error
# ^^^^^^^^^^^^^^^^^^^^^^^^^^
#
# Distances between points transformed by the given transformation and their
# location in another coordinate system. When the points are only used to
# evaluate registration accuracy (not used in the registration) this is the
# target registration error (TRE).


def target_registration_errors(tx, point_list, reference_point_list):
    return [np.linalg.norm(np.array(tx.TransformPoint(p)) - np.array(p_ref))
            for p, p_ref in zip(point_list, reference_point_list)]

##############################################################################
# Check difference between two transformations
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#
# Check whether two transformations are "equivalent" in an arbitrary spatial
# region either 3D or 2D, [x=(-10,10), y=(-100,100), z=(-1000,1000)]. This is
# just a sanity check, as we are just looking at the effect of the
# transformations on a random set of points in the region.


def print_transformation_differences(tx1, tx2):
    if tx1.GetDimension() == 2 and tx2.GetDimension() == 2:
        bounds = [(-10, 10), (-100, 100)]
    elif tx1.GetDimension() == 3 and tx2.GetDimension() == 3:
        bounds = [(-10, 10), (-100, 100), (-1000, 1000)]
    else:
        raise ValueError('Transformation dimensions mismatch, '
                         'or unsupported transformation dimensionality')
    num_points = 10
    point_list = uniform_random_points(bounds, num_points)
    tx1_point_list = [tx1.TransformPoint(p) for p in point_list]
    differences = target_registration_errors(tx2, point_list, tx1_point_list)

    print('{} - {} :\tminDifference: {:.2f} maxDifference: {:.2f}'.format(
        tx1.GetName(), tx2.GetName(), min(differences), max(differences)))

##############################################################################
# In SimpleITK points can be represented by any vector-like data type.
# In Python these include Tuple, Numpy array, and List. In general Python will
# treat these data types differently, as illustrated by the print function
# below.
#
# SimpleITK points represented by vector-like data structures.
point_tuple = (9.0, 10.531, 11.8341)
point_np_array = np.array([9.0, 10.531, 11.8341])
point_list = [9.0, 10.531, 11.8341]

print('tuple : {}'.format(point_tuple))
print('numpy array : {}'.format(point_np_array))
print('list: {}'.format(point_list))

# Uniform printing with specified precision.
precision = 2
print(point2str(point_tuple, precision))
print(point2str(point_np_array, precision))
print(point2str(point_list, precision))


##############################################################################
# Global Transformations
# ======================
# All global transformations *except* translation are of the form:
#
# .. math ::
#     T(\mathbf{x}) = A(\mathbf{x}-\mathbf{c}) + \mathbf{t} + \mathbf{c}
#
# In ITK speak (when printing your transformation):
#
# - Matrix: the matrix  :math:`A`
# - Center: the point  :math:`c`
# - Translation: the vector  :math:`t`
# - Offset:  :math:`t+c−Ac`
#
#
# TranslationTransform
# --------------------
# A 3D translation. Note that you need to specify the dimensionality,
# as the sitk TranslationTransform represents both 2D and 3D translations.

dimension = 3
offset = (1, 2, 3)  # offset can be any vector-like data
translation = sitk.TranslationTransform(dimension, offset)
print(translation)

##############################################################################
# Transform a point and use the inverse transformation to get the original
# back.

point = [10, 11, 12]
transformed_point = translation.TransformPoint(point)
translation_inverse = translation.GetInverse()
print(('original point:    {} \n'
       'transformed point: {} \n'
       'back to original:  {} \n').format(
    point2str(point),
    point2str(transformed_point),
    point2str(translation_inverse.TransformPoint(transformed_point))))

##############################################################################
# Euler2DTransform
# ----------------
#
# This transform applies a rigid transformation is 2D space. The transform
# is specified as a rotation around arbitrary center and is followed by a
# translation.


rotation2D = sitk.Euler2DTransform()
rotation2D.SetTranslation((7.2, 8.4))
rotation2D.SetAngle(np.pi / 2)

point = [10, 11]
print(('original point:    {}\n'
       'transformed point:  {}').format(
    point2str(point),
    point2str(rotation2D.TransformPoint(point))))

##############################################################################
# Change the center of rotation so that it coincides with the point we want to
# transform, why is this a unique configuration?

rotation2D.SetCenter(point)
print(('original point:    {}\n'
       'transformed point:  {}').format(
    point2str(point),
    point2str(rotation2D.TransformPoint(point))))

##############################################################################
# VersorTransform
# ---------------
#
# Rotation only, parametrized by Versor (vector part of unit quaternion),
# quaternion defined by rotation of theta around axis n:
#
# .. math ::
#       q = [n\sin(\theta/2), \cos(\theta/2)]
#
# 180 degree rotation around z axis

# Using a versor
rotation1 = sitk.VersorTransform([0, 0, 1, 0])

# Using axis-angle:
rotation2 = sitk.VersorTransform((0, 0, 1), np.pi)

# Using a matrix:
rotation3 = sitk.VersorTransform()
rotation3.SetMatrix([-1, 0, 0, 0, -1, 0, 0, 0, 1])

point = (10, 100, 1000)
p1 = rotation1.TransformPoint(point)
p2 = rotation2.TransformPoint(point)
p3 = rotation3.TransformPoint(point)

print(('Points after transformation:\n'
       'p1 = {} \n'
       'p2 = {} \n'
       'p3 = {} \n').format(p1, p2, p3))

##############################################################################
# We applied the "same" transformation to the same point, so why are the
# results slightly different for the second initialization method?
#
# This is where theory meets practice. Using the axis-angle initialization
# method involves trigonometric functions which on a fixed precision machine
# lead to these slight differences. In many cases this is not an issue, but it
# is something to remember. From here on we will sweep it under the rug
# (printing with a more reasonable precision).
#
# Translation to Rigid [3D]
# -------------------------
# .. todo ::
#   Fill all the notebook. It's too boring and requires too much work.
