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

#include "sitkImageBuffer.h"
#include "sitkImage.h"
#include "sitkPixelIDValues.h"
#include <cstring>
#include <iostream>

// #define sitkImageBuffer_DEBUG

namespace sitk = itk::simple;


// Buffer object structure
typedef struct
{
  PyObject_HEAD PyObject * pyImageRef; // Python Image object reference (stored directly as member)
  int                      ndim;
  Py_ssize_t               shape[SITK_MAX_DIMENSION + 1];
  Py_ssize_t               strides[SITK_MAX_DIMENSION + 1];
} sitkImageBuffer;

// Helper function to get the sitk::Image from buffer object
static const sitk::Image *
GetImageFromBuffer(sitkImageBuffer * self)
{
  if (self->pyImageRef)
  {
    // Use the helper function defined in Python.i to extract the Image pointer
    return sitk_GetImagePointerFromPyObject(self->pyImageRef);
  }
  return nullptr;
}

// Helper function to get format string for pixel type
static const char *
GetFormatString(sitk::PixelIDValueEnum pixelID)
{
  switch (pixelID)
  {
    case sitk::sitkUInt8:
      return "B"; // unsigned char
    case sitk::sitkInt8:
      return "b"; // signed char
    case sitk::sitkUInt16:
      return "H"; // unsigned short
    case sitk::sitkInt16:
      return "h"; // signed short
    case sitk::sitkUInt32:
      return "I"; // unsigned int
    case sitk::sitkInt32:
      return "i"; // signed int
    case sitk::sitkUInt64:
      return "Q"; // unsigned long long
    case sitk::sitkInt64:
      return "q"; // signed long long
    case sitk::sitkFloat32:
      return "f"; // float
    case sitk::sitkFloat64:
      return "d"; // double
    case sitk::sitkComplexFloat32:
      return "Zf"; // complex float
    case sitk::sitkComplexFloat64:
      return "Zd"; // complex double
    case sitk::sitkVectorUInt8:
      return "B";
    case sitk::sitkVectorInt8:
      return "b";
    case sitk::sitkVectorUInt16:
      return "H";
    case sitk::sitkVectorInt16:
      return "h";
    case sitk::sitkVectorUInt32:
      return "I";
    case sitk::sitkVectorInt32:
      return "i";
    case sitk::sitkVectorUInt64:
      return "Q";
    case sitk::sitkVectorInt64:
      return "q";
    case sitk::sitkVectorFloat32:
      return "f";
    case sitk::sitkVectorFloat64:
      return "d";
    case sitk::sitkLabelUInt8:
      return "B";
    case sitk::sitkLabelUInt16:
      return "H";
    case sitk::sitkLabelUInt32:
      return "I";
    case sitk::sitkLabelUInt64:
      return "Q";
    default:
      return "B"; // fallback to unsigned char
  }
}

// Helper function to get item size from format string, with special handling for complex types
static Py_ssize_t
GetItemSizeFromFormat(const char * format)
{
  if (!format)
  {
    PyErr_SetString(PyExc_ValueError, "Format string is NULL");
    return -1;
  }

  // Handle complex types that PyBuffer_SizeFromFormat doesn't support
  if (format[0] == 'Z' && format[1] != '\0')
  {
    // spell-check-disable
    // Complex format: "Zf" -> 2 * sizeof(float), "Zd" -> 2 * sizeof(double)
    // spell-check-enable
    Py_ssize_t base_size = PyBuffer_SizeFromFormat(format + 1);
    if (base_size > 0)
    {
      return base_size * 2;
    }
    else
    {
      // Use hard-coded sizes for complex types as fallback
      if (format[1] == 'f')
      {
        return sizeof(float) * 2; // 8 bytes for complex float
      }
      else if (format[1] == 'd')
      {
        return sizeof(double) * 2; // 16 bytes for complex double
      }
      else
      {
        PyErr_Format(PyExc_ValueError, "Unsupported complex format: '%s'", format);
        return -1;
      }
    }
  }

  // Use Python's official size calculation for standard formats
  Py_ssize_t size = PyBuffer_SizeFromFormat(format);

  // if SizeFromFormat fails, it returns -1 and sets an error
  return size;
}

