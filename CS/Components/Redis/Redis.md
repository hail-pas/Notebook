# Redis 缓存系统
	 数据：安全稳定第一位
	 key-value NoSQL
	 提高访问速度、减少数据库访问
	 NoSQL-Not Only SQL； 泛指非关系型数据库
	 Web2.0    User Generate Content  - SNS(Social Network Society)
	 用户产生数据存储，关系型数据库乏力
	 架构
			Redis ----  Process(Memory) -----  DB
----
## NoSQL
- 分类
	- 键值(key-value)存储数据库    --key hash
		 value无结构化
	- 列式存储数据库
		 分布式存储海量数据， 键指向多个列
	- 文档型数据库    --mongoDB
		 键值； value数据半结构化文档格式统一； 类似jason
	- 图形数据库
- 应用
	  数据模型简单
	 灵活性要求高
	 数据库性能要求高
	 数据一致性要求低
	 给定key值，能较容易映射复杂值的环境
----
## Redis    --单进程、单线程 -> IO多路复用epoll
	key-value nosql 数据库
	只存储在内存，value类型多
	Redis会周期性的把更新的数据写入磁盘或者把修改操作写入追加的记录文件，并且在此基础上实现了master-slave(主从)同步
			 手动持久化   save
			 自动周期时间配置
					save 900 1      --多于1个小于10个key在保存之后变化，则会在900s-15min之后再次持久化更新
					save 300 10      save 60 1000    --变化越频繁，保存周期应该越短，增加持久化数据的可用性
	Redis是非常快，Redis 的操作都是原子的
- value类型
	 string(字符串)、list(列表)、set(集合)、zset(sorted set有序集合)、hash（哈希类型）
				 hash是一个string类型的field和value的映射表。添加和删除操作都是O（1）（平均）的复杂度；field唯一
----
## python连接
	 redis模块
- 单命令连接
	 提供两个类Redis和StrictRedis用于实现Redis的命令，StrictRedis用于实现大部分官方的命令，并使用官方的语法和命令，
	 Redis是StrictRedis的子类，用于向后兼容旧版本的redis-py
import redis
remand = redis.Redis(host='', port=6379, db=0, password="")
remand.set('foo', 'Bar')     --命令
result = remand.get('foo')
- 管道批量命令连接    --连接池，使用匹配执行命令，统一提交要么都成功/失败
import redis
pool = redis.ConnectionPool(host='', port=6379, db=0, password='')    --暂存。连接池交互
remand = redis.Redis(connection_pool=pool)      --redis实例
pipe = remand.pipeline(transaction=True)          --实例声明pipeline
pipe.set('', '')
pipe.set('', '')
pipe.execute()              --执行
----
## 订阅-发布    --需要在线收听
remand = redis.Redis(host='10.211.55.4')
=======发布，指定频道、信息
remand.publish(chan, msg)
=======订阅指定频道、收听解析信息
subscriber = remand.pubsub()
subscriber.subscribe(chan)
suscriber.parse_response()

## 操作 Key-value
	 启动 redis-server  redis.conf
	 redis-cli   连接
	 索引从0开始， -1为最后一个元素
- 连接命令行       --配置密码的情况下
	 auth password
- db
	 redis 生成最多16个db独立内存，相互之间，互不影响
	 select num    --切换， 0-15
- 通用常见命令    --都支持模糊匹配
	 save
	 type key
	 scan 0 match z*
	 delete key     --del
	 keys key    --*  所有key值
	 exists key
	 expire key time
	 rename src tar
	 move key db    --存在同名的移动失败
	 randomkey
### String
- 命令
	 set key value []
			 参数：
			 ex num ，过期时间（秒）    --> setex
			 px num ，过期时间（毫秒）   --> psetex
			 nx ，又该参数时，则只有name不存在时，当前set操作才执行（创建） --> setnx
			 xx ，又该参数时，则只有name存在时，当前前set操作才执行（修改）
	 mset  批量
	 del key
	 get key
	 mget key key
	 getset key value      --修改并返回旧值
	 getrange key start_n end_n
	 setrang key offset_n value    --从offset处往后覆盖修改
	 setbit key offset_n 0/1     --位修改，字符串中字符对应的ascii编码序号变成二进制
	 getbit key offset_n
	 bitcount key                -- 1的数量
			  ord("") - chr(int)
			  bin(int)
			  高效应用：访问用户id统计及查询是否访问      每个用户占其id 的那一个二进制位
						  set access_users ""     # 比特位全0
						  用户访问时  setbit access_users id 1
								查询是否访问      getbit access_users id        --为1则访问过，否则为0
								总访问人数        bitcount access_users
	 strlen key    --字节长度
	 incr key     --增加1
	 incrbyfloat key float
	 decr key     --减少1
	 append key value   --增加
### hash     --关联String
	  name --> {key ,value }
- 命令
	 hset name key value [key value]
	 hget name key [key]
	 hdel name key [key]      --del 删除整个hash name
	 hgetall name     --获取所有key、value； hkeys/hvals
	 hsan name 0 match a*    --匹配查询
	 hlen name       --key数量
	 hexists name key
	 hdel name key
	 hincrby name key 1     --增加； byfloat
### list
	  key --> [value, value]
	 	l - r
- 命令
	 lpush key value value    --创建，不需要声明; 左边先进入
	 lpushx key value       --已存在添加，必须已存在
	 lset key index value     --修改
	 linsert insert｜after value new_value      --插入指定位置
	 lrange key start end
	 lrem key count value   --删除值
	 lpop key
	 lindex key index    --取指定索引值
	 ltrim key start end    --截取
	 rpoplpush src tar     --列表关联移动元素操作
	 brpoplpush src tar timeout   --block 阻塞时长
	 blpop key key timeout    --将多个列表排列，按照从左到右去pop对应列表的元素； pop完后等待数据的timeout；0永久等待
### set集合

- 命令
	==========================无序集合
	 sadd key value value
	 scard key    --返回集合中value个数
	 srem key value value   --删除
	 smembers key    --取出所有元素
	 srandmember key count    --获取count个随机元素
	 sscan key 0 match *a
	 sismember key value   --检查是否有某value
	 smove src tar value    --移动
	 spop key     --右侧删除
	 关系
		- 差集s1-s2
			  sdiff s1 s2   => s1-s2
			  sdiff result s1 s2
		- 交集
			 sinter s1 s2
	===========================有序集合z  权重
	 zadd nx|xx score value score value      --按权重排序
	 zrange / zrevrange / zrangebyscore
	 zrank key value    --值的权重排名
	 zscore key value    --值的分数、权重
	 zremrangebyrank key min max     --按权重删除
	 关系
		- 交集
			 zinterstore tar num s1 s2 aggregate sum -获取两个有序集合的交集，如果遇到相同值不同分数，按aggregate=sum/min/max处理
		- 并集
			 zunionstore
	 zscan key 0 match x*     --模糊查询
