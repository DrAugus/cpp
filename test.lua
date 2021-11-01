local tbl = { "apple", "pear", "orange", "grape" }
for key, val in pairs(tbl) do
    print("Key", key, 'value', val)
end

a3 = {}
for i = 1, 10 do
    a3[i] = i
end
for key, val in pairs(a3) do
    print("Key", key, 'value', val)
end

for key, val in ipairs(a3) do
    print("Key", key, 'value', val)
end

s, e = string.find('i have a word', 'word')
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

function print_table(table, printKey)
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

my_table = {}
my_table[1] = 'shit'
my_table[3] = 'fuck'
tbl = my_table
print('----my_table---')
print_table(my_table)
print('--tbl---')
print_table(tbl)
my_table = nil
print('----my_table---')
print_table(my_table)
print('--tbl---')
print_table(tbl)

fruits = { "banana", "orange", "apple" }
print('在末尾插入')
table.insert(fruits, "mango")
print_table(fruits, true)
print('在索引为 2 的键处插入')
table.insert(fruits, 2, "grapes")
print_table(fruits, true)
print('remove fruits最后一个元素')
table.remove(fruits)
print_table(fruits, true)
print('sort fruits')
table.sort(fruits)
print_table(fruits)