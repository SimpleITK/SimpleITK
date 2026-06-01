#!/usr/bin/env lua

-- Check command line arguments
if #arg < 2 then
    print("Usage: ParameterMaps <fixedImage> <movingImage> [outputPrefix]")
    os.exit(1)
end

-- Load SimpleITK
SimpleITK = require("SimpleITK")

-- Read input images
fixedImage = SimpleITK.ReadImage(arg[1])
movingImage = SimpleITK.ReadImage(arg[2])

print("SimpleITK Elastix Parameter Maps Example")
print(string.rep("=", 60))

--START_DEFAULT_PARAMETER_MAP
-- Get a default parameter map for a common registration type
parameterMap = SimpleITK.GetDefaultParameterMap("translation")

-- Print parameter map to see its contents
SimpleITK.PrintParameterMap(parameterMap)
--END_DEFAULT_PARAMETER_MAP

--START_MODIFY_PARAMETER_MAP
-- Modify parameter map entries (values are VectorString)
transformValue = SimpleITK.VectorString()
transformValue:push_back("AffineTransform")
parameterMap:set("Transform", transformValue)

iterValue = SimpleITK.VectorString()
iterValue:push_back("512")
parameterMap:set("MaximumNumberOfIterations", iterValue)

samplesValue = SimpleITK.VectorString()
samplesValue:push_back("8192")
parameterMap:set("NumberOfSpatialSamples", samplesValue)
--END_MODIFY_PARAMETER_MAP

--START_MULTI_STAGE_REGISTRATION
-- Multi-stage registration: translation -> affine -> bspline
elastixImageFilter = SimpleITK.ElastixImageFilter()
elastixImageFilter:SetFixedImage(fixedImage)
elastixImageFilter:SetMovingImage(movingImage)

elastixImageFilter:SetParameterMap(SimpleITK.GetDefaultParameterMap("translation"))
elastixImageFilter:AddParameterMap(SimpleITK.GetDefaultParameterMap("affine"))

bsplineMap = SimpleITK.GetDefaultParameterMap("bspline")
gridSpacing = SimpleITK.VectorString()
gridSpacing:push_back("8.0")
bsplineMap:set("FinalGridSpacingInPhysicalUnits", gridSpacing)
elastixImageFilter:AddParameterMap(bsplineMap)

elastixImageFilter:LogToConsoleOff()
resultImage = elastixImageFilter:Execute()

-- Retrieve transform parameter maps from the result
transformParameterMaps = elastixImageFilter:GetTransformParameterMaps()
--END_MULTI_STAGE_REGISTRATION

--START_READ_WRITE_PARAMETER_MAP
-- Write a parameter map to a file
SimpleITK.WriteParameterFile(parameterMap, "parameters.txt")

-- Read a parameter map from a file
readMap = SimpleITK.ReadParameterFile("parameters.txt")
--END_READ_WRITE_PARAMETER_MAP

-- Write results if output prefix provided
if #arg > 2 then
    outputPrefix = arg[3]
    for i = 0, transformParameterMaps:size() - 1 do
        filename = string.format("%s_TransformParameters_%d.txt", outputPrefix, i)
        SimpleITK.WriteParameterFile(transformParameterMaps[i], filename)
    end
    SimpleITK.WriteImage(resultImage, outputPrefix .. ".nii")
end
