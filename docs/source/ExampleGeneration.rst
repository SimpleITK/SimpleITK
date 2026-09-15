Example Generation System
*************************

Overview
========

SimpleITK includes a code generation system for automatically producing
multi-language example programs for image filters. Given a filter's existing
YAML description file, the system renders a set of Jinja2 templates to produce
ready-to-run example code in every supported language as well as accompanying
documentation and a CMake build file.

The system has three components:

1. **The filter YAML files** in ``Code/BasicFilters/yaml/`` — one per filter,
   describing the filter's parameters, inputs, brief description, and tests.
2. **The example filter list** at ``Examples/example_filter_list.yaml`` — a
   curated list of filters for which examples should be generated.
3. **The Jinja2 templates** in
   ``ExpandTemplateGenerator/templates/examples/`` — one template per output
   file type.

The ``ExpandTemplateGenerator/ExpandTemplate.py`` script drives the process:
it reads a filter's YAML file, loads the appropriate Jinja2 template, and
writes the rendered output to disk.


Generated Output Files
======================

For each filter named ``<FilterName>`` listed in
``Examples/example_filter_list.yaml``, the following files are generated under
``Examples/<FilterName>/``:

.. list-table::
   :widths: 35 65
   :header-rows: 1

   * - File
     - Description
   * - ``<FilterName>.py``
     - Python example script
   * - ``<FilterName>.cxx``
     - C++ example source file
   * - ``<FilterName>.cs``
     - C# example
   * - ``<FilterName>.java``
     - Java example
   * - ``<FilterName>.lua``
     - Lua example
   * - ``<FilterName>.R``
     - R example
   * - ``<FilterName>.rb``
     - Ruby example
   * - ``Documentation.rst``
     - Sphinx documentation page for the example, including an
       ``exec_code`` block that runs the example during the docs build
   * - ``CMakeLists.txt``
     - CMake file for building the C++ example


Templates
=========

All templates live in ``ExpandTemplateGenerator/templates/examples/`` and use
the `Jinja2 <https://jinja.palletsprojects.com/>`_ templating language. Each
template file name reflects the output it produces:

.. list-table::
   :widths: 45 55
   :header-rows: 1

   * - Template file
     - Rendered output
   * - ``ExampleTemplate.py.jinja``
     - Python source file
   * - ``ExampleTemplate.cxx.jinja``
     - C++ source file
   * - ``ExampleTemplate.cs.jinja``
     - C# source file
   * - ``ExampleTemplate.java.jinja``
     - Java source file
   * - ``ExampleTemplate.lua.jinja``
     - Lua source file
   * - ``ExampleTemplate.R.jinja``
     - R source file
   * - ``ExampleTemplate.rb.jinja``
     - Ruby source file
   * - ``ExampleDocumentation.rst.jinja``
     - Sphinx documentation page
   * - ``ExampleCMakeLists.cmake.jinja``
     - CMake build file

Templates consume variables from the filter's YAML description.  The most
important ones are:

- ``name`` — the SimpleITK filter class name (e.g. ``DiscreteGaussianImageFilter``).
- ``briefdescription`` / ``detaileddescription`` — human-readable description text.
- ``number_of_inputs`` — count of positional input images.
- ``inputs`` — list of named input image descriptors.
- ``members`` — filter parameters (name, type, default value, description).
- ``measurements`` — output measurements returned by the filter.
- ``no_return_image`` — ``true`` for measurement-only filters that do not
  produce an output image.
- ``tests`` — list of test entries; the first entry (``tests[0]``) is used as
  the example data source when no ``example`` key is present.
- ``example`` — optional override (see :ref:`example-key`).

Templates also have access to several custom Jinja2 filters:

- ``regex_replace(find, replace)`` — Python ``re.sub`` inside a template.
- ``ruby_capitalize`` — capitalizes the first letter of every word.
- ``quote`` — wraps a string in double quotes.
- ``format_list(pattern)`` — applies a ``str.format`` pattern to every item
  in a list.


The ``example_filter_list.yaml`` File
======================================

``Examples/example_filter_list.yaml`` is the entry point for the generator.
It contains a ``filters`` list with one filter name per entry:

.. code-block:: yaml

   filters:
     # ---- Smoothing / blurring ----
     - DiscreteGaussianImageFilter
     - SmoothingRecursiveGaussianImageFilter
     - MedianImageFilter
     # ...

