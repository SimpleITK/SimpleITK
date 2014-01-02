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
#include "sitkProcessObject.h"

#include "itkProcessObject.h"

#include <iostream>

namespace itk {
namespace simple {

namespace
{
static bool GlobalDefaultDebug = false;
}

//----------------------------------------------------------------------------

//
// Default constructor that initializes parameters
//
ProcessObject::ProcessObject ()
  : m_Debug(ProcessObject::GetGlobalDefaultDebug()),
    m_NumberOfThreads(ProcessObject::GetGlobalDefaultNumberOfThreads())
{
}

//
// Default destructor
//
ProcessObject::~ProcessObject ()
{
}

std::ostream & ProcessObject::ToStringHelper(std::ostream &os, const char &v)
{
  os << int(v);
  return os;
}

std::ostream & ProcessObject::ToStringHelper(std::ostream &os, const signed char &v)
{
  os << int(v);
  return os;
}

std::ostream & ProcessObject::ToStringHelper(std::ostream &os, const unsigned char &v)
{
  os << int(v);
  return os;
}


void ProcessObject::DebugOn()
{
  this->m_Debug = true;
}

void ProcessObject::DebugOff()
{
  this->m_Debug = false;
}

bool ProcessObject::GetDebug() const
{
  return this->m_Debug;
}


void ProcessObject::SetDebug( bool debugFlag)
{
  this->m_Debug = debugFlag;
}


void ProcessObject::GlobalDefaultDebugOn()
{
  GlobalDefaultDebug = true;
}

void ProcessObject::GlobalDefaultDebugOff()

{
  GlobalDefaultDebug = false;
}

bool ProcessObject::GetGlobalDefaultDebug()
{
  return GlobalDefaultDebug;
}

void ProcessObject::SetGlobalDefaultDebug(bool debugFlag)
{
  GlobalDefaultDebug = debugFlag;
}



void ProcessObject::SetGlobalDefaultNumberOfThreads(unsigned int n)
{
  MultiThreader::SetGlobalDefaultNumberOfThreads(n);
}

unsigned int ProcessObject::GetGlobalDefaultNumberOfThreads()
{
  return MultiThreader::GetGlobalDefaultNumberOfThreads();
}

void ProcessObject::SetNumberOfThreads(unsigned int n)
{
  m_NumberOfThreads = n;
}

unsigned int ProcessObject::GetNumberOfThreads() const
{
  return m_NumberOfThreads;
}


void ProcessObject::PreUpdate( itk::ProcessObject *p )
{
  assert(p);

  if (this->GetDebug())
     {
     std::cout << "Executing ITK filter:" << std::endl;
     p->Print(std::cout);
     }

  p->SetNumberOfThreads(this->GetNumberOfThreads());

}

} // end namespace simple
} // end namespace itk
