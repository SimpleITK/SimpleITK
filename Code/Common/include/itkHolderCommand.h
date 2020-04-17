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
#ifndef itkHolderCommand_h
#define itkHolderCommand_h

#include "itkCommand.h"

namespace itk {

/** \class HolderCommand
 *  \brief An ITK Command class to hold a object until destruction
 *
 * This command is to add resource management, by utilizing
 * the lifetime of a Command added to an object is about the same as
 * that managed object. So this command holds onto a resource or object for
 * lifetime of itself. By adding as a command to an ITK object it will
 * be released on destruction of the ITK object ( subject to the
 * reference counting on the Command ).
 */
template< class T >
class HolderCommand
  : public itk::Command
{
public:
  using ObjectType = T;

  using Self = HolderCommand;
  using Superclass = itk::Command;

  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;

  itkNewMacro( HolderCommand );

  void Set(const ObjectType object) { this->m_Object = object; }
  ObjectType &Get() {return this->m_Object;}
  const ObjectType &Get() const {return this->m_Object;}

  void Execute(itk::Object*, const itk::EventObject&) override {}
  void Execute(const itk::Object*, const itk::EventObject&) override {}

  void operator=(const HolderCommand&) = delete;
  HolderCommand(const HolderCommand&) = delete;

protected:
  HolderCommand() = default;
  ~HolderCommand() override = default;

private:
  ObjectType m_Object;

};

template< class T >
class HolderCommand<T*>
  : public itk::Command
{
public:
  using ObjectType = T;

  using Self = HolderCommand;
  using Superclass = itk::Command;

  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;

  itkNewMacro( HolderCommand );

  void Set(ObjectType *object) { this->m_Object = object; }
  ObjectType *Get() {return this->m_Object;}
  const ObjectType *Get() const {return this->m_Object;}

  void Execute(itk::Object*, const itk::EventObject&) override {}
  void Execute(const itk::Object*, const itk::EventObject&) override {}

  void operator=(const HolderCommand&) = delete;
  HolderCommand(const HolderCommand&) = delete;

protected:
  HolderCommand() : m_Object(nullptr) {};
  ~HolderCommand() override { delete m_Object;}

private:

  ObjectType* m_Object;

};

} // end namespace

#endif
