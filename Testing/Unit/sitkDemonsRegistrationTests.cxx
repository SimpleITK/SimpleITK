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

#include <SimpleITKTestHarness.h>

#include <sitkDemonsRegistrationFilter.h>
#include <sitkAdditiveGaussianNoiseImageFilter.h>
#include <sitkVectorMagnitudeImageFilter.h>
#include <sitkStatisticsImageFilter.h>
#include <sitkSubtractImageFilter.h>

TEST(DemonsRegistration, StopRegistration)
{
namespace sitk = itk::simple;

sitk::AdditiveGaussianNoiseImageFilter addNoise;
addNoise.SetSeed( 10 );
addNoise.SetMean( 0 );
addNoise.SetStandardDeviation( 1.0 );

sitk::Image fixed = addNoise.Execute(sitk::Image( {128, 128}, sitk::sitkFloat32 ));
fixed.SetPixelAsFloat({10,10}, 10);
fixed.SetPixelAsFloat({100,100}, 10);

addNoise.SetSeed( 11 );
sitk::Image moving = addNoise.Execute(sitk::Image( {128, 128}, sitk::sitkFloat32 ));
moving.SetPixelAsFloat({11,11}, 10);
moving.SetPixelAsFloat({101,101}, 10);



sitk::DemonsRegistrationFilter filter;

constexpr unsigned int stop_iteration = 2;

auto stopLambda =  [&filter, stop_iteration] (){ if ( filter.GetElapsedIterations() >= stop_iteration ){ filter.StopRegistration();}};
filter.AddCommand(sitk::sitkIterationEvent, stopLambda);


filter.SetNumberOfIterations( 50 );
filter.SetStandardDeviations( 1.0 );


EXPECT_ANY_THROW(filter.StopRegistration());

sitk::Image displacementField = filter.Execute( fixed, moving );
EXPECT_EQ(stop_iteration, filter.GetElapsedIterations());
EXPECT_LT( filter.GetMaximumRMSError(), filter.GetRMSChange() );

EXPECT_EQ( std::vector<unsigned int>({128,128}), displacementField.GetSize());

filter.RemoveAllCommands();
filter.SetNumberOfIterations(stop_iteration);

sitk::Image displacementField2 = filter.Execute( fixed, moving );

sitk::Image mag = sitk::VectorMagnitude(sitk::Subtract(displacementField, displacementField));
sitk::StatisticsImageFilter stats;
stats.Execute(mag);
EXPECT_NEAR(0.0, stats.GetSum(), 1e-4);

EXPECT_NO_THROW(filter.StopRegistration());
}
