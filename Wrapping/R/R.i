 // R specific swig components
#if SWIGR

// ignore overload methods of int type when there is an enum
%ignore itk::simple::CastImageFilter::SetOutputPixelType( PixelIDValueType pixelID );
%ignore itk::simple::GetPixelIDValueAsString( PixelIDValueType type );

#define SITK_RETURN_SELF_TYPE_HEADER void

%include <std_vector.i>
// we don't want a class assigned to unsigned char
%typemap(scoerceout) unsigned char,
   unsigned char *,
   unsigned char &
   %{    %}

// The swig bindings catch C++ exceptions and turn them into
// R warnings, including the relevant message.
// It is probably going to be hard/dangerous to
// fiddle with the c++ layer to change these warnings
// to errors. Other types of exception, such as
// failures in tests of input arguments, do get
// translated to R errors. Here we will test
// for the NA value and raise an error at the R
// level
%typemap(scoerceout) SWIGTYPE &, SWIGTYPE &&, SWIGTYPE *, SWIGTYPE *const
%{
  if (inherits($result, 'externalptr')) {
   $result <- new("$R_class", ref=$result);
} else {
   stop("Exception in SITK - check warning messages\n")
}
%}
%typemap(scoerceout) SWIGTYPE
%{
  if (inherits($result, 'externalptr')) {
   $result <- new("$&R_class", ref=$result);
} else {
   stop("Exception in SITK - check warning messages\n")
}
%}

// itk::Simple::Image should always have a finalizer attached in R
// simpleitk deals with reference counting.
%typemap (ret) itk::simple::Image, itk::simple::Image &, itk::simple::Image &&, itk::simple::Image *, itk::simple::Image *const
%{
  R_RegisterCFinalizerEx(r_ans, delete_Image_void, TRUE);
%}


// same thing for transforms
%typemap (ret) itk::simple::Transform, itk::simple::Transform &, itk::simple::Transform &&, itk::simple::Transform *, itk::simple::Transform *const
%{
  /* return typemap here - Image ref/pointer */
  R_RegisterCFinalizerEx(r_ans, delete_Transform_void, TRUE);
%}


// SEXP numeric typemap for array/image converion - SEXP are
// arrays here
%typemap("rtype") SEXP "numeric";

// Gets rid of the class check for unsigned char function arguments
%typemap("rtype") unsigned char, unsigned char *, unsigned char & "integer";
// and for unsigned int vectors, and various pixel types that can be automatically
// converted to R vectors. Otherwise the conversion happens in the C code and
// the wrong class gets assigned on output
%typemap("rtype") std::vector<unsigned int>, std::vector<unsigned int> *, std::vector<unsigned int> & "integer";
%typemap("rtype") std::vector<int32_t>, std::vector<int32_t> *, std::vector<int32_t> & "integer";
%typemap("rtype") std::vector<uint32_t>, std::vector<uint32_t> *, std::vector<uint32_t> & "integer";
%typemap("rtype") std::vector<double>, std::vector<double> *, std::vector<double> & "numeric";

// stop classes being asigned as these are already converted to R vectors.
%typemap(scoerceout) std::vector<int32_t>, std::vector<int32_t> *, std::vector<int32_t> &,
std::vector<float>, std::vector<float> *, std::vector<float> &
%{    %}

%apply std::vector< std::basic_string<char> > { std::vector< std::string> & };

// Experiments on lists/vectors of images
// it would be nice to generalise this to vectors of SWIG_TYPE
// Are there use cases beyond vectors of images - e.g. vectors of filters?
%typemap("rtype") std::vector<itk::simple::Image>, std::vector<itk::simple::Image>& "list";
%typemap("rtypecheck") std::vector<itk::simple::Image>, std::vector<itk::simple::Image>&
%{
  (is.list($arg) & all(sapply($arg, inherits, what='_p_itk__simple__Image')))
%}
%typemap("scoercein") std::vector<itk::simple::Image>, std::vector<itk::simple::Image>&
%{
  $input=ImListToVec($input);
  $input=slot($input, "ref")
%}

%typemap("scoerceout") std::vector<itk::simple::Image>, std::vector<itk::simple::Image>&
%{
  $result=ImportSwigVec($result);
%}

// stop printing "NULL" when calling a method
// returning void. Also check for NA returned by
// an exception.
%typemap(scoerceout) void
%{
  if (is.null($result)) {
    return(invisible($result))
  } else {
    # should be a NULL - otherwise an exception
    stop("Exception in SITK - check warnings")
  }
%}


