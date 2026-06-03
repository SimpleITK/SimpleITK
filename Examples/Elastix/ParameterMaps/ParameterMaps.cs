using System;
using itk.simple;

namespace itk.simple.examples
{
    class ParameterMaps
    {
        static void Main(string[] args)
        {
            if (args.Length < 2)
            {
                Console.WriteLine("Usage: ParameterMaps <fixedImage> <movingImage> [outputPrefix]");
                return;
            }

            // Read input images
            Image fixedImage = SimpleITK.ReadImage(args[0]);
            Image movingImage = SimpleITK.ReadImage(args[1]);

            Console.WriteLine("SimpleITK Elastix Parameter Maps Example");
            Console.WriteLine(new string('=', 60));

            //START_DEFAULT_PARAMETER_MAP
            // Get a default parameter map for a common registration type
            var parameterMap = SimpleITK.GetDefaultParameterMap("translation");

            // Print parameter map to see its contents
            SimpleITK.PrintParameterMap(parameterMap);
            //END_DEFAULT_PARAMETER_MAP

            //START_MODIFY_PARAMETER_MAP
            // Modify parameter map entries (values are VectorString)
            VectorString transformValue = new VectorString();
            transformValue.Add("AffineTransform");
            parameterMap["Transform"] = transformValue;

            VectorString iterValue = new VectorString();
            iterValue.Add("512");
            parameterMap["MaximumNumberOfIterations"] = iterValue;

            VectorString samplesValue = new VectorString();
            samplesValue.Add("8192");
            parameterMap["NumberOfSpatialSamples"] = samplesValue;
            //END_MODIFY_PARAMETER_MAP

            //START_MULTI_STAGE_REGISTRATION
            // Multi-stage registration: translation -> affine -> bspline
            ElastixImageFilter elastixImageFilter = new ElastixImageFilter();
            elastixImageFilter.SetFixedImage(fixedImage);
            elastixImageFilter.SetMovingImage(movingImage);

            elastixImageFilter.SetParameterMap(SimpleITK.GetDefaultParameterMap("translation"));
            elastixImageFilter.AddParameterMap(SimpleITK.GetDefaultParameterMap("affine"));

            var bsplineMap = SimpleITK.GetDefaultParameterMap("bspline");
            VectorString gridSpacing = new VectorString();
            gridSpacing.Add("8.0");
            bsplineMap["FinalGridSpacingInPhysicalUnits"] = gridSpacing;
            elastixImageFilter.AddParameterMap(bsplineMap);

            elastixImageFilter.LogToConsoleOff();
            Image resultImage = elastixImageFilter.Execute();

            // Retrieve transform parameter maps from the result
            VectorOfParameterMap transformParameterMaps = elastixImageFilter.GetTransformParameterMaps();
            //END_MULTI_STAGE_REGISTRATION

            //START_READ_WRITE_PARAMETER_MAP
            // Write a parameter map to a file
            SimpleITK.WriteParameterFile(parameterMap, "parameters.txt");

            // Read a parameter map from a file
            var readMap = SimpleITK.ReadParameterFile("parameters.txt");
            //END_READ_WRITE_PARAMETER_MAP

            // Write results if output prefix provided
            if (args.Length > 2)
            {
                string outputPrefix = args[2];
                for (int i = 0; i < transformParameterMaps.Count; i++)
                {
                    string filename = string.Format("{0}_TransformParameters_{1}.txt", outputPrefix, i);
                    SimpleITK.WriteParameterFile(transformParameterMaps[i], filename);
                }
                SimpleITK.WriteImage(resultImage, string.Format("{0}.nii", outputPrefix));
            }
        }
    }
}
