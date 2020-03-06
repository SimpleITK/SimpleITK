/*=========================================================================
*
*  Copyright NumFOCUS
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/

using System;
using itk.simple;

namespace itk.simple.examples
{


    class IterationUpdate : Command
    {

        private ImageRegistrationMethod m_Method;

        public IterationUpdate(ImageRegistrationMethod m)
        {
            m_Method = m;
        }

        public override void Execute()
        {
            VectorDouble pos = m_Method.GetOptimizerPosition();
            Console.WriteLine("{0:3} = {1:10.5} : [{2}, {3}]",
                              m_Method.GetOptimizerIteration(),
                              m_Method.GetMetricValue(),
                              pos[0], pos[1]);
        }
    }

    class ImageRegistrationMethod2
    {

        static void Main(string[] args)
        {

            if (args.Length < 3)
            {
                Console.WriteLine("Usage: %s <fixedImageFilter> <movingImageFile> <outputTransformFile>\n", "ImageRegistrationMethod2");
                return;
            }

            ImageFileReader reader = new ImageFileReader();
            reader.SetOutputPixelType(PixelIDValueEnum.sitkFloat32);

            reader.SetFileName(args[0]);
            Image fixedImage = reader.Execute();
            fixedImage = SimpleITK.Normalize(fixedImage);
            SimpleITK.DiscreteGaussian(fixedImage, 2.0);

            reader.SetFileName(args[1]);
            Image movingImage = reader.Execute();
            movingImage=SimpleITK.Normalize(movingImage);
            movingImage = SimpleITK.DiscreteGaussian(movingImage, 2.0);

            ImageRegistrationMethod R = new ImageRegistrationMethod();
            R.SetMetricAsJointHistogramMutualInformation();

            double learningRate = 1;
            uint  numberOfIterations = 200;
            double convergenceMinimumValue = 1e-4;
            uint convergenceWindowSize = 5;
            
            R.SetOptimizerAsGradientDescentLineSearch(learningRate,
                                                      numberOfIterations,
                                                      convergenceMinimumValue,
                                                      convergenceWindowSize);

            R.SetInitialTransform(new TranslationTransform(fixedImage.GetDimension()));
            R.SetInterpolator(InterpolatorEnum.sitkLinear);

            IterationUpdate cmd = new IterationUpdate(R);
            R.AddCommand(EventEnum.sitkIterationEvent, cmd);

            Transform outTx = R.Execute(fixedImage, movingImage);

            outTx.WriteTransform(args[2]);

        }

    }

}

