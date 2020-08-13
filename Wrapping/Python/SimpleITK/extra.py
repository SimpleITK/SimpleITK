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

from SimpleITK.SimpleITK import *
from SimpleITK.SimpleITK import _GetMemoryViewFromImage
from SimpleITK.SimpleITK import _SetImageFromArray

from typing import List, Union


def Resample(image1, *args, **kwargs):
    """
     Resample ( Image image1,
                Transform transform = itk::simple::Transform(),
                InterpolatorEnum interpolator = itk::simple::sitkLinear,
                double defaultPixelValue = 0.0,
                PixelIDValueEnum outputPixelType = itk::simple::sitkUnknown,
                bool useNearestNeighborExtrapolator = false);

     Resample ( Image image1,
                Image referenceImage,
                Transform transform = itk::simple::Transform(),
                InterpolatorEnum interpolator = itk::simple::sitkLinear,
                double defaultPixelValue = 0.0,
                PixelIDValueEnum outputPixelType = sitkUnknown,
                bool useNearestNeighborExtrapolator = false);

     Resample ( const Image& image1,
                VectorUInt32 size,
                Transform transform = itk::simple::Transform(),
                InterpolatorEnum interpolator = itk::simple::sitkLinear,
                VectorDouble outputOrigin = std::vector<double>(3, 0.0),
                VectorDouble outputSpacing = std::vector<double>(3, 1.0),
                VectorDouble outputDirection = std::vector<double>(),
                double defaultPixelValue = 0.0,
                PixelIDValueEnum outputPixelType = sitkUnknown,
                bool useNearestNeighborExtrapolator = false);

     itk::simple::ResampleImageFilter procedural interface.

     This is a custom overloaded python method, which fully supports the 3 signatures with positional and keyword
      arguments. The second positional parameters without a default value are used to determine which overloaded
      procedure signature to invoke.

    """

    def _r_image(referenceImage,
                 transform=Transform(),
                 interpolator=sitkLinear,
                 defaultPixelValue=0.0,
                 outputPixelType=sitkUnknown,
                 useNearestNeighborExtrapolator=False):
        resampler = ResampleImageFilter()
        resampler.SetReferenceImage(referenceImage)
        resampler.SetTransform(transform)
        resampler.SetInterpolator(interpolator)
        resampler.SetDefaultPixelValue(defaultPixelValue)
        resampler.SetOutputPixelType(outputPixelType)
        resampler.SetUseNearestNeighborExtrapolator(useNearestNeighborExtrapolator)
        return resampler.Execute(image1)

    def _r(size,
           transform=Transform(),
           interpolator=sitkLinear,
           outputOrigin=(0.0, 0.0, 0.0),
           outputSpacing=(1.0, 1.0, 1.0),
           outputDirection=(),
           defaultPixelValue=0.0,
           outputPixelType=sitkUnknown,
           useNearestNeighborExtrapolator=False):
        resampler = ResampleImageFilter()
        resampler.SetSize(size)
        resampler.SetTransform(transform)
        resampler.SetInterpolator(interpolator)
        resampler.SetOutputOrigin(outputOrigin)
        resampler.SetOutputSpacing(outputSpacing)
        resampler.SetOutputDirection(outputDirection)
        resampler.SetDefaultPixelValue(defaultPixelValue)
        resampler.SetOutputPixelType(outputPixelType)
        resampler.SetUseNearestNeighborExtrapolator(useNearestNeighborExtrapolator)
        return resampler.Execute(image1)

    if args:
        if isinstance(args[0], Image):
            return _r_image(*args, **kwargs)
        if not isinstance(args[0], Transform):
            try:
                iter(args[0])
                return _r(*args, **kwargs)
            except TypeError as e:
                pass

    if "referenceImage" in kwargs:
        return _r_image(*args, **kwargs)
    if "size" in kwargs:
        return _r(*args, **kwargs)

    return _r_image(image1, *args, **kwargs)


HAVE_NUMPY = True
try:
    import numpy
except ImportError:
    HAVE_NUMPY = False


def _get_numpy_dtype(sitkImage):
    """Given a SimpleITK image, returns the numpy.dtype which describes the data"""

    if not HAVE_NUMPY:
        raise ImportError('Numpy not available.')

    # this is a mapping from sitk's pixel id to numpy's dtype
    _sitk_np = {sitkUInt8: numpy.uint8,
                sitkUInt16: numpy.uint16,
                sitkUInt32: numpy.uint32,
                sitkUInt64: numpy.uint64,
                sitkInt8: numpy.int8,
                sitkInt16: numpy.int16,
                sitkInt32: numpy.int32,
                sitkInt64: numpy.int64,
                sitkFloat32: numpy.float32,
                sitkFloat64: numpy.float64,
                sitkComplexFloat32: numpy.complex64,
                sitkComplexFloat64: numpy.complex128,
                sitkVectorUInt8: numpy.uint8,
                sitkVectorInt8: numpy.int8,
                sitkVectorUInt16: numpy.uint16,
                sitkVectorInt16: numpy.int16,
                sitkVectorUInt32: numpy.uint32,
                sitkVectorInt32: numpy.int32,
                sitkVectorUInt64: numpy.uint64,
                sitkVectorInt64: numpy.int64,
                sitkVectorFloat32: numpy.float32,
                sitkVectorFloat64: numpy.float64,
                sitkLabelUInt8: numpy.uint8,
                sitkLabelUInt16: numpy.uint16,
                sitkLabelUInt32: numpy.uint32,
                sitkLabelUInt64: numpy.uint64
                }

    return _sitk_np[sitkImage.GetPixelIDValue()]


