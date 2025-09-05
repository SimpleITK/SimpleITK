# ==========================================================================
#
#   Copyright NumFOCUS
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          http://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
# ==========================================================================*/

from pathlib import Path
import pytest
import SimpleITK as sitk


@pytest.fixture
def test_dir(tmp_path):
    """Fixture providing a temporary directory for test outputs"""
    return tmp_path


def create_test_image(img_type: int) -> sitk.Image:
    """Create a test image with specific values for testing.

    Args:
        img_type: SimpleITK pixel type (e.g., sitk.sitkInt8)

    Returns:
        SimpleITK Image with test patterns
    """
    img_size = [64] * 2
    img = sitk.Image(img_size, img_type)

    # Set positive values
    img[0, 1] = 1
    img[0, 2] = 1000
    img[0, 3] = 2**33

    # Set negative values for signed types
    if img_type in [sitk.sitkInt8, sitk.sitkInt16, sitk.sitkInt32, sitk.sitkInt64]:
        img[1, 0] = -1
        img[2, 0] = -100
        img[3, 0] = -(2**34)

    return img


def test_write_pathlib(test_dir):
    """Test writing images using pathlib.Path objects"""
    # Test single image write
    img = sitk.Image([32, 32], sitk.sitkUInt8)
    img[10, 10] = 13
    path = test_dir / "write_pathlib.mha"

    sitk.WriteImage(img, path)
    out = sitk.ReadImage(path)
    assert sitk.Hash(img) == sitk.Hash(out), "Image hash mismatch after read/write"

    # Test image series write
    z_size = 3
    path_list = [test_dir / f"write_pathlib_{i}.mha" for i in range(z_size)]
    img = sitk.Image([32, 32, z_size], sitk.sitkUInt8)
    sitk.WriteImage(img, path_list)

    # Verify all files were created
    for path in path_list:
        assert path.exists(), f"Expected file {path} was not created"


def test_write_procedure(test_dir):
    """Test basic functionality of ImageRead and ImageWrite procedures"""
    # Test single slice image with compression
    img = sitk.Image([32, 32], sitk.sitkUInt8)
    output_path = test_dir / "test_write_1.tiff"
    sitk.WriteImage(
        img,
        output_path,
        useCompression=True,
        compressor="DEFLATE",
        compressionLevel=1
    )
    rimg = sitk.ReadImage(output_path)
    assert sitk.Hash(img) == sitk.Hash(rimg), "Image hash mismatch after TIFF compression"

    # Test JPEG write/read
    output_path = test_dir / "test_write_2.jpg"
    sitk.WriteImage(img, output_path, True, 1)
    rimg = sitk.ReadImage(output_path, imageIO="JPEGImageIO")
    # Note: Don't check hash for JPEG as it's lossy compression

    # Test image series write/read
    img = sitk.Image([32, 32, 4], sitk.sitkUInt8)
    series_paths = [test_dir / f"series_{i}.tif" for i in range(img.GetSize()[2])]
    sitk.WriteImage(img, series_paths, compressionLevel=90)
    read_img = sitk.ReadImage(series_paths, imageIO="TIFFImageIO")
    assert img.GetSize() == read_img.GetSize(), "Image size changed after series write/read"

    with pytest.raises(RuntimeError):
        sitk.WriteImage(img, "this.isafilenamewithnoimageio")




def test_path_type(test_dir):
    """Test functionality of PathType object wrapping"""
    img = sitk.Image([32, 32], sitk.sitkUInt8)
    writer = sitk.ImageFileWriter()

    # Test Path object
    out_path = test_dir / "test_path_type.mha"
    assert not out_path.exists(), "Test file should not exist before writing"
    writer.SetFileName(out_path)
    assert isinstance(writer.GetFileName(), str), "GetFileName should return string"
    writer.Execute(img)
    assert out_path.exists(), "File should exist after writing"

    # Test string path
    out_path = test_dir / "test_path_type_str.mha"
    writer.SetFileName(str(out_path))
    assert isinstance(writer.GetFileName(), str), "GetFileName should return string"
    writer.Execute(img)
    assert out_path.exists(), "File should exist after writing"

    # Test series writing with Path objects
    writer = sitk.ImageSeriesWriter()
    z_size = 3
    out_path_series = [test_dir / f"test_path_type_{i}.mha" for i in range(z_size)]
    img = sitk.Image([32, 32, z_size], sitk.sitkUInt8)
    writer.SetFileNames(out_path_series)

    assert all(isinstance(p, str) for p in writer.GetFileNames()), \
        "All file names should be strings"

    writer.Execute(img)
    for p in out_path_series:
        assert p.exists(), f"Series file {p} should exist"


def test_reader_kwargs(test_dir):
    """Test keyword arguments in ReadImage method"""
    # Create test image series
    z_size = 3
    img = sitk.Image([32, 32, z_size], sitk.sitkUInt16)
    for z in range(z_size):
        img[:, :, z] = 1 + z * 5

    # Write series as PNG files
    file_paths = [test_dir / f"test_reader_kwargs_{z}.png" for z in range(z_size)]
    sitk.WriteImage(img, file_paths)

    # Test reverse order reading
    reversed_img = sitk.ReadImage(
        file_paths,
        reverseOrder=True,
        spacingWarningRelThreshold=0.0
    )

    # Verify slice order is reversed
    for z in range(z_size):
        orig_hash = sitk.Hash(img[:, :, z])
        rev_hash = sitk.Hash(reversed_img[:, :, -z-1])
        assert orig_hash == rev_hash, f"Slice mismatch at position {z}"

    # Test invalid keyword argument
    with pytest.raises(TypeError):
        sitk.ReadImage(file_paths, nonsenseKwarg=True)


def verify_read_write(img: sitk.Image, output_path: Path):
    """Verify image read/write operation maintains image integrity.

    Args:
        img: Original image to write
        output_path: Path where to write the image
    """
    base_hash = sitk.Hash(img)
    sitk.WriteImage(img, output_path)
    in_img = sitk.ReadImage(output_path)

    assert base_hash == sitk.Hash(in_img), "Image hash changed after read/write"
    assert img.GetPixelID() == in_img.GetPixelID(), "Pixel type changed after read/write"


@pytest.mark.parametrize("extension,pixel_type", [
    ("mha", sitk.sitkUInt64),
    ("mha", sitk.sitkInt64),
    ("nrrd", sitk.sitkUInt64),
    ("nrrd", sitk.sitkInt64),
    ("nii", sitk.sitkUInt64),
    ("nii", sitk.sitkInt64),
])
def test_read_write_types(test_dir, extension, pixel_type):
    """Test reading and writing images with different types and formats"""
    fname = test_dir / f"test64.{extension}"
    img = create_test_image(pixel_type)
    verify_read_write(img, fname)
