<h3><a href = "https://www.runoob.com/sql/sql-insert-into-select.html" title="more info" target="_blank">SQL INSERT INTO SELECT 语法</a></h3>
从一个表中复制所有的列插入到另一个已存在的表中：<br>
```sql
INSERT INTO table2
SELECT * FROM table1;
```
只复制希望的列插入到另一个已存在的表中：<br>
```sql
INSERT INTO table2
(column_name(s))
SELECT column_name(s)
FROM table1;
```