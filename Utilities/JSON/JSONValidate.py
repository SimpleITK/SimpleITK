#!/usr/bin/env python
import json, sys

try:
    json.load(open(sys.argv[1], "r", encoding="utf-8"))
except ValueError as e:
    print("ValueError: {0}".format(e))
    print("{0}:0:0: error: validating json file.".format(sys.argv[1]))
    sys.exit(1)
except TypeError as e:
    print("TypeError: {0}".format(e))
    print("{0}:0:0: error: validating json file.".format(sys.argv[1]))
    sys.exit(1)
