Readme
======

This directory is for images used by for the Sphinx
documentation. Because images are relatively large files compared to
source code, they are not stored in the git repository. Instead we
just store SHA512 hashed of the files then utilize [CMake's
ExternalData](https://cmake.org/cmake/help/v3.10/module/ExternalData.html)
module to download the data.

To add data to this directory, the file must be uploaded to one of the
binary data stores, and the sha512 files are committed to the repository.
