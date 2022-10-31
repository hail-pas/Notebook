# Redis 4.x Cookbook

## 第一章 开始使用Redis

> 键值存储，数据结构服务器，REmote DIctionary Server。C语言编写的开源软件
> 命名规则：major.minor:patch，主版本号 偶=稳定、奇=下一版本的beta

### 1.1 应用场景

TOP N、全局缓存、全局会话、分布式锁、集合运算、基数计数、基于内存的对账、不严格可靠的消息队列

### 1.2 START

#### 1.2.1 创建Redis实例

```shell
######## 编译 安装
sudo apt-get install build-essential  # 安装编译工具 libc、gcc
mkdir /redis
cd /redis
wget http://download.redis.io/releases/redis-6.x.x.tar.gz
tar zxvf redis-6.x.x.tar.gz
cd redis-6.x.x
mkdir /redis/conf
cp redis.conf /redis/conf/  # include /path/to/redis.conf 可以包含另外的配置文件
# 编译预选项
cd deps
make hiredis lua jemalloc linenoise # f非必须
cd ..
# 编译
make
# 安装
make PREFIX=/redis install
######## 直接安装
sudo apt-get update
sudo apt-get install redis-server
which redis-server # 验证
```

/redis/bin/

​	redis-server
​	redis-sentinel          |  redis-serer的软链接
​	redis-cli				   | 命令行工具
​	redis-check-rdb	  | RDB检查工具
​	redis-check-aof	  | Append Only File检查工具
​	redis-benchmark.   | 基准性能测试工具

#### 1.2.2 常用操作

##### 1.2.2.1 启动/停止

```shell
# 前台模式启动 start
redis-server [conf] [-a pwd]
########################
# redis-server 相关参数 --option value 覆盖启动
--port port --bind host --dbfilename filename.rdb
# 后台模式启动
vim /cus/conf
damonize yes
redis-server [/cus/conf]
# 停止 stop
kill `pidof redis-server` # 善后处理，SIGTERM(15)
redis-cli shutdown save # 持久化、一致性检查；清理.pid文件 和 socket套接字文件描述符；退出进程
```

Redis实例 = redis-server 进程，一台主机上可以运行多个Redis实例，只需要这些实例使用不同的配置，如：绑定到不同的端口、使用不同的路径保存持久化相关的文件、不同日志路径

##### 1.2.2.2 命令行

```shell
redis-cli -h hostname -p port -a pwd
IP地址:port> COMMAND
# INFO 状态、指标查询
INFO [section]
	section: 
		Server：服务器基本信息
		Clients：客户端状态、指标
		Memory：内存消耗
		Persistence：持久化状态、指标
		Stats：总体统计数据
		Replication：主从复制相关
		CPU：CPU使用情况
		CLuster：集群状态
		Keyspace：数据库相关统计数据
```

#### 1.2.3 事件模型

> 高性能，单线程、非阻塞、多路复用的I/O模型
> 异步事件库：ae 轻量级上下文I/O模型，封装了不同操作系统的polling机制(即非阻塞I/O相关机制)
> select(轮询)、epoll、kqueue 回调
> 一次只能处理一个命令，导致延迟问题

​	ae 包含 AcceptHandler、ReadHandler、Write Handler，事件三个handler
​	aeCreateEventLoop：创建事件循环
​	anetTcpServer：创建TCP服务器
​	客户端连接套接字FD

#### 1.2.4 通信协议

> 接收并处理客户端请求的非阻塞、I/O复用的TCP服务器。 RESP Redis序列化协议，不同编程语言实现Redis客户端和代理

```shell
# netcat 工具
❯ echo -e "*1\r\n\$4\r\nPING\r\n" | nc 127.0.0.1 6379
+PONG
❯ echo -e "*3\r\n\$3\r\nset\r\n\$5\r\nmykey\r\n\$1\r\n1\r\n" | nc 127.0.0.1 6379
+OK
❯ echo -e "*2\r\n\$4\r\nINCR\r\n\$5\r\nmykey\r\n" | nc 127.0.0.1 6379
:2
# RESP redis序列化协议 
## 五种类型
	e g. "*1\r\n\$4\r\nPING\r\n"  一个resp数组，可多个一起发送
	- *后面的数字1代表这个数组的总大小
	- \r\n是RESP中每个部分的终结符
	- $表示后面的数组字部分长度，需要转义
	- $4表示接下来是四个字符组成的字符串
	- PING 为字符串本身
	- +PONG为接收的响应
		+ 字符串
		- 错误信息
		: 数字
	re："*3\r\n\$3set\r\n\$8\r\nkey_name\r\n\$5\r\nvalue\r\n" = set key_name value
```

## 第二章 数据类型

> String、list、set、sorted set、hash、HyperLogLog、Geo、键管理

### 2.1 字符串string

> 所有的键都必须是字符串

