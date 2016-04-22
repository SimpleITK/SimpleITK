 // R specific swig components
#if SWIGR

// ignore overload methods of int type when there is an enum
%ignore itk::simple::CastImageFilter::SetOutputPixelType( PixelIDValueType pixelID );
%ignore itk::simple::GetPixelIDValueAsString( PixelIDValueType type );

%include <std_vector.i>
// we don't want a class assigned to unsigned char
%typemap(scoerceout) unsigned char,
   unsigned char *,
   unsigned char &
   %{    %}


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
// returning void
%typemap(scoerceout) void
%{
  return(invisible($result))
%}

%inline
%{
#include "sitkConditional.h"


  // functions for image content access via bracket operator
  itk::simple::Image SingleBracketOperator(std::vector<int> xcoord, std::vector<int> ycoord, std::vector<int> zcoord, const itk::simple::Image src)
    {
      itk::simple::PixelIDValueType  PID=src.GetPixelIDValue();
      // use 3D coords. They get trimmed appropriately for 2D during access.
      std::vector<unsigned int> scoord(3);
      std::vector<unsigned int> dcoord(3);

      itk::simple::Image dest;

      if (zcoord.size() > 1)
        {
          dest = itk::simple::Image(xcoord.size(),ycoord.size(), zcoord.size(),
                                    static_cast<itk::simple::PixelIDValueEnum>(src.GetPixelIDValue()));
        }
      else
        {
          dest = itk::simple::Image(xcoord.size(),ycoord.size(),
                                    static_cast<itk::simple::PixelIDValueEnum>(src.GetPixelIDValue()));

        }
      dest.SetSpacing(src.GetSpacing());

      switch (PID) {
      case itk::simple::ConditionalValue< itk::simple::sitkUInt8 != itk::simple::sitkUnknown, itk::simple::sitkUInt8, -2 >::Value:
        {
          for (unsigned z = 0, K=0; z < zcoord.size(); z++)
            {
              scoord[2]=static_cast<unsigned int>(zcoord[z]);
              dcoord[2]=K;
              for (unsigned y = 0,J=0; y < ycoord.size(); y++)
                {
                  scoord[1]=static_cast<unsigned int>(ycoord[y]);
                  dcoord[1]=J;
                  for (unsigned x = 0,I=0; x < xcoord.size(); x++)
                    {
                      scoord[0]=static_cast<unsigned int>(xcoord[x]);
                      dcoord[0]=I;
                      dest.SetPixelAsUInt8(dcoord, src.GetPixelAsUInt8(scoord));
                      I++;
                    }
                  J++;
                }
              K++;
            }
          return(dest);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkInt8 != itk::simple::sitkUnknown, itk::simple::sitkInt8, -3 >::Value:
        {
          for (unsigned z = 0, K=0; z < zcoord.size(); z++)
            {
              scoord[2]=static_cast<unsigned int>(zcoord[z]);
              dcoord[2]=K;
              for (unsigned y = 0,J=0; y < ycoord.size(); y++)
                {
                  scoord[1]=static_cast<unsigned int>(ycoord[y]);
                  dcoord[1]=J;
                  for (unsigned x = 0,I=0; x < xcoord.size(); x++)
                    {
                      scoord[0]=static_cast<unsigned int>(xcoord[x]);
                      dcoord[0]=I;
                      dest.SetPixelAsInt8(dcoord, src.GetPixelAsInt8(scoord));
                      I++;
                    }
                  J++;
                }
              K++;
            }
          return(dest);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkUInt16 != itk::simple::sitkUnknown, itk::simple::sitkUInt16, -4 >::Value:
        {
          for (unsigned z = 0, K=0; z < zcoord.size(); z++)
            {
              scoord[2]=static_cast<unsigned int>(zcoord[z]);
              dcoord[2]=K;
              for (unsigned y = 0,J=0; y < ycoord.size(); y++)
                {
                  scoord[1]=static_cast<unsigned int>(ycoord[y]);
                  dcoord[1]=J;
                  for (unsigned x = 0,I=0; x < xcoord.size(); x++)
                    {
                      scoord[0]=static_cast<unsigned int>(xcoord[x]);
                      dcoord[0]=I;
                      dest.SetPixelAsUInt16(dcoord, src.GetPixelAsUInt16(scoord));
                      I++;
                    }
                  J++;
                }
              K++;
            }
          return(dest);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkInt16 != itk::simple::sitkUnknown, itk::simple::sitkInt16, -5 >::Value:
        {
          for (unsigned z = 0, K=0; z < zcoord.size(); z++)
            {
              scoord[2]=static_cast<unsigned int>(zcoord[z]);
              dcoord[2]=K;
              for (unsigned y = 0,J=0; y < ycoord.size(); y++)
                {
                  scoord[1]=static_cast<unsigned int>(ycoord[y]);
                  dcoord[1]=J;
                  for (unsigned x = 0,I=0; x < xcoord.size(); x++)
                    {
                      scoord[0]=static_cast<unsigned int>(xcoord[x]);
                      dcoord[0]=I;
                      dest.SetPixelAsInt16(dcoord, src.GetPixelAsInt16(scoord));
                      I++;
                    }
                  J++;
                }
              K++;
            }
          return(dest);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkUInt32 != itk::simple::sitkUnknown, itk::simple::sitkUInt32, -6 >::Value:
        {
          for (unsigned z = 0, K=0; z < zcoord.size(); z++)
            {
              scoord[2]=static_cast<unsigned int>(zcoord[z]);
              dcoord[2]=K;
              for (unsigned y = 0,J=0; y < ycoord.size(); y++)
                {
                  scoord[1]=static_cast<unsigned int>(ycoord[y]);
                  dcoord[1]=J;
                  for (unsigned x = 0,I=0; x < xcoord.size(); x++)
                    {
                      scoord[0]=static_cast<unsigned int>(xcoord[x]);
                      dcoord[0]=I;
                      dest.SetPixelAsUInt32(dcoord, src.GetPixelAsUInt32(scoord));
                      I++;
                    }
                  J++;
                }
              K++;
            }
          return(dest);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkInt32 != itk::simple::sitkUnknown, itk::simple::sitkInt32, -7 >::Value:
        {
          for (unsigned z = 0, K=0; z < zcoord.size(); z++)
            {
              scoord[2]=static_cast<unsigned int>(zcoord[z]);
              dcoord[2]=K;
              for (unsigned y = 0,J=0; y < ycoord.size(); y++)
                {
                  scoord[1]=static_cast<unsigned int>(ycoord[y]);
                  dcoord[1]=J;
                  for (unsigned x = 0,I=0; x < xcoord.size(); x++)
                    {
                      scoord[0]=static_cast<unsigned int>(xcoord[x]);
                      dcoord[0]=I;
                      dest.SetPixelAsInt32(dcoord, src.GetPixelAsInt32(scoord));
                      I++;
                    }
                  J++;
                }
              K++;
            }
          return(dest);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkUInt64 != itk::simple::sitkUnknown, itk::simple::sitkUInt64, -8 >::Value:
        {
          for (unsigned z = 0, K=0; z < zcoord.size(); z++)
            {
              scoord[2]=static_cast<unsigned int>(zcoord[z]);
              dcoord[2]=K;
              for (unsigned y = 0,J=0; y < ycoord.size(); y++)
                {
                  scoord[1]=static_cast<unsigned int>(ycoord[y]);
                  dcoord[1]=J;
                  for (unsigned x = 0,I=0; x < xcoord.size(); x++)
                    {
                      scoord[0]=static_cast<unsigned int>(xcoord[x]);
                      dcoord[0]=I;
                      dest.SetPixelAsUInt64(dcoord, src.GetPixelAsUInt64(scoord));
                      I++;
                    }
                  J++;
                }
              K++;
            }
          return(dest);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkInt64 != itk::simple::sitkUnknown, itk::simple::sitkInt64, -9 >::Value:
        {
          for (unsigned z = 0, K=0; z < zcoord.size(); z++)
            {
              scoord[2]=static_cast<unsigned int>(zcoord[z]);
              dcoord[2]=K;
              for (unsigned y = 0,J=0; y < ycoord.size(); y++)
                {
                  scoord[1]=static_cast<unsigned int>(ycoord[y]);
                  dcoord[1]=J;
                  for (unsigned x = 0,I=0; x < xcoord.size(); x++)
                    {
                      scoord[0]=static_cast<unsigned int>(xcoord[x]);
                      dcoord[0]=I;
                      dest.SetPixelAsInt64(dcoord, src.GetPixelAsInt64(scoord));
                      I++;
                    }
                  J++;
                }
              K++;
            }
          return(dest);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkFloat32 != itk::simple::sitkUnknown, itk::simple::sitkFloat32, -10 >::Value:

        {
          for (unsigned z = 0, K=0; z < zcoord.size(); z++)
            {
              scoord[2]=static_cast<unsigned int>(zcoord[z]);
              dcoord[2]=K;
              for (unsigned y = 0,J=0; y < ycoord.size(); y++)
                {
                  scoord[1]=static_cast<unsigned int>(ycoord[y]);
                  dcoord[1]=J;
                  for (unsigned x = 0,I=0; x < xcoord.size(); x++)
                    {
                      scoord[0]=static_cast<unsigned int>(xcoord[x]);
                      dcoord[0]=I;
                      dest.SetPixelAsFloat(dcoord, src.GetPixelAsFloat(scoord));
                      I++;
                    }
                  J++;
                }
              K++;
            }
          return(dest);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkFloat64 != itk::simple::sitkUnknown, itk::simple::sitkFloat64, -11 >::Value:
        {
          for (unsigned z = 0, K=0; z < zcoord.size(); z++)
            {
              scoord[2]=static_cast<unsigned int>(zcoord[z]);
              dcoord[2]=K;
              for (unsigned y = 0,J=0; y < ycoord.size(); y++)
                {
                  scoord[1]=static_cast<unsigned int>(ycoord[y]);
                  dcoord[1]=J;
                  for (unsigned x = 0,I=0; x < xcoord.size(); x++)
                    {
                      scoord[0]=static_cast<unsigned int>(xcoord[x]);
                      dcoord[0]=I;
                      dest.SetPixelAsDouble(dcoord, src.GetPixelAsDouble(scoord));
                      I++;
                    }
                  J++;
                }
              K++;
            }
          return(dest);
        }
      case itk::simple::ConditionalValue< itk::simple::sitkComplexFloat32 != itk::simple::sitkUnknown, itk::simple::sitkComplexFloat32, -12 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkComplexFloat64 != itk::simple::sitkUnknown, itk::simple::sitkComplexFloat64, -13 >::Value:
        {
          char error_msg[1024];
          snprintf( error_msg, 1024, "Exception thrown SingleBracketOperator : complex floating types not supported");
          Rprintf(error_msg);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt8 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt8, -14 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorInt8 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt8, -15 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt16 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt16, -16 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorInt16 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt16, -17 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt32 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt32, -18 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorInt32 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt32, -19 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt64 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt64, -20 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorInt64 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt64, -21 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorFloat32 != itk::simple::sitkUnknown, itk::simple::sitkVectorFloat32, -22 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorFloat64 != itk::simple::sitkUnknown, itk::simple::sitkVectorFloat64, -23 >::Value:
        {
        char error_msg[1024];
        snprintf( error_msg, 1024, "Images of Vector Pixel types currently are not supported." );
        Rprintf(error_msg);
        }
        break;
      default:
        char error_msg[1024];
        snprintf( error_msg, 1024, "Exception thrown SingleBrackeOperator : unsupported pixel type: %d", PID );
        Rprintf(error_msg);
      }
      // return something to keep R happy.
      return(itk::simple::Image(0,0,0, itk::simple::sitkUInt8));
    }

  SEXP ImAsArray(itk::simple::Image src)
  {
    // tricky to make this efficient with memory and fast.
    // Ideally we want multithreaded casting directly to the
    // R array. We could use a Cast filter and then a memory copy,
    // obviously producing a redundant copy. If we do a direct cast,
    // then we're probably not multi-threaded.
    // Lets be slow but memory efficient.

    std::vector<unsigned int> sz = src.GetSize();
    itk::simple::PixelIDValueType  PID=src.GetPixelIDValue();
    SEXP res = 0;
    double *dans=0;
    int *ians=0;
    unsigned pixcount=src.GetNumberOfComponentsPerPixel();
    for (unsigned k = 0; k < sz.size();k++)
      {
        pixcount *= sz[k];
      }
    switch (PID)
      {
      case itk::simple::sitkUnknown:
        {
          char error_msg[1024];
          snprintf( error_msg, 1024, "Exception thrown ImAsArray : unkown pixel type");
          Rprintf(error_msg);
          return(res);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkInt8 != itk::simple::sitkUnknown, itk::simple::sitkInt8, -3 >::Value:
case itk::simple::ConditionalValue< itk::simple::sitkVectorInt8 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt8, -15 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkUInt8 != itk::simple::sitkUnknown, itk::simple::sitkUInt8, -2 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt8 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt8, -14 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkInt16 != itk::simple::sitkUnknown, itk::simple::sitkInt16, -5 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorInt16 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt16, -17 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkUInt16 != itk::simple::sitkUnknown, itk::simple::sitkUInt16, -4 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt16 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt16, -16 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkInt32 != itk::simple::sitkUnknown, itk::simple::sitkInt32, -7 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorInt32 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt32, -19 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkUInt32 != itk::simple::sitkUnknown, itk::simple::sitkUInt32, -6 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt32 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt32, -18 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkUInt64 != itk::simple::sitkUnknown, itk::simple::sitkUInt64, -8 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt64 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt64, -20 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkInt64 != itk::simple::sitkUnknown, itk::simple::sitkInt64, -9 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorInt64 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt64, -21 >::Value:
        {
          // allocate an integer array
          PROTECT(res = Rf_allocVector(INTSXP, pixcount));
          ians = INTEGER_POINTER(res);
        }
        break;
      default:
        {
          // allocate double array
          PROTECT(res = Rf_allocVector(REALSXP, pixcount));
          dans = NUMERIC_POINTER(res);
        }
      }

    switch (PID)
      {
      case itk::simple::ConditionalValue< itk::simple::sitkUInt8 != itk::simple::sitkUnknown, itk::simple::sitkUInt8, -2 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt8 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt8, -14 >::Value:
        {
        uint8_t * buff = src.GetBufferAsUInt8();
        std::copy(buff,buff + pixcount,ians);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkInt8 != itk::simple::sitkUnknown, itk::simple::sitkInt8, -3 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorInt8 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt8, -15 >::Value:
        {
        int8_t * buff = src.GetBufferAsInt8();
        std::copy(buff,buff + pixcount,ians);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkUInt16 != itk::simple::sitkUnknown, itk::simple::sitkUInt16, -4 >::Value:
case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt16 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt16, -16 >::Value:
        {
        uint16_t * buff = src.GetBufferAsUInt16();
        std::copy(buff,buff + pixcount,ians);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkInt16 != itk::simple::sitkUnknown, itk::simple::sitkInt16, -5 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorInt16 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt16, -17 >::Value:
        {
        int16_t * buff = src.GetBufferAsInt16();
        std::copy(buff,buff + pixcount,ians);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkUInt32 != itk::simple::sitkUnknown, itk::simple::sitkUInt32, -6 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt32 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt32, -18 >::Value:
        {
        uint32_t * buff = src.GetBufferAsUInt32();
        std::copy(buff,buff + pixcount,ians);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkInt32 != itk::simple::sitkUnknown, itk::simple::sitkInt32, -7 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorInt32 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt32, -19 >::Value:
        {
        int32_t * buff = src.GetBufferAsInt32();
        std::copy(buff,buff + pixcount,ians);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkUInt64 != itk::simple::sitkUnknown, itk::simple::sitkUInt64, -8 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt64 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt64, -20 >::Value:

        {
        uint64_t * buff = src.GetBufferAsUInt64();
        std::copy(buff,buff + pixcount,ians);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkInt64 != itk::simple::sitkUnknown, itk::simple::sitkInt64, -9 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorInt64 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt64, -21 >::Value:
        {
        int64_t * buff = src.GetBufferAsInt64();
        std::copy(buff,buff + pixcount,ians);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkFloat32 != itk::simple::sitkUnknown, itk::simple::sitkFloat32, -10 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorFloat32 != itk::simple::sitkUnknown, itk::simple::sitkVectorFloat32, -22 >::Value:
        {
        float * buff = src.GetBufferAsFloat();
        std::copy(buff,buff + pixcount,dans);
        }
        break;
      case itk::simple::ConditionalValue< itk::simple::sitkFloat64 != itk::simple::sitkUnknown, itk::simple::sitkFloat64, -11 >::Value:
      case itk::simple::ConditionalValue< itk::simple::sitkVectorFloat64 != itk::simple::sitkUnknown, itk::simple::sitkVectorFloat64, -23 >::Value:
        {
        double * buff = src.GetBufferAsDouble();
        std::copy(buff,buff + pixcount,dans);
        }
        break;
      default:
        char error_msg[1024];
        snprintf( error_msg, 1024, "Exception thrown ImAsArray : unsupported pixel type: %d", PID );
        Rprintf(error_msg);
      }
    UNPROTECT(1);
    return(res);
  }

#include "sitkImportImageFilter.h"

itk::simple::Image ArrayAsIm(SEXP arr,
                             std::vector<unsigned int> size,
                             std::vector<double> spacing,
                             std::vector<double> origin)
    {
      // can't work out how to get the array size in C
      itk::simple::ImportImageFilter importer;
      importer.SetSpacing( spacing );
      importer.SetOrigin( origin );
      importer.SetSize( size );
      if (Rf_isReal(arr))
        {
          importer.SetBufferAsDouble(NUMERIC_POINTER(arr));
        }
      else if (Rf_isInteger(arr) || Rf_isLogical(arr))
        {
          importer.SetBufferAsInt32(INTEGER_POINTER(arr));
        }
      else
        {
          char error_msg[1024];
          snprintf( error_msg, 1024, "Exception thrown ArrayAsIm : unsupported array type");
          Rprintf(error_msg);
        }
      itk::simple::Image res = importer.Execute();
      return(res);
    }

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


// a wrapper converting the Wrapped image to itk::simple::Image
%wrapper %{
  SWIGEXPORT itk::simple::Image * convertSwigSimpleITKImage( SEXP obj )
  {
    itk::simple::Image* img;
    if (SWIG_ConvertPtr(obj, (void **) &img, SWIGTYPE_p_itk__simple__Image, 0) == -1)
      return NULL;
    return img;
  }
  %}

#endif
