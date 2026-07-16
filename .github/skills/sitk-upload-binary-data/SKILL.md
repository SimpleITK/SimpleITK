---
name: sitk-upload-binary-data
description: 'Upload binary testing data to SimpleITK ExternalData repository. Use when: adding test data, uploading binary file, creating content link, new test input, ExternalData upload, sha512 content link.'
argument-hint: 'Relative path to binary file, e.g. Testing/Data/Baseline/MyFilter_output.nrrd'
---

# Upload Binary Data to SimpleITK ExternalData

Upload binary files (test inputs, baseline images, etc.) to the
`SimpleITK/SimpleITKExternalData` GitHub repository by computing their
SHA-512 hash, placing them in the `.ExternalData` object store, creating
content link files, and opening a draft PR.

## When to Use

- Adding new test input images or baseline outputs
- Uploading any binary file that should not be committed to the SimpleITK Git repo
- Replaces input file with a `.sha512` CMake ExternalData content link

## Required Tools

Verify these are available before proceeding:

| Tool | Purpose | Check command |
|------|---------|---------------|
| `git` | Repository operations | `git --version` |
| `gh` | GitHub CLI for forking/PRs | `gh auth status` |
| `sha512sum` or `shasum` | Compute file hashes | `sha512sum --version` (Linux) or `shasum --version` (macOS) |

## Background

Binary test data in SimpleITK uses
[CMake ExternalData](https://cmake.org/cmake/help/latest/module/ExternalData.html).
Content link files (e.g. `Testing/Data/Input/image.nrrd.sha512`) contain
only a 128-character lowercase hex **SHA-512** hash followed by a newline.
The `.ExternalData` directory at the SimpleITK source root is a clone of
`SimpleITK/SimpleITKExternalData` and also a local CMake ExternalData
object store (listed in `.gitignore`), so builds work immediately once a
file is placed there.

Always create `.sha512` content links and `SHA512/<hash>` objects. See
[resources/external-data-background.md](resources/external-data-background.md)
for full history, legacy considerations, and object store/URL resolution
details.

## Bundled Script

### `scripts/hash_and_stage.sh`

A bash script that handles hashing, copying, content-link creation, and
cleanup for one or more binary files. Run from the SimpleITK source root.

**Usage:**
```
bash .github/skills/sitk-upload-binary-data/scripts/hash_and_stage.sh <file1> [<file2> ...]
```

**What it does:**
1. Validates prerequisites (`sha512sum`, git repo, `.ExternalData` clone).
2. For each file:
   - Computes the SHA-512 hash via `sha512sum`.
   - Copies the binary to `.ExternalData/SHA512/<hash>` (skips if the
     hash already exists).
   - Writes `<file>.sha512` containing the 128-char hex hash + newline.
   - Removes the original binary file.
   - Notes any existing `.md5` content link for removal.
3. Prints suggested `git add` / `git rm` commands.

**Output labels:**
- `COPY` — binary copied to object store
- `SKIP` — hash already present, no copy needed
- `LINK` — `.sha512` content link created
- `DEL`  — original binary removed

**Does NOT:** create branches, commit, push, or open PRs — those steps
are performed separately (see Step 4 below).

**Exit codes:** non-zero on any error (missing file, bad `.ExternalData`
directory, missing `sha512sum`). The error message explains the problem.

## Procedure

Given one or more binary file paths relative to the SimpleITK source root.
Example: `Testing/Data/Baseline/BasicFilters_NormalizedCorrelationImageFilter_NoMask.nrrd`

### Step 1 — Verify the file exists

Confirm each binary file is present at the given path. If not, stop and
tell the user.

### Step 2 — Verify the `.ExternalData` clone and select a push remote

All commands run from the **SimpleITK source root**. First confirm
`.ExternalData` is a real git clone:

```bash
test -d .ExternalData/.git
```

If this fails, **stop** and tell the user:

> The `.ExternalData` directory must be a clone of
> `SimpleITK/SimpleITKExternalData`. To set it up, run:
>
> ```
> gh repo clone SimpleITK/SimpleITKExternalData .ExternalData
> ```

Otherwise, list its remotes to find one to push to:

```bash
git -C .ExternalData remote -v
```

- Ignore any remote pointing at `SimpleITK/SimpleITKExternalData` itself
  (typically `origin`/`upstream`) — that's the upstream, not a fork.
- If exactly one other remote remains, use its name as `<push-remote>`.
- Otherwise (zero or multiple candidates), ask the user which remote
  name to use as `<push-remote>`, listing whatever remote names were
  found. If none exist, tell the user they need to add one first (e.g.
  by running `gh repo fork --remote --remote-name <name>` themselves).

Use as `<push-remote>` in Step 4.

### Step 3 — Hash, copy, create content links, remove originals

Run the [bundled script](#bundled-script) from the SimpleITK source root:

```bash
bash .github/skills/sitk-upload-binary-data/scripts/hash_and_stage.sh \
  path/to/file1 [path/to/file2 ...]
```

Capture the hash from the script output (the `COPY` or `SKIP` line) or
read it from the generated `.sha512` file:

```bash
HASH=$(cat path/to/file.sha512)
```

If the script fails, read its error output and report to the user.

### Step 4 — Create branch, commit, and PR in ExternalData repo

All commands use `git -C .ExternalData` to stay in the source root.
Run from the **SimpleITK source root**:

```bash
git -C .ExternalData fetch origin
git -C .ExternalData checkout -B <branch-name> origin/main
git -C .ExternalData add SHA512/<hash>
git -C .ExternalData commit -m "Add <original-filename>"
git -C .ExternalData push --force-with-lease <push-remote> HEAD:<branch-name>
```

The `gh` CLI does not support `-C`, so use a subshell for PR creation.
The subshell does **not** change the parent shell's working directory:

```bash
(cd .ExternalData && gh pr create --repo SimpleITK/SimpleITKExternalData \
  --title "Add <original-filename>" \
  --body "Binary testing data for SimpleITK." \
  --draft)
```

**Branch naming**: Use the sanitized original filename (replace dots and
special chars with hyphens, no prefix). For multiple files use
`upload-N-files`.

**Commit message**: `Add filename1, filename2, ...` — include original
filenames so reviewers know what the data is.

### Step 5 — Stage the content link in SimpleITK

Back in the SimpleITK source root:

```bash
git add -- path/to/file.sha512
```


### Step 6 — Report to user

Summarize:
- Content link created at `<path>.sha512`
- Data placed in `.ExternalData/SHA512/<hash>` (builds work locally now)
- Draft PR opened on `SimpleITK/SimpleITKExternalData` (include URL)
- Remind: data won't be available via S3/CMake download until the
  ExternalData PR is merged


# Troubleshooting Resources
- Additional background information is available in [resources/external-data-background.md](resources/external-data-background.md).
