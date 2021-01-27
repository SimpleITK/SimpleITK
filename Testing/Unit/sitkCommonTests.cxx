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
#include <SimpleITKTestHarness.h>

#include <sitkConditional.h>
#include <sitkCommand.h>
#include <sitkFunctionCommand.h>
#include <sitkCastImageFilter.h>

#include <sitkKernel.h>
#include <sitkVersion.h>
#include <sitkVersionConfig.h>
#include <itkConfigure.h>
#include "sitkLogger.h"
#include <cctype>

#include "itkMacro.h"

TEST( VersionTest, VersionTest)
{
  using Version = itk::simple::Version;

  EXPECT_EQ(Version::MajorVersion(), SimpleITK_VERSION_MAJOR);
  EXPECT_EQ(Version::MinorVersion(), SimpleITK_VERSION_MINOR);
  EXPECT_EQ(Version::PatchVersion(), SimpleITK_VERSION_PATCH);
  //EXPECT_EQ(Version::TweakVersion(), SimpleITK_VERSION_TWEAK);
  std::cout << "Version String: " << Version::VersionString() << std::endl;
  std::cout << "BuildDate String: " << Version::BuildDate() << std::endl;
  EXPECT_EQ(Version::ITKMajorVersion(), ITK_VERSION_MAJOR);
  EXPECT_EQ(Version::ITKMinorVersion(), ITK_VERSION_MINOR);
  EXPECT_EQ(Version::ITKPatchVersion(), ITK_VERSION_PATCH);
  std::cout << "ITK Version String: " << Version::ITKVersionString() << std::endl;

  std::cout << "Extended Version String: " << Version::ExtendedVersionString() << std::endl;

  std::vector<std::string> itk_modules = Version::ITKModulesEnabled();
  EXPECT_NE( std::find( itk_modules.begin(), itk_modules.end(), "ITKCommon" ), itk_modules.end());
  EXPECT_NE( std::find( itk_modules.begin(), itk_modules.end(), "ITKIOImageBase" ), itk_modules.end());
}


TEST( ProcessObject, GlobalTolerance ) {
  // basic coverage test of setting and getting

  namespace sitk = itk::simple;

  EXPECT_EQ( sitk::ProcessObject::GetGlobalDefaultCoordinateTolerance(), 1e-6 );
  EXPECT_EQ( sitk::ProcessObject::GetGlobalDefaultDirectionTolerance(), 1e-6 );

  sitk::ProcessObject::SetGlobalDefaultCoordinateTolerance( 1e-5 );
  EXPECT_EQ( sitk::ProcessObject::GetGlobalDefaultCoordinateTolerance(), 1e-5 );
  EXPECT_EQ( sitk::ProcessObject::GetGlobalDefaultDirectionTolerance(), 1e-6 );

  sitk::ProcessObject::SetGlobalDefaultDirectionTolerance( 1e-4);
  EXPECT_EQ( sitk::ProcessObject::GetGlobalDefaultCoordinateTolerance(), 1e-5 );
  EXPECT_EQ( sitk::ProcessObject::GetGlobalDefaultDirectionTolerance(), 1e-4 );

}

TEST( ProcessObject, GlobalWarning ) {
  // Basic coverage test of setting and getting. Need separate
  // specific check for propagation of warning to ITK.

  namespace sitk = itk::simple;

  EXPECT_TRUE( sitk::ProcessObject::GetGlobalWarningDisplay() );

  sitk::ProcessObject::GlobalWarningDisplayOff();
  EXPECT_FALSE( sitk::ProcessObject::GetGlobalWarningDisplay() );

  sitk::ProcessObject::GlobalWarningDisplayOn();
  EXPECT_TRUE( sitk::ProcessObject::GetGlobalWarningDisplay() );

  sitk::ProcessObject::SetGlobalWarningDisplay(false);
  EXPECT_FALSE( sitk::ProcessObject::GetGlobalWarningDisplay() );

}


