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

public class elx {
    public static void main(String[] args) {
        if (args.length < 5) {
            System.out.println("Usage: elx <fixedImage> <movingImage> <parameterFile> <outputImage> <outputParameterFile>");
            System.exit(1);
        }

        // Instantiate SimpleElastix
        ElastixImageFilter elastixImageFilter = new ElastixImageFilter();

        // Read input
        elastixImageFilter.setFixedImage(SimpleITK.readImage(args[0]));
        elastixImageFilter.setMovingImage(SimpleITK.readImage(args[1]));
        elastixImageFilter.setParameterMap(SimpleITK.readParameterFile(args[2]));
        elastixImageFilter.logToConsoleOn();

        // Run registration
        elastixImageFilter.execute();

        // Write result image
        SimpleITK.writeImage(elastixImageFilter.getResultImage(), args[3]);

        // Write parameter file. This example only supports one parameter map and one transform parameter map.
        SimpleITK.writeParameterFile(elastixImageFilter.getTransformParameterMaps().get(0), args[4]);
    }
}