Guidelines for adding a filter to the list:

- Prefer filters with a clear single-input → single-output relationship so the
  generated example is self-contained and easy to read.
- Filters that have at least one test entry in their YAML are preferred because
  the test data is reused as the example input.
- Measurement-only filters (``no_return_image: true``) are welcome; the
  templates will print computed values instead of writing an image file.


.. _example-key:

The Optional ``example`` Key in a Filter YAML
=============================================

By default the generator uses the first entry in the filter's ``tests`` list
to determine which input files and parameter settings appear in the example
code.  You can override this by adding an ``example`` key directly to the
filter's YAML file:

.. code-block:: yaml

   example:
     inputs:
       - Input/BrainProtonDensitySlice.png   # path relative to SimpleITK_DATA_ROOT
     settings:
       - parameter: Sigma
         type: double
         value: 2.0
     description: "Blur with sigma = 2.0 in physical space."

When the ``example`` key is present it takes complete precedence over
``tests[0]``.  If neither ``example`` nor ``tests`` is defined, the generated
code emits placeholder strings such as ``<input>`` and ``<output>`` that the
user must replace manually.


Running the Generator
=====================

The generator script is invoked once per output file:

.. code-block:: bash

   python ExpandTemplateGenerator/ExpandTemplate.py \
       Code/BasicFilters/yaml/DiscreteGaussianImageFilter.yaml \
       ExampleTemplate.py.jinja \
       -D ExpandTemplateGenerator/templates/examples \
       -o Examples/DiscreteGaussianImageFilter/DiscreteGaussianImageFilter.py

Key command-line options:

.. list-table::
   :widths: 30 70
   :header-rows: 1

   * - Option
     - Description
   * - ``config_file`` (positional)
     - Path to the filter's YAML description file.
   * - ``template`` (positional)
     - Jinja2 template file name (looked up in the directories given by ``-D``).
   * - ``-D`` / ``--template_dir``
     - Directory to search for templates. May be repeated to add multiple
       directories.
   * - ``-o`` / ``--output``
     - Path to the output file. Omit to write to stdout.
   * - ``--no-overwrite``
     - Do not overwrite the output file if it already exists.
   * - ``-g`` / ``--global``
     - Define a global template variable in ``NAME=VALUE`` form (e.g.
       ``TEST_HARNESS_DATA_DIRECTORY=/path/to/data``).  May be repeated.
   * - ``-v`` / ``--verbose``
     - Enable verbose logging.


Adding Support for a New Filter
================================

1. Verify the filter has a YAML description in ``Code/BasicFilters/yaml/``.
   The schema for the YAML format is documented in
   ``ExpandTemplateGenerator/simpleitk_filter_description.schema.json`` and
   described in :doc:`FilterTemplates`.

2. (Optional) Add an ``example`` key to the filter's YAML if you want to use
   inputs or settings different from those in ``tests[0]``.

3. Add the filter name to the ``filters`` list in
   ``Examples/example_filter_list.yaml``.

4. Run ``ExpandTemplate.py`` for each template (or let the CMake build system
   do it) to produce the files under ``Examples/<FilterName>/``.

5. Review the generated files and commit them.


Adding a New Language Template
===============================

To add example generation for a new language:

1. Create a new Jinja2 template file in
   ``ExpandTemplateGenerator/templates/examples/`` following the naming
   convention ``ExampleTemplate.<ext>.jinja``.

2. Use the same template variables described in the `Templates`_ section above.
   Consult an existing template such as ``ExampleTemplate.py.jinja`` as a
   reference.

3. Update the CMake logic (and ``example_filter_list.yaml`` comments) to
   invoke ``ExpandTemplate.py`` with the new template for each listed filter.


Relation to the Filter Code-Generation System
=============================================

The example generation system reuses the same YAML filter description files
and the same ``ExpandTemplate.py`` script that drives SimpleITK's *source code*
generation for filters (described in :doc:`FilterTemplates`).  The only
difference is the set of templates used:

- Filter source-code templates live in ``Code/BasicFilters/templates/``.
- Example templates live in ``ExpandTemplateGenerator/templates/examples/``.

This means any filter that already has a well-formed YAML description can have
examples generated for it immediately, without any additional tooling.