TEST( ProcessObject, Command_Register ) {
  // Test the references between Process Objects and command.
  // Try to be mean and break stuff

  namespace sitk = itk::simple;

  // Case 0a: stack,  command first
  {
  sitk::Command cmd;
  sitk::CastImageFilter po1;
  po1.AddCommand(sitk::sitkAnyEvent, cmd);
  EXPECT_TRUE(po1.HasCommand(sitk::sitkAnyEvent));
  }

  // Case 0b: stack, process first
  {
  sitk::CastImageFilter po1;
  sitk::Command cmd;
  po1.AddCommand(sitk::sitkAnyEvent, cmd);
  EXPECT_TRUE(po1.HasCommand(sitk::sitkAnyEvent));
  }

  // Case 1a: single command, command deleted first
  {
  std::unique_ptr<sitk::CastImageFilter> po1(new sitk::CastImageFilter());
  std::unique_ptr<sitk::Command> cmd(new sitk::Command());
  po1->AddCommand(sitk::sitkAnyEvent, *cmd);

  EXPECT_TRUE(po1->HasCommand(sitk::sitkAnyEvent));
  cmd.reset();
  EXPECT_FALSE(po1->HasCommand(sitk::sitkAnyEvent));
  }

  // Case 1b: single command, process deleted first
  {
  std::unique_ptr<sitk::CastImageFilter> po1( new sitk::CastImageFilter());
  std::unique_ptr<sitk::Command> cmd(new sitk::Command());
  po1->AddCommand(sitk::sitkAnyEvent, *cmd);
  po1.reset();
  }

  // Case 2a: single command, multiple processes, command deleted first
  {
  std::unique_ptr<sitk::CastImageFilter> po1(new sitk::CastImageFilter());
  std::unique_ptr<sitk::CastImageFilter> po2(new sitk::CastImageFilter());
  std::unique_ptr<sitk::CastImageFilter> po3(new sitk::CastImageFilter());

  std::unique_ptr<sitk::Command> cmd(new sitk::Command());
  po1->AddCommand(sitk::sitkAnyEvent, *cmd);
  po2->AddCommand(sitk::sitkStartEvent, *cmd);
  po3->AddCommand(sitk::sitkEndEvent, *cmd);
  cmd.reset();
  }

  // Case 2b: single command, multiple processes, processes mostly deleted first
  {
  std::unique_ptr<sitk::CastImageFilter> po1(new sitk::CastImageFilter());
  std::unique_ptr<sitk::CastImageFilter> po2(new sitk::CastImageFilter());
  std::unique_ptr<sitk::CastImageFilter> po3(new sitk::CastImageFilter());

  std::unique_ptr<sitk::Command> cmd(new sitk::Command());
  po1->AddCommand(sitk::sitkAnyEvent, *cmd);
  po2->AddCommand(sitk::sitkStartEvent, *cmd);
  po3->AddCommand(sitk::sitkEndEvent, *cmd);

  EXPECT_TRUE(po1->HasCommand(sitk::sitkAnyEvent));
  EXPECT_TRUE(po2->HasCommand(sitk::sitkStartEvent));
  EXPECT_TRUE(po3->HasCommand(sitk::sitkEndEvent));

  po1.reset();
  EXPECT_TRUE(po2->HasCommand(sitk::sitkStartEvent));
  EXPECT_TRUE(po3->HasCommand(sitk::sitkEndEvent));
  po2.reset();
  EXPECT_TRUE(po3->HasCommand(sitk::sitkEndEvent));
  cmd.reset();
  EXPECT_FALSE(po3->HasCommand(sitk::sitkEndEvent));
  }

  // Case 3a: multiple commands, command deleted mostly first
  {
  std::unique_ptr<sitk::CastImageFilter> po1(new sitk::CastImageFilter());
  std::unique_ptr<sitk::Command> cmd1(new sitk::Command());
  std::unique_ptr<sitk::Command> cmd2(new sitk::Command());
  std::unique_ptr<sitk::Command> cmd3(new sitk::Command());

  po1->AddCommand(sitk::sitkAnyEvent, *cmd1);
  po1->AddCommand(sitk::sitkStartEvent, *cmd2);
  po1->AddCommand(sitk::sitkEndEvent, *cmd3);

  EXPECT_TRUE(po1->HasCommand(sitk::sitkAnyEvent));
  EXPECT_TRUE(po1->HasCommand(sitk::sitkStartEvent));
  EXPECT_TRUE(po1->HasCommand(sitk::sitkEndEvent));

  cmd1.reset();
  EXPECT_FALSE(po1->HasCommand(sitk::sitkAnyEvent));
  EXPECT_TRUE(po1->HasCommand(sitk::sitkStartEvent));
  EXPECT_TRUE(po1->HasCommand(sitk::sitkEndEvent));
  cmd2.reset();
  EXPECT_FALSE(po1->HasCommand(sitk::sitkAnyEvent));
  EXPECT_FALSE(po1->HasCommand(sitk::sitkStartEvent));
  EXPECT_TRUE(po1->HasCommand(sitk::sitkEndEvent));
  po1.reset();
  }

  // Case 3b: multiple commands, process object deleted first
  {
  std::unique_ptr<sitk::CastImageFilter> po1(new sitk::CastImageFilter());
  std::unique_ptr<sitk::Command> cmd1(new sitk::Command());
  std::unique_ptr<sitk::Command> cmd2(new sitk::Command());
  std::unique_ptr<sitk::Command> cmd3(new sitk::Command());
  po1->AddCommand(sitk::sitkAnyEvent, *cmd1);
  po1->AddCommand(sitk::sitkStartEvent, *cmd2);
  po1->AddCommand(sitk::sitkEndEvent, *cmd3);
  po1.reset();

  }


}

