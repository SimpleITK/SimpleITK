/* File : CSharpTypemapHelper.i */
%define %CSharpTypemapHelper(TYPE, CSTYPE)
  %typemap(in) TYPE "$1 = ($1_ltype)$input;" // wrap
  %typemap(imtype) TYPE "CSTYPE" // pinvoke
  %typemap(cstype, excode=SWIGEXCODE) TYPE "CSTYPE" // cs
  %typemap(csin, excode=SWIGEXCODE) TYPE "$csinput"
  %typemap(csout, excode=SWIGEXCODE) TYPE {
    CSTYPE ret = $imcall;$excode
    return ret;
  }
  %typemap(csvarin, excode=SWIGEXCODE) TYPE "
      set {
        $imcall;$excode
      }"
  %typemap(csvarout, excode=SWIGEXCODE) TYPE "
      get {
        return $imcall;$excode
      }"
%enddef

%define %CSharpPointerTypemapHelper(TYPE, CSTYPE)
  %typemap(in) TYPE "$1 = $1_ltype(($1_ltype::ObjectType*)$input);" // wrap
  %typemap(imtype) TYPE "CSTYPE" // pinvoke
  %typemap(cstype, excode=SWIGEXCODE) TYPE "CSTYPE" // cs
  %typemap(csin, excode=SWIGEXCODE) TYPE "$csinput"
  %typemap(csout, excode=SWIGEXCODE) TYPE {
    CSTYPE ret = $imcall;$excode
    return ret;
  }
  %typemap(csvarin, excode=SWIGEXCODE) TYPE "
      set {
        $imcall;$excode
      }"
  %typemap(csvarout, excode=SWIGEXCODE) TYPE "
      get {
        return $imcall;$excode
      }"
%enddef