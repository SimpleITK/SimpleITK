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
#ifndef __sitkDirectionConvert_hxx
#define  __sitkDirectionConvert_hxx

namespace itk
{
namespace simple
{

template< typename TDirectionType >
TDirectionType VectorToITKDirection( std::vector<double> &direction )
{
  TDirectionType itkDirection;

  if ( direction.size() == 0 )
  {
  itkDirection.SetIdentity();
  }
  else if( direction.size() == TDirectionType::RowDimensions*TDirectionType::ColumnDimensions )
    {
    std::copy( direction.begin(), direction.end(), itkDirection.GetVnlMatrix().begin() );
    }
  else
    {
    }

  return itkDirection;
}

} // end namespace simple
} // end namespace itk

#endif // __sitkDirectionConvert_hxx
