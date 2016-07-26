
#!/usr/bin/env python


import glob, os, getopt, sys, tempfile
from doxy2swig import *


def usage():
    print( "\ndoxyall.py [options] doxygen_xml_dir output.i|output_directory" )
    print( "" )
    print( "     -h, --help    This help message" )
    print( "     -j, --java    Java style output" )
    print( "     -r, --R       R style output - note that output directory must be specified for R" )
    print( "" )


javaFlag = 0
rFlag = 0

try:
    opts, args = getopt.getopt(sys.argv[1:], "hjr", [ "help", "java", "R" ] )
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
    elif o in ("-r", "--R"):
        rFlag = 1
    else:
        assert False, "Unhandled option"


if len(args) < 2:
    usage()
    exit(1);

indir = args[0]
outfile = args[1]

if rFlag:
    outdir = args[1]

files = glob.glob(indir+"/*.xml")
files.sort()

tmpfd, tmpfile = tempfile.mkstemp(suffix=".i", text=True)
#tmpfile = "/tmp/doxyall." + str(os.getpid()) + ".i"

logfd, logfile = tempfile.mkstemp(suffix=".txt", prefix="doxyall.", text=True)

if not rFlag:
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
        if (rFlag):
            p = Doxy2R(x)
        else:
            p = Doxy2SWIG(x, javaFlag)

        p.generate()
        p.write(tmpfile)

        if (rFlag):
            ThisClassName = p.sitkClassName;
            # also exclude ones starting with detail or that are template instantiations
            if ThisClassName.find("detail::") >=0 or ThisClassName.find("<") >=0:
                continue

            ThisClassName = ThisClassName.replace("itk::simple::", "")
            ThisClassName = ThisClassName.replace("itk::Functor::", "")
            ## Get rid of the ITK classes
            if ThisClassName.find("itk::") >=0 or ThisClassName.find("<") >=0:
                continue

            outfile=outdir + "/" + ThisClassName + ".Rd"
            fout = open(outfile, "w")



        fin = open(tmpfile, "r")

        for line in fin:
            if (rFlag):
                if line in ('\n', '\r\n'):
                    continue
                line2 = line.replace("itk::simple::detail::", "")
                line2 = line.replace("itk::simple::", "")
            else:
                line2 = line.replace("itk::simple::detail::", "itk::simple::")
            line2 = line2.rstrip()
            fout.write(line2)
            fout.write('\n')
            if (rFlag):
                ## Need to duplicate the name entry to alias
                if line2.find("\\name{") >= 0:
                    line3=line2.replace("\\name{", "\\alias{")
                    line4=line2.replace("\\name{", "\\title{")
                    fout.write(line3)
                    fout.write('\n')
                    fout.write(line4)
                    fout.write('\n')

        if (rFlag):
            fout.close()
        fin.close()
    except:
        flog.write( "Error on file " + x + "\n")
        print( "Error on file " + x + "\n")
        errorCount = errorCount+1
if ( not rFlag):
    fout.close()

flog.close()

# the procedural interface
if rFlag:
    nspacefile=os.path.join(indir, "namespaceitk_1_1simple.xml")
    p = Doxy2RProc(nspacefile)
    p.generate()
    p.write(outdir)

os.close(tmpfd)
os.close(logfd)

if errorCount==0:
    os.remove(tmpfile)
    os.remove(logfile)
    print ("doxyall.py generated " + args[1])
else:
    print ("Warning: doxyall.py had " + str(errorCount) + "errors.  Log in " + logfile)
