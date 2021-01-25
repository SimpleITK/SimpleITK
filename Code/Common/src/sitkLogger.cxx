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

#include "sitkLogger.h"
#include "sitkExceptionObject.h"
#include <iostream>
#include "itkOutputWindow.h"
#include "itkObjectFactory.h"

namespace itk
{
namespace simple
{

namespace
{
class SimpleLoggerAdaptor : public itk::OutputWindow
{
public:
  using Self = SimpleLoggerAdaptor;
  using Superclass = itk::OutputWindow;
  using Pointer = SmartPointer<Self>;


  itkNewMacro(Self);
  itkTypeMacro(SimpleLoggerAdaptor, OutputWindow);

  void
  SetSimpleLogger(itk::simple::LoggerBase * logger)
  {
    m_That = logger;
  }

  void
  DisplayText(const char * t) override
  {
    if (m_That)
    {
      m_That->DisplayText(t);
    }
    else
    {
      Superclass::DisplayText(t);
    }
  }

  void
  DisplayErrorText(const char * t) override
  {
    if (m_That)
    {
      m_That->DisplayErrorText(t);
    }
    else
    {
      Superclass::DisplayErrorText(t);
    }
  }

  void
  DisplayWarningText(const char * t) override
  {
    if (m_That)
    {
      m_That->DisplayWarningText(t);
    }
    else
    {
      Superclass::DisplayWarningText(t);
    }
  }

  void
  DisplayDebugText(const char * t) override
  {
    if (m_That)
    {
      m_That->DisplayDebugText(t);
    }
    else
    {
      Superclass::DisplayDebugText(t);
    }
  }

  void
  DisplayGenericOutputText(const char * t) override
  {
    if (m_That)
    {
      m_That->DisplayGenericOutputText(t);
    }
    else
    {
      Superclass::DisplayGenericOutputText(t);
    }
  }

protected:
  itk::simple::LoggerBase * m_That{ nullptr };

  SimpleLoggerAdaptor() = default;
  ~SimpleLoggerAdaptor() override = default;
};


} // namespace

LoggerBase::~LoggerBase() {}

ITKLogger
LoggerBase::SetAsGlobalITKLogger()
{
  auto                  logger = SimpleLoggerAdaptor::New();
  SimpleLoggerAdaptor * ptrLogger = logger;

  auto itkDeleteEventCallback = [this, ptrLogger](const itk::EventObject &) { this->RemoveObject(ptrLogger); };

  auto itkObserverID = logger->AddObserver(itk::DeleteEvent(), itkDeleteEventCallback);

  auto loggerCallback = [ptrLogger, itkObserverID]() {
    ptrLogger->SetSimpleLogger(nullptr);
    ptrLogger->RemoveObserver(itkObserverID);
  };

  AddObjectCallback(logger, loggerCallback);

  logger->SetSimpleLogger(this);

  ITKLogger oldLogger = GetGlobalITKLogger();

  itk::OutputWindow::SetInstance(logger);
  return oldLogger;
}


ITKLogger
LoggerBase::GetGlobalITKLogger()
{
  return ITKLogger(itk::OutputWindow::GetInstance());
}

void
LoggerBase::DisplayErrorText(const char * txt)
{
  return this->DisplayText(txt);
}

void
LoggerBase::DisplayWarningText(const char * txt)
{
  return this->DisplayText(txt);
}

void
LoggerBase::DisplayGenericOutputText(const char * txt)
{
  return this->DisplayText(txt);
}

void
LoggerBase::DisplayDebugText(const char * txt)
{
  return this->DisplayText(txt);
}

std::string
LoggerBase::GetName() const
{
  return ObjectOwnedBase::GetName();
}

void
LoggerBase::SetName(const std::string & n)
{
  ObjectOwnedBase::SetName(n);
}

ITKLogger::ITKLogger(itk::OutputWindow * ow)
  : m_OutputWindow(ow)
{
  if (m_OutputWindow)
  {
    m_OutputWindow->Register();
  }
  LoggerBase::SetName("ITKLogger");
}

ITKLogger::ITKLogger(const ITKLogger & other)
  : LoggerBase(other)
  , m_OutputWindow(other.m_OutputWindow)
{
  if (m_OutputWindow)
  {
    m_OutputWindow->Register();
  }
}

ITKLogger &
ITKLogger::operator=(ITKLogger o)
{
  using std::swap;

  if (o.GetOwnedByObjects())
  {
    sitkExceptionMacro("ITKLogger::GetOwnedByObjects is true unable to copy.")
  }
  // todo: check there are no callbacks.

  swap(m_OutputWindow, o.m_OutputWindow);
  this->SetName(o.GetName());
  return *this;
}


ITKLogger::~ITKLogger()
{
  if (GetOwnedByObjects())
  {
    sitkWarningMacro("ITKLogger::GetOwnedByObjects is true.")
  }
  if (m_OutputWindow)
  {
    m_OutputWindow->UnRegister();
    m_OutputWindow = nullptr;
  }
}

void
ITKLogger::DisplayText(const char * t)
{
  if (m_OutputWindow)
  {
    m_OutputWindow->DisplayText(t);
  }
}

void
ITKLogger::DisplayErrorText(const char * t)
{
  if (m_OutputWindow)
  {
    m_OutputWindow->DisplayErrorText(t);
  }
}

void
ITKLogger::DisplayWarningText(const char * t)
{
  if (m_OutputWindow)
  {
    m_OutputWindow->DisplayWarningText(t);
  }
}

void
ITKLogger::DisplayGenericOutputText(const char * t)
{
  if (m_OutputWindow)
  {
    m_OutputWindow->DisplayGenericOutputText(t);
  }
}

void
ITKLogger::DisplayDebugText(const char * t)
{
  if (m_OutputWindow)
  {
    m_OutputWindow->DisplayDebugText(t);
  }
}

ITKLogger
ITKLogger::SetAsGlobalITKLogger()
{
  if (!m_OutputWindow)
  {
    sitkExceptionMacro("Unable to set global ITK logger to nullptr.")
  }
  ITKLogger oldLogger = GetGlobalITKLogger();
  itk::OutputWindow::SetInstance(m_OutputWindow);
  return oldLogger;
}

} // namespace simple
} // namespace itk