TEST( ProcessObject, Command_Add ) {
  // Add command for events and verifies the state

  namespace sitk = itk::simple;

  sitk::CastImageFilter po1;
  sitk::Command cmd;

  // check initial state
  EXPECT_FALSE(po1.HasCommand(sitk::sitkAnyEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkAbortEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkDeleteEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkEndEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkIterationEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkProgressEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkStartEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkUserEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkMultiResolutionIterationEvent));

  po1.AddCommand(sitk::sitkAnyEvent, cmd);
  EXPECT_TRUE(po1.HasCommand(sitk::sitkAnyEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkAbortEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkDeleteEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkEndEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkIterationEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkProgressEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkStartEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkUserEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkMultiResolutionIterationEvent));

  po1.RemoveAllCommands();
  EXPECT_FALSE(po1.HasCommand(sitk::sitkAnyEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkAbortEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkDeleteEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkEndEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkIterationEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkProgressEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkStartEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkUserEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkMultiResolutionIterationEvent));

  po1.AddCommand(sitk::sitkAnyEvent, cmd);
  po1.AddCommand(sitk::sitkAbortEvent, cmd);
  po1.AddCommand(sitk::sitkDeleteEvent, cmd);
  po1.AddCommand(sitk::sitkEndEvent, cmd);
  po1.AddCommand(sitk::sitkIterationEvent, cmd);
  po1.AddCommand(sitk::sitkProgressEvent, cmd);
  po1.AddCommand(sitk::sitkStartEvent, cmd);
  po1.AddCommand(sitk::sitkUserEvent, cmd);
  po1.AddCommand(sitk::sitkMultiResolutionIterationEvent, cmd);

  EXPECT_TRUE(po1.HasCommand(sitk::sitkAnyEvent));
  EXPECT_TRUE(po1.HasCommand(sitk::sitkAbortEvent));
  EXPECT_TRUE(po1.HasCommand(sitk::sitkDeleteEvent));
  EXPECT_TRUE(po1.HasCommand(sitk::sitkEndEvent));
  EXPECT_TRUE(po1.HasCommand(sitk::sitkIterationEvent));
  EXPECT_TRUE(po1.HasCommand(sitk::sitkProgressEvent));
  EXPECT_TRUE(po1.HasCommand(sitk::sitkStartEvent));
  EXPECT_TRUE(po1.HasCommand(sitk::sitkUserEvent));
  EXPECT_TRUE(po1.HasCommand(sitk::sitkMultiResolutionIterationEvent));
}



