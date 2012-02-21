#=========================================================================
#
#  Copyright Insight Software Consortium
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0.txt
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
#=========================================================================
import SimpleITK as sitk

fixed = sitk.Cast( sitk.ReadImage( "r16slice.nii.gz" ), sitk.sitkFloat32 )
moving = sitk.Cast( sitk.ReadImage( "r64slice.nii.gz" ), sitk.sitkFloat32 )

moving = sitk.HistogramMatching( moving, fixed, inNumberOfHistogramLevels = 256, inNumberOfMatchPoints = 12, inThresholdAtMeanIntensity = True )

R = sitk.ANTSRegistration()

R.SetIterations( [200, 200] )
R.SetSmoothingSigmas( [ 2.0, 1.0 ] )
R.SetShrinkFactors( [ 4, 2] )

R.SetMetricAsNeighborhoodCrossCorreclation( 16 )
R.SetTransformationAsAffine( .1 )


tx = R.Execute( fixed, moving )
print tx

ResampleIF = sitk.ResampleImageFilter()
ResampleIF.SetReferenceImage( fixed )
ResampleIF.SetTransform( tx )
out1 = ResampleIF.Execute( moving )

sitk.Show( out1, "Registered" )
sitk.Show( fixed, "Fixed" );
sitk.Show( moving, "Moving" )
sitk.Show( sitk.Abs( moving-fixed ), "Initial Difference" )
sitk.Show( sitk.Abs( out1-fixed ), "Registered Difference" )
sitk.Show( sitk.Abs( out1-moving ), "Difference To moving" )
