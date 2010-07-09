

print ( #arg )

if #arg < 3 then
  print ( "Usage: SimpleGaussian <input> <sigma> <output>" )
  os.exit ( 1 )
end

reader = SimpleITK.ImageFileReader()
-- Remember that Lua arrays are 1-based, and that arg does not contain the application name!
reader:setFilename ( arg[1] )
image = reader:execute();
  
print ( image:toString() )

gaussian = SimpleITK.Gaussian()
gaussian:setSigma ( arg[2] )
image = gaussian:execute ( image );

print ( image:toString() )

writer = SimpleITK.ImageFileWriter()
writer:setFilename ( arg[3] )
writer:execute ( image );

