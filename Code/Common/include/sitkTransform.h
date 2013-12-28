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
#ifndef __sitkTransform_h
#define __sitkTransform_h

#include "sitkCommon.h"
#include "sitkExceptionObject.h"
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
                     sitkAffine,
                     sitkComposite };


/** \class Tranform
 * \brief A simplified wrapper around a variety of ITK transforms.
 *
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
    {
      sitkStaticAssert( NDimension == 2 || NDimension == 3, "Only 2D and 3D transforms are supported" );
      if ( compositeTransform == NULL )
        {
        sitkExceptionMacro( "Unable to construct a null transform!" );
        }
      this->InternalInitialization<NDimension>( sitkComposite, compositeTransform );
    }

  /** \brief Construct a specific transformation
   */
  Transform( unsigned int dimensions, TransformEnum type);

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
  Transform &AddTransform( Transform t );

  std::vector< double > TransformPoint( const std::vector< double > &point ) const;

  // write
  void WriteTransform( const std::string &filename ) const;

  // todo set identity

  std::string ToString( void ) const;


protected:

  void MakeUniqueForWrite( void );

private:

  template< unsigned int VDimension>
  void InternalInitialization(  TransformEnum type, itk::TransformBase *base = NULL );

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

#endif // __sitkTransform_h
