# =========================================================================
#
#  Copyright NumFOCUS
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0.txt
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
# =========================================================================

"""Exercise release staging through its CLI, using synthetic file contents."""

import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

HELPER = Path(__file__).resolve().parents[1] / "PrepareReleaseAssets.py"
ABC_SHA256 = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"
EMPTY_SHA256 = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
HELLO_SHA256 = "5891b5b522d5df086d0ff0b110fbd9d21bb4fc7163af34d08286a2e846f6be03"


class PrepareReleaseAssetsTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory(prefix="simpleitk-release-tests-")
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.source = self.root / "source assets"
        self.source.mkdir()
        self.destination = self.root / "release assets"

    def write_asset(self, name, content, source=None):
        path = (self.source if source is None else source) / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(content)
        return path

    def run_helper(self, source=None, destination=None):
        return subprocess.run(
            [
                sys.executable,
                str(HELPER),
                str(self.source if source is None else source),
                str(self.destination if destination is None else destination),
            ],
            cwd=self.root,
            capture_output=True,
            text=True,
            timeout=15,
            check=False,
        )

    def assert_failure(self, result, category):
        self.assertNotEqual(result.returncode, 0, result.stdout)
        self.assertRegex(result.stderr.lower(), category)

    def make_symlink(self, target, link, directory=False):
        try:
            link.symlink_to(target, target_is_directory=directory)
        except (NotImplementedError, OSError) as error:
            self.skipTest(f"Symlinks are unavailable: {error}")

    def test_stages_flat_assets_with_exact_sorted_manifest(self):
        self.write_asset("runner two/alpha.zip", b"")
        self.write_asset("runner one/nested/beta.tar.gz", b"hello\n")
        self.write_asset("runner three/Zeta.whl", b"abc")

        result = self.run_helper()

        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(
            {path.name for path in self.destination.iterdir()},
            {"Zeta.whl", "alpha.zip", "beta.tar.gz", "SHA256SUMS"},
        )
        self.assertEqual((self.destination / "Zeta.whl").read_bytes(), b"abc")
        self.assertEqual((self.destination / "alpha.zip").read_bytes(), b"")
        self.assertEqual((self.destination / "beta.tar.gz").read_bytes(), b"hello\n")
        self.assertEqual(
            (self.destination / "SHA256SUMS").read_bytes(),
            (
                f"{ABC_SHA256}  Zeta.whl\n"
                f"{EMPTY_SHA256}  alpha.zip\n"
                f"{HELLO_SHA256}  beta.tar.gz\n"
            ).encode("ascii"),
        )

    def test_hashes_binary_contents_across_read_boundaries(self):
        payload = b"\x00\xff\r\n" * 300000
        self.write_asset("binary.whl", payload)

        result = self.run_helper()

        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual((self.destination / "binary.whl").read_bytes(), payload)
        self.assertEqual(
            (self.destination / "SHA256SUMS").read_text(),
            "8e041aae8c78249acbef9acda966c52c01d8cf8557c35c145667a144285a2518"
            "  binary.whl\n",
        )

    def test_selects_only_regular_case_sensitive_archive_extensions(self):
        self.write_asset("keep.zip", b"abc")
        for name in (
            "README.md",
            "SHA256SUMS",
            "notes # label.txt",
            "archive.WHL",
            "archive.ZIP",
            "archive.GZ",
            "archive.Zip",
            "archive.whl.sig",
            "archive.gz.tmp",
            "archive.tgz",
        ):
            self.write_asset(name, b"ignored")
        (self.source / "directory.whl").mkdir()
        if hasattr(os, "mkfifo"):
            os.mkfifo(self.source / "pipe.gz")

        result = self.run_helper()

        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(
            {path.name for path in self.destination.iterdir()},
            {"keep.zip", "SHA256SUMS"},
        )
        self.assertEqual(
            (self.destination / "SHA256SUMS").read_text(),
            f"{ABC_SHA256}  keep.zip\n",
        )

    def test_skips_file_symlinks_and_does_not_follow_directory_symlinks(self):
        regular = self.write_asset("nested/real.whl", b"abc")
        outside = self.root / "outside assets"
        outside.mkdir()
        external = self.write_asset("external.zip", b"hello\n", source=outside)
        self.make_symlink(regular, self.source / "file-link.whl")
        self.make_symlink(external, self.source / "external-link.zip")
        self.make_symlink(outside / "missing", self.source / "broken.zip")
        self.make_symlink(outside, self.source / "directory-link", directory=True)
        self.make_symlink(
            self.source / "nested", self.source / "mirror", directory=True
        )

        result = self.run_helper()

        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(
            {path.name for path in self.destination.iterdir()},
            {"real.whl", "SHA256SUMS"},
        )
        self.assertFalse((self.destination / "real.whl").is_symlink())
        self.assertEqual((self.destination / "real.whl").read_bytes(), b"abc")

    def test_rejects_no_matches_without_creating_destination(self):
        for ignored_only in (False, True):
            with self.subTest(ignored_only=ignored_only):
                if ignored_only:
                    self.write_asset("README.md", b"not a release asset")
                    self.write_asset("archive.ZIP", b"case matters")
                result = self.run_helper()
                self.assert_failure(result, r"(?:no|without).*(?:asset|archive|match)")
                self.assertFalse(os.path.lexists(self.destination))

    def test_rejects_missing_and_non_directory_sources(self):
        ordinary_file = self.root / "ordinary file"
        ordinary_file.write_bytes(b"preserve me")
        for source in (self.root / "missing source", ordinary_file):
            with self.subTest(source=source.name):
                result = self.run_helper(source=source)
                self.assert_failure(
                    result, r"source|directory|does not exist|not found"
                )
                self.assertFalse(os.path.lexists(self.destination))
        self.assertEqual(ordinary_file.read_bytes(), b"preserve me")

    def test_rejects_duplicate_basenames_even_with_identical_contents(self):
        self.write_asset("one/duplicate.whl", b"abc")
        for content in (b"different contents", b"abc"):
            with self.subTest(content=content):
                self.write_asset("two/duplicate.whl", content)
                result = self.run_helper()
                self.assert_failure(result, r"duplicate|collision|collid")
                self.assertFalse(os.path.lexists(self.destination))

    def test_handles_case_distinct_source_archives_without_overwriting(self):
        self.write_asset("one/SimpleITK-3.0.0.tar.gz", b"abc")
        self.write_asset("two/simpleitk-3.0.0.tar.gz", b"hello\n")
        (self.root / "CaseProbe").write_bytes(b"filesystem probe")
        case_sensitive = not (self.root / "caseprobe").exists()

        result = self.run_helper()

        if case_sensitive:
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertEqual(
                (self.destination / "SimpleITK-3.0.0.tar.gz").read_bytes(), b"abc"
            )
            self.assertEqual(
                (self.destination / "simpleitk-3.0.0.tar.gz").read_bytes(), b"hello\n"
            )
            self.assertEqual(
                (self.destination / "SHA256SUMS").read_text(),
                f"{ABC_SHA256}  SimpleITK-3.0.0.tar.gz\n"
                f"{HELLO_SHA256}  simpleitk-3.0.0.tar.gz\n",
            )
        else:
            self.assert_failure(result, r"collision|collid|case.sensitive")
            self.assertFalse(os.path.lexists(self.destination))

    def test_rejects_unsafe_asset_names_before_creating_destination(self):
        names = (
            "package#label.zip",
            "package name.whl",
            "-option.gz",
            ".hidden.whl",
            "_leading.zip",
            "caf\N{LATIN SMALL LETTER E WITH ACUTE}.zip",
            "local+build.whl",
            "line\nbreak.zip",
        )
        for index, name in enumerate(names):
            with self.subTest(name=name):
                source = self.root / f"unsafe-source-{index}"
                self.write_asset("valid.whl", b"abc", source=source)
                self.write_asset(name, b"unsafe name", source=source)
                result = self.run_helper(source=source)
                self.assert_failure(
                    result,
                    r"unsafe|invalid.*(?:name|filename)|(?:name|filename).*invalid",
                )
                self.assertFalse(os.path.lexists(self.destination))

    def test_rejects_and_preserves_existing_destinations(self):
        self.write_asset("package.whl", b"abc")
        for kind in ("empty directory", "occupied directory", "file"):
            with self.subTest(kind=kind):
                destination = self.root / kind
                if kind == "file":
                    destination.write_bytes(b"existing output file")
                else:
                    destination.mkdir()
                    if kind == "occupied directory":
                        (destination / "SHA256SUMS").write_bytes(b"old manifest")
                        (destination / "package.whl").write_bytes(b"old asset")
                    expected = {
                        path.name: path.read_bytes() for path in destination.iterdir()
                    }

                result = self.run_helper(destination=destination)

                self.assert_failure(result, r"exist|already|overwrite")
                if kind == "file":
                    self.assertEqual(destination.read_bytes(), b"existing output file")
                else:
                    self.assertEqual(
                        {
                            path.name: path.read_bytes()
                            for path in destination.iterdir()
                        },
                        expected,
                    )

    def test_rejects_destination_inside_source_without_creating_parents(self):
        self.write_asset("package.whl", b"abc")
        for relative in ("staged", "missing parent/staged"):
            with self.subTest(relative=relative):
                result = self.run_helper(destination=self.source / relative)
                self.assert_failure(result, r"within|inside|outside|nested|contain")
                self.assertEqual(
                    {path.name for path in self.source.iterdir()}, {"package.whl"}
                )

    def test_rejects_destination_inside_source_through_symlink(self):
        self.write_asset("package.whl", b"abc")
        alias = self.root / "source alias"
        self.make_symlink(self.source, alias, directory=True)

        result = self.run_helper(destination=alias / "staged")

        self.assert_failure(result, r"within|inside|outside|nested|contain")
        self.assertFalse(os.path.lexists(self.source / "staged"))
        self.assertTrue(alias.is_symlink())

    def test_staged_copies_are_independent_of_later_source_changes(self):
        original = self.write_asset("nested/package.whl", b"abc")
        result = self.run_helper()
        self.assertEqual(result.returncode, 0, result.stderr)

        original.write_bytes(b"the source changed after staging")
        self.assertEqual((self.destination / "package.whl").read_bytes(), b"abc")
        original.unlink()
        self.assertEqual((self.destination / "package.whl").read_bytes(), b"abc")
        self.assertEqual(
            (self.destination / "SHA256SUMS").read_text(),
            f"{ABC_SHA256}  package.whl\n",
        )

    def check_with_system_verifier(self, command):
        self.write_asset("package.zip", b"abc")
        result = self.run_helper()
        self.assertEqual(result.returncode, 0, result.stderr)

        verified = subprocess.run(
            command,
            cwd=self.destination,
            capture_output=True,
            text=True,
            timeout=15,
            check=False,
        )
        self.assertEqual(verified.returncode, 0, verified.stdout + verified.stderr)

        (self.destination / "package.zip").write_bytes(b"changed staged bytes")
        tampered = subprocess.run(
            command,
            cwd=self.destination,
            capture_output=True,
            text=True,
            timeout=15,
            check=False,
        )
        self.assertNotEqual(tampered.returncode, 0, tampered.stdout)
        self.assertIn("package.zip", tampered.stdout + tampered.stderr)

    @unittest.skipUnless(shutil.which("sha256sum"), "sha256sum is not installed")
    def test_sha256sum_verifies_manifest_and_detects_tampering(self):
        self.check_with_system_verifier(
            [shutil.which("sha256sum"), "--check", "SHA256SUMS"]
        )

    @unittest.skipUnless(shutil.which("shasum"), "shasum is not installed")
    def test_shasum_verifies_manifest_and_detects_tampering(self):
        self.check_with_system_verifier(
            [shutil.which("shasum"), "-a", "256", "-c", "SHA256SUMS"]
        )

    def test_unreadable_asset_failure_leaves_no_partial_destination(self):
        self.write_asset("first.whl", b"abc")
        unreadable = self.write_asset("last.zip", b"hello\n")
        unreadable.chmod(0)
        try:
            try:
                with unreadable.open("rb") as stream:
                    stream.read(1)
            except PermissionError:
                pass
            else:
                self.skipTest("This runner can read files with no read permissions")

            result = self.run_helper()

            self.assert_failure(result, r"permission|denied|copy|read|stage|staging")
            self.assertFalse(os.path.lexists(self.destination))
        finally:
            unreadable.chmod(0o600)


if __name__ == "__main__":
    unittest.main()
