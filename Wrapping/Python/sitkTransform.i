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
%extend itk::simple::Transform {
   %pythoncode
%{

        def __copy__(self):
          """Create a SimpleITK shallow copy, where the internal transform is shared with a copy on write implementation."""
          return self.__class__(self)

        def __deepcopy__(self, memo):
          """Create a new copy of the data and internal ITK Transform object."""
          dc = self.__class__(self)
          dc.MakeUnique()
          return dc

        def __setstate__(self, args):
          if args[0] != 0:
            raise ValueError("Unable to handle SimpleITK.Transform pickle version {0}".args[0])

          if len(args) == 1:
            return

          state = namedtuple('state_tuple_0', "version fixed_parameters parameters")(*args)

          self.SetFixedParameters(state.fixed_parameters)
          self.SetParameters(state.parameters)


        def __reduce_ex__(self, protocol):
          version = 0

          downcasted = self.Downcast()

          if downcasted.__class__ is DisplacementFieldTransform:
            dis = downcasted.GetDisplacementField()
            if all( 0 == s for s in dis.GetSize() ):
                # The null state needs special handling
                args = (downcasted.GetDimension(),)
                S = (version, downcasted.GetFixedParameters(), downcasted.GetParameters())
            else:
                args = (dis, )
                S = (version, )
          elif downcasted.__class__ is BSplineTransform:
            args = (tuple(downcasted.GetCoefficientImages()), downcasted.GetOrder())
            S = (version, )
          elif downcasted.__class__ == CompositeTransform:
            if downcasted.GetNumberOfTransforms() > 0:
               args = ([ downcasted.GetNthTransform(n) for n in range(downcasted.GetNumberOfTransforms()) ], )
            else:
               args = (downcasted.GetDimension(),)
            S = (version, )

          else:
            args = ()
            if downcasted.__class__ in [AffineTransform, ScaleTransform, TranslationTransform]:
                args = (downcasted.GetDimension(),)
            elif downcasted.__class__ is Transform:
                args = (downcasted.GetDimension(), downcasted.GetTransformEnum())

            S = (version, downcasted.GetFixedParameters(), downcasted.GetParameters())

          return downcasted.__class__, args, S

        def Downcast(self):
            """Convert to the appropriate derived SimpleITK object. A lazy copy to
            the underlying ITK object is performed. """

            transform_downcast_map  = {
                sitkUnknownTransform: (None, None),
                sitkIdentity: (Transform, Transform),
                sitkTranslation: (TranslationTransform, TranslationTransform),
                sitkScale: (ScaleTransform, ScaleTransform),
                sitkScaleLogarithmic: (Transform, Transform),
                sitkEuler: (Euler2DTransform, Euler3DTransform),
                sitkSimilarity: (Similarity2DTransform, Similarity3DTransform),
                sitkQuaternionRigid: (None, Transform),
                sitkVersor: (None, VersorTransform),
                sitkVersorRigid: ( None, VersorRigid3DTransform),
                sitkScaleSkewVersor: ( None, ScaleSkewVersor3DTransform),
                sitkScaleVersor: ( None, ScaleVersor3DTransform),
                sitkAffine: (AffineTransform, AffineTransform),
                sitkComposite: (CompositeTransform, CompositeTransform),
                sitkDisplacementField: (DisplacementFieldTransform, DisplacementFieldTransform),
                sitkBSplineTransform: (BSplineTransform, BSplineTransform)
            }

            id = self.GetTransformEnum()
            if id is sitkUnknownTransform:
                raise TypeError("Unknown internal ITK transform type.")
            downcast_type = transform_downcast_map[id][self.GetDimension()-2]
            if downcast_type is None:
                raise TypeError("Unable to downcast transform type.")
            return downcast_type(self)
%}

}