Redis字符串编码（根据字符串值）：

 - int			 保存的是整数值，能够使用64位有符号整数(`long` 类型 8 字节)表示的字符串
 - embstr     保存的是字符串值，长度小于或等于44字节的字符串（内存使用和性能方面更有效率）
                   一次分配两块连续内存（ redisObject【type、coding、ptr -> sds.buf】、sdshdr【len、free、buf】）
 - raw           保存的是字符串值，长度大于44字节的字符串，（两次调用分配）

> OBJECT 命令 OBJECT <ENCODING|REFCOUNT|IDLETIME> <key>， 查看编码、引用、闲置时间等

#### 2.1.1 常用命令

- SET <key> <value>
  覆盖设置

- SETNX <key> <value>
  仅不存在时创建

- SETRANGE <key> <spos> <value>  ｜  GETRANGE <key> <start> <end>
  偏移从0开始，直到最后; -1为最后一个

- APPEND <key> <value> 

  不存在则会创建空值再追加

- GET <key>

- GETSET <key> <value>
  设置新值并返回旧值

- STRLEN <key>

- INCRBY|DECRBY|INCRBYFLOAT <key> <value>

- M-prefix 批量命令、原子操作

  - MSET <key> <value> [<keey> <value> <key> <value> ... ]
  - MGET <key> [<key> <key> ...]

```python
# python 的 redis锁实现
redis = await aioredis.create_redis_pool(
            f"redis://{host}:{port}", password=password, db=db, **kwargs
        ) # redis实例

RedisLock = namedtuple("RedisLock", ["lock"])

def make_redis_lock(redis):
  	redis = None

    async def get_redis_():
        nonlocal redis

        if redis is None:
            redis = await get_redis()

        return redis
    
    @asynccontextmanager
    # __aenter__(self) ， __aexit__(self, exc_type, exc_val, exc_tb)
    async def lock(key, timeout = 60):
        v = urandom(20)

        accquired = False

        while not accquired:
            accquired = await redis.set(key, v, expire=timeout, exist="SET_IF_NOT_EXIST")

            if not accquired:
                await sleep(1)

        try:
            yield    # value,  async with redis_lock.lock() as v: with下的逻辑代码嵌入到这里执行 
        finally:		 # 最后处理逻辑代码
          	# lua脚本删除key
            await redis.eval("""
                if redis.call("get", KEYS[1]) == ARGV[1]
                then
                    return redis.call("del", KEYS[1])
                else
                    return 0
                end
            """, [key], [v])  # eval("""xxx""", KEYS=[], ARGV=[]), 下标从1开始； 

    redis_lock = RedisLock(
        lock = lock,
    )

    return redis_lock

# lua脚本原子删除指定前缀的键  prefix:*
redis.eval("""
	return redis.call("del", unpack(redis.call("keys", ARGV[1])))
""", [], ["prefix:*"])
```

### 2.2 列表list

> 双向链表， LPUSH、RPUSH、LINSERT 都会返回列表长度

Redis内部使用 quicklist存储列表对象，相关配置项：

- list-max-ziplist-size  一个列表条目中 一个内部节点的最大大小（quicklist的每个节点都是一个ziplist）
- list-compress-depth  列表压缩策略，列表很长时最可能访问的时列表两端的数据

#### 2.2.1 常用命令

- LPUSH <key> <value> [value ]      |     RPUSH

- LPUSHX ｜ RPUSHX 

  仅当存在键时才新增元素；会自动回收

- LPOP <key>    ｜    RPOP

- BLPOP <key> <timeout>      |      BRPOP 
  阻塞版本的pop，timeout为超时时间，当为0时则永久等待

- LRANGE <key> <start> <end>

- LTRIM <key> <start> <end>

- LINDEX <key> <index>

- LSET <key> <index> <value>
  已存在的元素才能修改

- LINSERT <key> [AFTER|BEFORE] <exvalue> <newvalue>

### 2.3 哈希hash

> Redis数据集本身就可以看作一个哈希（map、字典）

一个哈希最多能容纳2^32 - 1 个字段，Redis内部使用两种编码方式来存储哈序对象：

- ziplist    较小的哈希， hash-max-ziplist-entries = 512， hash-max-ziplist-value = 64B
- hashtable   不适用于ziplist的情况

#### 2.3.1 常用命令

- HMSET <key> <inkey> <value> [<inkey> <value> ]

- HMGET <key> <inkey> [<inkey> ]

- HSET <key> <inkey> <value>

- HSETNX <key> <inkey> <value>
  当不存在该字段时才会设置字段的值，防止默认覆盖字段的行为

- HGET <key> <inkey>

- HDEL <key> <inkey> [<inkey>]

- HEXISTS <key> <inkey>

- HGETALL <key>
  不建议对数量巨大的哈希使用，会阻塞redis服务器

