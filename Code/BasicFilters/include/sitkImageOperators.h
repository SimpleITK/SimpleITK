/*=========================================================================
*
*  Copyright Insight Software Consortium
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/
#ifndef __sitkImageOperators_h
#define __sitkImageOperators_h

#include "sitkAddImageFilter.h"
#include "sitkSubtractImageFilter.h"
#include "sitkMultiplyImageFilter.h"
#include "sitkDivideImageFilter.h"
#include "sitkModulusImageFilter.h"
#include "sitkUnaryMinusImageFilter.h"
#include "sitkBitwiseNotImageFilter.h"
#include "sitkAndImageFilter.h"
#include "sitkOrImageFilter.h"
#include "sitkXorImageFilter.h"

#include <algorithm>

namespace itk {
namespace simple {

    /*
     *   This family of math operators are designed to provide a more feature rich
     *   math interface for simple ITK.  Inspired by the math operations in
     *   matlab, and as a mechanism to facilitate migration of matlab code to
     *   SimpleITK as a means to provide a lower barrier translation of
     *   prototyping code into production code.
     *
     *   These adapters allow vector images to be processed in a way that
     *   would be natural to matlab/octave users.
     *
     *   VectorImage vi([2,2], sitk::sitkVectorFloat32, 7);
     *   double scaler = 7
     *
     *   vi = vi ./ scalar
     *   vi = vi .* scalar
     *   vi = scaler .* vi
     *   vi = scalar ./ vi
     *
     *   Note that addition and subtraction of vector images is already working properly
     */
#define DO_VECTOR_MATH_OP(PIXEL_TYPE,TYPE_NAME, OPERATIONCODE)                        \
    {                                                                                 \
    out = Image(img1);                                                                \
    const size_t N = out.GetNumberOfPixels() * out.GetNumberOfComponentsPerPixel();   \
    PIXEL_TYPE * iter = out.GetBufferAs##TYPE_NAME();                                 \
    const PIXEL_TYPE * const end = iter+N;                                            \
    /* std::for_each( start, start+N, [&s](PIXEL_TYPE & x) { OPERATION ;}); */        \
    while(iter < end)                                                                 \
      {                                                                               \
       PIXEL_TYPE &x = *iter;                                                         \
       OPERATIONCODE;                                                                 \
       ++iter;                                                                        \
      }                                                                               \
    }

#define DoFloatMathVectorPixelTypes( OPERATIONCODE )                   \
case itk::simple::sitkVectorFloat32:                                   \
  DO_VECTOR_MATH_OP(float, Float, OPERATIONCODE );                     \
  break;                                                               \
case itk::simple::sitkVectorFloat64:                                   \
  DO_VECTOR_MATH_OP(double, Double, OPERATIONCODE );                   \
  break                                                               \

#define DoIntegerMathVectorPixelTypes( OPERATIONCODE )                 \
case itk::simple::sitkVectorInt8:                                      \
  DO_VECTOR_MATH_OP(int8_t, Int8, OPERATIONCODE );                     \
  break;                                                               \
case itk::simple::sitkVectorInt16:                                     \
  DO_VECTOR_MATH_OP(int16_t, Int16, OPERATIONCODE );                   \
  break;                                                               \
case itk::simple::sitkVectorInt32:                                     \
  DO_VECTOR_MATH_OP(int32_t, Int32, OPERATIONCODE );                   \
  break;                                                               \
case itk::simple::sitkVectorInt64:                                     \
  DO_VECTOR_MATH_OP(int64_t, Int64, OPERATIONCODE );                   \
  break;                                                               \
case itk::simple::sitkVectorUInt8:                                     \
  DO_VECTOR_MATH_OP(uint8_t, UInt8, OPERATIONCODE );                   \
  break;                                                               \
case itk::simple::sitkVectorUInt16:                                    \
  DO_VECTOR_MATH_OP(uint16_t, UInt16, OPERATIONCODE );                 \
  break;                                                               \
