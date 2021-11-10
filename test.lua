-- 基本方法
-- enum implement
enum = {}
local function make_meta(idx, name, value, _type)
    return {
        __index = { value = idx, name = value, _type = _type },
        __newindex = function()
            error("Cannot set fields in enum value", 2)
        end,
        __tostring = function()
            return string.format('<%s.%s: %d>', name, value, idx)
        end,
        __le = function()
            error("Unsupported operation")
        end,
        __lt = function()
            error("Unsupported operation")
        end,
        __eq = function(this, other)
            return this._type == other._type and this.value == other.value
        end,
    }
end
local function check(values)
    local found = {}

    for _, v in ipairs(values) do
        if type(v) ~= "string" then
            error("Can create enum only from strings")
        end

        if found[v] == nil then
            found[v] = 1
        else
            found[v] = found[v] + 1
        end
    end

    local msg = "Attempted to reuse key: '%s'"
    for k, v in pairs(found) do
        if v > 1 then
            error(msg:format(k))
        end
    end
end
function enum.new (name, values)
    local _Private = {}
    local _Type = {}

    setmetatable(
            _Private,
            {
                __index = function(t, k)
                    local v = rawget(t, k)
                    if v == nil then
                        error("Invalid enum member: " .. k, 2)
                    end
                    return v
                end
            }
    )

    check(values)

    for i, v in ipairs(values) do
        local o = {}
        setmetatable(o, make_meta(i, name, v, _Type))
        _Private[v] = o
        _Private[i] = o
    end

    -- public readonly table
    local Enum = {}
    setmetatable(
            Enum,
            {
                __index = _Private,
                __newindex = function()
                    error("Cannot set enum value")
                end,
                __tostring = function()
                    return string.format("<enum '%s'>", name)
                end,
            }
    )

    return Enum
end

------------------------------------------------


a3 = {}
for i = 1, 2 do
    a3[i] = i
end
for key, val in pairs(a3) do
    print("Key", key, 'value', val)
end

for key, val in ipairs(a3) do
    print("Key", key, 'value', val)
end

local findSource = 'you need a word'
local findDes = 'word'
s, e = string.find(findSource, findDes)
print(s, e)

tab3 = {}
tab3[1] = "1"
tab3[2] = "2"
tab3[4] = "4"
print("tab3长度" .. #tab3)

tab3 = {}
tab3[1] = "1"
tab3[2] = "2"
tab3['9'] = "5"
print("tab3的长度" .. #tab3)

local tab = {
    [1] = "a",
    [3] = "b",
    [4] = "c"
}
for i, v in pairs(tab) do
    -- 输出 "a" ,"b", "c"  ,
    print(tab[i])
end

for i, v in ipairs(tab) do
    -- 输出 "a" ,k=2时断开
    print(tab[i])
end

what = {}
function what:fuck()
    print('i am ...')
end

what:fuck()

function what:print_table(table, printKey)
    if table == nil then
        return print('null table')
    end
    for i, v in pairs(table) do
        if printKey == nil then
            print(i, v)
        else
            print(v)
        end
    end
end

print('测试table移除')
my_table = {}
my_table[1] = 'shit'
my_table[3] = 'fuck'
tbl = my_table
print('--my_table--')
what:print_table(my_table)
print('--tbl---')
what:print_table(tbl)
my_table = nil
print('--my_table--')
what:print_table(my_table)
print('--tbl---')
what:print_table(tbl)

fruits = { "banana", "orange", "apple" }
print('在末尾插入')
table.insert(fruits, "mango")
what:print_table(fruits, true)
print('在索引为 2 的键处插入')
table.insert(fruits, 2, "grapes")
what:print_table(fruits, true)
print('remove fruits最后一个元素')
table.remove(fruits)
what:print_table(fruits, true)
print('sort fruits')
table.sort(fruits)
what:print_table(fruits)

function what:table_length(t)
    local mn = 0
    for k, v in pairs(t) do
        mn = k
    end
    return mn
end

--元表
print('元表')
myMetatable = setmetatable(
        { 10, 9, 8, 7 },
        {
            __index = { key = 6 },
            __add = function(myMetatable, newT)
                local newLen = what:table_length(myMetatable) + what:table_length(newT)
                for i = what:table_length(myMetatable), newLen do
                    table.insert(myMetatable, what:table_length(myMetatable) + 1, newT[i - what:table_length(myMetatable)])
                end
                return myMetatable
            end,
            __call = function(myMetatable, newTable)
                sum = 0
                for i = 1, what:table_length(myMetatable) do
                    sum = sum + myMetatable[i]
                end
                for i = 1, what:table_length(newTable) do
                    sum = sum + newTable[i]
                end
                return sum
            end,
            __tostring = function(myMetatable, showKey)
                if myMetatable == nil then
                    return 'null table'
                end
                local str = ''
                for i, v in pairs(myMetatable) do
                    if showKey == nil then
                        str = str .. i .. ' ' .. v .. '\n'
                    else
                        str = str + v + '\n'
                    end
                end
                -- 移除最后一个 \n
                str = string.sub(str, 1, -2)
                return str
            end
        }
)

plusTable = { 'shit', 'ffff' }
plusTable = { 2, 3 }

print('----------')
what:print_table(myMetatable)
print('=======__add=======')
myMetatable = myMetatable + plusTable
what:print_table(myMetatable)
print('#####__call#####')
print(myMetatable(plusTable))
print('000000__toString000000')
print(myMetatable)
print('-- rawget 1 --')
print(rawget(myMetatable, 1))

definitions = {}
definitions.test_enum = enum.new("test_enum", {
    "cow", "bull", "hide", "bush"
}
)
print(definitions.test_enum.cow)
print(definitions.test_enum.cow.value)

