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
#ifndef __sitkShow_h
#define __sitkShow_h

#include "sitkImage.h"
#include "sitkIO.h"

namespace itk
{
namespace simple
{

  /** Display an image using ImageJ
   *
   *  This function requires that ImageJ
   *  (\see http://rsb.info.nih.gov/ij/) be properly installed for Mac
   *  and Windows, and in the user's path for Linux.  ImageJ must have
   *  a plugin for reading Nifti formatted files (\see
   *  http://www.loci.wisc.edu/bio-formats/imagej)
   **/
   void SITKIO_EXPORT Show ( const Image &image, const std::string title = "" );
}
}

#endif
