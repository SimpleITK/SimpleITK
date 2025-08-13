import argparse
import json
from jinja2 import Environment, FileSystemLoader
import os
from typing import List
from pathlib import Path
import logging

import re
import yaml

# Constants for template generation
WORD_WRAP_WIDTH = 120
DOXYGEN_WORDWRAP_WIDTH = WORD_WRAP_WIDTH - 3 # Subtracting for the Doxygen comment prefix


def quote_string(s:str) -> str: # pragma: no cover
    """A Jinja2 filter that quotes a string."""
    if not isinstance(s, str):
        logging.error("Input must be a string.")
        return s
    return f'"{s}"'

def ruby_capitalize(s:str) -> str:
    """A Jinja2 filter that capitalizes the first letter of each word in a string."""
    if not isinstance(s, str):
        logging.error("Input must be a string.")
        return s
    def capitalize_first_letter(word):
        if len(word) > 1:
            return word[0].upper() + word[1:]
        else:
            return word.upper()

    return ' '.join(capitalize_first_letter(word) for word in s.split())

def regex_replace(s, find, replace):
    """An optimal and robust implementation of a Jinja2 regex filter."""
    if not isinstance(s, str):
        logging.error("Input must be a string.")
        return s
    if not isinstance(find, str) or not find.strip():
        logging.error("Regex pattern must be a non-empty string.")
        return s
    if not isinstance(replace, str):
        logging.error("Replacement must be a string.")
        return s
    try:
        pattern = re.compile(find)
        return pattern.sub(replace, s)
    except re.error as e:
        logging.error(f"Invalid regex pattern: {find}. Error: {e}")
        return s

def format_list(list_, pattern):
    """ Formats a list of strings using a given pattern.
    """
    return [pattern.format(s) for s in list_]

def load_configuration(config_file: Path):
    """Load configuration from a YAML file."""
    try:
        with open(config_file, 'r', encoding='utf-8') as f:
            if config_file.suffix.lower() in ['.yaml', '.yml']:
                return yaml.safe_load(f)
            else:
                logging.error(f"Unsupported configuration file format: {config_file.suffix}. Only YAML is supported.")
                return None
    except Exception as e:
        logging.error(f"Error loading configuration file {config_file}: {e}")
        return None

def expand_template(config_file:Path, template:Path, template_dirs: List[Path], output_file:Path, verbose= False, clobber:bool=True):
    """
    Expands a template using the provided YAML configuration and Jinja2.
    """
    # Load configuration
    filter_description = load_configuration(config_file)
    if filter_description is None:
        return -1

    # check all paths exist, print a warning if they do not
    for template_dir in template_dirs:
        if not os.path.exists(template_dir):
            logging.warning(f"Template directory {template_dir} does not exist.")

    # add directories to the Environment loader
    template_dirs = [Path(template_dir) for template_dir in template_dirs]
    env = Environment(loader=FileSystemLoader(template_dirs))

    env.filters['regex_replace'] = regex_replace
    env.filters['ruby_capitalize'] = ruby_capitalize
    env.filters['quote'] = quote_string
    env.filters['format_list'] = format_list

    # Add global constants for templates
    env.globals['DOXYGEN_WORDWRAP_WIDTH'] = DOXYGEN_WORDWRAP_WIDTH


    try:
        template_obj = env.get_template(str(template))

        # Check if the template file exists
        if not template_obj:
            logging.error(f"Template file {template} not found in the specified directories.")
            return -1


        # Render the template with the filter description
        output_content = template_obj.render(filter_description)
    except Exception as e:
        logging.error(f"Jinja2 error: {e}")
        return -1

    if output_file.exists() and not clobber:
        logging.error(f"Output file {output_file} already exists and cannot be overwritten.")
        return -1

    if output_file.exists():
        with open(output_file, 'r', encoding='utf-8') as f:
            existing_content = f.read()
        if existing_content == output_content:
            logging.info(f"Output file {output_file} already exists and content is identical. Skipping write.")
            return 0
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write(output_content)
    return 0


def main() -> int:
    parser = argparse.ArgumentParser(description="Expand a template using a YAML configuration file and Jinja2.")
    parser.add_argument("config_file", type=Path, help="Path to the YAML configuration file.")
    parser.add_argument("template", type=Path, help="JINJA template file")
    # Update the argument to accept a list of directories with multiple `-D` flags, allowing it to be used zero or more times.
    parser.add_argument("-D", "--template_dir", action='append', type=Path, default=[], help="Directory containing the main template files.")
    # add overwrite option defaulting to true and an additional no-overwrite option
    parser.add_argument("-o", "--overwrite", action='store_true', default=True, help="Overwrite the output file if it exists.")
    parser.add_argument("-n", "--no-overwrite", action='store_false', dest='overwrite', help="Do not overwrite the output file if it exists.")
    parser.add_argument("-v", "--verbose", action='store_true', help="Enable verbose output.")



    parser.add_argument("output_file", type=Path, help="Path to the output file to be generated.")

    args = parser.parse_args()

    template = Path(args.template)

    return expand_template(args.config_file,
                    template,
                    args.template_dir,
                    args.output_file,
                    verbose=args.verbose,
                    clobber=args.overwrite)

if __name__ == "__main__":
    import sys

    sys.exit(main())