TEST( ProcessObject, Command_Add_lambda ) {
  // Add command for events and verifies the state

  namespace sitk = itk::simple;

  sitk::CastImageFilter po1;

  // check initial state
  EXPECT_FALSE(po1.HasCommand(sitk::sitkAnyEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkAbortEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkDeleteEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkEndEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkIterationEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkProgressEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkStartEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkUserEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkMultiResolutionIterationEvent));

  po1.AddCommand(sitk::sitkAnyEvent, []{std::cout << "command\n";});
  EXPECT_TRUE(po1.HasCommand(sitk::sitkAnyEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkAbortEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkDeleteEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkEndEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkIterationEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkProgressEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkStartEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkUserEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkMultiResolutionIterationEvent));

  po1.RemoveAllCommands();
  EXPECT_FALSE(po1.HasCommand(sitk::sitkAnyEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkAbortEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkDeleteEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkEndEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkIterationEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkProgressEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkStartEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkUserEvent));
  EXPECT_FALSE(po1.HasCommand(sitk::sitkMultiResolutionIterationEvent));

  po1.AddCommand(sitk::sitkAnyEvent, []{std::cout << "command\n";});
  po1.AddCommand(sitk::sitkAbortEvent, []{std::cout << "command\n";});
  po1.AddCommand(sitk::sitkDeleteEvent, []{std::cout << "command\n";});
  po1.AddCommand(sitk::sitkEndEvent, []{std::cout << "command\n";});
  po1.AddCommand(sitk::sitkIterationEvent, []{std::cout << "command\n";});
  po1.AddCommand(sitk::sitkProgressEvent, []{std::cout << "command\n";});
  po1.AddCommand(sitk::sitkStartEvent, []{std::cout << "command\n";});
  po1.AddCommand(sitk::sitkUserEvent, []{std::cout << "command\n";});
  po1.AddCommand(sitk::sitkMultiResolutionIterationEvent, []{std::cout << "command\n";});

  EXPECT_TRUE(po1.HasCommand(sitk::sitkAnyEvent));
  EXPECT_TRUE(po1.HasCommand(sitk::sitkAbortEvent));
  EXPECT_TRUE(po1.HasCommand(sitk::sitkDeleteEvent));
  EXPECT_TRUE(po1.HasCommand(sitk::sitkEndEvent));
  EXPECT_TRUE(po1.HasCommand(sitk::sitkIterationEvent));
  EXPECT_TRUE(po1.HasCommand(sitk::sitkProgressEvent));
  EXPECT_TRUE(po1.HasCommand(sitk::sitkStartEvent));
  EXPECT_TRUE(po1.HasCommand(sitk::sitkUserEvent));
  EXPECT_TRUE(po1.HasCommand(sitk::sitkMultiResolutionIterationEvent));
}


TEST( ProcessObject, DeleteCommandActiveProcess )
{
  // Test the case of deleting the command while the process is active.
  namespace sitk = itk::simple;

  class DeleteCommandAtCommand
  : public ProcessObjectCommand
  {
  public:
    DeleteCommandAtCommand(itk::simple::ProcessObject &po, float abortAt, Command *cmd)
      : ProcessObjectCommand(po),
        m_AbortAt(abortAt),
        m_Cmd(cmd)
      {
      }

    void Execute( ) override
      {
        if ( m_Process.GetProgress() >= m_AbortAt )
          {
          delete m_Cmd;
          m_Cmd = nullptr;
          }
      }

    float m_AbortAt;
    Command *m_Cmd;
  };

  sitk::CastImageFilter po;
  sitk::Image img(100,100,100, sitk::sitkUInt16);

  sitk::Command *cmd1 = new sitk::Command();
  DeleteCommandAtCommand cmd2(po, .01f, cmd1);

  po.AddCommand(sitk::sitkAnyEvent, *cmd1);
  po.AddCommand(sitk::sitkProgressEvent, cmd2);


  ASSERT_NO_THROW(po.Execute(img)) << "Exception with deleting command";

  EXPECT_FALSE(po.HasCommand(sitk::sitkAnyEvent));
  EXPECT_TRUE(po.HasCommand(sitk::sitkProgressEvent));
}

