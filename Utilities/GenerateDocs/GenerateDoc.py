#!/usr/bin/env python

from __future__ import print_function
import os, sys, io, json, re
import xml.etree.ElementTree as ET
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

if len(sys.argv) != 3:
    print("usage: GenerateDoc.py <SimpleITKClass.json> <Path/To/ITK-build/With/Doxygen>\n")

sitk_json = sys.argv[1]
itk_path  = sys.argv[2]

blue_text = "\033[0;34m"
end_color = "\033[0m"

# Load the JSON file
with open(sitk_json, "r") as fp:
  json_obj = json.load(fp, object_pairs_hook=OrderedDict)

#print(json.dumps(json_obj, indent=1))


itk_name = ''
if 'itk_name' in json_obj:
  itk_name = json_obj['itk_name']

name = ''
if 'name' in json_obj:
  name = json_obj['name']

template_code_filename = ''
if 'template_code_filename' in json_obj:
  template_code_filename = json_obj['template_code_filename']

  XMLFileOptions = ["classitk_1_1" + itk_name + ".xml",
                    "classitk_1_1" + name + template_code_filename + ".xml",
                    "classitk_1_1" + name + ".xml"]
#print( XMLFileOptions )


# Find the XML file
XMLFile = None
for xf in XMLFileOptions:
  xname = itk_path + '/' + xf
  if os.path.isfile(xname):
    try:
      XMLFile = io.open(xname, "r")
      print("xml file: ", xname)
    except:
      XMLFile = None
      print("no xml file: ", xname)

if not XMLFile:
  print( "Tried to read a file for " + name)
  print(XMLFileOptions)
  sys.exit ( 1 )


# Load the XML file
tree = ET.parse(XMLFile)
root = tree.getroot()


#
# traverse an XML subtree to produced a formated description string
#
def traverseXML( xml_node, depth=0, Debug=False ):
  result = ""
  prefix = { 'listitem' : "\\li ",
             'itemizedlist' : "\n",
             'computeroutput' : " ",
             'programlisting' : "\\code\n"}
  postfix = { 'para' : "\n\n",
              'title' : "\n",
              'computeroutput' : " ",
              'ref' : " ",
              'ulink' : " ",
              'codeline' : "\n",
              'programlisting' : "\\endcode\n",
              'sp' : " "}
  if Debug:
    print( "\nNode: ", xml_node )
    for i in range(depth):
      sys.stdout.write("  ")
    print( xml_node.tag, ": ", xml_node.attrib, xml_node.text)

  # handle simplesection nodes (particularly See nodes)
  if xml_node.tag == 'simplesect':
    if xml_node.attrib['kind'] == 'see':
      for child in xml_node:
        child_desc = traverseXML( child, depth+1 )
        if (len(child_desc)):
          result = result + "\\see " + child_desc + "\n"
          if Debug:
            print("See result: ", repr(result))
      return result
    else:
      result = result + "\\" + xml_node.attrib['kind'] + " "

  # iterate through the children
  for child in xml_node:
    if Debug:
      print ("Child: ", child, child.text)
    result = result + traverseXML(child, depth+1 )

  text = xml_node.text

  # handle formula nodes
  if xml_node.tag == 'formula':
    if Debug:
      print(blue_text, "\nFormula", end_color)
      print(text)
    text = text.replace("\[", " \\f[", 1)
    text = text.replace( "\\]", "\\f] " )
    text = text.replace( "$", "\\f$" ) +  " "
    if Debug:
      print(text)


  # add the prefix and postfixes
  if xml_node.tag in prefix:
    result = prefix[xml_node.tag] + result
  if text != None:
    result = text + result
  if xml_node.tag in postfix:
    result = result + postfix[xml_node.tag]
  if xml_node.tail:
    result = result + xml_node.tail

  # finished
  if Debug:
    for i in range(depth):
      sys.stdout.write("  ")
    print ("result: ", repr(result))

  return result


# Call the recursive XML traversal function, then clean up some white space
def formatDescription( xml_node ):
  result = traverseXML( xml_node )
  result = result.replace("\n\n\n", "\n\n")
  result = re.sub( ' +', ' ', result)
  result = result.strip()
  return result


# Class brief description
briefdesc = root.find( './compounddef/briefdescription' )
# Class detailed description
detaileddesc = root.find( './compounddef/detaileddescription' )



#
# Set the class detailed description in the JSON to the formated text from the XML tree
#
json_obj['detaileddescription'] = formatDescription(detaileddesc)
print ( blue_text, "\nDetailed description\n", end_color, repr(json_obj['detaileddescription']) )

#
# Set the class brief description in the JSON to the formated text from the XML tree
#
json_obj['briefdescription'] = formatDescription(briefdesc)
print ( blue_text, "\nBrief description\n", end_color, repr(json_obj['briefdescription']) )


#
# Build a dict of class member functions in the XML
#
member_dict = {}
print ( blue_text, "\nBuilding XML member function dict\n", end_color )
for m in root.findall("./compounddef/sectiondef/memberdef[@kind='function']"):
  name_node = m.find("./name")
  if name_node != None:
    print (name_node.text, " : ", repr(m))
    member_dict[name_node.text] = m


#
# Loop through the class members and measurements in the JSON
#
print ( blue_text, "\nJSON class members and measurements\n", end_color )
obj_list = []

# Create a list of members and measurements
if 'members' in json_obj:
  obj_list = obj_list + json_obj['members']
if 'measurements' in json_obj:
  obj_list = obj_list + json_obj['measurements']


for m in obj_list:
  name = m['name']
  print( blue_text, name, end_color )

  # Iterate through the possible prefixes
  for prefix in [ "", "Set", "Get" ]:
    funcname = prefix+name

    if funcname in member_dict:
      # find the item in the XML that corresponds to the JSON member function
      m_xml = member_dict[funcname]
      print (funcname, repr(m_xml))

      # pull the brief and detailed descriptions from the XML to the JSON
      for dtype in ['briefdescription', 'detaileddescription']:
          desc_prefix = dtype + prefix
          print( "Setting", desc_prefix )
          desc_node = m_xml.find("./"+dtype)
          if desc_node != None:
            m[desc_prefix] = formatDescription( desc_node )
            print( "  ", m[desc_prefix] )
          else:
            print ("./"+dtype+ " not found in the XML")


#
# We done.  Write out the results.
#
backup_flag = False
if backup_flag:
  os.rename(sitk_json, sitk_json+".BAK")

fp = file(sitk_json, "w")
json.dump(json_obj, fp, indent=2, separators=(',', ' : '))
print ( "", file=fp )
fp.close()
