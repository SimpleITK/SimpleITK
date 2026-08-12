"""
Scikit-build-core dynamic-metadata provider that delegates version
computation to CMake, so the wheel's PKG-INFO "Version:" field matches
SimpleITK.__version__ from the real CMake build (see
CMake/sitkVersionDriver.cmake, Version.cmake, sitkSourceVersion.cmake,
sitkPythonVersion.cmake).

    [tool.scikit-build.metadata.version]
    provider = "sitk_version_provider"
    provider-path = "CMake"
    driver-script = "sitkVersionDriver.cmake"  # optional, relative to provider-path

"driver-script" is optional and defaults to "sitkVersionDriver.cmake".
"""

from __future__ import annotations

import shutil
import subprocess
import tempfile
from pathlib import Path

__all__ = ["dynamic_metadata"]

_THIS_DIR = Path(__file__).resolve().parent
_SOURCE_DIR = _THIS_DIR.parent
_DEFAULT_DRIVER_SCRIPT = "sitkVersionDriver.cmake"


def __dir__() -> list[str]:
    return __all__


def dynamic_metadata(
    field: str,
    settings: dict[str, object] | None = None,
) -> str:
    if field != "version":
        raise ValueError("sitk_version_provider only supports the 'version' field")

    settings = dict(settings or {})
    driver_script_name = settings.pop("driver-script", _DEFAULT_DRIVER_SCRIPT)
    if settings:
        raise ValueError(
            f"sitk_version_provider: unknown setting(s) {sorted(settings)}"
        )

    driver_script = _THIS_DIR / driver_script_name
    if not driver_script.is_file():
        raise ValueError(
            f"sitk_version_provider: driver-script {driver_script_name!r} "
            f"not found at {driver_script}"
        )

    cmake_exe = shutil.which("cmake")
    if cmake_exe is None:
        raise RuntimeError(
            "sitk_version_provider: could not find a 'cmake' executable on "
            "PATH. CMake is required to compute the SimpleITK version "
            "(see CMake/sitkVersionDriver.cmake)."
        )

    with tempfile.TemporaryDirectory(prefix="sitk-version-") as tmpdir:
        output_file = Path(tmpdir) / "version.txt"
        result = subprocess.run(
            [
                cmake_exe,
                f"-DSITK_SOURCE_DIR={_SOURCE_DIR}",
                f"-DSITK_VERSION_OUTPUT_FILE={output_file}",
                "-P",
                str(driver_script),
            ],
            capture_output=True,
            text=True,
            check=False,
        )

        if result.returncode != 0 or not output_file.is_file():
            raise ValueError(
                "sitk_version_provider: failed to compute the SimpleITK "
                f"version via {driver_script}.\n\n"
                "Make sure you're building from a fully intact git "
                "repository or an official 'git archive' source tarball "
                "with .git_archival.txt placeholders expanded. GitHub's "
                "auto-generated zip download and a checkout missing both "
                ".git and an expanded .git_archival.txt will not work.\n\n"
                f"--- cmake stdout ---\n{result.stdout}\n"
                f"--- cmake stderr ---\n{result.stderr}\n"
            )

        version = output_file.read_text(encoding="utf-8").strip()

    if not version:
        raise ValueError(
            "sitk_version_provider: CMake produced an empty version string. "
            f"See {driver_script} for how SimpleITK derives "
            "its version from git tags."
        )
    return version
