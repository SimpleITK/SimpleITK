

import SimpleITK
import sys

if len ( sys.argv ) < 4:
    print "Usage: MathematicalMorphology <input> <operation> <output>";
    print "operation: 0=binary erode, 1=binary dilate, 2=grayscale erode, 3=grayscale dilate";
    sys.exit ( 1 )

reader = SimpleITK.ImageFileReader()
reader.SetFileName ( sys.argv[1] )
image = reader.Execute();

print image.ToString()

morphoMath = SimpleITK.MathematicalMorphologyImageFilter()
morphoMath.SetOperation ( int ( sys.argv[2] ) )
image = morphoMath.Execute ( image );

print image.ToString()

writer = SimpleITK.ImageFileWriter()
writer.SetFileName ( sys.argv[3] )
writer.Execute ( image );

