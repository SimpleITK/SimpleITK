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
#ifndef sitkTransform_h
#define sitkTransform_h

#include "sitkCommon.h"
#include "sitkExceptionObject.h"
#include "sitkImage.h"
#include <vector>


namespace itk
{

template< typename TScalar > class TransformBaseTemplate;
using TransformBase = TransformBaseTemplate<double>;

#if !defined(SWIG)
template< typename TScalar, unsigned int NDimension> class CompositeTransform;
#endif

namespace simple
{

class PimpleTransformBase;


enum TransformEnum { sitkUnknownTransform = -1,
                     sitkIdentity,
                     sitkTranslation,
                     sitkScale,
                     sitkScaleLogarithmic,
                     sitkEuler,
                     sitkSimilarity,
                     sitkQuaternionRigid,
                     sitkVersor,
                     sitkVersorRigid,
                     sitkScaleSkewVersor,
                     sitkComposeScaleSkewVersor,
                     sitkScaleVersor,
                     sitkAffine,
                     sitkComposite,
                     sitkDisplacementField,
                     sitkBSplineTransform
};


/** \class Transform
 * \brief A simplified wrapper around a variety of ITK transforms.
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
  using Self = Transform;

  /** \brief By default a 3-d identity transform is constructed
   */
  Transform( );

  /** \brief Construct a SimpleITK Transform from a pointer to an ITK
   * composite transform.
   *
   */
  template<unsigned int NDimension>
  explicit Transform( itk::CompositeTransform< double, NDimension >* compositeTransform )
    : m_PimpleTransform( nullptr )
    {
      static_assert( NDimension == 2 || NDimension == 3, "Only 2D and 3D transforms are supported" );
      if ( compositeTransform == nullptr )
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
  explicit Transform( Image &displacement, TransformEnum type = sitkDisplacementField );

  virtual ~Transform( );

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
   * The return value should immediately be assigned to as
   * itk::SmartPointer.
   *
   * In many cases the value may need to be dynamically cast to
   * the actual transform type.
   *
   * @{
   */
  itk::TransformBase* GetITKBase( );
  const itk::TransformBase* GetITKBase( ) const;
  /**@}*/

  /** Return the dimension of the Transform ( 2D or 3D )
   */
  unsigned int GetDimension( ) const;

  // todo get transform type

  /** Set/Get Transform Parameter
   * @{
   */
  void SetParameters ( const std::vector<double>& parameters );
  std::vector<double> GetParameters( ) const;
  /**@}*/

  /** Return the number of optimizable parameters */
  unsigned int GetNumberOfParameters( ) const;

  /** Set/Get Fixed Transform Parameter
   * @{
   */
  void SetFixedParameters ( const std::vector<double>& parameters );
  std::vector<double> GetFixedParameters( ) const;
  /**@}*/

  /** Get the number of fixed parameters */
  unsigned int GetNumberOfFixedParameters( ) const;

  /** Apply transform to a point.
   *
   * The dimension of the point must match the transform.
   */
  std::vector< double > TransformPoint( const std::vector< double > &point ) const;

  /** Apply transform to a vector at a point.
   *
   * The ITK concept of a vector is a direction at a specific point,
   * for example the difference between two points is a vector.
   *
   * For linear transforms the point does not matter, in general
   * the vector is transformed by the Jacobian with respect to point
   * position.
   *
   * The dimension of the vector and point must match the transform.
   */
  std::vector< double > TransformVector( const std::vector< double > &vector, const std::vector< double > &point) const;

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
   * transforms are not invertible, an exception will be throw is
   * there is no inverse.
   */
  Transform GetInverse() const;

  std::string ToString( ) const;


  /** return user readable name for the SimpleITK transform */
  virtual std::string GetName() const;

  /** \brief Performs actually coping if needed to make object unique.
   *
   * The Transform class by default performs lazy coping and
   * assignment. This method make sure that coping actually happens
   * to the itk::Transform pointed to is only pointed to by this
   * object.
   */
  void MakeUnique( );

  /** \brief Get the TransformEnum of the underlying Transform.
   *
   *  A SimpleITK Transform object can internally hold any ITK transform. This
   *  method returns the TransformEnum representing the internal ITK
   *  transform. This value may be used to identify which SimpleITK
   *  class the transform can be converted to.
   */
  TransformEnum GetTransformEnum() const;

protected:


  explicit Transform( PimpleTransformBase *pimpleTransform );

  // this method is called to set the private pimpleTransform outside
  // of the constructor, derived classes can override it of update the
  // state.
  virtual void SetPimpleTransform( PimpleTransformBase *pimpleTransform );

private:

  template< unsigned int VDimension>
  void InternalInitialization( TransformEnum type, itk::TransformBase *base = nullptr );

  struct TransformTryCastVisitor
  {
    itk::TransformBase *transform;
    Transform *that;
    template< typename TransformType >
    void operator() ( ) const
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
    using ObjectType = typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType;

    template< typename TImageType >
    TMemberFunctionPointer operator() ( ) const
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
