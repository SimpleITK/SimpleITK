#!/usr/bin/env python
# =========================================================================
#
#  Copyright NumFOCUS
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0.txt
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
# =========================================================================

import re, sys, csv
import SimpleITK
import itk
import argparse


class bcolors:
    """A class to print colored text."""

    HEADER = "\033[95m"
    OKBLUE = "\033[94m"
    OKGREEN = "\033[92m"
    WARNING = "\033[93m"
    FAIL = "\033[91m"
    ENDC = "\033[0m"


class FilterSet:
    """The main data structure for holding the filter data"""

    filters = list()  # a list of all the filters
    itk = set()  # a set of all the ITK filters
    sitk = set()  # a set of all the SimpleITK filters
    todo = set()  # a set of the ITK filters not yet in SimpleITK but to be done
    remarks = dict()  # a dictionary of remarks, indexed by filter name


# Global variables
fs = FilterSet()  # the filter data structure
remarkFile = ""
onlyRemarksFlag = False
sortByType = False
quietMode = False
writelessMode = False

fieldnames = ("Filter", "ITK", "SITK", "Remark", "ToDo")  # fields in the CSV file


#
#
class unix_dialect(csv.Dialect):
    """Describe the usual properties of unix-generated CSV files."""

    delimiter = ","
    quotechar = '"'
    doublequote = True
    skipinitialspace = False
    lineterminator = "\n"
    quoting = csv.QUOTE_MINIMAL


def writeCSV(name):
    """Write the results out to a common-spaced-value file (readable by any spreadsheet program)"""
    csv.register_dialect("unix_dialect", unix_dialect)
    try:
        with open(name, "w") as fp:
            writer = csv.DictWriter(fp, fieldnames=fieldnames, dialect="unix_dialect")
            headers = dict((n, n) for n in fieldnames)
            writer.writerow(headers)
            for filt in fs.filters:
                if filt in fs.remarks:
                    rem = fs.remarks[filt]
                else:
                    rem = ""
                if len(rem) or not onlyRemarksFlag:
                    writer.writerow(
                        {
                            fieldnames[0]: filt,
                            fieldnames[1]: filt in fs.itk,
                            fieldnames[2]: filt in fs.sitk,
                            fieldnames[3]: rem,
                            fieldnames[4]: filt in fs.todo,
                        }
                    )
    except:
        print(
            bcolors.FAIL,
            "Error:",
            bcolors.ENDC,
            "Couldn't write output file",
            name,
            "\n",
        )
        sys.exit(-1)


#
#
def readCSV(name):
    """Read the filters from a CSV file.

    Note that the only the Remark and ToDo fields are taken from the CSV file.
    The filter names and which toolkits have each filter comes from is not read
    from the file.  Rather that information is loaded from the ITK and SimpleITK
    Python symbol tables.
    """
    try:
        with open(name, "rU") as fp:
            reader = csv.DictReader(fp)
            for row in reader:
                filt = row[fieldnames[0]]

                # Check the file to see if the ITK/SITK flags match what we've pulled from Python.
                iflag = sflag = False
                if len(row[fieldnames[1]]):
                    iflag = row[fieldnames[1]].lower() == "true"
                if len(row[fieldnames[2]]):
                    sflag = row[fieldnames[2]].lower() == "true"

                initk = filt in fs.itk
                insitk = filt in fs.sitk

                if not initk and not insitk:
                    print(
                        bcolors.FAIL,
                        "Warning: ",
                        bcolors.ENDC,
                        "Filter ",
                        filt,
                        "not found in either ITK or SimpleITK",
                    )

                if (iflag != initk) or (sflag != insitk):
                    print(
                        bcolors.FAIL,
                        "Warning: ",
                        bcolors.ENDC,
                        "mismatch between file and symbol table for filter ",
                        filt,
                    )
                    print("    ", row)

                # Get the remark field from the file.
                if row[fieldnames[3]] != None:
                    if len(row[fieldnames[3]]):
                        fs.remarks[filt] = row[fieldnames[3]]

                # Get the ToDo flag
                if len(row[fieldnames[4]]):
                    if row[fieldnames[4]].lower() == "true":
                        fs.todo.add(filt)

    except:
        print(
            bcolors.FAIL,
            "Warning:",
            bcolors.ENDC,
            "Couldn't read input file",
            name,
            ".  Proceeding without it.\n",
        )
    else:
        if not quietMode:
            print("Read file", remarkFile, "\n")


