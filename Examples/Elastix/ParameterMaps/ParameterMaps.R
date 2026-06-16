#!/usr/bin/env Rscript

# Check command line arguments
args <- commandArgs(TRUE)
if (length(args) < 2) {
    cat("Usage: ParameterMaps <fixedImage> <movingImage> [outputPrefix]\n")
    quit(status = 1)
}

# Load SimpleITK
library(SimpleITK)

# Read input images
fixedImage <- ReadImage(args[1])
movingImage <- ReadImage(args[2])

cat("SimpleITK Elastix Parameter Maps Example\n")
cat(paste(rep("=", 60), collapse = ""), "\n")

# Create ElastixImageFilter for parameter map operations
elastixImageFilter <- ElastixImageFilter()

#START_DEFAULT_PARAMETER_MAP
# Get a default parameter map for a common registration type
parameterMap <- elastixImageFilter$GetDefaultParameterMap("translation")

# Print parameter map to see its contents
elastixImageFilter$PrintParameterMap(parameterMap)
#END_DEFAULT_PARAMETER_MAP

#START_MODIFY_PARAMETER_MAP
# Modify parameter map entries
# Values are character vectors (representing VectorString in C++)
parameterMap$set("Transform", c("AffineTransform"))
parameterMap$set("MaximumNumberOfIterations", c("512"))
parameterMap$set("NumberOfSpatialSamples", c("8192"))
#END_MODIFY_PARAMETER_MAP

#START_MULTI_STAGE_REGISTRATION
# Multi-stage registration: translation -> affine -> bspline
elastixImageFilter$SetFixedImage(fixedImage)
elastixImageFilter$SetMovingImage(movingImage)

elastixImageFilter$SetParameterMap(elastixImageFilter$GetDefaultParameterMap("translation"))
elastixImageFilter$AddParameterMap(elastixImageFilter$GetDefaultParameterMap("affine"))

bsplineMap <- elastixImageFilter$GetDefaultParameterMap("bspline")
# Modify bspline parameter map using set() method
bsplineMap$set("FinalGridSpacingInPhysicalUnits", c("8.0"))
elastixImageFilter$AddParameterMap(bsplineMap)

elastixImageFilter$LogToConsoleOff()
resultImage <- elastixImageFilter$Execute()

# Retrieve transform parameter maps from the result
transformParameterMaps <- elastixImageFilter$GetTransformParameterMaps()
#END_MULTI_STAGE_REGISTRATION

#START_READ_WRITE_PARAMETER_MAP
# Write a parameter map to a file
elastixImageFilter$WriteParameterFile(parameterMap, "parameters.txt")

# Read a parameter map from a file
readMap <- elastixImageFilter$ReadParameterFile("parameters.txt")
#END_READ_WRITE_PARAMETER_MAP

# Write results if output prefix provided
if (length(args) > 2) {
    outputPrefix <- args[3]
    for (i in 0:(transformParameterMaps$size() - 1L)) {
        filename <- sprintf("%s_TransformParameters_%d.txt", outputPrefix, i)
        elastixImageFilter$WriteParameterFile(transformParameterMaps$"__getitem__"(i), filename)
    }
    WriteImage(resultImage, paste0(outputPrefix, ".nii"))
}
