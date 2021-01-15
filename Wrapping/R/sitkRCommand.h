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

#ifndef sitkRCommand_h
#define sitkRCommand_h

#include "sitkCommand.h"




namespace itk
{
namespace simple
{

/** \class RCommand
 *  \brief Command subclass that calls an R callable object, e.g.
 *  an R  function.
 *
 * With this class, arbitrary R functions
 * can be associated with an instance to be used in AddObserver calls.
 *
 * Written by Richard Beare <richard.beare |AT| ieee.org, based on
 * sitkPyCommand,
 * which was based on the WrapITK itkPyCommand class originally contributed by
 * Charl P. Botha <cpbotha |AT| ieee.org>.
 */

#include "Rinternals.h"

class RCommand
  : public itk::simple::Command
{
public:
  // Standard "Self" typedef.
  using Self = RCommand;
  using Super = Command;

  RCommand();
  ~RCommand();

  /**
   * Assign a R callable object to be used.  You don't have to keep
   * a binding to the callable, RCommand will preserve the objects
   * across library calls
   */
  /* This method is called from AddCommand, defined in R.i */
  /* It is a simplified interface that doesn't allow separate passing
   * of the function and environment, which usually just makes things
   * more confusing
   */
  void SetFunctionClosure(SEXP FN);

  SEXP GetCallbackRCallable();

  virtual void Execute(void);

  #ifndef SWIG
  // export for access in the custom ProcessObject method for callables
  using Super::SetOwnedByObjects;
  using Super::GetOwnedByObjects;
  using Super::OwnedByObjectsOn;
  using Super::OwnedByObjectsOff;
  #endif


protected:

  void SetCallbackRCallable(SEXP obj);
  void SetCallbackREnviron(SEXP rho);

private:
  SEXP m_Object;
  SEXP m_Environ;
  // the function closure is stored to
  // allow safe cleanup
  SEXP m_FunctionClosure;
};

} // namespace simple
} // namespace itk

#endif // _sitkRCommand_h
