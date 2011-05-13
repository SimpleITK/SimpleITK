#ifndef __SimpleITK_h
#define __SimpleITK_h

#include <stdint.h>

#include "sitkDetail.h"
#include "sitkMacro.h"
#include "sitkImage.h"
#include "sitkShow.h"

#include "sitkImageFilter.h"

#include "sitkHashImageFilter.h"
#include "sitkPixelIDTypeLists.h"
#include "sitkImageFileReader.h"
#include "sitkImageSeriesReader.h"
#include "sitkImageFileWriter.h"
#include "sitkStatisticsImageFilter.h"
#include "sitkLabelStatisticsImageFilter.h"
#include "sitkExtractImageFilter.h"
#include "sitkCastImageFilter.h"

#include "sitkConditional.h"

// Operators
#include "sitkImageOperators.h"

// Registration support
#include "sitkTransform.h"
#include "sitkAffineTransform.h"
#include "sitkLinearInterpolate.h"
#include "sitkMattesMutualInformationMetric.h"
#include "sitkRegistration.h"
#include "sitkRegularStepGradientDescentOptimizer.h"
#include "sitkResampleImageFilter.h"


// These headers are auto-generated
#include "SimpleITKBasicFiltersGeneratedHeaders.h"
#endif
