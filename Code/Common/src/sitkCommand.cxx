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
#include "sitkCommand.h"
#include "sitkProcessObject.h"

namespace itk
{
namespace simple
{

Command::Command( )
{
  ObjectOwnedBase::SetName("Command");
}

Command::~Command( )
{
}

std::string
Command::GetName() const
{
  return ObjectOwnedBase::GetName();
}

void
Command::SetName(const std::string & n)
{
  ObjectOwnedBase::SetName(n);
}

void Command::Execute()
{
}

size_t Command::AddProcessObject(itk::simple::ProcessObject *o)
{
  return AddObjectCallback(reinterpret_cast<itk::Object *>(o), [o, this]() { o->onCommandDelete(this); });
}

size_t Command::RemoveProcessObject(const itk::simple::ProcessObject *co)
{
  return RemoveObject(reinterpret_cast<const itk::Object *>(co));
}


} // end namespace simple
} // end namespace itk
