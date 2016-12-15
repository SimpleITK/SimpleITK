/*=========================================================================
 *
 *  Copyright Insight Software Consortium
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

class MyCommand  extends Command {

  private ProcessObject m_ProcessObject;

  public MyCommand(ProcessObject po) {
    super();
    m_ProcessObject=po;
  }

  public void execute() {
    double progress = m_ProcessObject.getProgress();
    System.out.format("%s Progress: %f\n", m_ProcessObject.getName(), progress);
  }
}

class FilterProgressReporting {

  public static void main(String argv[]) {
    if ( argv.length < 3 ) {
      System.out.format("Usage: java %s <input> <variance> <output>", "FilterProgressReporting" );
      System.exit(-1);
    }

      org.itk.simple.ImageFileReader reader = new org.itk.simple.ImageFileReader();
      reader.setFileName(argv[0]);
      Image img = reader.execute();

      DiscreteGaussianImageFilter filter = new DiscreteGaussianImageFilter();
      filter.setVariance(Double.valueOf( argv[1] ).doubleValue());

      MyCommand cmd = new MyCommand(filter);
      filter.addCommand(EventEnum.sitkProgressEvent, cmd);

      Image blurredImg = filter.execute(img);

      CastImageFilter caster = new CastImageFilter();
      caster.setOutputPixelType(img.getPixelID());
      Image castImg = caster.execute(blurredImg);

      ImageFileWriter writer = new ImageFileWriter();
      writer.setFileName(argv[2]);

      writer.execute(castImg);

    }

}
