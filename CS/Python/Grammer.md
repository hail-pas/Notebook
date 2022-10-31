# Grammer

----
## Math
- +、-、*、/、//、%、**
- 8b = 8bit = 8位 = 1B = 1Byte = 1字节 => {汉字符=3 ascii、utf8，2 gbk, 1 unicode；英文字符=1}
- 1字 = 2字节 = 16位
- 进制转化
	 bin()、oct()、hex()
	  0b  、 0o  、 0x
----
## 模块导入

> 模块和包在底层都是PyModuleObject
> 绝对导入：根目录为绝对路径，相对导入：当前路径. 隐式/显式

- 关键字导入
  import os

- import模块导入
  from importlib import import_module
  os = import_module("os")

- 内置函数导入

  os = __import__("os")

搜索 -> 加载绑定到当前作用域的local空间内

----
## 命令行参数
- sys.argv
- getopt模块    --支持 - 短选项； -- 长选项
	- options, args = getopt.getopt(args, options[, long_options])

            参数args：一般是sys.argv[1:]。过滤掉sys.argv[0]，它是执行脚本的名字，不算做命令行参数。
            参数shortopts：短格式分析串。例如："hp:i:"，h后面没有冒号，表示后面不带参数；p和i后面带有冒号，表示后面带参数。
            参数longopts：长格式分析串列表。例如：["help", "ip=", "port="]，help后面没有等号，表示后面不带参数；ip和port后面带冒号，表示后面带参数。
              
            返回值options是以元组为元素的列表，每个元组的形式为：(选项串, 附加参数)，如：('-i', '192.168.0.1')
            返回值args是个列表，其中的元素是那些不含'-'或'--'的参数。
		    			options = ((-opt,value),(--opt,value))    
		    			args = 不含 - 或 -- 的参数
		    			options, args = getopt.getopt(argv, "hu:p:", ["help", "username=", "password="])  # 参数、短、长选项
		    			错误 ： getopt.GetoptError
----
## Circle
- for i in range()  --in object，迭代器。后面同一层次的else 只会在for正常执行完毕后再执行
- while
	break、continue
	not、and、or
----
##Coding
  二进制 -> bytes -> unicode -> 可识别文本
	计算机内存中，统一使用Unicode编码, 十六进制表示； unicode编码的任何编码格式都可以正常解码
		#!/usr/bin/env python3
		# -*- coding: utf-8 -*-    文件保存的编码
	ord("") -> 码 ； chr(码) -> ""
- Binary -> ASCII(128个) -> GB2312 -> GBK1.0 -> GB18030   --China
- Binary -> ASCII -> Unicode:4 char ~ UTF-32/16/8   --Global
	- ASCII ==> 0-9：48-57 ; A-Z：65-90 ; a-z：97-122
- localCode --encode--> Unicode --decode--> otherCode  同编码群才能相互识别
- python2 --ASCII as default #coding:utf-8
	- bytes=str(默认ASCII) + unicode ==>  basestring 的子类
	- decode("unicode") -> encode("gbk")  : utf-8 --unicode--> gbk
	- str = "编码python"	(存储为ASCII编码的bytes)  #\xx\xx\xx\xx\xx\xxpython
	- Python 2 将会自动的将ASCII编码的 bytes 数据解码成 unicode 字符串 (bytes <-> unicode) => 中文的类似拼接会报错
- python3  --utf-8 as default
	- 编码的同时会将字符串转换为bytes类型
	- str(默认unicode)  +   bytes  （为了自定义编码转换）
代码文件本身使用的编码是当前的编码，在此基础上操作：
encode("")  ==> 以""编码    或    bytes(,"")
decode("")  ==> 将以""编码的文件解码成unicode（文件本身的编码）      或    str(,"")

文件 - 解释器 - 显示设备 ==> 编码格式一致: A1 --> unicode-内存 --> A2 --> A3
open(,,encoding="") # 默认使用系统环境编码
----
	内存地址： id(var)
##Type   --str、int等转换数据类型，eval恢复原数据类型    if type(var) is Type:
```
const.py
class _const:
    class ConstError(TypeError):pass
    def __setattr__(self,name,value):
        if name in self.__dict__:
            raise self.ConstError("Can't rebind const (%s)" %name)
        self.__dict__[name]=value
const = _const()

from const import const
const.PI = 3.14

字符转数字： if '9' >= char >= '0': int(char) ;  isdigit() ; ord(char) - ord('0') 字符转数字

```
- list[]  -- 列表，线程不安全；可变 => 栈、队列， 列表生成式：[fun(x)/exp for x in somerange if x >= y]
	 enumerate() 函数生成 (index, sequence)
	- 双端队列 from collections import deque 模块 多个left -> appendleft、popleft； 堆 ：import heapq
	- 多值对应赋值 ： a,b,c = list
	- 切片[strat,end,interval] end=-1：倒数第二个, 正数时为结束元素的后一位，interval=负数：倒着取
	- 函数
		- 增: append() - 一次一个、insert(index,"element")、extend([]) - 扩展多个
		- 删：remove("")、pop（index）、del 、clear() - 清空
		- 改：下标单元素赋值、切片多元素赋值
		- 查：从0开始、count()、index()、“element” in a - 判别
		- 排序：sort(reverse=TRUE) - 默认是从小到大、reverse()
		- 计数：count（“element”）， 与set配合使用可以同时获取非重复元素及其个数
	- 队列-多线程   --queue 模块 - 默认操作右边、双端队列 collections.deque - appendleft、 堆  heapq
		- Queue(num)    --默认先入先出FIFO、 pipe；创建队列实例
			- put(var)  --数据插入队列； num限制数量会阻塞；默认阻塞
				- put(var, 0 )  => 如果无法继续插入则报错
			- get()    --获取最后进入的数据； 获取不到数据会阻塞
				- get(0)    --将阻塞改为报错
			- qsize()   --获取队列长度
			- full()   --   empty()
