-- require 'Expand'
local strfind = string.find
local strsub  = string.sub
local push    = table.insert
local pop     = table.remove
local concat  = table.concat

local statements = {}
for w in string.gfind('do if for while repeat', '%a+') do
  statements[w] = true
end

function expand(str, ...)
  assert(type(str)=='string', 'expecting string')
  local searchlist = arg
  local estring,evar

  function estring(str)
    local b,e,i
    b,i = strfind(str, '%$.')
    if not b then return str end

    local R, pos = {}, 1
    repeat
      b,e = strfind(str, '^%b{}', i)
      if b then
        push(R, strsub(str, pos, b-2))
        push(R, evar(strsub(str, b+1, e-1)))
        i = e+1
        pos = i
      else
        b,e = strfind(str, '^%b()', i)
        if b then
          push(R, strsub(str, pos, b-2))
          push(R, evar(strsub(str, b+1, e-1)))
          i = e+1
          pos = i
        elseif strfind(str, '^%a', i) then
          push(R, strsub(str, pos, i-2))
          push(R, evar(strsub(str, i, i)))
          i = i+1
          pos = i
        elseif strfind(str, '^%$', i) then
          push(R, strsub(str, pos, i))
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
    error('unknown variable: '.. index)
  end

  local function elist(var, v, str, sep)
    local tab = search(v)
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
      return estring(tostring(search(var)))
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
      local f = assert(loadstring(var))
      local t = searchlist[1]
      assert(type(t)=='table' or type(t)=='userdata', 'expecting table')
      setfenv(f, setmetatable({}, {__index=get, __newindex=t}))
      return estring(tostring(f()))
    end
  end

  return estring(str)
end

-- Args should be parameters template output
if #arg ~= 3 then
  print ( 'usage: ExpandTemplate.lua config template output ' )
  os.exit ( 1 )
end

configFile = arg[1]
templateFile = arg[2]
outputFile = arg[3]

fid = io.open ( templateFile )
if fid == nil then
  print ( 'failed to open ' .. templateFile )
  os.exit ( 1 )
end

template = fid:read ( "*all" )
fid:close()

-- Load it
dofile ( configFile )
if Filter == nil then
  print ( 'failed to find filter config in ' .. configFile )
  os.exit ( 1 )
end

fid = io.open ( outputFile, 'w' )
if fid == nil then
  print ( 'failed to open ' .. outputFile .. ' for writing' )
  os.exit ( 1 )
end
fid:write ( expand ( template, Filter ) )
fid:close()