// Helper function to check if a pixel type is a vector type
static bool
IsVectorPixelType(sitk::PixelIDValueEnum pixelID)
{
  if (pixelID == sitk::sitkUnknown)
  {
    return false;
  }
  switch (pixelID)
  {
    case sitk::sitkVectorUInt8:
    case sitk::sitkVectorInt8:
    case sitk::sitkVectorUInt16:
    case sitk::sitkVectorInt16:
    case sitk::sitkVectorUInt32:
    case sitk::sitkVectorInt32:
    case sitk::sitkVectorUInt64:
    case sitk::sitkVectorInt64:
    case sitk::sitkVectorFloat32:
    case sitk::sitkVectorFloat64:
      return true;
    default:
      return false;
  }
}

// Buffer protocol implementation
static int
sitkImageBuffer_getbuffer(PyObject * exporter, Py_buffer * view, int flags)
{
  sitkImageBuffer *   self = (sitkImageBuffer *)exporter;
  const sitk::Image * imagePtr = nullptr;

  // Determine writable vs readonly access
  bool isWritable = (flags & PyBUF_WRITABLE) == PyBUF_WRITABLE;

  if (isWritable)
  {
    PyErr_SetString(PyExc_BufferError, "Cannot create writable buffer for image");
    return -1;
  }

  if ((flags & PyBUF_F_CONTIGUOUS) == PyBUF_F_CONTIGUOUS && (flags & PyBUF_ANY_CONTIGUOUS) != PyBUF_ANY_CONTIGUOUS)
  {
    PyErr_SetString(PyExc_BufferError, "SimpleITK images are C-contiguous, cannot provide Fortran-contiguous buffer");
    return -1;
  }


  // if flags is zero set to PyBUF_SIMPLE and produce a warning
  if (flags == 0)
  {
    flags = PyBUF_SIMPLE;
    PyErr_WarnEx(PyExc_RuntimeWarning, "Buffer flag was zero, using PyBUF_SIMPLE", 1);
  }

  // Zero-initialize the entire Py_buffer structure
  memset(view, 0, sizeof(Py_buffer));

  // Read-only access is fine with reference
  imagePtr = GetImageFromBuffer(self);
  if (!imagePtr)
  {
    PyErr_SetString(PyExc_BufferError, "Buffer object has no associated image");
    return -1;
  }

  try
  {
    const sitk::Image &    image = *imagePtr;
    const unsigned int     dimension = image.GetDimension();
    sitk::PixelIDValueEnum pixelID = image.GetPixelID();
    const unsigned int     totalDimensions = dimension + (IsVectorPixelType(pixelID) ? 1 : 0);


    if (pixelID == sitk::sitkUnknown || pixelID == sitk::sitkLabelUInt8 || pixelID == sitk::sitkLabelUInt16 ||
        pixelID == sitk::sitkLabelUInt32 || pixelID == sitk::sitkLabelUInt64)
    {
      PyErr_SetString(PyExc_BufferError, "Cannot create buffer for image with unknown or label pixel type");
      return -1;
    }

    // Get buffer pointer and calculate size
    const void * buffer_ptr = image.GetBufferAsVoid();
    if (!buffer_ptr)
    {
      PyErr_SetString(PyExc_BufferError, "Image buffer is null");
      return -1;
    }

#ifdef sitkImageBuffer_DEBUG
    // Debug message for buffer creation
    std::cerr << "[DEBUG] Creating Py_buffer for image size=[";

    std::vector<unsigned int> size = image.GetSize();
    for (size_t i = 0; i < size.size(); ++i)
    {
      if (i > 0)
        std::cerr << ", ";
      std::cerr << size[i];
    }
    std::cerr << "], pixel_type=" << image.GetPixelIDTypeAsString() << ", ptr=" << buffer_ptr << ", flags=0x"
              << std::hex << flags << std::dec << ", self=" << (void *)self
              << ", writable=" << (isWritable ? "yes" : "no") << std::endl;
    std::cerr.flush();
#endif

    // Get format string and calculate item size from it
    const char * format = GetFormatString(pixelID);

    Py_ssize_t itemSize = GetItemSizeFromFormat(format);
#ifdef sitkImageBuffer_DEBUG
    std::cerr << "[DEBUG] Format string: '" << format << "'" << std::endl;
    std::cerr << "[DEBUG] GetItemSizeFromFormat returned: " << itemSize << std::endl;
#endif

    if (itemSize < 0)
    {
      // Error was already set by GetItemSizeFromFormat
      return -1;
    }

    // Fill in the required fields (structure already zero-initialized)
    view->buf = (void *)buffer_ptr;
    view->itemsize = itemSize;
    view->ndim = (flags & PyBUF_ND) == PyBUF_ND ? totalDimensions : 1;

    // Calculate total buffer size
    Py_ssize_t buffer_size = itemSize;
    for (unsigned int i = 0; i < totalDimensions; ++i)
    {
      buffer_size *= self->shape[i];
    }
    view->len = buffer_size;

    // Set readonly flag based on writable request
    view->readonly = !isWritable;

    // Handle format flag
    if ((flags & PyBUF_FORMAT) == PyBUF_FORMAT)
    {
      view->format = (char *)format; // Use the already-computed format string
    }

    // Use the pre-allocated shape array
    if ((flags & PyBUF_ND) == PyBUF_ND)
    {
      view->shape = self->shape;

      // Handle strides - use the pre-allocated strides array
      if ((flags & PyBUF_STRIDES) == PyBUF_STRIDES)
      {
        view->strides = self->strides;
      }
    }


    // Increment reference count for the exporter object
    view->obj = (PyObject *)self;
    Py_INCREF((PyObject *)self);

    return 0;
  }
  catch (const std::exception & e)
  {
    PyErr_SetString(PyExc_BufferError, e.what());
    return -1;
  }
}

