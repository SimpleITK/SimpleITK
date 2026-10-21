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

// PyModExport shim for PEP 793 / PEP 803 free-threaded ABI support.
// This module entry point wraps SWIG's legacy PyInit_SimpleITK hook in the
// export-hook form required by the free-threaded Stable ABI.

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE
#include <sitkPython.h>

extern "C"
{
  PyMODINIT_FUNC
  PyInit_SimpleITK(void);
}

namespace
{

static int
sitk_exec(PyObject * m)
{
  PyObject * swig_module = PyInit_SimpleITK();
  if (swig_module == NULL)
  {
    return -1;
  }

  PyObject * swig_dict = PyModule_GetDict(swig_module);
  if (swig_dict == NULL)
  {
    Py_DECREF(swig_module);
    return -1;
  }

  PyObject * key = NULL;
  PyObject * value = NULL;
  Py_ssize_t pos = 0;

  while (PyDict_Next(swig_dict, &pos, &key, &value))
  {
    if (PyObject_SetAttr(m, key, value) < 0)
    {
      Py_DECREF(swig_module);
      return -1;
    }
  }

  Py_DECREF(swig_module);
  return 0;
}

} // namespace

PyABIInfo_VAR(sitk_abi_info);

static PySlot sitk_slots[] = { PySlot_DATA(Py_mod_name, const_cast<char *>("SimpleITK")),
                               PySlot_DATA(Py_mod_doc,
                                           const_cast<char *>("SimpleITK: Simple Image Transformation Kit")),
                               PySlot_DATA(Py_mod_abi, &sitk_abi_info),
                               PySlot_FUNC(Py_mod_exec, sitk_exec),
                               { 0 } };

extern "C"
{
  PyMODEXPORT_FUNC
  PyModExport_SimpleITK(void)
  {
    return sitk_slots;
  }

} // extern "C"
