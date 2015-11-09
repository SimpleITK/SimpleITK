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
