# Effective Python
> 59个有效方法； 编程：定义类（数据、数据交互方式） + 处理类之间的关系
> www.effectivepython.com
----
## 数据
```python
# 弱引用
import weakref
dic_name = weakref.WeakValueDictionary()
dic_name["key"] = value  # 指向的value被垃圾回收时，对应的key也会自动删除
```
----
## 异常处理

```python
try/except/else/finally
# else
try:
  target_dict = json.loads(data)
except ValueError as e:
  handle_error(e) or raise
else:
  return target_dict   # 上一个语句快未执行的情况下 - except
# 文件操作 - try和else 切分处理逻辑
获取文件句柄（IOError）
try:
  读取文件
except:
  异常处理
else:
  处理文件内容
finally:  # 收尾
  关闭文件句柄
```
----

## 函数

> 函数是一级对象直接引用

1. 函数返回值

   ```python
   True/False, value/None --替代--> value/None
   status, result
   抛出异常 --代替--> None
   ```

2. 闭包 -> 变量调用 - 类封装

   - 定义在某个作用域中的函数，该函数能饮用这个作用域里的变量

   ```python
   默认赋值修改的方式无法影响外层作用域变量
   # nonlocal-函数/global-模块 --> 防止局部变量污染函数外作用域的变量
   # 使用类封装 取代 nonlocal
   属性 = nonlocal 变量 --> 修改保存
   # 引用类型  替代 nonlocal
   # 变量名 _ 指代不需要使用的变量
   ```

3. 生成器 - 大数据集

   ```python
   # 生成器取代返回列表
   # 可迭代对象 - 容器
   __iter__()  # for调用
   # 迭代器 - 生成器是特殊优雅的迭代器
   __iter__()
   __next()__
   	# 内置iter函数: 可迭代对象 -> 生成器
     		- 传递的参数是迭代(生成)器 -> 返回原迭代器
       	- 传递的参数是可迭代对象 -> 返回新的迭代器
         if iter(tar) is iter(tar): 
            => tar is a generator
   # 生成器 -> 可迭代对象
   class GetItem(object):
     def __init__(self, iter_data_src):
       self.data = iter_data_src
     def __iter__():
       for item in self.data:
         yield item
   ```

4. 参数

   ```python
   # 位置参数、关键字参数、不定参数   --后两者在引用的时候都可以是可选的（关键词参数设置默认值）
   # *args - args可为生成器
   # 参数的默认值只在函数定义的时候生成，后续不会改变  -eg（ time=datetime.now() ）
   	动态 不定类型 关键字参数：
     		(time=None)
       	""" 描述实际行为 """
         time = datetime.now() if time is None else time
   # 关键字参数 = 引用类型 -> 只在函数定义时创建一个引用类型，后续则是共享 None解决
   # 只能以关键字形式指定的参数 - * 分隔
   		def func(posi_arg, posi_arg, *, key_arg=default, key_arg=default) 
     	**kwargs ->
       		kwargs.pop(, default)  --取出所需要的
         	if kwargs:
             	raise TypeError("msg")
   ```

----

## 类与继承

1. 数据、状态维护

   ```python
   self.__class__.__name__
   # 取代字典和元组 - 字典嵌套、过长元组
   	1. collections.namedtuple("Grades",("score", "weight"))   # 内部封装命名元组类,无默认值，下标
     2. 类定义 - 基本数据 + 容器
     			基本数据：																 容器：  
       			class Subject(object):					｜ 			class GradeBook(object):
         		class Student(object):					｜				--最外引用
   ```

2. 钩子函数 - lambda函数式参数

   ```python
   函数作为参数传递 - hook钩子  # 可以是类封装起来的函数，一般使用call
   .sort(key=lambda x:len(x))
   ```

3. 类的多态构建 - @classmethod

   ```python
   class Cls():
   		@classmethod
   		def create(cls, config):  # cls类似self，占位标识
         # 解析config进行动态的创建
   ```

4. 初始化父类 - super

   ```python
   # 简单继承体系 - 多继承的时候会产生无法预知的行为
   BaseClass.__init__(self, *args)
   # 菱形继承问题 - { Base; Senior1(Base), Senior2(Base); Gson(Senior1, Senior2) }
   # 基类__init__被多次执行
   => super  # 定义方法解析顺序； 深度优先，从左至右
   	MRO顺序：类.mro() 栈
     python2: super(SubClass, self).method(*args)
     python3: super(__class__,self).method(*args) = super().method(*args)
   ```