#
#
def filterKey(filter_name):
    """Function that produces a key for sorting filters by toolkit.

    If a filter is in ITK, an 'I' gets prepended to the name, if not an 'i'.
    Similarly if the filter is in SimpleITK it gets a 'S', if not an 's'.
    The SimpleITK letter comes after the ITK.  So if the filter # is in both toolkits,
    it gets "IS"; only in ITK gets "Is"; only in SimpleITK gets "iS".
    """
    itag = "I" if filter_name in fs.itk else "i"
    stag = "S" if filter_name in fs.sitk else "s"
    return itag + stag + filter_name


#
#
def parse_arguments():
    parser = argparse.ArgumentParser(
        description="Compare what image filters ITK (via WrapITK) and SimpleITK implement."
    )
    parser.add_argument(
        "output_file", nargs="?", default="filters.csv", help="Output file name (default: filters.csv)"
    )
    parser.add_argument(
        "-t", "--type", action="store_true", help="Sort printed filters by toolkit type."
    )
    parser.add_argument(
        "-r", "--remark", metavar="FILTER:REMARK", help="Add a remark entry in the format 'filter_name:remark string'."
    )
    parser.add_argument(
        "-o", "--only", action="store_true", help="Only output filters with remarks."
    )
    parser.add_argument(
        "-q", "--quiet", action="store_true", help="Quiet mode, don't print filter list."
    )
    parser.add_argument(
        "-w", "--writeless", action="store_true", help="Writeless mode, don't write the output file."
    )
    return parser.parse_args()


args = parse_arguments()
remarkFile = args.output_file
onlyRemarksFlag = args.only
sortByType = args.type
quietMode = args.quiet
writelessMode = args.writeless

if args.remark:
    words = args.remark.partition(":")
    remarks[words[0]] = words[2]
    print(words[0], remarks[words[0]])


#
#   Get all the ITK and SimpleITK classes from Python symbol tables.
#

sclasses = dir(SimpleITK)
iclasses = dir(itk)

#   Find all the SimpleITK class names that end with "ImageFilter".
#   SimpleITK has a base class that is just "ImageFilter" that we want to omit.
for s in sclasses:
    if re.search(r"ImageFilter$", s):
        if s != "ImageFilter":
            fs.sitk.add(s)

if not quietMode:
    print("\nSimpleITK has", bcolors.OKBLUE, len(fs.sitk), bcolors.ENDC, "filters.")


#   Find all the ITK class names that end with "ImageFilter" or "ImageSource"
#   ITK has a base class that is just "ImageSource" that we want to omit.
for i in iclasses:
    if re.search(r"ImageFilter$", i) or re.search(r"ImageSource$", i):
        if i != "ImageSource":
            fs.itk.add(i)

if not quietMode:
    print("ITK has", bcolors.OKBLUE, len(fs.itk), bcolors.ENDC, "filters.\n")

fs.filters = list(fs.itk.union(fs.sitk))


#
# Sort the filters either by name or toolkit and name
#

if sortByType:
    fs.filters = sorted(fs.filters, key=filterKey)
else:
    fs.filters.sort()


#
#  Read the remarks from file

if remarkFile != "":
    readCSV(remarkFile)


#
#    Print all the filters
#

if not quietMode:
    bothcount = icount = scount = 0
    word = ""

    for filt in fs.filters:
        inI = filt in fs.itk
        inS = filt in fs.sitk
        if inI and inS:
            color = bcolors.OKBLUE
            word = "Both"
            bothcount += 1
        elif inI:
            color = bcolors.OKGREEN
            word = "ITK "
            icount += 1
        else:
            color = bcolors.FAIL
            word = "SITK"
            scount += 1

        rem = ""
        if filt in fs.remarks:
            rem = fs.remarks[filt]
        print("%50s %s %s %s      %s" % (filt, color, word, bcolors.ENDC, rem))

    print("")
    print("%3d filters in both toolkits." % bothcount)
    print("%3d filters in ITK only." % icount)
    print("%3d filters in SimpleITK only." % scount)
    print("")


#
#   Write out the new CSV file
#

if not writelessMode:
    if remarkFile == "":
        remarkFile = "filters.csv"
    writeCSV(remarkFile)
    if not quietMode:
        print("Wrote file", remarkFile)
        print("")
