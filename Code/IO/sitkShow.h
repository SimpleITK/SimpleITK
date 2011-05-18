#ifndef __sitkShow_h
#define __sitkShow_h


#include "sitkImage.h"

namespace itk
{
namespace simple
{

  /** Display an image using ImageJ
   *
   *  This function requires that ImageJ
   *  (\see http://rsb.info.nih.gov/ij/) be properly installed for Mac
   *  and Windows, and in the user's path for Linux.  ImageJ must have
   *  a plugin for reading Nifti formatted files (\see
   *  http://www.loci.wisc.edu/bio-formats/imagej)
   **/
  void Show ( const Image &image, const std::string title = "" );
}
}

#endif
