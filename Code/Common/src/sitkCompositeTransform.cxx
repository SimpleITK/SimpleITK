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
#include "sitkCompositeTransform.h"
#include "sitkTransformHelper.hxx"
#include "sitkPimpleTransform.hxx"

#include "itkCompositeTransform.h"

namespace itk
{
namespace simple
{

CompositeTransform::~CompositeTransform() = default;

CompositeTransform::CompositeTransform(unsigned int dimensions )
    : Transform(dimensions, sitkComposite)

{
  Self::InternalInitialization(Self::GetITKBase());
}


CompositeTransform::CompositeTransform( const CompositeTransform &arg )
    : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}


CompositeTransform::CompositeTransform( const Transform &arg )
    : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}

CompositeTransform::CompositeTransform( const std::vector<Transform> &transformList )
    : Transform(transformList.at(0).GetDimension(),sitkComposite)
{
  Self::InternalInitialization(Self::GetITKBase());

  for( auto &t : transformList)
  {
    Self::AddTransform(t);
  }
}

CompositeTransform &CompositeTransform::operator=( const CompositeTransform &arg )
{
  Superclass::operator=(arg);
  return *this;
}

void CompositeTransform::SetPimpleTransform( PimpleTransformBase *pimpleTransform )
{
  Superclass::SetPimpleTransform(pimpleTransform);
  Self::InternalInitialization(this->GetITKBase());
}

void CompositeTransform::InternalInitialization(itk::TransformBase *transform)
{

  MyVisitor visitor;
  visitor.transform = transform;
  visitor.that = this;

  // The list is traversed from the end to the beginning. The transform is first tested
  // to see if it is an itk::CompositeTransform, then if it is a regular transform
  // a CompositeTransform will be constructed and the transform added to it.
  typedef typelist::MakeTypeList<
      itk::CompositeTransform<double, 3>,
      itk::CompositeTransform<double, 2>,
      itk::Transform<double, 2, 2>,
      itk::Transform<double, 3, 3> >::Type TransformTypeList;

  typelist::Visit<TransformTypeList> callInternalInitialization;

  // explicitly remove all function pointer with reference to prior transform
  this->m_pfFlattenTransform = nullptr;
  this->m_pfAddTransform = nullptr;
  this->m_pfGetNumberOfTransforms = nullptr;
  this->m_pfClearTransformQueue = nullptr;

  callInternalInitialization(visitor);

  if ( this->m_pfFlattenTransform == nullptr)
  {

    sitkExceptionMacro("Transform is not of type " << this->GetName() << "!" );
  }

}


CompositeTransform &CompositeTransform::AddTransform( Transform t )
{
  this->MakeUnique();
  this->m_pfAddTransform(t);
  return *this;
}


CompositeTransform &CompositeTransform::FlattenTransform()
{
  this->MakeUnique();
  this->m_pfFlattenTransform();
  return *this;
}

unsigned int CompositeTransform::GetNumberOfTransforms() const
{
  return this->m_pfGetNumberOfTransforms();
}

void CompositeTransform::ClearTransforms()
{
  this->MakeUnique();
  return this->m_pfClearTransformQueue();
}

void CompositeTransform::RemoveTransform()
{
  if (this->GetNumberOfTransforms() > 0)
  {
    this->MakeUnique();
    return this->m_pfRemoveTransform();
  }
  else
  {
    sitkExceptionMacro("No transform to remote");
  }
}

Transform CompositeTransform::GetBackTransform()
{
  if (this->GetNumberOfTransforms() > 0)
  {
    Transform tx = this->m_pfBackTransform();
    tx.MakeUnique();
    return tx;
  }
  else
  {
    sitkExceptionMacro("No transforms");
  }
}



Transform CompositeTransform::GetNthTransform(unsigned int n)
{
  if (this->GetNumberOfTransforms() <= n) {
    sitkExceptionMacro("CompositeTransform index out of range");
  }
  else
    {
    Transform tx = this->m_pfGetNthTransform(n);
    tx.MakeUnique();
    return tx;
  }
}


template<unsigned int NDimension>
void CompositeTransform::InternalInitialization(itk::CompositeTransform< double, NDimension > *t)
{
  using TransformType = itk::CompositeTransform< double, NDimension >;
  m_pfFlattenTransform = [t]() { return t->FlattenTransformQueue(); };
  m_pfGetNumberOfTransforms = [t]() {return t->GetNumberOfTransforms();};
  m_pfClearTransformQueue = [t]() {return t->ClearTransformQueue();};
  m_pfRemoveTransform = [t]() {return t->RemoveTransform();};
  m_pfBackTransform = [t]() {return Transform(t->GetTransformQueue().back());};
  m_pfGetNthTransform = [t](unsigned int n) {return Transform(t->GetNthTransform(n));};
  m_pfAddTransform = [t](Transform add)
  {
    if ( add.GetDimension() != TransformType::InputSpaceDimension )
    {
      sitkExceptionMacro( "Transform  argument has dimension " << add.GetDimension()
                                                              << " does not match this dimension of " << TransformType::InputSpaceDimension );
    }

    // perform deep-copy to prevent aliasing.
    add.MakeUnique();
    auto baseAdd = dynamic_cast<itk::Transform<double, NDimension, NDimension> *>(add.GetITKBase());
    t->AddTransform( baseAdd );
    t->SetAllTransformsToOptimizeOff();
    t->SetOnlyMostRecentTransformToOptimizeOn();
  };

}

template <unsigned int NDimensions>
void CompositeTransform::InternalInitialization(itk::Transform<double, NDimensions, NDimensions> *tx)
{
  // Construct a new itk::CompositeTransform and hold the argument transform.
  using CompositeTransformType = itk::CompositeTransform<double, NDimensions>;

  auto ctx = CompositeTransformType::New();

  ctx->AddTransform(tx);

  // Call InternalInitialization again with a CompositeTransform the second time.
  Self::SetPimpleTransform(new PimpleTransform<CompositeTransformType >(ctx));
}


}
}
