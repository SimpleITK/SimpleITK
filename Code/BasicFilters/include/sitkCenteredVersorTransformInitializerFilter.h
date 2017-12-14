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
#ifndef sitkCenteredVersorTransformInitializerFilter_h
#define sitkCenteredVersorTransformInitializerFilter_h

/*
 * WARNING: DO NOT EDIT THIS FILE!
 * THIS FILE IS AUTOMATICALLY GENERATED BY THE SIMPLEITK BUILD PROCESS.
 * Please look at sitkImageFilterTemplate.h.in to make changes.
 */

#include <memory>

#include "sitkBasicFilters.h"
#include "sitkProcessObject.h"
#include "sitkMemberFunctionFactory.h"

namespace itk {
  namespace simple {

    /**\class CenteredVersorTransformInitializerFilter
\brief CenteredVersorTransformInitializerFilter is a helper class
intended to initialize the center of rotation, versor, and translation
of the VersorRigid3DTransform.

This class derived from the CenteredTransformInitializerand uses it in
a more constrained context. It always uses the Moments mode, and also
takes advantage of the second order moments in order to initialize the
Versorrepresenting rotation.

\sa itk::CenteredVersorTransformInitializer for the Doxygen on the original ITK class.
     */
    class SITKBasicFilters_EXPORT CenteredVersorTransformInitializerFilter : public ProcessObject {
    public:
      typedef CenteredVersorTransformInitializerFilter Self;

      /** Default Constructor that takes no arguments and initializes
       * default parameters */
      CenteredVersorTransformInitializerFilter();

      /** Destructor */
      ~CenteredVersorTransformInitializerFilter();

      /** Define the pixels types supported by this filter */
      typedef BasicPixelIDTypeList  PixelIDTypeList;


      /**
       * Enable the use of the principal axes of each image to compute an initial rotation that will align them.
       */
      SITK_RETURN_SELF_TYPE_HEADER SetComputeRotation ( bool ComputeRotation ) { this->m_ComputeRotation = ComputeRotation; return *this; }

      /** Set the value of ComputeRotation to true or false respectfully. */
      SITK_RETURN_SELF_TYPE_HEADER ComputeRotationOn() { return this->SetComputeRotation(true); }
      SITK_RETURN_SELF_TYPE_HEADER ComputeRotationOff() { return this->SetComputeRotation(false); }

      /**
       * Enable the use of the principal axes of each image to compute an initial rotation that will align them.
       */
        bool GetComputeRotation() const { return this->m_ComputeRotation; }
      /** Name of this class */
      std::string GetName() const { return std::string ("CenteredVersorTransformInitializerFilter"); }

      /** Print ourselves out */
      std::string ToString() const;


      /** Execute the filter on the input image */
      Transform Execute ( const Image & fixedImage, const Image & movingImage, const Transform & transform );


      /** Execute the filter on the input image with the given parameters */
      Transform Execute ( const Image & fixedImage, const Image & movingImage, const Transform & transform, bool computeRotation );


    private:

      /** Setup for member function dispatching */

      typedef Transform (Self::*MemberFunctionType)( const Image * fixedImage, const Image * movingImage, const itk::simple::Transform * transform );
      template <class TImageType> Transform ExecuteInternal ( const Image * fixedImage, const Image * movingImage, const itk::simple::Transform * transform );


      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;

      nsstd::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;


      bool  m_ComputeRotation;
    };


    /**
     * \brief CenteredVersorTransformInitializer is a helper class intended to initialize the center of rotation, versor, and translation of the VersorRigid3DTransform.
     *
     * This function directly calls the execute method of CenteredVectorTransformInitializerFilter
     * in order to support a procedural API.
     *
     * \sa itk::simple::CenteredVersorTransformInitializerFilter for the object oriented interface
     */
  SITKBasicFilters_EXPORT Transform CenteredVersorTransformInitializer ( const Image & fixedImage, const Image & movingImage, const Transform & transform, bool computeRotation = false );

  }
}
#endif
