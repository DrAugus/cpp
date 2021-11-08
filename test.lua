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