TEST( ProcessObject, RemoveAllCommandsActiveProcess )
{
  // Test the case of deleting the command while the process is active.
  namespace sitk = itk::simple;

  class RemoveAllCommandsAtCommand
  : public ProcessObjectCommand
  {
  public:
    RemoveAllCommandsAtCommand(itk::simple::ProcessObject &po, float abortAt )
      : ProcessObjectCommand(po),
        m_AbortAt(abortAt)
      {
      }

    void Execute( ) override
      {
        if ( m_Process.GetProgress() >= m_AbortAt )
          {
          std::cout << "Removing All Commands" << std::endl;
          m_Process.RemoveAllCommands();
          std::cout << "Done" << std::endl;
          }
      }

    float m_AbortAt;
  };

  sitk::CastImageFilter po;
  sitk::Image img(100,100,100, sitk::sitkUInt16);

  sitk::Command cmd1;
  RemoveAllCommandsAtCommand cmd2(po, .01f);

  po.AddCommand(sitk::sitkAnyEvent, cmd1);
  po.AddCommand(sitk::sitkProgressEvent, cmd2);


  ASSERT_NO_THROW(po.Execute(img)) << "Exception with remove all commands";

  EXPECT_FALSE(po.HasCommand(sitk::sitkAnyEvent));
  EXPECT_FALSE(po.HasCommand(sitk::sitkProgressEvent));
}


TEST( Event, Test1 )
{
  // Test print of EventEnum with output operator
  namespace sitk = itk::simple;

  std::stringstream ss;
  ss << sitk::sitkAnyEvent;
  EXPECT_EQ("AnyEvent", ss.str());
  ss.str("");
  ss << sitk::sitkAbortEvent;
  EXPECT_EQ("AbortEvent", ss.str());
  ss.str("");
  ss << sitk::sitkDeleteEvent;
  EXPECT_EQ("DeleteEvent", ss.str());
  ss.str("");
  ss << sitk::sitkEndEvent;
  EXPECT_EQ("EndEvent", ss.str());
  ss.str("");
  ss << sitk::sitkIterationEvent;
  EXPECT_EQ("IterationEvent", ss.str());
  ss.str("");
  ss << sitk::sitkProgressEvent;
  EXPECT_EQ("ProgressEvent", ss.str());
  ss.str("");
  ss << sitk::sitkStartEvent;
  EXPECT_EQ("StartEvent", ss.str());
  ss.str("");
  ss << sitk::sitkUserEvent;
  EXPECT_EQ("UserEvent", ss.str());
  ss.str("");
  ss << sitk::sitkMultiResolutionIterationEvent;
  EXPECT_EQ("MultiResolutionIterationEvent", ss.str());
}


TEST( Command, Test1 ) {
  // Basic test.
  namespace sitk = itk::simple;

  sitk::Command cmd1;
  // not copy construct able
  //sitk::Command cmd2(cmd1);

  // not assignable
  //cmd1 = cmd1;

  // Does nothing
  cmd1.Execute();

  EXPECT_EQ( "Command", cmd1.GetName() );
  cmd1.SetName("SomeName");
  EXPECT_EQ( "SomeName", cmd1.GetName() );

}


