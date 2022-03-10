-- company test code
local function company_code()

    local test_policy1 = {
        avail_date = {
            -- 指定时间段为时间戳，指定时间周期为"23:59:59"
            -- 开始s结束e （如果永远不过期，那么这项就不写）
            avail_time = {{
                s = "18:02:34",
                e = "18:02:34"
            }, {
                s = "19:02:34",
                e = "18:02:34"
            }, {
                s = "17:02:34",
                e = "18:02:34"
            }},
            date_type = 2, -- 1 every day 2 week 3 month  
            num = {1, 4, 6, 0} -- specific week/month num 周为 0-6 Sun-Sat 日为1-31 其他不填 
        }
    }
    local test_policy2 = {
        avail_date = {
            -- 指定时间段为时间戳，指定时间周期为"23:59:59"
            -- 开始s结束e （如果永远不过期，那么这项就不写）
            avail_time = {{
                s = "08:02:34",
                e = "18:02:34"
            }, {
                s = "09:02:34",
                e = "18:02:34"
            }, {
                s = "12:02:34",
                e = "18:02:34"
            }},
            date_type = 2, -- 1 every day 2 week 3 month  
            num = {1, 2, 6, 0} -- specific week/month num 周为 0-6 Sun-Sat 日为1-31 其他不填 
        }
    }
    local test_policy3 = {
        avail_date = {
            -- 指定时间段为时间戳，指定时间周期为"23:59:59"
            -- 开始s结束e （如果永远不过期，那么这项就不写）
            avail_time = {{
                s = "08:02:34",
                e = "18:02:34"
            }, {
                s = "09:02:34",
                e = "18:02:34"
            }, {
                s = "12:02:34",
                e = "18:02:34"
            }},
            date_type = 2, -- 1 every day 2 week 3 month  
            num = {1, 3, 6, 0} -- specific week/month num 周为 0-6 Sun-Sat 日为1-31 其他不填 
        }
    }
    local test_policy4 = {
        avail_date = {
            -- 指定时间段为时间戳，指定时间周期为"23:59:59"
            -- 开始s结束e （如果永远不过期，那么这项就不写）
            avail_time = {{
                s = "1645430372",
                e = "1647849572"
            }}
        }
    }

    local function policy_time_avail(policy)
        -- policy.avail_date.date_type 1 every day 2 week 3 month
        -- policy.avail_date.num specific week/month num. [1,3,7] mon wed sun
        if policy == nil then
            return false
        end
    
        -- no time limit
        if policy.avail_date == nil then
            return true
        end
    
        if policy.avail_date.avail_time == nil and policy.avail_date.date_type == nil and policy.avail_date.num == nil then
            return true
        end
    
        local ctime = os.time()
        -- 指定时间段 's' 'e' means start/end timestamp
        if policy.avail_date.avail_time ~= nil and policy.avail_date.date_type == nil and policy.avail_date.num == nil then
            if ctime < tonumber(policy.avail_date.avail_time[1].s) or ctime > tonumber(policy.avail_date.avail_time[1].e) then
                return false
            end
            return true
        end
    
        -- 指定时间周期
        local get_day = os.date("%d") -- e.g. 01-31
        local get_week = os.date("%w") -- e.g. 0-6 = Sun-Sat
    
        if policy.avail_date.date_type == 1 then
            -- every day
            -- no more extra handle
        elseif policy.avail_date.date_type == 2 then
            -- week
            local is_current = false
            for key, value in pairs(policy.avail_date.num) do
                if value == tonumber(get_week) then
                    is_current = true
                end
            end
            if is_current == false then
                return false
            end
        elseif policy.avail_date.date_type == 3 then
            -- day
            local is_current = false
            for key, value in pairs(policy.avail_date.num) do
                if value == tonumber(get_day) then
                    is_current = true
                end
            end
            if is_current == false then
                return false
            end
        end
    
        if policy.avail_date.avail_time ~= nil then
            local format_date = os.date("*t")
            -- 年月日都定为1970/1/2 因为标准是从 1970-01-01 08:00:00 起始 防止8点前出错
            local current_time = os.time({
                year = 1970,
                month = 1,
                day = 2,
                hour = format_date.hour,
                min = format_date.min,
                sec = format_date.sec
            })
            -- time str 23:59:59 trim
            local function format_time(str_time)
                return os.time({
                    year = 1970,
                    month = 1,
                    day = 2,
                    hour = string.sub(str_time, 1, 2),
                    min = string.sub(str_time, 4, 5),
                    sec = string.sub(str_time, 7, 8)
                })
            end
    
            -- 三段 时间
            local hit = false
            for i = 1, 3 do
                if policy.avail_date.avail_time[i] == nil or policy.avail_date.avail_time[i].s == nil then
                    break
                end
                local get_s = format_time(policy.avail_date.avail_time[i].s)
                local get_e = format_time(policy.avail_date.avail_time[i].e)
                if os.difftime(get_s, current_time) < 0 and os.difftime(current_time, get_e) < 0 then
                    hit = true
                    break
                end
            end
            if hit == false then
                return false
            end
        end
    
        return true
    end

    print('test_policy1', policy_time_avail(test_policy1))
    print('test_policy2', policy_time_avail(test_policy2))
    print('test_policy3', policy_time_avail(test_policy3))
    print('test_policy4', policy_time_avail(test_policy4))