case itk::simple::sitkVectorUInt32:                                    \
  DO_VECTOR_MATH_OP(uint32_t, UInt32, OPERATIONCODE );                 \
  break;                                                               \
case itk::simple::sitkVectorUInt64:                                    \
  DO_VECTOR_MATH_OP(uint64_t, UInt64, OPERATIONCODE );                 \
  break

#define DoAllMathVectorPixelTypes( OPERATIONCODE )                     \
        DoFloatMathVectorPixelTypes( OPERATIONCODE );                  \
        DoIntegerMathVectorPixelTypes( OPERATIONCODE )



//HACK:  This is needed to provide scaler by vector math operations
// Similar to matlab "dot operator" functionality
// new3DMatrix = my3DMatrix .* s
inline void MultiplyImageAdaptor(Image &out, const Image &img1, const double s) {
  // img1.MakeUnique();
  if (out.GetITKBase() != img1.GetITKBase()) //If they are not same image, then Deep copy first.
  {
    out = Image(img1);
  }
  switch (img1.GetPixelID()) {
    DoAllMathVectorPixelTypes(x *= s);
    default: //Scalar images need no special treatment
      out = Multiply(img1, s);
  }
}

inline void DivideImageAdaptor(Image &out, const double s, const Image &img1) {
  //TODO: Do we need to be concerned with copy-on-write behavior?  Is the the correct way to do it?
  // img1.MakeUnique();
  if (out.GetITKBase() != img1.GetITKBase()) //If they are not same image, then Deep copy first.
  {
    out = Image(img1);
  }
  switch (img1.GetPixelID()) {
    DoAllMathVectorPixelTypes(x = s / static_cast<double>(x));
    default:
      out = Divide(s, img1);
  }
}

inline void DivideImageAdaptor(Image &out, const Image &img1, const double s) {
  const double inverse_s = 1.0 / s;
  MultiplyImageAdaptor(out, img1, inverse_s);
}

inline void MultiplyImageAdaptor(Image &out, const double s, const Image &img1) {
  MultiplyImageAdaptor(out, img1, s);
}

inline void ModuloImageAdaptor(Image &out, const Image &img1, const uint32_t s) {
  // img1.MakeUnique();
  if (out.GetITKBase() != img1.GetITKBase()) //If they are not same image, then Deep copy first.
  {
    out = Image(img1);
  }
  switch (img1.GetPixelID()) {
    DoIntegerMathVectorPixelTypes(x %= s);
    default: //Scalar images need no special treatment
      out = Modulus(img1, s);
  }
}

inline void ModuloImageAdaptor(Image &out, const uint32_t s, const Image &img1) {
  //img1.MakeUnique();
  if (out.GetITKBase() != img1.GetITKBase()) //If they are not same image, then Deep copy first.
  {
    out = Image(img1);
  }
  switch (img1.GetPixelID()) {
    DoIntegerMathVectorPixelTypes(x = s % x);
    default: //Scalar images need no special treatment
      out = Modulus(s, img1);
  }
}

#undef DoAllMathVectorPixelTypes
#undef DO_VECTOR_MATH_OP