def _get_sitk_pixelid(numpy_array_type):
    """Returns a SimpleITK PixelID given a numpy array."""

    if not HAVE_NUMPY:
        raise ImportError('Numpy not available.')

    # This is a Mapping from numpy array types to sitks pixel types.
    _np_sitk = {numpy.character: sitkUInt8,
                numpy.uint8: sitkUInt8,
                numpy.uint16: sitkUInt16,
                numpy.uint32: sitkUInt32,
                numpy.uint64: sitkUInt64,
                numpy.int8: sitkInt8,
                numpy.int16: sitkInt16,
                numpy.int32: sitkInt32,
                numpy.int64: sitkInt64,
                numpy.float32: sitkFloat32,
                numpy.float64: sitkFloat64,
                numpy.complex64: sitkComplexFloat32,
                numpy.complex128: sitkComplexFloat64
                }

    try:
        return _np_sitk[numpy_array_type.dtype]
    except KeyError:
        for key in _np_sitk:
            if numpy.issubdtype(numpy_array_type.dtype, key):
                return _np_sitk[key]
        raise TypeError('dtype: {0} is not supported.'.format(numpy_array_type.dtype))


def _get_sitk_vector_pixelid(numpy_array_type):
    """Returns a SimpleITK vector PixelID given a numpy array."""

    if not HAVE_NUMPY:
        raise ImportError('Numpy not available.')

    # This is a Mapping from numpy array types to sitks pixel types.
    _np_sitk = {numpy.character: sitkVectorUInt8,
                numpy.uint8: sitkVectorUInt8,
                numpy.uint16: sitkVectorUInt16,
                numpy.uint32: sitkVectorUInt32,
                numpy.uint64: sitkVectorUInt64,
                numpy.int8: sitkVectorInt8,
                numpy.int16: sitkVectorInt16,
                numpy.int32: sitkVectorInt32,
                numpy.int64: sitkVectorInt64,
                numpy.float32: sitkVectorFloat32,
                numpy.float64: sitkVectorFloat64,

                }

    try:
        return _np_sitk[numpy_array_type.dtype]
    except KeyError:
        for key in _np_sitk:
            if numpy.issubdtype(numpy_array_type.dtype, key):
                return _np_sitk[key]
        raise TypeError('dtype: {0} is not supported as an array.'.format(numpy_array_type.dtype))


# SimplyITK <-> Numpy Array conversion support.

def GetArrayViewFromImage(image):
    """Get a NumPy ndarray view of a SimpleITK Image.

    Returns a Numpy ndarray object as a "view" of the SimpleITK's Image buffer. This reduces pixel buffer copies, but
     requires that the SimpleITK image object is kept around while the buffer is being used.
    """

    if not HAVE_NUMPY:
        raise ImportError('NumPy not available.')

    pixel_id = image.GetPixelIDValue()
    assert pixel_id != sitkUnknown, "An SimpleITK image of Unknown pixel type should not exists!"

    dtype = _get_numpy_dtype(image)

    shape = image.GetSize()
    if image.GetNumberOfComponentsPerPixel() > 1:
        shape = (image.GetNumberOfComponentsPerPixel(), ) + shape

    image.MakeUnique()

    image_memory_view = _GetMemoryViewFromImage(image)
    array_view = numpy.asarray(image_memory_view).view(dtype = dtype)
    array_view.shape = shape[::-1]

    return array_view


def GetArrayFromImage(image):
    """Get a NumPy ndarray from a SimpleITK Image.

    This is a deep copy of the image buffer and is completely safe and without potential side effects.
    """

    # TODO: If the image is already not unique then a second copy may be made before the numpy copy is done.
    array_view = GetArrayViewFromImage(image)

    # perform deep copy of the image buffer
    return numpy.array(array_view, copy=True)


def GetImageFromArray(arr, isVector=None):
    """ Get a SimpleITK Image from a numpy array.

     If isVector is True, then the Image will have a Vector pixel type, and the last dimension of the array will be
     considered the component index. By default when isVector is None, 4D arrays
     are automatically considered 3D vector images, but 3D arrays are 3D images.
    """

    if not HAVE_NUMPY:
        raise ImportError('Numpy not available.')

    z = numpy.asarray(arr)

    if isVector is None:
      if z.ndim == 4 and z.dtype != numpy.complex64 and z.dtype != numpy.complex128:
          isVector = True

    if isVector:
        id = _get_sitk_vector_pixelid(z)
        if z.ndim > 2:
            number_of_components = z.shape[-1]
            shape = z.shape[-2::-1]
        else:
            number_of_components = 1
            shape = z.shape[::-1]
    else:
        number_of_components = 1
        id = _get_sitk_pixelid(z)
        shape = z.shape[::-1]

    # SimpleITK throws an exception if the image dimension is not supported
    img = Image(shape, id, number_of_components)

    _SetImageFromArray(z.tobytes(), img)

    return img