- tuple()  -- 元组，直接元素不可修改（包含列表，列表内是可变的），单元素格式：（single，）
	- 做为固定值存储，不可变
- dict{}  -- 字典，健值对，实现switch case功能，建立一个 键是条件 ：值是函数名 的字典
	引用类型，指向同一源地址； hash高效
	默认无序， OrderedDict 有序字典
	- 函数
		- 增：dictname[key]=value  或 dict.get('key1','key2') 高效率/ setdefault(key,value) 设定默认值，该函数返回当前值
		- 查：items()、keys()、values()、has_keys(key) 判断是否有该key
		- 改：dic1.update(dic2), update({"key":value}) 合并扩展
		- 删：del dic[key]、.pop(key)、.clear()、.popitem()随机删除-无序
		- 创建：dic1=dict.fromkeys([][[allkeys],[singlevalue])
		- 复制：copy()
		- 排序：python内置的sorted()，生成新的字典
- set {}  --集合，或者函数调用list创建，key集合，*无重复* 无序
	- 只能调用对象创建, 可hash即元素要*不可变*。集合本身不可hash
		- set()、frozenset()
	- 函数
		- 更新
			- add()   --添加一个元素
			- update()   --添加新内容，可能多个 [,]  只针对可变集合
			- remove()、pop()、clear()、del
		- 集合操作符、关系测试
			- == < >
			- 超集 = a>b = a.issuperset(b)
			- 子集 = a<b = a.issubset(b)
			- 交集 = a+b = a.intersection(b)
			- 并集 = a|b = a.union(b)
			- 差集 = a-b = a.difference(b)  a有b没有 ; symetric_diffrence =
							 a^b  对称差集
- String  --字符串
	- 函数
		- "symbol".join([a,b,c])   --用symbol将参数内的所有字符串拼接，空字符时为连接+
		- .count('word')  --统计字符串中某字符个数
		- .capitalize()  --首字母大写
		- .center(int,"填充符")   --居中显示, ljust() \ rjust()
		- .endswith("str")  --以什么结尾判断   startswith("str")
		- .expandtabs(tabsize=int)  --设定tab  \t 的空格数
		- .find("w")  --返回第一个该字符的索引值；rfind(), 倒序寻找，  index()
		- "{var:-9} is {var2:2.2%}".format(var1=value1,var2=value2)  --可以是变量名:格式化、> ^ < 左中右对齐、或用值的顺序号对应值
		- "{var:-9} is {var2:2.2%}".format_map({var1:value1,var2:value2})   --字典来对应取值
		- .isalnum()  --判断是否是字母或数字
		- .isdecimal()  --十进制判断
		- .isdigital()  --数字  isnumeric()
		- .isidentifier()  --判断是否可以做为规范变量名
		- .islower()   --小写、isupper(); 大小写转换 lower()\ upper()\ swapcase()
		- .isspace()  --空格 istitle()
		- .strip()   --将前后的空格、换行符去掉。文本处理去掉 \n  \t ；lstrip()  \  rstrip()
		- .replace("sour","tar",int)  --替换至匹配到的第int个
		- .split(" ",int)  --以“ ”来分割字符串成列表, rsplit()   join()
		- .title()  --格式化成标题， istitle()
- bytes    --十六进制， 更底层高效； str - unicode
			bytes <-- string  <-- others； 其他类型转换为bytes需要经过string
			bytes --> 类型(b"bstr")
	- 编码：string	>>> bytes ，
		- bstr = bytes(str,"utf8")  ； 以utf8编码的bytes类型
		- str.encode("utf8")
	- 解码： bytes >>> string , 以同一规则解码
		- str(bstr,"utf8")
		- bstr.decode("utf8")

==========================
- 数据解析     --文件的写入写出是str类型，需要先经过转换，再经过eval()还原
- 序列化模块    --把对象从内存中变成可存储或传输的过程，python中叫pickling  -- unpickling
- xml 和 json
	- json    --是python中的一个模块，引自js。 无法序列化函数、类等复杂对象，使用pickle
		- dumps(obj)    --序列化函数，变成json格式字符串
		- json.dump(obj,open())    --无需write()方法
			等价于 =>  f.write(json.dumps(obj))
		- loads(f.read())    --反序列化
		- load(fileobj)    --无需read()方法
	- pickle    --序列化模块，可以对函数、类等进行操作
		- dumps()    --bytes类型，所以打开方式要为 wb   dump
		- loads()    --模式 rb;函数是内存指向    load
	- shelve     --将句柄变成**对象**直接操作，key必须为字符串
		- f = shelve.open(r'path/filename')
			f['dictname] = {'key':'value';'key':'value'}
			f.get('dictname')[key]    #获取

- XML 替代configparser
==========================
- 拷贝
	- .copy()    --浅拷贝，只拷贝父级元素，不会递归拷贝,copy.copy()  仍然是浅拷贝
	- 深拷贝   --全克隆
		- import copy; copy.deepcopy(source)
	- 列表 a = b 共享内存，会互相影响
- 可迭代对象Iterable   isinstance(a,b)   a是否是b类型

	- 对象内部含有 ___iter___方法
- 迭代器Iterator     --iter(obj) 将可迭代对象生成迭代器，可以使用next(iter(obj))方法  
	- 同时有iter方法 + ___next___方法   ==> yield 封装   var = (yield var1)
	- 生成器是特殊优雅的迭代器
	- for 实现逻辑
		1. 调用可迭代对象iter方法，实现nest变成迭代器
		2. 不断调用next方法
		3. 处理stopIteration

----

## File  --全是字符串; linux-文件描述符；win-文件句柄
- open("path/file","mode",encoding="")  --操作文件描述符，mode: r/w/a <-> b/+/b+， w模式打开时默认会清空,a是附加模式.
	- r+读写  --读和追加。指针光标在最前「r和w的光标不一致」write从最后添加。修改文件中间部分线性存储机制，但可以复制 加 修改 到新文件
	- w+写读  --先清空，新增后指针后移，无法直接读取
	- a+追加读  --同理，指针光标默认在最后
	- with open("path/file","r") as f:    --不需要手动关闭，需要注意缩进
		 - with open() as f_a, open() as f_b:     --创建多个文件句柄
		 - 对资源进行访问的场合，确保在访问的过程中不管是否发生异常都会指执行必要
		 - 的清理操作，比如文件的自动关闭以及线程中锁的自动获取与释放。
		 - with context_expression [as target(s)]:    (上下文管理器，__enter__(),__exit__()函数控制)
		 - target 多值时必须加(), 实质上是将__enter__()的返回值给target. 内部封装try  finally，减少编码
		 - 支持上下文协议的模块 ： threading、decimal、file
		 	with open(os.path.join(enroll_dir_path, upload_file.name), "wb") as upload:
					for chunk in upload_file.chunks():
					upload.write(chunk)
- 属性
	- closed  --状态判断
	- mode  --访问模式
	- name  --文件名
- 函数  「read和write一致，都会移动文件读取的位置、指针」
	- read(int)    --deadline()、readlines(字节数int) - 列表  可以先全提取出来  for i in f： for将f对象做成迭代器获取
	- next()    -文件下一行
	- write("content")  --默认替换  writelines(sequence) 自己加换行符
	- seek(int,whence=1)    --参数：whence = 0、1、2 - 起始、当前、末尾 做为偏移量起点，文件指针定位
	- tell()   --返回文件当前位置，中文是3个字符
	- os.rename(old,new)  --os模块重命名、remove()、rmdir()、mkdir()、chdir()、getcwd()当前目录
	- fileno()  --文件描述符
	- flush()  --主动将缓冲区内容写入
	- truncate()   --默认-1,截断全部; 其他参数到结束。主义w模式默认先清空
	- close()  --缓冲区的内容保存， time.sleep(int) 测试句柄未关的情况
----
## Generator    --生成器，是一个返回迭代器的函数或表达式；或者简单理解其本身就是一个迭代器 反之不然
	 惰性运算
- list = [fun(x) for x in range(10)]
- generator = (fun(x) for x in range(10))  ==> 指向数据而不存储数据，本质是函数
	- 创建   --表达式和函数
		- generator = （表达式）
		- yield     --  把输出或者返回语句替换成yield，保存函数对象
			def foo():  #生成器对象
				功能模块1
				yield    #类似 return  但可以多次返回，也可以理解为暂停标志
				功能模块2
				yield
				.......
			next(foo())   #调用，只会执行功能模块， next(foo()) = yield返回值，最后会报错 StopIteration
	- 获取
		- generator.___next___()   ===> 生成器内置函数  py2: generator.next()
		- next(generator)    ===> py3内置可迭代对象操作函数 。 for i in Iterable 的本质
		- generator.send(value)   ====> 传值执行功能模块   g.send(None)  =  next(g)
			需要先进入入口 ： send之前next(obj)  or  send(None) ,将代码执行到第一个yield
			第二个 g.send(value)  => 给第一个yield 赋值， 但g.send(value) = 第二个yield 值
			def foo():
				功能模块
				var1 = yield result1
				调用var
				功能模块2
				yield 2
	- 回收
		- python 垃圾回收机制：内存空间里的对象没有被引用、指向的时候。迭代器只有一个i在引用，永远只有一个变量
	- 应用  
		- Fib
		def fib(max):
			n,before,after = 0,0,1  
			when n < max:
				yield before
				before,after = after,before + after #先计算出右边再赋值
				n+=1
		- 保留函数现场，伪并发
## 迭代器
	 可迭代对象未必是迭代器，
	- 可迭代
		- 只要含有__iter__()方法的就是可迭代； for 循环调用
	- 迭代器      --惰性、不定长； 字典、列表等可以转换成迭代器 iter(list)
		- 同时含有__iter__()方法和__next()__方法的就是迭代器； iter相当于返回初始值， next变化值并返回
		- 缺点
			- 无法获取迭代器的长度，使用不如列表索引取值灵活
			- 一次性的，只能往后取值，不能倒着取值
		- 用途
			 for循环：遍历之前，先调用可迭代对象的__iter__方法将其转换成一个迭代器
			 再使用next()获取值
----

## Function
- 定义   --减少重复、易于修改扩展、代码统一；___doc___ 属性，文档字符串
	- def fun_name(var1,var2="default"):  #函数名区分大小写
			..........
- 参数    --python创建的变量没有类型限制，传入的和默认的不一定要保持一致,函数可以作为参数或者返回值。
	- 高阶函数，函数的引用和执行，单函数名字表引用获取内存地址可以赋值给新的变量名，名字加括号参数表示执行。
	- 必须参数   --没指明，需要顺序对应
	- 关键参数   --指明形参 var2=xxx，var1=yyy
	- 默认参数   --必须在其他参数的*后面*
	- *args     --不定长参数，存储在一个元组里面，args[i] 或 迭代器 *args代表位置参数，**kwargs代表的关键字参数(位置:关键)
		- 命名健值对不定长参数 >>> ***kvargs ，存储为字典。 两个配合使用 def funname(***args,***kvargs): # 可以接受任意参数
		- 大类按顺序对应，只能  先无命名参数再命名参数
		- 默认参数要放在前面
		- f(*list) ==> args = list  ; f(***dict) ==> args = dict
		def funname(a,varname="default",**args,***kvargs):    #参数顺序
- return   --结束的标志
	- None   --默认
	- 多对象   --会被封装成一个对象
- 作用域
	- Python built_in -> global -> enclosing locals -> local局部  （legb法则）
	- 只有模块（module），类（class）以及函数（def、lambda）才会引入新的作用域
	- 局部函数不能修改全局变量，除非使用global 声明，最好在需要使用的函数内部global声明就好。
	- if __name__ == "__main__":  # 主函数可以直接使用
	- 变量 ： 非全局，但是是上一层的。  使用 nonlocal 声明
- 递归    --递归大多情况效率低，可能导致栈溢出，可以用循环来替代
	- 调用自身，参数规律性变化
	- 又一个结束条件
----

## Decorator    --装饰器、公共模块封闭原则。开放原则功能扩展；即在不修改原有功能的基础上新增扩展
		装饰对象可以是类
		三层包装参数：装饰器传入参数 - 被装饰函数 - 被装饰函数参数
- 闭包：内部函数对外其外部作用域的引用，称该内部函数为闭包  {作用域、高阶函数}
- foo()  --> showTime(foo)  利用另一个函数实现与foo有关的新增功能
- 装饰器 - 功能扩展不改变原函数，只新增 功能。插入日志、性能测试、事务处理、缓存、权限校验等场景
	- 实现逻辑| 基本模型 - 两层
		def showTime(func):   # 装饰器函数
				def inner(*arg, **kwarg):
						调用foo(*arg, **kwarg)的新功能模块
				return inner()     # 返回的是内一层的函数名，装饰器参数涉及到
		foo = showTime(foo)    # @showTime    python内置装饰器赋值方式，最外层的函数名
		def foo():   #  原函数
				原功能模块
		foo()   # 实际执行的是新功能模块代码
	- 参数
		- 原功能参数 和 装饰器内部函数参数 一一对应
		- 装饰器函数参数（嵌套加层）；装饰最外层的参数
			def thirdFun():
					功能语句
			def flagDeco(flag):   # 默认参数可以在后面装饰器赋值的时候缺省
					def showTime(foo):
							def inner():
									调用foode新模块功能
									if flag == "":
										thirdFun()
							return inner
					return showTime
			foo = flagDeco(True)  # 执行最外层，虽然内层有定义函数但是没有调用，
															所以直接执行return内层函数的语句到内层，再继续。   
															-> showTime(foo) 闭包可以引用上一层的参数。使用 *args 和 **args实现接受任意参数
	- 应用    --@login() , 调用公共模块 原函数做为参数传入
	- 类装饰器
				cls.
				继承
						initialize()
----
## Object-Oriented Progaraming   --抽象类共同特征，需要封装单独的数据，记得对象实例可以直接dump 并load 读取
	 实例化对象执行函数时的继承，记住self是实例化的那个对象，每次遇到self都优先在实例化对象中找
- metaclass    --class是type的对象，尽皆对象

- class name(object, metaclass = mytype)     --可指明继承的元类，当需要自定义元类的时候

- class name(object):    --子类、超类 - issubclass(,),  ___bases___属性，isinstance(,)； 类的命名空间
		data
		def foo(self,*arg):   #self指调用的实例对象
				steps
		==> class_gen = type('name', (object,),{'func':funcname})   #默认继承object类，用type来创建类，type用C实现，执行type的init
				 动态生成类，类名、基类集、类成员;  成员事先定义好，函数注意(self)参数,再调用； 使用class_gen() 实例化
				 django 自定义admin界面，修改表数据时动态生成 ModelForm 类
	  type 和 object 如 鸡 和 蛋 的关系
			 面向对象存在两种关系：
					 父子继承关系 - __bases__
					 类型实例关系 - __class__或type()
			 object是父子关系的顶端; type是类型实例关系的顶端
			 所有数据结构的类型都是type； 父类都是object
			 type 是元类
					 自定义元类 class M(type):       --type是实例关系的顶端，即初元类
					 元类的实例化，需要定义另外一个类指明元类：
								 class TM(object): __metaclass__ = M
								 class TM(object, metaclass=M)

- 普通 & 静态    => callable() 是否可调用

- 字段     --可动态添加属性，admin_class
	- 静态字段    --和方法同级，存储在类中，可以用类名直接调用；会被对象重赋值遮盖
	- self.varname			--init函数中初始化
	- ___dict___    --返回对象或类中的所有成员
	- ___doc___    --注释
	-

- 方法    --特殊方法__ ； 非静态和类方法的其他方法全要加self参数
	- ___init___    --构造方法，初始化动作self.element = "value"  封装数据， 类名() 执行该函数
	- ___del___     --析构方法，当实例被回收的时候被调用
	- ___new___     --创建实例对象,自定义动态modelform时用到该方法获取models的字段  base_ fields
	- ___call___    --insobj() 执行该函数
	- ___class___   --转换数据类型函数，当转换成str型时执行___str___ 函数， print(insobj) -> print(str(insobj))时该值为str函数的值
	- ___add___(self, other)     --两对象 + 运算的定义，执行第一个对象的add函数，第二个做为参数
	- ___getitem___    --索引int、切片（slice类）方法，索引为参数执行该函数，___setitem___(self, key, value); delitem(self, key)。 列表的索引实现
	- ___iter___     --迭代方法，可迭代标志，迭代式执行获取返回值(可迭代对象的迭代器 iter())，
	- 双下划线__   --创建伪私有成员，开头加“_类名_xxx” ==> 转换成classname.__classname___funcname  ==>
																					 																	insobj.__clsaaname___funcname; 依然可以访问
		只能通过内部方法访问

- 属性

- 装饰器
	- @abstractmethod    --抽象方法pass
	- @staticmethod      -- 变成静态方法，self非必须、可无参，可以直接用类调用，相当于类外函数，可通过类或实例来调用
	- @classmethod     --变成类方法，默认至少一个参数 _cls_ ，都不依赖对象，自动加载当前类， 将类做为参数传入，调用方式同
												 框架中用于获取配置文件响应数据作为参数创建类
	- @property      --属性装饰器，函数做为字段格式调用， 获取值.  只是对应关系，里面的代码逻辑可以更改
			proname = property(fget = funcname, fset = funcname, fdel = funcname，doc = "")   #与用装饰器等效,关键字参数可以缺省，位置
		- @proname.setter   --接收参数更改property， 字段方式调用 = ， 赋值操作
		- @proname.deleter   --del proname 会执行该函数

- 特性
	- 封装
	- 继承    --重写  class subclass(mainclass):   扩展或修改父类的功能； __无法继承访问
		- 多继承    --C++、python
			- 同名，self.xx  来调用方法，从实例参数从左到右，深度优先查找。（就近原则，有共同的远层级父类时不深度到底）；其他没有影响
		- 调用父类    --直接使用父类名调用更方便
			- super 关键字  ==>   p3可以省略参数，但是需要在子类的函数内使用灿能不传参数
			 默认深度优先，再广度
					super(subclassname, self).func(args)  =>  父类.func(args)，可以直接 . 调用父类中的方法
					super().__Animal___heshui()   --单下划线 双下划线
			- MainClassNAme.funcname(self, *args)   ==> 直接调用父类方法;  self必需要带，显示传递类实例
				 多继承时，可以指定父类方法执行
	- 多态    --参数的多态。数据类型，父类子类做为一种参数被接收。python默认不区分数据类型

- 反射    --通过字符串操作对象中的指定元素、成员  insobj.___dict___[varname]  得到成员字典
	- hasattr()
	- getattr(insobj, “name”)      #同样适用于类、模块， 类是type的对象
	- setattr(insobj, ”name“, value)
	- delattr()
	- 根据输入来反射获取动作

- 字典化类     --字典本质, 自定义cookie， 类传递
	- __setitem__(self, key, value)
	- __getitem__(self, key)
	- __delitem__(self, key)   --> del
	- __contains__(self, item)       in 判断本质

- 字符串反射实例化对象  [r]split("char",int)
	- 字符串导入模块
		 import imortlib
		 imported_module = importlib.import_module("py文件引用路径")   --aaaa.bbb.cccc.dddd   缺省py后缀

	- 模块中反射获取类
		 cls = getattr(imported_module, "类名")
	 cls()       --实例化

		___init___文件使用 ，直接导入init所在的文件夹，会直接加载init文件
		文件夹名.类名    可以直接使用init中的类

- 魔法方法

   ```python
   静态 - abc.
   	类 - class AbstractCls(metaclass=ABCMeta):
     方法 - @abstractmethod
   	属性 - __dict__ 汇总字典、__class__
   ```
```

   ```python
   Magic Method => __methname__
   __new__(cls, )  # 创建实例
   __init__(self, )  # 构造函数，传实例参数
   __del__(self)   # 析构函数
   __call__(self [,...])
   __getattribute(self, name)   # 点运算取值
   #### 比较
   __cmp__(self, )    #
   __eq__(self, other)  # 同对象->实例 ==
   __ne__(self, other)  # 同对象->实例 !=
   __lt__(self, other)  # 同对象->实例 <
   __gt__(self, other)  # 同对象->实例 >=
   #### 一元操作符
   __pos__(self)    # 一元加运算符 +self
   __neg__(self)    # 一元减运算符 -self
   __abs__(self)  # abs()
   __invert__()    # 取反运算符  ～self
   #### 算数运算
   		# -> __radd__() 反运算   /   __iadd__(self, other)  增量赋值（%=）
   __add__(self, other)  # +
   __sub__(self, other)  # -
   __mul__(self, other)  # *
   __floordiv__(self, other)  # //
   __div__(self, other)  # /
   __truediv__(self, other)  #
__mod__(self, other)  # %
   __divmod___(self, other)  # divmod()
   __pow__(self, other)  # **
   #### 逻辑运算
   __bool__  
   __rlshift__()   /   __ilshif__()  <<= (加等运算)
   __lshift__(self, other)  # <<
   __rshift__(self, other)  # >>
   __and__(self, other)  # &
   __or__(self, other)  # |
   __xor__(self, other)  # ^
   #### 类型转换
   __int__(self) / __long__(self) / __float__(self) /
   __complex__(self) # 复数
   __bin__(self) / __oct__(self) / __hex__(self)  # 进制转换
   __repr__(self) / __str__(self)  # repr() - unicode、str()
   __index__(self)  # 转换为切片索引使用  x[self]
   __trunc__(self)  # math.trunc(self)  截取运算返回值
   __hash__()  # hash(), 字典中进行快速比较
   __nonzero__(self)  # 对象bool计算   bool(self)
   __getattr__(self, name)   # 访问一个不存在的属性  self.name
   __setattr__(self, name, val)  # 对属性赋值  self.name = val
   __delattr__(self, name)   # 删除属性  del self.name
   	# 避免递归
     	def __setattr__(self, name, value):
       		self.name = value
       #每当属性被赋值的时候， ``__setattr__()`` 会被调用，这样就造成了递归调用
       #这意味这会调用 ``self.__setattr__('name', value)`` ，每次方法会调用自己。这样会造成程序崩溃
   #### 定制序列
   __getitem__(self, key)   # self[key]; 切片、迭代、逆序reversed()、in
   __setitem__(self, key, val)   # self[key] = val
   __delitem__(self, key)  # del self[key]
   __iter__(self)   # for x in self
   __next__(self)   # 生成器调用 next(self)
   __len__(self)  # len()
   __contains__(self, value)  # in、not in
   __concat__(self, value)  # 序列连接运算  self + other
   #### 反射
   __instancecheck__(self, instance)    # isinstance()
   __subclasscheck__(self, subclass)    # issubclass()
   __enter__(self) / __exit__(self, exc, val, trace)  # with 语句上下文管理， with Cls() as clsin:
   __getstate__(self)  # 序列化 pickle.dump(pkl_file, self)
   __setstate__(self)  # 反序列化  data = pickle.load(pkl_file)
```
```

__repr__,__str__,__format__,__bytes__ __abs__,__bool__,__complex__,__int__,__float__,__hash__,__in
dex__ __len__,__getitem__,__setitem__,__delitem__,__contains__ __iter__, __reversed__, __next__
__call__
__enter__,__exit__
__new__,__init__,__del__ __getattr__,__getattribute__,__setattr__,__delattr__,__dir__ __get__,__set__,__delete__ __prepare__,__instancecheck__,__subclasscheck__
__neg__-,__pos__+,__abs__abs() __lt__>,__le__<=,__eq__==,__ne__!=,__gt__>,__ge__>=
__add__+,__sub__-,__mul__*,__truediv__/,__floordiv__//,__mod__ %,__divmod__divmod(),__pow__** orpow(),__round__round()
__radd__,__rsub__,__rmul__,__rtruediv__,__rfloordiv__, __rmod__, __rdivmod__, __rpow__
__iadd__,__isub__,__imul__,__itruediv__,__ifloordiv__,__im od__,__ipow__
__invert__~,__lshift__<<,__rshift__>>,__and__&,__or__|, __xor__ ^
__rlshift__,__rrshift__,__rand__,__rxor__,__ror__ __ilshift__, __irshift__, __iand__, __ixor__, __ior__
```

----
## Exception  Warning
- try:
		...正常逻辑代码 （出现错误则跳转）
		raise Exception()    #主动抛出异常
	except (InexError, OtherError) as e_name:  # 小到大，同时处理多个并赋值给一个变量
		...异常处理代码
	except Exception as excename:  #捕获所有错误类型 - except ; 多个 except (exce1,exce2,...)
		...异常处理代码
	else:
		...不出错时执行的代码
	finally:
		...最终都要执行的代码
- 断言    --AssertionError
	assert 条件
	条件成立则无任何影响，不成立则报错；即必须要条件为真，先决条件
- Exception     --异常大类，子类细分
	- LookupError
		- IndexError
		- KeyError
	- NameError
	- ValueError
	- TypeError
	- ZeroDivisionError
	- AttributeError
	-
	- 自定义类 - 继承Exception，___init___, ___str___ : print该自定义错误时的信息
----
## 多线程    --继承  或  调用; IO密集型,公用进程的资源； GIL锁，cpu只允许一个线程使用cpu
	pycharm进程 -> py 文件线程
	pthon高级代码 --> Cpython解释器 --> OS --> 进程（资源 + CPU - 线程) --> CPU
	进程是操作系统 分配资源 的最小单元（独立的内存）, 线程是操作系统 调度 的最小单元（共享进程的内存-互斥锁)mutex=semaphore(1)
- 区别
	- 内存
	- 通信 - 信号、管道 ；共享内存、消息队列
- 选择    --基于GIL
	- 对CPU密集型代码(比如循环计算) - 多进程效率更高（没有线程间context switch）  C支持最好
	- 对IO密集型代码(比如文件操作，网络爬虫) - 多线程效率更高
- GIL    --global interpreter Lock  全局解释器锁
	- 同一时刻只能有一个线程进入解释器，执行bytecode - 锁 --> 为了解决数据操作问题 ==> 没有多线程
	- 解决
		- 协程    --微线程，纤程。英文名Coroutine,用户态轻量级线程
		- 多进程 - multi-GIL
	- 同步锁    --数据保护
- 模块   --创建： 直接实例化，或者继承重写
	- multiprocessing    --进程,CPU核心数 -> Process(target, args = (,))、Pool
	- threading    --线程  --> Thread(target, args = (,)) --> 重写 init - args、run - target方法
	- 线程池 ->
		 pool = ThreadPoolExecutor(int)        --ProcessPoolExecutor(int)
		 pool.submit(function, arg)
			 p = pool.submit(func, arg1, arg2)
			 p.add_done_callback(done_func)
			 def done_func(*args, **kwargs)    //包含submit执行函数的返回值封装对象future
			 def done_func(future, *args, **kwargs)   ==>   future.result() = 执行函数返回值
		 pool.shutdown(wait=True)
- 对象方法
	- start()    --启动
	- join()    --阻塞,该子进程未执行完成前，父进程会阻塞
	- setdaemon(True)    --watchdog作用，当为子进程设为true有自己的守护时，即不需要父进程守护，父进程可以直接结束
- 静态方法   --threading.
	- current_thread()
	- active_count()
- 同步锁
	- 互斥锁  --mutex
		- Lock()    --锁,针对的是数据保护
			- acquire()   --  release()
		- RLock()    --可重用锁，（锁+计数）
	- 信号量    --semaphore 计数锁控制线程并发数，即锁允许的阈值大于1
		- Semaphore(num)
		- BoundedSemaphore(num)    --创建
			- acquire()   --   release()
	- 条件变量    --锁、 线程间通信（线程间关联、先后顺序执行）
		- Condition(Lock/RLock)   --默认RLock
			- acquire()   --   release()    返回boolean
			- wait()   --条件不满足时调用，线程会 释放 锁并进入 等待阻塞 状态 --> 恢复到重新获取锁开始，wait有释放动作
			- notify()    --线程创造条件后调用，awake通知到等待池的一个线程 --> wait()
			- notifyall()
			- 生产 - 消费者： 共享队列，队列操作保护，生产notify，消费wait
	- 同步条件    --类似条件变量，但是没有锁功能； 相当于 共享的flag
		- Event()    --初始状态为False
			- isSet()   --状态判断
			- wait()   --当状态为False时等待，阻塞后续代码
			- set()    --设为True
			- clear()    --清空恢复为False
	- 消息队列 - queue.Queue(size)    --模块 queue； 阻塞；列表-线程不安全
		- put("")
		- Q.get()   --线程安全，自带互斥锁；不会同时获取到同一数据
		- 常见Queue
			- 线程Queue
			- 进程Queue
			- RabbitMQ
----
## 多进程    --真正的并行，多cpu； 计算密集型 => cpu交互对进程没有限制
- multiprocessing
- 创建
	- Process(target,args=(,))    --init, run
	- 继承Process ： 重写init、run 方法
- 进程池
	- ProcessPoolExecutor(int)
- 方法
	- start
	- join
	- setDaemon()
- 类
	- Lock、RLock、Event、Semaphore、Condition
- 进程通信类
	- Pipe   --管道
		- Pipe()   --主进程中创建
		- parent_conn, child_conn = Pipe()   #生成两个进程管道套接字
		- send()  <-->   recv()    #直接传递字符串
	- Queue    --队列， 线程：queue.Queue()
		-	Queu()    --主进程创建队列，就存在于multiprocess中。
		- 做为参数传递到子进程中,（MacOS公用一份内存，但是win是copy的一份）
		- put、get
- 进程数据共享
	- Manager()  类
	- with Manager() as manager: #上下文创建, 后面的所有需要共享数据的操作都要在该上下文里
				manager.dict()
				manager.list(int)
----
## 协程    --  nginx使用协程，协程就是一串比函数粒度还要小的可手动控制的过程，时间切片;类似c语言的goto；不存在真正协程
	微线程，纤程。英文名Coroutine,用户态轻量级线程，在线程中
	并不真实存在
	拥有自己的寄存器上下文和栈；单独保存，自己控制切换
	非抢占式协异步执行，保留-恢复机制；无须锁和同步控制，无（用户态 <-> 内核态）切换消耗
	高并发、高扩展、低成本
	无法利用多核（多进程 + 协程）
- yield    --最底层
	 协程+ 异步IO --> 高并发 （Nginx）
	- yield传入参数控制代码继续执行或保留挂起；必须是生成器
	- ibj.send("")    --传入参数，需要使用一次obj.send(None) 或 next(obj) 将代码执行到第一个yield
		- varname = yield
	- next(obj)   --只返回值，无须传参数
- gevent    --模块,基于greenlet+异步IO
	 当一个greenlet遇到IO操作时，比如访问网络，就自动切换到其他的greenlet，等到IO操作完成，再在适当的时候切换回来继续执行
	 由于切换是在IO操作时自动完成，所以gevent需要修改Python自带的一些标准库，这一过程在启动时通过monkey patch完成
	 from gevent import monkey; monkey.patch_socket()     --准备工作，必须初始化
	- 静态方法    --gevent.
		- joinall([gevent.spawn(tarfunc, args),])    --协程池
		- spawn(tar, args)    --创建一个执行tar的协程
		- sleep(int)    --阻塞
----

## Bult-in Function
- filter(func,iter)    --参数为函数以及序列  （func的参数为str）
	- 作用：对str序列里的元素进行以func函数为条件的过滤，不会对序列里元素的值进行更改，只可能删
	- 生成一个迭代器，可以强制转换数据类型
- map(func,str)
	- 作用：对序列里的元素值进行操作
- reduce(func,str)    --需要调用 from functions import reduce
	- 作用：迭代处理序列中的值，比如传入的str = [x,y,z,a,b,c,d]; func(var1,var2,var3) ，最后得到func结果
	- => 先x,y,z做为func参数传入生成output1 并入str =[ouyput1,a,b,c,d]再迭代处理直到str为空
- lambda     --匿名函数
	- var = lambda a,b : a+b     # 参数 : 过程
	- reduce(lambda x,y : x*y,range(1,6)    #1到6的阶乘
- enumerate(iterable,int)    --生成一个同时具有索引和可迭代对象值的对象，可以用index,item同时取出。int可以指定索引开始位置
- abs()   --取绝对值
- all()   --判断变量是否可迭代
- divmod()   --求余数
- eval()    --还原被强制转换数据的数据类型，计算功能参数为运算式
- var = input('text')
- exit("text")
- print('Text',end='\n',flush=True)
	- printf("%s  %d"%(v1,v2))  --格式化输出, %s、%d、%f，等价于多行变量格式'''
		- 多变量组合string赋值
			var = "%s-%s-%d-%s_%s" %(var1,var2,var3,var4,var5)
	- "string {:-9d} with {: 2.2%s}".format(var1,var2,....)
		- { :<>^10.2f }    对齐方式
	- sys模块
		- sys.stdout.write("")、sys.stdout.flush()、time.sleep(int)  ==>实现终端步进输出
- .istype()  --type判断
- range(start,end,interval)  --获取范围
- time
	- time.strtime("%Y-%m-%d %X")      --当前时间转换为字符串  %X 具体时间到秒
-:
