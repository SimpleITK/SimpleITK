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


#include "sitkPimpleTransform.hxx"

#include "sitkTransform.h"
#include "sitkTemplateFunctions.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkImageConvert.h"

#include "itkTransformBase.h"
#include "itkTransformFactory.h"

#include "itkIdentityTransform.h"
#include "itkTranslationTransform.h"
#include "itkScaleTransform.h"
#include "itkScaleLogarithmicTransform.h"
#include "itkSimilarity2DTransform.h"
#include "itkSimilarity3DTransform.h"
#include "itkEuler2DTransform.h"
#include "itkEuler3DTransform.h"
#include "itkQuaternionRigidTransform.h"
#include "itkVersorTransform.h"
#include "itkVersorRigid3DTransform.h"
#include "itkScaleSkewVersor3DTransform.h"
#include "itkScaleVersor3DTransform.h"
#include "itkAffineTransform.h"
#include "itkCompositeTransform.h"

#include "itkDisplacementFieldTransform.h"
#include "itkBSplineTransform.h"

#include "itkTransformFileReader.h"
#include "itkTransformFileWriter.h"

#include "itkVectorImage.h"
#include "itkCommand.h"

#include <memory>

#include "nsstd/type_traits.h"

namespace itk
{
namespace simple
{

namespace
{

//
// Transform trait class to map to correct special transform type.
template<class T, unsigned int ImageDimension>
class TransformTraits
{
public:
  // undefined types for non-2D/3D
};

template<class T>
class TransformTraits<T,2>
{
public:
  typedef itk::Euler2DTransform<T>       EulerTransformType;
  typedef itk::Similarity2DTransform<T>  SimilarityTransformType;
};

template<class T>
class TransformTraits<T,3>
{
public:
  typedef itk::Euler3DTransform<T>       EulerTransformType;
  typedef itk::Similarity3DTransform<T>  SimilarityTransformType;
};

template<unsigned int Dimension>
bool RegisterMoreTransforms(void)
{
  typedef itk::MatrixOffsetTransformBase<double, Dimension, Dimension> MatrixOffsetTransformType;
  itk::TransformFactory<MatrixOffsetTransformType>::RegisterTransform();

  // Only BSpline transforms of order 3 are registered in ITK
  typedef itk::BSplineTransform<double, Dimension, 0> BSplineTransformO0Type;
  itk::TransformFactory<BSplineTransformO0Type>::RegisterTransform();
  typedef itk::BSplineTransform<double, Dimension, 1> BSplineTransformO1Type;
  itk::TransformFactory<BSplineTransformO1Type>::RegisterTransform();
  typedef itk::BSplineTransform<double, Dimension, 2> BSplineTransformO2Type;
  itk::TransformFactory<BSplineTransformO2Type>::RegisterTransform();

  return true;
}

bool initialized = RegisterMoreTransforms<2>() && RegisterMoreTransforms<3>();


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
  typedef T ObjectType;

  typedef  HolderCommand Self;
  typedef  itk::Command  Superclass;

  typedef itk::SmartPointer<Self>        Pointer;
  typedef itk::SmartPointer<const Self>  ConstPointer;

  itkNewMacro( HolderCommand );

  void Set(const ObjectType object) { this->m_Object = object; }
  ObjectType &Get() {return this->m_Object;}
  const ObjectType &Get() const {return this->m_Object;}

  void Execute(itk::Object*, const itk::EventObject&) {}
  void Execute(const itk::Object*, const itk::EventObject&) {}

protected:
  HolderCommand() {};
  ~HolderCommand() {};

private:
  void operator=(const HolderCommand&); // not implemented
  HolderCommand(const HolderCommand&); // not implemented