- HSCAN               tips：SCAN、HSCAN、SSCAN、ZSCAN 增量的迭代遍历元素
  基于指针的迭代器，指定一个游标（从0开始）。返回元素列表和新的游标

  ```shell
  # HSCAN <key> <cursorstart> [MATCH pattern] [COUNT number] 
  # MATCH 模式匹配， COUNT 参考返回元素个数
  # 模式匹配
  127.0.0.1:6379> HSCAN large_hash 0 MTACH *garden*    # 包含garden的字段
  1) "309"    # 新的游标
  2) 1) "panda garden"
     2) "3.9"
     3) "vhang garden"
     4) "4.5"
  127.0.0.1:6379> HSCAN large_hash 309 MTACH *garden* # 使用新的游标
  1) "0"    # 为 0 时则表示遍历完成
  2) 1) "panda garden"
     2) "3.9"
     3) "vhang garden"
     4) "4.5"
  ```

### 3.4 集合set

> 唯一、无序

最多可容纳2^32 - 1 个成员，Redis内部使用两种编码方式来存储集合对象：

- intset  元素都是整数，且元素个数小于配置的set-max-intset-entries = 512 的集合
- hashtable  较大时不符合intset的情况

#### 3.4.1 常用命令

- SADD <key> <value> [<value> ]
- SISMEMBER <key> <tvalue>
- SREM <key> <value>  
  删除
- SCARD <key> 
  获取成员数量
- SMEMBERS <key> 
  获取所有的成员，可能阻塞
- SSCAN <key> <cursor> [MATCH pattern]
- SUNION <key1> <key2>
- SUINONSTORE <result> <key1> <key2>
  SINTER、SINTERSTORE

### 3.5 有序集合sorted set

> 带权重的有序集合，相同权重时按照字典序排序

Redis内部使用两种编码方式存储有序集合对象：

- ziplist    长度小于 zset-max-ziplist-entries = 128 且所有元素的大小都小于 zset-max-ziplist-value = 64B 的有序集合
- skiplist 

#### 3.5.1 常用命令

- ZADD <key> [NX] <score> <member> [<score> <member>]
  NX 只新增不覆盖, XX 只更新不新增
- ZRANGE <key> <start> <end> [WITHSCORES]
  升序，ZREVRANGE 是 降序
- ZINCRBY <key> <increment> <member>
- ZRANK <key> <member>
  查看 member 的升序排行, 从0开始； ZREVRANK 是降序
- ZSCORE <key> <member>
- ZUNIONSTORE <des> <setnum> <zset1> [<zset2> <zset3>] WEIGHTS <weight1> [<weight2> <weight3>]
  ZUNIONSTORE result 3 zset1 zset2 zset3 WEIGHTS 2 3 1
  最终值:  weighti * i 之和

### 3.6 HyperLogLog

> 唯一计数，集合；当数据量增大到上千万时需要考虑内存消耗和性能下降的问题
> 当只需要获取集合中 某子集的个数 而不需要 具体的数据集内容 时使用HLL - 基数统计

Redis内部使用两种不同的方式来存储：

- 稀疏Sparse  长度小于 hll-sparse-max-bytes = 3000，消耗更多CPU资源
- 稠密Dense

#### 3.6.1 常用命令

> 命令PF开头是为了向HLL数据结构发明者 Philippe Flajolet 致敬

- PFADD <key> <value> <value>
  自动去重统计

- PFCOUNT <key>

- PFMERGE <des> <key1> <key2>

  每天的统计，合并成周统计

#### 3.6.2 使用场景

- 统计注册 IP 数 
- 统计每日访问 IP 数
- 统计页面实时 UV 数
- 统计在线用户数
- 统计用户每天搜索不同词条的个数

### 3.7 Geo

> 地理位置信息；里面的member存储方式为zset,52位整数位score

#### 3.7.1 常用命令

- GEOADD <key> <longitude> <latitude> <member> [<longitude> <latitude> <member>]
  坐标会被内部转换成一个52位整数的的GEOHASH（坐标编码系统）；GEO的member实际上被存储为有序集合zset
- GEOPOS <key> <member>
- GEORADIUS <key> <longitude> <latitude> <raiusnum> <m|km|ft|mi> [WITHDIST] [ASC|DESC]
  获取距该经纬度 radiusnum 距离内的member；WITHDIST参数获得距离
- GEORADIUSBYMEMBER <key> <member> <raiusnum> <m|km|ft|mi> [WITHDIST] [ASC|DESC]
  member为中心
- GEODIST <key> <member1> <member2> <m|km|ft|mi>
  两个member之间的距离

### 3.8 键管理

> 键命名冒号分割

#### 3.8.1 常用命令

- DBSIZE  键个数

- 获取所有键

  KEYS *   阻塞

  SCAN 0

- 删除键

  DEL <key> [<key>]

  UNLINK <key>  异步删除大键

- EXPIRE <key> <seconds>

- PERSIST <key>

- TTL <key>
  查看剩余过期时间；-1 为没有过期时间，-2 为键不存在

- EXISTS <key>

- TYPE <key>

- RENAME <key>
  目标键存在时会先DEL删除，大键可能会阻塞。所以先EXISTS检测，再UNLINK，最后重命名

## 第三章 数据特性

> bitmap、SORT、键过期时间、管道、事务、发布订阅

### 3.1 位图

