

import SimpleITK
import sys

if len ( sys.argv ) < 4:
    print "Usage: SimpleGaussian <input> <sigma> <output>";
    sys.exit ( 1 )

reader = SimpleITK.ImageFileReader()
reader.setFilename ( sys.argv[1] )
image = reader.execute();
  
print image.toString()

gaussian = SimpleITK.Gaussian()
gaussian.setSigma ( float ( sys.argv[2] ) )
image = gaussian.execute ( image );

print image.toString()

writer = SimpleITK.ImageFileWriter()
writer.setFilename ( sys.argv[3] )
writer.execute ( image );

