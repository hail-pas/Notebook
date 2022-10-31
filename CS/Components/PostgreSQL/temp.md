### 概念

- 表  --> 命名模式 -->  数据库 --组成--> 数据库集簇 （PostgreSQL服务器实例管理）
- Database.schema.table;  默认为public模式
  - 内建模式： pg_catalog； 重载： 将其放在 search_path 最后
  - 系统表名称以`pg_`开头

### 类型

```sql
-- SQL类型
int、smallint、real、double precision、char(N)、varchar(N)、date、time、timestamp、interval
-- 几何类型
point
-- 用户自定义数据类型（任意数量）
```



### 操作

> --基于SQL

```sql
-- 创建表
CREATE TABLE weather(
	city			varchar(80),
  temp_lo		int,				--最低温度
  temp_hi		int,				--最高温度
  prcp			real,				--湿度
  date			date
);
CREATE TABLE city (
    name            varchar(80),
    location        point
);
-- 插入数据
-- 非简单数字值的常量必须使用单引号 '' 包围
INSERT INTO weather (city, temp_lo, temp_hi, prcp, date)
    VALUES ('San Francisco', 43, 57, 0.0, '1994-11-29');
INSERT INTO city VALUES ('San Francisco', '(-194.0, 53.0)');
-- COPY 创建
COPY weather FROM '/home/user/weather.txt';
```

### 事务

> PostgreSQL实际上将每一个SQL语句都作为一个事务来执行。

```sql
-- 事务开始和提交
BEGIN;
UPDATE accounts SET balance = balance - 100.00
    WHERE name = 'Alice';
-- etc etc
COMMIT;  -- ROLLBACK
-- 保存点
BEGIN;
UPDATE accounts SET balance = balance - 100.00
    WHERE name = 'Alice';
SAVEPOINT my_savepoint;
UPDATE accounts SET balance = balance + 100.00
    WHERE name = 'Bob';
-- oops ... forget that and use Wally's account
ROLLBACK TO my_savepoint;  -- 回滚到某个保存点
UPDATE accounts SET balance = balance + 100.00
    WHERE name = 'Wally';
COMMIT;
```

### 窗口函数 OVER

> 区别于聚集函数，不会使多行聚集成一个单独的输出； 在WHERE、GROUP BY、HAVING之后

```sql
-- 每一个员工的薪水以及其所在部门的平均薪水
SELECT depname, empno, salary, avg(salary) OVER (PARTITION BY depname) FROM empsalary;
/*
  depname  | empno | salary |          avg
-----------+-------+--------+-----------------------
 develop   |    11 |   5200 | 5020.0000000000000000
 develop   |     7 |   4200 | 5020.0000000000000000
 develop   |     9 |   4500 | 5020.0000000000000000
 develop   |     8 |   6000 | 5020.0000000000000000
 develop   |    10 |   5200 | 5020.0000000000000000
 personnel |     5 |   3500 | 3700.0000000000000000
 personnel |     2 |   3900 | 3700.0000000000000000
 sales     |     3 |   4800 | 4866.6666666666666667
 sales     |     1 |   5000 | 4866.6666666666666667
 sales     |     4 |   4800 | 4866.6666666666666667
(10 rows)
*/
-- 窗口分区内排序
OVER (PARTITION BY depname ORDER BY salary DESC)
```

### 继承

> INHERITS 面向对象数据库概念； 但是还未与唯一约束或外键集成

```sql
CREATE TABLE cities (
  name       text,
  population real,
  altitude   int     -- (in ft)
);

CREATE TABLE capitals (
  state      char(2)
) INHERITS (cities);
-- 查询包含首都的全部城市
SELECT name, altitude
  FROM cities
  WHERE altitude > 500;
-- 只查询非首都的城市（cities表）
SELECT name, altitude
    FROM ONLY cities
    WHERE altitude > 500;
```

