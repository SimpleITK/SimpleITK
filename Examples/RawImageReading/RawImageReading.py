#!/usr/bin/env python
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
import os
import tempfile

import SimpleITK as sitk


def read_raw(binary_file_name, image_size, sitk_pixel_type, image_spacing=None,
             image_origin=None, big_endian=False):
    """
    Read a raw binary scalar image.

    Parameters
    ----------
    binary_file_name (str): Raw, binary image file content.
    image_size (tuple like): Size of image (e.g. [2048,2048])
    sitk_pixel_type (SimpleITK pixel type: Pixel type of data (e.g.
        sitk.sitkUInt16).
    image_spacing (tuple like): Optional image spacing, if none given assumed
        to be [1]*dim.
    image_origin (tuple like): Optional image origin, if none given assumed to
        be [0]*dim.
    big_endian (bool): Optional byte order indicator, if True big endian, else
        little endian.

    Returns
    -------
    SimpleITK image or None if fails.
    """

    pixel_dict = {sitk.sitkUInt8: 'MET_UCHAR',
                  sitk.sitkInt8: 'MET_CHAR',
                  sitk.sitkUInt16: 'MET_USHORT',
                  sitk.sitkInt16: 'MET_SHORT',
                  sitk.sitkUInt32: 'MET_UINT',
                  sitk.sitkInt32: 'MET_INT',
                  sitk.sitkUInt64: 'MET_ULONG_LONG',
                  sitk.sitkInt64: 'MET_LONG_LONG',
                  sitk.sitkFloat32: 'MET_FLOAT',
                  sitk.sitkFloat64: 'MET_DOUBLE'}
    direction_cosine = ['1 0 0 1', '1 0 0 0 1 0 0 0 1',
                        '1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1']
    dim = len(image_size)
    header = ['ObjectType = Image\n'.encode(),
              (f'NDims = {dim}\n').encode(),
              ('DimSize = ' + ' '.join([str(v) for v in image_size]) + '\n')
              .encode(),
              ('ElementSpacing = ' + (' '.join([str(v) for v in image_spacing])
                                      if image_spacing else ' '.join(
                  ['1'] * dim)) + '\n').encode(),
              ('Offset = ' + (
                  ' '.join([str(v) for v in image_origin]) if image_origin
                  else ' '.join(['0'] * dim) + '\n')).encode(),
              ('TransformMatrix = ' + direction_cosine[dim - 2] + '\n')
              .encode(),
              ('ElementType = ' + pixel_dict[sitk_pixel_type] + '\n').encode(),
              'BinaryData = True\n'.encode(),
              ('BinaryDataByteOrderMSB = ' + str(big_endian) + '\n').encode(),
              # ElementDataFile must be the last entry in the header
              ('ElementDataFile = ' + os.path.abspath(
                  binary_file_name) + '\n').encode()]
    fp = tempfile.NamedTemporaryFile(suffix='.mhd', delete=False)

    print(header)

    # Not using the tempfile with a context manager and auto-delete
    # because on windows we can't open the file a second time for ReadImage.
    fp.writelines(header)
    fp.close()
    img = sitk.ReadImage(fp.name)
    os.remove(fp.name)
    return img


parser = argparse.ArgumentParser()
parser.add_argument('raw_file_name', help='path to raw binary image file')
parser.add_argument('out_file_name',
                    help='output file name when image read as little endian')
parser.add_argument("big_endian", type=lambda v: v.lower() in {"1", "true"},
                    help="\'false\' for little ending or \'true\'for big "
                    "endian")
parser.add_argument('sitk_pixel_type',
                    help="SimpleITK pixel type (e.g. sitk.sitkUInt16)")
parser.add_argument('sz', nargs='+', help="image size, x,y,...",
                    type=int)
args = parser.parse_args()

string_to_pixelType = {"sitkUInt8": sitk.sitkUInt8,
                       "sitkInt8": sitk.sitkInt8,
                       "sitkUInt16": sitk.sitkUInt16,
                       "sitkInt16": sitk.sitkInt16,
                       "sitkUInt32": sitk.sitkUInt32,
                       "sitkInt32": sitk.sitkInt32,
                       "sitkUInt64": sitk.sitkUInt64,
                       "sitkInt64": sitk.sitkInt64,
                       "sitkFloat32": sitk.sitkFloat32,
                       "sitkFloat64": sitk.sitkFloat64}

# Read the image using both big and little endian
image = read_raw(binary_file_name=args.raw_file_name,
                 image_size=args.sz,
                 sitk_pixel_type=string_to_pixelType[args.sitk_pixel_type],
                 big_endian=args.big_endian)

sitk.WriteImage(image, args.out_file_name)

if "SITK_NOSHOW" not in os.environ:
    sitk.Show(image, 'raw converted')
