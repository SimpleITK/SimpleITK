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
#if SWIGPYTHON
%include "PythonDocstrings.i"
// Make __str__ transparent by renaming ToString to __str__
%rename(__str__) ToString;

%rename( __GetPixelAsInt8__ ) itk::simple::Image::GetPixelAsInt8;
%rename( __GetPixelAsUInt8__ ) itk::simple::Image::GetPixelAsUInt8;
%rename( __GetPixelAsInt16__ ) itk::simple::Image::GetPixelAsInt16;
%rename( __GetPixelAsUInt16__ ) itk::simple::Image::GetPixelAsUInt16;
%rename( __GetPixelAsInt32__ ) itk::simple::Image::GetPixelAsInt32;
%rename( __GetPixelAsUInt32__ ) itk::simple::Image::GetPixelAsUInt32;
%rename( __GetPixelAsInt64__ ) itk::simple::Image::GetPixelAsInt64;
%rename( __GetPixelAsUInt64__ ) itk::simple::Image::GetPixelAsUInt64;
%rename( __GetPixelAsFloat__ ) itk::simple::Image::GetPixelAsFloat;
%rename( __GetPixelAsDouble__ ) itk::simple::Image::GetPixelAsDouble;

%rename( __SetPixelAsInt8__ ) itk::simple::Image::SetPixelAsInt8;
%rename( __SetPixelAsUInt8__ ) itk::simple::Image::SetPixelAsUInt8;
%rename( __SetPixelAsInt16__ ) itk::simple::Image::SetPixelAsInt16;
%rename( __SetPixelAsUInt16__ ) itk::simple::Image::SetPixelAsUInt16;
%rename( __SetPixelAsInt32__ ) itk::simple::Image::SetPixelAsInt32;
%rename( __SetPixelAsUInt32__ ) itk::simple::Image::SetPixelAsUInt32;
%rename( __SetPixelAsInt64__ ) itk::simple::Image::SetPixelAsInt64;
%rename( __SetPixelAsUInt64__ ) itk::simple::Image::SetPixelAsUInt64;
%rename( __SetPixelAsFloat__ ) itk::simple::Image::SetPixelAsFloat;
%rename( __SetPixelAsDouble__ ) itk::simple::Image::SetPixelAsDouble;

%pythoncode %{
   import operator
%}

