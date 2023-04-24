# MySQL
## 前言
- DB ==> DBMS 交互软件
	- RDB    --关系型数据库
		- MySQL    --MariaDB是其替代品
	- No-SQL    --非关系型数据图
		- key:value，图
		- Redis    --key-value，数据结构-list、set、zset、hash，master-slave数据备份
		- MongoDB    --文档{key:value}，集合{}{}，数据库
- 3范式
	- 原子属性
	- 属性依赖主键
	- 直接依赖
- ACID四大特性    --事务要求， InnoDB引擎支持
	- Atomicity 原子性
	- Consistency 一致性
	- Isolation 隔离性
	- Durability 持久性
- 环境变量
	- export PATH=$PATH:xxx:xxx
	- 用户 - 不同的终端的不同配置文件
----
## SQL语句
操作层次: 库 -> 表 -> 行
{create、alter、drop、desc} -> {user、database、table、view、index}
```shell
# 登录
mysql -u u_name -h ip -P port -p    --指定用户名和授权主机，默认主机localhost
```
### 用户

```mysql
-- 创建
create user "u_name"@"ip" identified by "p_word"    # % 通配符，192.168.7.%
-- 修改
rename user "u_name"@"ip" to "new"
set password for "u_name"@"ip" = password("newp_word")
-- 删除
drop user "u_name"@"ip"
```
### 权限
数据库.*；all privileges、select、update、alter
```mysql
-- 查看
show grants for '用户'@'IP地址'
-- 授权
grant 权限 on 数据库.表 to '用户'@'IP地址'
-- 收回
revoke 权限 on 数据库.表 from '用户'@'IP地址'
-- 权限读取到内存, 立即生效
flush privileges
```
### 数据库
```mysql
show databases
drop database if exists db_name
create database db_name CHARSET utf8 COLLATE utf8_general_ci CHARACTER SET gbk COLLATE gbk_chinese_ci    --gbk
use db_name
```
### 表
```mysql
-- show、drop
-- 创建
create table if not exists tb_name(
	'id' type not null default xx primary key auto_increment comment '',
	'otb_id' type not mull,
	FOREIGN key ('`otbid'`) REFERENCES otb('`id'`),
	INDEX [indexName] (username(length),id)
	UNIQUE [iname] (,)
)ENGINE=InnoDB DEFAULT CHARSET=utf8;
-- key: { primary key，foreign key，unique key } => 约束、索引
-- 多行定义： primary key( , , )
- 清空
delete from tb_name   --清空表内容，后续新增时，自增继续增长
truncate table tb_name   --清空表内容，后续新增时，自增从开始重新增长
-- 添加列
alter table 表名 add 列名 类型
-- 删除列
alter table 表名 drop column 列名
-- 修改列
alter table 表名 modify column 列名 类型    -- 类型
alter table 表名 change 原列名 新列名 类型    -- 列名，类型
-- 添加主键
alter table 表名 add primary key(列名)
-- 删除主键：
alter table 表名 drop primary key;
alter table 表名 modify 列名 int, drop primary key;    -- 修改某个列并接解除其主键性质
-- 添加外键
alter table 表1名 add constraint 约束名称 foreign key 表1(外键字段) references 表2名(主键字段);
-- 删除外键
alter table 表名 drop foreign key 外键约束    -- change删除
--修改默认值
ALTER TABLE 表名 ALTER 列名 SET DEFAULT 1000;
-- 删除默认值
ALTER TABLE 表名 ALTER 列名 DROP DEFAULT;
```
### 行
```mysql
-- 增
insert into 表名(列名1，列名2) value(值1，值2),(值, 值)
insert into 表 (列名,列名...) select (列名,列名...) from 表   --表复制
-- 删
delete from 表
delete from 表 where 列名＝value and 列名=value
-- 改
update 表 set 列名＝value where 条件
-- 查
select (distinct 列名1，列名2，列名3 as 重命名) from 表名 where 条件    -- * 为所有行；定义首行
-- 其他
-- a、条件
	><!=、between x and y、not in (set)、in (select * from 表)
-- b、通配符
	select * from 表 where name like 'ale%'  - ale开头的所有（多个字符串）
									 'ale_'  - ale开头的所有（一个字符）