TEST( ProcessObject, Command_Ownership ) {
  // Test the functionality of the ProcessObject Owning the Command
  namespace sitk = itk::simple;

  static int destroyedCount = 0;

  class HeapCommand
    : public sitk::Command
  {
  public:
    HeapCommand() : v(false) {};
    ~HeapCommand() override {++destroyedCount;}
    void Execute() override {v=true;}
    using Command::SetOwnedByObjects;
    using Command::GetOwnedByObjects;
    using Command::OwnedByObjectsOn;
    using Command::OwnedByObjectsOff;

    bool v;
  };

  {
  // test set/get/on/off
  HeapCommand cmd;
  EXPECT_FALSE(cmd.GetOwnedByObjects());
  cmd.SetOwnedByObjects(true);
  EXPECT_TRUE(cmd.GetOwnedByObjects());
  cmd.OwnedByObjectsOff();
  EXPECT_FALSE(cmd.GetOwnedByObjects());
  cmd.OwnedByObjectsOn();
  EXPECT_TRUE(cmd.GetOwnedByObjects());

  HeapCommand *cmd1 = new HeapCommand();
  cmd1->OwnedByObjectsOn();
  EXPECT_EQ(0,destroyedCount);
  delete cmd1;
  EXPECT_EQ(1,destroyedCount);
  }
  EXPECT_EQ(2,destroyedCount);

  // case 1
  // single po, multiple cmds
  {
  sitk::CastImageFilter po;
  sitk::Image img(5,5, sitk::sitkUInt16);

  HeapCommand *cmd2 = new HeapCommand();
  cmd2->OwnedByObjectsOn();
  po.AddCommand(sitk::sitkAnyEvent, *cmd2);

  EXPECT_FALSE(cmd2->v);
  EXPECT_NO_THROW( po.Execute(img) );
  EXPECT_TRUE(cmd2->v);
  cmd2->v = false;

  HeapCommand *cmd3 = new HeapCommand();
  cmd3->OwnedByObjectsOn();
  po.AddCommand(sitk::sitkAnyEvent, *cmd3);

  EXPECT_FALSE(cmd2->v);
  EXPECT_FALSE(cmd3->v);
  EXPECT_NO_THROW( po.Execute(img) );
  EXPECT_TRUE(cmd2->v);
  EXPECT_TRUE(cmd3->v);
  cmd2->v = false;

  delete cmd3;
  EXPECT_EQ(3,destroyedCount);
  }
  EXPECT_EQ(4,destroyedCount);

  // case 2
  // cmd registered to multiple PO
  {
  std::unique_ptr<sitk::CastImageFilter> po1(new sitk::CastImageFilter());
  std::unique_ptr<sitk::CastImageFilter> po2(new sitk::CastImageFilter());

  HeapCommand *cmd = new HeapCommand();
  cmd->OwnedByObjectsOn();

  po1->AddCommand(sitk::sitkAnyEvent, *cmd);
  po1->AddCommand(sitk::sitkStartEvent, *cmd);

  EXPECT_TRUE(po1->HasCommand(sitk::sitkAnyEvent));
  EXPECT_TRUE(po1->HasCommand(sitk::sitkStartEvent));

  po2->AddCommand(sitk::sitkAnyEvent, *cmd);
  EXPECT_TRUE(po2->HasCommand(sitk::sitkAnyEvent));


  po2.reset();

  EXPECT_TRUE(po1->HasCommand(sitk::sitkAnyEvent));
  EXPECT_TRUE(po1->HasCommand(sitk::sitkStartEvent));
  EXPECT_EQ(4,destroyedCount);
  }
  EXPECT_EQ(5,destroyedCount);


}

TEST( ProcessObject, Threads )
{
  namespace sitk = itk::simple;

  sitk::CastImageFilter po;

  EXPECT_EQ( sitk::ProcessObject::GetGlobalDefaultNumberOfThreads(), po.GetNumberOfThreads() );


  auto strupper = [](std::string s) {
    std::transform( s.begin(), s.end(), s.begin(), [] ( char c ) { return (std::toupper( c ) ); } );
    return s;
  };

  EXPECT_TRUE( sitk::ProcessObject::SetGlobalDefaultThreader("PLATFORM") );
  EXPECT_EQ( "PLATFORM", strupper(sitk::ProcessObject::GetGlobalDefaultThreader()) );


  EXPECT_TRUE( sitk::ProcessObject::SetGlobalDefaultThreader("POOL") );
  EXPECT_EQ( "POOL", strupper(sitk::ProcessObject::GetGlobalDefaultThreader()) );
}

TEST( Command, Test2 ) {
  // Check basic name functionality
  namespace sitk = itk::simple;

  sitk::Command cmd1;


}

TEST( FunctionCommand, Test1 ) {
  // Basic test.
  namespace sitk = itk::simple;

  sitk::FunctionCommand cmd1;
  // not copy construct able
  //sitk::Command cmd2(cmd1);

  // not assignable
  //cmd1 = cmd1;

  // Does nothing
  cmd1.Execute();

  EXPECT_EQ( "FunctionCommand", cmd1.GetName() );
  cmd1.SetName("AnotherName");
  EXPECT_EQ( "AnotherName", cmd1.GetName() );
}