%extend itk::simple::Image {


//      def __floordiv__( other )


        %pythoncode %{

        # mathematical operators

        def __add__( self, other ):
            if isinstance( other, Image ):
               return Add( self, other )
            try:
               return Add( self, float(other)  )
            except ValueError:
               return NotImplemented
        def __sub__( self, other ):
            if isinstance( other, Image ):
               return Subtract( self, other )
            try:
               return Subtract( self, float(other) )
            except ValueError:
               return NotImplemented
        def __mul__( self, other ):
            if isinstance( other, Image ):
               return Multiply( self, other )
            try:
               return Multiply( self, float(other) )
            except ValueError:
               return NotImplemented
        def __div__( self, other ):
            if isinstance( other, Image ):
               return Divide( self, other )
            try:
               return Divide( self, float(other) )
            except ValueError:
               return NotImplemented

        def __neg__( self ):
            return UnaryMinus( self )
        def __pos__( self ):
            return self

        # NOTE: for the reverse methods other cannot be an image, so
        # therefore other should be able to be considered a constant.

        def __radd__( self, other ):
            try:
               return Add( float(other), self )
            except ValueError:
               return NotImplemented
        def __rsub__( self, other ):
            try:
               return Subtract( float(other), self )
            except ValueError:
               return NotImplemented
        def __rmul__( self, other ):
            try:
               return Multiply( float(other), self )
            except ValueError:
               return NotImplemented
        def __rdiv__( self, other ):
            try:
               return Divide( float(other), self )
            except ValueError:
               return NotImplemented

         # NOTE: the __i*__ methods are not implemented because there
         # currently in no way to make the underlying filters run
         # inplace. But python will implement a default version based
         # on the standard method
        def __iadd__ ( self, other ):
            self = Add( self, other )
            return self;

        # logic operators

        def __and__( self, other ):
            if isinstance( other, Image ):
               return And( self, other )
            try:
               return And( self, int(other) )
            except ValueError:
               return NotImplemented
        def __rand__( self, other ):
            try:
               return And( int(other), self )
            except ValueError:
               return NotImplemented
        def __or__( self, other ):
            if isinstance( other, Image ):
               return Or( self, other )
            try:
               return Or( self, int(other) )
            except ValueError:
               return NotImplemented
        def __ror__( self, other ):
            try:
               return Or( int(other), self )
            except ValueError:
               return NotImplemented
        def __xor__( self, other ):
            if isinstance( other, Image ):
               return Xor( self, other )
            try:
               return Xor( self, int(other) )
            except ValueError:
               return NotImplemented
        def __rxor__( self, other ):
            try:
               return Xor( int(other), self )
            except ValueError:
               return NotImplemented
        def __invert__( self ): return Not( self )

        # Relational and Equality operators

        def __lt__( self, other ):
            if isinstance( other, Image ):
               return Less( self, other )
            try:
               return Less( self, float(other) )
            except ValueError, TypeError:
               return NotImplemented
        def __le__( self, other ):
            if isinstance( other, Image ):
               return LessEqual( self, other )
            try:
               return LessEqual( self, float(other) )
            except ValueError, TypeError:
               return NotImplemented
        def __eq__( self, other ):
            if isinstance( other, Image ):
               return Equal( self, other )
            try:
               return Equal( self, float(other) )
            except ValueError, TypeError:
               return NotImplemented
        def __ne__( self, other ):
            if isinstance( other, Image ):
               return NotEqual( self, other )
            try:
               return NotEqual( self, float(other) )
            except ValueError, TypeError:
               return NotImplemented
        def __gt__( self, other ):
            if isinstance( other, Image ):
               return Greater( self, other )
            try:
               return Greater( self, int(other) )
            except ValueError, TypeError:
               return NotImplemented
        def __ge__( self, other ):
            if isinstance( other, Image ):
               return GreaterEqual( self, other )
            try:
               return GreaterEqual( self, int(other) )
            except ValueError, TypeError:
               return NotImplemented


        # "function" operators

        def __pow__( self, other ):
            if isinstance( other, Image ):
               return Pow( self, other )
            try:
               return Pow( self, float(other) )
            except ValueError:
               return NotImplemented
        def __rpow__( self, other ):
            try:
               return Pow( float(other), self )
            except ValueError:
               return NotImplemented
        def __mod__( self, other ): return Modulus( self, other )
        def __abs__( self ): return Abs( self )

        # iterator and container methods

        def __iter__( self ):

            if len(self) == 0:
              raise StopIteration

            dim = self.GetDimension()
            size = self.GetSize()
            idx = [0] * dim

            while idx[dim-1] < size[dim-1]:

              yield self[ idx ]

              # increment the idx
              for d in range( 0, dim ):
                idx[d] += 1
                if idx[d] >= size[d] and d != dim  - 1:
                   idx[d] = 0
                else:
                   break

            return

        def __len__( self ):
            l = 1
            for ds in self.GetSize():
              l *= ds
            return l

        # set/get pixel methods

        def __getitem__( self, idx ):
            """Returns the value of pixel at index idx.

            The dimension of idx should match that of the image."""
            pixelID = self.GetPixelIDValue()
            if pixelID == sitkUnknown:
               raise Exception("Logic Error: invalid pixel type")
            if pixelID == sitkInt8:
               return self.__GetPixelAsInt8__( idx )
            if pixelID == sitkUInt8 or pixelID == sitkLabelUInt8:
               return self.__GetPixelAsUInt8__( idx )
            if pixelID == sitkInt16:
               return self.__GetPixelAsInt16__( idx )
            if pixelID == sitkUInt16 or pixelID == sitkLabelUInt16:
               return self.__GetPixelAsUInt16__( idx )
            if pixelID == sitkInt32:
               return self.__GetPixelAsInt32__( idx )
            if pixelID == sitkUInt32 or pixelID == sitkLabelUInt32:
               return self.__GetPixelAsUInt32__( idx )
            if pixelID == sitkInt64:
               return self.__GetPixelAsInt64__( idx )
            if pixelID == sitkUInt64 or pixelID == sitkLabelUInt64:
               return self.__GetPixelAsUInt64__( idx )
            if pixelID == sitkFloat32:
               return self.__GetPixelAsFloat__( idx )
            if pixelID == sitkFloat64:
               return self.__GetPixelAsDouble__( idx )
            raise Exception("Unknown pixel type")


        def __setitem__( self, idx, value ):
            """Sets the pixel value at index idx to value.

            The dimension of idx should match that of the image."""
            pixelID = self.GetPixelIDValue()
            if pixelID == sitkUnknown:
               raise Exception("Logic Error: invalid pixel type")
            if pixelID == sitkInt8:
               return self.__SetPixelAsInt8__( idx )
            if pixelID == sitkUInt8 or pixelID == sitkLabelUInt8:
               return self.__SetPixelAsUInt8__( idx, value )
            if pixelID == sitkInt16:
               return self.__SetPixelAsInt16__( idx, value )
            if pixelID == sitkUInt16 or pixelID == sitkLabelUInt16:
               return self.__SetPixelAsUInt16__( idx, value )
            if pixelID == sitkInt32:
               return self.__SetPixelAsInt32__( idx, value )
            if pixelID == sitkUInt32 or pixelID == sitkLabelUInt32:
               return self.__SetPixelAsUInt32__( idx, value )
            if pixelID == sitkInt64:
               return self.__SetPixelAsInt64__( idx )
            if pixelID == sitkUInt64 or pixelID == sitkLabelUInt64:
               return self.__SetPixelAsUInt64__( idx )
            if pixelID == sitkFloat32:
               return self.__SetPixelAsFloat__( idx, value )
            if pixelID == sitkFloat64:
               return self.__SetPixelAsDouble__( idx, value )
            raise Exception("Unknown pixel type")

        def GetPixel(self, *idx):
             """Returns the value of a pixel.

	     This method takes 2 parameters in 2D: the x and y index,
             and 3 parameters in 3D: the x, y and z index."""
             return self[idx]

        def SetPixel(self, *args):
             """Sets the value of a pixel.

	     This method takes 3 parameters in 2D: the x and y index then the value,
             and 4 parameters in 3D: the x, y and z index then the value."""
             if len(args) < 2:
                raise Exception( "Wrong number of arguments, coordinates arguments then value" )
             idx = args[:len(args)-1]
             value = args[-1]
             self[idx] = value


         %}



}

