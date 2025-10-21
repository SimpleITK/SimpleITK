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

""" A SimpleITK example that demonstrates how to adapt SimpleITK messages
    to be handled by a Python Logger object. """

import logging
import os
import SimpleITK as sitk


class SimpleITKLogger(sitk.LoggerBase):
    """
    Adapts SimpleITK messages to be handled by a Python Logger object.

    Allows using the logging module to control the handling of messages coming
    from ITK and SimpleTK. Messages such as debug and warnings are handled by
    objects derived from sitk.LoggerBase.

    The LoggerBase.SetAsGlobalITKLogger method must be called to enable
    SimpleITK messages to use the logger.

    The Python logger module adds a second layer of control for the logging
    level in addition to the controls already in SimpleITK.

    The "Debug" property of a SimpleITK object must be enabled (if
    available) and the support from the Python "logging flow" hierarchy
    to handle debug messages from a SimpleITK object.

    Warning messages from SimpleITK are globally disabled with
    ProcessObject:GlobalWarningDisplayOff.
    """

    _context_args = ("file", "line", "className", "objectAddress")

    def __init__(self, logger: logging.Logger = logging.getLogger("SimpleITK")):
        """
        Initializes with a Logger object to handle the messages emitted from
        SimpleITK/ITK.
        """
        super().__init__()
        self._logger = logger

    @property
    def logger(self):
        """ return the logger object """
        return self._logger

    @logger.setter
    def logger(self, logger):
        """ set the logger object """
        self._logger = logger

    def __enter__(self):
        """ Set this object as the global ITK logger. """
        self._old_logger = self.SetAsGlobalITKLogger()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        """ Restore the previous global ITK logger. """
        self._old_logger.SetAsGlobalITKLogger()
        del self._old_logger

    def DisplayText(self, message):
        """ Display text message. """
        extra = { key: None for key in self._context_args }
        self._logger.info(message, extra=extra)

    def DisplayErrorText(self,
                         message,
                         file = None,
                         line = None,
                         className = None,
                         objectAddress = None):
        """
        This python method signature will be called for both C++ overloaded DisplayErrorText methods. These additional context parameters can be passed to the logger as extra information.

        """
        extra = { key: locals()[key] for key in self._context_args }
        self._logger.error(message, extra=extra)

    def DisplayWarningText(self,
                           message,
                           file = None,
                           line = None,
                           className = None,
                        objectAddress = None):
        extra = { key: locals()[key] for key in self._context_args }
        self._logger.warning(message, extra=extra)

    def DisplayGenericOutputText(self,
                                 message,
                                 file = None,
                                 line = None):
        extra = { key: locals()[key] for key in ("file", "line") }
        self._logger.info(message, extra=extra)

    def DisplayDebugText(self,
                         message,
                         file = None,
                         line = None,
                         className = None,
                         objectAddress = None):

        extra = { key: locals()[key] for key in self._context_args }
        self._logger.debug(message, extra=extra)


# Enable all debug messages for all ProcessObjects, and procedures
sitk.ProcessObject.GlobalDefaultDebugOn()

# Construct a SimpleITK logger to Python Logger adaptor
sitkLogger = SimpleITKLogger()

# Configure ITK to use the logger adaptor
sitkLogger.SetAsGlobalITKLogger()

sitkLogger.DisplayText("check")

# Configure the Python root logger, enabling debug and info level messages.
# Note that if an ITK extra context is not provided, then the logging message will not occur due to the missing context keys.
logging.basicConfig(format="%(name)s [%(file)s#%(line)s] (%(levelname)s): %(message)s", level=logging.DEBUG)


img = sitk.GaborSource(size=[64, 64, 64], frequency=4.0 / 64)

with SimpleITKLogger(logging.getLogger("Show")) as showLogger:
    print(f"Logger name: {showLogger.GetName()}")

    if "SITK_NOSHOW" not in os.environ:
        sitk.Show(img, debugOn=True)
