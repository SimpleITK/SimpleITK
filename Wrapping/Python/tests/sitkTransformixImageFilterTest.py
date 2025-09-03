from __future__ import print_function
import sys
import pytest

import SimpleITK as sitk


def test_TransformixImageFilter_GetDeformationField():
    """Test the TransformixImageFilter's deformation field computation.

    This test:
    1. Creates simple fixed and moving images with identical patterns but different origins
    2. Performs a basic registration using ElastixImageFilter
    3. Uses TransformixImageFilter to compute the deformation field
    4. Verifies the deformation field is computed correctly
    """
    # Setup test images
    fixedImage = sitk.Image(4, 4, sitk.sitkFloat32)
    movingImage = sitk.Image(4, 4, sitk.sitkFloat32)

    # Set up a simple pattern
    fixedImage[0, 0] = movingImage[0, 0] = 1
    fixedImage[0, 1] = movingImage[0, 1] = 1
    fixedImage[1, 0] = movingImage[1, 0] = 1
    fixedImage[1, 1] = movingImage[1, 1] = 1

    movingImage.SetOrigin((1, 1))

    # Perform dummy registration
    elastixImageFilter = sitk.ElastixImageFilter()
    elastixImageFilter.SetParameter("MaximumNumberOfIterations", "10")
    elastixImageFilter.SetFixedImage(fixedImage)
    elastixImageFilter.SetMovingImage(movingImage)
    elastixImageFilter.Execute()

    # Set up transformix filter
    transformixImageFilter = sitk.TransformixImageFilter()
    transformixImageFilter.SetTransformParameterMap(
        elastixImageFilter.GetTransformParameterMap()
    )
    transformixImageFilter.ComputeDeformationFieldOn()

    # Set moving image (required to avoid "Input MovingImage is required but not set" error)
    transformixImageFilter.SetMovingImage(movingImage)

    # Execute and get deformation field
    transformixImageFilter.Execute()
    deformationField = transformixImageFilter.GetDeformationField()

    # Verify the deformation field
    assert deformationField is not None, "Deformation field should not be None"
    assert deformationField.GetDimension() == 2, "Expected 2D deformation field"
    assert deformationField.GetNumberOfComponentsPerPixel() == 2, "Expected 2 components per pixel (x,y displacement)"
    assert deformationField.GetSize() == (4, 4), "Deformation field should match input image size"
