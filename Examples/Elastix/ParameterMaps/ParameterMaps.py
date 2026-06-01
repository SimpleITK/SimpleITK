#!/usr/bin/env python

import sys
import SimpleITK as sitk

if len(sys.argv) < 3:
    print("Usage: ParameterMaps <fixedImage> <movingImage> [outputImage]")
    sys.exit(1)

# Read input images
fixed_image = sitk.ReadImage(sys.argv[1])
moving_image = sitk.ReadImage(sys.argv[2])

print("SimpleITK Elastix Parameter Maps Example")
print("=" * 60)

#START_DEFAULT_PARAMETER_MAP
# Get a default parameter map for a common registration type
parameter_map = sitk.GetDefaultParameterMap("translation")

# Print parameter map to see its contents
sitk.PrintParameterMap(parameter_map)
#END_DEFAULT_PARAMETER_MAP

#START_MODIFY_PARAMETER_MAP
# Modify parameter map entries (values are lists of strings)
parameter_map["Transform"] = ["AffineTransform"]
parameter_map["MaximumNumberOfIterations"] = ["512"]
parameter_map["NumberOfSpatialSamples"] = ["8192"]
#END_MODIFY_PARAMETER_MAP

#START_MULTI_STAGE_REGISTRATION
# Multi-stage registration: translation -> affine -> bspline
elastix_image_filter = sitk.ElastixImageFilter()
elastix_image_filter.SetFixedImage(fixed_image)
elastix_image_filter.SetMovingImage(moving_image)

elastix_image_filter.SetParameterMap(sitk.GetDefaultParameterMap("translation"))
elastix_image_filter.AddParameterMap(sitk.GetDefaultParameterMap("affine"))

bspline_map = sitk.GetDefaultParameterMap("bspline")
bspline_map["FinalGridSpacingInPhysicalUnits"] = ["8.0"]
elastix_image_filter.AddParameterMap(bspline_map)

elastix_image_filter.LogToConsoleOff()
result_image = elastix_image_filter.Execute()

# Retrieve transform parameter maps from the result
transform_parameter_maps = elastix_image_filter.GetTransformParameterMaps()
#END_MULTI_STAGE_REGISTRATION

#START_READ_WRITE_PARAMETER_MAP
# Write a parameter map to a file
sitk.WriteParameterFile(parameter_map, "parameters.txt")

# Read a parameter map from a file
parameter_map = sitk.ReadParameterFile("parameters.txt")
#END_READ_WRITE_PARAMETER_MAP

# Write results if output path provided
if len(sys.argv) > 3:
    output_dir = sys.argv[3]
    for i, tpm in enumerate(transform_parameter_maps):
        filename = f"{output_dir}_TransformParameters_{i}.txt"
        sitk.WriteParameterFile(tpm, filename)
    sitk.WriteImage(result_image, f"{output_dir}.nii")
print("Example completed successfully!")
print("=" * 60)