-- c、分页
	select * from 表 limit 5;            - 前5行
					 limit 4,5;          - 从第4行开始取5行
					 limit 5 offset 4    - 从第4行开始取5行
-- d、排序
	select * from 表 order by 列 asc/desc             - 根据 “列” 升/降序排列
							  列1 desc,列2 asc    - 根据 “列1” 从大到小排列，如果相同则按列2从小到大排序
-- e、分组
	select num,nid from 表 group by num,nid    --列定义 group by 配合聚合函数使用
						   where nid > 10 group by num,nid order nid desc
	select num,nid,count(*),sum(score),max(score),min(score) from 表 group by num,nid    --分组压缩成一行
	select num from 表 group by num having max(id) > 10    --having对分组结果进一步过滤
	=> 特别的：group by 必须在where之后，order by之前  >> 筛选、分组、排序
-- f、连表   {inner join、left join、right join} on 条件
	select A.num, A.name, B.name from A,B Where A.nid = B.nid    --笛卡尔乘积，无则不显
	select A.num, A.name, B.name from A inner join B on A.nid = B.nid    --无则不显
	select A.num, A.name, B.name from A left join B on A.nid = B.nid    --以左为基准，右表无值则为null
	select A.num, A.name, B.name from A right join B on A.nid = B.nid    --以右为基准
-- g、结果联合
	select nickname from A union select name from B    --默认去重， union all不去重
```

## 数据类型
### 数值
	- bit(1~64)
	- {tinyint、smallint、int、bigint} * {signed、unsigned}
	- decimal、float、double => decimal是精确的基于字符串，double稍微好于float. 参数（n，n-整数部分长度）
### 字符串
	- char -- 定长
	- varchar、text、mediumtext、longtext -- 变长， var最大255
### 二进制数据
	- tinyblob、blob、mediumblob、longblob -- 上传文件
### 时间
	- DATE - YYYY-MM-DD
	- TIME - HH:MM:SS
	- DATETIME - YYYY-MM-DD HH:MM:SS
	- YEAR - YYYY
	- TIMESTAMP YYYYMMDD HHMMSS
### enum - 枚举 单==> 字典，限定范围
	- enum( , , )    --只能取一个限定范围里的值
### set - 集合 多
	- set( , , , )    --可以取集合中的多个
## 索引
> 表内索引， 二叉搜索树（Binary Search Tree）--> B+树 ==>约束和加速（条件查找：索引->表）（B+树索引、hash索引）

### 类别
	- index 普通   --加速, 组合索引（列1，列2），最左匹配触发 即只有从左边匹配任意个才触发索引（如 username+passwd）
	- unique 唯一    --primary，加速、约束  ==> 联合键、组合索引
	- fulltext 全局
	- spatial 空间
### 操作
```mysql
-- 创建
CREATE [UNIQUE|FULLTEXT|SPATIAL] INDEX indexName ON 表(列名(长度));   --指定索引字符长度，text、blob等数据类型太大
-- 修改
ALTER table tableName ADD INDEX indexName(columnName)
-- 显示
SHOW INDEX FROM table_name;
-- 删除
DROP [UNIQUE|FULLTEXT|SPATIAL] INDEX [indexName] ON mytable;
```
### 执行计划
> 相对较正确的当前SQL运行状况，是否使用索引，性能情况
#### 分析
```mysql
explain SQL语句    --返回type
-> type
	- all    --全数据表扫描一遍
	- index    --全索引表扫描一遍
	------最低标准------
	- range    --索引列的比较><=、范围in 的条件查找 或者 limit ,使用的type，效率比上两种高；注意： !=、> 不能走范围索引
	- index_merge    --索引合并，多个单独索引; 索引覆盖（select 索引， 条件也是索引）
	- REF    --使用索引查找
	- EQ_REF   --通过unique索引连接表来查找  select tb2.nid,tb1.name from tb2 left join tb1 on tb2.nid = tb1.nid
	- const  --只在索引表中查找一次，只扫描一次   select nid from tb1 where nid = 2
	- system    --const的特列，  select * from (select nid from tb1 where nid = 1) as A
```
#### 不走索引的情况
```mysql
-- like '%xx'      --使用xx% 则可以
			select * from tb1 where name like '%cn';
-- 使用函数    --查找条件函数计算索引会变化，不走索引；分离成两步解决
	select * from tb1 where reverse(name) = 'wupeiqi';
