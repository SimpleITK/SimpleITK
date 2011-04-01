#if SWIGPYTHON
// Make __str__ transparent by renaming ToString to __str__
%rename(__str__) ToString;


%extend itk::simple::Image {

//      def __floordiv__( other )
//      def __pow__( double s )
//      def __neg__( )
//      def __abs__( )
//      def __getitem( self, pos ) 
//      def __setitem( self, pos, value )

        %pythoncode %{

        def __add__( self, other ):
            if isinstante( other, self ):
               return Add( self, other )
            return AddConstantTo( self, other )
        def __sub__( self, other ):
            if isinstante( other, self ):
               return Subtract( self, other )
            return SubtractConstantFrom( self, other )
        def __mul__( self, other ):
            if isinstante( other, self ):
               return Multiply( self, other )
            return MultiplyByConstant( self, other )
        def __div__( self, other ):
            if isinstante( other, self ):
               return Divide( self, other )
            return DivideByConstant( self, s )

        def __iadd__ ( self, other ):
            self = Add( self, other )
            return self;

        def __and__( self, other ): return And( self, other )
        def __or__( self, other ): return Or( self, other )
        def __xor__( self, other ): return Xor( self, other )
        def __invert__( self ): return Not( self )

        %}

       
};


#endif
