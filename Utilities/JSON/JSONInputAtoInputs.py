#!/usr/bin/env python
import json
import sys
import collections

# this script takes one argument the name of a json file.
# it converts the old style "inputA", "inputB" to the new style
# "inputs[]" for the testing fields in the json. Example of the change
# below:

#   "tests" : [ {
#    "tag" : "2d",
#    "description" : "2D",
#    "inputA" : "Input/STAPLE1.png",
#    "inputB" : "Input/STAPLE2.png",
#    "settings" : [ ],
#    "md5hash" : "bc458a17e18c79ae767e8be47451d1b4"
#  } ...

#  "tests" : [
#    {
#      "tag" : "2d",
#      "description" : "2D",
#      "settings" : [],
#      "md5hash" : "bc458a17e18c79ae767e8be47451d1b4",
#      "inputs" : [
#        "Input/STAPLE1.png",
#        "Input/STAPLE2.png"
#      ]
#    }

fname = sys.argv[1]

print "Processing ", fname

fp = file( fname, "r" )
j = json.load( fp,object_pairs_hook=collections.OrderedDict )
fp.close()

for test in j["tests"]:
    inputs = []
    if "inputA" in test:
        inputs.append( test["inputA"] )
        del test["inputA"]

    if "inputB" in test:
        inputs.append( test["inputB"] )
        del test["inputB"]

    if( len( inputs ) ):
       test["inputs"] = inputs


fp = file( fname, "w" )
json.dump( j, fp, indent=2, separators=(',',' : ') )
print  >>fp, ""
fp.close()
