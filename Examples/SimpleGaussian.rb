require 'simpleitk'

if ARGV.length != 3 then
  puts "Usage: SimpleGaussian <input> <sigma> <output>";
  exit( 1 )
end

reader = Simpleitk::ImageFileReader.new
reader.set_file_name( ARGV[0] )
image = reader.execute
  
puts image.to_string

gaussian = Simpleitk::RecursiveGaussianImageFilter.new
gaussian.set_sigma ARGV[1].to_f
image = gaussian.execute image;

puts image.to_string

writer = Simpleitk::ImageFileWriter.new
writer.set_file_name ARGV[2] 
writer.execute image

