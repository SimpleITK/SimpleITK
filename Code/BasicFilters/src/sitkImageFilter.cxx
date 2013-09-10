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
#include "sitkImageFilter.h"
#include "sitkImageFilterExecuteBase.hxx"

namespace itk {
namespace simple {

namespace
{
static bool GlobalDefaultDebug = false;
}

//----------------------------------------------------------------------------

//
// Default constructor that initializes parameters
//
template< unsigned int N >
ImageFilter< N >::ImageFilter ()
  : m_Debug(GlobalDefaultDebug)
  {
  }

//
// Default destructor
//
template< unsigned int N >
ImageFilter< N >::~ImageFilter ()
  {
  }

template< unsigned int N >
std::ostream & ImageFilter< N >::ToStringHelper(std::ostream &os, const char &v)
{
  os << int(v);
  return os;
}

template< unsigned int N >
std::ostream & ImageFilter< N >::ToStringHelper(std::ostream &os, const signed char &v)
{
  os << int(v);
  return os;
}

template< unsigned int N >
std::ostream & ImageFilter< N >::ToStringHelper(std::ostream &os, const unsigned char &v)
{
  os << int(v);
  return os;
}


template< unsigned int N > void ImageFilter< N >::DebugOn()
{
  this->m_Debug = true;
}

template< unsigned int N > void ImageFilter< N >::DebugOff()
{
  this->m_Debug = false;
}

template< unsigned int N > bool ImageFilter< N >::GetDebug() const
{
  return this->m_Debug;
}


template< unsigned int N > void ImageFilter< N >::SetDebug( bool debugFlag)
{
  this->m_Debug = debugFlag;
}


template< unsigned int N > void ImageFilter< N >::GlobalDefaultDebugOn()
{
  GlobalDefaultDebug = true;
}

template< unsigned int N > void ImageFilter< N >::GlobalDefaultDebugOff()

{
  GlobalDefaultDebug = false;
}

template< unsigned int N > bool ImageFilter< N >::GetGlobalDefaultDebug()
{
  return GlobalDefaultDebug;
}

template< unsigned int N > void ImageFilter< N >::SetGlobalDefaultDebug(bool debugFlag)
{
  GlobalDefaultDebug = debugFlag;
}



template class ImageFilter<0>;
template class ImageFilter<1>;
template class ImageFilter<2>;
template class ImageFilter<3>;
template class ImageFilter<4>;
template class ImageFilter<5>;

} // end namespace simple
} // end namespace itk
