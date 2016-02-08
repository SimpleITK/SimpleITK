#!/usr/bin/env python


import glob, os, getopt, sys, tempfile
from doxy2swig import *


def usage():
    print( "\ndoxyall.py [options] doxygen_xml_dir output.i" )
    print( "" )
    print( "     -h, --help    This help message" )
    print( "     -j, --java    Java style output" )
    print( "" )


javaFlag = 0

try:
    opts, args = getopt.getopt(sys.argv[1:], "hj", [ "help", "java", ] )
except getopt.GetoptErr, err:
    print( str(err) )
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
files.sort()

tmpfd, tmpfile = tempfile.mkstemp(suffix=".i", text=True)
#tmpfile = "/tmp/doxyall." + str(os.getpid()) + ".i"

logfd, logfile = tempfile.mkstemp(suffix=".txt", prefix="doxyall.", text=True)

fout = open(outfile, "w")

flog = open(logfile, "w")

flog.write("tempfile: " + tmpfile + "\n")
errorCount = 0

for x in files:

# exclude the index file and tcl files.  the xml parse chokes on them
    if x.find("index")>=0 or x.find("tcl")>=0:
        continue

    flog.write("Processing " + x + "\n")

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
        flog.write( "Error on file " + x + "\n")
        print( "Error on file " + x + "\n")
        errorCount = errorCount+1

fout.close()
flog.close()

os.close(tmpfd)
os.close(logfd)

if errorCount==0:
    os.remove(tmpfile)
    os.remove(logfile)
    print ("doxyall.py generated " + args[1])
else:
    print ("Warning: doxyall.py had " + str(errorCount) + "errors.  Log in " + logfile)
