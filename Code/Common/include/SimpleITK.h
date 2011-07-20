#ifndef __SimpleITK_h
#define __SimpleITK_h

#include <stdint.h>

// Utility classes
#include "sitkDetail.h"
#include "sitkMacro.h"
#include "sitkVersion.h"
#include "sitkImage.h"
#include "sitkShow.h"

#include "sitkImageFilter.h"

// IO classes
#include "sitkImageFileReader.h"
#include "sitkImageSeriesReader.h"
#include "sitkImageFileWriter.h"
#include "sitkImportImageFilter.h"


#include "sitkHashImageFilter.h"
#include "sitkPixelIDTypeLists.h"
#include "sitkStatisticsImageFilter.h"
#include "sitkLabelStatisticsImageFilter.h"

#include "sitkCastImageFilter.h"

// Registration support
#include "sitkTransform.h"
#include "sitkAffineTransform.h"
#include "sitkLinearInterpolate.h"
#include "sitkMattesMutualInformationMetric.h"
#include "sitkRegistration.h"
#include "sitkRegularStepGradientDescentOptimizer.h"


// These headers are auto-generated
#include "SimpleITKBasicFiltersGeneratedHeaders.h"
#endif
