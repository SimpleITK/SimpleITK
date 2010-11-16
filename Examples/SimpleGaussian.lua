

print ( #arg )

if #arg < 3 then
  print ( "Usage: SimpleGaussian <input> <sigma> <output>" )
  os.exit ( 1 )
end

reader = SimpleITK.ImageFileReader()
-- Remember that Lua arrays are 1-based, and that arg does not contain the application name!
reader:SetFilename ( arg[1] )
image = reader:Execute();
  
print ( image:ToString() )

gaussian = SimpleITK.RecursiveGaussianImageFilter()
gaussian:SetSigma ( arg[2] )
image = gaussian:Execute ( image );

print ( 'Finished filtering' )
print ( image:ToString() )

writer = SimpleITK.ImageFileWriter()
writer:SetFilename ( arg[3] )
writer:Execute ( image );