#ifdef sitkImageBuffer_DEBUG
static void
sitkImageBuffer_releasebuffer(PyObject * exporter, Py_buffer * view)
{
  sitkImageBuffer * self = (sitkImageBuffer *)exporter;
  // Debug message for buffer release
  const sitk::Image * imagePtr = GetImageFromBuffer(self);
  if (imagePtr)
  {
    const sitk::Image &       image = *imagePtr;
    std::vector<unsigned int> size = image.GetSize();
    std::cerr << "[DEBUG] Releasing Py_buffer for image size=[";
    for (size_t i = 0; i < size.size(); ++i)
    {
      if (i > 0)
        std::cerr << ", ";
      std::cerr << size[i];
    }
    std::cerr << "], ptr=" << view->buf << std::endl;
    std::cerr.flush();
  }
  else
  {
    std::cerr << "[DEBUG] Releasing Py_buffer (no image)" << std::endl;
    std::cerr.flush();
  }

  // Verify that view->obj is the same as self (safety check)
  if (view->obj && view->obj != (PyObject *)self)
  {
    std::cerr << "[WARNING] Buffer release: view->obj != self" << std::endl;
  }
}
#endif

// Object life-cycle methods
static PyObject *
sitkImageBuffer_new(PyTypeObject * type, PyObject * args, PyObject * kwds)
{
  sitkImageBuffer * self = (sitkImageBuffer *)PyType_GenericAlloc(type, 1);
  return (PyObject *)self;
}

static int
sitkImageBuffer_init(sitkImageBuffer * self, PyObject * args, PyObject * kwds)
{
  PyObject * pyImageObj = nullptr;

  // Parse the SimpleITK Image object argument
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
    // Extract SimpleITK Image from SWIG-wrapped Python object using helper function
    sitk::Image * sitkImage = sitk_GetImagePointerFromPyObject(pyImageObj);
    if (!sitkImage)
    {
      PyErr_SetString(PyExc_TypeError, "Expected a SimpleITK Image object");
      return -1;
    }

    // Initialize shape and strides arrays based on the image
    unsigned int              dimension = sitkImage->GetDimension();
    std::vector<unsigned int> size = sitkImage->GetSize();
    sitk::PixelIDValueEnum    pixelID = sitkImage->GetPixelID();

    // Calculate total dimensions (add one for vector images)
    const unsigned int totalDimensions = dimension + (IsVectorPixelType(pixelID) ? 1 : 0);

    // Store the total dimensions in the struct
    self->ndim = totalDimensions;

    // Initialize shape array (reverse order for NumPy compatibility)
    for (unsigned int i = 0; i < dimension; ++i)
    {
      self->shape[dimension - 1 - i] = size[i];
    }
    if (IsVectorPixelType(pixelID))
    {
      self->shape[dimension] = sitkImage->GetNumberOfComponentsPerPixel();
    }
    // Clear unused entries
    for (unsigned int i = totalDimensions; i < SITK_MAX_DIMENSION; ++i)
    {
      self->shape[i] = 0;
    }

    // Initialize strides array using format-based size calculation
    const char * format = GetFormatString(pixelID);
    Py_ssize_t   itemSize = GetItemSizeFromFormat(format);
    if (itemSize < 0)
    {
      // Error was already set by GetItemSizeFromFormat
      return -1;
    }

    Py_ssize_t stride = itemSize;
    for (int i = totalDimensions - 1; i >= 0; --i)
    {
      self->strides[i] = stride;
      stride *= self->shape[i];
    }
    // Clear unused entries
    for (unsigned int i = totalDimensions; i < SITK_MAX_DIMENSION; ++i)
    {
      self->strides[i] = 0;
    }

    // Store the Python Image object reference in the member
    // Increment reference count to keep the image alive
    Py_INCREF(pyImageObj);
    self->pyImageRef = pyImageObj;

    return 0; // Success
  }
  catch (const std::exception & e)
  {
    PyErr_SetString(PyExc_RuntimeError, e.what());
    return -1;
  }
}

