#!/usr/bin/env bash
#==========================================================================
#
#   Copyright NumFOCUS
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          http://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
#==========================================================================

# This script is a crude process which adds the Appache License boiler
# plate to the start of files. It has some ad-hoc rule for choosing
# the comment style needed based on the file extension.

# Usage: ApplyApacheLicense.sh file1.cxx file2.py ... fileN.ext



header_c='/*=========================================================================\
 *\
 *  Copyright NumFOCUS\
 *\
 *  Licensed under the Apache License, Version 2.0 (the "License");\
 *  you may not use this file except in compliance with the License.\
 *  You may obtain a copy of the License at\
 *\
 *         http://www.apache.org/licenses/LICENSE-2.0.txt\
 *\
 *  Unless required by applicable law or agreed to in writing, software\
 *  distributed under the License is distributed on an "AS IS" BASIS,\
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\
 *  See the License for the specific language governing permissions and\
 *  limitations under the License.\
 *\
 *=========================================================================*/\
'
header_pound='#=========================================================================\
 #\
 #  Copyright NumFOCUS\
 #\
 #  Licensed under the Apache License, Version 2.0 (the "License");\
 #  you may not use this file except in compliance with the License.\
 #  You may obtain a copy of the License at\
 #\
 #         http://www.apache.org/licenses/LICENSE-2.0.txt\
 #\
 #  Unless required by applicable law or agreed to in writing, software\
 #  distributed under the License is distributed on an "AS IS" BASIS,\
 #  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\
 #  See the License for the specific language governing permissions and\
 #  limitations under the License.\
 #\
 #=========================================================================\
'
header_lua='--=========================================================================\
 --\
 --  Copyright NumFOCUS\
 --\
 --  Licensed under the Apache License, Version 2.0 (the "License");\
 --  you may not use this file except in compliance with the License.\
 --  You may obtain a copy of the License at\
 --\
 --         http://www.apache.org/licenses/LICENSE-2.0.txt\
 --\
 --  Unless required by applicable law or agreed to in writing, software\
 --  distributed under the License is distributed on an "AS IS" BASIS,\
 --  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\
 --  See the License for the specific language governing permissions and\
 --  limitations under the License.\
 --\
 --=========================================================================\
'

while (( "$#" )); do

    f="$1"

    # extract the extension, removing the possible trailing .in
    ext="${f#*.}"
    ext="${ext%.in}"

    echo "FILE: ${1}"
    echo "extension: ${ext}"

    header="$header_c"

    if [ -d "$1" ]
    then
        shift
        continue
    fi

    if [ "$1" = "CMakeLists.txt" ]
    then
        shift
        continue
    fi

    if [ "${ext}" = "lua" ]
    then
        header="${header_lua}"
    fi


    if [ "${ext}" = "py" ] ||
        [ "${ext}" = "R" ] ||
        [ "${ext}" = "tcl" ] ||
        [ "${ext}" = "rb" ] ||
        [ "${ext}" = "sh" ] ||
        [ "${ext}" = "cmake" ]
    then
        header="${header_pound}"
    fi

    grep -q 'Copyright NumFOCUS' "$1" || (
    sed '1 i\
'"$header" $1 > $1.tmp && mv $1.tmp $1 )
    shift
done