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

import org.itk.simple.*;


class IterationUpdate  extends Command {

  private ImageRegistrationMethod m_Method;

  public IterationUpdate(ImageRegistrationMethod m) {
    super();
    m_Method=m;
  }

  public void execute() {
    org.itk.simple.VectorDouble pos = m_Method.getOptimizerPosition();
    System.out.format("%3d = %10.5f : [%f, %f]\n",
                      m_Method.getOptimizerIteration(),
                      m_Method.getMetricValue(),
                      pos.get(0), pos.get(1));
  }
}

class ImageRegistrationMethod1 {

  public static void main(String argv[]) {

  if ( argv.length < 3 )
    {
      System.out.format( "Usage: %s <fixedImageFilter> <movingImageFile> <outputTransformFile>\n", "ImageRegistrationMethod1");
      System.exit(-1);
    }

  org.itk.simple.ImageFileReader reader = new org.itk.simple.ImageFileReader();
  reader.setOutputPixelType( PixelIDValueEnum.sitkFloat32 );

  reader.setFileName(argv[0]);
  Image fixed = reader.execute();

  reader.setFileName(argv[1]);
  Image moving = reader.execute();

  org.itk.simple.ImageRegistrationMethod R = new  org.itk.simple.ImageRegistrationMethod();
  R.setMetricAsMeanSquares();
  double maxStep = 4.0;
  double minStep = 0.01;
  int numberOfIterations = 200;
  double relaxationFactor = 0.5;
  R.setOptimizerAsRegularStepGradientDescent( maxStep,
                                              minStep,
                                              numberOfIterations,
                                              relaxationFactor );
  R.setInitialTransform( new org.itk.simple.TranslationTransform( fixed.getDimension() ) );
  R.setInterpolator( InterpolatorEnum.sitkLinear );

  IterationUpdate cmd = new IterationUpdate(R);
  R.addCommand( EventEnum.sitkIterationEvent, cmd);

  org.itk.simple.Transform outTx = R.execute( fixed, moving );

  System.out.println("-------");
  System.out.println(outTx.toString());
  System.out.format("Optimizer stop condition: %s\n", R.getOptimizerStopConditionDescription());
  System.out.format(" Iteration: %d\n", R.getOptimizerIteration());
  System.out.format(" Metric value: %f\n", R.getMetricValue());

  outTx.writeTransform(argv[2]);

  }

}
