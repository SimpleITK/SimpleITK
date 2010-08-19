/**
 * Debugging test application
 */

#include <iostream>

#include <itkImage.h>

#include "simpleExplicitInstantiations.cxx"
#include "SimpleITKMacro.h"
#include "simpleImage.cxx"

int main() {
  
  //
  // create a test itk image
  //
  typedef itk::Image<int,3> ITKImageType;
  typedef ITKImageType::RegionType RegionType;
  typedef ITKImageType::SizeType SizeType;
  typedef ITKImageType::IndexType IndexType;
  
  
  SizeType sz;
  sz[0] = 10;
  sz[1] = 11;
  sz[2] = 12;
  IndexType idx;
  idx[0] = 0;
  idx[1] = 0;
  idx[2] = 0;
  RegionType region;
  region.SetSize(sz);
  region.SetIndex(idx);
  
  ITKImageType::Pointer itkIm = ITKImageType::New();
  itkIm->SetLargestPossibleRegion(region);
  itkIm->SetBufferedRegion(region);
  itkIm->Allocate();
  
  // set one pixel
  IndexType pxIdx;
  pxIdx[0] = 2;
  pxIdx[1] = 3;
  pxIdx[2] = 4;
  itkIm->SetPixel(pxIdx, 5);
  
  // print out pixel contents
  int itkVal1 = itkIm->GetPixel(idx);
  int itkVal2 = itkIm->GetPixel(pxIdx);
  std::cout << "itkIm(0,0,0) = " << itkVal1 << " itkIm(2,3,4) = " << itkVal2 << std::endl;
  
  
  //
  // Try converting 
  //
  typedef itk::simple::Image SimpleImageType;
  SimpleImageType::Pointer simpleIm = new SimpleImageType(itkIm, itk::simple::sitkFloat32);
  
  // print out pixel contents
  float val1;
  float val2;
  simpleIm->getPixel(0,0,0, &val1);
  simpleIm->getPixel(2,3,4, &val2);
  std::cout << "simpleIm(0,0,0) = " << val1 << " simpleIm(2,3,4) = " << val2 << std::endl;
  
}