static void
sitkImageBuffer_dealloc(sitkImageBuffer * self)
{
#ifdef sitkImageBuffer_DEBUG
  // Debug message for ImageBuffer deallocation
  const sitk::Image * imagePtr = GetImageFromBuffer(self);
  if (imagePtr)
  {
    const sitk::Image &       image = *imagePtr;
    std::vector<unsigned int> size = image.GetSize();
    std::cerr << "[DEBUG] Deallocating ImageBuffer for image size=[";
    for (size_t i = 0; i < size.size(); ++i)
    {
      if (i > 0)
        std::cerr << ", ";
      std::cerr << size[i];
    }
    std::cerr << "], pixel_type=" << image.GetPixelIDTypeAsString() << ", self=" << (void *)self << std::endl;
    std::cerr.flush();
  }
  else
  {
    std::cerr << "[DEBUG] Deallocating ImageBuffer (no image), self="
              << ", self=" << (void *)self << std::endl;
    std::cerr.flush();
  }
#endif

  // Decrement reference to Python Image object
  Py_DECREF(self->pyImageRef);
  self->pyImageRef = nullptr;

  PyTypeObject * type = Py_TYPE((PyObject *)self);
#ifdef Py_LIMITED_API
  freefunc free_func = (freefunc)PyType_GetSlot(type, Py_tp_free);
  free_func((PyObject *)self);
#else
  type->tp_free((PyObject *)self);
#endif
  Py_DECREF(type);
}

// String representation
static PyObject *
sitkImageBuffer_repr(sitkImageBuffer * self)
{
  const sitk::Image * imagePtr = GetImageFromBuffer(self);
  if (!imagePtr)
  {
    return PyUnicode_FromString("<sitkImageBuffer: no image>");
  }

  const sitk::Image &       image = *imagePtr;
  std::vector<unsigned int> size = image.GetSize();
  std::string               sizeStr = "[";
  for (size_t i = 0; i < size.size(); ++i)
  {
    if (i > 0)
      sizeStr += ", ";
    sizeStr += std::to_string(size[i]);
  }
  sizeStr += "]";

  std::string repr = "<sitkImageBuffer: " + std::to_string(image.GetDimension()) + "D image, size=" + sizeStr +
                     ", pixel_type=" + image.GetPixelIDTypeAsString() + ">";

  return PyUnicode_FromString(repr.c_str());
}

