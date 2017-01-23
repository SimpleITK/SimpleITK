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
#ifndef sitkTransform_h
#define sitkTransform_h

#include "sitkCommon.h"
#include "sitkExceptionObject.h"
#include "sitkImage.h"
#include <vector>


namespace itk
{

// Forward declaration for pointer
// After ITK_VERSION 4.5 (Acutally after June 20th, 2013) the ITK Transform
// classes are now templated.  This requires forward declarations to be defined
// differently.
#if ( ( SITK_ITK_VERSION_MAJOR == 4 ) && ( SITK_ITK_VERSION_MINOR < 5 ) )
class TransformBase;
#else
template< typename TScalar > class TransformBaseTemplate;
typedef TransformBaseTemplate<double> TransformBase;
#endif

template< typename TScalar, unsigned int NDimension> class CompositeTransform;

namespace simple
{

class PimpleTransformBase;


enum TransformEnum { sitkIdentity,
                     sitkTranslation,
                     sitkScale,
                     sitkScaleLogarithmic,
                     sitkEuler,
                     sitkSimilarity,
                     sitkQuaternionRigid,
                     sitkVersor,
                     sitkVersorRigid,
                     sitkScaleSkewVersor,
                     sitkAffine,
                     sitkComposite,
                     sitkDisplacementField,
                     sitkBSplineTransform
};


/** \brief A simplified wrapper around a variety of ITK transforms.
 *
 * The interface to ITK transform objects to be used with the
 * ImageRegistrationMethod, ResampleImageFilter and other SimpleITK
 * process objects. The transforms are designed to have a serialized
 * array of parameters to facilitate optimization for registration.
 *
 * Provides a base class interface to any type of ITK
 * transform. Objects of this type may have their interface converted
 * to a derived interface while keeping the same reference to the ITK
 * object.
 *
 * Additionally, this class provides a basic interface to a composite
 * transforms.
 *
 * \sa itk::CompositeTransform
 */
class SITKCommon_EXPORT Transform
{
public:
  typedef Transform Self;

  /** \brief By default a 3-d identity transform is constructed
   */
  Transform( void );

  /** \brief Construct a SimpleITK Transform from a pointer to an ITK
   * composite transform.
   *
   */
  template<unsigned int NDimension>
  explicit Transform( itk::CompositeTransform< double, NDimension >* compositeTransform )
    : m_PimpleTransform( NULL )
    {
      sitkStaticAssert( NDimension == 2 || NDimension == 3, "Only 2D and 3D transforms are supported" );
      if ( compositeTransform == NULL )
        {
        sitkExceptionMacro( "Unable to construct a null transform!" );
        }
      this->InternalInitialization<NDimension>( sitkComposite, compositeTransform );
    }

  explicit Transform( itk::TransformBase *transform );

  /** \brief Construct a specific transformation
   *
   * \deprecated This constructor will be removed in future releases.
   */
  Transform( unsigned int dimensions, TransformEnum type);

  /** \brief Use an image to construct a transform.
   *
   * The input displacement image is transferred to the constructed
   * transform object. The input image is modified to be a default
   * constructed Image object.
   *
   * Only the sitkDisplacementField transformation type can currently
   * be constructed this way. Image must be of sitkVectorFloat64 pixel
   * type with the number of components equal to the image dimension.
   *
   * \deprecated This constructor will be removed in future releases.
   */
  Transform( Image &displacement, TransformEnum type = sitkDisplacementField );

  virtual ~Transform( void );

  /** \brief Copy constructor and assignment operator
   *
   * Performs a shallow copy of the internal ITK transform. A deep
   * copy will be done if the transform in modified.
   * @{
   */
  Transform &operator=( const Transform & );
  Transform( const Transform & );
  /**@}*/


