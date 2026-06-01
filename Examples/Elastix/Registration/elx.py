#!/usr/bin/env python

# This example demonstrates the usage of the SimpleElastix framework
# for image registration using the ElastixImageFilter.

import SimpleITK as sitk
import sys

if len(sys.argv) < 6:
    print(
        f"Usage: {sys.argv[0]} <fixedImage> <movingImage> <parameterFile> <outputImage> <outputParameterFile>"
    )
    sys.exit(1)

# Instantiate SimpleElastix
elastix_image_filter = sitk.ElastixImageFilter()

# Read input images
fixed_image = sitk.ReadImage(sys.argv[1])
moving_image = sitk.ReadImage(sys.argv[2])

# Set images
elastix_image_filter.SetFixedImage(fixed_image)
elastix_image_filter.SetMovingImage(moving_image)

# Read and set parameter map
parameter_map = sitk.ReadParameterFile(sys.argv[3])
elastix_image_filter.SetParameterMap(parameter_map)

# Enable logging to console
elastix_image_filter.LogToConsoleOn()

# Run registration
elastix_image_filter.Execute()

# Write result image
sitk.WriteImage(elastix_image_filter.GetResultImage(), sys.argv[4])

# Write parameter file
# This example only supports one parameter map and one transform parameter map
sitk.WriteParameterFile(elastix_image_filter.GetTransformParameterMaps()[0], sys.argv[5])
