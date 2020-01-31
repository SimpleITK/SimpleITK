// This one header will include all SimpleITK filters and external objects.
#include <SimpleITK.h>
#include <sitkImageOperators.h>

// create convenient namespace alias
namespace sitk = itk::simple;

int main ( int argc, char* argv[] ) {

    sitk::PixelIDValueEnum pixelType = sitk::sitkUInt8;
    std::vector<unsigned int> imageSize ( 2, 128 );

    // Create a black image
    sitk::Image image( imageSize, pixelType );

    // Add a Gaussian blob to the image
    std::vector<double> blobSize ( 2, 64.0 );
    std::vector<double> blobCenter ( 2, 64.0 );
    image = image + sitk::GaussianSource( pixelType, imageSize, blobSize, blobCenter );

    // Write the image as a PNG file
    sitk::WriteImage(image, "blob.png" );

}
