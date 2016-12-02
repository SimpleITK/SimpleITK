--!/usr/bin/env lua
--=========================================================================
--
--  Copyright Insight Software Consortium
--
--  Licensed under the Apache License, Version 2.0 (the "License");
--  you may not use this file except in compliance with the License.
--  You may obtain a copy of the License at
--
--         http://www.apache.org/licenses/LICENSE-2.0.txt
--
--  Unless required by applicable law or agreed to in writing, software
--  distributed under the License is distributed on an "AS IS" BASIS,
--  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
--  See the License for the specific language governing permissions and
--  limitations under the License.
--
--=========================================================================

-- This script parses a JSON file, and print specified json fields provided by JSON paths.
--
-- It is currently expected that path specified is the lua table access
-- string to the correct field. There currently is no real validation
-- or error checking.

package.path = debug.getinfo(1).source:match("@?(.*/)")..'?.lua;' .. package.path

require "json"

if #arg < 2 then
   print("usage: "..arg[0].." [json file] [json path]+")
   os.exit(1)
end

--print("Reading \""..arg[1].."\"...")

local f = assert(io.open(arg[1]))

local str = f:read("*all")
f:close()

json_table = decode(str)

bad_count = 0

for i=2,#arg do
    json_path=arg[i]
    cmd = loadstring("return json_table."..json_path)
    if not cmd then
        io.stderr:write("Warning: bad path -> "..json_path.."\n")
        bad_count = bad_count+1
    else
        out = cmd()
        if not out then
            io.stderr:write(json_path.." NOT FOUND\n")
        else
            print(json_path..": \""..cmd().."\"")
        end
    end
end

os.exit( bad_count )
