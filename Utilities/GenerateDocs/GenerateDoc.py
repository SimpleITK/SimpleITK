#!/usr/bin/env python

import sys
import json
import yaml
import re
import argparse
from pathlib import Path
from xml.etree import ElementTree
from collections import OrderedDict
from typing import Dict, List, Any, Union


# YAML block style classes
class folded_str(str):
    pass

class literal_str(str):
    pass

def folded_presenter(dumper, data):
    return dumper.represent_scalar('tag:yaml.org,2002:str', data, style='>')

def literal_presenter(dumper, data):
    return dumper.represent_scalar('tag:yaml.org,2002:str', data, style='|')

yaml.add_representer(folded_str, folded_presenter)
yaml.add_representer(literal_str, literal_presenter)

def apply_block_styles(obj: Any, *, folded_style_keys: List[str] = None, literal_style_keys: List[str] = None) -> Any:
    """Apply block styles to specified keys in a data structure."""
    if folded_style_keys is None:
        folded_style_keys = []
    if literal_style_keys is None:
        literal_style_keys = []
        
    if isinstance(obj, dict):
        result = {}
        for k, v in obj.items():
            if k in folded_style_keys and isinstance(v, str):
                # Convert to folded string for block-style YAML
                result[k] = folded_str(v)
            elif k in literal_style_keys and isinstance(v, str):
                # Convert to literal string for block-style YAML
                result[k] = literal_str(v)
            else:
                result[k] = apply_block_styles(v, folded_style_keys=folded_style_keys, literal_style_keys=literal_style_keys)
        return result
    elif isinstance(obj, list):
        return [apply_block_styles(item, folded_style_keys=folded_style_keys, literal_style_keys=literal_style_keys) for item in obj]
    else:
        return obj


#
#  This script updates the documentation of a SimpleITK class in its
#  JSON or YAML file.  The documentation is pulled from the corresponding ITK
#  class XML file.  The SimpleITKClass.json/yaml file is modified in place.
#
#  The script is a re-write of the GenerateDocumentation.groovy script in python.
#
#  usage: GenerateDoc.py <SimpleITKClass.json|yaml> <Path/To/ITK-build/With/Doxygen>
#


def parse_arguments():
    """Parse command line arguments using argparse."""
    parser = argparse.ArgumentParser(
        description='Update the documentation of a SimpleITK class in its JSON or YAML file. '
                   'The documentation is pulled from the corresponding ITK class XML file.',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog='This script is a re-write of the GenerateDocumentation.groovy script in Python.'
    )

    parser.add_argument('sitk_file', type=Path,
                       help='Path to the SimpleITK class JSON or YAML file')
    parser.add_argument('itk_path', type=Path,
                       help='Path to ITK build directory with Doxygen XML files')
    parser.add_argument('-D', '--debug',
                       action='store_true',
                       help='Enable debugging messages')
    parser.add_argument('-b', '--backup',
                       action='store_true',
                       help='Backup JSON/YAML file before modification')

    return parser.parse_args()



def find_xml_file(itk_path: Path, data_obj: Dict[str, Any]) -> Path:
    itk_name = data_obj.get("itk_name", "")
    name = data_obj.get("name", "")
    template_code_filename = data_obj.get("template_code_filename", "")

    xml_file_options = [
        f"classitk_1_1{itk_name}.xml",
        f"classitk_1_1{name}{template_code_filename}.xml",
        f"classitk_1_1{name}.xml",
    ]

    for xf in xml_file_options:
        xname = itk_path / xf
        if xname.is_file():
            try:
                with open(xname, "r", encoding="utf-8"):
                    print(f"xml file: {xname}")
                    return xname
            except OSError as e:
                print(f"Failed to open file: {xname} - {e}")

    print(f"Tried to read a file for {name}")
    print(xml_file_options)
    sys.exit(1)