  ObjectType m_Object;

};

template< class T >
class HolderCommand<T*>
  : public itk::Command
{
public:
  typedef T ObjectType;

  typedef  HolderCommand Self;
  typedef  itk::Command  Superclass;

  typedef itk::SmartPointer<Self>        Pointer;
  typedef itk::SmartPointer<const Self>  ConstPointer;

  itkNewMacro( HolderCommand );

  void Set(ObjectType *object) { this->m_Object = object; }
  ObjectType *Get() {return this->m_Object;}
  const ObjectType *Get() const {return this->m_Object;}

  void Execute(itk::Object*, const itk::EventObject&) SITK_OVERRIDE {}
  void Execute(const itk::Object*, const itk::EventObject&) SITK_OVERRIDE {}

protected:
  HolderCommand() : m_Object(NULL) {};
  ~HolderCommand() { delete m_Object;}

private:
  void operator=(const HolderCommand&); // not implemented
  HolderCommand(const HolderCommand&); // not implemented

  ObjectType* m_Object;

};

}


//
// class Transform
//

Transform::Transform( )
  : m_PimpleTransform( NULL )
  {
    m_PimpleTransform = new PimpleTransform<itk::IdentityTransform< double, 3 > >();
  }

Transform::Transform( itk::TransformBase *transformBase )
  : m_PimpleTransform( NULL )
{
  this->InternalInitialization( transformBase );
}

  Transform::Transform( unsigned int dimensions, TransformEnum type)
    : m_PimpleTransform( NULL )
  {
    if ( dimensions == 2 )
      {
      this->InternalInitialization<2>(type);
      }
    else if ( dimensions == 3 )
      {
      this->InternalInitialization<3>(type);
      }
    else
      {
      sitkExceptionMacro("Invalid dimension for transform");
      }
  }


  Transform::~Transform()
  {
    delete m_PimpleTransform;
    this->m_PimpleTransform = NULL;
  }

  Transform::Transform( const Transform &txf )
    : m_PimpleTransform( NULL )
  {
    Self::SetPimpleTransform( txf.m_PimpleTransform->ShallowCopy() );
  }

  Transform& Transform::operator=( const Transform & txf )
  {
    assert( m_PimpleTransform );
    PimpleTransformBase *temp = txf.m_PimpleTransform->ShallowCopy();
    this->SetPimpleTransform( temp );
    return *this;
  }


Transform::Transform( Image &image, TransformEnum txType )
    : m_PimpleTransform( NULL )
  {


    if (txType == sitkDisplacementField)
      {
      const PixelIDValueEnum type = image.GetPixelID();
      const unsigned int dimension = image.GetDimension();

      // The pixel IDs supported
      typedef typelist::MakeTypeList<VectorPixelID<double> >::Type PixelIDTypeList;

      typedef void (Self::*MemberFunctionType)( Image & );

      typedef DisplacementInitializationMemberFunctionAddressor<MemberFunctionType> Addressor;

      detail::MemberFunctionFactory<MemberFunctionType> initializationMemberFactory(this);
      initializationMemberFactory.RegisterMemberFunctions< PixelIDTypeList, 3,  Addressor > ();
      initializationMemberFactory.RegisterMemberFunctions< PixelIDTypeList, 2,  Addressor > ();


      initializationMemberFactory.GetMemberFunction( type, dimension )( image );
      }
    else if ( txType == sitkBSplineTransform )
      {
      const unsigned int dimension = image.GetDimension();

      switch (dimension)
        {
        case 2:
          this->InternalBSplineInitialization<2>(image);
          break;
        case 3:
          this->InternalBSplineInitialization<3>(image);
          break;
        default:
          sitkExceptionMacro("LogicError: Unexplected case!");
        }
      }
    else
      {
      sitkExceptionMacro("Expected sitkDisplacementField or sitkBSplineTransform for the Transformation type!")
      }


  }

template< unsigned int ImageDimension>
void Transform::InternalBSplineInitialization( Image & inImage )
{
  typedef itk::ImageBase<ImageDimension> ImageType;
  typename ImageType::Pointer image = dynamic_cast<ImageType *>( inImage.GetITKBase() );

  if ( !image )
    {
    sitkExceptionMacro( "Unexpected template dispatch error!" );
    }

  typedef itk::BSplineTransform<double,ImageDimension,3> BSplineTransformType;
  typename BSplineTransformType::Pointer itkBSpline = BSplineTransformType::New();

  itkBSpline->SetTransformDomainOrigin( image->GetOrigin() );
  itkBSpline->SetTransformDomainDirection( image->GetDirection() );

  const typename BSplineTransformType::MeshSizeType  meshSize( image->GetLargestPossibleRegion().GetSize() );

  typename BSplineTransformType::PhysicalDimensionsType fixedPhysicalDimensions;

  for( unsigned int i=0; i< ImageDimension; i++ )
    {
    fixedPhysicalDimensions[i] = image->GetSpacing()[i] * static_cast<double>( meshSize[i] - 1 );
    }

  itkBSpline->SetTransformDomainMeshSize( meshSize );
  itkBSpline->SetTransformDomainPhysicalDimensions( fixedPhysicalDimensions );


  typedef typename BSplineTransformType::ParametersType ParametersType;

  typename HolderCommand<ParametersType *>::Pointer holder = HolderCommand<ParametersType *>::New();
  itkBSpline->AddObserver( itk::DeleteEvent(), holder);
  holder->Set( new ParametersType( itkBSpline->GetNumberOfParameters() ) );

  itkBSpline->SetParameters( *holder->Get() );
  itkBSpline->SetIdentity();


  Self::SetPimpleTransform( new PimpleTransform< BSplineTransformType >( itkBSpline.GetPointer() ) );
}