-- or 有非索引列， 当全是索引时就会变成索引合并
	select * from tb1 where nid = 1 or email = 'seven@live.com';
	特别的：当or条件中有未建立索引的列才失效，以下会走索引
					select * from tb1 where nid = 1 or name = 'seven';
					select * from tb1 where nid = 1 or email = 'seven@live.com' and name = 'alex'
-- 数据类型不一致
	如果列是字符串类型，传入条件是必须用引号引起来，不然...
	select * from tb1 where name = 999;
-- !=    目前发现会优化成范围查找，但是范围查找不走索引
	select * from tb1 where name != 'alex'
	特别的：如果是主键，则还是会走索引
			select * from tb1 where nid != 123
-- >     --主键、数字类型索引都会走
	select * from tb1 where name > 'alex'
	特别的：如果是主键或索引是整数类型，则还是会走索引
			select * from tb1 where nid > 123
			select * from tb1 where num > 123
-- order by    --当以主键排序时，所有映射都走索引
	select email from tb1 order by name desc;
	当根据索引排序时候，select的映射如果不是索引，则不走索引
	特别的：如果对主键排序，则还是走索引：
			select * from tb1 order by nid desc;
-- 组合索引最左前缀
```
#### 注意事项
```mysql
-- 避免使用select *
-- count(1)或count(列) 代替 count(*)
-- 创建表时尽量时 char 代替 varchar； 表的字段顺序固定长度的字段优先
-- 组合索引代替多个单列索引（经常使用多个条件查询时）
-- 尽量使用短索引
-- 使用连接（JOIN）来代替子查询(Sub-Queries)；连表时注意条件类型需一致
-- 索引散列值小（大量重复）不适合建索引，例：性别不适合
```
#### 应用->分页
```mysql
-- 常规
select * from tb_name limit pos,页长    --从开始一直扫描到满足条件，速度问题，浪费
-- 常见： 索引 -> 反取
select * from tb_name where nid in（select nid from tb_name limit pos,页长）
-- 最优：改变开始扫描的行，只扫描需要部分 => where nid>n , limit 页长
	自增列：可能中断跳跃
	下一页 - 传递当前页最后一行的自增列值n，where nid>n
		cursor.execute(select * from tb_name where nid>%s limit 页长, last_nid)
	上一页 - 传递当前页第一行的自增列值m，where nid<m，对其desc反转排序再 limit 页长 取值
		cursor.execute(select * from tb_name where nid<%s order by nid desc limit 页长, first_nid)
		result = cursor.fetchall()
		result = reverse(result)
```
## 视图
> 虚拟临时表,每次取数据更新，只是sql语句的对应关系; 不允许删除、更新
```mysql
-- 创建
create view v_name as sql查询语句
-- 修改
alter
-- 删除
drop
```
## 触发器
> 无法主动引用，只能动作被动触发
```mysql
--创建    --配合if then 逻辑语句使用
CREATE TRIGGER tri_name {BEFORE|AFTER} {INSERT|DELETE|UPDATE} ON tb_name FOR EACH ROW
BEGIN
	...    --NEW表示即将插入的数据行，OLD表示即将删除的数据行
	NEW.列名    --引用列数据
END
-- 删除
DROP TRIGGER tri_name
```
## 事务
> ACID
```mysql
DECLARE exit handler for sqlexception
BEGIN
	-- ERROR
    set p_return_code = 1;
    rollback;
END;

DECLARE exit handler for sqlwarning
BEGIN
    -- WARNING
    set p_return_code = 2;
    rollback;
END;

START TRANSACTION;     --开始事务
    DELETE from tb1;
    insert into tb2(name)values('seven');
COMMIT;    --提交事务
```


## 存储过程
> 是一个逻辑SQL语句集合，非事务
### 无参数
```mysql
-- 创建    --使用delimiter 来 使用语句块执行，当需要连着写多个sql语句时
delimiter //    #定义//为结束符，忽略；
create procedure p_name()
BEGIN
	select * from t1;  #sql语句
END//
delimiter；   #恢复默认
- 调用
call p_name()
cursor.callproc('p_name',(args))    --pymysql
```
### 带参数
> in、inout、out, in varname type
```mysql
-- 变量：procedure内部-declare；sql语句-set @varname ==> 定义+赋值
-- pymysql获取：select @_p_name_i
-- 创建
delimiter \\
create procedure p1(
		in i1 int,
		in i2 int,
		inout i3 int,
		out r1 int    --不等于结果集=表- selet结果，都需要函数fetch
	)
