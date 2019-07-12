#!/usr/bin/env python

from __future__ import print_function
import os
import sys
import io
import json
import re
import getopt
from lxml import etree
from collections import OrderedDict


#
#  This script updates the documentation of a SimpleITK class in its
#  JSON file.  The documentation is pulled from the correpsonding ITK
#  class XML file.  The SimpleITKClass.json file is modified in place.
#
#  The script is a re-write of the GenerateDocumentation.groovy script in python.
#
#  usage: GenerateDoc.py <SimpleITKClass.json> <Path/To/ITK-build/With/Doxygen>
#

def usage():
    print("")
    print(
        "usage: GenerateDoc.py [options] <SimpleITKClass.json> <Path/To/ITK-build/With/Doxygen>")
    print("")
    print("   -h, --help    This help message")
    print("   -D, --Debug   Enable debugging messages")
    print("   -b, --backup  Backup JSON file")
    print("")


def find_xml_file(itk_path, json_obj):
    itk_name = ''
    if 'itk_name' in json_obj:
        itk_name = json_obj['itk_name']

    name = ''
    if 'name' in json_obj:
        name = json_obj['name']

    template_code_filename = ''
    if 'template_code_filename' in json_obj:
        template_code_filename = json_obj['template_code_filename']

    xml_file_options = ["classitk_1_1" + itk_name + ".xml",
                      "classitk_1_1" + name + template_code_filename + ".xml",
                      "classitk_1_1" + name + ".xml"]
    #print( xml_file_options )
    for xf in xml_file_options:
        xname = itk_path + '/' + xf
        if os.path.isfile(xname):
            try:
                xml_file = io.open(xname, "r", encoding='utf8')
                print("xml file: ", xname)
            except BaseException:
                xml_file = None
                print("no xml file: ", xname)

    if not xml_file:
        print("Tried to read a file for " + name)
        print(xml_file_options)
        sys.exit(1)
    return xml_file


#
# Prunes any simplesect nodes that have a title node containing the text 'Wiki Examples'
#
def process_xml(root, debug=False):
    if debug:
        print (root)

    # Remove the parents of 'Wiki Examples' title nodes
    wiki_sect = root.xpath('//title[contains(., "Wiki Examples")]/..')
    for ws in wiki_sect:
        par = ws.getparent()

        if debug:
            print ('\nBefore:', etree.tostring(par), '\n')
        par.remove(ws)
        if debug:
            print ('After:', etree.tostring(par), '\n')


#
# Recursively traverse an XML subtree to produced a formated description string
#
def traverse_xml(xml_node, depth=0, debug=False):
    result = ""
    prefix = {'listitem': "\\li ",
              'itemizedlist': "\n",
              'computeroutput': " ",
              'programlisting': "\\code\n"}
    postfix = {'para': "\n\n",
               'title': "\n",
               'computeroutput': " ",
               'ref': " ",
               'ulink': " ",
               'codeline': "\n",
               'programlisting': "\\endcode\n",
               'sp': " "}
    if debug:
        print("\nNode: ", xml_node)
        for i in range(depth):
            sys.stdout.write("  ")
        print(xml_node.tag, ": ", xml_node.attrib, xml_node.text)

    # handle simplesection nodes (particularly See nodes)
    if xml_node.tag == 'simplesect':
        if xml_node.attrib['kind'] == 'see':
            for child in xml_node:
                child_desc = traverse_xml(child, depth + 1, debug)
                if (len(child_desc)):
                    result = result + "\\see " + child_desc + "\n"
                    if debug:
                        print("See result: ", repr(result))
            return result
        else:
            # other, non-see, simplesect nodes
            result = result + "\\" + xml_node.attrib['kind'] + " "

    # iterate through the children
    for child in xml_node:
        if debug:
            print ("Child: ", child, child.tag, child.text)
        result = result + traverse_xml(child, depth + 1, debug)

    text = xml_node.text

    # handle formula nodes
    if xml_node.tag == 'formula':
        if debug:
            print(blue_text, "\nFormula", end_color)
            print(text)
        text = text.replace("\[", " \\f[", 1)
        text = text.replace("\\]", "\\f] ")
        text = text.replace("$", "\\f$") + " "
        if debug:
            print(text)

    # add the prefix and postfixes
    if xml_node.tag in prefix:
        result = prefix[xml_node.tag] + result
    if text is not None:
        result = text + result
    if xml_node.tag in postfix:
        result = result + postfix[xml_node.tag]
    if xml_node.tail:
        result = result + xml_node.tail

    # finished
    if debug:
        for i in range(depth):
            sys.stdout.write("  ")
        print ("result: ", repr(result))

    return result


