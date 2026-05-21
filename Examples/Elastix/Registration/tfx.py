#!/usr/bin/env python

import SimpleITK as sitk
import sys

if len(sys.argv) < 4:
    print(f"Usage: {sys.argv[0]} <inputImage> <parameterFile> <outputImage>")
    sys.exit(1)

# Instantiate transformix
transformix_image_filter = sitk.TransformixImageFilter()

# Enable logging to console
transformix_image_filter.LogToConsoleOn()

# Read input image
moving_image = sitk.ReadImage(sys.argv[1])
transformix_image_filter.SetMovingImage(moving_image)

# Read and set transform parameter map
transform_parameter_map = sitk.ReadParameterFile(sys.argv[2])
transformix_image_filter.SetTransformParameterMap(transform_parameter_map)

# Run warp
transformix_image_filter.Execute()

# Write result image
sitk.WriteImage(transformix_image_filter.GetResultImage(), sys.argv[3])
