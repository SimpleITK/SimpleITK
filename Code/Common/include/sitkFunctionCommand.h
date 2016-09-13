/*=========================================================================
*
*  Copyright Insight Software Consortium
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
#ifndef sitkFunctionCommand_h
#define sitkFunctionCommand_h


#include "sitkCommand.h"

#include "nsstd/functional.h"

namespace itk {
namespace simple {

/** \class FunctionCommand
 * \brief A Command class which allows setting an external function,
 * or member function.
 */
class SITKCommon_EXPORT FunctionCommand:
    public Command
{
public:

  typedef FunctionCommand Self;

  FunctionCommand();

  virtual void Execute(void);

  /** Generic method to set a class's member function to be called in
   *  the Execute method.
   */
  template <class T>
    void SetCallbackFunction ( T *object, void(T::* pMemberFunction )() )
  {
    m_Function = nsstd::bind(pMemberFunction, object);
  }

  /** Set a C-Style function to be called in the Execute method */
  void SetCallbackFunction ( void(* pFunction )() );

  /** Set a C-Style function with a void* clientData as an
    *  argument. The caller is responsible for managing the life of
    *  the clientData and that it's valid when Execute is called with
    *  the clientData.
    */
  void SetCallbackFunction( void(* pFunction )(void *), void *clientData );

private:

  typedef nsstd::function<void()> FunctionObjectType;
  FunctionObjectType m_Function;

};

} // end namespace simple
} // end namespace itk

#endif