> 也被称为 位数组 或 位向量，基本组成位bit位
> 实际的底层数据类型是字符串，字符串的本质是二进制大对象BLOB-Binary Large OBject

### 3.1.1 常用命令

> 使用时需要考虑位图的疏密度，当位图很稀疏的时候使用集合替代

- SETBIT <key> <offset> <value>   0/1
- GETBIT <key> <offset>
- BITCOUNT <key>
- BITOP [AND|OR|XOR|NOT] <des> <key1> [<key2>]

### 3.2 设置键的过期时间

> 过期时间会存储为一个绝对的UNIX时间戳并持久化到RDB中
> 被动过期：客户端访问过期键时触发删除 + 基于概率的定时扫描清理删除（20个，25%，10s一次）；SCAN

- EXPIRE <key> <seconds>    |    PEXPIRE  毫秒级
- EXPIREAT <key> <UNIX>     |    PEXPIREAT
- PERSIST <key>
  SET、GETSET、*STORE会清楚过期时间；被另一没有过期时间的键重命名
- TTL <key>
  -1 为没有过期时间，-2 为键不存在

### 3.3 排序 SORT

> 列表、集合、有序集合的排序；O(N + M*log(M)) 大量数据排序时性能降低

- SORT <key> [ALPHA] [LIMIT <offset> <size>] [DESC|ASC]
  字符串元素的排序需要加 ALPHA选项

- SORT <key> BY pattern [DESC|ASC] [LIMIT] [GET pattern] [STORE <des>]

  pattern =  content* ，即以content + 内容的组合为键并取其值  排序
  值的外关联排序，如：

  ```shell
  SORT user:123:favorite_rest_ids BY rest_rating_* DESC GET rest_name_* STORE rest_name_sort_by_ranking
  # 时间复杂度为： O(N + M*log(M)), N 为容器中的元素总个数，M为返回元素个数
  ```

### 3.4 管道pipeline

> redis的单线程执行模型；pipeline用于打包命令，减少多次发送命令产生的1、4步网络时延
> 客户端发送命令 -> 服务器接收命令放入执行队列 -> 执行 -> 返回结果

```shell
# 以\r\n结束的易读命令
> cat pipcommand.txt
	set mykey myvalue
	sadd myset value1 value2
> unix2dos pipecommand.txt  # 每一行使用 \r\n 结束
# 构造resp的多命令
cat pipecommand.txt
	*3\r\n\$3set\r\n\$8\r\nkey_name\r\n\$5\r\nvalue\r\n*2\r\n\$4\r\nINCR\r\n\$5\r\nmykey\r\n
# --pipe 选项通过通道一次性发送来自stdin的命令
> cat pipecommand.txt | bin/redis-cli --pipe
```

### 3.5 Redis事务

> Redis事务没有回滚功能；保证了一致性 和 隔离性，不保证原子性 和 持久性

事务的两种错误

- 入队语法错误，事务命令入队时检测出语法错误，整个事务失败，所有命令不会执行
- 执行异常错误，其他命令正常执行，且不会回滚

```shell
127.0.0.1:6379> WATCH key1 # 监视键，使得事务有条件的执行：只有被监视的键在提交事务之前没有被修改过事务才有效
127.0.0.1:6379> MULTI  # 开启事务
127.0.0.1:6379> COMMANDS1
QUEUED
127.0.0.1:6379> COMMANDS2
QUEUED
127.0.0.1:6379> EXEC  # 提交事务
# DISCARD 放弃事务，退出事务状态
1) result1 
2) result2
```

### 3.6 发布订阅PubSub

> 非可靠消息传输，无法持久化

- SUBSCRIBE <channel1> <channel2>
- PUBLISH <key> <value>
- PUBSUB CHANNELS
  查看当前活跃的频道

### 3.7 Lua脚本

> 服务器端脚本语言，原子化执行的，类似于事务

#### 3.7.1 使用

> 单线程独占式执行，需要考量脚本执行的时间（默认执行时长限制lua-time-limit = 5s）

- ```lua
  -- 更新或新增json内容
  local id = KEYS[1]
  local data = ARGV[1]  	-- 下标从 1 开始  /**/
  local dataSource = cjson.decode(data)
  local retJson = redis.call("get", id)
  if retJson == false then
    retJson = {}
  else
    retJson = cjson.decode(retJson)
  end
  for k,v in pairs(dataSource) do
    retJson[k] = v
  end
  redis.call("set", id, cjson.encode(retJson))
  return redis.call("get", id)
  ```

- ```shell
  # redis-command
  EVAL script numkeys key [key ...] arg [arg ...]
  # redis-cli
  redis-cli --eval script.lua key1 [key2] , argv1 [argv2]  # "script"
  SCRIPT KILL #中止脚本执行
  # 注册缓存脚本
  SCRIPT EXISTS "scriptsha1id"
  redis-cli SCRIPT LOAD "`cat script.lua`" # 返回唯一 SHA-1 标识符
  # 只缓存在redis服务器进程中，重启后会丢失
  # 执行注册脚本
  redis-cli EVALSHA "scriptsha1id" numkeys key1 [key2] argv1 [argv2]
  ```

