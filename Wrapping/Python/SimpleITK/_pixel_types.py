# ========================================================================
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
# ========================================================================

"""
Pixel type classification for SimpleITK.

This module provides constants and functions to classify SimpleITK pixel types
into categories: Basic, Vector, and Label types.
"""

from SimpleITK.SimpleITK import (
    sitkUnknown,
    sitkUInt8,
    sitkInt8,
    sitkUInt16,
    sitkInt16,
    sitkUInt32,
    sitkInt32,
    sitkUInt64,
    sitkInt64,
    sitkFloat32,
    sitkFloat64,
    sitkComplexFloat32,
    sitkComplexFloat64,
    sitkVectorUInt8,
    sitkVectorInt8,
    sitkVectorUInt16,
    sitkVectorInt16,
    sitkVectorUInt32,
    sitkVectorInt32,
    sitkVectorUInt64,
    sitkVectorInt64,
    sitkVectorFloat32,
    sitkVectorFloat64,
    sitkLabelUInt8,
    sitkLabelUInt16,
    sitkLabelUInt32,
    sitkLabelUInt64,
)

# Basic pixel types - scalar pixel types including integers, floats, and complex
# Filter out any sitkUnknown values in case some types are not instantiated
BASIC_PIXEL_IDS = frozenset(
    pixel_id for pixel_id in [
        sitkUInt8,
        sitkInt8,
        sitkUInt16,
        sitkInt16,
        sitkUInt32,
        sitkInt32,
        sitkUInt64,
        sitkInt64,
        sitkFloat32,
        sitkFloat64,
        sitkComplexFloat32,
        sitkComplexFloat64,
    ]
    if pixel_id != sitkUnknown
)

# Vector pixel types - multi-component pixel types
# Filter out any sitkUnknown values in case some types are not instantiated
VECTOR_PIXEL_IDS = frozenset(
    pixel_id for pixel_id in [
        sitkVectorUInt8,
        sitkVectorInt8,
        sitkVectorUInt16,
        sitkVectorInt16,
        sitkVectorUInt32,
        sitkVectorInt32,
        sitkVectorUInt64,
        sitkVectorInt64,
        sitkVectorFloat32,
        sitkVectorFloat64,
    ]
    if pixel_id != sitkUnknown
)

# Label pixel types - RLE encoded label types
# Filter out any sitkUnknown values in case some types are not instantiated
LABEL_PIXEL_IDS = frozenset(
    pixel_id for pixel_id in [
        sitkLabelUInt8,
        sitkLabelUInt16,
        sitkLabelUInt32,
        sitkLabelUInt64,
    ]
    if pixel_id != sitkUnknown
)


def is_basic(pixel_id: int) -> bool:
    """
    Check if a pixel ID is a basic (scalar) type.

    Basic pixel types include unsigned and signed integers, floating-point,
    and complex floating-point types.

    Parameters
    ----------
    pixel_id : int
        A SimpleITK PixelIDValueEnum value.

    Returns
    -------
    bool
        True if the pixel ID is a basic type, False otherwise.
    """
    return pixel_id in BASIC_PIXEL_IDS


def is_vector(pixel_id: int) -> bool:
    """
    Check if a pixel ID is a vector (multi-component) type.

    Vector pixel types represent multi-component pixels where each pixel
    contains a fixed-size vector of scalar values.

    Parameters
    ----------
    pixel_id : int
        A SimpleITK PixelIDValueEnum value.

    Returns
    -------
    bool
        True if the pixel ID is a vector type, False otherwise.

    """
    return pixel_id in VECTOR_PIXEL_IDS


def is_label(pixel_id: int) -> bool:
    """
    Check if a pixel ID is a label type.

    Label pixel types use Run-Length Encoding (RLE) for efficient storage
    of label maps, commonly used for segmentation masks.

    Parameters
    ----------
    pixel_id : int
        A SimpleITK PixelIDValueEnum value.

    Returns
    -------
    bool
        True if the pixel ID is a label type, False otherwise.

    """
    return pixel_id in LABEL_PIXEL_IDS



__all__ = [
    'BASIC_PIXEL_IDS',
    'VECTOR_PIXEL_IDS',
    'LABEL_PIXEL_IDS',
    'is_basic',
    'is_vector',
    'is_label'
]
