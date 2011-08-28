#include "sitkImage.h"

// Python is written in C
extern "C"
{

static PyObject *
sitk_GetArrayFromImage( PyObject *SWIGUNUSEDPARM(self), PyObject *args )
{
  /* Cast over to a sitk Image. */
  PyObject * pyImage;
  void * voidImage;
  const itk::simple::Image * sitkImage;
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
  sitkImage = reinterpret_cast< const itk::simple::Image * >( voidImage );

  printf( "the dimension is %d\n", sitkImage->GetDimension() );

  return Py_BuildValue("i", 42);
fail:
  return NULL;
}

static PyObject *
sitk_GetImageFromArray( PyObject *SWIGUNUSEDPARM(self), PyObject *args )
{
  const PyObject * arr;
  return Py_BuildValue("i", 42);
}

}
