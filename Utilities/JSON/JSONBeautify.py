#!/usr/bin/env python3
import json
import sys
try:
    from collections import OrderedDict
except ImportError:
    import ordereddict as OrderedDict

# This script takes one argument the name of a json file.
#


fname = sys.argv[1]

print( "Processing ", fname)

with open( fname, "r" ) as fp:
    j = json.load( fp, object_pairs_hook=OrderedDict )

with open( fname, "w" ) as fp:
    json.dump( j, fp, indent=2, separators=(',',' : ') )
    print("", file=fp)
