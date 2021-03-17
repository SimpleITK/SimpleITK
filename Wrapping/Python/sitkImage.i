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


%rename( __GetPixelAsInt8__ ) itk::simple::Image::GetPixelAsInt8;
%rename( __GetPixelAsUInt8__ ) itk::simple::Image::GetPixelAsUInt8;
%rename( __GetPixelAsInt16__ ) itk::simple::Image::GetPixelAsInt16;
%rename( __GetPixelAsUInt16__ ) itk::simple::Image::GetPixelAsUInt16;
%rename( __GetPixelAsInt32__ ) itk::simple::Image::GetPixelAsInt32;
%rename( __GetPixelAsUInt32__ ) itk::simple::Image::GetPixelAsUInt32;
%rename( __GetPixelAsInt64__ ) itk::simple::Image::GetPixelAsInt64;
%rename( __GetPixelAsUInt64__ ) itk::simple::Image::GetPixelAsUInt64;
%rename( __GetPixelAsFloat__ ) itk::simple::Image::GetPixelAsFloat;
%rename( __GetPixelAsDouble__ ) itk::simple::Image::GetPixelAsDouble;
%rename( __GetPixelAsVectorInt8__ ) itk::simple::Image::GetPixelAsVectorInt8;
%rename( __GetPixelAsVectorUInt8__ ) itk::simple::Image::GetPixelAsVectorUInt8;
%rename( __GetPixelAsVectorInt16__ ) itk::simple::Image::GetPixelAsVectorInt16;
%rename( __GetPixelAsVectorUInt16__ ) itk::simple::Image::GetPixelAsVectorUInt16;
%rename( __GetPixelAsVectorInt32__ ) itk::simple::Image::GetPixelAsVectorInt32;
%rename( __GetPixelAsVectorUInt32__ ) itk::simple::Image::GetPixelAsVectorUInt32;
%rename( __GetPixelAsVectorInt64__ ) itk::simple::Image::GetPixelAsVectorInt64;
%rename( __GetPixelAsVectorUInt64__ ) itk::simple::Image::GetPixelAsVectorUInt64;
%rename( __GetPixelAsVectorFloat32__ ) itk::simple::Image::GetPixelAsVectorFloat32;
%rename( __GetPixelAsVectorFloat64__ ) itk::simple::Image::GetPixelAsVectorFloat64;
%rename( __GetPixelAsComplexFloat32__ ) itk::simple::Image::GetPixelAsComplexFloat32;
%rename( __GetPixelAsComplexFloat64__ ) itk::simple::Image::GetPixelAsComplexFloat64;

%rename( __SetPixelAsInt8__ ) itk::simple::Image::SetPixelAsInt8;
%rename( __SetPixelAsUInt8__ ) itk::simple::Image::SetPixelAsUInt8;
%rename( __SetPixelAsInt16__ ) itk::simple::Image::SetPixelAsInt16;
%rename( __SetPixelAsUInt16__ ) itk::simple::Image::SetPixelAsUInt16;
%rename( __SetPixelAsInt32__ ) itk::simple::Image::SetPixelAsInt32;
%rename( __SetPixelAsUInt32__ ) itk::simple::Image::SetPixelAsUInt32;
%rename( __SetPixelAsInt64__ ) itk::simple::Image::SetPixelAsInt64;
%rename( __SetPixelAsUInt64__ ) itk::simple::Image::SetPixelAsUInt64;
%rename( __SetPixelAsFloat__ ) itk::simple::Image::SetPixelAsFloat;
%rename( __SetPixelAsDouble__ ) itk::simple::Image::SetPixelAsDouble;
%rename( __SetPixelAsVectorInt8__ ) itk::simple::Image::SetPixelAsVectorInt8;
%rename( __SetPixelAsVectorUInt8__ ) itk::simple::Image::SetPixelAsVectorUInt8;
%rename( __SetPixelAsVectorInt16__ ) itk::simple::Image::SetPixelAsVectorInt16;
%rename( __SetPixelAsVectorUInt16__ ) itk::simple::Image::SetPixelAsVectorUInt16;
%rename( __SetPixelAsVectorInt32__ ) itk::simple::Image::SetPixelAsVectorInt32;
%rename( __SetPixelAsVectorUInt32__ ) itk::simple::Image::SetPixelAsVectorUInt32;
%rename( __SetPixelAsVectorInt64__ ) itk::simple::Image::SetPixelAsVectorInt64;
%rename( __SetPixelAsVectorUInt64__ ) itk::simple::Image::SetPixelAsVectorUInt64;
%rename( __SetPixelAsVectorFloat32__ ) itk::simple::Image::SetPixelAsVectorFloat32;
%rename( __SetPixelAsVectorFloat64__ ) itk::simple::Image::SetPixelAsVectorFloat64;
%rename( __SetPixelAsComplexFloat32__ ) itk::simple::Image::SetPixelAsComplexFloat32;
%rename( __SetPixelAsComplexFloat64__ ) itk::simple::Image::SetPixelAsComplextFloat64;