#### 3.7.2 调试

- 调试相关lua内嵌函数

  ```lua
  redis.debug(value)
  redis.breakpoint()
  redis.log(redis.LOG_WARNING, value)
  ```

- redis-cli调试启动ldb调试器

  ```shell
  # 创建单独的进程，不会阻塞；修改会回滚
  # --ldb-sync-mode 则会阻塞服务器
  redis-cli --ldb --eval script key1 [key2] , argv1 [argv2]  # 进入交互调试
  
  #######相关操作
  # s 步进执行
  # c 断点执行
  # p var 查看变量
  # w 查看脚本内容
  # b numline 设置断点行
  ```

## 第四章 使用Redis进行开发

### 4.1 常见应用场景

- 会话存储
  超时管理，后端服务器隔离
- 分析统计
  原子操作INCR、无需担心竞态问题
- 排行榜
  有序集合、权重值排序；ZRANGE ｜ ZREVRANGE
- 队列
  列表数据类型，LPUSH ｜ RPOP ｜ BRPOP
- 最新的N个记录
  LPUSH <key> <value>;   LTRIM <key> 0 N
- 缓存
  过期时间、LRU最近最少使用 等原子回收

### 4.2 数据类型使用原则

> 尽可能低的内存消耗

- 相关命令

  ```shell
  INFO [SECTION] # 查看redis实例信息， 
  	MEMORY				# 查看内存消耗
  	REPLICATION		# 查看主从复制
  	PERSISTENCE		# 查看持久化相关
  	CLUSTER				# 查看集群运行信息
  	KEYSPACE			#	查看键数据
  	COMMANDSTATS	# 命令处理相关统计
  SHUTDOWN SAVE			# 关闭redis实例
  ```

- 降低消耗 - 键
  减少数量
  压缩键值 cmsgpack库

### 4.3 API使用原则

- 数据操作组合在一起，降低往返时延（管道）
- 时间复杂度高于O(N)的API 谨慎使用，如：KEYS *、FLUSHDB、大键的删除HDEL

### 4.6 使用Python连接Redis

>redis-py

#### 4.6.1 同步redis

```python
import redis
class RedisUtil:
  r = None # type: redis.Redis
  
  @classmethod
  def init(cls, conn=None, host="127.0.0.1", port=6379, password="", db=0, **kwargs):
    if conn:
      cls.r = conn
    else:
      # 连接池
      # 客户端本地创建多个连接并保存在连接池，获取使用、交还；减少连接多次创建所造成的时间消耗
      pool = redis.ConnectionPool(host=host, port=port, password=password, db=db, **kwargs)
      cls.r = redis.Redis(connection_pool=pool)
  
  @classmethod
  def pipeline(cls):
    """管道
    pipeline.set("mykey", "myvalue")
    pipeline.sadd("myset", "value1", "value2")
    
    response = pipeline.execute()
    """
    return cls.r.pipeline()
  
  @classmethod
  def get(cls, key, default=None):
    res = cls.r.get(key)
    if res is None:
      return default
    return res
    
  @classmethod
  def lua(cls, file_path, keys=[], args=[]):
    """lua脚本"""
    with open(file_path) as f:
	    # 获取脚本内容
      code = f.read()
      # 注册脚本
      script = cls.r.register_script(code)
      
      return script(keys=keys, args=args)
  
  @classmethod
  def delete(cls, *names):
    """del为python保留关键字，重命名为delete"""
    return cls.r.delete(*names)
```

#### 4.6.2 异步aioredis

```python
class AsyncRedisUtil:
  r = None  # type: aioredis.Redis
  
  @classmethod
  def init(cls, host="127.0.0.1", port=6379, password="", db=0, **kwargs):
    cls.r = await aioredis.create_redis_pool(
      		f"redis://{host}:{port}", password=password, **kwargs
    )
    return cls.r  
```

## 第五章 复制

> 主从复制 -> Redis Cluster；默认主实例运行
> 容错性、水平扩展；主实例PING从实例、从实例发送REPLCONF ACK <offset> 报告当前复制偏移量
> 可能复制超时 会切断复制连接；当上述的两种通信在超时时间（预防阻塞）没有回复时就会超时
>
> 主实例切换需要从新同步，v4.0之后保留复制了先前实例的 master_replid 和 master_repl_offset 能接收部分同步

### 5.1 配置Redis的复制机制

```shell
# redis-slave.conf  从redis实例的配置
port 6380
pidfile /var/run/redis_6380.pid
dir /redis/slave    # 需要创建相应的目录 mkdir -p /redis/slave
slaveof 127.0.0.1 6379    # 支持命令行参数 动态创建从实例
##### 其他相关默认配置
slave-read-only yes   # 最好留以使主从实例数据一致
```

### 5.2 复制机制的调优

> ( master_replid、master_repl_offset )  版本快照标识
> repl-backlog-size = 1MB;  repl-disable-tcp-nodelay = yes 会合并小包，但是会有40毫秒的复制延迟

