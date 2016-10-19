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

#include "itkVariableLengthVector.h"


namespace itk {
namespace simple {


namespace
{

template <typename TValueType, typename TPixel>
static void ToPixelType( TValueType inPixel, TPixel &outPixel)
{
  outPixel = static_cast<TPixel>( inPixel );
}

template <typename TValueType, typename TComponent>
static void ToPixelType( TValueType inPixel, itk::VariableLengthVector<TComponent> &outPixel)
{
  outPixel.Fill( static_cast<TComponent>( inPixel ) );
}

}
}
}
