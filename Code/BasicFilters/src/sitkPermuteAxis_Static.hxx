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
#ifndef sitkPermiteAxis_Static_hxx
#define sitkPermiteAxis_Static_hxx

#include "sitkPermuteAxesImageFilter.h"

// This file is intended to contain the definition of static
// membervariables needed by JSON Expand templated image filters.
// It may also contain other member declarations, or other useful
// items that could be specified here, as opposed to the JSON.

namespace itk {
  namespace simple {

  const unsigned int PermuteAxesImageFilter::DefaultOrder[3] = {0,1,2};

  }
}

#endif
