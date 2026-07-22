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

#include "sitkImagePixelIterator.h"
#include "sitkImageBuffer.h"
#include "sitkImage.h"
#include "sitkPixelIDValues.h"

namespace sitk = itk::simple;

typedef struct
{
  PyObject_HEAD PyObject * pyImageRef;
  const char *             buf;
  Py_ssize_t               pos;
  Py_ssize_t               num_pixels;
  Py_ssize_t               bytes_per_pixel;
  int                      pixel_id;
  int                      num_components;
} sitkImagePixelIterator;


static PyObject *
sitkImagePixelIterator_new(PyTypeObject * type, PyObject * args, PyObject * kwds)
{
  sitkImagePixelIterator * self = (sitkImagePixelIterator *)PyType_GenericAlloc(type, 1);
  if (self)
  {
    self->pyImageRef = nullptr;
    self->buf = nullptr;
    self->pos = 0;
    self->num_pixels = 0;
    self->bytes_per_pixel = 0;
    self->pixel_id = sitk::sitkUnknown;
    self->num_components = 1;
  }
  return (PyObject *)self;
}


static int
sitkImagePixelIterator_init(sitkImagePixelIterator * self, PyObject * args, PyObject * kwds)
{
  PyObject * pyImageObj = nullptr;

  static char * kwlist[] = { (char *)"image", NULL };
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "O", kwlist, &pyImageObj))
  {
    return -1;
  }

  if (!pyImageObj)
  {
    PyErr_SetString(PyExc_ValueError, "Image object is required");
    return -1;
  }

  try
  {
    sitk::Image * imagePtr = sitk_GetImagePointerFromPyObject(pyImageObj);
    if (!imagePtr)
    {
      PyErr_SetString(PyExc_TypeError, "Expected a SimpleITK Image object");
      return -1;
    }

    const sitk::Image & constImage = static_cast<const sitk::Image &>(*imagePtr);

    sitk::PixelIDValueEnum pixelID = constImage.GetPixelID();

    if (pixelID == sitk::sitkUnknown)
    {
      PyErr_SetString(PyExc_TypeError, "Cannot iterate over image with unknown pixel type");
      return -1;
    }

    if (pixelID == sitk::sitkLabelUInt8 || pixelID == sitk::sitkLabelUInt16 || pixelID == sitk::sitkLabelUInt32 ||
        pixelID == sitk::sitkLabelUInt64)
    {
      PyErr_SetString(PyExc_TypeError, "Cannot iterate over label map images");
      return -1;
    }

    const void * buffer = constImage.GetBufferAsVoid();
    if (!buffer)
    {
      PyErr_SetString(PyExc_RuntimeError, "Image buffer is null");
      return -1;
    }

    uint64_t     npix = constImage.GetNumberOfPixels();
    unsigned int ncomp = constImage.GetNumberOfComponentsPerPixel();
    unsigned int compSize = constImage.GetSizeOfPixelComponent();

    self->buf = static_cast<const char *>(buffer);
    self->pos = 0;
    self->num_pixels = static_cast<Py_ssize_t>(npix);
    self->pixel_id = static_cast<int>(pixelID);
    self->num_components = static_cast<int>(ncomp);
    self->bytes_per_pixel = static_cast<Py_ssize_t>(compSize) * static_cast<Py_ssize_t>(ncomp);

    Py_INCREF(pyImageObj);
    self->pyImageRef = pyImageObj;

    return 0;
  }
  catch (const std::exception & e)
  {
    PyErr_SetString(PyExc_RuntimeError, e.what());
    return -1;
  }
}


static void
sitkImagePixelIterator_dealloc(sitkImagePixelIterator * self)
{
  Py_XDECREF(self->pyImageRef);
  self->pyImageRef = nullptr;

  PyTypeObject * type = Py_TYPE((PyObject *)self);
  freefunc       free_func = (freefunc)PyType_GetSlot(type, Py_tp_free);
  free_func((PyObject *)self);
  Py_DECREF(type);
}