def load_data_file(file_path: Path) -> Union[Dict[str, Any], OrderedDict]:
    """Load a JSON or YAML file and return the data."""
    file_ext = file_path.suffix.lower()

    with open(file_path, "r", encoding="utf-8") as fp:
        if file_ext == '.json':
            return json.load(fp, object_pairs_hook=OrderedDict)
        elif file_ext in ('.yaml', '.yml'):
            return yaml.load(fp, Loader=yaml.SafeLoader)
        else:
            raise ValueError(f"Unsupported file format: {file_ext}. Expected .json or .yaml/.yml")


def save_data_file(file_path: Path, data_obj: Union[Dict[str, Any], OrderedDict], backup: bool = False) -> None:
    """Save data to a JSON or YAML file with appropriate formatting."""
    file_ext = file_path.suffix.lower()

    if backup:
        backup_path = file_path.with_suffix(f"{file_path.suffix}.BAK")
        file_path.rename(backup_path)

    with open(file_path, "w", encoding="utf-8") as fp:
        if file_ext == '.json':
            json_string = json.dumps(
                data_obj, indent=2, separators=(",", " : "), ensure_ascii=False
            )
            fp.write(json_string)
            print("", file=fp)
        elif file_ext in ('.yaml', '.yml'):
            # Apply block styles for documentation fields
            folded_keys = ["detaileddescription", "detaileddescriptionSet", "detaileddescriptionGet"]
            literal_keys = ["custom_itk_cast", "custom_set_input"]
            styled_data = apply_block_styles(data_obj, folded_style_keys=folded_keys, literal_style_keys=literal_keys)

            yaml_content = yaml.dump(styled_data, default_flow_style=False, sort_keys=False, width=120)
            fp.write(yaml_content)
        else:
            raise ValueError(f"Unsupported file format: {file_ext}. Expected .json or .yaml/.yml")


def process_xml(root: ElementTree.Element, debug: bool = False) -> None:
    """Prune any simplesect nodes that have a title node containing the text 'Wiki Examples'."""
    if debug:
        print(root)

    # Find nodes with 'Wiki Examples' and 'ITK Sphinx Examples' in their title
    wiki_sect = root.findall(".//title[.='Wiki Examples']/..")
    wiki_sect += root.findall(".//title[.='ITK Sphinx Examples']/..")
    for ws in wiki_sect:
        par = ws.getparent()

        if debug:
            print(f"\nBefore: {ElementTree.tostring(par)}\n")
        par.remove(ws)
        if debug:
            print(f"After: {ElementTree.tostring(par)}\n")


def traverse_xml(xml_node: ElementTree.Element, depth: int = 0, debug: bool = False) -> str:
    """Recursively traverse an XML subtree to produce a formatted description string."""
    result = ""
    prefix = {
        "listitem": "\\li ",
        "itemizedlist": "\n",
        "computeroutput": " ",
        "programlisting": "\\code\n",
    }
    postfix = {
        "para": "\n\n",
        "title": "\n",
        "computeroutput": " ",
        "ref": "",
        "ulink": " ",
        "codeline": "\n",
        "programlisting": "\\endcode\n",
        "sp": " ",
    }
    if debug:
        print(f"\nNode: {xml_node}")
        print("  " * depth + f"{xml_node.tag}: {xml_node.attrib} {xml_node.text}")

    # handle simplesection nodes (particularly See nodes)
    if xml_node.tag == "simplesect":
        if xml_node.attrib["kind"] == "see":
            for child in xml_node:
                child_desc = traverse_xml(child, depth + 1, debug)
                if len(child_desc):
                    result = result + f"\\see {child_desc}\n"
                    if debug:
                        print(f"See result: {repr(result)}")
            return result
        else:
            # other, non-see, simplesect nodes
            result = result + f"\\{xml_node.attrib['kind']} "

    # iterate through the children
    for child in xml_node:
        if debug:
            print(f"Child: {child} {child.tag} {child.text}")
        result = result + traverse_xml(child, depth + 1, debug)

    text = xml_node.text

    # handle formula nodes
    if xml_node.tag == "formula":
        if debug:
            print(f"{blue_text}\nFormula{end_color}")
            print(text)
        text = text.replace("\\[", " \\f[", 1)
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
        print("  " * depth + f"result: {repr(result)}")

    return result


