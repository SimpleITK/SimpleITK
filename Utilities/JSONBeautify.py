#!/usr/bin/env python
import json
import sys
try:
    from collections import OrderedDict
except ImportError:
    import ordereddict as OrderedDict

# This script takes one argument the name of a json file.
#


fname = sys.argv[1]

print "Processing ", fname

fp = file( fname, "r" )
j = json.load( fp,object_pairs_hook=OrderedDict )
fp.close()


fp = file( fname, "w" )
json.dump( j, fp, indent=2, separators=(',',' : ') )
print  >>fp, ""
fp.close()
