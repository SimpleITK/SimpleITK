Python File Logging
===================


Overview
--------

SimpleITK is built on top of the C++ Insight Toolkit (ITK) which is wrapped
for use in the Python language. Some of the ITK functions report warnings
that are printed to standard error or standard output. There are three common
approaches to dealing with these warnings:

1. Do nothing, warnings are printed and we ignore them.
2. Suppress them, :code:`sitk.ProcessObject_SetGlobalWarningDisplay(False)`, warnings are not printed.
3. Include the warnings as part of a log file for program monitoring and debugging purposes.

This example illustrates how to ingest the ITK warnings into a log file created using the
Python logging framework.


Code
----

.. tabs::
  .. tab:: Python

    .. literalinclude:: ../../Examples/PythonFileLogging/FileLogging.py
       :language: python
       :lines: 19-