5. Mix-in组件

   ```python
   # 多重继承，通用功能模块提取封装 -> 复用
   ```
   
6. private属性

   ```python
   public - var_name
   protected - _var_name  # 说明字段的合理用法
   private - __var_name. =>  _clsname.__var_name
   # 私有属性使用 - 避免与子类（不可控时）的属性名重名
   ```

7. 自定义容器类型 - collections.abc

   ```python
   # 内置容器类型 - 继承添加功能函数 super().__init__()
   list、tuple、set、dict
   # 继承 collections.abc 的抽象容器 or 自定制magic方法
   # 定制方法
   _search(self, count, index)  # 做为辅助功能的保护类
   __getitem__(self, index):  # 下标取值， setitem(self, index, value)
     	found, _ = self._search(0, index)
       if not found:
         	raise IndexError("Index out of range")
       return found.value
   __contains__(self, value):  # in 判断  
   ```

----

## 元类及属性

> 动态的定义对属性的访问操作

1. 方法属性化/对象化 - 描述符协议（get/set）

   ```python
   # 属性的 getter 和 setter； 同名函数重载; 无副作用、简洁使用
   # 赋值的时候可以定义关联操作
   @property
   def varname(self):
     	return self.varname
   @varname.setter
   def varname(self, value)
   		# 防止父类属性被修改
     	if hasattr(self, '__ohms'):
         	raise(AttributeError("Can't set attribute"))
   # 代替属性重构（实时、动态计算） - 漏桶算法（容器、配给）
   @property
   def varname(self):
     	return self.varname * size  # 运算之后再返回
   # 复用属性的描述符协议 - 处理逻辑类似的字段值 变成 对象 (校验、限制等)
   	# 实现了 __set__ 和 __get__ 方法的对象
     # object的 __getattribute__ 方法进行转译
     class Exam(object):
        math_grade = Grade()
        writing_grade = Grade()
     class Grade(object): # 数据对象
        def  __init__(self):
            self._value = 0
        def __get__(self, instance, instance_type):
         	 return self._value
        def __set__(self, instance, value):
         	 if not (0 <= value <= 100):
             	raise ValueError()
            self._value = value
        # 上面这种当调用类中有多个字段使用 描述符 对象时会只有一个Grade实例，定义Exam时创建的一个
     class Grade(object):  # 数据对象中的不同 实例: 值  字典保存
        def __init(self):
           # self._value = {}   内存泄露
           self._value = WeakKeyDictionary()
        def __get__(self, instance, instance_type):
         	if instance is None: return self
           return self._value.get(instance, 0) # getattr(instance, self.comment, "")
        def __set__(self, instance, value):
         	 if not (0 <= value <= 100):
             	raise ValueError()
     			 self._value[instance] = value
        # 内存泄露，引用计数无法降为0，无法回收 ==> 使用 WeakKeyDictionary()
   ```

2. 属性按需生成

   ```python
   访问不存在的属性 => __getattr__ => __setattr__ => __dict__
   对 getattr 行为记录 => 继承、super().__getattr__(name)  # 首次 
   属性访问 => __getattribute__ --不存在-->  __getattr__
   # 防止无限递归 - 引用对象
   # 在 类似方法里 **访问** 实例属性，应该直接通过 super() 来获取
   解决 - super
       def __getattribute__(srlf, name):  # set 类似
           data_dict = super().__getattribute__("_dict")
           return data_dict[name]
   def __getattribute__(self, name):  # 属性获取 - 高优先级
      logging
      try:
       	return super().__getattribute__(name)
      except AttributeError:
       	value = ""
         setattr(self, name, value)
         return value
   def __getattr__(self, name):  # 属性获取 - 不存在
       logging
       setattr(self, name, value):  # __setattr__ 
       return value
   def __setattr__(self, name, value): # 属性赋值
     	logging
       super().__setattr__(name, value)
   ```

