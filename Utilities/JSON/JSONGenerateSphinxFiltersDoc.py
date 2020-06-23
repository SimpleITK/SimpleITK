#!/usr/bin/env python3
#
# JSONGenerateSphinxFiltersDoc.py
#
# This scripts read in the SimpleITK JSON descriptions of filters, and
# the text output produces a reStructuredText file for Sphinx documentation.
#
# Usage: Utilities/JSON/JSONGenerateSphinxFiltersDoc.py Code/BasicFilters/json/*.json
#

import json
import sys
try:
    from collections import OrderedDict
except ImportError:
    import ordereddict as OrderedDict

f = open("docs/source/filters.rst", "w+")
f.write('''.. _lbl_filter:

SimpleITK Filters
=================

.. list-table::
   :widths: 50 100
   :stub-columns: 1
   :header-rows: 1

   * - Filter Name\n     - Brief Description''')

entryFormat = "\n   * - `{0} <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1{1}.html>`_\n     - {2}"
json_list = []
for fname in sys.argv[1:]:
    with open( fname, "r" ) as fp:
        json_list.append(json.load( fp,object_pairs_hook=OrderedDict ))


json_list.sort( key= lambda j: j["name"] )

for j in json_list:
    jsonName = j["name"]

    if "briefdescription" in j:
        jsonBrief = j["briefdescription"]
    else:
        jsonBrief = ""

    if "itk_name" in j:
        jsonITK = j["itk_name"]
    elif "filter_type" in j:
        filter_type = j["filter_type"]
        if filter_type.startswith("itk::"):
            filter_type = filter_type[len("itk::"):]
        i=filter_type.find('<')
        if (i)!=-1:
            filter_type=filter_type[:i]
        jsonITK = filter_type
    else:
        jsonITK = jsonName

    f.write(entryFormat.format(jsonName, jsonITK, jsonBrief))

f.close()
