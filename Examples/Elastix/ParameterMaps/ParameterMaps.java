import org.itk.simple.*;

public class ParameterMaps {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: ParameterMaps <fixedImage> <movingImage> [outputPrefix]");
            return;
        }

        // Read input images
        Image fixedImage = SimpleITK.readImage(args[0]);
        Image movingImage = SimpleITK.readImage(args[1]);

        System.out.println("SimpleITK Elastix Parameter Maps Example");
        System.out.println("============================================================");

        //START_DEFAULT_PARAMETER_MAP
        // Get a default parameter map for a common registration type
        ParameterMap parameterMap = SimpleITK.getDefaultParameterMap("translation");

        // Print parameter map to see its contents
        SimpleITK.printParameterMap(parameterMap);
        //END_DEFAULT_PARAMETER_MAP

        //START_MODIFY_PARAMETER_MAP
        // Modify parameter map entries (values are VectorString)
        VectorString transformValue = new VectorString();
        transformValue.add("AffineTransform");
        parameterMap.put("Transform", transformValue);

        VectorString iterValue = new VectorString();
        iterValue.add("512");
        parameterMap.put("MaximumNumberOfIterations", iterValue);

        VectorString samplesValue = new VectorString();
        samplesValue.add("8192");
        parameterMap.put("NumberOfSpatialSamples", samplesValue);
        //END_MODIFY_PARAMETER_MAP

        //START_MULTI_STAGE_REGISTRATION
        // Multi-stage registration: translation -> affine -> bspline
        ElastixImageFilter elastixImageFilter = new ElastixImageFilter();
        elastixImageFilter.setFixedImage(fixedImage);
        elastixImageFilter.setMovingImage(movingImage);

        elastixImageFilter.setParameterMap(SimpleITK.getDefaultParameterMap("translation"));
        elastixImageFilter.addParameterMap(SimpleITK.getDefaultParameterMap("affine"));

        ParameterMap bsplineMap = SimpleITK.getDefaultParameterMap("bspline");
        VectorString gridSpacing = new VectorString();
        gridSpacing.add("8.0");
        bsplineMap.put("FinalGridSpacingInPhysicalUnits", gridSpacing);
        elastixImageFilter.addParameterMap(bsplineMap);

        elastixImageFilter.logToConsoleOff();
        Image resultImage = elastixImageFilter.execute();

        // Retrieve transform parameter maps from the result
        VectorOfParameterMap transformParameterMaps = elastixImageFilter.getTransformParameterMaps();
        //END_MULTI_STAGE_REGISTRATION

        //START_READ_WRITE_PARAMETER_MAP
        // Write a parameter map to a file
        SimpleITK.writeParameterFile(parameterMap, "parameters.txt");

        // Read a parameter map from a file
        ParameterMap readMap = SimpleITK.readParameterFile("parameters.txt");
        //END_READ_WRITE_PARAMETER_MAP

        // Write results if output prefix provided
        if (args.length > 2) {
            String outputPrefix = args[2];
            for (int i = 0; i < transformParameterMaps.size(); i++) {
                String filename = outputPrefix + "_TransformParameters_" + i + ".txt";
                SimpleITK.writeParameterFile(transformParameterMaps.get(i), filename);
            }
            SimpleITK.writeImage(resultImage, outputPrefix + ".nii");
        }
    }
}
