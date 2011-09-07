#include <string.h>

#include "sitkImage.h"

// Python is written in C
#ifdef __cplusplus
extern "C"
{
#endif

/** An internal function that extracts the data an information to be used by the
 * interpretted GetArrayFromImage to create the numpy array.  It avoids needing
 * numpy available at compile time.  This is not intended to be called directly.
 *
 * This return a tuple of a Python bytearray with the raw data, a Python tuple
 * with the shape, and an integer indicating the dtype. */
static PyObject *
sitk_GetArrayFromImage( PyObject *SWIGUNUSEDPARM(self), PyObject *args )
{
  // Holds the return tuple
  PyObject * resultTuple = NULL;
  // Holds the bulk data
  PyObject * byteArray = NULL;
  // Numpy array shape
  PyObject * shape = NULL;
  // An integer used by the interpreted caller to identify the pixel type
  // (dtype)
  PyObject * pixelID = NULL;

  const void * sitkBufferPtr;
  Py_ssize_t len;
  typedef std::vector< unsigned int > SizeType;
  SizeType size;
  int pixelDtype;
  size_t pixelSize;
  itk::simple::PixelIDValueType pixelIDValue;

  unsigned int dimension;

  /* Cast over to a sitk Image. */
  PyObject * pyImage;
  void * voidImage;
  itk::simple::Image * sitkImage;
  int res = 0;
  if( !PyArg_ParseTuple( args, "O", &pyImage ) )
    {
    SWIG_fail; // SWIG_fail is a macro that says goto: fail (return NULL)
    }
  res = SWIG_ConvertPtr( pyImage, &voidImage, SWIGTYPE_p_itk__simple__Image, 0 );
  if( !SWIG_IsOK( res ) )
    {
    SWIG_exception_fail(SWIG_ArgError(res), "in method 'GetArrayFromImage', argument needs to be of type 'itk::simple::Image *'");
    }
  sitkImage = reinterpret_cast< itk::simple::Image * >( voidImage );

  pixelIDValue = sitkImage->GetPixelIDValue();
  pixelSize = 1;
  pixelDtype = 0;
  switch( pixelIDValue )
    {
  case itk::simple::sitkUInt8:
    pixelDtype = 0;
    sitkBufferPtr = (const void *)sitkImage->GetBufferAsUInt8();
    pixelSize  = sizeof( uint8_t );
    break;
  case itk::simple::sitkInt8:
    pixelDtype = 1;
    sitkBufferPtr = (const void *)sitkImage->GetBufferAsInt8();
    pixelSize  = sizeof( int8_t );
    break;
  case itk::simple::sitkUInt16:
    pixelDtype = 2;
    sitkBufferPtr = (const void *)sitkImage->GetBufferAsUInt16();
    pixelSize  = sizeof( uint16_t );
    break;
  case itk::simple::sitkInt16:
    pixelDtype = 3;
    sitkBufferPtr = (const void *)sitkImage->GetBufferAsInt16();
    pixelSize  = sizeof( int16_t );
    break;
  case itk::simple::sitkUInt32:
    pixelDtype = 4;
    sitkBufferPtr = (const void *)sitkImage->GetBufferAsUInt32();
    pixelSize  = sizeof( uint32_t );
    break;
  case itk::simple::sitkInt32:
    pixelDtype = 5;
    sitkBufferPtr = (const void *)sitkImage->GetBufferAsInt32();
    pixelSize  = sizeof( int32_t );
    break;
// \todo reenable when vxl pixel long types are fixed
  //case itk::simple::sitkUInt64:
    //pixelDtype = 6;
    //sitkBufferPtr = (const void *)sitkImage->GetBufferAsUInt64();
    //pixelSize  = sizeof( uint64_t );
    //break;
  //case itk::simple::sitkInt64:
    //pixelDtype = 7;
    //sitkBufferPtr = (const void *)sitkImage->GetBufferAsInt64();
    //pixelSize  = sizeof( int64_t );
    //break;
  case itk::simple::sitkFloat32:
    pixelDtype = 8;
    sitkBufferPtr = (const void *)sitkImage->GetBufferAsFloat();
    pixelSize  = sizeof( float );
    break;
  case itk::simple::sitkFloat64:
    pixelDtype = 9;
    sitkBufferPtr = (const void *)sitkImage->GetBufferAsDouble(); // \todo rename to Float64 for consistency
    pixelSize  = sizeof( double );
    break;
// \todo re-enable when Image class gets more GetBuffer support
  //case itk::simple::sitkComplexFloat32:
    //pixelDtype = 10;
    //sitkBufferPtr = (const void *)sitkImage->GetBufferAsComplexFloat32();
    //pixelSize  = sizeof( std::complex<float> );
    //break;
  //case itk::simple::sitkComplexFloat64:
    //pixelDtype = 11;
    //sitkBufferPtr = (const void *)sitkImage->GetBufferAsComplexFloat64();
    //pixelSize  = sizeof( std::complex<double> );
    //break;
  // \todo sitkVectorUInt8, etc.?

  default:
    PyErr_SetString( PyExc_RuntimeError, "Unknown pixel type." );
    SWIG_fail;
    }

  dimension = sitkImage->GetDimension();
  size = sitkImage->GetSize();
  if( dimension == 2 )
    {
    len = size[0] * size[1] * pixelSize;
    }
  else if( dimension == 3 )
    {
    len = size[0] * size[1] * size[2] * pixelSize;
    }
  else
    {
    PyErr_SetString( PyExc_ValueError, "Unexpected Image dimension." );
    SWIG_fail;
    }
  // When the string is null, the bytearray is uninitialized but allocated
  byteArray = PyByteArray_FromStringAndSize( NULL, len );
  if( !byteArray )
    {
    SWIG_fail;
    }

  // For more information on the Py_buffer protocol, see PEP 3118
  // http://www.python.org/dev/peps/pep-3118/
  // This restricts us to Python 2.6 or better
  Py_buffer byteArrayView;
  if( PyObject_GetBuffer( byteArray, &byteArrayView, PyBUF_WRITABLE ) < 0 )
    {
    SWIG_fail;
    }
  memcpy( byteArrayView.buf, sitkBufferPtr, len );
  PyBuffer_Release( &byteArrayView );

  pixelID = Py_BuildValue( "i", pixelDtype );
  if( !pixelID )
    {
    SWIG_fail;
    }

  if( dimension == 2 )
    {
    shape = Py_BuildValue( "(ii)", size[1], size[0] );
    }
  else if( dimension == 3 )
    {
    shape = Py_BuildValue( "(iii)", size[2], size[1], size[0] );
    }
  else
    {
    PyErr_SetString( PyExc_ValueError, "Unexpected Image dimension." );
    SWIG_fail;
    }
  if( !shape )
    {
    SWIG_fail;
    }

  resultTuple = PyTuple_New( 3 );
  if( !resultTuple )
    {
    SWIG_fail;
    }
  if( PyTuple_SetItem( resultTuple, 0, byteArray ) != 0 )
    {
    SWIG_fail;
    }
  if( PyTuple_SetItem( resultTuple, 1, shape ) != 0 )
    {
    SWIG_fail;
    }
  if( PyTuple_SetItem( resultTuple, 2, pixelID ) != 0 )
    {
    SWIG_fail;
    }
  return resultTuple;

fail:
  Py_XDECREF( resultTuple ); // this should come first
  Py_XDECREF( shape );
  Py_XDECREF( pixelID );
  Py_XDECREF( byteArray );
  return NULL;
}

static PyObject *
sitk_GetImageFromArray( PyObject *SWIGUNUSEDPARM(self), PyObject *args )
{
  PyObject * arr = NULL;
  PyObject * dtype = NULL;
  PyObject * dtype_num = NULL;
  long dtype_num_long = -1;

  // For more information on the Py_buffer protocol, see PEP 3118
  // http://www.python.org/dev/peps/pep-3118/
  // This restricts us to Python 2.6 or better
  Py_buffer arrayView;
  arrayView.buf = NULL;
  itk::simple::Image * image = NULL;
  PyObject * pyImage = NULL;
  void * sitkBufferPtr;

  Py_ssize_t *shape = NULL;
  if( !PyArg_ParseTuple( args, "O", &arr ) )
    {
    SWIG_fail; // SWIG_fail is a macro that says goto: fail (return NULL)
    }

  if( PyObject_GetBuffer( arr, &arrayView, PyBUF_CONTIG_RO | PyBUF_C_CONTIGUOUS ) < 0 )
    {
    SWIG_fail;
    }

  dtype = PyObject_GetAttrString( arr, "dtype" );
  if( dtype == NULL )
    {
    SWIG_fail;
    }

  dtype_num = PyObject_GetAttrString( dtype, "num" );
  if( dtype_num == NULL )
    {
    SWIG_fail;
    }
  dtype_num_long = PyInt_AsLong( dtype_num );
  Py_DECREF( dtype_num );
  Py_DECREF( dtype );

  try
    {
    shape = arrayView.shape;
    if( arrayView.ndim == 2 )
      {
      switch( dtype_num_long )
        {
      case 1:
        image = new itk::simple::Image( shape[1], shape[0], itk::simple::sitkInt8 );
        sitkBufferPtr = (void *)image->GetBufferAsInt8();
        break;
      case 2:
        image = new itk::simple::Image( shape[1], shape[0], itk::simple::sitkUInt8 );
        sitkBufferPtr = (void *)image->GetBufferAsUInt8();
        break;
      case 3:
        image = new itk::simple::Image( shape[1], shape[0], itk::simple::sitkInt16 );
        sitkBufferPtr = (void *)image->GetBufferAsInt16();
        break;
      case 4:
        image = new itk::simple::Image( shape[1], shape[0], itk::simple::sitkUInt16 );
        sitkBufferPtr = (void *)image->GetBufferAsUInt16();
        break;
      case 5:
        image = new itk::simple::Image( shape[1], shape[0], itk::simple::sitkInt32 );
        sitkBufferPtr = (void *)image->GetBufferAsInt32();
        break;
      case 6:
        image = new itk::simple::Image( shape[1], shape[0], itk::simple::sitkUInt32 );
        sitkBufferPtr = (void *)image->GetBufferAsUInt32();
        break;
        //! \todo when sitk gets these implemented
      //case 7:
        //image = new itk::simple::Image( shape[1], shape[0], itk::simple::sitkInt64 );
        //sitkBufferPtr = (void *)image->GetBufferAsInt64();
        //break;
      //case 8:
        //image = new itk::simple::Image( shape[1], shape[0], itk::simple::sitkUInt64 );
        //sitkBufferPtr = (void *)image->GetBufferAsUInt64();
        //break;
      case 11:
        image = new itk::simple::Image( shape[1], shape[0], itk::simple::sitkFloat32 );
        sitkBufferPtr = (void *)image->GetBufferAsFloat();
        break;
      case 12:
        image = new itk::simple::Image( shape[1], shape[0], itk::simple::sitkFloat64 );
        sitkBufferPtr = (void *)image->GetBufferAsDouble();
        break;
//! \todo re-enable when Image class gets more GetBuffer support
      //case 14:
        //image = new itk::simple::Image( shape[1], shape[0], itk::simple::sitkComplexFloat32 );
        //sitkBufferPtr = (void *)image->GetBufferAsComplexFloat();
        //break;
      //case 15:
        //image = new itk::simple::Image( shape[1], shape[0], itk::simple::sitkComplexFloat64 );
        //sitkBufferPtr = (void *)image->GetBufferAsComplexDouble();
        //break;
      default:
        PyErr_SetString( PyExc_TypeError, "Unsupported array dtype." );
        SWIG_fail;
        } // end switch dtype_num
      } // end if ndim == 2
    else if( arrayView.ndim == 3 )
      {
      switch( dtype_num_long )
        {
      case 1:
        image = new itk::simple::Image( shape[2], shape[1], shape[0], itk::simple::sitkInt8 );
        sitkBufferPtr = (void *)image->GetBufferAsInt8();
        break;
      case 2:
        image = new itk::simple::Image( shape[2], shape[1], shape[0], itk::simple::sitkUInt8 );
        sitkBufferPtr = (void *)image->GetBufferAsUInt8();
        break;
      case 3:
        image = new itk::simple::Image( shape[2], shape[1], shape[0], itk::simple::sitkInt16 );
        sitkBufferPtr = (void *)image->GetBufferAsInt16();
        break;
      case 4:
        image = new itk::simple::Image( shape[2], shape[1], shape[0], itk::simple::sitkUInt16 );
        sitkBufferPtr = (void *)image->GetBufferAsUInt16();
        break;
      case 5:
        image = new itk::simple::Image( shape[2], shape[1], shape[0], itk::simple::sitkInt32 );
        sitkBufferPtr = (void *)image->GetBufferAsInt32();
        break;
      case 6:
        image = new itk::simple::Image( shape[2], shape[1], shape[0], itk::simple::sitkUInt32 );
        sitkBufferPtr = (void *)image->GetBufferAsUInt32();
        break;
        //! \todo when sitk gets these implemented
      //case 7:
        //image = new itk::simple::Image( shape[2], shape[1], shape[0], itk::simple::sitkInt64 );
        //sitkBufferPtr = (void *)image->GetBufferAsInt64();
        //break;
      //case 8:
        //image = new itk::simple::Image( shape[2], shape[1], shape[0], itk::simple::sitkUInt64 );
        //sitkBufferPtr = (void *)image->GetBufferAsUInt64();
        //break;
      case 11:
        image = new itk::simple::Image( shape[2], shape[1], shape[0], itk::simple::sitkFloat32 );
        sitkBufferPtr = (void *)image->GetBufferAsFloat();
        break;
      case 12:
        image = new itk::simple::Image( shape[2], shape[1], shape[0], itk::simple::sitkFloat64 );
        sitkBufferPtr = (void *)image->GetBufferAsDouble();
        break;
//! \todo re-enable when Image class gets more GetBuffer support
      //case 14:
        //image = new itk::simple::Image( shape[2], shape[1], shape[0], itk::simple::sitkComplexFloat32 );
        //sitkBufferPtr = (void *)image->GetBufferAsComplexFloat();
        //break;
      //case 15:
        //image = new itk::simple::Image( shape[2], shape[1], shape[0], itk::simple::sitkComplexFloat64 );
        //sitkBufferPtr = (void *)image->GetBufferAsComplexDouble();
        //break;
      default:
        PyErr_SetString( PyExc_TypeError, "Unsupported array dtype." );
        SWIG_fail;
        } // end switch dtype_num
      } // end if ndim == 3
    else
      {
      PyErr_SetString( PyExc_ValueError, "Unsupported array dimension." );
      SWIG_fail;
      }
    }
  catch( const itk::ExceptionObject &e )
    {
    std::string msg = "Exception thrown in SimpleITK new Image: ";
    msg += e.what();
    PyErr_SetString( PyExc_RuntimeError, msg.c_str() );
    SWIG_fail;
    }

  pyImage = SWIG_NewPointerObj( image, SWIGTYPE_p_itk__simple__Image, 1 );
  memcpy( (void *)sitkBufferPtr, arrayView.buf, arrayView.len );

  PyBuffer_Release( &arrayView );

  return pyImage;

fail:
  Py_XDECREF( dtype );
  Py_XDECREF( image );
  if( arrayView.buf != NULL )
    {
    PyBuffer_Release( &arrayView );
    }
  return NULL;
}

#ifdef __cplusplus
}
#endif
