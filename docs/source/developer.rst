Developer
========================

.. note:: This document is a work in progress. It is not yet complete.
    It is intended to provide a high-level overview of the codebase and
    development process for new contributors.



How to Make a Release
========================

For major and minor releases, several release candidates are created to verify the release
before the final release. The release candidates allow of testing the release in the wild
and in other projects. It also allows for testing the release in the CI/CD pipeline
and in the release process itself.

Before tag a release the SimpleITK JSON doc strings, and ensure data is synchronized with mirrors.

Steps to tag a pre-release (alpha, beta, or release candidate)
-------------------------------------------------------------------

1. Pre-releases are tagged on the main branch. The tags are of the format
   ``vX.Y.Z{a|b|rc}N`` where ``X`` is the major version, ``Y`` is the minor version,
   ``Z`` is the patch version, ``a``/``b``/``rc`` denotes an alpha, beta, or release
   candidate respectively, and ``N`` is the alpha/beta/release-candidate number.
   Alpha and beta tags are typically used earlier in a development cycle to
   exercise new features, while release candidates are used to verify a release
   that is otherwise considered feature-complete.

   The pre-release is tagged with the following command:

   .. code-block:: shell

      git tag -a vX.Y.Z{a|b|rc}N -m "SimpleITK X.Y.Z Alpha/Beta/Release Candidate N"
      git push origin vX.Y.Z{a|b|rc}N

3. The GHA workflow is triggered by the tag and the pre-release is built and
   published to Test PyPI and a GitHub release is created.
4. Verify all artifacts are created and uploaded to the GitHub release. This include Python wheels, Java binaries,
    C# binaries, Doxygen, source, and data files.

Steps to tag a major or minor release
---------------------------------------

1. The release is tagged on the main branch. The tags are of the format
   ``vX.Y.Z`` where ``X`` is the major version, ``Y`` is the minor version,
   and ``Z`` is the patch version. Additionally, the release branch is updated
   to point to the release tag.

   The follow command update local branches and then tags the release:

   .. code-block:: shell

        git fetch --all
        git checkout main
        git pull origin --ff-only main
        git push origin
        git checkout release
        git pull origin --ff-only release
        git merge --ff-only main
        git tag -a vX.Y.Z -m "SimpleITK X.Y.Z Release"
        git push origin release vX.Y.Z

2. The first commit on the main branch must update the version number in Version.cmake
   to the next planned release version.

   Edit and update the version number in the file ``Version.cmake``, then
   commit the change to the main branch directly. The commit message should be of the form
   ``Bump development version to X.Y.Z``.

   This commit should then be directly pushed to the origin by passing PR requirements.

Steps to tag a patch release
-----------------------------

Changes for patch releases are made to the release branch. Generally a change is first proposed and merged to the main
branch. If the change was not based of the release branch, it is cherry-picked onto a new branch before making another
pull request to the release branch. After a patch is merged into the release branch, the release branch is
merged back into the main branch. If there are conflicts then the "-s ours" strategy is used on the main branch.

To make a patch release, the following steps are taken:

1. On a local release branch, the Version.cmake file is updated to the new patch version.
   The commit message should be of the form ``Setting version to X.Y.Z``.

2. The release branch is tagged with the new patch version.
   The tag is of the form ``vX.Y.Z`` where ``X`` is the major version, ``Y`` is the minor version,
   and ``Z`` is the patch version.

   The following command tags the release:

   .. code-block:: shell

      git tag vX.Y.Z -m "SimpleITK X.Y.Z Release"
      git push origin vX.Y.Z

3. The release branch is merged back into the main branch.
    The following command merges the release branch into the main branch:

    .. code-block:: shell

        git checkout main
        git pull origin --ff-only main
        git merge -s ours release
        git push origin main


Action to Complete Release Process
----------------------------------

1. Add release notes for the version:

   a. Fetch the auto-generated notes from the GitHub release (created by the tag-triggered
      workflow) with ``Utilities/Maintenance/DownloadReleaseNotes.sh``, or
      ``gh release view vX.Y.Z --json body --jq '.body'``.
   b. Prepend a ``# SimpleITK Release vX.Y.Z`` header and add a "Release Highlights" section
      above the auto-generated "What's Changed" list.
   c. Save the result as ``docs/source/release_notes/notes-vX.Y.Z.md``.
   d. Add an entry for the new file at the top of the toctree in
      ``docs/source/release_notes/index.rst`` (newest release first).

2. The produced doxygen needs to be uploaded to SimpleITK/SimpleITK.github.io
3. Read the docs mark the release for build and publish
4. Update SimpleITKPythonPackage source based
5. Update SimpleITKRInstaller
6. Publish the release on GitHub
7. Publish wheels to PyPI with twine
8. Update conda-forge/libsimpleitk-feedstock then conda-forge/simpleitk-feedstock
9. Announce the release on ITK Discourse.
