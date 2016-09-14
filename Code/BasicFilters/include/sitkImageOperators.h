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
#ifndef sitkImageOperators_h
#define sitkImageOperators_h

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

namespace itk {
namespace simple {

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
inline Image operator*( const Image &img, double s  ) { return Multiply(img, s ); }
inline Image operator*( double s,  const Image &img ) { return Multiply(s, img ); }
inline Image operator/( const Image &img1, const Image &img2 ) { return Divide(img1, img2 ); }
inline Image operator/( const Image &img, double s  ) { return Divide(img, s ); }
inline Image operator/( double s,  const Image &img  ) { return Divide(s, img ); }
inline Image operator%( const Image &img1, const Image &img2 ) { return Modulus(img1, img2 ); }
inline Image operator%( const Image &img, uint32_t s  ) { return Modulus(img, s ); }
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
inline Image operator*=( Image &img1, double s ) { return img1 = Multiply(img1, s ); }
inline Image operator/=( Image &img1, const Image &img2 ) { return img1 = Divide(img1, img2 ); }
inline Image operator/=( Image &img1, double s ) { return img1 = Divide(img1, s ); }
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

#endif // sitkImageOperators_h
