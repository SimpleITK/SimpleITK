
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
    if pixelID == sitkUInt8:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.uint8)
    elif pixelID == sitkInt8:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.int8)
    elif pixelID == sitkUInt16:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.uint16)
    elif pixelID == sitkInt16:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.int16)
    elif pixelID == sitkUInt32:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.uint32)
    elif pixelID == sitkInt32:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.int32)
    elif pixelID == sitkUInt64:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.uint64)
    elif pixelID == sitkInt64:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.int64)
    elif pixelID == sitkFloat32:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.float32)
    elif pixelID == sitkFloat64:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.float64)
    elif pixelID == sitkComplexFloat32:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.complex64)
    elif pixelID == sitkComplexFloat64:
        arr = numpy.frombuffer(imageByteArray, dtype=numpy.complex128)

    arr.shape = shape

    return arr

def GetImageFromArray( arr ):
    """Get a SimpleITK Image from a numpy array."""

    return _SimpleITK.GetImageFromArray( arr )