BEGIN
	DECLARE temp1 int;
	DECLARE temp2 int default 0;
	set temp1 = 1;
	set r1 = i1 + i2 + temp1 + temp2;
	set i3 = i3 + 100;
end\\
delimiter ;
-- 执行
-- mysql
		set @t1 =4;     --创建变量，sql变量需要以@开头
		set @t2 = 0;
		CALL p1 (1, 2 ,@t1, @t2);   --返回参数也要传递进去，且需要在proce外部创建，类似使用全局变量
		SELECT @t1,@t2;
-- pymysql
		cursor.callproc('p_name', args=(1, 22, 3, 4))
		cursor.execute("select @_p_name_0,@_p_name_1,@_p_name_2,@_p_name_3") --固定格式，select按顺序获取传入的所有函数
		result = cursor.fetchall()
		conn.commit()    --涉及更改需要提交，保险起见加上
-- 逻辑语句
-- if  then
if xx then xxx; elseif xx then xxx; else xxx; endif;
-- while  do
while xx do xxx; end while;
-- repeat  until
repeat xxx; until xx; end repeat;
-- loop   ->   iterate -> leave -> end
loop_label: loop
	set i=i+1;
	if i<8 then
		iterate loop_label;
	end if;
	if i>=10 then
		leave loop_label;
	end if;
	select i;
end loop loop_label;
- 变量动态执行sql语句  --  prepare、 ？、execute 、using 、@varname、
PREPARE prod FROM 'select * from tb2 where nid > ?';    --占位符使用问号？
EXECUTE prod USING @p1;
DEALLOCATE prepare prod;
```
## 函数
### 内置
```mysql
CHAR_LENGTH(str)、LENGTH()
CONCAT(str1,str2,...)
CONCAT_WS(separator,str1,str2,...)  --自定义拼接符
CONV(var,from_base,to_base)    --进制转换，将var从from转到to
FORMAT(X,D)   --SELECT FORMAT(12332.1,4); 结果为： '12,332.1000'
INSERT(str,posint,lenint,newstr)    --posint>=0;逻辑 - 清除、替换
INSTR(str,substr)    --子字符串出现的第一个位置
LEFT(str,lenint)    --获取str从左起lenint个、RIGHT()、 substring(str, pos, len)
LOWER()   --UPPER()
LTRIM(str)   --RTRIM(str)  去除两端空白=> TRIM()
LOCATE(substr,str,pos)    --pos为起始计数，返回子字符串开始索引
REPEAT(str,count)    --返回组成字符串，str*count
REPLACE(str,from_str,to_str)    --指定替换
REVERSE(str)    --反序
RIGHT(str,len)    --返回str右边len长度的子字符串
SPACE(N)    --返回一个由N空格组成的字符串
SUBSTRING(str, pos, len)  =  SUBSTRING(str FROM pos FOR len)
TRIM()
	- LEADING 'x' FROM 'str'    --去除str中左边的x
	- TRAILING 'x' FROM 'str'    --去除右边
	- BOTH 'x'  FROM 'str'    --两边
```
### 自定义函数 function
> 存储过程中可以获取select结果集，但是函数不能返回结果集，但可使用select赋值； 存储过程用call调用； 函数直接传参执行
```mysql
-- 创建    --dilimeter
create function f_name(var1 int, var2 varchar(20))
returns varchar(20)     --显式返回，参数无须修饰传入传出参数
begin
	....
	declare var int
	set var = value1
	select id into var from t_name where <condition>    --select直接使用
end
-- 删除
drop function func_name;
```
## 慢sql日志
> mysqld --default-files=/path/to/file
```shell
# 配置文件修改    --  mac-.cnf; win-.ini
slow_query_log = OFF                           # 是否开启慢日志记录
long_query_time = 2                            # 时间限制，超过此时间，则记录
slow_query_log_file = /usr/slow.log            # 日志文件
log_queries_not_using_indexes = OFF            # 使用索引的搜索是否记录
# 配置内存直接修改    --工作中最好不要重启，内存修改立即生效
show variables like "%query%";
set xxxx=vvvv
```
