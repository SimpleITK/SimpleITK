#include "SimpleITKCxx.h"

extern "C" {
  SEXP mytest(SEXP img, SEXP origin_) {
    try {
    
      int n = length(origin_);
      std::vector<double> origin;
      for (int i = 0; i < n; i++)
	origin.push_back(REAL(origin_)[i]);
      sitk::Image * image = convertSwigSimpleITKImage(img);
      image->SetOrigin(origin);
      return img;
    } catch (std::exception& e) {
      ::Rf_error( e.what());
    } catch (...) {
      ::Rf_error("unknown exception");
    }
  }
}
