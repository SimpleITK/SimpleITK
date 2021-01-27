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

#include "sitkObjectOwnedBase.h"
#include "sitkExceptionObject.h"
#include "itkObject.h"

namespace itk
{
namespace simple
{


ObjectOwnedBase::~ObjectOwnedBase()
{
  ExecuteCallbacks();
}


ObjectOwnedBase::ObjectOwnedBase(const ObjectOwnedBase & o)
  : NonCopyable()
  , m_Name(o.m_Name)
{
  if (o.m_OwnedByObjects)
  {
    sitkExceptionMacro("Unable to copy object with OwnedByObjects enabled.");
  }
  m_ReferencedObjectsCallbacks = o.m_ReferencedObjectsCallbacks;
}


std::string
ObjectOwnedBase::GetName() const
{
  return this->m_Name;
}


void
ObjectOwnedBase::SetName(const std::string & name)
{
  this->m_Name = name;
}

size_t
ObjectOwnedBase::AddObjectCallback(itk::Object * o, std::function<void()> onDelete)
{
  // add new element and callback ( even if it already exists )
  m_ReferencedObjectsCallbacks.emplace(o, std::move(onDelete));
  return m_ReferencedObjectsCallbacks.size();
}

size_t
ObjectOwnedBase::RemoveObject(const itk::Object * co)
{
  // removes all elements matching
  m_ReferencedObjectsCallbacks.erase(const_cast<itk::Object *>(co));
  const size_t ret = m_ReferencedObjectsCallbacks.size();
  if (ret == 0 && GetOwnedByObjects())
  {
    delete this;
  }
  return ret;
}

void
ObjectOwnedBase::SetOwnedByObjects(bool o)
{
  if (m_ReferencedObjectsCallbacks.empty())
  {
    // AddObjectCallback must be called before setting ownership.
    sitkWarningMacro("No objects known to own this object.")
  }
  this->m_OwnedByObjects = o;
}

bool
ObjectOwnedBase::GetOwnedByObjects() const
{
  return this->m_OwnedByObjects;
}

void
ObjectOwnedBase::OwnedByObjectsOn()
{
  this->SetOwnedByObjects(true);
}

void
ObjectOwnedBase::OwnedByObjectsOff()
{
  this->SetOwnedByObjects(false);
}


void ObjectOwnedBase::ExecuteCallbacks()
{
  // move to local variable to prevent any call backs modifying the multimap of objects
  decltype(m_ReferencedObjectsCallbacks) referencedObjects;
  referencedObjects.swap(m_ReferencedObjectsCallbacks);

  for (auto & p : referencedObjects)
  {
    p.second();
  }

  if (!m_ReferencedObjectsCallbacks.empty())
  {
    sitkWarningMacro("Detected modification of referenced objects during callback execution!")
  }
}

} // namespace simple
} // namespace itk
