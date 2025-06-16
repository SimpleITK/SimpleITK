#!/usr/bin/env python
#==========================================================================
#
#   Copyright NumFOCUS
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          http://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
#==========================================================================
import argparse
import json
import os
import sys
import logging
from collections import OrderedDict

def main():
    parser = argparse.ArgumentParser(description="Beautify JSON files with consistent formatting.")
    parser.add_argument('json_files', nargs='+', help='One or more JSON files to beautify')
    parser.add_argument('-v', '--verbose', action='count', default=0, help='Increase output verbosity (can use -vv)')
    parser.add_argument('-q', '--quiet', action='store_true', help='Suppress non-error output')
    parser.add_argument('--indent', type=int, default=2, help='Number of spaces for indentation (default: 2)')
    parser.add_argument('--stop-on-error', action='store_true', help='Stop on the first error encountered')
    args = parser.parse_args()

    # Set up the logging level
    if args.quiet:
        loglevel = logging.ERROR
    elif args.verbose >= 2:
        loglevel = logging.DEBUG
    elif args.verbose == 1:
        loglevel = logging.INFO
    else:
        loglevel = logging.WARNING
    logging.basicConfig(level=loglevel, format='%(levelname)s: %(message)s')

    # Process each JSON file
    all_success = True
    for json_file in args.json_files:
        if not os.path.isfile(json_file):
            logging.error(f"JSON file '{json_file}' does not exist.")
            all_success = False
            if args.stop_on_error:
                sys.exit(1)
            continue

        try:
            # Load JSON with OrderedDict to preserve key order
            logging.info(f"Processing '{json_file}'")
            with open(json_file, 'r', encoding='utf-8') as fp:
                json_data = json.load(fp, object_pairs_hook=OrderedDict)

            # Write beautified JSON back to the file
            with open(json_file, 'w', encoding='utf-8') as fp:
                json.dump(json_data, fp, indent=args.indent, separators=(",", ": "), ensure_ascii=False)
                # Add a final newline
                print("", file=fp)

            logging.info(f"Successfully beautified '{json_file}'")

        except json.JSONDecodeError as e:
            logging.error(f"Invalid JSON in '{json_file}': {e}")
            all_success = False
            if args.stop_on_error:
                sys.exit(1)
        except Exception as e:
            logging.error(f"Error processing '{json_file}': {e}")
            all_success = False
            if args.stop_on_error:
                sys.exit(1)

    if not all_success:
        sys.exit(1)

if __name__ == "__main__":
    main()
