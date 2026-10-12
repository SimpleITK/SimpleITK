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
#include <cstring>
#include <vector>

#include "sitkImage.h"
#include "sitkImportImageFilter.h"

namespace sitk = itk::simple;

// Python is written in C
#ifdef __cplusplus
extern "C"
{
#endif

  // NOTE: PySequence_Fast()/PySequence_Fast_GET_ITEM() are not usable here -
  // this module is built against the Limited API (Py_LIMITED_API), which
  // does not expose the direct-struct-access macros those rely on. Use the
  // slower but ABI-stable PySequence_Size()/PySequence_GetItem() instead.
  static bool
  PySequenceToVectorUInt(PyObject * seq, std::vector<unsigned int> & out)
  {
    const Py_ssize_t n = PySequence_Size(seq);
    if (n < 0)
    {
      return false;
    }
    out.resize(static_cast<size_t>(n));
    for (Py_ssize_t i = 0; i < n; ++i)
    {
      PyObject * item = PySequence_GetItem(seq, i);
      if (!item)
      {
        return false;
      }
      const long v = PyLong_AsLong(item);
      Py_DECREF(item);
      if (v == -1 && PyErr_Occurred())
      {
        return false;
      }
      out[static_cast<size_t>(i)] = static_cast<unsigned int>(v);
    }
    return true;
  }

  static bool
  PySequenceToVectorDouble(PyObject * seq, std::vector<double> & out)
  {
    const Py_ssize_t n = PySequence_Size(seq);
    if (n < 0)
    {
      return false;
    }
    out.resize(static_cast<size_t>(n));
    for (Py_ssize_t i = 0; i < n; ++i)
    {
      PyObject * item = PySequence_GetItem(seq, i);
      if (!item)
      {
        return false;
      }
      const double v = PyFloat_AsDouble(item);
      Py_DECREF(item);
      if (v == -1.0 && PyErr_Occurred())
      {
        return false;
      }
      out[static_cast<size_t>(i)] = v;
    }
    return true;
  }

  /** Construct a SimpleITK Image that is a zero-copy view of a writable,
   * C-contiguous Python buffer-protocol object. The buffer's Py_buffer
   * export is pinned (not just given an extra reference) for exactly as long as the
   * underlying ITK image object exists, via Image::TieBufferLifetime() -
   * see sitkImage.h.
   */
  static PyObject *
  sitk_GetImageViewFromArray(PyObject * SWIGUNUSEDPARM(self), PyObject * args)
  {
    PyObject *   pyBufferObj = NULL;
    PyObject *   pySize = NULL;
    PyObject *   pySpacing = NULL;
    PyObject *   pyOrigin = NULL;
    PyObject *   pyDirection = NULL;
    int          pixelIDValue = 0;
    unsigned int numberOfComponents = 1;

    if (!PyArg_ParseTuple(args,
                          "OOiIOOO",
                          &pyBufferObj,
                          &pySize,
                          &pixelIDValue,
                          &numberOfComponents,
                          &pySpacing,
                          &pyOrigin,
                          &pyDirection))
    {
      return NULL;
    }

    std::vector<unsigned int> size;
    std::vector<double>       spacing;
    std::vector<double>       origin;
    std::vector<double>       direction;

    if (!PySequenceToVectorUInt(pySize, size) || !PySequenceToVectorDouble(pySpacing, spacing) ||
        !PySequenceToVectorDouble(pyOrigin, origin) || !PySequenceToVectorDouble(pyDirection, direction))
    {
      return NULL;
    }

    // Require a writable, C-contiguous export - this single call rejects
    // read-only objects (e.g. bytes, read-only NumPy arrays) and
    // non-contiguous views (e.g. transposed NumPy arrays) with a BufferError,
    // since ImportImageFilter assumes one flat, natural-order buffer and
    // writing into memory Python believes is read-only would be undefined
    // behavior.
    Py_buffer view;
    std::memset(&view, 0, sizeof(Py_buffer));
    if (PyObject_GetBuffer(pyBufferObj, &view, PyBUF_C_CONTIGUOUS | PyBUF_WRITABLE | PyBUF_FORMAT) != 0)
    {
      return NULL;
    }

    sitk::Image image;
    try
    {
      switch (static_cast<sitk::PixelIDValueEnum>(pixelIDValue))
      {
        case sitk::sitkInt8:
        case sitk::sitkVectorInt8:
          image =
            sitk::ImportAsInt8(static_cast<int8_t *>(view.buf), size, spacing, origin, direction, numberOfComponents);
          break;
        case sitk::sitkUInt8:
        case sitk::sitkVectorUInt8:
          image =
            sitk::ImportAsUInt8(static_cast<uint8_t *>(view.buf), size, spacing, origin, direction, numberOfComponents);
          break;
        case sitk::sitkInt16:
        case sitk::sitkVectorInt16:
          image =
            sitk::ImportAsInt16(static_cast<int16_t *>(view.buf), size, spacing, origin, direction, numberOfComponents);
          break;
        case sitk::sitkUInt16:
        case sitk::sitkVectorUInt16:
          image = sitk::ImportAsUInt16(
            static_cast<uint16_t *>(view.buf), size, spacing, origin, direction, numberOfComponents);
          break;
        case sitk::sitkInt32:
        case sitk::sitkVectorInt32:
          image =
            sitk::ImportAsInt32(static_cast<int32_t *>(view.buf), size, spacing, origin, direction, numberOfComponents);
          break;
        case sitk::sitkUInt32:
        case sitk::sitkVectorUInt32:
          image = sitk::ImportAsUInt32(
            static_cast<uint32_t *>(view.buf), size, spacing, origin, direction, numberOfComponents);
          break;
        case sitk::sitkInt64:
        case sitk::sitkVectorInt64:
          image =
            sitk::ImportAsInt64(static_cast<int64_t *>(view.buf), size, spacing, origin, direction, numberOfComponents);
          break;
        case sitk::sitkUInt64:
        case sitk::sitkVectorUInt64:
          image = sitk::ImportAsUInt64(
            static_cast<uint64_t *>(view.buf), size, spacing, origin, direction, numberOfComponents);
          break;
        case sitk::sitkFloat32:
        case sitk::sitkVectorFloat32:
          image =
            sitk::ImportAsFloat(static_cast<float *>(view.buf), size, spacing, origin, direction, numberOfComponents);
          break;
        case sitk::sitkFloat64:
        case sitk::sitkVectorFloat64:
          image =
            sitk::ImportAsDouble(static_cast<double *>(view.buf), size, spacing, origin, direction, numberOfComponents);
          break;
        default:
          PyErr_SetString(PyExc_TypeError,
                          "GetImageViewFromArray does not support this pixel type "
                          "(e.g. complex and label pixel types are not supported "
                          "by the underlying Import filter).");
          PyBuffer_Release(&view);
          return NULL;
      }
    }
    catch (const std::exception & e)
    {
      PyBuffer_Release(&view);
      std::string msg = "Exception thrown in SimpleITK GetImageViewFromArray: ";
      msg += e.what();
      PyErr_SetString(PyExc_RuntimeError, msg.c_str());
      return NULL;
    }

    // From here on, `image` is the sole reference (ITK refcount 1) to the
    // freshly-imported itk::Image, so pin the buffer export to it now,
    // before any other sitk::Image copy can be made or the wrapper is
    // handed back to Python. Image::TieBufferLifetime() calls this callback
    // exactly once, when the last Image sharing this same underlying data
    // is destroyed - view is captured by value, so the callback owns its
    // own copy of the Py_buffer descriptor.
    image.TieBufferLifetime([view]() mutable {
      PyGILState_STATE gstate = PyGILState_Ensure();
      PyBuffer_Release(&view);
      PyGILState_Release(gstate);
    });

    return SWIG_NewPointerObj(new sitk::Image(std::move(image)), SWIGTYPE_p_itk__simple__Image, SWIG_POINTER_OWN);
  }

#ifdef __cplusplus
} // end extern "C"
#endif
