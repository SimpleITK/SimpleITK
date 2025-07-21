#!/usr/bin/env python3
"""
Script to validate JSON/YAML configuration files against a JSON schema.
"""

import argparse
import json
import os
import sys
import logging
import pathlib
from jsonschema import validate, ValidationError, SchemaError, Draft7Validator

try:
    import yaml
    YAML_SUPPORT = True
except ImportError:
    YAML_SUPPORT = False


def load_config(file_path):
    """Load a configuration file (JSON or YAML) based on its extension."""
    suffix = pathlib.Path(file_path).suffix.lower()

    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            if suffix in ['.yaml', '.yml'] and YAML_SUPPORT:
                return yaml.safe_load(f)
            else:
                return json.load(f)
    except Exception as e:
        raise RuntimeError(f"Failed to load configuration file '{file_path}': {e}")


def validate_config(schema_file, config_file, verbose=False):
    """Validate a config file against a schema."""

    # Load schema
    try:
        with open(schema_file, 'r', encoding='utf-8') as f:
            schema = json.load(f)
        if verbose:
            logging.info(f"Loaded schema from '{schema_file}'")
    except Exception as e:
        raise RuntimeError(f"Failed to load schema: {e}")

    # Validate schema itself
    try:
        Draft7Validator.check_schema(schema)
    except SchemaError as e:
        raise RuntimeError(f"Invalid JSON schema: {e}")

    # Load and validate the config file
    try:
        config_data = load_config(config_file)
        if verbose:
            logging.info(f"Loaded configuration file '{config_file}'")
    except Exception as e:
        raise RuntimeError(str(e))

    # Perform validation
    validate(instance=config_data, schema=schema)
    return True


def main():
    """Main entry point for the script."""
    parser = argparse.ArgumentParser(
        description="Validate JSON/YAML files against a JSON schema."
    )
    parser.add_argument('schema', help='Path to the JSON schema file')
    parser.add_argument('config_files', nargs='+',
                        help='One or more JSON/YAML files to validate')
    parser.add_argument('-v', '--verbose', action='count', default=0,
                        help='Increase output verbosity (can use -vv)')
    parser.add_argument('-q', '--quiet', action='store_true',
                        help='Suppress non-error output')
    parser.add_argument('--stop-on-error', action='store_true',
                        help='Stop on the first error encountered')
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

    # Check if YAML is supported
    if not YAML_SUPPORT:
        logging.warning("PyYAML not installed, YAML validation not available. "
                        "Only JSON files will be validated.")

    # Validate each config file
    all_valid = True
    for config_file in args.config_files:
        if not os.path.isfile(config_file):
            logging.error(f"File '{config_file}' does not exist.")
            all_valid = False
            if args.stop_on_error:
                sys.exit(1)
            continue

        # Skip YAML files if YAML is not supported
        if (pathlib.Path(config_file).suffix.lower() in ['.yaml', '.yml'] and
            not YAML_SUPPORT):
            logging.error(f"Skipping YAML file '{config_file}': PyYAML not installed")
            all_valid = False
            continue

        try:
            validate_config(args.schema, config_file, args.verbose >= 1)
            logging.info(f"{config_file}: valid.")
        except ValidationError as e:
            logging.error(f"{config_file}: INVALID. {e.message}")
            if len(e.path) > 0:
                logging.error(f"  Path: {'.'.join(str(p) for p in e.path)}")
            all_valid = False
            if args.stop_on_error:
                sys.exit(1)
        except Exception as e:
            logging.error(f"{config_file}: Error during validation: {e}")
            all_valid = False
            if args.stop_on_error:
                sys.exit(1)

    if not all_valid:
        sys.exit(1)


if __name__ == "__main__":
    main()
