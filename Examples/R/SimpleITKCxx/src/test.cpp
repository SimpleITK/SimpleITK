#include "RcppSimpleITK.h"

RcppExport  SEXP mytest(SEXP img, SEXP origin_) {
  try {
    //convert SEXP vector to std::vector<double> using Rcpp::wrap
    std::vector<double> origin = as<std::vector<double> >(origin_);
    //unwrap SEXP object containing pointer to sitk::Image
    sitk::Image * image = convertSwigSimpleITKImage(img);
    image->SetOrigin(origin);
    //return image
    return img;
  } catch (std::exception& e) {
    ::Rf_error( e.what());
  } catch (...) {
    ::Rf_error("unknown exception");
  }
}