  template< typename TDisplacementType >
  void Transform::InternalDisplacementInitialization( Image & inImage )
  {
    typedef TDisplacementType VectorImageType;

    typedef typename VectorImageType::InternalPixelType ComponentType;
    const unsigned int ImageDimension = VectorImageType::ImageDimension;

    typedef itk::Image< itk::Vector<ComponentType, ImageDimension>, ImageDimension > ITKDisplacementType;
    typedef itk::DisplacementFieldTransform< ComponentType, ImageDimension > DisplacementTransformType;

    typename VectorImageType::Pointer image = dynamic_cast < VectorImageType* > ( inImage.GetITKBase() );

    if ( image.IsNull() )
      {
      sitkExceptionMacro( "Unexpected template dispatch error!" );
      }

    typename ITKDisplacementType::Pointer itkDisplacement = GetImageFromVectorImage(image.GetPointer(), true );
    inImage = Image();

    Self::SetPimpleTransform( new PimpleTransform< DisplacementTransformType >(itkDisplacement.GetPointer()) );
  }

void Transform::MakeUnique( void )
{
  if ( this->m_PimpleTransform->GetReferenceCount() > 1 )
    {
    PimpleTransformBase *temp = this->m_PimpleTransform->DeepCopy();
    this->SetPimpleTransform( temp );
    }
}

Transform::Transform( PimpleTransformBase *pimpleTransform )
    : m_PimpleTransform( pimpleTransform )
  {
    if ( pimpleTransform == NULL )
      {
      sitkExceptionMacro("Invalid NULL PimpleTransform!");
      }
  }


void Transform::SetPimpleTransform( PimpleTransformBase *pimpleTransform )
{
  delete this->m_PimpleTransform;
  this->m_PimpleTransform = pimpleTransform;
}


