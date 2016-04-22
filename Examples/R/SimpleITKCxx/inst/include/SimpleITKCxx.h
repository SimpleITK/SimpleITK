#ifndef _RcppSimpleITK_H__
#define _RcppSimpleITK_H__
#include "R.h"
#include "Rdefines.h"
#include "SimpleITK.h"

namespace sitk = itk::simple;
//using namespace Rcpp;
extern "C" {
extern itk::simple::Image * convertSwigSimpleITKImage( SEXP obj );
}

#endif