namespace
{

struct MemberFunctionCommandTest
{
  MemberFunctionCommandTest():v(0){}

  void DoSomething() {v=99;}
  int v;
};

int gValue = 0;
void functionCommand()
{
  gValue = 98;
}

void functionCommandWithClientData(void *_data)
{
  int &data = *reinterpret_cast<int*>(_data);
  data = 97;
}

}

TEST( FunctionCommand, Test2 ) {
  // check execution of different callbacks types
  namespace sitk = itk::simple;

  MemberFunctionCommandTest mfct;
  EXPECT_EQ(0,mfct.v);

  sitk::FunctionCommand cmd1;
  cmd1.SetCallbackFunction( &mfct, &MemberFunctionCommandTest::DoSomething );
  cmd1.Execute();
  EXPECT_EQ(99,mfct.v);
  mfct.v = 0;

  EXPECT_EQ(0,gValue);
  cmd1.SetCallbackFunction(functionCommand);
  cmd1.Execute();
  EXPECT_EQ(98,gValue);
  EXPECT_EQ(0,mfct.v);


  cmd1.SetCallbackFunction(functionCommandWithClientData, &gValue);
  cmd1.Execute();
  EXPECT_EQ(97,gValue);
  EXPECT_EQ(0,mfct.v);
}

TEST( Interpolator, Test1 )
{
  // Test print of InterpolatorEnum with output operator
  namespace sitk = itk::simple;

  std::stringstream ss;
  ss << sitk::sitkNearestNeighbor;
  EXPECT_EQ("NearestNeighbor", ss.str());
  ss.str("");
  ss << sitk::sitkLinear;
  EXPECT_EQ("Linear", ss.str());
  ss.str("");
  ss << sitk::sitkBSpline;
  EXPECT_EQ("BSpline", ss.str());
  ss.str("");
  ss << sitk::sitkGaussian;
  EXPECT_EQ("Gaussian", ss.str());
  ss.str("");
  ss << sitk::sitkLabelGaussian;
  EXPECT_EQ("LabelGaussian", ss.str());
  ss.str("");
  ss << sitk::sitkHammingWindowedSinc;
  EXPECT_EQ("HammingWindowedSinc", ss.str());
  ss.str("");
  ss << sitk::sitkCosineWindowedSinc;
  EXPECT_EQ("CosineWindowedSinc", ss.str());
  ss.str("");
  ss << sitk::sitkWelchWindowedSinc;
  EXPECT_EQ("WelchWindowedSinc", ss.str());
  ss.str("");
  ss << sitk::sitkLanczosWindowedSinc;
  EXPECT_EQ("LanczosWindowedSinc", ss.str());
  ss.str("");
  ss << sitk::sitkBlackmanWindowedSinc;
  EXPECT_EQ("BlackmanWindowedSinc", ss.str());

}


TEST( Kernel, Test1 )
{
  // Test print of KernelEnum with output operator
  namespace sitk = itk::simple;

  std::stringstream ss;
  ss << sitk::sitkAnnulus;
  EXPECT_EQ("Annulus", ss.str());
  ss.str("");
  ss << sitk::sitkBall;
  EXPECT_EQ("Ball", ss.str());
  ss.str("");
  ss << sitk::sitkBox;
  EXPECT_EQ("Box", ss.str());
  ss.str("");
  ss << sitk::sitkCross;
  EXPECT_EQ("Cross", ss.str());
  ss.str("");
  ss << sitk::sitkPolygon3;
  EXPECT_EQ("Polygon3", ss.str());
  ss.str("");
  ss << sitk::sitkPolygon4;
  EXPECT_EQ("Polygon4", ss.str());
  ss.str("");
  ss << sitk::sitkPolygon4;
  EXPECT_EQ("Polygon4", ss.str());
  ss.str("");
  ss << sitk::sitkPolygon5;
  EXPECT_EQ("Polygon5", ss.str());
  ss.str("");
  ss << sitk::sitkPolygon6;
  EXPECT_EQ("Polygon6", ss.str());
  ss.str("");
  ss << sitk::sitkPolygon7;
  EXPECT_EQ("Polygon7", ss.str());
  ss.str("");
  ss << sitk::sitkPolygon8;
  EXPECT_EQ("Polygon8", ss.str());
  ss.str("");
  ss << sitk::sitkPolygon9;
  EXPECT_EQ("Polygon9", ss.str());

}

