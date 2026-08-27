# Background: CMake ExternalData in SimpleITK

This is auxiliary reference material for the `sitk-upload-binary-data`
skill. It is not needed for routine uploads — see `SKILL.md` for the
procedure.

## What is CMake ExternalData?

SimpleITK stores large/binary test data outside the Git repository using
the [CMake ExternalData](https://cmake.org/cmake/help/latest/module/ExternalData.html)
module
([background](https://blog.kitware.com/cmake-externaldata-using-large-files-with-distributed-version-control/)).
Instead of committing a binary, the repo commits a small **content link**
file containing only a hash of the binary's contents. At configure/build
time, CMake resolves each content link to the real file, fetching it from
a local object store or a remote URL if not already present.

## Content link format

- File name: `<original-name>.<algo-extension>`, e.g. `image.nrrd.sha512`.
- File content: a single lowercase hex hash string (128 chars for
  SHA-512) followed by a newline. No other metadata.
- `<algo-extension>` for SHA-512 is `.sha512`. The legacy MD5 extension
  was `.md5` (32 hex chars) — see [Legacy MD5](#legacy-md5-do-not-use-for-new-data) below.

## Object stores and URL resolution

Configured in [`CMake/sitkExternalData.cmake`](../../../../CMake/sitkExternalData.cmake).
CMake looks for objects, in order:

1. Local object stores in `ExternalData_OBJECT_STORES` (defaults to
   `${CMAKE_BINARY_DIR}/ExternalData/Objects`).
2. `${SimpleITK_SOURCE_DIR}/.ExternalData`, if present — a clone of
   `SimpleITK/SimpleITKExternalData` used as a local object store (this is
   why the upload skill copies binaries here: builds succeed immediately
   without needing a network download).
3. Remote URL templates (`%(algo)/%(hash)`), tried in order:
   - `https://simpleitk.s3.amazonaws.com/public/%(algo)/%(hash)` — S3
     mirror, synced from the `SimpleITKExternalData` repo by a GitHub
     Actions workflow on merge to `main`.
   - `https://simpleitk.org/SimpleITKExternalData/%(algo)/%(hash)` —
     GitHub Pages mirror.
   - `https://data.kitware.com:443/api/v1/file/hashsum/%(algo)/%(hash)/download` —
     Girder instance (legacy/shared ITK ecosystem source).
   - `https://insightsoftwareconsortium.github.io/ITKTestingData/%(algo)/%(hash)`
     and `https://itk.org/files/ExternalData/%(algo)/%(hash)` — ITK's own
     testing data mirrors (shared ecosystem fallback, rarely hit for
     SimpleITK-specific data).

## The `SimpleITK/SimpleITKExternalData` repository

Stores binaries in a flat layout: `SHA512/<hash>` (and, historically,
`MD5/<hash>`). The file name IS the hash; the file content IS the raw
binary. There is no other indexing — a hash is only discoverable by
already knowing it from a content link.

## Legacy MD5: do not use for new data

MD5 was the original ExternalData hash algorithm used by SimpleITK.
The project fully migrated to SHA-512 for all content links, completed by
a 2019 commit titled "Use only sha512 data file remove md5", which
removed every remaining `.md5` content link file from the source tree.

- **All `.md5` content links have been removed from the SimpleITK repo.**
  No `.md5` content link should ever be added or reintroduced.
- The `MD5/` directory still exists in the `SimpleITKExternalData` object
  store (and on S3) purely as a historical remnant — old binaries that
  were only ever referenced by now-deleted `.md5` links. These objects
  are inert: nothing in the current source tree points to them.
- **Never add, modify, or reference MD5 objects.** Always hash and stage
  new binaries as SHA-512 (`.sha512` content links, `SHA512/<hash>`
  object paths), per the main skill procedure.
- If you encounter a `.md5` content link anywhere in the tree, treat it
  as a bug — it should be re-hashed to SHA-512 and the `.md5` file
  removed.

## Unrelated: `IMAGE_MD5_COMPARE` CMake test macro

`CMake/sitkAddTest.cmake` has a per-test option named `IMAGE_MD5_COMPARE`
that compares a generated test output image against an expected MD5
hash string given directly in the test definition (via the
`sitkTestDriver --compare-MD5` flag). This is a lightweight image
regression check unrelated to the ExternalData content-link mechanism
described above — it does not read or write `.md5`/`.sha512` files or
the `.ExternalData` object store. Do not confuse the two when searching
the codebase for "md5".
