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


import os
import sys
import logging
import SimpleITK as sitk


class SimpleitkWarningRedirector:
    """
    Context manager which re-routes the file descriptors for the C/C++ outputs
    to stdout, stderr but keeps those used by Python intact. This allows
    the user to record warnings issued by the underlying C++ code as part of the
    Python logging framework. Note that the C++ warnings will always be saved to
    the log file, unlike the finer control available via the Python logging
    setLevel mechanism.
    """

    def __init__(self, filename):
        sys.stdout.flush()
        sys.stderr.flush()
        self.logfile = os.open(filename, os.O_WRONLY | os.O_APPEND | os.O_CREAT)

    def __enter__(self):
        # Assuming that for all operating systems, stdout file descriptor
        # is 1 and stderr file descriptor is 2
        self.orig_stdout = os.dup(1)
        self.orig_stderr = os.dup(2)
        self.new_stdout = os.dup(1)
        self.new_stderr = os.dup(2)
        os.dup2(self.logfile, 1)
        os.dup2(self.logfile, 2)
        sys.stdout = os.fdopen(self.new_stdout, "w")
        sys.stderr = os.fdopen(self.new_stderr, "w")

    def __exit__(self, exc_type, exc_val, exc_tb):
        sys.stdout.flush()
        sys.stderr.flush()

        os.dup2(self.orig_stdout, 1)
        os.dup2(self.orig_stderr, 2)
        os.close(self.orig_stdout)
        os.close(self.orig_stderr)

        os.close(self.logfile)


log_file_name = "program.log"

logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)
formatter = logging.Formatter(
    "%(asctime)s | %(levelname)s | %(message)s", "%m-%d-%Y %H:%M:%S"
)
file_handler = logging.FileHandler(log_file_name)
# Set the file handler log level to info, so it doesn't pass all messages
# logger sends (only those INFO and above, ignores DEBUG level messages).
file_handler.setLevel(logging.INFO)
file_handler.setFormatter(formatter)
logger.addHandler(file_handler)

with SimpleitkWarningRedirector(log_file_name):
    print("I'm on stdout.", file=sys.stdout)
    print("I'm on stderr.", file=sys.stderr)
    logger.debug(
        "1. debug message. Only appears in log file if you changed file_handler log level to DEBUG."
    )
    logger.info("2. information message.")
    # There is no DICOM series in the current directory, the underlying C++ code issues a warning.
    sitk.ImageSeriesReader_GetGDCMSeriesFileNames(".")
    logger.info("3. information message.")
sys.exit(0)
