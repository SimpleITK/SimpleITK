#if SWIGPYTHON
// Make __str__ transparent by renaming ToString to __str__
%rename(__str__) ToString;

%rename( __GetPixelAsUInt8__ ) itk::simple::Image::GetPixelAsUInt8;
%rename( __GetPixelAsInt16__ ) itk::simple::Image::GetPixelAsInt16;
%rename( __GetPixelAsUInt16__ ) itk::simple::Image::GetPixelAsUInt16;
%rename( __GetPixelAsInt32__ ) itk::simple::Image::GetPixelAsInt32;
%rename( __GetPixelAsUInt32__ ) itk::simple::Image::GetPixelAsUInt32;
%rename( __GetPixelAsFloat__ ) itk::simple::Image::GetPixelAsFloat;
%rename( __GetPixelAsDouble__ ) itk::simple::Image::GetPixelAsDouble;


%extend itk::simple::Image {


//      def __floordiv__( other )
//      def __pow__( double s )
//      def __neg__( )
//      def __abs__( )
//      def __getitem( self, pos ) 
//      def __setitem( self, pos, value )

        %pythoncode %{

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

        def __iadd__ ( self, other ):
            self = Add( self, other )
            return self;

        def __and__( self, other ): return And( self, other )
        def __or__( self, other ): return Or( self, other )
        def __xor__( self, other ): return Xor( self, other )
        def __invert__( self ): return Not( self )

        def GetPixel(self, x, y, z ):
            pixelID = self.GetPixelIDValue()
            if pixelID == sitkUnknown:
               raise Exception("Logic Error: invalid pixel type")
            if pixelID == sitkUInt8 || pixelID == sitkLabelUInt8:
               return self.__GetPixelAsUInt8__( [ x, y, z ] )
            if pixelID == sitkInt16:
               return self.__GetPixelAsInt16__( [ x, y, z ] )
            if pixelID == sitkUInt16 || pixelID == sitkLabelUInt16:
               return self.__GetPixelAsUInt16__( [ x, y, z ] )
            if pixelID == sitkInt32:
               return self.__GetPixelAsInt32__( [ x, y, z ] )
            if pixelID == sitkUInt32 || pixelID == sitkLabelUInt32:
               return self.__GetPixelAsUInt32__( [ x, y, z ] )
            if pixelID == sitkFloat32:
               return self.__GetPixelAsFloat__( [ x, y, z ] )
            if pixelID == sitkFloat64:
               return self.__GetPixelAsDouble__( [ x, y, z ] )

            raise Exception("Unknown pixel type")


        def GetPixel(self, x, y):
            pixelID = self.GetPixelIDValue()
            if pixelID == sitkUnknown:
               raise Exception("Logic Error: invalid pixel type")
            if pixelID == sitkUInt8 || pixelID == sitkLabelUInt8:
               return self.__GetPixelAsUInt8__( [ x, y ] )
            if pixelID == sitkInt16:
               return self.__GetPixelAsInt16__( [ x, y ] )
            if pixelID == sitkUInt16 || pixelID == sitkLabelUInt16:
               return self.__GetPixelAsUInt16__( [ x, y ] )
            if pixelID == sitkInt32:
               return self.__GetPixelAsInt32__( [ x, y ] )
            if pixelID == sitkUInt32 || pixelID == sitkLabelUInt32:
               return self.__GetPixelAsUInt32__( [ x, y ] )
            if pixelID == sitkFloat32:
               return self.__GetPixelAsFloat__( [ x, y ] )
            if pixelID == sitkFloat64:
               return self.__GetPixelAsDouble__( [ x, y ] )

            raise Exception("Unknown pixel type")

         %}



};


#endif
