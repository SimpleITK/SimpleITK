# SimpleITK Sphinx Documentation

Guidelines for building and structuring the SimpleITK Sphinx documentation in this `docs/` directory.

## Pre-requisite setup

Use the python version specified in `.readthedocs.yml`.

- Create a Python virtual environment in the `docs/` directory (e.g. `python -m venv .venv`)
- Activate the virtual environment (e.g. `source .venv/bin/activate`)
- Install the dependencies (e.g. `pip install -r requirements.txt`)

## Build

```bash
cd docs
make html          # output: build/html/index.html
make clean         # remove build artifacts
```

## Structure

The `docs/` directory is organized as follows:

- `Makefile` — Sphinx build entry point (`make html`, `make clean`)
- `requirements.txt` — Python dependencies for the docs build
- `source/` — Sphinx source files
  - `conf.py` — Sphinx config
  - `index.rst` — Main TOC
  - `release_notes/` — Release notes (`.md` files + `index.rst`)
  - `migration_guides/` — Migration guides
  - `images/` — Image assets referenced by `source/` pages; large binaries are content-linked via CMake `ExternalData` (`.sha512` files), the same mechanism used for `Testing/Data/Baseline`
  - `*.rst`/`*.md` — Content pages
- `build/html/` — Generated output (do not commit)


## `link_*.rst` Files

The `source/link_*.rst` files are thin shims that use `.. include::` to pull in
`Documentation.rst` files from the `Examples/` directory tree into the Sphinx doc build.

Example — `link_SimpleGaussian_docs.rst`:
```rst
.. include:: ../../Examples/SimpleGaussian/Documentation.rst
```

**Do not edit these files** — edit the source `Documentation.rst` in `Examples/` instead.
To add a new example to the docs, create a `link_{ExampleName}_docs.rst` that includes
the example's `Documentation.rst`.


## Notes

- Both `.rst` and `.md` files are supported
- `source/release_notes/` is excluded from the spell checker (`.pre-commit-config.yaml`)
- Release notes live in `source/release_notes/` as `notes-{tag}.md` files.