// This is included inline because SwigMethods (SimpleITKPYTHON_wrap.cxx)
// is declared static.
%{
#include "sitkNumpyArrayConversion.cxx"
%}
// Numpy array conversion support
%native(_GetByteArrayFromImage) PyObject *sitk_GetByteArrayFromImage( PyObject *self, PyObject *args );
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

# SimplyITK <-> Numpy Array conversion support.

def GetArrayFromImage(image):
    """Get a numpy array from a SimpleITK Image."""

    if not HAVE_NUMPY:
        raise ImportError('Numpy not available.')

    imageByteArray = _SimpleITK._GetByteArrayFromImage(image)

    pixelID = image.GetPixelIDValue()
    assert pixelID != sitkUnknown, "An SimpleITK image of Unknow pixel type should now exists!"

    dtype = _get_numpy_dtype( image )

    arr = numpy.frombuffer(imageByteArray, dtype )

    shape = image.GetSize();
    if image.GetNumberOfComponentsPerPixel() > 1:
      shape += ( image.GetNumberOfComponentsPerPixel(), )

    arr.shape = shape[::-1]

    return arr

def GetImageFromArray( arr ):
    """Get a SimpleITK Image from a numpy array."""

    if not HAVE_NUMPY:
        raise ImportError('Numpy not available.')

    z = numpy.asarray( arr )
    id = _get_sitk_pixelid( z )

    assert len( z.shape ) in ( 2, 3, 4 ), \
      "Only arrays of 2, 3 or 4 dimensions are supported."

    if len( z.shape ) in ( 2, 3 ):
      img = Image( z.shape[::-1], id )
    elif len( z.shape == 4 ):
      img = Image( (z.shape[3], z.shape[2], z.shape[1]) , id, numberOfComponents = z.shape[0] )

    _SimpleITK._SetImageFromArray( z.tostring(), img )

    return img
%}

#endif
