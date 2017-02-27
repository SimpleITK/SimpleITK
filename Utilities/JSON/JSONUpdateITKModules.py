#!/usr/bin/env python
"""
Add and update the "itk_module" and "itk_group" fields in the
SimpleITK json file based on ITK source directory.
"""

import os, sys
import re
import json, collections


def IncludesToPaths(path):
  """Build a dict that maps include files to paths"""

  includeToPath = dict()
  prog = re.compile(r"(itk.*\.h)")
  for root, dirs, files in os.walk(path):
      for f in files:
          if prog.match(f):
              includeFile = prog.findall(f)[0]
              parts = root.split("/")
              module = parts[len(parts)-3] + parts[len(parts)-2]
              includeToPath[includeFile] = module
  return includeToPath

def FindModules(path):
    """Build a dict that maps paths to modules"""

    pathToModule = dict()
    fileProg = re.compile(r"itk-module.cmake")
    moduleProg = re.compile('.*itk_module[^(]*\(([^ \n]*)',re.S)
    for root, dirs, files in os.walk(path):
        for f in files:
            if fileProg.match(f):
                fid = open(root + "/" + f,"r")
                contents = fid.read()
                m = moduleProg.match(contents)
                if m:
                    moduleName = m.group(1)
                    parts = root.split("/")
                    pathToModule[parts[len(parts)-2] + parts[len(parts)-1]] = moduleName
                fid.close()
    return pathToModule

def FindGroups(path):
    """Build a dict that maps paths to groups"""

    pathToGroups = dict()
    fileProg = re.compile(r"itk-module.cmake")
    moduleProg = re.compile('.*itk_module[^(]*\(([^ \n]*)',re.S)
    for root, dirs, files in os.walk(path):
        for f in files:
            if fileProg.match(f):
                fid = open(root + "/" + f,"r")
                contents = fid.read()
                m = moduleProg.match(contents)
                if m:
                    groupName = os.path.basename(root)
                    parts = root.split("/")
                    pathToGroups[parts[len(parts)-2] + parts[len(parts)-1]] = groupName
                fid.close()
    return pathToGroups


pathToITK="/home/blowekamp/src/ITK"

# Generate dict's for mapping includes to modules
includesToPaths = IncludesToPaths(pathToITK + "/Modules")
pathsToModules = FindModules(pathToITK+"/Modules")
pathsToGroups = FindGroups(pathToITK+"/Modules")

# Test to see if ITK source is provided
if len(pathsToModules) == 0:
    print program + ": " + pathToITK + " is not an ITK source directory. It does not contain any itk-module.cmake files."
    exit(1)



for fname in sys.argv[1:]:

  print "Processing ", fname

  fp = file( fname, "r" )
  j = json.load( fp,object_pairs_hook=collections.OrderedDict )
  fp.close()

  if "itk_name" in j:
    inc=j["itk_name"]
  else:
    inc=j["name"]

  inc="itk"+inc+".h"

  if inc in includesToPaths:
    module = includesToPaths[inc]
    j["itk_module"]=pathsToModules[includesToPaths[inc]]
    j["itk_group"]=pathsToGroups[includesToPaths[inc]]

    with file( fname, "w" ) as fp:
      json.dump( j, fp, indent=2, separators=(',',' : ') )
  else:
    print "Unable to find include:",inc
