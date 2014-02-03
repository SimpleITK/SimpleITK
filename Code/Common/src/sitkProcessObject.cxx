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
#include "sitkCommand.h"

#include "itkProcessObject.h"
#include "itkCommand.h"

#include <iostream>
#include <algorithm>

#include "nsstd/functional.h"

namespace itk {
namespace simple {

namespace
{
static bool GlobalDefaultDebug = false;

static itk::AnyEvent eventAnyEvent;
static itk::AbortEvent eventAbortEvent;
static itk::DeleteEvent eventDeleteEvent;
static itk::EndEvent eventEndEvent;;
static itk::IterationEvent eventIterationEvent;
static itk::ProgressEvent eventProgressEvent;
static itk::StartEvent eventStartEvent;
static itk::UserEvent eventUserEvent;


// Create an ITK EventObject from the SimpleITK enumerated type.
const itk::EventObject &GetITKEventObject(EventEnum e)
{
  switch (e)
    {
    case sitkAnyEvent:
      return eventAnyEvent;
    case sitkAbortEvent:
      return eventAbortEvent;
    case sitkDeleteEvent:
      return eventDeleteEvent;
    case sitkEndEvent:
      return eventEndEvent;
    case sitkIterationEvent:
      return eventIterationEvent;
    case sitkProgressEvent:
      return eventProgressEvent;
    case sitkStartEvent:
      return eventStartEvent;
    case sitkUserEvent:
      return eventUserEvent;
    default:
      sitkExceptionMacro("LogicError: Unexpected event case!");
    }
}

// Local class to adapt a sitk::Command to ITK's command.
// It utilizes a raw pointer, and relies on the sitk
// ProcessObject<->Command reference to automatically remove it.
class SimpleAdaptorCommand
  : public itk::Command
{
public:

  typedef SimpleAdaptorCommand Self;
  typedef SmartPointer< Self >  Pointer;

  itkNewMacro(Self);

  itkTypeMacro(SimpleAdaptorCommand, Command);

  void SetSimpleCommand( itk::simple::Command *cmd )
    {
      m_That=cmd;
    }

  /**  Invoke the member function. */
  virtual void Execute(Object *, const EventObject & )
  {
    if (m_That)
      {
      m_That->Execute();
      }
  }

  /**  Invoke the member function with a const object */
  virtual void Execute(const Object *, const EventObject & )
  {
    if ( m_That )
      {
      m_That->Execute();
      }
  }

protected:
  itk::simple::Command *                    m_That;
  SimpleAdaptorCommand():m_That(0) {}
  virtual ~SimpleAdaptorCommand() {}

private:
  SimpleAdaptorCommand(const Self &); //purposely not implemented
  void operator=(const Self &);        //purposely not implemented
};

// utility method to find commands in list of pairs
bool rm_pred(const itk::simple::Command *cmd, const std::pair<EventEnum, Command*> &i) throw()
{
  return cmd == i.second;
}

// less than comparison command pointers
bool cmp_cmd_pred(const std::pair<EventEnum, Command*> &i, const std::pair<EventEnum, Command*> &j) throw()
{
  return i.second < j.second;
}

// is equal comparison of command pointers
bool eq_cmd_pred(const std::pair<EventEnum, Command*> &i, const std::pair<EventEnum, Command*> &j) throw()
{
  return i.second == j.second;
}

} // end anonymous namespace

//----------------------------------------------------------------------------

//
// Default constructor that initializes parameters
//
ProcessObject::ProcessObject ()
  : m_Debug(ProcessObject::GetGlobalDefaultDebug()),
    m_NumberOfThreads(ProcessObject::GetGlobalDefaultNumberOfThreads()),
    m_ActiveProcess(NULL),
    m_ProgressMeasurement(0.0)
{
}


//
// Destructor
//
ProcessObject::~ProcessObject ()
{
  // ensure to remove reference between sitk commands and process object
  Self::RemoveAllCommands();
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


void ProcessObject::SetDebug(bool debugFlag)
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


void ProcessObject::GlobalWarningDisplayOn()
{
  itk::Object::GlobalWarningDisplayOn();
}


void ProcessObject::GlobalWarningDisplayOff()
{
  itk::Object::GlobalWarningDisplayOff();
}


bool ProcessObject::GetGlobalWarningDisplay()
{
  return itk::Object::GetGlobalWarningDisplay();
}


void ProcessObject::SetGlobalWarningDisplay(bool flag)
{
  itk::Object::SetGlobalWarningDisplay(flag);
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


int ProcessObject::AddCommand(EventEnum event, Command &cmd)
{
  // add to our list of event, command pairs
  m_Commands.push_back(EventCommandPairType(event,&cmd));

  // register ourselves with the command
  cmd.AddProcessObject(this);

  return 0;
}


void ProcessObject::RemoveAllCommands()
{
  // set's the m_Commands to an empty list via a swap
  std::list<EventCommandPairType> oldCommands;
  swap(oldCommands, m_Commands);

  // we must only call RemoveProcessObject once for each command
  // so make a unique list of the Commands.
  oldCommands.sort(cmp_cmd_pred);
  oldCommands.unique(eq_cmd_pred);

  std::list<EventCommandPairType>::iterator i = oldCommands.begin();
  while( i != oldCommands.end() )
    {
    i++->second->RemoveProcessObject(this);
    }
}


bool ProcessObject::HasCommand( EventEnum event ) const
{
  std::list<EventCommandPairType>::const_iterator i = m_Commands.begin();
  while( i != m_Commands.end() )
    {
    if (i->first == event)
      {
      return true;
      }
    ++i;
    }
  return false;
}


float ProcessObject::GetProgress( ) const
{
  if ( this->m_ActiveProcess )
    {
    return this->m_ActiveProcess->GetProgress();
    }
  return m_ProgressMeasurement;
}


void ProcessObject::Abort()
{
  if ( this->m_ActiveProcess )
    {
    this->m_ActiveProcess->AbortGenerateDataOn();
    }
}


void ProcessObject::PreUpdate(itk::ProcessObject *p)
{
  assert(p);

  // propagate number of threads
  p->SetNumberOfThreads(this->GetNumberOfThreads());

  try
    {
    this->m_ActiveProcess = p;

    // register commands
    for (std::list<EventCommandPairType>::iterator i = m_Commands.begin();
         i != m_Commands.end();
         ++i)
      {
      const itk::EventObject &itkEvent = GetITKEventObject(i->first);

      Command *cmd = i->second;

      // adapt sitk command to itk command
      SimpleAdaptorCommand::Pointer itkCommand = SimpleAdaptorCommand::New();
      itkCommand->SetSimpleCommand(cmd);
      itkCommand->SetObjectName(cmd->GetName()+" "+itkEvent.GetEventName());

      // allow derived classes to customize there observer is added.
      this->PreUpdateAddObserver(p, itkEvent, itkCommand);
      }

    // add command on active process deletion
    itk::SimpleMemberCommand<Self>::Pointer onDelete = itk::SimpleMemberCommand<Self>::New();
    onDelete->SetCallbackFunction(this, &Self::OnActiveProcessDelete);
    p->AddObserver(itk::DeleteEvent(), onDelete);

    }
  catch (...)
    {
    this->m_ActiveProcess = NULL;
    throw;
    }



  if (this->GetDebug())
     {
     std::cout << "Executing ITK filter:" << std::endl;
     p->Print(std::cout);
     }

}


void ProcessObject::PreUpdateAddObserver( itk::ProcessObject *p,
                                          const itk::EventObject &e,
                                          itk::Command *c)
{
  p->AddObserver(e,c);
}

itk::ProcessObject *ProcessObject::GetActiveProcess( )
{
  if (this->m_ActiveProcess)
    {
    return this->m_ActiveProcess;
    }
  sitkExceptionMacro("No active process for \"" << this->GetName() << "\"!");
}


void ProcessObject::OnActiveProcessDelete( )
{
  if (this->m_ActiveProcess)
    {
    this->m_ProgressMeasurement = this->m_ActiveProcess->GetProgress();
    }
  else
    {
    this->m_ProgressMeasurement = 0.0f;
    }
  this->m_ActiveProcess = NULL;
}


void ProcessObject::onCommandDelete(const itk::simple::Command *cmd) throw()
{
  if (this->m_ActiveProcess)
    {
    // no current way to delete the command from the ITK object, fatal
    // due to the ITK process object having an invalid call-back
    std::cerr << "sitk::Fatal: Cannot delete Command during execution!" << std::endl;
    std::terminate();
    // It would be possible to iterate through the registered
    // commands with the active process, and delete the ones referring
    // to cmd, but that doesn't seem work the code.
    }

  // remove all uses of command
  using namespace nsstd::placeholders;
  m_Commands.remove_if(nsstd::bind(rm_pred,cmd,_1));
}

} // end namespace simple
} // end namespace itk