%pythoncode %{
   import operator
   import sys
   from collections import namedtuple
%}

%extend itk::simple::Image {

        Image __iadd__ ( const Image &i )
        {
          return (*$self) += i;
        }
        Image __iadd__ ( double c )
        {
          return (*$self) += c;
        }
        Image __isub__ ( const Image &i )
        {
          return (*$self) -= i;
        }
        Image __isub__ ( double c )
        {
          return (*$self) -= c;
        }
        Image __imul__ ( const Image &i )
        {
          return (*$self) *=  i;
        }
        Image __imul__ ( double c )
        {
          return (*$self) *=  c;
        }
        Image __imod__ ( const Image &i )
        {
          return (*$self) %=  i;
        }
        Image __imod__ ( int c )
        {
          return (*$self) %=  c;
        }



        Image __ifloordiv__ ( const Image &i )
        {
          return ((*$self) = DivideFloor(std::move(*$self), i));
        }
        Image __ifloordiv__ ( double c )
        {
          return ((*$self) = DivideFloor(std::move(*$self), c));
        }
        Image __itruediv__ ( const Image &i )
        {
          return ((*$self) = DivideReal(std::move(*$self), i));
        }
        Image __itruediv__ ( double c )
        {
          return ((*$self) = DivideReal(std::move(*$self), c));
        }


        Image __ipow__ ( const Image &i )
        {
          return ((*$self) = Pow(std::move(*$self), i));
        }
        Image __ipow__ ( double c)
        {
          return ((*$self) = Pow(std::move(*$self), c));
        }


        Image __ior__ ( const Image &i )
        {
          return (*$self) |=  i;
        }
        Image __ior__ ( int c )
        {
          return (*$self) |=  c;
        }
        Image __ixor__ ( const Image &i )
        {
          return (*$self) ^=  i;
        }
        Image __ixor__ ( int c )
        {
          return (*$self) ^=  c;
        }
        Image __iand__ ( const Image &i )
        {
          return (*$self) &=  i;
        }
        Image __iand__ ( int c )
        {
          return (*$self) &=  c;
        }
        // A wrapper for performing the paste operation in place
        Image __ipaste(const Image & sourceImage,
                   std::vector< unsigned int > sourceSize,
                   std::vector< int > sourceIndex,
                   std::vector< int > destinationIndex,
                   std::vector< bool > destinationSkipAxes)
        {
        itk::simple::PasteImageFilter paster;
        paster.SetSourceSize(std::move(sourceSize));
        paster.SetSourceIndex(std::move(sourceIndex));
        paster.SetDestinationIndex(std::move(destinationIndex));
        paster.SetDestinationSkipAxes(std::move(destinationSkipAxes));
        return (*$self) = paster.Execute(std::move(*$self), sourceImage);
        }
        Image __ipaste(double constant,
                   std::vector< unsigned int > sourceSize,
                   std::vector< int > sourceIndex,
                   std::vector< int > destinationIndex,
                   std::vector< bool > destinationSkipAxes)
        {
        itk::simple::PasteImageFilter paster;
        paster.SetSourceSize(std::move(sourceSize));
        paster.SetSourceIndex(std::move(sourceIndex));
        paster.SetDestinationIndex(std::move(destinationIndex));
        paster.SetDestinationSkipAxes(std::move(destinationSkipAxes));
        return (*$self) = paster.Execute(std::move(*$self), constant);
        }


        %pythoncode %{

        def __copy__(self):
          """Create a SimpleITK shallow copy, where the internal image share is shared with copy on write implementation."""
          return Image(self)

        def __deepcopy__(self, memo):
          """Create a new copy of the data and image class."""
          dc = Image(self)
          dc.MakeUnique()
          return dc

        def __setstate__(self, args):
          if args[0] != 0:
            raise ValueError("Unable to handle SimpleITK.Image pickle version {0}".args[0])

          state = namedtuple('state_tuple_0', "version buffer origin spacing direction metadata")(*args)

          _SetImageFromArray(state.buffer, self)
          self.SetOrigin(state.origin)
          self.SetSpacing(state.spacing)
          self.SetDirection(state.direction)
          for k,v in state.metadata.items():
            self.SetMetaData(k,v)

        def __reduce_ex__(self, protocol ):
          version = 0
          size = tuple(self.GetSize())
          t = int(self.GetPixelIDValue())
          ncomponents = int(self.GetNumberOfComponentsPerPixel())

          mv = _GetMemoryViewFromImage(self)
          origin = tuple(self.GetOrigin())
          spacing = tuple(self.GetSpacing())
          direction = tuple(self.GetDirection())
          metadata = {k:self.GetMetaData(k) for k in self.GetMetaDataKeys()}

          if protocol >= 5:
            import sys
            if sys.hexversion >= 0x03080000:
              import pickle
            elif sys.hexversion >= 0x03060000:
              try:
                import pickle5 as pickle
              except ImportError:
                raise ImportError("Pickle protocol 5 requires the pickle5 module for Python 3.6, 3.7")
            P = (version, pickle.PickleBuffer(mv), origin, spacing, direction, metadata)
          else:
            P = (version, mv.tobytes(), origin, spacing, direction, metadata)

          return self.__class__, (size, t, ncomponents), P



        # mathematical operators

        def __add__( self, other ):
            if isinstance( other, Image ):
               return Add( self, other )
            try:
               return Add( self, float(other)  )
            except ValueError:
               return NotImplemented
        def __sub__( self, other ):
            if isinstance( other, Image ):
               return Subtract( self, other )
            try:
               return Subtract( self, float(other) )
            except ValueError:
               return NotImplemented
        def __mul__( self, other ):
            if isinstance( other, Image ):
               return Multiply( self, other )
            try:
               return Multiply( self, float(other) )
            except ValueError:
               return NotImplemented
        def __div__( self, other ):
            if isinstance( other, Image ):
               return Divide( self, other )
            try:
               return Divide( self, float(other) )
            except ValueError:
               return NotImplemented
        def __floordiv__( self, other ):
            if isinstance( other, Image ):
               return DivideFloor( self, other )
            try:
               return DivideFloor( self, float(other) )
            except ValueError:
               return NotImplemented
        def __truediv__( self, other ):
            if isinstance( other, Image ):
               return DivideReal( self, other )
            try:
               return DivideReal( self, float(other) )
            except ValueError:
               return NotImplemented


        def __neg__( self ):
            return UnaryMinus( self )
        def __pos__( self ):
            return self

        # NOTE: for the reverse methods other cannot be an image, so
        # therefore other should be able to be considered a constant.

        def __radd__( self, other ):
            try:
               return Add( float(other), self )
            except ValueError:
               return NotImplemented
        def __rsub__( self, other ):
            try:
               return Subtract( float(other), self )
            except ValueError:
               return NotImplemented
        def __rmul__( self, other ):
            try:
               return Multiply( float(other), self )
            except ValueError:
               return NotImplemented
        def __rdiv__( self, other ):
            try:
               return Divide( float(other), self )
            except ValueError:
               return NotImplemented
        def __rfloordiv__( self, other ):
            try:
               return DivideFloor( float(other), self )
            except ValueError:
               return NotImplemented
        def __rtruediv__( self, other ):
            try:
               return DivideReal( float(other), self )
            except ValueError:
               return NotImplemented


        # logic operators

        def __and__( self, other ):
            if isinstance( other, Image ):
               return And( self, other )
            try:
               return And( self, int(other) )
            except ValueError:
               return NotImplemented
        def __rand__( self, other ):
            try:
               return And( int(other), self )
            except ValueError:
               return NotImplemented
        def __or__( self, other ):
            if isinstance( other, Image ):
               return Or( self, other )
            try:
               return Or( self, int(other) )
            except ValueError:
               return NotImplemented
        def __ror__( self, other ):
            try:
               return Or( int(other), self )
            except ValueError:
               return NotImplemented
        def __xor__( self, other ):
            if isinstance( other, Image ):
               return Xor( self, other )
            try:
               return Xor( self, int(other) )
            except ValueError:
               return NotImplemented
        def __rxor__( self, other ):
            try:
               return Xor( int(other), self )
            except ValueError:
               return NotImplemented
        def __invert__( self ): return BitwiseNot( self )

        # Relational and Equality operators

        def __lt__( self, other ):
            if isinstance( other, Image ):
               return Less( self, other )
            try:
               return Less( self, float(other) )
            except (ValueError, TypeError):
               return NotImplemented
        def __le__( self, other ):
            if isinstance( other, Image ):
               return LessEqual( self, other )
            try:
               return LessEqual( self, float(other) )
            except (ValueError, TypeError):
               return NotImplemented
        def __eq__( self, other ):
            if isinstance( other, Image ):
               return Equal( self, other )
            try:
               return Equal( self, float(other) )
            except (ValueError, TypeError):
               return NotImplemented
        def __ne__( self, other ):
            if isinstance( other, Image ):
               return NotEqual( self, other )
            try:
               return NotEqual( self, float(other) )
            except (ValueError, TypeError):
               return NotImplemented
        def __gt__( self, other ):
            if isinstance( other, Image ):
               return Greater( self, other )
            try:
               return Greater( self, float(other) )
            except (ValueError, TypeError):
               return NotImplemented
        def __ge__( self, other ):
            if isinstance( other, Image ):
               return GreaterEqual( self, other )
            try:
               return GreaterEqual( self, float(other) )
            except (ValueError, TypeError):
               return NotImplemented


        # "function" operators

        def __pow__( self, other ):
            if isinstance( other, Image ):
               return Pow( self, other )
            try:
               return Pow( self, float(other) )
            except ValueError:
               return NotImplemented
        def __rpow__( self, other ):
            try:
               return Pow( float(other), self )
            except ValueError:
               return NotImplemented
        def __mod__( self, other ):
            if isinstance( other, Image ):
               return Modulus( self, other )
            try:
               return Modulus( self, float(other) )
            except ValueError:
               return NotImplemented
        def __abs__( self ):
            return Abs( self )

        # iterator and container methods

        def __iter__( self ):

            if len(self) == 0:
              return

            dim = self.GetDimension()
            size = self.GetSize()
            idx = [0] * dim

            while idx[dim-1] < size[dim-1]:

              yield self[ idx ]

              # increment the idx
              for d in range( 0, dim ):
                idx[d] += 1
                if idx[d] >= size[d] and d != dim  - 1:
                   idx[d] = 0
                else:
                   break

            return

        def __len__( self ):
            l = 1
            for ds in self.GetSize():
              l *= ds
            return l

        # set/get pixel methods

        def __delitem__( self, key ):
            """Remove an item from the meta-data dictionary.

            It is an exception to delete the "origin", "spacing" and "direction" reserved keys.

            If the key does not exist in the dictionary no action or exception occours.
            """
            if not isinstance(key, str):
              raise TypeError("MetaData dictionary key must be str")
            if key in [ 'origin', 'spacing', 'direction' ]:
              raise KeyError(f"'{key} is read-only")
            return self.EraseMetaData( key )


        def __contains__( self, key ):
            """Test if key is contained in the meta-data dictionary.
            """
            if not isinstance(key, str):
              raise TypeError("MetaData dictionary key must be str")
            return key in [ 'origin', 'spacing', 'direction' ] or self.HasMetaDataKey( key )

        def _expand_ellipsis(self, idx):
            """Expand "..." in idx with slice(None) to fill to dimension."""
            if Ellipsis in idx:
              if idx.count(Ellipsis) > 1:
                raise IndexError("an index can only have one ellipses ('...')")
              nidx = []
              for i in range(len(idx)):
                if idx[i] is Ellipsis:
                  dim = self.GetDimension()
                  nidx.extend( [slice(None)]*(dim - len(idx) + 1) )
                else:
                  nidx.append(idx[i])
              return tuple(nidx)
            return tuple(idx)


        def __getitem__( self, idx ):
            """ Get an pixel value, a sliced image, or a metadata item

            This operator implements basic indexing where idx is
            arguments or a squence of integers the same dimension as
            the image. The result will be a pixel value from that
            index.

            Multi-dimension extended slice based indexing is also
            implemented. The return is a copy of a new image. The
            standard sliced based indices are supported including
            negative indices, to indicate location relative to the
            end, along with negative step sized to indicate reversing
            of direction.

            If the length of idx is less than the number of dimension
            of the image it will be padded with the defaults slice
            ":".

            When an index element is an integer, that dimension is
            collapsed extracting an image with reduced dimensionality.
            The minimum dimension of an image which can be extracted
            is 2D.

            If indexing with a string, then the metadata dictionary
            queried with the index as the key. If the metadata dictionary
            does not contain the key, a KeyError will occour.
            """

            if isinstance(idx, str):
              if idx == 'origin':
                return self.GetOrigin()
              elif idx == 'spacing':
                return self.GetSpacing()
              elif idx == 'direction':
                return self.GetDirection()
              else:
                try:
                  return self.GetMetaData(idx)
                except RuntimeError as e:
                    if not self.HasMetaDataKey( idx ):
                      raise KeyError(f"\"{idx}\" not in meta-data dictionary")
                    raise e

            if sys.version_info[0] < 3:
              def isint( i ):
                return type(i) == int or type(i) == long
            else:
              def isint( i ):
                return type(i) == int

            dim = self.GetDimension()
            size = self.GetSize()

            try:
              len(idx)
            except TypeError as e:
              # if the len function did not work then, assume is a
              # non-iterable, and make it a single element then an ...
              if idx == Ellipsis:
                idx = (Ellipsis,)
              else:
                idx = (idx, Ellipsis)

            if len(idx) > dim + (Ellipsis in idx):
              raise IndexError("too many indices for image")
            if (len(idx) < dim) and Ellipsis not in idx:
              # if the argument tuple has fewer elements then the dimension of the image then extend to match that of the image
              idx = tuple(idx) + (Ellipsis,)

            idx = self._expand_ellipsis(idx)

            # All the indices are integers just return GetPixel value
            if all( isint(i) for i in idx ):
              # if any of the arguments are negative integers subract them for the size
              idx = [idx[i] if idx[i] >= 0 else (size[i] + idx[i]) for i in range(len(idx))]

              for i in range(len(idx)):
                if idx[i] < 0 or idx[i] >= size[i]:
                  raise IndexError("index {0} is outside the extent for dimension {1} with size {2}".format( idx[i], i, size[i]))

              return self.GetPixel(*tuple(idx))


            # If an index is an integer then we are extracting to a small dimension
            slice_dims = []
            for i in range(len(idx)):
              if type(idx[i]) is slice:
                continue
              elif isint(idx[i]):
                slice_dims.append(i)

                s = idx[i]
                if s < 0:
                  s += size[i]
                if s < 0 or s >= size[i]:
                  raise IndexError("index {0} is outside the extent for dimension {1} with size {2}".format( idx[i], i, size[i]))


                idx = tuple(idx[:i]) + (slice(s, s+1),)+ tuple(idx[i+1:])

            if dim - len(slice_dims) < 2:
              raise IndexError("invalid slice extraction to 1 dimension")


            # Use the slice filter when all the elements are slices ( or have been processed to be )
            if all( type(i) is slice for i in idx ):

              # perform standard slice indexing, to clamp to ranges and add in defaults
              sidx = [ idx[i].indices(size[i]) for i in range(len(idx ))]

              # extract each element of the indices rages together
              (start, stop, step) = zip(*sidx)

              # run the slice filter
              img = Slice(self, start=start, stop=stop, step=step)

              if slice_dims:
                size = img.GetSize();

                # set the slice dimension size to 0
                for i in slice_dims:
                  size = tuple(size[:i]) + (0,) + tuple(size[i+1:])

                # Reduce the dimension of the image
                img = Extract( img, size )

              return img


            # the index parameter was an invalid set of objects
            raise IndexError("invalid index")


        def __setitem__( self, idx, rvalue ):
            """Sets this image's pixel value(s) to rvalue.

            The dimension of idx must match that of the image.

            If all indices are integers then rvalue should be a pixel value
            ( scalar or sequence for vector pixels). The value is assigned to
            the pixel.

            If the indices are slices or integers then, the PasteImageFilter is
            used to assign values to this image. The rvalue can be an image
            or a scalar constant value. When rvalue is an image it must be of
            the same pixel type and equal or lesser dimension than self. The
            region defined by idx and rvalue's size must be compatible. The
            region defined by idx will collapse one sized idx dimensions when it
            does not match the rvalue image's size.
            """

            if isinstance(idx, str):
              if idx == 'origin':
                return self.SetOrigin(rvalue)
              elif idx == 'spacing':
                return self.SetSpacing(rvalue)
              elif idx == 'direction':
                return self.SetDirection(rvalue)
              else:
                if not isinstance(rvalue, str):
                  raise TypeError("metadata item must be a string")
                return self.SetMetaData(idx, rvalue)

            if sys.version_info[0] < 3:
              def isint( i ):
                return type(i) == int or type(i) == long
            else:
              def isint( i ):
                return type(i) == int

            dim = self.GetDimension()
            size = self.GetSize()

            try:
              len(idx)
            except TypeError as e:
              # if the len function did not work then, assume is a
              # non-iterable, and make it a single element then an ...
              if idx == Ellipsis:
                idx = (Ellipsis,)
              else:
                idx = (idx, Ellipsis)

            if len(idx) > dim + (Ellipsis in idx):
              raise IndexError("too many indices for image")
            if (len(idx) < dim) and Ellipsis not in idx:
              # if the argument tuple has fewer elements then the dimension of the image then extend to match that of the image
              idx = tuple(idx) + (Ellipsis,)

            idx = self._expand_ellipsis(idx)

            # All the indices are integers use SetPixel
            if all( isint(i) for i in idx ):
              # if any of the arguments are negative integers subract them from the size
              idx = [idx[i] if idx[i] >= 0 else (size[i] + idx[i]) for i in range(len(idx))]

              for i in range(len(idx)):
                if idx[i] < 0 or idx[i] >= size[i]:
                  raise IndexError("index {0} is outside the extent for dimension {1} with size {2}".format( idx[i], i, size[i]))

              return self.SetPixel(*(tuple(idx)+(rvalue,)))

            for i in range(len(idx)):
              if type(idx[i]) is slice:
                continue
              elif isint(idx[i]):
                s = idx[i]
                if s < 0:
                  s += size[i]
                if s < 0 or s >= size[i]:
                  raise IndexError("index {0} is outside the extent for dimension {1} with size {2}".format( idx[i], i, size[i]))

                idx = tuple(idx[:i]) + (slice(s, s+1),)+ tuple(idx[i+1:])

            if all( type(i) is slice for i in idx ):
              sidx = [ idx[i].indices(size[i]) for i in range(len(idx ))]

              (start, stop, step) = zip(*sidx)
              size = [ e-b for b, e in zip(start, stop) ]
              try:
                sourceSize = rvalue.GetSize()
              except AttributeError:
                sourceSize = size

              for i in range(dim):
                if step[i] != 1:
                  raise IndexError("step {0} is not 1 for dimension {1}".format(step[i], i))

              skipAxes = [False] * dim

              s = 0;
              for i in range(dim):

                if size[i] == 1 and (len(sourceSize) <= s or sourceSize[s] != size[i]):
                  skipAxes[i] = True
                  continue

                if len(sourceSize) <= s  or sourceSize[s] != size[i]:
                  raise IndexError("cannot paste source with size {0} into destination with size {1}".format(size, sourceSize))
                s += 1

              size = [ sz for sz,skip  in zip(size, skipAxes) if not skip ]
              return self.__ipaste( rvalue, size, [0]*len(size), start, skipAxes)

            # the index parameter was an invalid set of objects
            raise IndexError("invalid index with types: {0}".format([type(i) for i in idx]))


        def GetPixel(self, *idx):
          """Returns the value of a pixel.

             This method takes 2 parameters in 2D: the x and y index,
             and 3 parameters in 3D: the x, y and z index."""

          if len(idx) == 1:
           idx = idx[0]

          pixelID = self.GetPixelIDValue()
          if pixelID == sitkUnknown:
            raise Exception("invalid pixel type")
          if pixelID == sitkInt8:
            return self.__GetPixelAsInt8__( idx )
          if pixelID == sitkUInt8 or pixelID == sitkLabelUInt8:
            return self.__GetPixelAsUInt8__( idx )
          if pixelID == sitkInt16:
            return self.__GetPixelAsInt16__( idx )
          if pixelID == sitkUInt16 or pixelID == sitkLabelUInt16:
            return self.__GetPixelAsUInt16__( idx )
          if pixelID == sitkInt32:
            return self.__GetPixelAsInt32__( idx )
          if pixelID == sitkUInt32 or pixelID == sitkLabelUInt32:
            return self.__GetPixelAsUInt32__( idx )
          if pixelID == sitkInt64:
            return self.__GetPixelAsInt64__( idx )
          if pixelID == sitkUInt64 or pixelID == sitkLabelUInt64:
            return self.__GetPixelAsUInt64__( idx )
          if pixelID == sitkFloat32:
            return self.__GetPixelAsFloat__( idx )
          if pixelID == sitkFloat64:
            return self.__GetPixelAsDouble__( idx )

          if pixelID == sitkVectorInt8:
            return self.__GetPixelAsVectorInt8__( idx )
          if pixelID == sitkVectorUInt8:
            return self.__GetPixelAsVectorUInt8__( idx )
          if pixelID == sitkVectorInt16:
            return self.__GetPixelAsVectorInt16__( idx )
          if pixelID == sitkVectorUInt16:
            return self.__GetPixelAsVectorUInt16__( idx )
          if pixelID == sitkVectorInt32:
            return self.__GetPixelAsVectorInt32__( idx )
          if pixelID == sitkVectorUInt32:
            return self.__GetPixelAsVectorUInt32__( idx )
          if pixelID == sitkVectorInt64:
            return self.__GetPixelAsVectorInt64__( idx )
          if pixelID == sitkVectorUInt64:
            return self.__GetPixelAsVectorUInt64__( idx )
          if pixelID == sitkVectorFloat32:
            return self.__GetPixelAsVectorFloat32__( idx )
          if pixelID == sitkVectorFloat64:
            return self.__GetPixelAsVectorFloat64__( idx )

          if pixelID == sitkComplexFloat32:
            return self.__GetPixelAsComplexFloat32__( idx )
          if pixelID == sitkComplexFloat64:
            return self.__GetPixelAsComplexFloat64__( idx )

          raise Exception("unknown pixel type")

        def SetPixel(self, *args):
          """Sets the value of a pixel.

           This method takes 3 parameters in 2D: the x and y index then the value,
           and 4 parameters in 3D: the x, y and z index then the value."""


          pixelID = self.GetPixelIDValue()
          if pixelID == sitkUnknown:
            raise Exception("invalid pixel type")

          if len(args) < 2:
            raise Exception( "Wrong number of arguments, coordinates arguments then value" )
          idx = args[:len(args)-1]
          if len(idx) == 1:
            idx = idx[0]
          value = args[-1]

          if pixelID == sitkInt8:
            return self.__SetPixelAsInt8__( idx, value )
          if pixelID == sitkUInt8 or pixelID == sitkLabelUInt8:
            return self.__SetPixelAsUInt8__( idx, value )
          if pixelID == sitkInt16:
            return self.__SetPixelAsInt16__( idx, value )
          if pixelID == sitkUInt16 or pixelID == sitkLabelUInt16:
            return self.__SetPixelAsUInt16__( idx, value )
          if pixelID == sitkInt32:
            return self.__SetPixelAsInt32__( idx, value )
          if pixelID == sitkUInt32 or pixelID == sitkLabelUInt32:
            return self.__SetPixelAsUInt32__( idx, value )
          if pixelID == sitkInt64:
            return self.__SetPixelAsInt64__( idx, value )
          if pixelID == sitkUInt64 or pixelID == sitkLabelUInt64:
            return self.__SetPixelAsUInt64__( idx, value )
          if pixelID == sitkFloat32:
            return self.__SetPixelAsFloat__( idx, value )
          if pixelID == sitkFloat64:
            return self.__SetPixelAsDouble__( idx, value )

          if pixelID == sitkVectorInt8:
            return self.__SetPixelAsVectorInt8__( idx, value )
          if pixelID == sitkVectorUInt8:
            return self.__SetPixelAsVectorUInt8__( idx, value )
          if pixelID == sitkVectorInt16:
            return self.__SetPixelAsVectorInt16__( idx, value )
          if pixelID == sitkVectorUInt16:
            return self.__SetPixelAsVectorUInt16__( idx, value )
          if pixelID == sitkVectorInt32:
            return self.__SetPixelAsVectorInt32__( idx, value )
          if pixelID == sitkVectorUInt32:
            return self.__SetPixelAsVectorUInt32__( idx, value )
          if pixelID == sitkVectorInt64:
            return self.__SetPixelAsVectorInt64__( idx, value )
          if pixelID == sitkVectorUInt64:
            return self.__SetPixelAsVectorUInt64__( idx, value )
          if pixelID == sitkVectorFloat32:
            return self.__SetPixelAsVectorFloat32__( idx, value )
          if pixelID == sitkVectorFloat64:
            return self.__SetPixelAsVectorFloat64__( idx, value )

          if pixelID == sitkComplexFloat32:
            return self.__SetPixelAsComplexFloat32__( idx, value )
          if pixelID == sitkComplexFloat64:
            return self.__SetPixelAsComplexFloat64__( idx, value )

          raise Exception("unknown pixel type")


         %}



}
