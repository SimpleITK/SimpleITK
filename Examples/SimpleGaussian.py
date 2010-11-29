

import SimpleITK
import sys

if len ( sys.argv ) < 4:
    print "Usage: SimpleGaussian <input> <sigma> <output>";
    sys.exit ( 1 )

reader = SimpleITK.ImageFileReader()
reader.SetFilename ( sys.argv[1] )
image = reader.Execute();
  
print image.ToString()

gaussian = SimpleITK.RecursiveGaussianImageFilter()
gaussian.SetSigma ( float ( sys.argv[2] ) )
image = gaussian.Execute ( image );

print image.ToString()

writer = SimpleITK.ImageFileWriter()
writer.SetFilename ( sys.argv[3] )
writer.Execute ( image );

