/* -----------------------------------------------------------------------------
 * Based on std_filesystem.i
 *
 * Allows convertsion from Python Strings or pathlib.Path to sitk.PathType
 * ----------------------------------------------------------------------------- */


%fragment("SWIG_sitk_PathType", "header"){
  SWIGINTERN PyObject * SWIG_sitk_PathType_importPathClass()
{
  PyObject * module = PyImport_ImportModule("pathlib");
  PyObject * cls = PyObject_GetAttrString(module, "Path");
  Py_DECREF(module);
  return cls;
}

SWIGINTERN bool
SWIG_sitk_PathType_isPathInstance(PyObject * obj)
{
  PyObject * cls = SWIG_sitk_PathType_importPathClass();
  bool       is_instance = PyObject_IsInstance(obj, cls);
  Py_DECREF(cls);
  return is_instance;
}

// converts a Python iterable of string or libpath.Path to a std::vector<std::string>
struct SWIG_sitk_PathType_IteratorProtocol {
  using type = std::vector<std::string, std::allocator< std::string>>;
  using value_type = typename type::value_type;
  static void assign(PyObject *obj, type *seq) {
    swig::SwigVar_PyObject iter = PyObject_GetIter(obj);
    if (iter) {
      swig::SwigVar_PyObject item = PyIter_Next(iter);
      while (item) {
        if (SWIG_sitk_PathType_isPathInstance(item))
        {
          item = PyObject_Str(item);
        }

        seq->insert(seq->end(), swig::as<value_type>(item));
        item = PyIter_Next(iter);
      }
    }
  }

  static bool check(PyObject *obj) {
    bool ret = false;
    swig::SwigVar_PyObject iter = PyObject_GetIter(obj);
    if (iter) {
      swig::SwigVar_PyObject item = PyIter_Next(iter);
      ret = true;
      while (item) {
        ret = SWIG_sitk_PathType_isPathInstance(item) || swig::check<value_type>(item);
        item = ret ? PyIter_Next(iter) : 0;
      }
    }
    return ret;
  }
};

}

%typemap(in, fragment="SWIG_sitk_PathType", fragment="<type_traits>") itk::simple::PathType {
  This is not being currently used
  if (PyUnicode_Check($input)) {
    PyObject *bytes = NULL;
    const char *s = SWIG_PyUnicode_AsUTF8AndSize($input, NULL, &bytes);
    $1 = itk::simple::PathType(s);
    Py_XDECREF(bytes);
  } else if (SWIG_sitk_PathType_isPathInstance($input)) {
    PyObject *str_obj = PyObject_Str($input);
    PyObject *bytes = NULL;
    const char *s = SWIG_PyUnicode_AsUTF8AndSize(str_obj, NULL, &bytes);
    $1 = itk::simpleitk::PathType(s);
    Py_XDECREF(bytes);
    Py_DECREF(str_obj);

  } else {
    std::string *ptr = (std::string *)0;
    int res = SWIG_AsPtr_std_string(obj1, &ptr);
    if (!SWIG_IsOK(res)) {
      %argument_fail(res, "$type", $symname, $argnum);
    }
  std::string * temp = %reinterpret_cast(ptr, $1_ltype*);
  $1 = itk::simple::PathType(*temp);
  }

}
%typemap(freearg) itk::simple::Path {}


%typemap(freearg) itk::simple::PathType {}


%typemap(in, fragment="SWIG_sitk_PathType", fragment="<type_traits>") const itk::simple::PathType &(itk::simple::PathType temp_path) {
  if (PyUnicode_Check($input)) {
    PyObject *bytes = NULL;
    const char *s = SWIG_PyUnicode_AsUTF8AndSize($input, NULL, &bytes);
    temp_path = itk::simple::PathType(s);
    $1 = &temp_path;
    Py_XDECREF(bytes);
  } else if (SWIG_sitk_PathType_isPathInstance($input)) {
    PyObject *str_obj = PyObject_Str($input);
    PyObject *bytes = NULL;
    const char *s = SWIG_PyUnicode_AsUTF8AndSize(str_obj, NULL, &bytes);
    temp_path = itk::simple::PathType(s);
    $1 = &temp_path;
    Py_XDECREF(bytes);
    Py_DECREF(str_obj);
  } else {
    void *argp = 0;
    int res = SWIG_ConvertPtr($input, &argp, $descriptor, $disown | 0);
    if (!SWIG_IsOK(res)) {
      %argument_fail(res, "$type", $symname, $argnum);
    }
    $1 = %reinterpret_cast(argp, $1_ltype);
  }
}

%typemap(freearg) const itk::simple::PathType &{}


// Fallback to the std::string "out" typemap
//
//%typemap(out, fragment="SWIG_sitk_PathType", fragment="<type_traits>") itk::simple::PathType {
//  $result = SWIG_From_std_string($1);
//}

//%typemap(out, fragment="SWIG_sitk_PathType", fragment="<type_traits>") const itk::simple::PathType & {
//  $result = SWIG_From_std_string(*$1);
//}


%typemap(in, fragement="SWIG_sitk_PathType", fragment="<type_traits>") const std::vector<itk::simple::PathType> &(std::vector<itk::simple::PathType> temp_path, int res) {
 if (SWIG_sitk_PathType_IteratorProtocol::check($input))
 {
  SWIG_sitk_PathType_IteratorProtocol::assign($input, &temp_path);
  $1 = &temp_path;
  res = SWIG_OK;
 } else {
  std::vector<std::string> * ptr = nullptr;
  res = swig::asptr($input, &ptr);
  if (!SWIG_IsOK(res))
  {
    %argument_fail(res, "$type", $symname, $argnum);
  }
  $1 = ptr;
  if (SWIG_IsNewObj(res))
  {
    delete ptr;
  }
 }
}