TEST(Logger, Logger)
{
  namespace sitk = itk::simple;

  auto logger = sitk::LoggerBase::GetGlobalITKLogger();


  testing::internal::CaptureStderr();

  logger.DisplayText("one\n");

  logger.DisplayErrorText("two\n");

  logger.DisplayWarningText("three\n");

  logger.DisplayGenericOutputText("four\n");

  logger.DisplayDebugText("five\n");

  const std::string expectedOutput = "one\n"
                                     "two\n"
                                     "three\n"
                                     "four\n"
                                     "five\n";

  EXPECT_EQ( testing::internal::GetCapturedStderr(), expectedOutput);
}

namespace {
// A mockup of a logger which saves messages to strings.
class MockLogger
:public itk::simple::LoggerBase {
public:

  MockLogger() = default;

  ~MockLogger() override = default;

  void DisplayText(const char * t) override {m_DisplayText << t;}

  void DisplayErrorText(const char * t) override {m_DisplayErrorText << t;}

  void DisplayWarningText(const char * t) override {m_DisplayWarningText << t;}

  void DisplayGenericOutputText(const char * t) override {m_DisplayGenericOutputText << t;}

  void DisplayDebugText(const char * t) override {m_DisplayDebugText << t;}

  std::stringstream m_DisplayText;
  std::stringstream m_DisplayErrorText;
  std::stringstream m_DisplayWarningText;
  std::stringstream m_DisplayGenericOutputText;
  std::stringstream m_DisplayDebugText;
};
}


TEST(Logger, MockLogger)
{

  namespace sitk = itk::simple;

  testing::internal::CaptureStderr();

  {
    MockLogger logger;

    logger.SetAsGlobalITKLogger();

    logger.DisplayText("test1\n");
    itk::OutputWindowDisplayText( "OutputWindowDisplayText1\n" );
    itk::OutputWindowDisplayErrorText( "OutputWindowDisplayErrorText1\n" );
    itk::OutputWindowDisplayWarningText( "OutputWindowDisplayWarningText1\n" );
    itk::OutputWindowDisplayGenericOutputText( "OutputWindowDisplayGenericOutputText1\n" );
    itk::OutputWindowDisplayDebugText("OutputWindowDebugText1\n" );


    EXPECT_EQ(logger.m_DisplayText.str(), "test1\nOutputWindowDisplayText1\n" );
    EXPECT_EQ(logger.m_DisplayErrorText.str(), "OutputWindowDisplayErrorText1\n" );
    EXPECT_EQ(logger.m_DisplayWarningText.str(), "OutputWindowDisplayWarningText1\n" );
    EXPECT_EQ(logger.m_DisplayGenericOutputText.str(), "OutputWindowDisplayGenericOutputText1\n" );
    EXPECT_EQ(logger.m_DisplayDebugText.str(), "OutputWindowDebugText1\n" );
  }
  itk::OutputWindowDisplayText( "OutputWindowDisplayText2\n" );
  itk::OutputWindowDisplayErrorText( "OutputWindowDisplayErrorText2\n" );
  itk::OutputWindowDisplayWarningText( "OutputWindowDisplayWarningText2\n" );
  itk::OutputWindowDisplayGenericOutputText( "OutputWindowDisplayGenericOutputText2\n" );
  itk::OutputWindowDisplayDebugText("OutputWindowDebugText2\n" );

  const std::string expectedLogOutput = "OutputWindowDisplayText2\n"
                                        "OutputWindowDisplayErrorText2\n"
                                        "OutputWindowDisplayWarningText2\n"
                                        "OutputWindowDisplayGenericOutputText2\n"
                                        "OutputWindowDebugText2\n";

  EXPECT_EQ( testing::internal::GetCapturedStderr(), expectedLogOutput);

}
