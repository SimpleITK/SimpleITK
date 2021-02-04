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
#include "sitkProcessObject.h"
#include "sitkCommand.h"

#include "itkProcessObject.h"
#include "itkCommand.h"
#include "sitkFunctionCommand.h"
#include "itkImageToImageFilter.h"
#include "itkTextOutput.h"

#include <iostream>
#include <algorithm>
#include <cstring>
#include <functional>

namespace itk {
namespace simple {

namespace
{
static bool GlobalDefaultDebug = false;

static itk::AnyEvent eventAnyEvent;
static itk::AbortEvent eventAbortEvent;
static itk::DeleteEvent eventDeleteEvent;
static itk::EndEvent eventEndEvent;
static itk::IterationEvent eventIterationEvent;
static itk::ProgressEvent eventProgressEvent;
static itk::StartEvent eventStartEvent;
static itk::UserEvent eventUserEvent;
static itk::MultiResolutionIterationEvent eventMultiResolutionIterationEvent;


// Local class to adapt a sitk::Command to ITK's command.
// It utilizes a raw pointer, and relies on the sitk
// ProcessObject<->Command reference to automatically remove it.
class SimpleAdaptorCommand
  : public itk::Command
{
public:

  using Self = SimpleAdaptorCommand;
  using Pointer = SmartPointer< Self >;

  itkNewMacro(Self);

  itkTypeMacro(SimpleAdaptorCommand, Command);

  void SetSimpleCommand( itk::simple::Command *cmd )
    {
      m_That=cmd;
    }

  /**  Invoke the member function. */
  void Execute(Object *, const EventObject & ) override
  {
    if (m_That)
      {
      m_That->Execute();
      }
  }

  /**  Invoke the member function with a const object */
  void Execute(const Object *, const EventObject & ) override
  {
    if ( m_That )
      {
      m_That->Execute();
      }
  }

  SimpleAdaptorCommand(const Self &) = delete;
  void operator=(const Self &) = delete;

protected:
  itk::simple::Command *                    m_That{nullptr};
  SimpleAdaptorCommand() = default;
  ~SimpleAdaptorCommand() override = default;
};

} // end anonymous namespace

//----------------------------------------------------------------------------

//
// Default constructor that initializes parameters
//
ProcessObject::ProcessObject ()
  : m_Debug(ProcessObject::GetGlobalDefaultDebug()),
    m_NumberOfThreads(itk::MultiThreaderBase::GetGlobalDefaultNumberOfThreads()),
    m_NumberOfWorkUnits(0),
    m_ActiveProcess(nullptr),
    m_ProgressMeasurement(0.0)
{
  static bool firstTime=true;
  if (firstTime)
    {
    if (!strcmp(itk::OutputWindow::GetInstance()->GetNameOfClass(), "Win32OutputWindow"))
      {
      itk::OutputWindow::SetInstance( itk::TextOutput::New() );
      }
    firstTime = false;
    }
}


//
// Destructor
//
ProcessObject::~ProcessObject ()
{
  // ensure to remove reference between sitk commands and process object
  Self::RemoveAllCommands();
}

std::string ProcessObject::ToString() const
{
  std::ostringstream out;

  out << "  Debug: ";
  this->ToStringHelper(out, this->m_Debug) << std::endl;

  out << "  NumberOfThreads: ";
  this->ToStringHelper(out, this->m_NumberOfThreads) << std::endl;

  out << "  NumberOfWorkUnits: ";
  this->ToStringHelper(out, this->m_NumberOfWorkUnits) << std::endl;

  out << "  Commands:" << (m_Commands.empty()?" (none)":"") << std::endl;
  for( const auto &eventCommand : m_Commands)
    {
    assert( eventCommand.m_Command );
    out << "    Event: " << eventCommand.m_Event << " Command: " << eventCommand.m_Command->GetName() << std::endl;
    }

  out << "  ProgressMeasurement: ";
  this->ToStringHelper(out, this->m_ProgressMeasurement) << std::endl;

  out << "  ActiveProcess:" << (this->m_ActiveProcess?"":" (none)") <<std::endl;
  if( this->m_ActiveProcess )
    {
    this->m_ActiveProcess->Print(out, itk::Indent(4));
    }

  return out.str();
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


double ProcessObject::GetGlobalDefaultCoordinateTolerance()
{
  return itk::ImageToImageFilterCommon::GetGlobalDefaultCoordinateTolerance();
}

void ProcessObject::SetGlobalDefaultCoordinateTolerance(double tolerance)
{
  return itk::ImageToImageFilterCommon::SetGlobalDefaultCoordinateTolerance(tolerance);
}

double ProcessObject::GetGlobalDefaultDirectionTolerance()
{
  return itk::ImageToImageFilterCommon::GetGlobalDefaultDirectionTolerance();
}

void ProcessObject::SetGlobalDefaultDirectionTolerance(double tolerance)
{
  return itk::ImageToImageFilterCommon::SetGlobalDefaultDirectionTolerance(tolerance);
}


void ProcessObject::SetGlobalDefaultNumberOfThreads(unsigned int n)
{
  itk::MultiThreaderBase::SetGlobalDefaultNumberOfThreads(n);
}

unsigned int ProcessObject::GetGlobalDefaultNumberOfThreads()
{
  return itk::MultiThreaderBase::GetGlobalDefaultNumberOfThreads();
}

bool ProcessObject::SetGlobalDefaultThreader(const std::string &threader)
{
  auto threaderEnum = itk::MultiThreaderBase::ThreaderTypeFromString(threader);
  if (threaderEnum == itk::MultiThreaderBase::ThreaderEnum::Unknown
#if !defined(ITK_USE_TBB)
      || threaderEnum == itk::MultiThreaderBase::ThreaderEnum::Unknown
#endif
    )
    {
    return false;
    }
  itk::MultiThreaderBase::SetGlobalDefaultThreader(threaderEnum);
  return true;
}

std::string ProcessObject::GetGlobalDefaultThreader()
{
  auto threaderEnum =  itk::MultiThreaderBase::GetGlobalDefaultThreader();
  return itk::MultiThreaderBase::ThreaderTypeToString(threaderEnum);
}


void ProcessObject::SetNumberOfThreads(unsigned int n)
{
  m_NumberOfThreads = n;
}


unsigned int ProcessObject::GetNumberOfThreads() const
{
  return m_NumberOfThreads;
}


void ProcessObject::SetNumberOfWorkUnits(unsigned int n)
{
  m_NumberOfWorkUnits = n;
}


unsigned int ProcessObject::GetNumberOfWorkUnits() const
{
  return m_NumberOfWorkUnits;
}


int ProcessObject::AddCommand(EventEnum event, Command &cmd)
{
  // add to our list of event, command pairs
  m_Commands.emplace_back(event,&cmd);

  // register ourselves with the command
  cmd.AddProcessObject(this);

  if (this->m_ActiveProcess)
    {
    this->AddObserverToActiveProcessObject( m_Commands.back() );
    }
  else
    {
    m_Commands.back().m_ITKTag = std::numeric_limits<unsigned long>::max();
    }

  return 0;
}

int ProcessObject::AddCommand(itk::simple::EventEnum event, const std::function<void()> &func)
{
  std::unique_ptr<FunctionCommand> cmd(new FunctionCommand());
  cmd->SetCallbackFunction(func);

  int id = this->AddCommand(event, *cmd.get());
  cmd->OwnedByObjectsOn();
  cmd.release();
  return id;
}


void ProcessObject::RemoveAllCommands()
{
  // set's the m_Commands to an empty list via a swap
  std::list<EventCommand> oldCommands;
  swap(oldCommands, m_Commands);

  // remove commands from active process object
  std::list<EventCommand>::iterator i = oldCommands.begin();
  while( i != oldCommands.end() && this->m_ActiveProcess )
    {
    this->RemoveObserverFromActiveProcessObject(*i);
    ++i;
    }

  // we must only call RemoveProcessObject once for each command
  // so make a unique list of the Commands.
  oldCommands.sort();
  oldCommands.unique();
  i = oldCommands.begin();
  while( i != oldCommands.end() )
    {
    // note: this may call onCommandDelete, but we have already copied
    // this->m_Command will be empty
    i++->m_Command->RemoveProcessObject(this);
    }
}


bool ProcessObject::HasCommand( EventEnum event ) const
{
  for ( const auto& eventCommand: m_Commands)
    {
    if (eventCommand.m_Event == event)
      {
      return true;
      }
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
  if ( this->GetNumberOfWorkUnits() != 0 )
    {
    p->SetNumberOfWorkUnits(this->GetNumberOfWorkUnits());
    }

  p->GetMultiThreader()->SetMaximumNumberOfThreads(this->GetNumberOfThreads());

  try
    {
    this->m_ActiveProcess = p;

    // add command on active process deletion
    p->AddObserver(eventDeleteEvent, [this](const itk::EventObject &) {this->OnActiveProcessDelete();});

    // register commands
    for (auto &eventCommand: m_Commands )
      {
      this->AddObserverToActiveProcessObject(eventCommand);
      }

    }
  catch (...)
    {
    this->m_ActiveProcess = nullptr;
    throw;
    }

  sitkDebugMacro( "Executing ITK filter:\n" << *p );

}


unsigned long ProcessObject::AddITKObserver( const itk::EventObject &e,
                                             itk::Command *c)
{
  assert(this->m_ActiveProcess);
  return this->m_ActiveProcess->AddObserver(e,c);
}


void ProcessObject::RemoveITKObserver( EventCommand &e )
{
  assert(this->m_ActiveProcess);
  this->m_ActiveProcess->RemoveObserver(e.m_ITKTag);
}


const itk::EventObject &ProcessObject::GetITKEventObject(EventEnum e)
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
    case sitkMultiResolutionIterationEvent:
      return eventMultiResolutionIterationEvent;
    default:
      sitkExceptionMacro("LogicError: Unexpected event case!");
    }
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

  // clear registered command IDs
  for (std::list<EventCommand>::iterator i = m_Commands.begin();
         i != m_Commands.end();
         ++i)
      {
      i->m_ITKTag = std::numeric_limits<unsigned long>::max();
      }

  this->m_ActiveProcess = nullptr;
}


void ProcessObject::onCommandDelete(const itk::simple::Command *cmd) noexcept
{
  // remove command from m_Command book keeping list, and remove it
  // from the  ITK ProcessObject
  std::list<EventCommand>::iterator i =  this->m_Commands.begin();
  while ( i !=  this->m_Commands.end() )
    {
    if ( cmd == i->m_Command )
      {
      if ( this->m_ActiveProcess )
        {
        this->RemoveObserverFromActiveProcessObject( *i );
        }
      this->m_Commands.erase(i++);
      }
    else
      {
      ++i;
      }

    }
}

unsigned long ProcessObject::AddObserverToActiveProcessObject( EventCommand &eventCommand )
{
  assert( this->m_ActiveProcess );

  if (eventCommand.m_ITKTag != std::numeric_limits<unsigned long>::max())
    {
    sitkExceptionMacro("Commands already registered to another process object!");
    }

  const itk::EventObject &itkEvent = GetITKEventObject(eventCommand.m_Event);

  // adapt sitk command to itk command
  SimpleAdaptorCommand::Pointer itkCommand = SimpleAdaptorCommand::New();
  itkCommand->SetSimpleCommand(eventCommand.m_Command);
  itkCommand->SetObjectName(eventCommand.m_Command->GetName()+" "+itkEvent.GetEventName());

  return eventCommand.m_ITKTag = this->AddITKObserver( itkEvent, itkCommand );
}

void ProcessObject::RemoveObserverFromActiveProcessObject( EventCommand &e )
 {
   assert( this->m_ActiveProcess );

   if (e.m_ITKTag != std::numeric_limits<unsigned long>::max() )
     {
     this->RemoveITKObserver(e);
     e.m_ITKTag = std::numeric_limits<unsigned long>::max();
     }

 }

} // end namespace simple
} // end namespace itk