def ReadImage(fileName: Union[str, List[str]],
              outputPixelType: "PixelIDValueEnum" = sitkUnknown,
              imageIO: str = "") \
        -> Image:
    r"""ReadImage is a procedural interface to the ImageFileReader class which is convenient for most image reading
     tasks.

    This method can read a single image or a list of images into a volume.

    Parameters
    ----------
    fileName
     A single or a list of file names. the filename of an Image e.g. "cthead.mha"
    outputPixelType
     The pixel type of the returned Image. By default the value is sitkUnknown, which enable the output pixel type to
     be same as the file. If the pixel type is specified then the itk::ConvertPixelBuffer will be used to convert the
     pixels.
    imageIO
     The name of the ITK ImageIO to use to read the file. An option to override the automatically detected ImageIO used
     to read the image. The available ImageIOs are listed by the GetRegisteredImageIOs method. If the ImageIO can not
     be constructed an exception will be generated. If the ImageIO can not read the file an exception will be
     generated.

    Returns
    -------
     The provided image file name(s) read into an Image.

    Also See
    --------
     itk::simple::ImageFileReader for reading a single file.
     itk::simple::ImageSeriesReader for reading a series and meta-data dictionaries.

    """

    if isinstance(fileName, str):
        reader = ImageFileReader()
        reader.SetFileName(fileName)
    else:
        reader = ImageSeriesReader()
        reader.SetFileNames(fileName)

    reader.SetImageIO(imageIO)
    reader.SetOutputPixelType(outputPixelType)
    return reader.Execute()


def WriteImage(image: "Image",
               fileName: Union[str, List[str]],
               useCompression: bool = False,
               compressionLevel=-1,
               *,
               imageIO: str = "",
               compressor: str = "") -> "None":
    r"""
    WriteImage is a procedural interface to the ImageFileWriter and ImageSeriesWriter classes which is convenient for
    many image writing tasks.

    For an input image of N dimensions, a series of N-1 dimensional (slices) images can be written by providing a list
    if file names equal to the number of slices in the input image.

    Parameters
    ----------
    image
     the input image to be written
    fileName
     a single or a list of file names to be written
    useCompression
     request to compress the written file
    compressionLevel
     a hint for the amount of compression to be applied during writing
    imageIO
     the name of the ImageIO to perform the writing
    compressor
     a hint for the compression algorithm to use

    Also See
    --------
     itk::simple::ImageFileWriter for writing a single file.
     itk::simple::ImageSeriesWriter for writing a series of files
    """
    if isinstance(fileName, str):
        writer = ImageFileWriter()
        writer.SetFileName(fileName)
    else:
        writer = ImageSeriesWriter()
        writer.SetFileNames(fileName)

    writer.SetUseCompression(useCompression)
    writer.SetCompressionLevel(compressionLevel)
    writer.SetImageIO(imageIO)
    writer.SetCompressor(compressor)
    return writer.Execute(image)


def SmoothingRecursiveGaussian(image1, sigma=[1]*3, normalizeAcrossScale=False):
    """Computes the smoothing of an image by convolution with
    the Gaussian kernels implemented as IIR filters.

    This function directly calls the execute method of SmoothingRecursiveGaussianImageFilter
    in order to support a procedural API.

    Also See
    --------
      itk::simple::SmoothingRecursiveGaussianImageFilter for the object oriented interface
    """

    f = SmoothingRecursiveGaussianImageFilter()
    f.SetSigma(sigma)
    f.SetNormalizeAcrossScale(normalizeAcrossScale)
    return f.Execute(image1)


def DiscreteGaussian(image1, variance=[1] * 3, maximumKernelWidth=32, maximumError=0.01, useImageSpacing=True):
    """Blurs an image by separable convolution with discrete
     gaussian kernels. This filter performs Gaussian blurring by
     separable convolution of an image and a discrete Gaussian
     operator (kernel).

     This function directly calls the execute method of DiscreteGaussianImageFilter
     in order to support a procedural API.

    Also See
    --------
      \sa itk::simple::DiscreteGaussianImageFilter for the object oriented interface
    """
    f = DiscreteGaussianImageFilter()
    f.SetVariance(variance)
    f.SetMaximumKernelWidth(maximumKernelWidth)
    f.SetMaximumError(maximumError)
    f.SetUseImageSpacing(useImageSpacing)
    return f.Execute(image1)



__all__ = ["Resample",
           "GetArrayViewFromImage",
           "GetArrayFromImage",
           "GetImageFromArray",
           "ReadImage",
           "WriteImage",
           "SmoothingRecursiveGaussian",
           "DiscreteGaussian"]
