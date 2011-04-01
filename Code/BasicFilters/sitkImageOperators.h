#ifndef __sitkImageOperators_h
#define __sitkImageOperators_h

#include "sitkAddImageFilter.h"
#include "sitkSubtractImageFilter.h"
#include "sitkMultiplyImageFilter.h"
#include "sitkDivideImageFilter.h"
#include "sitkMultiplyByConstantImageFilter.h"
#include "sitkAddConstantToImageFilter.h"
#include "sitkSubtractConstantFromImageFilter.h"
#include "sitkDivideByConstantImageFilter.h"
#include "sitkNotImageFilter.h"
#include "sitkAndImageFilter.h"
#include "sitkOrImageFilter.h"
#include "sitkXorImageFilter.h"

namespace itk {
namespace simple {


inline Image operator+( const Image &img1, const Image &img2 ) { return Add(img1, img2 ); }
inline Image operator-( const Image &img1, const Image &img2 ) { return Subtract(img1, img2 ); }
inline Image operator*( const Image &img1, const Image &img2 ) { return Multiply(img1, img2 ); }
inline Image operator/( const Image &img1, const Image &img2 ) { return Divide(img1, img2 ); }

inline Image operator*( const Image &img, double s  ) { return MultiplyByConstant(img, s ); }
inline Image operator*( double s,  Image &img ) { return MultiplyByConstant(img, s ); }


inline Image operator+( Image &img, double s ) { return  AddConstantTo(img, s ); }
inline Image operator+( double s,  Image &img ) { return  AddConstantTo(img, s ); }

inline Image operator-( Image &img, double s ) { return  SubtractConstantFrom(img, s ); }

inline Image operator/( Image &img, double s  ) { return DivideByConstant(img, s ); }

// Modoulo does not appear to be defined?
// Image operator%( Image &img1, Image &img2 )
// Image &operator%=( Image &img1, double s )

inline Image operator~( const Image &img ) { return Not( img ); }
inline Image operator&( const Image &img1, const Image &img2 ) { return And(img1, img2 ); }
inline Image operator|( const Image &img1, const Image &img2 ) { return Or(img1, img2 ); }
inline Image operator^( const Image &img1, const Image &img2 ) { return Xor(img1, img2 ); }

/** \todo these operators should some how be done "in-place" */
inline Image &operator+=( Image &img1, const Image &img2 ) { return img1 = Add(img1, img2 ); }
inline Image &operator+=( Image &img1, double s ) { return img1 = AddConstantTo(img1, s ); }
inline Image &operator-=( Image &img1, const Image &img2 ) { return img1 = Subtract(img1, img2 ); }
inline Image &operator-=( Image &img1, double s ) { return img1 = SubtractConstantFrom(img1, s ); }
inline Image &operator*=( Image &img1, const Image &img2 ) { return img1 = Multiply(img1, img2 ); }
inline Image &operator*=( Image &img1, double s ) { return img1 = MultiplyByConstant(img1, s ); }
inline Image &operator/=( Image &img1, const Image &img2 ) { return img1 = Divide(img1, img2 ); }
inline Image &operator/=( Image &img1, double s ) { return img1 = DivideByConstant(img1, s ); }
inline Image &operator&=( Image &img1, const Image &img2 ) { return img1 = And(img1, img2 ); }
inline Image &operator|=( Image &img1, const Image &img2 ) { return img1 = Or(img1, img2 ); }
inline Image &operator^=( Image &img1, const Image &img2 ) { return img1 = Xor(img1, img2 ); }

}
}

#endif // __sitkImageOperators_h