3. 元类 - 子类

   ```python
   # 自定义元类 - 继承自 typing.Type
   # class语句定义时的挂钩
   class Meta(Type):
     	def __new__(meta, name, bases, class_dict):  # 子类定义时发送调用
         # meta 元类
         # name 子类名
         # bases 父类
         # class_dict 子类属性/方法字典
         if bases != (object,):
           	if ....
         return type.__new__(meta, name, bases, class_dict)
   # 使用
   class Subclass(object, metaclass=Meta):
   # 元类检验子类 - 定义是否正确（风格、方法、属性 => init < 在Meta.__new__中添加参数的逻辑验证(针对子类)
   		# 使用 __new__函数，子类在整个class与具体处理完毕后 会 调用其元类的__new__函数
   # 元类注册子类 - 简单标识符 映射 类  {序列 和 反序列}
   		# __new__ 预先生成
     	def __new__(meta, name, bases, class_dict):
         	cls = type.__new__(meta, name, bases, class_dict)
           func(cls)  # 一定需要的 子类操作逻辑
           return cls
   # 元类注解类属性
   		def __new__(meta, name, bases, class_dict):
       		for key, value in class_dict.items():
           		if isinstance(value, Field):
               		value.name = key
                 	value.comment = "comment"   # 配合描述符协议
               cls = type.__new__(meta, name, bases, class_dict)
               return cls
       # 描述符
       	class Field(object):
            def __init__(self):
               	self.name = None  # 元类分配
                 self.commnet = None
            def __get__(self, instance, instance_type):
             		if instance is None:
                 		return self
                 return getattr(instance, self.comment, "")
            def __set__(self, instance, value):
             		setattr(instance, self.comment, value)
   ```
## 并发与并行

1. subprocess模块 - 子进程

   ```python
   # popen、os.exec
   proc = subprocess.Popen(["command", "arg"], stdout=subprocess.PIPE)
   out, err = proc.communicate()  # 执行，out.decode("utf-8")
   proc.poll()
   # 子进程 传输/获取 数据
   try:
     	proc.communicate(timeout=1.5)
   except subprocess.TimeoutExpired:
     	proc.terminate()  # kill()
       proc.wait() 
   # 构造
   	Popen(
       ["COMMAND", '-c', args[0], args[1], ...], 
       stdin="输入", 
       stdout=subprocess.PIPE
     )
   # 方法
   	communicate(input=None, timeout=None) # 与进程交互：向 stdin 传输数据。从 stdout 和 stderr 读取数据，直到文件结束符。等待进程终止。可选的 input 参数应当为被传输给子进程的数据，如果没有数据应被传输给子进程则为 None。如果流以文本模式打开， input 必须为字符串。否则，它必须为字节
   	poll() # 检查子进程是否已被终止。设置并返回 returncode 属性。否则返回 None
     wait() # 等待子进程被终止。设置并返回 returncode 属性
     proc.terminate()  # kill()
   # 属性
   	args
     stdin/stdout/stderr
     pid # 子进程的进程号
     returncode # 一个 None 值 表示此进程仍未结束。一个负值 -N 表示子进程被信号 N 中断 (仅 POSIX)
   ```

2. 多线程处理阻塞式I/O任务 - Lock/Queue

   ```python
   # GIL 影响python代码的单一执行，不会影响系统调用
   # asyncio
   # Lock - 防止数据竞争
   with Lock():
     	......   #互斥的执行该代码
   class LockingData(object):
     	def __init__(self):
         	self.lock = Lock()
           self.data = 0
       def change(self, value):
         	with self.lock:
             	self.count += value
   # Queue 协调各线程间工作 - 管线
   	# 环节  - 函数 ==> 组合（任务传递方式）
     # 队列 worker
     	# 自编队列 （无缓冲区控制、阻塞）
         class LockQueue(object):
             def __init__(self):
                 self.items = deque()
                 self.lock = Lock()
             def put(self, item):
                 with self.lock:
                     self.items.append(item)
             def get(self):
                 with self.lock:
                     self.items.popleft()
       # queue.Queue - { get()、put() ｜ task_done()、join()}
       	queue = Queue(buffer_size)
         queue.task_done() 	# get后处理完成，设置队列数据减一的信号到队列，标示使用数据的当前任务结束
         queue.join()  # 监控queue是否为空，阻塞挂起直到队列为空（ task_done() 清空 ）的信号，全部结束
     class Worker(Thread):
       def __init__(self, func, in_queue, out_queue):
         	super().__init__()
         	self.func = func
         	self.in_queue = in_queue
         	self.out_queue = out_queue
         	self.polled_count = 0
         	self.work_done = 0
     	def run(self):
         while True:
           	self.polled_count +=1
           	try: # 自己判断队列是否为空
               	item = self.in_queue.get()
             except IndexError:
               	sleep(0.01)
             else:
               	result = self.func(item)
                 self.out_queue.put(result)
                 self.work_done +=1
       # start() 函数启动  
       # polled_count 为 sleep() 或 其他信号中断的次数
   # =======应用=======
   download_queue = LockQueue()
   resize_queue = LockQueue()
   upload_queue = LockQueue()
   done_queue = LockQueue()
   
   threads = [
     Worker(download, download_queue, resize_queue),
     Worker(resize, resize_queue, upload_queue),
     Worker(upload, upload_queue, done_queue)
   ]
   ```