end

company_code()

print(os.date("*t").day, os.time())

local function format_time(str_time)
    local a = os.time({
        year = 1970,
        month = 1,
        day = 2,
        hour = string.sub(str_time, 1, 2),
        min = string.sub(str_time, 4, 5),
        sec = string.sub(str_time, 7, 8)
    })
    return a
end

local ostime = os.date("*t")
print(ostime)
local ctime = os.time({
    year = 1970,
    month = 1,
    day = 2,
    hour = ostime.hour,
    min = ostime.min,
    sec = ostime.sec
})
print('ctime', ctime)

local diffs = "07:02:22"
local diffe = "08:02:22"

local function trim_time(str)
    print(string.sub(str, 1, 2), string.sub(str, 4, 5), string.sub(str, 7, 8))
end

trim_time(diffs)

local get_s = format_time(diffs)
local get_e = format_time(diffe)

print(os.difftime(get_s, ctime))

if os.difftime(ctime, get_s) < 0 or os.difftime(get_e, ctime) < 0 then
    print("test finish")
end

print('get_s', get_s)
print('get_e', get_e)

-- 基本方法
-- enum implement
enum = {}
local function make_meta(idx, name, value, _type)
    return {
        __index = {
            value = idx,
            name = value,
            _type = _type
        },
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
        end
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
function enum.new(name, values)
    local _Private = {}
    local _Type = {}

    setmetatable(_Private, {
        __index = function(t, k)
            local v = rawget(t, k)
            if v == nil then
                error("Invalid enum member: " .. k, 2)
            end
            return v
        end
    })

    check(values)

    for i, v in ipairs(values) do
        local o = {}
        setmetatable(o, make_meta(i, name, v, _Type))
        _Private[v] = o
        _Private[i] = o
    end

    -- public readonly table
    local Enum = {}
    setmetatable(Enum, {
        __index = _Private,
        __newindex = function()
            error("Cannot set enum value")
        end,
        __tostring = function()
            return string.format("<enum '%s'>", name)
        end
    })

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

fruits = {"banana", "orange", "apple"}
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

-- 元表
print('元表')
myMetatable = setmetatable({10, 9, 8, 7}, {
    __index = {
        key = 6
    },
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
})

plusTable = {'shit', 'ffff'}
plusTable = {2, 3}

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
definitions.test_enum = enum.new("test_enum", {"cow", "bull", "hide", "bush"})
print(definitions.test_enum.cow)
print(definitions.test_enum.cow.value)