#### 5.2.1 同步机制

  **Rrplication Backlog**
	主实例的内存缓冲区(固定长度)，跟踪最近所有的写入命令（offset标识）

- 部分重新同步 - backlog缓存区命令；版本增量式
- 完全重新同步 - RDB存储文件复制到硬盘再传输、异步；新进程 内存开销
  repl-diskless-sync = yes 可以不复制到磁盘直接发送

## 第六章 持久化

> RDB、AOF 持久化到磁盘；结合使用

### 6.1 RDB

> Redis 在某个时间节点上的快照snapshot -> 备份和容灾恢复
> 恢复速度快、磁盘占用少；但无法保证非常强的一致性

**配置**

```shell
# 命令行
CONFIG GET save 												 # 获取持久化配置
CONFIG SET save  "" 	 									 # 禁用
CONFIG SET save "900 1 300 10 60 10000"  # 启用
# 配置文件
# save <internal> <numkeys>
save 900 1     # 多于1个小于10个key在保存之后变化，则会在900s-15min之后再次持久化更新
save 300 10
save 60 10000
# 手动触发RDB持久化
SVAE  # 阻塞式
SHUTDOWN SAVE 	# 配合关闭redis实例
BGSAVE  # 非阻塞式
```

**备份恢复**
	保存RDB快照文件，将备份文件复制到新的工作目录，并且保证启动redis实例的用户有该文件的读/写权限，再启动新redis实例，使用SHUTDOWN NOSAVE命令以防止覆盖的方式停止实例，重命名备份文件为 dbfilename 配置项指定的名字，重启redis实例

### 6.2 AOF

> Append-Only File 是一种只记录Redis写入命令的追加式日志文件，能保证更佳的一致性
> 命令先经过系统缓冲区阻塞式的同步存储到磁盘的aof文件（粒度可调整）
> 文件内容是resp协议字符串

**配置**

```shell
# 命令行
CONFIG GET appendonly
CONFIG SET appendonly yes/no
# 配置文件
appendonly yes/no
appendfsync always|everysec|no   # 缓冲区存入磁盘： 每一个命令 ｜ 每一秒 ｜ 操作系统决定 一般为30s
# 重写
BGREWRITEAOF
# 修复
redis-check-aof --fix appendonly.aof
```

**优化**
	BGREWRITEAOF    触发aof文件异步重写优化，清楚已删除、过期的键操作命令和只保留最新更新值

### 6.3 混合持久化

```shell
auto-use-rdb-preamble yes
# RDB转储、AOF日志记录
# 转储和重写不会同时进行
# 重写AOF文件时会优化 先把数据集一RDB的格式转存储到内存中并作为AOF文件的开始部分（AOF文件的开始部分有标识），重写之后继续追加式的传统AOF格式记录命令（数据和日志的结合）
# 恢复时 优先加载AOF，检查是否混合持久化，是则先加载RDB 再调用 AOF
```



## 第七章 配置高可用和集群

> 原生支持的高可用架构，Redis Sentineli、Redis Cluster
> CAP原则：一致性C、可用性A、分区容错性Partition tolerance
> BASE理论：Basically Available、SOft State、Eventually Consistent

**主从复制的问题**

- 需要人工切换主实例
- 数据量大时持久化和主从复制高延迟

### 7.1 Sentinel

> 充当主/从实例的守卫者（1对1），故障迁移基于多哨兵仲裁系统（至少三个以上） PING检测实例
> SENTINEL 会获得主从拓扑结构的最新消息-递归获取所有实例

**通信**

 ```shell 向主实例发送 INFO REPLICATION 获取主从拓扑结构向名为
 1. 向主实例发送 INFO REPLICATION 获取主从拓扑结构
 2. 向名为 __SENTINEL__:hello 的redis频道发布消息（自身及其监控实例的状态）
 ```



#### 7.1.1 配置

```shell
# 指定redis host
bind 127.0.0.1 192.168.0.xx # 同一台机器模拟只需要使用不同的端口即可
```



```shell
port 26379
dir /tmp
sentinel monitor <master-name> <ip> <port> <quorum>    # 所有的哨兵监控的都是当前的主实例
# quorum为采取故障迁移操作前发现并同意实例不可达的最少哨兵数
sentinel down-after-milliseconds <master-name> <sec>
```

#### 7.1.2 测试

```shell
SENTINEL FAILOVER <mymaster>  # 手动出发故障迁移
切换实例：
	1. 确认旧主实例 - 投票
	2. 进行故障迁移
	3. 选举新主实例 - 投票
	4. 同步 
```

#### 7.1.3 管理

```shell
SENTINEL [option] 
		GET-MASTER-ADDR-BY-NAME <mymaster>  # 获取master的信息 host + port
		MASTERS   # 查看被监控主实例的状态
		SLAVES <mymaster>  # 查看所有的从实例
		SET <mymaster> [sentinel-config-key value]
		#### 支持脚本触发
		# notification-script <mymaster> /path/to/script.ext 需要注意配合使用传递参数
```