/**
* \brief Performs the operator on a per pixel basis.
*
* All overloaded simpleITK operators are performed on a per-pixel
* basis, and implemented with the coresponding image filters. These
* operators gernerally don't work with label images, and the logical
* operators don't work with images of real components or vector images.
* @{
*/
inline Image operator+( const Image &img1, const Image &img2 ) { return Add(img1, img2 ); }
inline Image operator+( const Image &img, double s ) { return  Add(img, s ); }
inline Image operator+( double s,  const Image &img ) { return  Add(s, img ); }
inline Image operator-( const Image &img1, const Image &img2 ) { return Subtract(img1, img2 ); }
inline Image operator-( const Image &img, double s ) { return  Subtract(img, s ); }
inline Image operator-(double s, const Image &img ) { return  Subtract(s, img ); }
inline Image operator*( const Image &img1, const Image &img2 ) { return Multiply(img1, img2 ); }
inline Image operator*( const Image &img, double s  ) { Image out; MultiplyImageAdaptor(out, img, s ); return out; }
inline Image operator*( double s,  const Image &img ) { Image out; MultiplyImageAdaptor(out, s, img ); return out; }
inline Image operator/( const Image &img1, const Image &img2 ) { return Divide(img1, img2 ); }
inline Image operator/( const Image &img, double s  ) { Image out;  DivideImageAdaptor(out, img, s ); return out; }
inline Image operator/( double s,  const Image &img  ) { Image out; DivideImageAdaptor(out, s, img ); return out; }
inline Image operator%( const Image &img1, const Image &img2 ) { return Modulus(img1, img2 ); }
inline Image operator%( const Image &img, uint32_t s  ) { return Modulus(img, s ); }  //TODO: Later
inline Image operator%( uint32_t s,  const Image &img  ) { return Modulus(s, img ); }


// Modoulo does not appear to be defined?
// Image operator%( Image &img1, Image &img2 )
// Image &operator%=( Image &img1, double s )

inline Image operator-( const Image &img ) { return UnaryMinus( img ); }

inline Image operator~( const Image &img ) { return BitwiseNot( img ); }
inline Image operator&( const Image &img1, const Image &img2 ) { return And(img1, img2 ); }
inline Image operator&( const Image &img,  int s ) { return And(img, s ); }
inline Image operator&( int s, const Image &img ) { return And(s, img ); }
inline Image operator|( const Image &img1, const Image &img2 ) { return Or(img1, img2 ); }
inline Image operator|( const Image &img, int s ) { return Or(img, s ); }
inline Image operator|( int s, const Image &img ) { return Or(s, img ); }
inline Image operator^( const Image &img1, const Image &img2 ) { return Xor(img1, img2 ); }
inline Image operator^( const Image &img, int s ) { return Xor(img, s ); }
inline Image operator^( int s, const Image &img ) { return Xor(s, img ); }

/** \todo these operators should some how be done "in-place" */
inline Image operator+=( Image &img1, const Image &img2 ) { return img1 = Add(img1, img2 ); }
inline Image operator+=( Image &img1, double s ) { return img1 = Add(img1, s ); }
inline Image operator-=( Image &img1, const Image &img2 ) { return img1 = Subtract(img1, img2 ); }
inline Image operator-=( Image &img1, double s ) { return img1 = Subtract(img1, s ); }
inline Image operator*=( Image &img1, const Image &img2 ) { return img1 = Multiply(img1, img2 ); }
inline Image operator*=( Image &img1, double s ) {  MultiplyImageAdaptor(img1, img1, s ); return img1; }
inline Image operator/=( Image &img1, const Image &img2 ) { return img1 = Divide(img1, img2 ); }
inline Image operator/=( Image &img1, double s ) { DivideImageAdaptor(img1, img1, s ); return img1;}
inline Image operator%=( Image &img1, const Image &img2 ) { return img1 = Modulus(img1, img2 ); }
inline Image operator%=( Image &img1, uint32_t s ) { return img1 = Modulus(img1, s ); }
inline Image operator&=( Image &img1, const Image &img2 ) { return img1 = And(img1, img2 ); }
inline Image operator&=( Image &img1, int s ) { return img1 = And(img1, s ); }
inline Image operator|=( Image &img1, const Image &img2 ) { return img1 = Or(img1, img2 ); }
inline Image operator|=( Image &img1, int s ) { return img1 = Or(img1, s ); }
inline Image operator^=( Image &img1, const Image &img2 ) { return img1 = Xor(img1, img2 ); }
inline Image operator^=( Image &img1, int s ) { return img1 = Xor(img1, s ); }
/**@} */
}
}

#endif // __sitkImageOperators_h
