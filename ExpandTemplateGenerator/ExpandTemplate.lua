package.path = debug.getinfo(1).source:match("@?(.*/)")..'?.lua;' .. package.path

require "json"

-- require 'Expand'
local strfind = string.find
local strsub  = string.sub
local push    = table.insert
local pop     = table.remove
local concat  = table.concat

-- based on http://lua-users.org/lists/lua-l/2010-06/msg00314.html
-- this assumes f is a function
local function findenv(f)
  local level = 1
  repeat
    local name, value = debug.getupvalue(f, level)
    if name == '_ENV' then return level, value end
    level = level + 1
  until name == nil
  return nil end
getfenv = function (f) return(select(2, findenv(f)) or _G) end
setfenv = function (f, t)
  local level = findenv(f)
  if level then debug.setupvalue(f, level, t) end
  return f end

local statements = {}
for w in string.gmatch('do if for while repeat', '%a+') do
  statements[w] = true
end

function expand(str, ...)
  assert(type(str)=='string', 'expecting string')
  local searchlist = table.pack(...)
  local estring,evar

  function estring(str)
    local b,e,i
    -- print ( "---------" )
    -- print ( "estring: starting with " .. str );
    -- print ( "---------" )
    b,i = strfind(str, '%$.')
    if not b then return str end

    local R, pos = {}, 1
    repeat
      b,e = strfind(str, '^%b{}', i)
      if b then
        -- Found dollar substitution ${dosomething}
        -- print ( '\testring: matched ^%b{} to "' .. string.sub ( str, b, e ) .. '"  calling evaluate recursively \n' )
        push(R, strsub(str, pos, b-2))
        push(R, evar(strsub(str, b+1, e-1)))
        i = e+1
        pos = i
      else
        b,e = strfind(str, '^%b()', i)
        if b then
          -- Found dollar command $(dosomething)
          -- print ( '\testring: matched ^%b() to "' .. string.sub ( str, b, e ) .. '"  calling evaluate recursively \n' )
          push(R, strsub(str, pos, b-2))
          push(R, evar(strsub(str, b+1, e-1)))
          i = e+1
          pos = i
        elseif strfind(str, '^%$', i) then
          -- Found double dollar ($$)
          -- print ( '\testring: matched ^%$ @ ' .. i .. ' to "' .. strsub ( str, pos ) .. '" returning ' .. strsub(str,pos,i-1) .. '\n');
          push(R, strsub(str, pos, i-1))
          i = i+1
          pos = i
        end
      end
      b,i = strfind(str, '%$.', i)
    until not b

    push(R, strsub(str, pos))
    return concat(R)
  end

  local function search(index)
    for _,symt in ipairs(searchlist) do
      local ts = type(symt)
      local value
      if     ts == 'function' then value = symt(index)
      elseif ts == 'table'
          or ts == 'userdata' then value = symt[index]
          if type(value)=='function' then value = value(symt) end
      else error'search item must be a function, table or userdata' end
      if value ~= nil then return value end
    end
    return nil
  end

  local function elist(var, v, str, sep)
    local tab = search(v)
    if tab == nil then
        io.stderr:write('Warning: unknown variable: '.. v .. ' used with foreach\n')
    end
    if tab then
      assert(type(tab)=='table', 'expecting table from: '.. var)
      local R = {}
      push(searchlist, 1, tab)
      push(searchlist, 1, false)
      for _,elem in ipairs(tab) do
        searchlist[1] = elem
        push(R, estring(str))
      end
      pop(searchlist, 1)
      pop(searchlist, 1)
      return concat(R, sep)
    else
      return ''
    end
  end

  local function get(tab,index)
    for _,symt in ipairs(searchlist) do
      local ts = type(symt)
      local value
      if     ts == 'function' then value = symt(index)
      elseif ts == 'table'
          or ts == 'userdata' then value = symt[index]
      else error'search item must be a function, table or userdata' end
      if value ~= nil then
        tab[index] = value  -- caches value and prevents changing elements
        return value
      end
    end
  end

  function evar(var)
    if strfind(var, '^[_%a][_%w]*$') then -- ${vn}
      local v = search(var)
      if v == nil then
        io.stderr:write('Warning: unknown variable: '.. var .. '  using nil\n')
      end
      return estring(tostring(v))
    end
    local b,e,cmd = strfind(var, '^(%a+)%s.')
    if cmd == 'foreach' then -- ${foreach vn xxx} or ${foreach vn/sep/xxx}
      local vn,s
      b,e,vn,s = strfind(var, '^([_%a][_%w]*)([%s%p]).', e)
      if vn then
        if strfind(s, '%s') then
          return elist(var, vn, strsub(var, e), '')
        end
        b = strfind(var, s, e, true)
        if b then
          return elist(var, vn, strsub(var, b+1), strsub(var,e,b-1))
        end
      end
      error('syntax error in: '.. var, 2)
    -- Add "include" option for SimpleITK
    elseif cmd == 'include' then -- $(include xxx)

      filename = templateComponentDirectory .. "/" .. estring(strsub(var,e))
      local includefid = io.open ( filename )
      if includefid == nil then
        print ( 'Error: failed to include ' .. filename )
        os.exit ( 1 )
      end

      includedText = includefid:read ( "*all" )
      includefid:close()

      --Remove the last character
      includedText=includedText:sub(1,#includedText-1)

      return estring(includedText)

    elseif cmd == 'when' then -- $(when vn xxx)
      local vn
      b,e,vn = strfind(var, '^([_%a][_%w]*)%s.', e)
      if vn then
        local t = search(vn)
        if not t then
          return ''
        end
        local s = strsub(var,e)
        if type(t)=='table' or type(t)=='userdata' then
          push(searchlist, 1, t)
          s = estring(s)
          pop(searchlist, 1)
          return s
        else
          return estring(s)
        end
      end
      error('syntax error in: '.. var, 2)
    else
      if statements[cmd] then -- do if for while repeat
        var = 'local OUT="" '.. var ..' return OUT'
      else  -- expression
        var = 'return '.. var
      end
      local f = assert(load(var))
      local t = searchlist[1]
      assert(type(t)=='table' or type(t)=='userdata', 'expecting table')
      setfenv(f, setmetatable({}, {__index=get, __newindex=t}))
      return estring(tostring(f()))
    end
  end

  return estring(str)
end

-- Args should be parameters template output
if #arg ~= 6 then
  print ( 'usage: ExpandTemplate.lua test_or_code_flag file_variables template_directory template_component_directory template_extension output ' )
  os.exit ( 1 )
end

testOrCodeFlag = arg[1]
configFile = arg[2]
templateFileDirectoryAndPrefix = arg[3]
templateComponentDirectory = arg[4]
templateFileExtension = arg[5]
outputFile = arg[6]

-- The following output may be useful for debuging perposes
-- Alternatively a command line option could be added to increase verbosity
-------------------------------
-- print ( 'configFile = ' .. configFile )
-- print ( 'testOrCodeFlag = ' .. testOrCodeFlag )
-- print ( 'templateFileDirectoryAndPrefix = ' .. templateFileDirectoryAndPrefix )
-- print ( 'templateComponentDirectory = ' .. templateComponentDirectory )
-- print ( 'templateFileExtension = ' .. templateFileExtension )
-- print ( 'outputFile = ' .. outputFile )

-- Load it
-- dofile ( configFile )
fid = io.open ( configFile )
if fid == nil then
  print ( 'Error: failed to open ' .. configFile )
  os.exit ( 1 )
end
json = fid:read ( "*all" )
fid:close()
filterDescription = decode ( json )

templateBaseFilename = templateFileExtension

if testOrCodeFlag == "code" then
  if filterDescription.template_code_filename == nil then
      templateBaseFilename = "ImageFilter" .. templateBaseFilename
    else
      templateBaseFilename = filterDescription.template_code_filename .. templateBaseFilename
    end
else
  if testOrCodeFlag == "test" then
    if filterDescription.template_test_filename == nil then
      templateBaseFilename = "ImageFilter" .. templateBaseFilename
    else
      templateBaseFilename = filterDescription.template_test_filename .. templateBaseFilename
    end
  else
    print('Warning: ExpandTemplate unknown flag value' .. testOrCodeFlag )
  end
end

templateFilename = templateFileDirectoryAndPrefix .. templateBaseFilename


fid = io.open ( templateFilename )
if fid == nil then
  print ( 'Error: failed to open ' .. templateFilename )
  os.exit ( 1 )
end

template = fid:read ( "*all" )
fid:close()


if filterDescription == nil then
  print ( 'Error: failed to find filter config in ' .. configFile )
  os.exit ( 1 )
end

fid = io.open ( outputFile, 'w' )
if fid == nil then
  print ( 'Error: failed to open ' .. outputFile .. ' for writing' )
  os.exit ( 1 )
end
fid:write ( expand ( template, filterDescription ) )
fid:close()
