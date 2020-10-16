.. _lbl_cpp_inplace:

C++ InPlace Filter Execution
============================


Overview
--------

With the C++ interface of SimpleITK, some filters and image operators can run "inplace" to reduce memory
usage and improve performance. When a filter is run in-place the memory allocated to the image buffer of
the input image is reused for the output. Since the output buffer is not separately allocated, the peak memory usage
can be reduced by 50%. The performance improvement of running an algorithm in-place comes from not only removing
the cost of memory allocating but also reduced memory accessed during algorithm execution. Speed up of
1.5x are common while speedup of 10x have been observed.

The SimpleITK filters automatically run in-place with rvalue references. When a temporary result is
passed as an input argument to a filter ( procedure or a filter's `Execute` method ), the temporary's buffer will be
re-used for the output. Move semantics and rvalue references are an advanced C++ topic which require additional studying
to fully understand the details. Procedures and `Execute` methods with rvalue references (`&&` before argument name)
as the first argument support the in-place execution. The following is an example of two procedural methods which support
execution in-place.

.. code-block:: c++

  Image UnaryMinus(Image &&image1);
  Image SmoothingRecursiveGaussian(Image &&image1, std::vector<double> sigma, bool normalizeAcrossScale);

Additionally, most C++ overloaded Image numeric operators such as `+`, `-`, `*`, `%`, etc. support in-place execution.

The SimpleITK Image class supports move semantics with the constructor and assignment operator. Since the
Image class also uses a lazy copy-on-write implement for the constructors and assignment there is not a  significant
direct performance benefit using these operations. However, the move semantics can be useful to reduce the number
of Image objects referencing the same image buffer to prevent unnecessary copies. Lastly, if a rvalue Image object is
passed to a filter and that Image object's buffer is not unique, then the image buffer will be copied before the filter is
executed in-place. Generally, copying the image then executing the filter in-place is faster than executing the not
in-place implementation.

The following example demonstrates implicit and explicit use of C++ rvalues to execute filter in-place for improve
performance.

Code
----

.. tabs::

  .. tab:: C++

    .. literalinclude:: ../../Examples/CppInPlace/CppInPlace.cxx
       :language: c++
       :lines: 18-
