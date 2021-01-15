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
#ifndef sitkCommand_h
#define sitkCommand_h


#include "sitkCommon.h"
#include "sitkObjectOwnedBase.h"

#include <set>

namespace itk {
namespace simple {

class ProcessObject;

/** \class Command
 * \brief An implementation of the Command design pattern for callback.
 *
 * This class provides a callback mechanism for event that occur from
 * the ProcessObject. These commands can be utilized to observe these
 * events.
 *
 * The Command can be created on the stack, and will automatically
 * unregistered it's self when destroyed.
 *
 * For more information see the page \ref CommandPage.
 */
class SITKCommon_EXPORT Command : public ObjectOwnedBase
{
public:
  /** \brief Default Constructor */
  Command();

  /** Destructor. */
  virtual ~Command() override;

  /** Set/Get Command Name */
  std::string
  GetName() const override;
  void
  SetName(const std::string & n) override;

  /** The method that defines action to be taken by the command */
  virtual void
  Execute();

protected:
  friend class itk::simple::ProcessObject;

#ifndef SWIG
  // internal methods to maintain reference between ProcessObject and
  // Command, so when either is destroyed, the other will be notified.
  //
  // Return value is the number of referenced process objects after
  // operation.
  virtual size_t
  AddProcessObject(itk::simple::ProcessObject * o);
  virtual size_t
  RemoveProcessObject(const itk::simple::ProcessObject * o);

#endif
};

} // end namespace simple
} // end namespace itk

#endif
