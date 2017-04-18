"""
Transforms and Resampling
*************************

This tutorial explains how to apply transforms to images.

SimpleITK provides you with variety of transforms like Translation,
Affine (which includes rotations, shear, scaling)

It is important to keep in mind that these transforms are applied on the 
points in the physical space, not the image cordinates itself. 

A few conventions:

- Points are represented by vector-like data types: Tuple, Numpy array, List.
- Matrices are represented by vector-like data types in row major order.

.. contents:: On this Page
    :local:
    :backlinks: none

"""
# License: CC-BY
# sphinx_gallery_thumbnail_number = 7

import SimpleITK as sitk
import numpy as np
from myshow import myshow

##############################################################################
# Creating and Manipulating Transforms
# ====================================
# A number of different spatial transforms are available in SimpleITK.
#
# Identity Transform
# ------------------
# The simplest is the Identity Transform.
# This transform simply returns input points unaltered.
#


dimension = 2

print('*Identity Transform*')
identity = sitk.Transform(dimension, sitk.sitkIdentity)
print('Dimension: {}'.format(identity.GetDimension()))

# Points are always defined in physical space
point = (1.0, 1.0)


def transform_point(transform, point):
    transformed_point = transform.TransformPoint(point)
    print('Point {} is transformed to {}'.format(point, transformed_point))

transform_point(identity, point)

##############################################################################
# Transform are defined by two sets of parameters, the ``Parameters`` and
# ``FixedParameters``.  ``FixedParameters`` are not changed during the
# optimization process when performing registration.
#
# Translation Transform
# ---------------------
# This transform simply translates input points by a offest.
# For the TranslationTransform, the Parameters are the values of this translation
# Offset.

print('*Translation Transform*')
translation = sitk.TranslationTransform(dimension)

print('Parameters: {}'.format(translation.GetParameters()))
print('Offset:     {}'.format(translation.GetOffset()))
print('FixedParameters: {}'.format(translation.GetFixedParameters()))
transform_point(translation, point)

print('')
translation.SetParameters((3.1, 4.4))
print('Parameters: {}'.format(translation.GetParameters()))
transform_point(translation, point)

##############################################################################
# Affine Transform
# ----------------
# The affine transform is capable of representing translations, rotations,
# shearing, and scaling.
#
# Affine transformation can be described with the following equation:
#
# .. math::
#
#     x' = A.(x-c) + t
#
# where x is the input cordinate vector and x' is the output cordinate vector,
# A is the affine matrix, t is the translation and c is the centre of
# the affine transform.
# By default, A = I and C = 0

print('*Affine Transform*')
affine = sitk.AffineTransform(dimension)

print('Parameters: {}'.format(affine.GetParameters()))
print('FixedParameters: {}'.format(affine.GetFixedParameters()))
transform_point(affine, point)

print('')
affine.SetTranslation((3.1, 4.4))
print('Parameters: {}'.format(affine.GetParameters()))
transform_point(affine, point)

##############################################################################
# A number of other transforms exist to represent non-affine deformations,
# well-behaved rotation in 3D, etc. See the :doc:`Next guide` for more
# information.
#
# Applying Transforms to Images
# =============================
# Let's create a grid image to illustrate our transforms.

grid = sitk.GridSource(outputPixelType=sitk.sitkUInt16,
                       size=(250, 250),
                       sigma=(0.5, 0.5),
                       gridSpacing=(5.0, 5.0),
                       gridOffset=(0.0, 0.0),
                       spacing=(0.2, 0.2))

myshow(grid, 'Grid Input')

##############################################################################
# To apply the transform, a resampling operation is required.
#
# .. note::
#
#   Resample applies transform to phyiscal space, not voxel cordinates directly.
#   Once phyiscal space is transformed, you will need to specify how you view
#   this space by setting output origin, spacing and direction. Alternatively,
#   you can specify a reference image so that output origin, spacing and
#   direction are set to that of the reference image.
#
# In the following ``resample`` function, output image Origin, Spacing, Size,
# Direction are taken from the reference


def resample(image, transform):
    reference_image = image
    interpolator = sitk.sitkCosineWindowedSinc
    default_value = 100.0
    return sitk.Resample(image, reference_image, transform,
                         interpolator, default_value)

##############################################################################
# Let's apply translation to image

translation = sitk.TranslationTransform(2)
translation.SetOffset((3.1, 4.6))
transform_point(translation, point)
resampled = resample(grid, translation)
myshow(resampled, 'Resampled Translation')

##############################################################################
# What happened?  The translation is positive in both directions.  Why does the
# output image move down and to the left?
#
# .. note::
#
#   It important to keep in mind that a transform in a resampling operation
#   defines *the transform from the output space to the input space*.

inv_translation = translation.GetInverse()
transform_point(inv_translation, point)
resampled = resample(grid, inv_translation)
myshow(resampled, 'Inverse Resampled')

##############################################################################
# An affine (line preserving) transformation, can perform translation, scaling,
# rotation and shearing:
#
# Translation
# -----------


x_translation, y_translation = (3.1, 4.6)

affine = sitk.AffineTransform(2)
affine.SetTranslation((x_translation, y_translation))
resampled = resample(grid, affine)
myshow(resampled, 'Translated')

##############################################################################
# Scaling
# -------
x_scale, y_scale = 3.0, 0.7

affine = sitk.AffineTransform(2)
affine.Scale((x_scale, y_scale))
resampled = resample(grid, affine)
myshow(resampled, 'Scaled')


##############################################################################
# Rotation
# --------
# We can either use ``AffineTransform::Rotate`` or directly set rotation matrix.
# Let's take the first route.

degrees = 20

affine = sitk.AffineTransform(2)
radians = np.pi * degrees / 180.
affine.Rotate(axis1=0, axis2=1, angle=radians)
resampled = resample(grid, affine)
myshow(resampled, 'Rotated')

##############################################################################
# Shearing
# --------
# This time, let's directly set the matrix.

x_shear, y_shear = 0.3, 0.1

matrix = np.eye(2)
matrix[0, 1] = -x_shear
matrix[1, 0] = -y_shear
print(matrix)

affine.SetMatrix(matrix.ravel())
resampled = resample(grid, affine)
myshow(resampled, 'Sheared')


##############################################################################
# Composite Transform
# ===================
# It is possible to compose multiple transform together into a single transform 
# object. With a composite transform, multiple resampling operations are 
# prevented, so interpolation errors are not accumulated. For example, an 
# affine transformation that consists of a translation and rotation:

translate = (8.0, 16.0)
rotate = 20.0

affine = sitk.AffineTransform(2)
affine.SetTranslation(translate)
affine.Rotate(axis1=0, axis2=1, angle=np.pi / 180 * rotate)

resampled = resample(grid, affine)
myshow(resampled, 'Single Transform')

##############################################################################
# This can also be represented with two Transform objects applied in sequence 
# with a Composite Transform:

translation = sitk.TranslationTransform(2)
translation.SetOffset(translate)

affine = sitk.AffineTransform(2)
affine.Rotate(axis1=0, axis2=1, angle=np.pi / 180 * rotate)

composite = sitk.Transform(2, sitk.sitkComposite)
composite.AddTransform(translation)
composite.AddTransform(affine)

resampled = resample(grid, composite)
myshow(resampled, 'Composite of Two Transforms')

##############################################################################
# Beware, tranforms are non-commutative -- order matters!

composite = sitk.Transform(2, sitk.sitkComposite)
composite.AddTransform(affine)
composite.AddTransform(translation)

resampled = resample(grid, composite)
myshow(resampled, 'Composite in reverse')