  template< unsigned int VDimension>
  void Transform::InternalInitialization(  TransformEnum type, itk::TransformBase *base )
  {
    PimpleTransformBase* temp;
    switch( type )
      {

      case sitkTranslation:
        temp = new PimpleTransform<itk::TranslationTransform< double, VDimension > >();
        break;
      case sitkScale:
        temp = new PimpleTransform<itk::ScaleTransform< double, VDimension > >();
        break;
      case sitkScaleLogarithmic:
        temp = new PimpleTransform<itk::ScaleLogarithmicTransform< double, VDimension > >();
        break;
      case sitkEuler:
        temp = new PimpleTransform<typename TransformTraits<double,VDimension>::EulerTransformType>();
        break;
      case sitkSimilarity:
        temp = new PimpleTransform<typename TransformTraits<double,VDimension>::SimilarityTransformType>();
        break;
      case sitkQuaternionRigid:
        if( VDimension != 3)
          {
          sitkExceptionMacro( "A sitkQuaternionRigid Transform only works for 3D!");
          }

        temp = new PimpleTransform<itk::QuaternionRigidTransform< double > >();
        break;
      case sitkVersor:
        if( VDimension != 3)
          {
          sitkExceptionMacro( "A sitkVersor Transform only works for 3D!");
          }

        temp = new PimpleTransform<itk::VersorTransform< double > >();
        break;
      case sitkVersorRigid:
        if( VDimension != 3)
          {
          sitkExceptionMacro( "A sitkVersorRigid Transform only works for 3D!");
          }

        temp = new PimpleTransform<itk::VersorRigid3DTransform< double > >();
        break;
      case sitkScaleSkewVersor:
        if( VDimension != 3)
          {
          sitkExceptionMacro( "A sitkScaleSkewVersor Transform only works for 3D!");
          }

        temp = new PimpleTransform<itk::ScaleSkewVersor3DTransform< double > >();
        break;
      case sitkAffine:
        temp = new PimpleTransform<itk::AffineTransform< double, VDimension > >();
        break;
      case sitkComposite:
        {
        typename itk::CompositeTransform<double, VDimension>::Pointer compositeTransform;

        // if null it'll be converted, no null check needed
        compositeTransform = dynamic_cast<itk::CompositeTransform<double, VDimension>*>( base );

        if ( !compositeTransform )
          {
          compositeTransform = itk::CompositeTransform<double, VDimension>::New();

          // base argument was non-composite place into composite
          if ( base )
            {
            typedef itk::Transform<double,  VDimension,  VDimension> TransformType;
            TransformType* itktx = dynamic_cast<TransformType*>(base);

            compositeTransform->ClearTransformQueue();
            compositeTransform->AddTransform( itktx );
            }
          }


        if ( compositeTransform->IsTransformQueueEmpty() )
          {

          // Load an identity transform in case no transforms are loaded.
          typedef itk::IdentityTransform<double, VDimension> IdentityTransformType;
          typename IdentityTransformType::Pointer identityTransform = IdentityTransformType::New();

          compositeTransform->AddTransform( identityTransform );
          }

        compositeTransform->SetAllTransformsToOptimizeOff();
        compositeTransform->SetOnlyMostRecentTransformToOptimizeOn();

        temp = new PimpleTransform<itk::CompositeTransform<double, VDimension> >( compositeTransform );

        }
        break;
      case sitkDisplacementField:
      case sitkBSplineTransform:
        // todo print transform type..
        sitkExceptionMacro("Incorrect constructor for transform type.");
      case sitkIdentity:
      default:
        temp = new PimpleTransform<itk::IdentityTransform< double, VDimension > >();

      }
    Self::SetPimpleTransform(temp);
  }

  template void SITKCommon_EXPORT Transform::InternalInitialization<2>( TransformEnum, itk::TransformBase * );
  template void SITKCommon_EXPORT Transform::InternalInitialization<3>( TransformEnum, itk::TransformBase * );

  itk::TransformBase* Transform::GetITKBase ( void )
  {
    assert( m_PimpleTransform );
    return this->m_PimpleTransform->GetTransformBase();
  }

  const itk::TransformBase* Transform::GetITKBase ( void ) const
  {
    assert( m_PimpleTransform );
    return this->m_PimpleTransform->GetTransformBase();
  }

  unsigned int  Transform::GetDimension( void ) const
  {
    assert( m_PimpleTransform );
    return this->m_PimpleTransform->GetInputDimension();
  }

  void Transform::SetParameters ( const std::vector<double>& parameters )
  {
    assert( m_PimpleTransform );
    this->MakeUnique();
    this->m_PimpleTransform->SetParameters( parameters );
  }