  /** Get access to internal ITK data object.
   *
   * The return value should imediately be assigned to as
   * itk::SmartPointer.
   *
   * In many cases the value may need to be dynamically casted to
   * the the actual transform type.
   *
   * @{
   */
  itk::TransformBase* GetITKBase( void );
  const itk::TransformBase* GetITKBase( void ) const;
  /**@}*/

  /** Return the dimension of the Transform ( 2D or 3D )
   */
  unsigned int GetDimension( void ) const;

  // todo get transform type

  /** Set/Get Transform Parameter
   * @{
   */
  void SetParameters ( const std::vector<double>& parameters );
  std::vector<double> GetParameters( void ) const ;
  /**@}*/

  /** Set/Get Fixed Transform Parameter
   * @{
   */
  void SetFixedParameters ( const std::vector<double>& parameters );
  std::vector<double> GetFixedParameters( void ) const ;
  /**@}*/

  // Make composition
  SITK_RETURN_SELF_TYPE_HEADER AddTransform( Transform t );

  std::vector< double > TransformPoint( const std::vector< double > &point ) const;

  // write
  void WriteTransform( const std::string &filename ) const;

  virtual bool IsLinear() const;

  virtual void SetIdentity();

  /** \brief Try to change the current transform to it's inverse.
   *
   * If the transform has an inverse, i.e. non-singular linear
   * transforms, then a new ITK transform is created of the same type
   * and this object is set to it.
   *
   * However not all transform have a direct inverse, if the inverse
   * does not exist or fails false will be returned and this transform
   * will not be modified.
   */
  virtual bool SetInverse();

  /** \brief Return a new inverse transform of the same type as this.
   *
   * Creates a new transform object and tries to set the value to the
   * inverse. As not all transform types have inverse and some
   * transforms are not invertable, an exception will be throw is
   * there is no inverse.
   */
  Transform GetInverse() const;

  std::string ToString( void ) const;


  /** return user readable name for the SimpleITK transform */
  virtual std::string GetName() const;

  /** \brief Performs actually coping if needed to make object unique.
   *
   * The Transform class by default performs lazy coping and
   * assignment. This method make sure that coping actually happens
   * to the itk::Transform pointed to is only pointed to by this
   * object.
   */
  void MakeUnique( void );

protected:


  explicit Transform( PimpleTransformBase *pimpleTransform );

  // this method is called to set the private pimpleTransfrom outside
  // of the constructor, derived classes can override it of update the
  // state.
  virtual void SetPimpleTransform( PimpleTransformBase *pimpleTransform );

private:

  template< unsigned int VDimension>
  void InternalInitialization( TransformEnum type, itk::TransformBase *base = NULL );

  struct TransformTryCastVisitor
  {
    itk::TransformBase *transform;
    Transform *that;
    template< typename TransformType >
    void operator() ( void ) const
      {
        TransformType *t = dynamic_cast<TransformType*>(transform);
        if (t)
          {
          that->InternalInitialization<TransformType>(t);
          }
      }
  };


  template< class TransformType>
  void InternalInitialization( TransformType *t );
  void InternalInitialization( itk::TransformBase *base );


  template< unsigned int >
    void InternalBSplineInitialization( Image & img );

  template< typename TDisplacementType >
    void InternalDisplacementInitialization( Image & img );

  template < class TMemberFunctionPointer >
    struct DisplacementInitializationMemberFunctionAddressor
  {
    typedef typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType ObjectType;

    template< typename TImageType >
    TMemberFunctionPointer operator() ( void ) const
      {
        return &ObjectType::template InternalDisplacementInitialization< TImageType >;
      }
  };

  // As is the architecture of all SimpleITK pimples,
  // this pointer should never be null and should always point to a
  // valid object
  PimpleTransformBase *m_PimpleTransform;
};


// read
SITKCommon_EXPORT Transform ReadTransform( const std::string &filename );

// write
SITKCommon_EXPORT void WriteTransform( const Transform &transform, const std::string &filename);

}
}

#endif // sitkTransform_h
