#!/usr/bin/env python
from __future__ import print_function
import json, sys

try:
    json.load( open( sys.argv[1], "r" ))
except ValueError:
    t, e = sys.exc_info()[:2] # works on old python versions
    print( "ValueError: {0}".format( e ) )
    print( "{0}:0:0: error: validating json file.".format( sys.argv[1] ) )
    sys.exit(1)
except TypeError:
    t, e = sys.exc_info()[:2]
    print( "TypeError: {0}".format( e ) )
    print( "{0}:0:0: error: validating json file.".format( sys.argv[1] ) )
    sys.exit(1)