#
# Call the recursive XML traversal function to get a description string,
# then clean up some white space
#
def format_description(xml_node, debug):
    result = traverse_xml(xml_node, 0, debug)
    result = result.replace("\n\n\n", "\n\n")
    result = re.sub(' +', ' ', result)
    result = result.strip()
    return result


#
#  Our main program
#
if __name__ == '__main__':

    # settings
    debug = False
    backup_flag = False
    blue_text = "\033[0;34m"
    end_color = "\033[0m"

    # Parse command line arguments
    try:
        opts, args = getopt.getopt(sys.argv[1:], "hD", ["help", "debug", ])
    except getopt.GetoptError as err:
        print (str(err))
        usage()
        sys.exit(2)

    for o, a in opts:
        if o in ("-D", "--debug"):
            print ("Debug")
            debug = True
        elif o in ("-b", "--backup"):
            backup_flag = True
        elif o in ("-h", "--help"):
            usage()
            sys.exit()
        else:
            assert False, "unhandled options"

    if len(args) != 2:
        print (args)
        usage()
        sys.exit(1)

    sitk_json = args[0]
    itk_path = args[1]

    #
    # Load the JSON file
    with io.open(sitk_json, "r", encoding='utf8') as fp:
        json_obj = json.load(fp, object_pairs_hook=OrderedDict)

    #print(json.dumps(json_obj, indent=1))

    # Find and load the XML file
    xml_file = find_xml_file(itk_path, json_obj)
    tree = etree.parse(xml_file)
    root = tree.getroot()

    # Filter the XML to remove extraneous stuff
    process_xml(root, debug)

    # Get the class brief description node
    briefdesc = root.find('./compounddef/briefdescription')
    # Get the class detailed description node
    detaileddesc = root.find('./compounddef/detaileddescription')

    #
    # Set the class detailed description in the JSON to the formated text from the XML tree
    #
    json_obj['detaileddescription'] = format_description(detaileddesc, debug)
    print (
        blue_text,
        "\nDetailed description\n",
        end_color,
        repr(
            json_obj['detaileddescription']))

    #
    # Set the class brief description in the JSON to the formated text from the XML tree
    #
    json_obj['briefdescription'] = format_description(briefdesc, debug)
    print (
        blue_text,
        "\nBrief description\n",
        end_color,
        repr(
            json_obj['briefdescription']))

    #
    # Build a dict of class member functions in the XML
    #
    member_dict = {}
    print (blue_text, "\nBuilding XML member function dict\n", end_color)
    for m in root.findall(
            "./compounddef/sectiondef/memberdef[@kind='function']"):
        name_node = m.find("./name")
        if name_node is not None:
            print (name_node.text, " : ", repr(m))
            member_dict[name_node.text] = m

    #
    # Loop through the class members and measurements in the JSON
    #
    print (blue_text, "\nJSON class members and measurements\n", end_color)
    obj_list = []

    # Create a list of members and measurements
    if 'members' in json_obj:
        obj_list = obj_list + json_obj['members']
    if 'measurements' in json_obj:
        obj_list = obj_list + json_obj['measurements']

    for m in obj_list:
        name = m['name']
        print(blue_text, name, end_color)

        # Iterate through the possible prefixes
        for prefix in ["", "Set", "Get"]:
            funcname = prefix + name

            if funcname in member_dict:
                # find the item in the XML that corresponds to the JSON member
                # function
                m_xml = member_dict[funcname]
                print (funcname, repr(m_xml))

                # pull the brief and detailed descriptions from the XML to the
                # JSON
                for dtype in ['briefdescription', 'detaileddescription']:
                    desc_prefix = dtype + prefix
                    print("Setting", desc_prefix)
                    desc_node = m_xml.find("./" + dtype)
                    if desc_node is not None:
                        m[desc_prefix] = format_description(desc_node, debug)
                        print("  ", m[desc_prefix])
                    else:
                        print ("./" + dtype + " not found in the XML")

    #
    # We done.  Write out the results.
    #
    if backup_flag:
        os.rename(sitk_json, sitk_json + ".BAK")

    with io.open(sitk_json, "w", encoding='utf8') as fp:
        json_string = json.dumps(json_obj, indent=2, separators=(u',', u' : '), ensure_ascii=False)
        fp.write(json_string)
        print (u"", file=fp)
