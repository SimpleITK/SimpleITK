#include "SimpleITKCxx.h"

extern "C" {
  SEXP mytest(SEXP img, SEXP origin_) {
    try {
      int n = length(origin_);
      std::vector<double> origin;
      for (int i = 0; i < n; i++)
	origin.push_back(REAL(origin_)[i]);

      // ideally the package would use Rcpp (https://cran.r-project.org/package=Rcpp)
      // then it would be more elegant and efficient to use
      // std::vector<double> origin = Rcpp::as<std::vector<double> >(origin_);
      
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