  std::vector<double> Transform::GetParameters( void ) const
  {
    assert( m_PimpleTransform );
    return this->m_PimpleTransform->GetParameters();
  }

  void Transform::SetFixedParameters ( const std::vector<double>& parameters )
  {
    assert( m_PimpleTransform );
    this->MakeUnique();
    this->m_PimpleTransform->SetFixedParameters( parameters );
  }

  std::vector<double> Transform::GetFixedParameters( void ) const
  {
    assert( m_PimpleTransform );
    return this->m_PimpleTransform->GetFixedParameters();
  }

  Transform &Transform::AddTransform( Transform t )
  {
    assert( m_PimpleTransform );
    this->MakeUnique();
    // this returns a pointer which may be the same or a new object
    PimpleTransformBase *temp = this->m_PimpleTransform->AddTransform( t );
    if ( temp != this->m_PimpleTransform )
      {
      this->SetPimpleTransform(temp);
      }
    return *this;
  }

  std::vector< double > Transform::TransformPoint( const std::vector< double > &point ) const
  {
    assert( m_PimpleTransform );
    return this->m_PimpleTransform->TransformPoint( point );
  }


  bool Transform::IsLinear() const
  {
    assert( m_PimpleTransform );
    return this->m_PimpleTransform->IsLinear();
  }

  void Transform::SetIdentity()
  {
    assert( m_PimpleTransform );
    this->MakeUnique();
    return this->m_PimpleTransform->SetIdentity();
  }

  bool Transform::SetInverse()
  {
    assert( m_PimpleTransform );
    nsstd::auto_ptr<PimpleTransformBase> temp;
    {
    // See if a new pimple transform can be created
    PimpleTransformBase *p = NULL;
    if (!this->m_PimpleTransform->GetInverse(p))
      {
      return false;
      }
    temp.reset(p);
    }
    // take ownership of the new pimple transform
    this->SetPimpleTransform( temp.release() );
    return true;
  }

  Transform Transform::GetInverse() const
  {
    // create a shallow copy
    Transform tx(*this);
    if (!tx.SetInverse())
      {
      sitkExceptionMacro("Unable to create inverse!");
      }
    return tx;
  }

  std::string Transform::ToString( void ) const
  {
    assert( m_PimpleTransform );

    // mark as used
    static_cast<void>( itk::simple::initialized );

    return std::string("itk::simple::")+this->GetName() + '\n'+this->m_PimpleTransform->ToString();
  }

