

# SimplyITK <-> Numpy Array conversion support.

def GetArrayFromImage( image ):
    """Get a numpy array from a SimpleITK Image."""

    return _SimpleITK.GetArrayFromImage( image )

def GetImageFromArray( arr ):
    """Get a SimpleITK Image from a numpy array."""

    return _SimpleITK.GetImageFromArray( arr )