### 7.2 Redis Cluster

> 多主节点，每个主节点有主从结构
> 集群运行时，每个节点会打开两个TCP套接字。第一个用于客户端连接；第二个用作实例间信息交换的通信总线（端口号为第一个端口号 + 10000，索引实例监听端口必须小于55536）
> **集群模式** 下只能使用 **一个** 数据库空间，即 db0

#### 7.2.1 配置

```shell
# 单节点配置， 无法同时使用 replicaof 配置
daemonize yes
pidfile "/path/to/redis-xxxx.pid"
port xxxx
bind xxx.xxx.xxx.xxx
logfile "/path/to/file.log"
dbfilename "dump-xxx.rdb"

cluster-enabled yes
cluster-config-file nodes-6379.conf  # 启动时自动生成
cluster-node-timeout 10000
```

```shell
# redis 命令行操作  -c 指定集群模式下
1. 发现对应节点
CLUSTER MEET <host> <port>   
2. 哈希数据槽分配 固定 16384 个哈希槽
for i in {start..end}; do redis-cli -h <host> -p <port> CLUSTER ADDSLOTS $i; done 
# 0 - 5400 ; 5401 - 11000 ; 11001 - 16383
# key 分配数据槽 HASH_SLOT = CRC(key) mod 16384
3. 查看集群节点信息
CLUSTER NODES
CLUSTER INFO
CLUSTER FAILOVER
CLUSTER SALVAES
4. 设置主从结构
CLUSTER REPLICATE <nodeid>   # 被选中的从节点必须是空的且没有分配数据槽
5. 使用
redis-cli -h <host> -p <port> -c  # 需要指定集群模式连接
```

## 第八章 生产环境部署

> Linux；配置调整、日志

**服务器优化**

```shell
# 内存相关  /etc/sysctl.conf  
# sysctl [config]
# echo "" >> /etc/sysctl.conf
sysctl -w vm.overcommit_memory=1   # 内存分配
sysctl -w vm.swappiness=0  # 交换区大小

# 禁用透明大页功能（transparent huge page）
cat >> /etc/rc.local << EOF
echo never > /sys/kernel/mm/transparent_hugepage/enabled
echo never > /sys/kernel/mm/transparent_hugepage/defrag
EOF

# 网络优化  echo "" >> /etc/sysctl.conf
sysctl -w net.core.somaxconn=65535 
sysctl -w net.ipv4.tcp_max_syn_backlog=65535

# redis进程打开最大文件数
# 必须小于/proc/sys/fs/file-max的值
su - redis
ulimit -n 288000
cat >> /etc/security/limits.conf << EOF
redis soft nofile 288000
redis hard nofile 288000
```

**安全相关**

```shell
include /path/to/file.conf
# 使redis只监听UNIX套接字连接，而不监听任何网络接口

# redis密码开启
	## 主实例
requirepass password
	## 从实例
masterauth password

# 命令重命名和禁用
rename-command <ocommand> <ncommand>
rename-command <ocommand> ""      # 禁用
```

**客户端**

```shell
# 网络参数
timeout 0 # 客户端空闲N秒后关闭连接
tcp-backlog 511 # 刮起套接字请求队列的大小
# 客户端数量和keepalive时间
maxclients 10000
tcp-keeplive 300
# 客户端缓冲区参数
client-output-buffer-limit normal 0 0 0
client-output-buffer-limit slave 512mb 256mb 60
client-output-buffer-limit pubsub 32mb 8mb 60
```

**内存配置-淘汰机制**

```shell
# 达到maxmemory限制时相应的动作
no-eviction				不淘汰，直接报错
allkeys-lru				最近最少使用
volatile-lru			使用最近最少使用淘汰超时键，没有符合条件的键则使用no-eviction
allkeys-lfu				最不常使用
volatile-lru
allkeys-random		随机淘汰
volatile-random
volatile-ttl			淘汰马上要过期的键
```

**基准测试**

```shell
redis-benchmark 命令
```

**日志配置**

```shell
# 日志格式
pid:role timestamp loglevel message
role: 
	X  Sentinel
	C  RDB/AOF wrting child
	S  Slave
	M  Master
loglevel:
	.  debug
	-  verbose
	*. notice
	# warning
# redis.conf
# CONFIG SET
loglevel notice	# 从低到高：debug、verbose、notice、warning；一般notice足矣；
# 空字符串将日志输出到标准输出；开启守护进程后台运行则会重定向到/dev/null丢弃
logfile "path/to/redis-server.log"

```

## 第九章 管理Redis

> 服务器配置、redis-cli、备份恢复、内存使用、客户端和数据迁移

### 9.1 管理服务端

```shell
CONFIG GET/SET
CONFIG REWRITE  		# 将当前配置持久化到配置文件，前提是必须指定配置文件启动。默认配置文件不修改
INFO STATS					# 统计数据
CONFIG RESETSTAT		# 重置INFO命令报告的统计项
```

### 9.2 redis-cli操作