// Method to create a weak memoryview from this buffer object
// Note: This does NOT keep a strong reference to the ImageBuffer or Image.
// The caller must ensure the source Image/ImageBuffer remains alive.
static PyObject *
sitkImageBuffer_GetWeakMemoryView(sitkImageBuffer * self, PyObject * args)
{
  int flags = PyBUF_FULL_RO; // Default to read-only

  // Parse optional flags argument
  if (!PyArg_ParseTuple(args, "|i", &flags))
  {
    return nullptr;
  }

#ifdef sitkImageBuffer_DEBUG
  // Add debug printing message
  std::cerr << "[DEBUG] sitkImageBuffer_GetWeakMemoryView called, self=" << (void *)self << ", flags: 0x" << std::hex
            << flags << std::dec << std::endl;
#endif

#if 1
  Py_buffer view;
  if (PyObject_GetBuffer((PyObject *)self, &view, flags) < 0)
  {
    return nullptr;
  }

  PyObject * memoryview = PyMemoryView_FromBuffer(&view);

  PyBuffer_Release(&view);

#else
  PyObject * memoryview = PyMemoryView_FromObject((PyObject *)self);
#endif
  if (!memoryview)
  {
    PyBuffer_Release(&view);
    return nullptr;
  }
#ifdef sitkImageBuffer_DEBUG
  std::cerr << "[DEBUG] Created memoryview, self=" << (void *)self << ", memoryview=" << (void *)memoryview
            << std::endl;
#endif
  return memoryview;
}

// Method definitions
static PyMethodDef sitkImageBuffer_methods[] = {
  { "get_weak_memoryview",
    (PyCFunction)sitkImageBuffer_GetWeakMemoryView,
    METH_VARARGS,
    "get_weak_memoryview(flags=PyBUF_RECORDS) -> memoryview\n\n"
    "Create a weak memoryview from this ImageBuffer.\n\n"
    "IMPORTANT: This method does NOT keep a strong reference to the ImageBuffer\n"
    "or the source Image object. The returned memoryview is 'weak' - it does not\n"
    "prevent the source objects from being garbage collected. The caller must\n"
    "ensure the source Image remains alive for the lifetime of\n"
    "the returned memoryview, otherwise accessing the memoryview will result in\n"
    "undefined behavior (likely a segmentation fault).\n\n"
    "Parameters:\n"
    "    flags (int, optional): Buffer protocol flags (default: PyBUF_FULL_RO)\n\n"
    "Returns:\n"
    "    memoryview: A memoryview object providing access to the image data.\n"
    "                This memoryview does NOT hold strong references." },
  { NULL } // Sentinel
};

// Getter for _image_ref property (stable API compatible)
static PyObject *
sitkImageBuffer_get_image_ref(sitkImageBuffer * self, void * closure)
{
  if (self->pyImageRef)
  {
    Py_INCREF(self->pyImageRef);
    return self->pyImageRef;
  }
  Py_RETURN_NONE;
}

// Property definitions (using PyGetSetDef, which is stable API compatible)
static PyGetSetDef sitkImageBuffer_getsetters[] = {
  { "_image_ref",
    (getter)sitkImageBuffer_get_image_ref,
    NULL, // No setter - read-only
    "Reference to the Python Image object",
    NULL },
  { NULL } // Sentinel
};

// Type slots for Limited API
static PyType_Slot sitkImageBuffer_slots[] = {
  { Py_tp_dealloc, (void *)sitkImageBuffer_dealloc },
  { Py_tp_repr, (void *)sitkImageBuffer_repr },
  { Py_tp_doc, (void *)"SimpleITK Image Holder for Buffer Protocol" },
  { Py_tp_methods, sitkImageBuffer_methods },
  { Py_tp_getset, sitkImageBuffer_getsetters },
  { Py_tp_init, (void *)sitkImageBuffer_init },
  { Py_tp_new, (void *)sitkImageBuffer_new },
  { Py_bf_getbuffer, (void *)sitkImageBuffer_getbuffer },
#ifdef sitkImageBuffer_DEBUG
  { Py_bf_releasebuffer, (void *)sitkImageBuffer_releasebuffer },
#endif
  { 0, NULL } // Sentinel
};

// Type spec for Limited API
static PyType_Spec sitkImageBufferType_spec = {
  "simpleitk.ImageBuffer",                  // name
  sizeof(sitkImageBuffer),                  // basic size
  0,                                        // item size
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HEAPTYPE, // flags
  sitkImageBuffer_slots                     // slots
};

extern "C"
{

  int
  InitImageBufferType(PyObject * module)
  {
    PyObject * type = PyType_FromSpec(&sitkImageBufferType_spec);
    if (!type)
    {
      return -1;
    }

    if (PyModule_AddObject(module, "ImageBuffer", type) < 0)
    {
      Py_DECREF(type);
      return -1;
    }

    return 0;
  }

} // extern "C"
