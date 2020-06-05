# =========================================================================
#
#  Copyright NumFOCUS
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0.txt
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
# =========================================================================

import argparse
import csv
import functools
import itertools
import multiprocessing
import os
import sys

import SimpleITK as sitk


def convert_image(input_file_name, output_file_name, new_width=None):
    try:
        image_file_reader = sitk.ImageFileReader()
        # only read DICOM images
        image_file_reader.SetImageIO('GDCMImageIO')
        image_file_reader.SetFileName(input_file_name)
        image_file_reader.ReadImageInformation()
        image_size = list(image_file_reader.GetSize())
        if len(image_size) == 3 and image_size[2] == 1:
            image_size[2] = 0
        image_file_reader.SetExtractSize(image_size)
        image = image_file_reader.Execute()
        if new_width:
            original_size = image.GetSize()
            original_spacing = image.GetSpacing()
            new_spacing = [(original_size[0] - 1) * original_spacing[0]
                           / (new_width - 1)] * 2
            new_size = [new_width, int((original_size[1] - 1)
                                       * original_spacing[1] / new_spacing[1])]
            image = sitk.Resample(image1=image, size=new_size,
                                  transform=sitk.Transform(),
                                  interpolator=sitk.sitkLinear,
                                  outputOrigin=image.GetOrigin(),
                                  outputSpacing=new_spacing,
                                  outputDirection=image.GetDirection(),
                                  defaultPixelValue=0,
                                  outputPixelType=image.GetPixelID())
        # If a single channel image, rescale to [0,255]. Also modify the
        # intensity values based on the photometric interpretation. If
        # MONOCHROME2 (minimum should be displayed as black) we don't need to
        # do anything, if image has MONOCRHOME1 (minimum should be displayed as
        # white) we flip # the intensities. This is a constraint imposed by ITK
        # which always assumes MONOCHROME2.
        if image.GetNumberOfComponentsPerPixel() == 1:
            image = sitk.RescaleIntensity(image, 0, 255)
            if image_file_reader.GetMetaData('0028|0004').strip() \
                    == 'MONOCHROME1':
                image = sitk.InvertIntensity(image, maximum=255)
            image = sitk.Cast(image, sitk.sitkUInt8)
        sitk.WriteImage(image, output_file_name)
        return True
    except BaseException:
        return False


def convert_images(input_file_names, output_file_names, new_width):
    MAX_PROCESSES = 15
    with multiprocessing.Pool(processes=MAX_PROCESSES) as pool:
        return pool.starmap(functools.partial(convert_image,
                                              new_width=new_width),
                            zip(input_file_names, output_file_names))


def positive_int(int_str):
    value = int(int_str)
    if value <= 0:
        raise argparse.ArgumentTypeError(
            int_str + ' is not a positive integer value')
    return value


def directory(dir_name):
    if not os.path.isdir(dir_name):
        raise argparse.ArgumentTypeError(dir_name +
                                         ' is not a valid directory name')
    return dir_name


def main(argv=None):
    parser = argparse.ArgumentParser(
        description='Convert and resize DICOM files to common image types.')
    parser.add_argument('root_of_data_directory', type=directory,
                        help='Path to the topmost directory containing data.')
    parser.add_argument(
        'output_file_extension',
        help='Image file extension, this determines output file type '
             '(e.g. png) .')
    parser.add_argument('--w', type=positive_int,
                        help='Width of converted images.')
    parser.add_argument('--od', type=directory, help='Output directory.')
    args = parser.parse_args(argv)

    input_file_names = []
    for dir_name, subdir_names, file_names in os.walk(
            args.root_of_data_directory):
        input_file_names += [os.path.join(os.path.abspath(dir_name), fname)
                             for fname in file_names]
    if args.od:
        # if all output files are written to the same directory we need them
        # to have a unique name, so use an index.
        file_names = [os.path.join(os.path.abspath(args.od), str(i))
                      for i in range(len(input_file_names))]
    else:
        file_names = input_file_names
    output_file_names = [file_name + '.' + args.output_file_extension
                         for file_name in file_names]

    res = convert_images(input_file_names, output_file_names, args.w)
    input_file_names = list(itertools.compress(input_file_names, res))
    output_file_names = list(itertools.compress(output_file_names, res))

    # save csv file mapping input and output file names.
    # using csv module and not pandas so as not to create more dependencies
    # for the examples. pandas based code is more elegant/shorter.
    dir_name = args.od if args.od else os.getcwd()
    with open(os.path.join(dir_name, 'file_names.csv'), mode='w') as fp:
        fp_writer = csv.writer(fp, delimiter=',', quotechar='"',
                               quoting=csv.QUOTE_MINIMAL)
        fp_writer.writerow(['input file name', 'output file name'])
        for data in zip(input_file_names, output_file_names):
            fp_writer.writerow(data)


if __name__ == "__main__":
    sys.exit(main())