%extend itk::simple::Image {
  // a dummy function that we'll replace
  // strategy is to make swig generate a binding to something with the correct name,
  // and place those names in the method list for $ operator
  // The hand coded R version is provided in zA.R
  void SetPixel(const std::vector< uint32_t > &idx, double v)
  {
    itk::simple::Unused(v);
    itk::simple::Unused(idx);
  }

  double GetPixel(const std::vector< uint32_t > &idx)
  {
    itk::simple::Unused(idx);
    double e = 0;
    return(e);
  }

}

%ignore delete_Image_void(SEXP p);
%ignore delete_Transform_void(SEXP p);

%ignore R_swig_delete_Image ( SEXP self);
%ignore R_swig_delete_Transform (SEXP self);
%inline
%{
#ifdef __cplusplus
extern "C" {
#endif

SEXP R_swig_delete_Image ( SEXP self);
SEXP R_swig_delete_Transform (SEXP self);

  // wrappers for the swig generated destructors that return void
void delete_Image_void(SEXP p)
  {
    R_swig_delete_Image(p);
  }

void delete_Transform_void(SEXP p)
  {
    R_swig_delete_Transform(p);
  }

#ifdef __cplusplus
}
#endif

SEXP ImAsArray(itk::simple::Image src);
itk::simple::Image ArrayAsIm(SEXP arr,
                             std::vector<unsigned int> size,
                             std::vector<double> spacing,
                             std::vector<double> origin);
%}


// Garbage collection issues are tricky here. The obj parameter
// is a function closure - see ImageRegistrationMethod1.R for
// example of how to set it up. The closure part of it includes
// the environment in which the function was created, which is
// how it is able to access the registration object.
// The call to AddCommand is like this:
// Reg$AddCommand('sitkIterationEvent', commandIteration(Reg))
// It is difficult to cause crashes, even by calling gc() manually.
//
// The R documentation describes the scenario in which C code
// allocates R objects. The idea is that garbage collection
// can be invoked while the C code is being run due to
// calls to R internal functions. The PROTECT mechanism
// is used to guard the objects allocated in the C code.
//
// This doesn't cover the situation we have here, in which
// R objects are retained inside C objects, or are allocated
// then retained and are used in multiple C call.
// This case seems to be mentioned in passing at
// the end of 5.9.1 of Writing R extensions - R_PreserveObject
// and R_ReleaseObject. Sparing use is advised, but this
// seems like the situation for it.
// In order to keep things simple, we'll preserve the
// function closure passed in and the call we create.
// The obj will be passed to RCommand so that we can
// release it in the destructor.

// Dispatching is based on a type attribute attached to
// R classes. For standard types this is simple. For c++
// objects we end up with a class name that is a mangled
// c++ name. R SEXP objects are a problem. The default
// mangled name isn't useful and SEXP is used to represent
// everything in R. Ideally we can supply custom rtype
// setting, as below, but this gets quite tricky to mangage.
// The only other place where an SEXP is passed to/from
// swig bindings is in the array/image conversion code,
// which doesn't do dispatching. That code is largely
// confined to this file, so we put it first and set
// rtype to "numeric" there, then to "function" here.
// Finer control will require putting swig code in the right
// scope.

%typemap("rtype") SEXP "function";
%{
#include "sitkRCommand.h"
%}

%extend itk::simple::ProcessObject {
  int AddCommand( itk::simple::EventEnum e, SEXP obj )
 {
   // make sure that the CommandCallable is in fact callable
   if (!Rf_isFunction(obj))
     {
           sitkExceptionMacro(<<"R object is not a function, "
                              <<"or it has not been set.");
     }
   itk::simple::RCommand *cmd = NULL;
   try
     {
       cmd = new itk::simple::RCommand();
       cmd->SetFunctionClosure(obj);
       int ret = self->AddCommand(e,*cmd);
       cmd->OwnedByProcessObjectsOn();
       return(ret);
     }
   catch(...)
     {
       delete cmd;
       throw;
     }
 }
};

//#define %rcode %insert("sinit")

%Rruntime %{

  setMethod('show', '_p_itk__simple__Image', function(object) Show(object))
  setMethod('print', '_p_itk__simple__Image', function(x, ...)cat(x$ToString()))

  setMethod('print', 'C++Reference', function(x, ...)cat(x$ToString()))
  setMethod('show', 'C++Reference', function(object)cat(object$ToString()))

ImportSwigVec <- function(ImVec)
{
  # an import function for unsupported std::vector types
  # intended for vectors of sitk images
  l <- ImVec$'__len__'()
  return(lapply(1:l, function(idx, V)return(V$'__getitem__'(idx-1))))
}

ImListToVec <- function(ImList)
{
  l <- length(ImList)
  cppvec <- VectorOfImage()
  for (idx in 1:l)
    {
      cppvec$push_back(ImList[[idx]])
    }
   return(cppvec)
}

%}
#endif
