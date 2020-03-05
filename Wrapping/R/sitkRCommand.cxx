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

// The python header defines _POSIX_C_SOURCE without a preceding #undef
#include <iostream>
#include <Rinternals.h>

#include "sitkRCommand.h"
#include "sitkExceptionObject.h"




namespace itk
{
namespace simple
{


RCommand::RCommand()
  : m_Object(R_NilValue),
    m_Environ(R_NilValue),
    m_FunctionClosure(R_NilValue)
{
}

RCommand::~RCommand()
{
  R_ReleaseObject(this->m_Object);
  R_ReleaseObject(this->m_FunctionClosure);
}

void RCommand::SetCallbackRCallable(SEXP obj)
{
  if (obj != this->m_Object)
    {
      if (this->m_Object != R_NilValue)
        {
          // unprotect
          R_ReleaseObject(this->m_Object);
        }
    this->m_Object = obj;
    R_PreserveObject(this->m_Object);
    }
}
void RCommand::SetCallbackREnviron(SEXP rho)
{
  if (rho != this->m_Environ)
    {
      // Don't need to do any releasing of the
      // environment as it is part of the callable,
      // and we haven't needed to explicitly protect it
      this->m_Environ = rho;
    }
}

void RCommand::SetFunctionClosure(SEXP FN)
{
  if (FN != this->m_FunctionClosure)
    {
      if (this->m_FunctionClosure != R_NilValue)
        {
          R_ReleaseObject(this->m_FunctionClosure);
        }
      this->m_FunctionClosure = FN;
      R_PreserveObject(this->m_FunctionClosure);

       // set up expression for evaluation
      SEXP R_fcall;
      // Rf_lang1 creates an executable pair list with one
      // element
      R_fcall = PROTECT(Rf_lang1(this->m_FunctionClosure));
      this->SetCallbackRCallable(R_fcall);
      this->SetCallbackREnviron(CLOENV(this->m_FunctionClosure));
      UNPROTECT(1);
    }
}


SEXP RCommand::GetCallbackRCallable()
{
  return this->m_Object;
}

void RCommand::Execute()
{
  // if null do nothing
  if ((!this->m_Object) || (!this->m_Environ))
    {
    return;
    }

  else
    {
    SEXP result;
    // retrieve the environment for passing to eval
    result = eval(this->m_Object, this->m_Environ);
    if (result == NULL)
      {
        sitkExceptionMacro(<<"There was an error executing the "
                           <<"R Callable.");
      }
    }
}


} // namespace simple
} // namespace itk
