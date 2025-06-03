#!/usr/bin/env python
import argparse
import json
import os
import sys
import logging
from jsonschema import validate, ValidationError, SchemaError, Draft7Validator

def main():
    parser = argparse.ArgumentParser(description="Validate JSON files against a JSON schema.")
    parser.add_argument('schema', help='Path to the JSON schema file')
    parser.add_argument('json_files', nargs='+', help='One or more JSON files to validate')
    parser.add_argument('-v', '--verbose', action='count', default=0, help='Increase output verbosity (can use -vv)')
    parser.add_argument('-q', '--quiet', action='store_true', help='Suppress non-error output')
    parser.add_argument('--stop-on-error', action='store_true', help='Stop on the first error encountered')
    args = parser.parse_args()

    # Set up logging level
    if args.quiet:
        loglevel = logging.ERROR
    elif args.verbose >= 2:
        loglevel = logging.DEBUG
    elif args.verbose == 1:
        loglevel = logging.INFO
    else:
        loglevel = logging.WARNING
    logging.basicConfig(level=loglevel, format='%(levelname)s: %(message)s')

    # Check schema file exists
    if not os.path.isfile(args.schema):
        logging.error(f"Schema file '{args.schema}' does not exist.")
        sys.exit(1)

    # Load schema
    try:
        with open(args.schema, 'r', encoding='utf-8') as f:
            schema = json.load(f)
        logging.info(f"Loaded schema from '{args.schema}'")
    except Exception as e:
        logging.error(f"Failed to load schema: {e}")
        sys.exit(1)

    # Validate schema itself
    try:
        Draft7Validator.check_schema(schema)
    except SchemaError as e:
        logging.error(f"Invalid JSON schema: {e}")
        sys.exit(1)
    except Exception as e:
        logging.debug(f"Schema validation: {e}")

    # Validate each JSON file
    all_valid = True
    for json_file in args.json_files:
        if not os.path.isfile(json_file):
            logging.error(f"JSON file '{json_file}' does not exist.")
            all_valid = False
            if args.stop_on_error:
                sys.exit(1)
            continue
        try:
            with open(json_file, 'r', encoding='utf-8') as f:
                data = json.load(f)
            logging.info(f"Loaded JSON file '{json_file}'")
        except Exception as e:
            logging.error(f"Failed to load JSON file '{json_file}': {e}")
            all_valid = False
            if args.stop_on_error:
                sys.exit(1)
            continue
        try:
            validate(instance=data, schema=schema)
            logging.info(f"{json_file}: valid.")
        except ValidationError as e:
            logging.error(f"{json_file}: INVALID. {e.message}")
            all_valid = False
            if args.stop_on_error:
                sys.exit(1)
        except Exception as e:
            logging.error(f"{json_file}: Error during validation: {e}")
            all_valid = False
            if args.stop_on_error:
                sys.exit(1)

    if not all_valid:
        sys.exit(1)

if __name__ == "__main__":
    main()
