
HAVE_NUMPY = True
try:
    import numpy
except ImportError:
    HAVE_NUMPY = False

# SimplyITK <-> Numpy Array conversion support.

def GetArrayFromImage(image):
    """Get a numpy array from a SimpleITK Image."""

    if not HAVE_NUMPY:
        raise ImportError('Numpy not available.')

    imageByteArray, shape, pixelID = _SimpleITK.GetArrayFromImage(image)
    if pixelID == 0:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.uint8)
    elif pixelID == 1:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.int8)
    elif pixelID == 2:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.uint16)
    elif pixelID == 3:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.int16)
    elif pixelID == 4:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.uint32)
    elif pixelID == 5:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.int32)
    elif pixelID == 6:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.uint64)
    elif pixelID == 7:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.int64)
    elif pixelID == 8:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.float32)
    elif pixelID == 9:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.float64)
    elif pixelID == 10:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.complex64)
    elif pixelID == 11:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.complex128)

    arr.shape = shape

    return arr

def GetImageFromArray( arr ):
    """Get a SimpleITK Image from a numpy array."""

    return _SimpleITK.GetImageFromArray( arr )