```shell
redis-cli -p <port> --[raw | csv] COMMAND
# 最后一个参数接收标准输入
echo "bar" ｜ redis-cli -p <port> -x SET foo
# 管道批量命令
unix2dos commands
cat commands | redis-cli -p <port> --pipe
# 间隔重复执行
redis-cli -r <count> -i <delay> COMMAND
# 扫描指定键
redis-cli --scan --pattern "str:*xxx"   # 正则匹配
```

### 9.3 备份和恢复

```shell
# crontab 备份
crontab -e
0 0 * * * sh /usr/local/redis/script/redis_rdb_backup_daily.sh
# 脚本内容：取日期、删除当前已存在和不需要保存的、复制当前的rdb
```



```shell
# RDB备份，一般使用 crontab
BGSAVE
# 恢复
## 检查AOF
CONFIG SET appendonly no  # 会先从AOF恢复，无则从空数据集开始，使用时键改动触触发RDB备份，原备份会被覆盖
CONFIG REWRITE  # 关闭aof并持久化到配置文件
## 关闭服务器， 删除原AOF和RDB文件
SHUTDOWN
rm *.aof *.rdb
## 备份文件移动替换，并设置正确的权限
chown redis:redis dump.rdb
chmod 777 dum.rdb   # 文件所属用户、文件所属组、其他人。读=4、写=2、执行=1
redis-server conf/redis-server.conf 
## AOF重新启用 如有必要的话
```

### 9.4 监控内存使用

```shell
INFO MEMORY  # 整个实例
MEMORY USAGE <key>
MEMORY STATS  # 内存消耗的每个部分
MEMORY DOCTOR
```

### 9.5 管理客户端

```shell
INFO CLIENTS  # 统计数据
CLIENT 
	LIST										# 详细信息
	SETNAME <name>					# 设置当前连接的别名标识
	KILL <chost>:<cport>		# 断开
	PAUSE <millsec>					# 暂停；复制机制不受影响进行数据迁移
	
```

### 9.6 数据迁移

```shell
# 主从复制迁移
SLAVEOF <originhost> <originport>
SLAVEOF NO ONE
# AOF, 需要都启用AOF持久化 且 appendobly=yes; aof-use-rdb-preamble=yes
origin > BGREWRITEAOF  # AOF重写优化； 然后停止目标实例，复制到目标实例db目录下，最后重启
```

## 第十章 Redis的故障诊断

> 慢日志、慢查询、延迟、内存、进程崩溃

### 10.1 健康检查

```shell
INFO STATS  # 静态总体统计数据
redis-cli --stat  # 持续监控
```

### 10.2 SLOWLOG

```shell
# 配置
CONFIG SET slowlog-log-slower-than 10000  # 微秒 默认 10 毫秒


SLOWLOG 
	GET		# 获取所有日志
	LEN		# 数量
	RESET	# 清除
```

### 10.3 延迟问题

- 慢命令

  ```shell
  INFO COMMANDSTAS
  ```

- CPU

  ```shell
  ps aux | head -1; ps aux | grep redis-server #  获取头行
  ```

- 连接

  ```shell
  INFO STATS | grep total_connections_received
  ```

- 持久化 - AOF缓冲区系统调用、IO读写、交换空间内核阻塞

  ```shell
  INFO | grep fork   # 最后一次fork耗费的时间，持久化创建子进程
  INFO | grep aof_delayed_fsync
  INFO | grep aof_pending_bio_fsync
  INFO | grep process_id		# 是否使用了交换空间
  less redis.log  # 查看是否有缓慢的AOF fsync
  iostat 1				# 持续查看io
  ```

- 网络拥塞

### 10.4 内存问题

```shell
INFO MEMORY | grep "used_memory_human|maxmemory_human"
INFO MEMORY | grep "used_memory_dataset|used_memory_dataset_perc"
# 大键搜索
redis-cli --bigkeys
```

### 10.5 崩溃问题

```shell
GDB 调试
```

## 第十一章 Redis模块

> 共享的C语言库，可以创建新的数据结构、命令直接调用、运行速度快（扩展开发）

### 11.1 加载模块

> ReJSON模块

```shell
# 配置文件加载
loadmodule /target/xxxx.so
# 启动加载
redis-server --loadmodule /target/xxxx.so		# Macos 为 dylib
# 命令加载
MODULE 
	LOAD /target/xxxx.so
	UNLOAD <modulename>
	LIST
```

### 11.2 编写模块

> C语言

```c
#include "redismodule.h"

int RedisModule_OnLoad(RedisModuleCtx* ctx,  RedisModuleString** argv, int argc);
int MyModule_Zip(RedisModuleCtx* ctx,  RedisModuleString** argv, int argc);
static RedisModuleString* ListPopRPush(RedisModuleKey* ListKey);

// 逻辑实现
```

```shell
# 编译
gcc -fPIC -shared -std=gnu99 -o mymodule.so mymodule.c
```

## 第十二章 Redis生态系统

> 第三方组件：工具、客户端、代理

