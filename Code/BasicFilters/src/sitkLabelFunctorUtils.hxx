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
#ifndef sitkLabelFunctorUtils_hxx
#define sitkLabelFunctorUtils_hxx

namespace itk
{
namespace simple
{

/** \brief Set the Colormap functor to the provided color map
 *
 * The implicit TLabelFunctorType template parameter is expected to
 * have the interface of itk::LabelToRGBFunctor. The functor's color
 * are reset. The color map parameter is expected to be triples of
 * R,G,B if the size is not divisible by 3 then the remainder are
 * ignored.
 */
template <typename TLabelFunctorType>
void
SetLabelFunctorFromColormap( TLabelFunctorType &functor, const std::vector<unsigned char> &colormap )
{
  if (colormap.size()/3 > 0 )
    {
    functor.ResetColors();
    }

  for(size_t i = 0; i < colormap.size(); i += 3)
    {
    functor.AddColor(colormap[i],colormap[i+1],colormap[i+2]);
    }
}

}
}

#endif //sitkLabelFunctorUtils_hxx
