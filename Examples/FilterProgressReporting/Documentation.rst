.. _lbl_filter_progress_reporting:

Filter Progress Reporting
=========================


Overview
--------

SimpleITK has the ability to add commands or callbacks as observers of
events that may occur during data processing. This feature can be used to add
progress reporting to a console, to monitor the process of optimization,
to abort a process, or to improve the integration of
SimpleITK into Graphical User Interface event queues.


Events
------

Events are a simple enumerated type in SimpleITK, represented by
the `EventEnum type <https://simpleitk.org/doxygen/latest/html/namespaceitk_1_1simple.html#aa7399868984d99493c5a307cce373ace>`_.
More information about each event type can be found in the documentation
for the enum. All SimpleITK filters, including the reading
and writing ones, are derived from the ProcessObject class which has
support for events. SimpleITK utilizes the native ITK event system
but has simpler events and methods to add an observer or commands. The goal
is to provide a simpler interface more suitable for scripting
languages.

Commands
--------

The command design pattern is used to allow user code to be executed
when an event occurs. It is encapsulated in the Command class. The
Command class provides a virtual Execute method to be overridden in
derived classes. Additionally, SimpleITK provides internal reference
tracking between the ProcessObject and the Command. This reference tracking
allows an object to be created on the stack or dynamically allocated, without
additional burden.

Command Directors for Wrapped Languages
---------------------------------------
SimpleITK uses SWIG's director feature to enable wrapped languages to
derive classes from the Command class.  Thus a user may  override the
Command class's Execute method for custom call-backs. The following
languages support deriving classes from the Command class:

.. tabs::

  .. group-tab:: C#

    .. literalinclude:: ../../Examples/FilterProgressReporting/FilterProgressReporting.cs
       :language: c#
       :start-after: [csharp director command]
       :end-before: [csharp director command]

  .. group-tab:: Java

    .. literalinclude:: ../../Examples/FilterProgressReporting/FilterProgressReporting.java
       :language: java
       :start-after: [java director command]
       :end-before: [java director command]

  .. group-tab:: Python

    .. literalinclude:: ../../Examples/FilterProgressReporting/FilterProgressReporting.py
       :language: python
       :start-after: [python director command]
       :end-before: [python director command]

  .. group-tab:: Ruby

    .. literalinclude:: ../../Examples/FilterProgressReporting/FilterProgressReporting.rb
       :language: ruby
       :start-after: [ruby director command]
       :end-before: [ruby director command]


Command Functions and Lambdas for Wrapped Languages
---------------------------------------------------

Not all languages are naturally object oriented, and it is
often easier to simply define a callback inline with a lambda
function. The following language supports inline function definitions
for functions for the ProcessObject::AddCommand method:

.. tabs::

  .. group-tab:: C++

    .. literalinclude:: ../../Examples/FilterProgressReporting/FilterProgressReporting.cxx
       :language: c++
       :start-after: [cpp lambda command]
       :end-before: [cpp lambda command]

  .. group-tab:: Python

    .. literalinclude:: ../../Examples/FilterProgressReporting/FilterProgressReporting.py
       :language: python
       :start-after: [python lambda command]
       :end-before: [python lambda command]

  .. group-tab:: R

    .. literalinclude:: ../../Examples/FilterProgressReporting/FilterProgressReporting.R
       :language: r
       :start-after: [R lambda command]
       :end-before: [R lambda command]



Code
----

.. tabs::

  .. group-tab:: CSharp

    .. literalinclude:: ../../Examples/FilterProgressReporting/FilterProgressReporting.cs
       :language: c#
       :lines: 18-

  .. group-tab:: C++

    .. literalinclude:: ../../Examples/FilterProgressReporting/FilterProgressReporting.cxx
       :language: c++
       :lines: 18-

  .. group-tab:: Java

    .. literalinclude:: ../../Examples/FilterProgressReporting/FilterProgressReporting.java
       :language: java
       :lines: 18-

  .. group-tab:: Python

    .. literalinclude:: ../../Examples/FilterProgressReporting/FilterProgressReporting.py
       :language: python
       :lines: 1,19-

  .. group-tab:: R

    .. literalinclude:: ../../Examples/FilterProgressReporting/FilterProgressReporting.R
       :language: r
       :lines:  18-

  .. group-tab:: Ruby

    .. literalinclude:: ../../Examples/FilterProgressReporting/FilterProgressReporting.rb
       :language: ruby
       :lines:  18-
