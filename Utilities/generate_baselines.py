#!/usr/bin/env python3
"""Generate baseline images for all filter examples that produce output images."""

import argparse
import os
import subprocess
import sys
from pathlib import Path

import yaml

try:
    from yaml import CSafeLoader as Loader
except ImportError:
    from yaml import SafeLoader as Loader


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source-dir", default=".", type=Path,
                        help="SimpleITK source directory")
    parser.add_argument("--data-dir", required=True, type=Path,
                        help="ExternalData Testing/Data directory (contains Input/)")
    parser.add_argument("--baseline-dir", default=None, type=Path,
                        help="Output baseline directory (default: <source>/Testing/Data/Baseline)")
    parser.add_argument("--python", default=sys.executable,
                        help="Python executable to use")
    parser.add_argument("--filter", default=None,
                        help="Only generate baseline for this filter name")
    args = parser.parse_args()

    source_dir = args.source_dir.resolve()
    data_dir = args.data_dir.resolve()
    baseline_dir = (args.baseline_dir or source_dir / "Testing/Data/Baseline").resolve()
    baseline_dir.mkdir(parents=True, exist_ok=True)

    filter_list_yaml = source_dir / "Examples/example_filter_list.yaml"
    yaml_dir = source_dir / "Code/BasicFilters/yaml"

    filter_list = yaml.load(filter_list_yaml.read_text(), Loader=Loader).get("filters", [])
    if args.filter:
        filter_list = [f for f in filter_list if f == args.filter]

    ok, skip, fail = [], [], []

    for fname in filter_list:
        yaml_file = yaml_dir / f"{fname}.yaml"
        if not yaml_file.exists():
            skip.append((fname, "no yaml"))
            continue

        fd = yaml.load(yaml_file.read_text(), Loader=Loader)

        if fd.get("no_return_image", False):
            skip.append((fname, "no_return_image"))
            continue

        ex = fd.get("example") or (fd.get("tests") or [None])[0]
        if not ex:
            skip.append((fname, "no test data"))
            continue

        input_paths = [str(data_dir / p) for p in ex.get("inputs", [])]
        script = source_dir / f"Examples/{fname}/{fname}.py"
        baseline = str(baseline_dir / f"Example_{fname}.nrrd")

        if not script.exists():
            skip.append((fname, "script not generated yet"))
            continue

        if Path(baseline).exists():
            skip.append((fname, "baseline already exists"))
            continue

        cmd = [args.python, str(script)] + input_paths + [baseline]
        env = {**os.environ, "SITK_NOSHOW": "YES"}

        print(f"Generating {fname}...", flush=True)
        result = subprocess.run(cmd, env=env, capture_output=True, text=True)
        if result.returncode == 0:
            ok.append(fname)
            print(f"  OK -> {baseline}")
        else:
            last_err = (result.stderr.strip().splitlines() or ["(no output)"])[-1]
            fail.append((fname, last_err))
            print(f"  FAILED: {last_err}", flush=True)

    print(f"\nSummary: {len(ok)} generated, {len(skip)} skipped, {len(fail)} failed")
    if fail:
        print("Failed:")
        for f, e in fail:
            print(f"  {f}: {e}")


if __name__ == "__main__":
    main()
