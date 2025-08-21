#!/usr/bin/env python3
"""
JSON to YAML Conversion Script

This script converts JSON configuration files to YAML format and renames them using git.

Prerequisites
-------------
Before using this script, make sure you have the required Python packages installed:

    pip install pyyaml

Usage
-----
To convert all JSON files in a directory:

    # Run with a dry run first to see what changes would be made
    ./convert_json_to_yaml.py --dry-run Code/BasicFilters/json

    # Run the actual conversion
    ./convert_json_to_yaml.py Code/BasicFilters/json

What the script does
--------------------
1. Searches for all `.json` files in the specified directory
2. Converts each file's content from JSON to YAML format
3. Writes the converted content to a new `.yaml` file

Options
-------
- `--dry-run`: Show what would be done without making changes
- `--clobber`: Allow overwriting existing YAML files

Example
-------
    # Convert a specific directory of JSON files
    ./convert_json_to_yaml.py /path/to/json/files

Note
----
This script creates YAML files alongside the existing JSON files.
Make sure to review the converted files before using them.
"""

import os
import sys
import json
import yaml
import argparse
import subprocess
import re
from pathlib import Path


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

def apply_block_styles(obj, *, folded_style_keys=[], literal_style_keys=[]):
    if isinstance(obj, dict):
        result = {}
        for k, v in obj.items():
            if k in folded_style_keys and isinstance(v, str):
                # Convert to folded string for block-style YAML
                v = re.sub(r'[ \t]+\n', '\n', v)
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


def convert_file(json_file_path, clobber=False, dry_run=False):
    """
    Convert a JSON file to YAML format and write it.

    Args:
        json_file_path: Path to the JSON file
        clobber: Whether to overwrite existing YAML files
        dry_run: If True, only test conversion but don't write files

    Returns:
        Path to the new YAML file
    """
    # Determine the new filename with .yaml extension
    yaml_file_path = str(json_file_path).replace('.json', '.yaml')

    # Check if YAML file already exists
    if os.path.exists(yaml_file_path) and not clobber:
        print(f"Skipping {json_file_path}: {yaml_file_path} already exists (use --clobber to overwrite)")
        return None

    print(f"Converting {json_file_path} to {yaml_file_path}")

    try:
        # Read the JSON file
        with open(json_file_path, 'r') as json_file:
            data = json.load(json_file)

        folded_keys = ["detaileddescription", "detaileddescriptionSet", "detaileddescriptionGet"]
        literal_keys = ["custom_itk_cast", "custom_set_input"]
        data = apply_block_styles(data, folded_style_keys=folded_keys, literal_style_keys=literal_keys)

        # Convert to YAML
        yaml_content = yaml.dump(data, default_flow_style=False, sort_keys=False, width=120)

        # If dry run, just test that we can write but don't actually write
        if dry_run:
            print(f"Would write {len(yaml_content)} bytes to {yaml_file_path}")
            return None

        # Write YAML file
        with open(yaml_file_path, 'w') as yaml_file:
            yaml_file.write(yaml_content)

        return yaml_file_path

    except Exception as e:
        print(f"Error converting {json_file_path}: {e}")
        return None


def main():
    parser = argparse.ArgumentParser(
        description="Convert JSON files to YAML and rename them using git."
    )
    parser.add_argument(
        "directory",
        type=str,
        help="Directory containing JSON files to convert"
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Show what would be done without making changes"
    )
    parser.add_argument(
        "--clobber",
        action="store_true",
        help="Allow overwriting existing YAML files"
    )
    args = parser.parse_args()

    # Normalize directory path
    directory = Path(args.directory)

    if not directory.exists() or not directory.is_dir():
        print(f"Error: Directory {directory} does not exist or is not a directory")
        return 1

    print(f"Searching for JSON files in {directory}")

    # Find all JSON files in the directory
    json_files = list(directory.glob("*.json"))

    if not json_files:
        print(f"No JSON files found in {directory}")
        return 0

    print(f"Found {len(json_files)} JSON files")

    if args.dry_run:
        print("Dry run mode - no changes will be made")

    converted_files = []
    failed_files = []
    skipped_files = []

    for json_file in json_files:
        result = convert_file(json_file, clobber=args.clobber, dry_run=args.dry_run)
        if result:
            converted_files.append(result)
        elif result is None and os.path.exists(str(json_file).replace('.json', '.yaml')):
            skipped_files.append(json_file)
        else:
            failed_files.append(json_file)

    # Summary
    print("\nConversion summary:")
    print(f"  Converted: {len(converted_files)} files")
    if skipped_files:
        print(f"  Skipped: {len(skipped_files)} files (already exist)")
    if failed_files:
        print(f"  Failed: {len(failed_files)} files")
        for file in failed_files:
            print(f"    - {file}")

    return 0 if not failed_files else 1


if __name__ == "__main__":
    sys.exit(main())
