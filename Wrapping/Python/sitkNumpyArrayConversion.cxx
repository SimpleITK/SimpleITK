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
#include <string.h>

#include <numeric>
#include <functional>

#include "sitkImage.h"
#include "sitkConditional.h"
#include "sitkExceptionObject.h"

namespace sitk = itk::simple;

// Python is written in C
#ifdef __cplusplus
extern "C"
{
#endif

/** An internal function that returns a memoryview object to the
 * SimpleITK Image's buffer (shallow). The correct copy and writing
 * policies need to be done by the end-user method.
 */
static PyObject *
sitk_GetMemoryViewFromImage( PyObject *SWIGUNUSEDPARM(self), PyObject *args )
{
  const void *                sitkBufferPtr;
  Py_ssize_t                  len;

  /* Cast over to a sitk Image. */
  PyObject *                  pyImage;
  void *                      voidImage;
  sitk::Image *               sitkImage;
  int                         res           = 0;

  PyObject *                  memoryView    = NULL;
  Py_buffer                   pyBuffer;
  memset(&pyBuffer, 0, sizeof(Py_buffer));


  if( !PyArg_ParseTuple( args, "O", &pyImage ) )
    {
    SWIG_fail; // SWIG_fail is a macro that says goto: fail (return NULL)
    }
  res = SWIG_ConvertPtr( pyImage, &voidImage, SWIGTYPE_p_itk__simple__Image, 0 );
  if( !SWIG_IsOK( res ) )
    {
    SWIG_exception_fail(SWIG_ArgError(res), "in method 'GetByteArrayFromImage', argument needs to be of type 'sitk::Image *'");
    }
  sitkImage = reinterpret_cast< sitk::Image * >( voidImage );

  if ( sitkImage->GetPixelIDValue() == sitk::sitkUnknown)
    {
    PyErr_SetString( PyExc_RuntimeError, "Unknown pixel type." );
    SWIG_fail;
    }
  sitkBufferPtr = sitkImage->GetBufferAsVoid();

  len = size_t(sitkImage->GetNumberOfPixels()) * sitkImage->GetSizeOfPixelComponent();
  len *= sitkImage->GetNumberOfComponentsPerPixel();

  if (PyBuffer_FillInfo(&pyBuffer, NULL, (void*)sitkBufferPtr, len, true, PyBUF_CONTIG_RO)!=0)
    {
    SWIG_fail;
    }
  memoryView = PyMemoryView_FromBuffer(&pyBuffer);

  PyBuffer_Release(&pyBuffer);
  return memoryView;

fail:
  Py_XDECREF( memoryView );
  return NULL;
}

/** An internal function that performs a deep copy of the image buffer
 * into a python byte array. The byte array can later be converted
 * into a numpy array with the frombuffer method.
 */
static PyObject*
sitk_SetImageFromArray( PyObject *SWIGUNUSEDPARM(self), PyObject *args )
{
  PyObject * pyImage = NULL;

  const void *buffer;
  Py_ssize_t buffer_len;
  Py_buffer  pyBuffer;
  memset(&pyBuffer, 0, sizeof(Py_buffer));

  sitk::Image * sitkImage = NULL;
  void * sitkBufferPtr = NULL;

  size_t len = 1;

  // We wish to support both the new PEP3118 buffer interface and the
  // older. So we first try to parse the arguments with the new buffer
  // protocol, then the old.
  if (!PyArg_ParseTuple( args, "s*O", &pyBuffer, &pyImage ) )
    {
    PyErr_Clear();

#ifdef PY_SSIZE_T_CLEAN
    using bufSizeType = Py_ssize_t;
#else
    using bufSizeType = int;
#endif

    bufSizeType _len;
    // This function takes 2 arguments from python, the first is an
    // python object which support the old "ReadBuffer" interface
    if( !PyArg_ParseTuple( args, "s#O", &buffer, &_len, &pyImage ) )
      {
      return NULL;
      }
    buffer_len = _len;
    }
  else
    {
    if ( PyBuffer_IsContiguous( &pyBuffer, 'C' ) != 1 )
      {
      PyBuffer_Release( &pyBuffer );
      PyErr_SetString( PyExc_TypeError, "A C Contiguous buffer object is required." );
      return NULL;
      }
    buffer_len = pyBuffer.len;
    buffer = pyBuffer.buf;
    }

  /* Cast over to a sitk Image. */
  {
    void * voidImage;
    int res = 0;
    res = SWIG_ConvertPtr( pyImage, &voidImage, SWIGTYPE_p_itk__simple__Image, 0 );
    if( !SWIG_IsOK( res ) )
      {
      SWIG_exception_fail(SWIG_ArgError(res), "in method 'SetImageFromArray', argument needs to be of type 'sitk::Image *'");
      }
    sitkImage = reinterpret_cast< sitk::Image * >( voidImage );
  }

  try
    {
    if ( sitkImage->GetPixelIDValue() == sitk::sitkUnknown)
      {
      PyErr_SetString( PyExc_RuntimeError, "Unknown pixel type." );
      SWIG_fail;
      }

    sitkBufferPtr = sitkImage->GetBufferAsVoid();
    }
  catch( const std::exception &e )
    {
    std::string msg = "Exception thrown in SimpleITK new Image: ";
    msg += e.what();
    PyErr_SetString( PyExc_RuntimeError, msg.c_str() );
    goto fail;
    }


  len = size_t(sitkImage->GetNumberOfPixels()) * sitkImage->GetSizeOfPixelComponent();
  len *= sitkImage->GetNumberOfComponentsPerPixel();

  if ( buffer_len != len )
    {
    PyErr_SetString( PyExc_RuntimeError, "Size mismatch of image and Buffer." );
    goto fail;
    }

  memcpy( (void *)sitkBufferPtr, buffer, len );


  PyBuffer_Release( &pyBuffer );
  Py_RETURN_NONE;

fail:
  PyBuffer_Release( &pyBuffer );
  return NULL;
}

#ifdef __cplusplus
} // end extern "C"
#endif
