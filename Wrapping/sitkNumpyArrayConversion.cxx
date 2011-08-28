// Python is written in C
extern "C"
{

static PyObject *
sitk_GetArrayFromImage( PyObject *self, PyObject *args )
{
  return Py_BuildValue("i", 42);
}

static PyObject *
sitk_GetImageFromArray( PyObject *self, PyObject *args )
{
  return Py_BuildValue("i", 42);
}

}