static PyObject *
sitkImagePixelIterator_iter(PyObject * self)
{
  Py_INCREF(self);
  return self;
}


static PyObject *
sitkImagePixelIterator_next(sitkImagePixelIterator * self)
{
  if (self->pos >= self->num_pixels)
  {
    return NULL; // StopIteration
  }

  const char * p = self->buf + self->pos * self->bytes_per_pixel;
  self->pos++;

  switch (self->pixel_id)
  {
    // --- Integer scalar types ---
    case sitk::sitkUInt8:
      return PyLong_FromUnsignedLong(*reinterpret_cast<const uint8_t *>(p));
    case sitk::sitkInt8:
      return PyLong_FromLong(*reinterpret_cast<const int8_t *>(p));
    case sitk::sitkUInt16:
      return PyLong_FromUnsignedLong(*reinterpret_cast<const uint16_t *>(p));
    case sitk::sitkInt16:
      return PyLong_FromLong(*reinterpret_cast<const int16_t *>(p));
    case sitk::sitkUInt32:
      return PyLong_FromUnsignedLong(*reinterpret_cast<const uint32_t *>(p));
    case sitk::sitkInt32:
      return PyLong_FromLong(*reinterpret_cast<const int32_t *>(p));
    case sitk::sitkUInt64:
      return PyLong_FromUnsignedLongLong(*reinterpret_cast<const uint64_t *>(p));
    case sitk::sitkInt64:
      return PyLong_FromLongLong(*reinterpret_cast<const int64_t *>(p));

    // --- Float scalar types ---
    case sitk::sitkFloat32:
      return PyFloat_FromDouble(static_cast<double>(*reinterpret_cast<const float *>(p)));
    case sitk::sitkFloat64:
      return PyFloat_FromDouble(*reinterpret_cast<const double *>(p));

    // --- Complex types ---
    case sitk::sitkComplexFloat32:
    {
      const float * cf = reinterpret_cast<const float *>(p);
      return PyComplex_FromDoubles(static_cast<double>(cf[0]), static_cast<double>(cf[1]));
    }
    case sitk::sitkComplexFloat64:
    {
      const double * cd = reinterpret_cast<const double *>(p);
      return PyComplex_FromDoubles(cd[0], cd[1]);
    }

    // --- Vector integer types ---
    case sitk::sitkVectorUInt8:
    {
      int             n = self->num_components;
      const uint8_t * vp = reinterpret_cast<const uint8_t *>(p);
      PyObject *      t = PyTuple_New(n);
      if (!t)
        return NULL;
      for (int i = 0; i < n; i++)
        PyTuple_SetItem(t, i, PyLong_FromUnsignedLong(vp[i]));
      return t;
    }
    case sitk::sitkVectorInt8:
    {
      int            n = self->num_components;
      const int8_t * vp = reinterpret_cast<const int8_t *>(p);
      PyObject *     t = PyTuple_New(n);
      if (!t)
        return NULL;
      for (int i = 0; i < n; i++)
        PyTuple_SetItem(t, i, PyLong_FromLong(vp[i]));
      return t;
    }
    case sitk::sitkVectorUInt16:
    {
      int              n = self->num_components;
      const uint16_t * vp = reinterpret_cast<const uint16_t *>(p);
      PyObject *       t = PyTuple_New(n);
      if (!t)
        return NULL;
      for (int i = 0; i < n; i++)
        PyTuple_SetItem(t, i, PyLong_FromUnsignedLong(vp[i]));
      return t;
    }
    case sitk::sitkVectorInt16:
    {
      int             n = self->num_components;
      const int16_t * vp = reinterpret_cast<const int16_t *>(p);
      PyObject *      t = PyTuple_New(n);
      if (!t)
        return NULL;
      for (int i = 0; i < n; i++)
        PyTuple_SetItem(t, i, PyLong_FromLong(vp[i]));
      return t;
    }
    case sitk::sitkVectorUInt32:
    {
      int              n = self->num_components;
      const uint32_t * vp = reinterpret_cast<const uint32_t *>(p);
      PyObject *       t = PyTuple_New(n);
      if (!t)
        return NULL;
      for (int i = 0; i < n; i++)
        PyTuple_SetItem(t, i, PyLong_FromUnsignedLong(vp[i]));
      return t;
    }
    case sitk::sitkVectorInt32:
    {
      int             n = self->num_components;
      const int32_t * vp = reinterpret_cast<const int32_t *>(p);
      PyObject *      t = PyTuple_New(n);
      if (!t)
        return NULL;
      for (int i = 0; i < n; i++)
        PyTuple_SetItem(t, i, PyLong_FromLong(vp[i]));
      return t;
    }
    case sitk::sitkVectorUInt64:
    {
      int              n = self->num_components;
      const uint64_t * vp = reinterpret_cast<const uint64_t *>(p);
      PyObject *       t = PyTuple_New(n);
      if (!t)
        return NULL;
      for (int i = 0; i < n; i++)
        PyTuple_SetItem(t, i, PyLong_FromUnsignedLongLong(vp[i]));
      return t;
    }
    case sitk::sitkVectorInt64:
    {
      int             n = self->num_components;
      const int64_t * vp = reinterpret_cast<const int64_t *>(p);
      PyObject *      t = PyTuple_New(n);
      if (!t)
        return NULL;
      for (int i = 0; i < n; i++)
        PyTuple_SetItem(t, i, PyLong_FromLongLong(vp[i]));
      return t;
    }
    case sitk::sitkVectorFloat32:
    {
      int           n = self->num_components;
      const float * vp = reinterpret_cast<const float *>(p);
      PyObject *    t = PyTuple_New(n);
      if (!t)
        return NULL;
      for (int i = 0; i < n; i++)
        PyTuple_SetItem(t, i, PyFloat_FromDouble(static_cast<double>(vp[i])));
      return t;
    }
    case sitk::sitkVectorFloat64:
    {
      int            n = self->num_components;
      const double * vp = reinterpret_cast<const double *>(p);
      PyObject *     t = PyTuple_New(n);
      if (!t)
        return NULL;
      for (int i = 0; i < n; i++)
        PyTuple_SetItem(t, i, PyFloat_FromDouble(vp[i]));
      return t;
    }

    default:
      PyErr_SetString(PyExc_TypeError, "Unsupported pixel type for iteration");
      return NULL;
  }
}