def format_description(xml_node: ElementTree.Element, debug: bool = False) -> str:
    """Call the recursive XML traversal function to get a description string, then clean up whitespace."""
    result = traverse_xml(xml_node, 0, debug)
    # Replace more than 2 consecutive newlines with two
    result = re.sub(r'\n\n+', '\n\n', result)
    result = re.sub(" +", " ", result)
    # Remove any whitespace (spaces, tabs) before newlines
    result = re.sub(r'[ \t]+\n', '\n', result)
    result = result.strip()

    return result


#
#  Our main program
#
if __name__ == "__main__":

    # Parse command line arguments using argparse
    args = parse_arguments()

    # Extract settings from parsed arguments
    debug = args.debug
    backup_flag = args.backup
    sitk_file = args.sitk_file
    itk_path = args.itk_path

    # Color constants for output
    blue_text = "\033[0;34m"
    end_color = "\033[0m"

    #
    # Load the JSON or YAML file
    data_obj = load_data_file(sitk_file)

    # print(json.dumps(data_obj, indent=1))

    # Find and load the XML file
    xml_filename = find_xml_file(itk_path, data_obj)
    with open(xml_filename, "r", encoding="utf-8") as xml_file:
        tree = ElementTree.parse(xml_file)
    root = tree.getroot()

    # Filter the XML to remove extraneous stuff
    process_xml(root, debug)

    # Get the class brief description node
    briefdesc = root.find("./compounddef/briefdescription")
    # Get the class detailed description node
    detaileddesc = root.find("./compounddef/detaileddescription")

    #
    # Set the class detailed description in the data to the formatted text from the XML tree
    #
    data_obj["detaileddescription"] = format_description(detaileddesc, debug)
    print(f"{blue_text}\nDetailed description\n{end_color}{repr(data_obj['detaileddescription'])}")

    #
    # Set the class brief description in the data to the formatted text from the XML tree
    #
    data_obj["briefdescription"] = format_description(briefdesc, debug)
    print(f"{blue_text}\nBrief description\n{end_color}{repr(data_obj['briefdescription'])}")

    #
    # Build a dict of class member functions in the XML
    #
    member_dict = {}
    print(f"{blue_text}\nBuilding XML member function dict\n{end_color}")
    for m in root.findall("./compounddef/sectiondef/memberdef[@kind='function']"):
        name_node = m.find("./name")
        if name_node is not None:
            print(f"{name_node.text} : {repr(m)}")
            member_dict[name_node.text] = m

    #
    # Loop through the class members and measurements in the data
    #
    print(f"{blue_text}\nClass members and measurements\n{end_color}")
    obj_list = []

    # Create a list of members and measurements
    if "members" in data_obj:
        obj_list.extend(data_obj["members"])
    if "measurements" in data_obj:
        obj_list.extend(data_obj["measurements"])

    for m in obj_list:
        name = m["name"]
        print(f"{blue_text}{name}{end_color}")

        # Iterate through the possible prefixes
        for prefix in ["", "Set", "Get"]:
            funcname = f"{prefix}{name}"

            if funcname in member_dict:
                # find the item in the XML that corresponds to the JSON member
                # function
                m_xml = member_dict[funcname]
                print(f"{funcname} {repr(m_xml)}")

                # pull the brief and detailed descriptions from the XML to the
                # data object
                for dtype in ["briefdescription", "detaileddescription"]:
                    desc_prefix = f"{dtype}{prefix}"
                    print(f"Setting {desc_prefix}")
                    desc_node = m_xml.find(f"./{dtype}")
                    if desc_node is not None:
                        m[desc_prefix] = format_description(desc_node, debug)
                        print(f"  {m[desc_prefix]}")
                    else:
                        print(f"./{dtype} not found in the XML")

    #
    # We done.  Write out the results.
    #
    save_data_file(sitk_file, data_obj, backup_flag)
