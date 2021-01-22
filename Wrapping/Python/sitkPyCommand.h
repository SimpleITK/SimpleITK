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

#ifndef sitkPyCommand_h
#define sitkPyCommand_h

#include "sitkCommand.h"



#ifndef PyObject_HEAD
struct _object;
using PyObject = _object;
#endif

namespace itk
{
namespace simple
{

/** \class PyCommand
 *  \brief Command subclass that calls a Python callable object, e.g.
 *  a Python function.
 *
 * With this class, arbitrary Python callable objects (e.g. functions)
 * can be associated with an instance to be used in AddObserver calls.
 *
 * Based of the WrapITK itkPyCommand class originally contributed by
 * Charl P. Botha <cpbotha |AT| ieee.org>.
 */
class PyCommand
  : public itk::simple::Command
{
public:
  using Super = Command;

  PyCommand();
  ~PyCommand();

  /**
   * Assign a Python callable object to be used.  You don't have to keep
   * a binding to the callable, PyCommand will also take out a reference
   * to make sure the Callable sticks around.
   */
  void SetCallbackPyCallable(PyObject *obj);

  PyObject * GetCallbackPyCallable();

  virtual void Execute(void);

  #ifndef SWIG
  // export for access in the custom ProcessObject method for callables
  using Super::SetOwnedByObjects;
  using Super::GetOwnedByObjects;
  using Super::OwnedByObjectsOn;
  using Super::OwnedByObjectsOff;
  #endif

private:
  PyObject *m_Object;
};

} // namespace simple
} // namespace itk

#endif // _sitkPyCommand_h