  std::string Transform::GetName( void ) const
  {
    return "Transform";
  }


void Transform::InternalInitialization(itk::TransformBase *transform)
{

  TransformTryCastVisitor visitor;
  visitor.transform = transform;
  visitor.that = this;

  // The following list must have the children before their parents to
  // cast to the most derived classes
  typedef typelist::MakeTypeList<itk::IdentityTransform<double, 2>,
                                 itk::IdentityTransform<double, 3>,
                                 itk::TranslationTransform<double, 2>,
                                 itk::TranslationTransform<double, 3>,

                                 itk::ScaleLogarithmicTransform< double, 2 >,
                                 itk::ScaleLogarithmicTransform< double, 3 >,
                                 itk::ScaleTransform< double, 2>,
                                 itk::ScaleTransform< double, 3>,

                                 TransformTraits< double, 2>::EulerTransformType,

                                 TransformTraits< double, 3>::EulerTransformType,

                                 TransformTraits< double, 2>::SimilarityTransformType,

                                 TransformTraits< double, 3>::SimilarityTransformType,
                                 itk::ScaleSkewVersor3DTransform< double >,
                                 itk::ScaleVersor3DTransform< double >,
                                 itk::VersorRigid3DTransform< double >,
                                 itk::VersorTransform< double >,

                                 itk::QuaternionRigidTransform< double >,

                                 itk::AffineTransform<double,3>,
                                 itk::AffineTransform<double,2>,

                                 itk::DisplacementFieldTransform<double, 3>,
                                 itk::DisplacementFieldTransform<double, 2>,

                                 itk::BSplineTransform<double, 3, 0>,
                                 itk::BSplineTransform<double, 2, 0>,
                                 itk::BSplineTransform<double, 3, 1>,
                                 itk::BSplineTransform<double, 2, 1>,
                                 itk::BSplineTransform<double, 3, 2>,
                                 itk::BSplineTransform<double, 2, 2>,
                                 itk::BSplineTransform<double, 3, 3>,
                                 itk::BSplineTransform<double, 2, 3>
                                 >::Type TransformTypeList;

  typelist::Visit<TransformTypeList> callInternalInitialization;

  callInternalInitialization(visitor);

  // The transform didn't match a known type, place it into a Composite.
  if ( !m_PimpleTransform )
    {
    if ( transform->GetInputSpaceDimension() == 2 &&
         transform->GetInputSpaceDimension() == 2 )
      {
      this->InternalInitialization<2>( sitkComposite, transform );
      }
    else if ( transform->GetInputSpaceDimension() == 3 &&
              transform->GetInputSpaceDimension() == 3 )
      {
      this->InternalInitialization<3>( sitkComposite, transform );
      }
    else
      {
      sitkExceptionMacro( "Unable to create transform with InputSpaceDimension: " <<  transform->GetInputSpaceDimension()
                        << " and OutputSpaceDimension: " << transform->GetOutputSpaceDimension() << ". "
                        << "Transform of type " << transform->GetNameOfClass() << "is not supported." );
      }
    }
}


template<class TransformType>
void Transform::InternalInitialization(TransformType *t)
{
  PimpleTransformBase* temp = new PimpleTransform<TransformType>(t);
  Self::SetPimpleTransform(temp);
}

  Transform ReadTransform( const std::string &filename )
  {
    TransformFileReader::Pointer reader = TransformFileReader::New();
    reader->SetFileName(filename.c_str() );
    reader->Update();

    itk::TransformFileReader::TransformListType *list = reader->GetTransformList();

    if ( list->empty() )
      {
      sitkExceptionMacro( "Read transform file: \"" << filename << "\", but there appears to be not transform in the file!" );
      }

    if( list->size() != 1 )
      {
      std::cerr << "Warning: There is more than one transform in the file! Only using the first transform.\n";
      }

    if( list->front()->GetInputSpaceDimension() == 3
        && list->front()->GetOutputSpaceDimension() == 3 )
      {
      typedef itk::Transform<double, 3, 3> TransformType3D;
      TransformType3D* itktx3d = dynamic_cast<TransformType3D*>(list->front().GetPointer());
      if (!itktx3d)
        {
        sitkExceptionMacro( "Unexpected type conversion error for 3D Transform!");
        }
      return Transform(itktx3d);

      }


    if( list->front()->GetInputSpaceDimension() == 2
        && list->front()->GetOutputSpaceDimension() == 2)
      {

      typedef itk::Transform<double, 2, 2> TransformType2D;
      TransformType2D* itktx2d = dynamic_cast<TransformType2D*>(list->front().GetPointer());
      if (!itktx2d)
        {
        sitkExceptionMacro( "Unexpected type conversion error for 2D Transform!");
        }
      return Transform(itktx2d);


      }


    sitkExceptionMacro( "Unable to transform with InputSpaceDimension: " <<  list->front()->GetInputSpaceDimension()
                        << " and OutputSpaceDimension: " << list->front()->GetOutputSpaceDimension() << ". "
                        << "Transform of type " << list->front()->GetNameOfClass() << "is not supported." );

  }

  void Transform::WriteTransform( const std::string &filename ) const
  {
    itk::simple::WriteTransform( *this, filename );
  }

  // write
  void WriteTransform( const Transform &transform, const std::string &filename)
  {
    itk::TransformFileWriter::Pointer writer = itk::TransformFileWriter::New();
    writer->SetFileName(filename.c_str());
    writer->SetInput( transform.GetITKBase() );
    writer->Update();

  }

}
}
