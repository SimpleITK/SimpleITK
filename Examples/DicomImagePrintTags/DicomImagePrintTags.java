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

/**
 * A SimpleITK example demonstrating how to print a DICOM image's tags.
 */

import org.itk.simple.*;
import java.util.*;

public class DicomImagePrintTags {
    /**
     * A SimpleITK script that prints a DICOM image's tags.
     */
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: DicomImagePrintTags <input_file>");
            System.exit(1);
        }

        ImageFileReader reader = new ImageFileReader();

        reader.setFileName(args[0]);
        reader.loadPrivateTagsOn();

        reader.readImageInformation();

        for (String k : reader.getMetaDataKeys()) {
            System.out.println("(" + k + ") = = \"" + reader.getMetaData(k) + "\"");
        }

        VectorUInt64 size = reader.getSize();
        System.out.print("Image Size: [" + size.get(0));
        for (int i = 1; i < size.size(); i++) {
            System.out.print(", " + size.get(i));
        }
        System.out.println("]");

        System.out.println("Image PixelType: " + SimpleITK.getPixelIDValueAsString(reader.getPixelID()));
    }
}
