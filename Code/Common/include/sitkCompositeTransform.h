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


#ifndef sitkCompositeTransform_h
#define sitkCompositeTransform_h

#include "sitkCommon.h"
#include "sitkTransform.h"

namespace itk
{


template <typename TParametersValueType, unsigned int NInputDimensions, unsigned int NOutputDimensions>
class Transform;

namespace simple
{

/** \class CompositeTransform
 * \brief This class contains a stack of transforms and concatenates them by composition.
 *
 * The transforms are composed in \b reverse order with the back being applied
 * first:
 *    \f$ T_0 o T_1 = T_0(T_1(x)) \f$
 * Transforms are stored in a queue, in the following order:
 *    \f$ T_0, T_1, ... , T_N-1 \f$
 *
 * Transforms are added via AddTransform(). This adds the transforms to the back
 * of the queue.
 *
 * The only parameters of the transform at the back of the queue are exposed and
 * optimizable for registration.
 *
 * Inverse:
 * The inverse transform is created by retrieving the inverse from each
 * sub transform and adding them to a composite transform in reverse order.
 * The m_TransformsToOptimizeFlags is copied in reverse for the inverse.
 *
 * \sa itk::CompositeTransform
 */
class SITKCommon_EXPORT CompositeTransform
    : public Transform {
public:
  using Self = CompositeTransform;
  using Superclass = Transform;

  /** \brief Construct an empty CompositeTransform
   *
   *  The created CompositeTransform is initialized with zero transforms.
   *  Additional transforms of dimensions can be added.
   */
  explicit CompositeTransform(unsigned int dimensions);

  /** \brief Create CompositeTransform converted or holding the transform argument.
   *
   * If the Transform is internally a CompositeTransform, a shallow copy to
   * the internal transform will be made. Otherwise a new CompositeTransform is
   * constructed which holds the transform argument.
   *
   */
  CompositeTransform( const Transform & );

  /** \brief A lazy copy constructor
   *
   * The new SimpleITK object will reference to the same underlying ITK
   * CompositeTransform. A deep-copy will be made when the object is modified.
   */
  CompositeTransform( const CompositeTransform & );

  /** \brief Create a composite from a vector of Transform
   *
   * The CompositeTransform is constructed from deep copies of the
   * Transforms. If the vector contains additional composite
   * transforms, deep copies will be made and nested composite
   * transforms will be constructed.
   *
   * An exception is thrown if the vector is empty.
   */
  explicit CompositeTransform(const std::vector<itk::simple::Transform> &);

  ~CompositeTransform() override;

  CompositeTransform &operator=( const CompositeTransform &);

  /** Name of this class */
  std::string GetName( ) const override  { return std::string("CompositeTransform");}


  /** \brief Removes nested composite transforms
   *
   * If this transform contains additional composite transforms, then these
   * nested composite transformed are removed, while preserving the order of the
   * regular transforms and transferring ownership to the parent
   * CompositeTransform.
   *
   * Nested composite transform may not be written to a file.
   */
  SITK_RETURN_SELF_TYPE_HEADER FlattenTransform();

  /** \brief Add a transform to the back of the stack.
   *
   * A deep-copy of the transform is performed. The added transform will have
   * the optimizable parameters, while the other parameters are part of the
   * fixed parameters.
   */
  SITK_RETURN_SELF_TYPE_HEADER AddTransform( Transform t );

  /** \brief The number of transforms in the stack */
  unsigned int GetNumberOfTransforms() const;

  /** \brief Remove all transforms from the stack. */
  void ClearTransforms();

  /** \brief Remove the active transform at the back.
   *
   * If the stack is empty an exception will be thrown.
   */
  void RemoveTransform();

  /** \brief Get a copy of the back transform.
   *
   * If the stack is empty an exception will be thrown.
   */
  Transform GetBackTransform();

  /** \brief Get a copy of a transform in the stack.
   *
   * If n is equal or greater than the number of transforms, then an exception
   * will be thrown.
   * */
  Transform GetNthTransform(unsigned int n);

protected:

  void SetPimpleTransform( PimpleTransformBase * ) override;

private:


  struct MyVisitor
  {
    itk::TransformBase *transform;
    CompositeTransform *that;
    template< typename TransformType >
    void operator() ( )
    {
      TransformType *t = dynamic_cast<TransformType*>(transform);
      if (t)
      {
        that->InternalInitialization(t);
        // set to null to stop trying dynamic_cast
        transform = nullptr;
      }
    }
  };

  void InternalInitialization(itk::TransformBase *transform);

  template<unsigned int NDimension>
  void InternalInitialization(itk::CompositeTransform< double, NDimension > *);

  template <unsigned int NDimensions>
  void InternalInitialization(itk::Transform<double, NDimensions, NDimensions> *);

  std::function<void ()> m_pfFlattenTransform;
  std::function<void ( Transform & )> m_pfAddTransform;
  std::function<void ()> m_pfRemoveTransform;
  std::function<Transform ()> m_pfBackTransform;
  std::function<Transform (unsigned int)> m_pfGetNthTransform;
  std::function<unsigned int ()> m_pfGetNumberOfTransforms;
  std::function<void ()> m_pfClearTransformQueue;
};

}
}

#endif // sitkCompositeTransform_h