3. 协程 - 函数并发

   ```python
   # 生成器 -- next=>send
   yield value/func()
   yield from 
   next(Gen)
   Gen.send(value)
   ```

4. concurrent.futures 真正的平行计算 - 复杂运算

   ```python
   # 平行计算方案：1、C语言扩展模块； 2、内置的 concurrent.futures 模块
   multiprocessing - Process/Thread(PoolExecutor) # 消耗：主进程 和 子进程 之间 序列化 和 反序列化
   multiprocessing 复杂、功能强大
   concurrent.futures - Process/ThreadPoolExecutor
   ```
   
   ## 内置模块 - Batteries Include
   
5. functools.wraps 定义函数修饰器

   ```python
   # 访问原函数 及其 参数、返回值；执行前后添加附加代码（约束、调试、注册）
   # 复制__name__、__annotations__、__doc__ 等
   def deco(func):
     	@wraps(func)   # 将被装饰函数的重要元数据（name、module）复制到外围函数 deco，保持函数信息一致性
     	def wrapper(*args, **kwargs):
         	return func(*args, **kwargs)
       return wrapper
   ```

6. contextlib模块 + with语句 代替 try/finally

   ```python
   # lock mutex
   lock = Lock()
   	######
     lock.acquire()
   	try:
   	  # holding the lock
   	  # do something
   	finally:
   	  lock.release()
     ######
     with lock:
       # holding the lock
   	  # do something
   # 标准上下文管理器下发：类 + __enter__、__exit__
   # 简便：contextlib 的 @contextmanager
   try/finally 的 with 用法
   @contextmanager  # 函数支持with语句
   def debug_logging(level, name):
     	logger = logging.getLogger()
       old_level = logger.getEffectiveLevel()
       logger.setLevel(level)  # with 语句内准备
       try:
         	yield name  # 返回的上下文对象，块内相关代码执行调用
       finally:   # with 结束后执行
         	looger.setLevel(old_level)
   with debug_logging(logging.DEBUG) as logger:  
     	# doing something
       # related_fun()  
   # 上下文管理对象赋值
   with ... as v_name:
     	# ...
   
   ######## 异步上下文装饰器
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
           await redis.eval("""
               if redis.call("get", KEYS[1]) == ARGV[1]
               then
                  return redis.call("del", KEYS[1])
               else
                  return 0
               end
            """, [key], [v])  # eval("""xxx""", KEYS=[], ARGV=[]), 下标从1开始； 
   ```

7. copyreg 实现可靠 pickle

   ```python
   # json 是可靠、安全的
   
   ```

8. datetime处理本地时间

   ```python
   # UTC - Coordinated Universal Time
   # time => UTC 和 计算机当地时区 转换
   # datetime. {datetime、timezone}    配合 pytz 使用
   time_str = "2020-02-02 20:00:02"
   time_tuple = datetime.strptime(timestr, time_format)  # 元组时间
   sh_tz = pytz.timezone("CN/Shanghai")
   sh_time = sh_tz.localize(time_tuple)
   utc_time = pytz.utc.normalize(sh_time.astimezone(pytz.utc))  # 操作
   sh_time = sh_tz.normalize(utc_time.astimezone(sh_tz))  # 转换回来
   ```

9. 内置算法和数据结构

   ```python
   # 双向队列
   collections.deque - FIFO { append(""), popleft() }
   # 有序字典
   collections.OrderedDict - 键的插入顺序
   # 带默认值的字典
   defaultdict()  # 直接运算，无需先判断赋值
   # 堆队列（优先级队列） - heapq模块 - 基于 列表
   a = []
   heappush(a, value)
   heappop(a)
   assert a[0] == nsmallest(1, a) == smallest_value
   # 二分查找 - bisect模块
   bisect_left(list, value)
   # 迭代器相关 - itertools
   	# 链接迭代器
     chain、cycle、tee、zip_longest
     # 过滤元素
     islice、takewhile、dropwhile、filterfalse、
     # 组合元素
     product、permutations、combination
   
   ```

10. 高精度 - Decimal 类

    ```python
    num_2 = Decimal(str(ceil(num * 100) / 100))  # 上取并保留两位小数
    # quantize
    num = 5.365
    result = num.quantize( Decimal("0.01"), rounding=ROUND_UP )  # 5.37
    # 精度不受限制的Fraction类 （fractions.Fraction）
    ```

