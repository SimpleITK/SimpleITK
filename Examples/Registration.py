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

fixed = sitk.Cast( sitk.ReadImage( "r16slice_rigid.nii.gz" ), sitk.sitkFloat32 )
moving = sitk.Cast( sitk.ReadImage( "r64slice.nii.gz" ), sitk.sitkFloat32 )

moving = sitk.HistogramMatching( moving, fixed, inNumberOfHistogramLevels = 256, inNumberOfMatchPoints = 12, inThresholdAtMeanIntensity = True )

R = sitk.ANTSRegistration()

R.SetIterations( [100, 100] )
R.SetSmoothingSigmas( [ 2.0, 1.0 ] )
R.SetShrinkFactors( [ 3, 2] )

R.SetMetricAsMutualInformation( 32 )
R.SetTransformationAsAffine( 0.25 )

tx = sitk.Transform( fixed.GetDimension(), sitk.sitkComposite )
tx.AddTransform( sitk.Transform( fixed.GetDimension(), sitk.sitkIdentity ) )

tx = R.Execute( fixed, moving, tx )
print tx

ResampleIF = sitk.ResampleImageFilter()
ResampleIF.SetReferenceImage( fixed )
ResampleIF.SetTransform( tx )

out1 = ResampleIF.Execute( moving )
sitk.Show( out1, "Registered Affine" )
sitk.Show( fixed, "Fixed" );
sitk.Show( moving, "Moving" )


R.SetIterations( [30,20] )
R.SetSmoothingSigmas( [1.0,0.5] )
R.SetShrinkFactors( [2,1] )
R.SetTransformationAsTimeVaryingBSplineVelocityField(0.8,[4,4,2],4,3)
R.SetMetricAsNeighborhoodCrossCorreclation( 4, 1 )

tx = R.Execute( fixed, moving, tx )


ResampleIF = sitk.ResampleImageFilter()
ResampleIF.SetReferenceImage( fixed )
ResampleIF.SetTransform( tx )

out2 = ResampleIF.Execute( moving )
sitk.Show( out2, "Registered TimeVarying" )
sitk.Show( sitk.Abs( out2-fixed ), "Difference" )
