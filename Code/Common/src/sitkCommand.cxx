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
#include "sitkCommand.h"
#include "sitkProcessObject.h"

namespace itk
{
namespace simple
{

Command::Command( )
  : m_OwnedByProcessObjects(false),
    m_Name("Command")
{
}

Command::~Command( )
{
  // tell the process object that we are being destroyed so that it
  // can remove this as an observer
  std::set<itk::simple::ProcessObject*>::iterator i = m_ReferencedObjects.begin();
  while( i !=  m_ReferencedObjects.end() )
    {
    (*i++)->onCommandDelete(this);
    }
}


void Command::Execute(void)
{
}

size_t Command::AddProcessObject(itk::simple::ProcessObject *o)
{
  // unique add process object to set
  m_ReferencedObjects.insert(o);
  return m_ReferencedObjects.size();
}

size_t Command::RemoveProcessObject(const itk::simple::ProcessObject *co)
{
  ProcessObject *o = const_cast<ProcessObject*>(co);
  m_ReferencedObjects.erase(o);
  const size_t ret = m_ReferencedObjects.size();
  if (ret==0 && m_OwnedByProcessObjects)
    {
    delete this;
    }
  return ret;
}


} // end namespace simple
} // end namespace itk
