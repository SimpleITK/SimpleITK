Logging
=======


Overview
--------

SimpleITK creates debug, warning and error messages intended for display or logging. The messaging and logging are
handled by a customizable class in ITK, the `OutputWindow`. The default implementation prints these messages to the
standard error. A derived class could print the messages to standard out or adapt the output to fit within another
logging framework. Errors in SimpleITK usually cause exceptions so any error message is unlikely. Warnings are more
likely and are enabled globally by default, but can be disabled with the `ProcessObject::SetGlobalWarningDisplay <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ProcessObject.html#a99d3df8ad7db82bc587edaa8706d135a>`_
method. Debug messages are set on a per object basis with the `SetDebug` method. The default value for new objects is
set by the `ProcessObject::SetGlobalDefaultDebug <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ProcessObject.html#a144b7364d2551428280cea91f4b28f30>`_
method. Disabled messages are not sent to the logging handler for efficiency.

The following example illustrates how to create a custom logging handler in SimpleITK. The example derives a class from
the `LoggerBase <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1LoggerBase.html>`_ class to customize
the logging behavior. The custom logger is then set as the ITK global logging handler, and then the original logger is
restored.



Code
----

.. tabs::

  .. tab:: Python

    .. literalinclude:: ../../Examples/Logging/Logging.py
       :language: python
       :lines: 19-