## 协作开发

1. 编写文档字符串

   ```python
   # python的代码和文档关联，运行过程中可以直接访问源代码中的文档信息
   __doc__ => """ docstring """
   help() 查看文档字符串
   # 文档规范
   1. 模块顶级文档 - 文档字符串开始
   	 """ Summary
   	 Detail Describe
   	 """
   2. 类文档 - """ Sum、类行为、期望子类行为、Important Method/Attr """
   3. 函数文档 - """ Sum、功能、Args、Returns """
   4. 协程 - """ yield产生/接纳的值、何时停止迭代 """
   ```

2. 包 - 模块 - 函数

   ```python
   # 模块之上的抽象层
   ## 定义
   	__init__.py  空文件的目录
   	from package import module
   ## 名称空间包 - 灵活定义、不同目录
   	路径区分
     from apackage.utils import inspect as a_inspect ｜ import apackage.utils
     from bpackage.utils import inspect as b_inspect ｜ 最高路径引用
     # 引入机制-深度优先
     	1. sys.path指定路径中，搜寻引入模块
       2. 从模块中加载代码，保证其能正确编译
       3. 创建与该模块对应的空对象
       4. 添加该空模块对象到 sys.modules
       5. 运行模块对象的代码，定义其内容
       循环依赖：
       	1. 数据结构独立，放在依赖树的最低层 - 重构代价大
         2. 调整引入顺序，不要一直在顶端引入 - PEP8
         	2.1 动态引入 - 需要的地方再引入
         3. 先引入、再配置、最后运行 - 模块只提供定义、不会执行引用
   ## 包/模块的可引入列表 - 隐藏内部结构 - 外部api引用
   	__init__.py 
     __all__ = [" "," "]  # 没有则默认只会引入 public 属性
     pkg.__all__ += mod__all_  
     # 只需要引入包的属性即可使用，mod对外不可见  from pkg import *
     # import * 可能会导致不可预知的同名覆盖
     # Error api自定义根异常 - 调用代码和api的错误分隔 - 具体异常
     	 调用者使用 try/except 处理异常，未处理的会raise到开发者
        
   ```

3. 虚拟环境

   ```python
   # 隔离项目、重建依赖
   pyvenv /dir/path   # python3 -m venv /dir/path
   source /dir/path/bin/activate  # 启动该虚拟环境
   # 依赖关系导出
   pip freeze > requirements.txt
   pip install -r requirments.txt
   # 其他
   { pycharm: virtualenv | conda } + { poetry-lock、install }
   ```

## 部署 - 程序产品化

1. 模块级别代码配置不同的部署环境 - 配置文件

   ```python
   # 部署环境 - 生产环境
   普通代码 { 变量定义 }
   # 环境判断
   sys
   os.environ
   ```

2. repr输出调试信息

   ```python
   repr()  # __repr__
   assert eval(repr(a)) == a
   ```

3. unittest

   ```python
   # TestCase子类、test_开头的函数 - self.assertEqual(预期结果, 调用结果）
   from unittest import TestCase, main
   
   class APITestCase(TestCase):
     	hsot = ""
       port = ""
       def get_url(self, viewname, *args, **kwargs):
         	pass
         
   class MyTestCase(APITestCase):
     	def setUp(self): # 或 多继承 准备工作
         	# 每次执行test_xxx之前调用
       def tearDown(self):
         	# 每次执行完test_xxx之后调用
     	def test_xxxx(self):
         	self.assertEqual()  # assertTrue、assertRaise(Error, )
   if __name == "__main__":
     	main()
   ```

4. 性能分析 先于 优化

   ```python
   # 高效率：字符串操作、生成器
   # 低效率：属性访问、函数调用
   # 性能分析 - 程序代码
   profile - 纯Python
   cProfile.Profile - C语言扩展（更好，更底层对受测程序的效率影响极小）
   
   def func(data):
     	# processing
       return
   test = lambda: func(data)
   profiler = Profile()
   profiler.runcall(test)
   stats = Stats(profiler)  # pstats.Stats 统计数据
   stats.strip_dirs()
   stats.sort_stats('cumulative')
   stats.print_stats()
   stats.print_caller()   # 调用情况
   ```

5. 内存相关

   ```python
   # 垃圾回收 - gc - 引用计数
   gc.get_objects(). # 总数量
   # tracemalloc - 关联对象 及其 内存分配地址
   ```

   

























