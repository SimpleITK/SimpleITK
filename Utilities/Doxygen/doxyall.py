#!/usr/bin/env python


import glob, os, getopt, sys
from doxy2swig import *


def usage():
    print "\ndoxyall.py [options] doxygen_xml_dir output.i"
    print ""
    print "     -h, --help    This help message"
    print "     -j, --java    Java style output"
    print ""


javaFlag = 0

try:
    opts, args = getopt.getopt(sys.argv[1:], "hj", [ "help", "java", ] )
except getopt.GetoptErr, err:
    print str(err)
    usage()
    sys.exit(1)

for o, a in opts:
    if o in ("-h", "--help"):
        usage()
        sys.exit()
    elif o in ("-j", "--java"):
        javaFlag = 1
    else:
        assert False, "Unhandled option"


if len(args) < 2:
    usage()
    exit(1);

indir = args[0]
outfile = args[1]

files = glob.glob(indir+"/*.xml")

tmpfile = "/tmp/doxyall.i"

fout = open(outfile, "w")

for x in files:

    print x

    try:
        p = Doxy2SWIG(x, javaFlag)
        p.generate()
        p.write(tmpfile)

        fin = open(tmpfile, "r")

        for line in fin:
            line2 = line.replace("itk::simple::detail::", "itk::simple::")
            line2 = line2.rstrip()
            fout.write(line2)
            fout.write('\n')

        fin.close()
    except:
        print "Error on file ", x, "\n"

fout.close()
