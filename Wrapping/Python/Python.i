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
#if SWIGPYTHON

%begin %{
#include "sitkPython.h"
%}

%{
#include "sitkPyCommand.h"
%}

%include "PythonDocstrings.i"

// ignore overload methods of int type when there is an enum
%ignore itk::simple::CastImageFilter::SetOutputPixelType( PixelIDValueType pixelID );
%ignore itk::simple::GetPixelIDValueAsString( PixelIDValueType type );

%ignore itk::simple::Resample;


// Make __str__ transparent by renaming ToString to __str__
%rename(__str__) ToString;

%include sitkImage.i
%include sitkTransform.i

// This is included inline because SwigMethods (SimpleITKPYTHON_wrap.cxx)
// is declared static.
%{
#include "sitkNumpyArrayConversion.cxx"
%}
// Numpy array conversion support
%native(_GetMemoryViewFromImage) PyObject *sitk_GetMemoryViewFromImage( PyObject *self, PyObject *args );
%native(_SetImageFromArray) PyObject *sitk_SetImageFromArray( PyObject *self, PyObject *args );

%pythoncode %{

HAVE_NUMPY = True
try:
    import numpy
except ImportError:
    HAVE_NUMPY = False


def _get_numpy_dtype( sitkImage ):
    """Given a SimpleITK image, returns the numpy.dtype which describes the data"""

    if not HAVE_NUMPY:
        raise ImportError('Numpy not available.')

    # this is a mapping from sitk's pixel id to numpy's dtype
    _sitk_np = {sitkUInt8:numpy.uint8,
                sitkUInt16:numpy.uint16,
                sitkUInt32:numpy.uint32,
                sitkUInt64:numpy.uint64,
                sitkInt8:numpy.int8,
                sitkInt16:numpy.int16,
                sitkInt32:numpy.int32,
                sitkInt64:numpy.int64,
                sitkFloat32:numpy.float32,
                sitkFloat64:numpy.float64,
                sitkComplexFloat32:numpy.complex64,
                sitkComplexFloat64:numpy.complex128,
                sitkVectorUInt8:numpy.uint8,
                sitkVectorInt8:numpy.int8,
                sitkVectorUInt16:numpy.uint16,
                sitkVectorInt16:numpy.int16,
                sitkVectorUInt32:numpy.uint32,
                sitkVectorInt32:numpy.int32,
                sitkVectorUInt64:numpy.uint64,
                sitkVectorInt64:numpy.int64,
                sitkVectorFloat32:numpy.float32,
                sitkVectorFloat64:numpy.float64,
                sitkLabelUInt8:numpy.uint8,
                sitkLabelUInt16:numpy.uint16,
                sitkLabelUInt32:numpy.uint32,
                sitkLabelUInt64:numpy.uint64
                }

    return _sitk_np[ sitkImage.GetPixelIDValue() ]



def _get_sitk_pixelid(numpy_array_type):
    """Returns a SimpleITK PixelID given a numpy array."""

    if not HAVE_NUMPY:
        raise ImportError('Numpy not available.')

    # This is a Mapping from numpy array types to sitks pixel types.
    _np_sitk = {numpy.character:sitkUInt8,
                numpy.uint8:sitkUInt8,
                numpy.uint16:sitkUInt16,
                numpy.uint32:sitkUInt32,
                numpy.uint64:sitkUInt64,
                numpy.int8:sitkInt8,
                numpy.int16:sitkInt16,
                numpy.int32:sitkInt32,
                numpy.int64:sitkInt64,
                numpy.float32:sitkFloat32,
                numpy.float64:sitkFloat64,
                numpy.complex64:sitkComplexFloat32,
                numpy.complex128:sitkComplexFloat64
                }

    try:
        return _np_sitk[numpy_array_type.dtype]
    except KeyError:
        for key in _np_sitk:
            if numpy.issubdtype(numpy_array_type.dtype, key):
                return _np_sitk[key]
        raise TypeError('dtype: {0} is not supported.'.format(numpy_array_type.dtype))

def _get_sitk_vector_pixelid(numpy_array_type):
    """Returns a SimpleITK vecotr PixelID given a numpy array."""

    if not HAVE_NUMPY:
        raise ImportError('Numpy not available.')

    # This is a Mapping from numpy array types to sitks pixel types.
    _np_sitk = {numpy.character:sitkVectorUInt8,
                numpy.uint8:sitkVectorUInt8,
                numpy.uint16:sitkVectorUInt16,
                numpy.uint32:sitkVectorUInt32,
                numpy.uint64:sitkVectorUInt64,
                numpy.int8:sitkVectorInt8,
                numpy.int16:sitkVectorInt16,
                numpy.int32:sitkVectorInt32,
                numpy.int64:sitkVectorInt64,
                numpy.float32:sitkVectorFloat32,
                numpy.float64:sitkVectorFloat64,
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

    Returns a Numpy ndarray object as a "view" of the SimpleITK's Image buffer. This reduces pixel buffer copies, but requires that the SimpleITK image object is kept around while the buffer is being used.


    """

    if not HAVE_NUMPY:
        raise ImportError('NumPy not available.')


    pixelID = image.GetPixelIDValue()
    assert pixelID != sitkUnknown, "An SimpleITK image of Unknown pixel type should not exists!"

    dtype = _get_numpy_dtype( image )

    shape = image.GetSize();
    if image.GetNumberOfComponentsPerPixel() > 1:
      shape = ( image.GetNumberOfComponentsPerPixel(), ) + shape

    image.MakeUnique()

    imageMemoryView =  _SimpleITK._GetMemoryViewFromImage(image)
    arrayView = numpy.asarray(imageMemoryView).view(dtype = dtype)
    arrayView.shape = shape[::-1]

    return arrayView

def GetArrayFromImage(image):
    """Get a NumPy ndarray from a SimpleITK Image.

    This is a deep copy of the image buffer and is completely safe and without potential side effects.
    """

    # TODO: If the image is already not unique then a second copy may be made before the numpy copy is done.
    arrayView = GetArrayViewFromImage(image)

    # perform deep copy of the image buffer
    return numpy.array(arrayView, copy=True)


def GetImageFromArray( arr, isVector=None):
    """Get a SimpleITK Image from a numpy array. If isVector is True, then the Image will have a Vector pixel type, and the last dimension of the array will be considered the component index. By default when isVector is None, 4D arrays are automatically considered 3D vector images, but 3D arrays are 3D images."""

    if not HAVE_NUMPY:
        raise ImportError('Numpy not available.')

    z = numpy.asarray( arr )

    if isVector is None:
      if z.ndim == 4 and z.dtype != numpy.complex64 and z.dtype != numpy.complex128:
        isVector = True

    if isVector:
      id = _get_sitk_vector_pixelid( z )
      if z.ndim > 2:
        number_of_components = z.shape[-1]
        shape = z.shape[-2::-1]
      else:
        number_of_components = 1
        shape = z.shape[::-1]
    else:
      number_of_components = 1
      id = _get_sitk_pixelid( z )
      shape = z.shape[::-1]

    # SimpleITK throws an exception if the image dimension is not supported
    img = Image( shape, id, number_of_components )

    _SimpleITK._SetImageFromArray( z.tostring(), img )

    return img
%}

%pythoncode %{
  def Resample( image1, *args, **kwargs):
    """
     Resample ( Image image1, Transform transform = itk::simple::Transform(), InterpolatorEnum interpolator = itk::simple::sitkLinear, double defaultPixelValue = 0.0, PixelIDValueEnum outputPixelType = itk::simple::sitkUnknown, bool useNearestNeighborExtrapolator = false);

     Resample ( Image image1, Image referenceImage, Transform transform = itk::simple::Transform(), InterpolatorEnum interpolator = itk::simple::sitkLinear, double defaultPixelValue = 0.0, PixelIDValueEnum outputPixelType = sitkUnknown, bool useNearestNeighborExtrapolator = false);

     Resample ( const Image& image1, VectorUInt32 size, Transform transform = itk::simple::Transform(), InterpolatorEnum interpolator = itk::simple::sitkLinear, VectorDouble outputOrigin = std::vector<double>(3, 0.0), VectorDouble outputSpacing = std::vector<double>(3, 1.0), VectorDouble outputDirection = std::vector<double>(), double defaultPixelValue = 0.0, PixelIDValueEnum outputPixelType = sitkUnknown, bool useNearestNeighborExtrapolator = false);

     itk::simple::ResampleImageFilter procedural interface.

     This is a custom overloaded python method, which fully supports the 3 signatures with positional and keyword arguemnts. The second positional parameters without a default value are used to determine which overloaded procedure signature to envoke.

    """
    def _r_image( referenceImage,
                  transform = Transform(),
                  interpolator = sitkLinear,
                  defaultPixelValue = 0.0,
                  outputPixelType = sitkUnknown,
                  useNearestNeighborExtrapolator = False):
       filter = ResampleImageFilter()
       filter.SetReferenceImage(referenceImage)
       filter.SetTransform(transform)
       filter.SetInterpolator(interpolator)
       filter.SetDefaultPixelValue(defaultPixelValue)
       filter.SetOutputPixelType(outputPixelType)
       filter.SetUseNearestNeighborExtrapolator(useNearestNeighborExtrapolator)
       return filter.Execute(image1)


    def _r( size,
            transform = Transform(),
            interpolator = sitkLinear,
            outputOrigin = (0.0, 0.0, 0.0),
            outputSpacing = (1.0, 1.0, 1.0),
            outputDirection = (),
            defaultPixelValue = 0.0,
            outputPixelType = sitkUnknown,
            useNearestNeighborExtrapolator = False):
        filter = ResampleImageFilter()
        filter.SetSize(size)
        filter.SetTransform(transform)
        filter.SetInterpolator(interpolator)
        filter.SetOutputOrigin(outputOrigin)
        filter.SetOutputSpacing(outputSpacing)
        filter.SetOutputDirection(outputDirection)
        filter.SetDefaultPixelValue(defaultPixelValue)
        filter.SetOutputPixelType(outputPixelType)
        filter.SetUseNearestNeighborExtrapolator(useNearestNeighborExtrapolator)
        filter.DebugOn()
        return filter.Execute(image1)

    if args:
      if isinstance(args[0], Image):
        return _r_image( *args, **kwargs)
      if not isinstance(args[0], Transform):
        try:
          iter(args[0])
          return _r( *args, **kwargs)
        except TypeError as e:
          pass

    if "referenceImage" in kwargs:
      return _r_image( *args, **kwargs)
    if "size" in kwargs:
      return _r( *args, **kwargs)

    return _r_image( image1, *args, **kwargs)

%}

// Enable Python classes derived from Command Execute method to be
// called from C++
%feature("director") itk::simple::Command;

%extend itk::simple::ProcessObject {
 int AddCommand( itk::simple::EventEnum e, PyObject *obj )
 {
   if (!PyCallable_Check(obj))
     {
     return 0;
     }
   itk::simple::PyCommand *cmd = NULL;
   try
     {
       cmd = new itk::simple::PyCommand();
       cmd->SetCallbackPyCallable(obj);
       int ret = self->AddCommand(e,*cmd);
       cmd->OwnedByProcessObjectsOn();
       return ret;
     }
   catch(...)
     {
       delete cmd;
       throw;
     }
 }
};

#endif
