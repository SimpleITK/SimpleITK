#!/usr/bin/env python3
# ==========================================================================
#
#   Copyright NumFOCUS
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          https://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
# ==========================================================================
#
# Validate the layout of a commit message: a non-empty subject line
# (8-78 characters, no leading/trailing space) followed by a blank line
# separating it from an optional free-form body.
#
# Adapted from ITK's Python commit-message hook (Utilities/Hooks in the
# ITK repository), dropping ITK's mandatory subject-line prefix convention
# (BUG:/ENH:/etc.), which is not used in SimpleITK, and the "kw-" naming
# convention.

import os
import re
import subprocess
import sys

from pathlib import Path


DEFAULT_LINE_LENGTH: int = 78


def die(message, commit_msg_path):
    print("commit-msg hook failure", file=sys.stderr)
    print("-----------------------", file=sys.stderr)
    print(message, file=sys.stderr)
    print("-----------------------", file=sys.stderr)
    print(
        f"""
To continue editing, run the command
  git commit -e -F "{commit_msg_path}"
(assuming your working directory is at the top).""",
        file=sys.stderr,
    )
    sys.exit(1)


def get_max_length():
    try:
        result = subprocess.run(
            ["git", "config", "--get", "hooks.commit-msg.maxLength"],
            capture_output=True,
            text=True,
            check=True,
        )
    except subprocess.CalledProcessError:
        return DEFAULT_LINE_LENGTH
    return int(result.stdout.strip())


def main():
    git_dir_path: Path = Path(os.environ.get("GIT_DIR", ".git")).resolve()
    commit_msg_path: Path = git_dir_path / "COMMIT_MSG"

    if len(sys.argv) < 2:
        die(f"Usage: {sys.argv[0]} <git_commit_message_file>", commit_msg_path)

    input_file: Path = Path(sys.argv[1])
    if not input_file.exists():
        die(
            f"Missing input_file {sys.argv[1]} for {sys.argv[0]} processing",
            commit_msg_path,
        )
    max_subjectline_length: int = get_max_length()

    with open(input_file) as f_in:
        original_input_file_lines: list[str] = f_in.readlines()

    # Prepare a copy of the message:
    #  - drop leading blank lines
    #  - strip comment lines
    #  - stop before the patch text some editors insert (as with
    #    `git commit --verbose`)
    input_file_lines: list[str] = []
    raw_subject_line: str = ""
    for raw_line in original_input_file_lines:
        test_line = raw_line.strip()
        if test_line.startswith("diff --git"):
            break
        is_empty_line_before_subject: bool = (
            len(input_file_lines) == 0 and len(test_line) == 0
        )
        if test_line.startswith("#") or is_empty_line_before_subject:
            continue
        if not input_file_lines:
            # Keep the subject line's original, not-yet-trimmed form so
            # leading/trailing whitespace can still be detected below.
            raw_subject_line = raw_line.rstrip("\n")
        input_file_lines.append(f"{test_line}\n")

    with open(commit_msg_path, "w") as f_out:
        f_out.writelines(input_file_lines)

    if not input_file_lines:
        die("The commit message must not be empty.", commit_msg_path)

    subject_line: str = raw_subject_line

    if len(subject_line) < 8:
        die(
            f"The first line must be at least 8 characters:\n--------\n{subject_line}\n--------",
            commit_msg_path,
        )
    if (
        len(subject_line) > max_subjectline_length
        and not subject_line.startswith("Merge ")
        and not subject_line.startswith("Revert ")
    ):
        die(
            f"The first line may be at most {max_subjectline_length} characters:\n"
            + "-" * max_subjectline_length
            + f"\n{subject_line}\n"
            + "-" * max_subjectline_length,
            commit_msg_path,
        )
    if re.match(r"^[ \t]|[ \t]$", subject_line):
        die(
            f"The first line may not have leading or trailing space:\n[{subject_line}]",
            commit_msg_path,
        )
    del subject_line

    if len(input_file_lines) > 1:
        second_line: str = input_file_lines[1].strip()
        if len(second_line) != 0:
            die(
                f'The second line must be empty:\n{second_line}',
                commit_msg_path,
            )
        del second_line

    # Any further lines are the free-form commit body and are not
    # validated further.


if __name__ == "__main__":
    main()
