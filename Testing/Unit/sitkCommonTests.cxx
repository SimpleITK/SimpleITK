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
#include <SimpleITKTestHarness.h>

#include <sitkConditional.h>
#include <sitkCommand.h>
#include <sitkFunctionCommand.h>
#include <sitkCastImageFilter.h>

#include <sitkKernel.h>

namespace nsstd = itk::simple::nsstd;

TEST( ConditionalTest, ConditionalTest1 ) {

  // a quick check to make sure the conditional works
  typedef itk::simple::Conditional<true, int, float>::Type IntType;
  typedef itk::simple::Conditional<false, int, float>::Type FloatType;


  EXPECT_EQ ( typeid( IntType ).name(), typeid( int ).name() );
  EXPECT_EQ ( typeid( FloatType ).name(), typeid( float ).name() );

  return;

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
  nsstd::auto_ptr<sitk::CastImageFilter> po1(new sitk::CastImageFilter());
  nsstd::auto_ptr<sitk::Command> cmd(new sitk::Command());
  po1->AddCommand(sitk::sitkAnyEvent, *cmd);

  EXPECT_TRUE(po1->HasCommand(sitk::sitkAnyEvent));
  cmd.reset();
  EXPECT_FALSE(po1->HasCommand(sitk::sitkAnyEvent));
  }

  // Case 1b: single command, process deleted first
  {
  nsstd::auto_ptr<sitk::CastImageFilter> po1( new sitk::CastImageFilter());
  nsstd::auto_ptr<sitk::Command> cmd(new sitk::Command());
  po1->AddCommand(sitk::sitkAnyEvent, *cmd);
  po1.reset();
  }

  // Case 2a: single command, multiple processes, command deleted first
  {
  nsstd::auto_ptr<sitk::CastImageFilter> po1(new sitk::CastImageFilter());
  nsstd::auto_ptr<sitk::CastImageFilter> po2(new sitk::CastImageFilter());
  nsstd::auto_ptr<sitk::CastImageFilter> po3(new sitk::CastImageFilter());

  nsstd::auto_ptr<sitk::Command> cmd(new sitk::Command());
  po1->AddCommand(sitk::sitkAnyEvent, *cmd);
  po2->AddCommand(sitk::sitkStartEvent, *cmd);
  po3->AddCommand(sitk::sitkEndEvent, *cmd);
  cmd.reset();
  }

  // Case 2b: single command, multiple processes, processes mostly deleted first
  {
  nsstd::auto_ptr<sitk::CastImageFilter> po1(new sitk::CastImageFilter());
  nsstd::auto_ptr<sitk::CastImageFilter> po2(new sitk::CastImageFilter());
  nsstd::auto_ptr<sitk::CastImageFilter> po3(new sitk::CastImageFilter());

  nsstd::auto_ptr<sitk::Command> cmd(new sitk::Command());
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
  nsstd::auto_ptr<sitk::CastImageFilter> po1(new sitk::CastImageFilter());
  nsstd::auto_ptr<sitk::Command> cmd1(new sitk::Command());
  nsstd::auto_ptr<sitk::Command> cmd2(new sitk::Command());
  nsstd::auto_ptr<sitk::Command> cmd3(new sitk::Command());

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
  nsstd::auto_ptr<sitk::CastImageFilter> po1(new sitk::CastImageFilter());
  nsstd::auto_ptr<sitk::Command> cmd1(new sitk::Command());
  nsstd::auto_ptr<sitk::Command> cmd2(new sitk::Command());
  nsstd::auto_ptr<sitk::Command> cmd3(new sitk::Command());
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

    virtual void Execute( )
      {
        if ( m_Process.GetProgress() >= m_AbortAt )
          delete m_Cmd;
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

    virtual void Execute( )
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
    ~HeapCommand() {++destroyedCount;}
    virtual void Execute() {v=true;}
    using Command::SetOwnedByProcessObjects;
    using Command::GetOwnedByProcessObjects;
    using Command::OwnedByProcessObjectsOn;
    using Command::OwnedByProcessObjectsOff;

    bool v;
  };

  {
  // test set/get/on/off
  HeapCommand cmd;
  EXPECT_FALSE(cmd.GetOwnedByProcessObjects());
  cmd.SetOwnedByProcessObjects(true);
  EXPECT_TRUE(cmd.GetOwnedByProcessObjects());
  cmd.OwnedByProcessObjectsOff();
  EXPECT_FALSE(cmd.GetOwnedByProcessObjects());
  cmd.OwnedByProcessObjectsOn();
  EXPECT_TRUE(cmd.GetOwnedByProcessObjects());

  HeapCommand *cmd1 = new HeapCommand();
  cmd1->OwnedByProcessObjectsOn();
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
  cmd2->OwnedByProcessObjectsOn();
  po.AddCommand(sitk::sitkAnyEvent, *cmd2);

  EXPECT_FALSE(cmd2->v);
  EXPECT_NO_THROW( po.Execute(img) );
  EXPECT_TRUE(cmd2->v);
  cmd2->v = false;

  HeapCommand *cmd3 = new HeapCommand();
  cmd3->OwnedByProcessObjectsOn();
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
  nsstd::auto_ptr<sitk::CastImageFilter> po1(new sitk::CastImageFilter());
  nsstd::auto_ptr<sitk::CastImageFilter> po2(new sitk::CastImageFilter());

  HeapCommand *cmd = new HeapCommand();
  cmd->OwnedByProcessObjectsOn();

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
void functionCommand(void)
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
