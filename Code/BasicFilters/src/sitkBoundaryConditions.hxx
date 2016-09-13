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
#ifndef sitkBoundaryConditions_h
#define sitkBoundaryConditions_h

#include <memory>
#include <itkConstantBoundaryCondition.h>
#include <itkPeriodicBoundaryCondition.h>
#include <itkZeroFluxNeumannBoundaryCondition.h>

namespace itk {
  namespace simple {

  /** Creates a boundary condition object from an enum. Uses an
   * auto_ptr for dynamically allocated object, to enforce the user to
   * take ownership of the object.
   *
   */
  template< class TFilter, class TInternalFilter >
  nsstd::auto_ptr<ImageBoundaryCondition< typename TInternalFilter::InputImageType > >
  CreateNewBoundaryConditionInstance(typename TFilter::BoundaryConditionType bc)
  {
    typedef nsstd::auto_ptr<ImageBoundaryCondition< typename TInternalFilter::InputImageType > > PointerType;

    switch ( bc )
      {
      case TFilter::ZERO_PAD:
        return PointerType(new ConstantBoundaryCondition< typename TInternalFilter::InputImageType >() );
        break;

      case TFilter::PERIODIC_PAD:
        return PointerType( new PeriodicBoundaryCondition< typename TInternalFilter::InputImageType >() );
        break;

      case TFilter::ZERO_FLUX_NEUMANN_PAD:
      default:
        return PointerType( new ZeroFluxNeumannBoundaryCondition< typename TInternalFilter::InputImageType >() );
        break;
      }
    }
  }
}

#endif