static PyType_Slot sitkImagePixelIterator_slots[] = { { Py_tp_dealloc, (void *)sitkImagePixelIterator_dealloc },
                                                      { Py_tp_doc,
                                                        (void *)"Fast pixel iterator for SimpleITK Image objects" },
                                                      { Py_tp_iter, (void *)sitkImagePixelIterator_iter },
                                                      { Py_tp_iternext, (void *)sitkImagePixelIterator_next },
                                                      { Py_tp_init, (void *)sitkImagePixelIterator_init },
                                                      { Py_tp_new, (void *)sitkImagePixelIterator_new },
                                                      { 0, NULL } };

static PyType_Spec sitkImagePixelIteratorType_spec = { "simpleitk.ImagePixelIterator",
                                                       sizeof(sitkImagePixelIterator),
                                                       0,
                                                       Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HEAPTYPE,
                                                       sitkImagePixelIterator_slots };


extern "C"
{

  int
  InitImagePixelIteratorType(PyObject * module)
  {
    PyObject * type = PyType_FromSpec(&sitkImagePixelIteratorType_spec);
    if (!type)
    {
      return -1;
    }

    if (PyModule_AddObject(module, "ImagePixelIterator", type) < 0)
    {
      Py_DECREF(type);
      return -1;
    }

    return 0;
  }

} // extern "C"
