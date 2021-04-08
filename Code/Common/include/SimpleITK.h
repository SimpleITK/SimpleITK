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
#ifndef SimpleITK_h
#define SimpleITK_h

/** \file SimpleITK.h
 *
 * Image C++ operators are not include by default in this file is an
 * intentional  design  choice. The addition of these convenience
 * mathematical operators in C++ can be a source of confusion.
 *
 * To enable Image C++ operators explicitly include
 * sitkImageOperators.h header file.
 */

#include <stdint.h>


// Utility classes
#include "sitkMacro.h"
#include "sitkDetail.h"
#include "sitkVersion.h"
#include "sitkImage.h"
#include "sitkTransform.h"
#include "sitkBSplineTransform.h"
#include "sitkDisplacementFieldTransform.h"
#include "sitkAffineTransform.h"
#include "sitkEuler2DTransform.h"
#include "sitkEuler3DTransform.h"
#include "sitkScaleTransform.h"
#include "sitkScaleSkewVersor3DTransform.h"
#include "sitkComposeScaleSkewVersor3DTransform.h"
#include "sitkScaleVersor3DTransform.h"
#include "sitkSimilarity2DTransform.h"
#include "sitkSimilarity3DTransform.h"
#include "sitkTranslationTransform.h"
#include "sitkVersorTransform.h"
#include "sitkVersorRigid3DTransform.h"
#include "sitkCompositeTransform.h"
#include "sitkShow.h"

#include "sitkInterpolator.h"
#include "sitkEvent.h"
#include "sitkRandomSeed.h"

#include "sitkProcessObject.h"
#include "sitkImageFilter.h"
#include "sitkObjectOwnedBase.h"
#include "sitkCommand.h"
#include "sitkFunctionCommand.h"
#include "sitkLogger.h"

// IO classes
#include "sitkImageFileReader.h"
#include "sitkImageSeriesReader.h"
#include "sitkImageFileWriter.h"
#include "sitkImageSeriesWriter.h"
#include "sitkImportImageFilter.h"
#include "sitkImageViewer.h"


#include "sitkHashImageFilter.h"
#include "sitkJoinSeriesImageFilter.h"
#include "sitkComposeImageFilter.h"
#include "sitkPixelIDTypeLists.h"

#include "sitkBSplineTransformInitializerFilter.h"
#include "sitkCenteredTransformInitializerFilter.h"
#include "sitkCenteredVersorTransformInitializerFilter.h"
#include "sitkLandmarkBasedTransformInitializerFilter.h"
#include "sitkCastImageFilter.h"
#include "sitkExtractImageFilter.h"
#include "sitkPasteImageFilter.h"

#include "sitkAdditionalProcedures.h"

#include "sitkImageRegistrationMethod.h"

// These headers are auto-generated
#include "SimpleITKBasicFiltersGeneratedHeaders.h"
#endif
