
import SimpleITK as sitk
import sys

if len ( sys.argv ) < 4:
    print "Usage: SimpleGaussian <input> <sigma> <output>";
    sys.exit ( 1 )


reader = sitk.ImageFileReader()
reader.SetFileName ( sys.argv[1] )
image = reader.Execute()

pixelID = image.GetPixelIDValue()

gaussian = sitk.SmoothingRecursiveGaussianImageFilter()
gaussian.SetSigma ( float ( sys.argv[2] ) )
image = gaussian.Execute ( image )

caster = sitk.CastImageFilter()
caster.SetOutputPixelType( pixelID )
image = caster.Execute( image )

writer = sitk.ImageFileWriter()
writer.SetFileName ( sys.argv[3] )
writer.Execute ( image );
