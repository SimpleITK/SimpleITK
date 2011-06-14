#if SWIGPYTHON
%include "PythonDocstrings.i"
// Make __str__ transparent by renaming ToString to __str__
%rename(__str__) ToString;

%rename( __GetPixelAsUInt8__ ) itk::simple::Image::GetPixelAsUInt8;
%rename( __GetPixelAsInt16__ ) itk::simple::Image::GetPixelAsInt16;
%rename( __GetPixelAsUInt16__ ) itk::simple::Image::GetPixelAsUInt16;
%rename( __GetPixelAsInt32__ ) itk::simple::Image::GetPixelAsInt32;
%rename( __GetPixelAsUInt32__ ) itk::simple::Image::GetPixelAsUInt32;
%rename( __GetPixelAsFloat__ ) itk::simple::Image::GetPixelAsFloat;
%rename( __GetPixelAsDouble__ ) itk::simple::Image::GetPixelAsDouble;


%rename( __SetPixelAsUInt8__ ) itk::simple::Image::SetPixelAsUInt8;
%rename( __SetPixelAsInt16__ ) itk::simple::Image::SetPixelAsInt16;
%rename( __SetPixelAsUInt16__ ) itk::simple::Image::SetPixelAsUInt16;
%rename( __SetPixelAsInt32__ ) itk::simple::Image::SetPixelAsInt32;
%rename( __SetPixelAsUInt32__ ) itk::simple::Image::SetPixelAsUInt32;
%rename( __SetPixelAsFloat__ ) itk::simple::Image::SetPixelAsFloat;
%rename( __SetPixelAsDouble__ ) itk::simple::Image::SetPixelAsDouble;

%pythoncode %{
   import operator
%}

%extend itk::simple::Image {


//      def __floordiv__( other )
//      def __pow__( double s )
//      def __neg__( )
//      def __abs__( )


        %pythoncode %{

        # mathematical operators

        def __add__( self, other ):
            if isinstance( other, Image ):
               return Add( self, other )
            return AddConstantTo( self, other )
        def __sub__( self, other ):
            if isinstance( other, Image ):
               return Subtract( self, other )
            return SubtractConstantFrom( self, other )
        def __mul__( self, other ):
            if isinstance( other, Image ):
               return Multiply( self, other )
            return MultiplyByConstant( self, other )
        def __div__( self, other ):
            if isinstance( other, Image ):
               return Divide( self, other )
            return DivideByConstant( self, other )

        def __radd__( self, other ):
            return self.__add__( other )
        def __rsub__( self, other ):
            return self.__sub__( other )
        def __rmul__( self, other ):
            return self.__mul__( other )
        def __rdiv__( self, other ):
            return self.__div__( other )

         # NOTE: the __i*__ methods are not implemented because there
         # currently in no way to make the underlying filters run
         # inplace". But python will implement a default version based
         # on the standard method
        def __iadd__ ( self, other ):
            self = Add( self, other )
            return self;

        # logic operators

        def __and__( self, other ): return And( self, other )
        def __or__( self, other ): return Or( self, other )
        def __xor__( self, other ): return Xor( self, other )
        def __invert__( self ): return Not( self )

        # iterator and container methods

        def __iter__( self ):
            self.iter_index = [0] * self.GetDimension()
            return self

        def next( self ):
            old_index = tuple( self.iter_index )

            dim = self.GetDimension()

            if self.iter_index[dim-1] >= self.GetSize()[dim-1]:
               raise StopIteration

            # increment the idx
            for d in range( 0, dim ):
                self.iter_index[d] += 1
                if self.iter_index[d] >= self.GetSize()[d] and d != dim  - 1:
                   self.iter_index[d] = 0
                else:
                   break

            return self[ old_index ]

        def __len__( self ):
            return reduce( operator.mul, self.GetSize(), 1 )

        # set/get pixel methods

        def __getitem__( self, idx ):
            """Returns the value of pixel at index idx.

            The dimension of idx should match that of the image."""
            pixelID = self.GetPixelIDValue()
            if pixelID == sitkUnknown:
               raise Exception("Logic Error: invalid pixel type")
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
            if pixelID == sitkFloat32:
               return self.__GetPixelAsFloat__( idx )
            if pixelID == sitkFloat64:
               return self.__GetPixelAsDouble__( idx )
            raise Exception("Unknown pixel type")


        def __setitem__( self, idx, value ):
            """Sets the pixel value at index idx to value.

            The dimension of idx should match that of the image."""
            pixelID = self.GetPixelIDValue()
            if pixelID == sitkUnknown:
               raise Exception("Logic Error: invalid pixel type")
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
            if pixelID == sitkFloat32:
               return self.__SetPixelAsFloat__( idx, value )
            if pixelID == sitkFloat64:
               return self.__SetPixelAsDouble__( idx, value )
            raise Exception("Unknown pixel type")

        def GetPixel(self, *idx):
             """Returns the value of a pixel.

	     This method takes 2 parameters in 2D: the x and y index,
             and 3 parameters in 3D: the x, y and z index."""
             return self[idx]

        def SetPixel(self, *args):
             """Sets the value of a pixel.

	     This method takes 3 parameters in 2D: the x and y index then the value,
             and 4 parameters in 3D: the x, y and z index then the value."""
             if len(args) < 2:
                raise Exception( "Wrong number of arguments, coordinates arguments then value" )
             idx = args[:len(args)-1]
             value = args[-1]
             self[idx] = value


         %}



}


#endif
