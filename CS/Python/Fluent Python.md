# Fluent Python

```
dis.dis("code")  # disassembler function 反汇编语句查看函数
eval(expression)   # 执行字符串的code
# 执行命令行   利用eval无法确保代码的安全性
__import__('os').system('whoami')
__import__("subprocess").getoutput('ls ~')
```

## Prologue
```python
# dunder method： special method, __getitem__ => dunder getitem
collections.namedtuple  # a new subclass of tuple with named fields; class with only attributes
eg:
  Card = collections.namedtuple('Card', ['rank', 'suit'])
# complex type
vec = Vector(a1, a2, a3)  # abs(vec)
# Overview of special methods
## operator exclude
- class attribute
	__class__  等价于  type(obj)  # self.__class__.method/attr; attr => self.__dict__.get(attr)
  __dict__ 存储对象或者类的可写属性，如果类有__slots__属性，则可能没有__dict__属性; vars(obj) 获取
  			dir(obj) 获取大多数属性，除了几个特殊的类属性 __mro__、__bases__、__name__
  __slots__ 类可以定义这个属性，用以限制实例能有那些属性。是字符串组成的元组，包含__dict__等所有属性的限制
- string/bytes representation
	__repr__,__str__,__format__,__bytes__
- conversion to number
  __abs__,__bool__,__complex__,__int__,__float__,__hash__,__index__ 
- emulating collections
  __len__,__getitem__,__setitem__,__delitem__,__contains__ 
- iteration
  __iter__, __reversed__, __next__
- emulating callables
  __call__
- context management
  __enter__,__exit__
- instance creation and destruction
  __new__创建实例 ,__init__ 接收、初始化实例,__del__ 删除实例-垃圾回收
- attribute management
  __getattr__ 只在类中寻找 __class__/type(obj),__getattribute__,__setattr__,__delattr__,__dir__
  		__setattr__()  在尝试设置值的时候总是会调用
    	__getattribute__(self, name) 在尝试获取制定属性时总会调用该方法
    			.attr  |  getattr()   | hasattr()
    	__getattr__(self, name) 获取指定属性失败，搜索过obj、class和超类之后调用
      # 获取 和 设置 属性的不对等 -> 覆盖型/非覆盖型描述符
  __slots__ 指定属性存储，声明之后不会使用__dict__
  __dict__ 默认属性存储（可增加/删除）
- attribute descriptors
  __get__,__set__,__delete__ 
- _class services
  __prepare__,__instancecheck__,__subclasscheck__
## operator
- unary numeric operators (一元运算符)
	__neg__ -,__pos__ +,__abs__ abs() 
- rich compartison operators
	__lt__ <,__le__ <=,__eq__ ==,__ne__ !=,__gt__ >,__ge__ >=
- arithmetic operators
  __add__ +,__sub__ -,__mul__ *,__truediv__ /,__floordiv__ //,__mod__ %,__divmod__ divmod(),__pow__** pow(),__round__ round()
- reversed arithmetic operators
  __radd__,__rsub__,__rmul__,__rtruediv__,__rfloordiv__, __rmod__, __rdivmod__, __rpow__
  	tips：These functions are only called if the left operand does not support the corresponding operation and the operands are 						of different types.
- augmented assignment arithmetic operators (增量赋值算术运算符) i++
  __iadd__,__isub__,__imul__,__itruediv__,__ifloordiv__,__im od__,__ipow__
- bitwise operators(位运算符)
  __invert__ ~,__lshift__ <<,__rshift__ >>,__and__ &,__or__ |, __xor__ ^
  	tips: __lshift__ << is defined as floor division by pow(2,n) ,__rshift__ >> is defined as multiplication with pow(2,n)
    			__and__ &,__or__ |, __xor__ ^  arguments must be integers
- reversed bitwise operators
  __rlshift__,__rrshift__,__rand__,__rxor__,__ror__ 
- augmented assignment bitwise operators
  __ilshift__, __irshift__, __iand__, __ixor__, __ior__
```

## Data Structure

> collections.abc => { Container、Iterable、Sized }
> comprehensions reversed code 代码逻辑逆序

### Sequence Type

``` python
Sequence -> MutableSequence
list、tuple、array、queue
# Basic (Implemented in C) 
> sorted(iterable, key=callable, reversed=False)
## type
> A memoryview object exposes the C level buffer interface
Container sequences
	list, tuple, collections.deque;  hold items of different types. 
Flat sequences
	str, bytes, bytearray, memoryview, array.array;   hold items of one type. [primitive values like characters, bytes and numbers]
## mutability
Mutable sequences
	list, bytearray, array.array, collections.deque, memoryview 
Immutable sequences
	tuple, str, bytes
# List comprehensions and generator expressions 列表推导list-comps 生成器表达式genexps
> line breaks are ignored inside pairs of [], {} or (); 
> Listcomps no longer leak their variables; has its own local scope like functions; 
> the local variables do not mask the variables from the surrounding scope
>>> x = 'ABC'
>>> dummy = [ord(x) for x in x] 
>>> x
"ABC"
>>> dummy 
[65, 66, 67]
## list-comps []
	list sequence
> map(func, iterable); func returns value
> filter(func/None, iterable); func returns bool, None = lambda x: bool(x)
## genexps ()
> 遵循迭代器协议 => yield one by one
	non-list sequence
## tuples
> immutable lists & batch records with no field names - position is vital with special meaning
> TupleName = collections.namedtuple("TupleName", ("field_name1", "field_value2"))  # ("field_name1 field_name")
>>> _fields    # class attr
>>> _make(iterable)  # TupleName("field_value1", "field_value2"); class method
>>> _asdict()  # instance method
> unpacking
>>> b,a=a,b  # elegant
>>> func(*args)  # **kwargs
>>> a, b, c, *rest = range(5)   # focus on part
>>> _, filename = os.path.split('~/.ssh/idrsa.pub')  # dummy variable placeholder; Attention: _ is an alias to gettext.gettext
>>> metro_areas = ('Tokyo', 'JP', 36.933, (35.689722, 139.691667))
>>> name, cc, pop, (latitude, longitude) = metro_areas  # nested unpacking
## sliceing
	__getitem__ & __setitem__
> slices and range exclude the last item  ==> length、split   pre = li[:x]; rest = li[x:]
>>> s[a:b:c]   # stride or step c; returns slice object: slice(a, b, c); slice(None, None) = all
>>> sq.__getitem__(slice(a, b, c))  = sq[slice(a, b, c)] = sq[a, b, c]
> multi-dimensional
>>> ndarray[i, j]  # 2-dimensional;  __getitem__((i, j))
>>> ndarray[m:n, k:l]
>>> ndarray[x, ...] ==> 4-dimensional  ndarray[x, :, :, :]   ellipsis省略对象
>>> ellipsis is class name，but instance name is Ellipsis；just like bool 
> reassign
>>> li[2:5] = [20, 30]   # replace part iterable
>>> li[2::2] = [20, 30]   # jump replace one value with ordering iterable sequence
## + * 
	extend content of sequence
>>> [[]] * 3
[[], [], []]  # The outer list is made of three references to the same inner list.
>>> [['_'] * 3] * 3 vs ['_' * 3 for i in range(3)]
>>> board = [['_'] * 3] * 3 
    row=['_']*3 board = []
    for i in range(3):
    	board.append(row)
## +=  *=
		augmented assignment operators += and *= depends on the first operand
a += b  # fallback a = a + b
__iadd__    "in-place addition" => mutable: a.extend(b); id will not change
__add__			a has a new reference for a new object, different id ==> immutable
		concatenate immutable sequence will create new objects (But str is an exception, so common that CPython is optimized for it)
		immutable sequence does not support iadd
>>> t=(1,2,[30,40])   # corner case 边界问题
>>> t[2] += [50, 60] 
		temp = t[2] + [50, 60]   # actual t[2] has changed
  	t[2] = temp   # raise Exception("TypeError")
    # 使用  t[2].extend([50, 60]) 可以避免
    # augmented assignment is not atomic
>>> t
(1, 2, [30, 40, 50, 60])
## list.sort & the sorted built-in function
	list.sort is in-place, return None  # e.g  random.shuffle; but not support Fluent interface; can not cascade
	sorted receive iterable then return a new created list
> params:
  	key=callable, default is None. e.g itertools.groupby()、heapq.nlargest()、max、min
    reverse=bool, default is False
> Timsotr: it preserves the relative ordering of items that compare equal. # 无法比较的两个元素多次排序的相对位置一致
> bisect
	managing ordered sequences with bisect
	bisect & insort — that use the binary search algorithm to quickly find and insert items in any sorted sequence
  	bisect_right = bisect、bisect_left  # equal item in the haystack, insert in its left or right
>>> index = bisect(haystack, needle, lo, hi)  # 干草垛寻针
>>> haystack.insert(index, needle)
>>> insort(haystack, needle)
> score => grade 区间筛选
>>> breakpoints = [60, 70, 80, 90]
>>> grades = "FDCBA"
>>> grade[bisect(breakpoints, score)]
## Not only list
> array
	large scale of float value; array is machine values as C language
  list store the float objects
number: array
containment check: set
FIFO: deque
### array
array("typecode", iterable)  # typecode describes underlying C type：  'b'= signed char；'d'=double
a.tofile(f);  a.fromfile(f, n)  # pickle.dumps();  pickle.loads()
a = array.array(a.typecode, sorted(a))   # not support in-place sorted
as lean as C array；
### memory views - 内存视图
	shared-memory sequence type that lets you handle slices of arrays without copying bytes.
>>> memoryview(object) 
>>> numbers = array.array('h', [-2, -1, 0, 1, 2])    # 16 bit per number
>>> memv = memoryview(numbers)
>>> memv[2]
0
>>> memv_oct = memv.cast("B")    # 8 bit per number
>>> memv_oct.tolist()
[254, 255, 255, 255, 0, 0, 1, 0, 2, 0]
	编码：符号位 + 数值位
  原 码  --> 反码(计算机内只有加法)  --> 补码(-0, 十进制与二进制的一对一转换)
  二进制 -->      数值位去反       -->           负数+1 (-0的补码溢出变成唯一的 +0)
### numpy and scipy
	SciPy is a library, written on top of NumPy
### deques and other queues
> deque
	collections.deque; thread-safe double-ended queue; 
  removing items from the middle of a deque is not as fast. It is really optimized for appending and popping from the ends.
  default change direction is tail
>>> dq = deque(terable, maxlen=5)    #  head <-[-]-- tail
>>> dq.rotate(n)   # n > 0 rotate n numbers from right to left(prepends: tail to head); n < 0 do the opposite(afterpends)
>>> dq.append(value)  # append to the right tail;   dq.appendleft(value)
>>> dq.extend(iterable)   # extend to the right tail;  dq.extendleft(iterable)
>>> dq.pop()   # pop the tail element;  dq.popleft();  not support li.pop(position) of list
> queue
	synchronized (thread safe)
	can be bounded and don’t discard items to make room as deque does. Instead blocking insertion
>>> queue.Queue; queue.LifoQueue; queue.PriorityQueue
>>> queue.LifoQueue(maxsize=size) 
	get/put、get/put_nowait、task_done() -> join()
> multiprocessing
	multiprocessing.Queue; multiprocessing.JoinableQueue  # JoinbleQueue is subclass of Queue, implement task_done and join
> asyncio
	 Queue, LifoQueue, PriorityQueue、JoinableQueue
> heapq
	 heap[0] is the smallest item, and heap.sort() maintains the heap invariant!
   heapq.heapify(list)  # heap sort the list ; Transform list x into a heap, in-place, in linear time
   heappushpop(li, 6)  # heappush(heap, item) + heappop(heap)
```

### Dictionaries & Sets

> Based on hash table; unordering because of resolustion for hash collision

```python
Mapping -> MutableMapping
Mapping is all mutable in standard python library
# Hashable
	__hash__ (hash value, never change during lifetime)
  __eq__ (hash value compare)
  e.g
  	str、bytes、numeric types、frozen set、 tuple(all its item are hashable)、user-define types(its id)
>>> hash()
```

#### Dict

```python
# dict 
collections.OrderedDict、collections.defaultdict
collections.ChainMap、collections.Counter
	ChainMap: a list of dict, the actions always on first dict in the chainmap
    >>> a = a.new_child(dic) # 左端增加一个dict
    >>> a.parents. # 除左端第一个dict外的ChainMap
    >>> a.maps  #  [{'te2': '2'}, {}, {'te': '1'}] 列表
  Counter: a mapping that holds an integer count for each key, updating an existing key adds to its count. the non-exi
    >>> ct = collections.Counter('abracadabra')  # iterable
    Counter({'a': 5, 'b': 2, 'r': 2, 'c': 1, 'd': 1})
    >>> ct.update('aaaaazzz')
    Counter({'a': 10, 'z': 3, 'b': 2, 'r': 2, 'c': 1, 'd': 1})
    >>> ct.most_common(2)   # most common element
    [('a', 10), ('z', 3)]
## method
	d.setdefault(k, «default») # if k in d, return d[k]; else set d[k] = default and return it; fetch/set and update
  d.get(k, «default»)
  dict.fromkeys(iterable)  # create new dict with keys in iterable and None value
  .keys(), .items() and .values() return a set like view objects
>>> {code: country.upper() for country, code in country_code.items() if code < 66}dictcomps
## solution for missing key { get() | default_dict or __missing__ }
>>> dic = collections.defaultdict(callable)  # create a item with key and callable() as value; when get a non-existent item
	tips: dic[k] based on __getitem__ will invoke the default mechanism, but the dic.get(k) will not
>>> __missing__ # __missing__ < __getitem__ < defaultdict; instead of raising KeyError.
	def __getitem__(self, key):
    if key does not exist:
       return self.__missing__(key)
      
	def __missing__(self, key): 
    if isinstance(key, str):  # to avoid infinite recursion, call self to implement self
			raise KeyError(key) return self[str(key)]
  # dict.keys() returns a view, which is similar to a set, and containment checks in sets are as fast as in dicts
## collections.UserDict
	does not inherit from dict, avoid infinite recursion
### attribute	
  	data: instance of dict
### Immutable mapping view
MappingProxyType
>>> d = {"A": 1}
>>> d_proxy = MappingProxyType(d)
>>> d["A"] = 2  # raise TypeError
```

#### Set

```python
A set is a collection of unique objects.  # { items }
Set elements must be hashable. The set type is not hashable, but frozenset is, so you can have frozenset elements inside a set
# Operators
	| union、& intersection、- difference、^ xor、in、<、<=、>、>=   # infix operators 中缀运算符
  {items} is better than set(iterable); {items} runs a specialized BUILD_SET bytecode. set(iterable) finds set constructor ....
  dis.dis("code")  # review the disasswmble statement
  frozenset must create by calling a constructor
# methods
	add(value) 
  discard(value) / remove(value)  # remove will raise KeyError
# set comprehensions
# Operations
```

#### Hash Table

```python
A hash table is a sparse array, i.e. an array which always has empty cells. the cells in a hash table are often called “buckets”.
In a dict, a bucket for each item and it contains two fields: a reference to the key and a reference to the value of the item. 
All buckets have the same size, Python tries to keep at least 1/3 of the buckets empty
# calculate hash
function: hash()  # __hash__; 
  	If two objects compare equal, their hash values must also be equal, objects that are similar but not equal should have hash 		values that differ widely
    a random salt value is added to the hashes of str, bytes and datetime objects. The salt value is constant with‐ in a Python 		process but varies between interpreter runs.
algorithm:
   dict[search_key] --> hash(search_key) --> uses part of hash number as an offset to look up a bucket in the hash table --> 			 found bucket --> 
  	{ empty: KeyError } --> end
    { item with found_key: found_value } -->
    		{ found_key = serach_key } --> return found_value --> end
    		{ found_key != serach_key } --> hash collision(subset of number as index) --> uses other part of hash number as an offset 				to look up a bucket in the hash table --> recursively find bucket
# To put an item in a hash table(fast with O(1))
	1. to calculate the hash value of the item key with hash()
  2. locate bucket
  3. put a value in bucket item
  4. may extend hash size
# limitations
	1. Keys must be hashable objects
  	 hashable: {
       1. supports the hash() function via a __hash__() method that always returns the same value of the object during lifetime.
       2. supports equality via an __eq__() method.
       3. If a == b is True then hash(a) == hash(b) must also be True
     }
     User-defined types are hashable by default because their hash value is their id() and they all compare not equal.
  2. dicts have significant memory overhead
  	 the __slots__ class attribute can change the storage way of instance attributes: dict -> tuple
  3. Key ordering depends on insertion order
  	 When a hash collision happens, the key will placed in another bucket. but dicts with the same kay-value pairs compare equal
  4. Adding items to a dict may change the order of existing keys
  	 may extend the hash table and may occurs hash collision. so should do scan and add in 2 steps
```



### Texts & bytes

> 	str object - bytes object
> 	  encoding: code points to bytes   # 码位 -> 字节标识
> 	  decoding: bytes to code points

```python
 Endianness## bytes
### bytes(sequences of integers)  re supports
  Each item is an integer in range(256). Slices of bytes are also bytes — even slices of a single byte(one item vs sequence).
  	tips: s[0] == s[:1] is only true for the str type
	1. immutable bytes
  2. mutable bytearray
  >>> bt = bytes("café", encoding="utf_8")
  >>> bt_arr = bytearray(bt)
  instantiate
  >>> bytes("café", encoding="utf_8")
  >>> bytes([1, 2, 45, 255, 245])
  >>> bytes(2)  # a binary sequence of size 2
  >>> bt_arr = bytearray(bt)   # bytes copy from an object that implements the buffer protocol (eg. bytes, bytearray, memoryview, 																 array.array)
### displays
	1. printable ASCII (from space to ~)
  2. escape sequences (\t, \n, \r, \\ )
  3. hexadecimal escape sequence (e.g. \x00 is null byte)
### methods - familiar string methods
	endswith, replace, strip, translate, upper
  fromhex()  # only for binary sequence
  >>> bytes.fromhex("31 4B CE A9")  # space separator is optional
# struts
	The struct module provides functions to parse packed bytes into a tuple of fields of different types and to perform the 				opposite conversion, from a tuple into packed bytes.
  struct is used with bytes, bytearray and memoryview objects.
  >>> img = memoryview(buffered objects)  # e.g PIL images
  >>> fmt = "<3s3sHH"
  >>> header = img[:10]  # slicing a memoryview returns a new memoryview, without copying bytes
  >>> struct.unpack(fmt, header) # extract structure info
  (b'GIF', b'89a', 555, 230)
# codecs(encoders/decoders)
	codecs name. e.g: utf_8 = utf8 = utf-8 = u8
  encoding argument value when related to buffer/bytes objects
     ASCII
	1. latin1 (iso8859_1, the basis for other encodings, such as cp1252 and Unicode)
	2. cp1252 (latin1 superset by Microsoft)
  3. cp437 (original character set of the IBM PC)
  4. gb2312 (Legacy standard to encode the simplified Chinese ideographs)
  5. utf-8 (The most common 8-bit encoding on the Web, pure ASCII text is valid UTF-8)
  6. utf-16le (One form of the UTF-16 16-bit encoding scheme)
# encode/decode problems
## Error
   UnicodeError{UnicodeEncodeError、UnicodeDecodeError}、SyntaxError (codecs not found)
   Not every byte holds a valid ASCII、UTF-8、UTF-16, so there will be errors when encoding/decoding
   Legacy 8-bit encodings like 'cp1252', 'iso8859_1', 'koi8_r' are able to decode any stream of bytes, including random noise, without generating errors. it will silently mmisinterpret and decode garbage.
   >>> city = 'São Paulo'
	 >>> city.encode('utf_8')
   >>> city.encode("cp437", errors="ignore") 
    		# strict(default、raise Error)
        # ignore(skip)
        # replace(substitutes unencodable characters with '?', code point of UTF-8 is U+FFFD) 
        # xmlcharefreplace(replaces unencodable characters with a XML entity)
## Source Encoding
	 default:
    	Python 3: UTF-8; Python 2: ASCII
   the .py containing non-UTF-8 data should be with encoding declaration; or will raise SyntaxError
   GNU/Linux and OSX: UTF-8; windows: cp1252
   encoding declaration comment
   >>> # coding: cp1252
## How to discover the encoding of a byte sequence (must be told)
	 package: Chardet 
 	 the UTF formats may prepend a byte order mark to the textual content.
   >>> BOM (byte-order mark 字节序标记)
    	a couple of extra bytes at the beginning of an UTF-16 encoded sequence
   >>> U+0045  # decimal 69
   >>> 69, 0   # 小字节序设备 U+ FFFE  \xff\xfe; UTF-16LE explicitly little endian, BOM will be ignored and self-generate
   >>> 0, 69   # 大字节序设备 U+ FEFF  \xfe\xff; UTF-16BE explicitly big endian
  		To avoid confusion, the UTF-16 encoding prepends the text to be encoded with the special character ZERO WIDTH NO-BREAK 					SPACE (U+FEFF) which is invisible
   		endianness only affects encodings that use words of more than one byte, like UTF-16 and UTF-32. UTF-8 use one byte, dont 				need BOM. But it will have the BOM with value \xef\xbb\xbf in some occasions(win) 
   tips: 
    	--->  : 大端/小端序，高位字节还是最低位字节前面； 混合序 16bit 内部 和 之间
      网络传输一般采用大端序，也被称之为网络字节序，或网络序。IP协议中定义大端序为网络字节序。虽然高字节先传，但每一字节内低位先传
    	Endianness 字节顺序(多字节)；endian 源于格列佛游记中小人国为水煮蛋该从大端(big-end)还是小端(little-end)剥开而争论
      将一个多位数的低位放在较小的地址处，高位放在较大的地址处，则称小端序;反之则称大端序
        0x1234567              --memory address-->  
      	big-end:  						 01 23 45 67									human-readable
        little-end:						 67 45 32 01									machine-handle
```

```python
## text
Inner process should be only related to text (Unicode Sandwish) e.g  open("path/file", "mode"); rb bytes mode
	bytes should be decoded to str as early as possible on input
  str should be encoded to bytes as late as possible on output
## file (text files & binary files)
	reading file depends on default encoding on system. specify the codecs
  >>> locale.getpreferredencoding()  # the default codecs text files | redirected console output； default value for open func
  >>> sys.stdout.encoding   # the same as the console encoding.  also applied to redirected console output but equal text codecs
  >>> sys.stdout.isatty()   # whether output to console
  >>> sys.getdefaultencoding()  #  convert binary data to/ from str
  >>> sys.getfilesystemencoding()  # encode/decode file names (not file con‐ tents)
## standard unicode for compare
	'é'  基字符-e 和 组合字符-重音符
  		 unicode 增加 微字符 兼容，normalize的时候不会改动
	>>> s1 = 'café' # composed "e" with acute accent as one
  len(s1) = 4
	>>> s2 = 'cafe\u0301' # decomposed "e" and acute accent into two
  len(s2) = 5
  >>> s1==s2 
  False. 
  'é' and 'e\u0301' are called “canonical equiv‐ alents”. But the python get different codecs
  >>> from unicodedata import normalize
  >>> normalize('NFC', s1) == normalize('NFC', s2)
  True
  - First Argument of normalize
  	- NFC  (Normalization Form Compose)  # Default nomalization form
    - NFD  (Normalization Form Decompose)
    - NFKC   # K means compatibility； 兼容会导致数据损失，一特殊情况使用 如 搜索、索引
    - NFKD
## Case folding
	str.casefold()
  str.casefold() equals str.lower(), when the string only contains latin1 characters; with only two exceptions: the micro sign 		'μ' is changed to the Greek lower case mu (which looks the same in most fonts) and the German Eszett or “sharp s” (ß) becomes 	“ss”.
## Compare
	def nfc_equal(str1, str2):
			return normalize('NFC', str1) == normalize('NFC', str2)
	
  def fold_equal(str1, str2):
			return (normalize('NFC', str1).casefold() == normalize('NFC', str2).casefold())
## Take out diacritics
	针对拉丁文，将其变成纯粹的ASCII
	def shave_marks(text):
    	"""
    		Remove all diacritic marks
    			NFD -> shave -> NFC
    		会修改非拉丁文字符
    	"""
      norm_text = unicodedata.normalize("NFD", text)  # decompose -> base character + separate combining character
      shaved = ''.join(c for c in norm_text if not unicodedata.combining(c))   # 判断是否是 separate conbining character（变音符）
      return unicodedata.normalize("NFC", shaved)
  
  def shave_marks4latin(text):
    	norm_text = unicodedata.normalize("NFD", text)  # decompose -> base character + separate combining character
      latin_base = False  # 前一个字符是否是latin base character
      filtered = []
      for cha in. norm_text:
        	if unicodedata.combining(cha) and latin_base:
            	continue  # shave
          filtered.append(cha)
          if not unicodedata.combining(cha):
            	latin_base = c in string.ascii_letters.  # 判断是否是
      shaved_text = "".join(filtered)
      retunr unicodedata.normalize("NFC", shaved_text)
```

## Function（First-class）

> - created at runtime
> - assigned to a variable or element in a data structure
> - passed as an argument to a function
> - returned as the result of a function

### 一等函数

```python
function 类
# attribute
	__doc__   # help(func_name)	
  __defaults__  # default value of arguments; 从后往前扫描匹配变量，因为参数数量不定
  __code__    # code object with name of arguments and etc
  		co_varname
    	co_argcount
# Hig-order Function
	A function that takes a function as argument or returns a function as result
  e.g 
  	map:   [ new_values ]   # lambada x: x*2  , returns value
    filter:  [ sub_iterable ]    # lambda x: x %2 == 0  , returns bool 
    reduce: single_value    # lambda x, y: x + y,  returns value; can initialize the first argument； accumulate
      reduce(lambda x, y: x + y, iterable, 10)  # 10 will be the first argument
      operator.add # 等价于 + 
    zip(iter1, iter2, iter3)
    apply: apply(callable, args, kwargs) = callable(args, kwargs)
    sorted: sorted(iterable, key=callable)
# Reducing Func
	reduce、sum、all、any
# Anonymous Func
	lambda syntactic sugar
# Callable Objects  # callable(obj) -> bool
	> based on __call__
	functions { User-defined、Built-in }
  method { Built-in、Class-method }
  Classe
  instance of class
  Generator   # functions or methods with yield key word
# keyword-only arguments
	def foo(a, *, b):  # b must passed as keyword argument
    	pass
  def foo(a, *args, b, *kwargs):
    	pass
# Retrieving information about parameters
	1. __code__
  2. inspect module
  	from inspect import signature
  	>>> sig = signature(foo)
    >>> sig.parameters.items()
    odict_items([('a', <Parameter "a">), ('args', <Parameter "*args">), ('b', <Parameter "b">), ('kwargs', <Parameter 							"**kwargs">)])
    >>> sig.parameters.get("a")
    <Parameter "a">    # name、kind、default、annotation
    >>> bound_args = sig,bind(**kwargs)   # 将value绑定到同名的形参
    from inspect import getmembers
    >>> getmembers(module, <<bool>>)  # 筛选条件
# Function annotations
	__annotations__
	def foo_v2(a: 'int > 0', b: 'int < 0') -> 'int > 0':
    	return a - b
# Packages for functional programming
	operator、functools
 	## Operator
  itemgetter((index1, index2))(iterable)   # returns (iterable[index1], iterable[index2]); based on __getitem__ (list、dict)
  attrgetter((attrname, attrname1.attrname2))(obj)  # returns attr of object recursively；  Name=namedtuple("Name", "attr1 attr2")
  methodcaller("func_name")(instance)
  	upcase = methodcaller("upper"); upcase("test string")
    replace = methodcaller("replace", " ", "-"); replace("test string")  # 限定参数， functools.partial
  ## functools
  reduce
  partial / partialmethod.  # 用于函数 和 方法
  	partial(callable, *args, **kwargs)
  	nfc = functools.partial(unicodedata.normalize, "NFC")
```

```python
Design patterns
# Strategy
当具体策略类只有一个类方法时，可以直接使用函数替换
>>> strategy.py
>>> selected_strategies = inspect.getmembers(strategy, <<bool>>)
# Command (invoker - command - client)
class Func:
  def __ini__(self):
    pass
  def __call__(self, *args, **kwargs):
    pass
def func(*args, **kwargs):
  pass
```

### 装饰器  -- 函数名的装饰，原有逻辑是一个整体，只能新建函数在其前面/后面增加 或 直接覆写； 装饰器返回的是新建函数名
```python
Decorator and closure
	A decorator is a callable that takes another function as argument (the decorated func‐ tion), returns it or replaces it with another function or callable object. 
	@deco
	def func():
		...
    retunr callable
  func = deco(func)
# Feature
	Replace
  Initialize when loading module / run right after the decorated function is defined
		# 函数装饰器在导入模块时立即执行，被装饰函数只在明确调用时执行
# Variable scope
	无声明的情况下，赋值即私有，若外部有相同名称的变量则被遮挡
	想修改外部变量，需声明（global、nonlocal），或者通过可变对象的内置函数
  变量名的绑定将在当前作用域中引入新的变量，同时屏蔽外层作用域中的同名变量
	假定在函数体中赋值的变量是局部变量
  g_b = 6
  def func1(a):
    print(a)
    print(b)
  def func2(a):
    print(a)
    print(b)
    b = 9    # UnboundLocalError: local variable 'b' referenced before assignment
# closure
	必包的自由变量绑定会保留到不同的内部作用域， 类似类的实例属性
  闭包延伸到函数的作用域之外
  def make_averager():   # free varable
    # ----------- 
		series = []   # free varable； 作用域在当前这个make_averager函数
		
    def averager(new_value): 
      series.append(new_value)    # free varable 自由变量 赋值操作仍会触发错误
      total = sum(series) 
      return total/len(series)
    # -----------   closure
    
		return averager
  >>> avg = make_averager()
  >>> avg.__code__.co_varnames
  ('new_value', 'total')
	>>> avg.__code__.co_freevars 
  ('series',)
  >>> abg.__closure__
  (<cell at 0x107a44f78: list object at 0x107a91a48>,)   # cell 对象，tr: cell_contents, 
  >>> avg.__closure__[0].cell_contents
	[10, 11, 12]
# Key Word
	global var
  nonlocal var    # 把变量标记为自由变量，更新会反影响到闭包
# Decorator
	装饰器叠加，上装饰下
  def outter(*args, **kwargs):
    def deco(func):
      @functools.wraps(func).   # 把func相关的属性复制到inner
      def inner(*args, **kwargs):
        return func(*args, **kwargs)
      return inner
    return deco
# functools decorators
	wraps、lru_cache、singledispatch
  > wraps  # 复制函数属性
  > lru_cache  # 备忘功能 Least Recent Used
  	@functools.lru_cache(maxsized=128, typed=False)
    # 缓存字典大小，typed是否区分传入参数类型 3 ｜ 3.0
    # 被装饰函数的传入参数必须是hashable，用于构建缓存key
    def fibonacci(n):
      	if n < 2:
          return n
        return fibonacci(n-2) + fibonacci(n-1)
  > singledispatch  # 单分派 + 泛函数
  	> 普通分派函数
    def dispatch_func(kind, *args, **kwargs):
      if kind == kind1:
        handle_kind1()
      elif kind == kind2:
        handle_kind2()
    > singledispatch   # 实现方法重载，根据不同第一个参数的不同类型分派处理
    from functools import singledispatch 
    from collections import abc
    import numbers
    import html
    
    @singledispatch    # 被修饰函数创建一个register绑定装饰器
    def htmlize(obj):   # 不确定对象参数
    	content = html.escape(repr(obj)) 
      return '<pre>{}</pre>'.format(content)
    
    # 被分派的函数应该处理抽象基类 numbers.Integral、abc.MutableSequence; 适用性更强
    # 叠加支持多种
    # 可随时扩展
    @htmlize.register(str) 
    def _(text):
    	content = html.escape(text).replace('\n', '<br>\n') 
      return '<p>{0}</p>'.format(content)
    
    @htmlize.register(numbers.Integral) 
    def _(n):
    	return '<pre>{0} (0x{0:x})</pre>'.format(n)
    @htmlize.register(tuple) 
    @htmlize.register(abc.MutableSequence) 
    def _(seq):
    	inner = '</li>\n<li>'.join(htmlize(item) for item in seq) 
      return '<ul>\n<li>' + inner + '</li>\n</ul>'
    
# built-in decorators
	property、classmethod、staticmethod

# registration decorator
  def register(active=True): 
    # ------------
    def decorate(func):
      # def inner()
			print('running register(active=%s)->decorate(%s)' % (active, func))
			if active: 
        registry.add(func)
			else: 
        registry.discard(func)
			return func 
    # ----------- 实际装饰器
    return decorate  # 返回装饰器
# Addition (dynamic scoping | lexical scope)
	scope: 一段程序代码中所用到的名字并不总是有效／可用的，而限定这个名字的可用性的代码范围就是这个名字的作用域。 # 命名空间。
	lexical scope: 它的作用域在词法分析阶段确定, 何处声明，基于作用域嵌套  # 作用域链， 定义时; 每次函数求值的时候都创建一个新的env
  dynamic scope: 何处调用, 作用域链是基于调用栈  # 调用栈， 运行时； 整个程序运行的时候只有一个env = binding { identifier: value }
  Scope in Python：
  	Local -> Enclosing -> Global -> Built-in
    module/def/class/lambda : create scope
    		在 def/class/lambda内进行**赋值**，就变成了其局部的作用域，局部作用域会覆盖全局作用域，但不会影响全局作用域
    Enclosing 介于 Local 和 Global 之间； 多层级时相对存在
    		local 中使用 变量赋值 则不会去 enclosing、global 中寻找
      	显示的使用 nonlocal、global 关键字
        locals()、globals()  返回存储当前作用域的binding
```



## Object Oriented

> Every object has an identity, a type and a value.
> 每个变量都有 标识、类型、值； is基于id()标识比较，== 基于__eq__值比较。# CPython中id函数返回对象的内存地址

### 作用域 scope

```python
不可变是指 所含元素的标识 不变
简单赋值 不创建副本，而是新增引用变量
增量赋值： 左边变量绑定的是不可变对象就会创建一个新对象， 为可变对象则会就地修改原对象的值
identity: id()、is    # == 基于 __eq__，有相同的值
# extend
  内嵌不可变元素的引用
  l1 = [3, [66, 55, 44], (7, 8, 9)]
  l2 = list(l1)
  l2[1] += [33, 22]  # l1、l2指向同一个，且更改列表的值
  l2[2] += (10, 11)  # 元组不可变，l2新建一个元组并指向这个新元组，l1不受影响
# 嵌套引用类型的复制
	copy、 deepcopy   # __copy__、__deepcopy__
# 传参
	引用类型 - 共享传参  # 函数内部的形参是实参的别名
  基本类型 - 值传参
# 引用类型做默认值的问题
	"""
		函数默认值保存在 func.__defaults__ 元组
	"""
	class HauntedBus:
    """A bus model haunted by ghost passengers"""
    def __init__(self, passengers=[]):   # 只有一个 default 列表，多个不传值时会共享指向同一个
        self.passengers = passengers
        # 更好的做法是创建副本， self.passengers = list(passengers)    默认浅拷贝，注意嵌套引用类型
    def pick(self, name): 
        self.passengers.append(name)
    def drop(self, name): 
        self.passengers.remove(name)
  bus1 = HauntedBus(['Alice', 'Bill'])  # 指定则无影响

  bus1.pick('Charlie')
  bus1.drop('Alice')

  bus2 = HauntedBus()
  bus2.pick('Carrie')

  bus3 = HauntedBus()   # 此时指向 默认列表
  bus3.passengers   # ['Carrie']
# 引用删除 ｜ 垃圾回收
	对象无引用时触发垃圾回收
  del 删除名称，而不是名称引用的对象， 当del的名称是对象的最后一个引用时会触发垃圾回收机制
  CPython：引用计数 - 垃圾回收算法
  	每个对象都会统计有多少引用指向自己，当计数为0或者仅存的对象引用不可用（循环引用、无引用指向）时，CPython会调用对象的__del__方法，然后释放分配给对象的内存。
    分发垃圾回收算法 -> 循环引用（引用计数永远不为0，但是对象不可获取，泄漏内存）
```

### 弱应用 weakref

```python
# 弱引用 weakref  -  常应用于缓存中
	注意是对 对象 的弱引用
	不会增加对象（被指对象）的引用计数，故不影响垃圾回收
  import weakref
  a_set = {0, 1}  # 对象
  a_wref = weakref.ref(a_set)    # 是可调用对象，返回 被指对象 或 None
  a_wref()   # {0, 1}   
  # 命令行模式下，隐式的将非None的表达式结果绑定到 _ 这个变量上
  a_set = {2, 3, 4}   # {0, 1} 引用计数变为1， _ 引用
  a_wref()  # {0, 1}  此时还有 _ 引用
  a_wref() is None  # False, 此时的 _ 变为引用 False； {0, 1} 的引用计数 为0
  a_wref() is None  # True
# finalize
	weakref.finalize(var, callback: <<callable>>)
	
# 弱引用集合
	1. WeakValueDictionary
  	可变映射，值为被指对象的弱引用，被被指对象被垃圾回收之后，对应的键会自动从wvd中删除，常用于缓存
    weakref.WeakValueDictionary()   # {}
  2. WeakSet
  	元素为被指对象的弱引用，被指对象被垃圾回收时会自动删除该引用元素
# 局限
	弱引用被指对象的局限， 
  	基本的 list、dict 类不能作为被指对象，但是他们的子类是可以的
  	int、tuple 不能作为弱引用，子类也不行
# 序列对象驻留 - 一种优化措施
	t1 = (1,2 ,3 )
	t2 = tuple(t1)
	t3 = t1[:]  # t1 t2 t3 指向同一个
  
  s1 = "ABC"
  s2 = "ABC"
  s1 is s2  # True. 指向同一个
  
  还有小的整数
```

### 类 - 鸭子/白鹅类型

```python
# Pythonic object
	扩展类基于鸭子类型：只需按照预定行为实现对象所需的方法即可
## Object representations
	repr(): __repr__, 便于开发者理解的方式返回字符串表示形式
  str(): __str__, 便于用户理解的方式返回字符串表示形式
  bytes(): __bytes__, 字节序列表示形式
  format(): __format__, 格式化显示
## Vector Class
	class Vector2d:
    __slots__ = ("__x", "__y")
    typecode = "d"
    
    def __init__(self, x, y):
        self.__x = float(x)
        self.__y = float(y)
        
    @property
    def x(self):
      	return self.__x
    
    @property
    def y(self):
      	return self.__y
    """
    实现hash是不需要该属性是只读的，但是一个实例的hash值不应该变化
    """

    def __iter__(self):  # 可迭代， 拆包调用
        return (i for i in (self.x, self.y))

    def __repr__():
        class_name = type(self).__name__   # type(instance)  获取到cls
        return "{}({!r}, {!r})".format(class_name, *self)
      	"""
      	{!r} 
      	！后面可以加s r a 分别对应str() repr() ascii() 作用是在填充前先用对应的函数来处理参数
      	"""
    
    def __str__(self):
        print(self)
        return str(tuple(self))

    def __bytes__(self):
        return (bytes([ord(self.typecode)]) + bytes(array(self.typecode, self)))
    
    def __eq__(self, other):
        return tuple(self) == tuple(other)
    
    def __abs__(self):  # 求弦
        return math.hypot(self.x, self.y)
    
    def __angle__(self):  # 求角度
      return math.atan2(self.y, self.x)
    
    def __bool__(self):
        return bool(abs(self))
    
    def __hash__(self):
        return hash(self.x) ^ hash(self.y)   # 使用 ^ 异或操作符来混合多个可hash的hash值
      
    @classmethod   # classmethod 是类方法-第一个参数为类本身cls， staticmethod是在类中的普通方法
    def frombytes(cls, octets):
        typecode = chr(octets[0])
        memv = memoryview(octets[1:].cast(typecode))
        return cls(*memv)
## Object Format
	object类 的默认 __format__ 实现 str(my_object)
  
  def __format__(self, format_spec = ""):
    	components = (format(c, format_spec) for c in self)
      return "({}, {})".format(*components)
  # 自定义格式说明符
  def __format__(self, format_spec = ""):
    	if format_spec.endswith("p"):
        	format_spec = format_spec[:-1]
          coords = (abs(self), self.angle())
          outer_fmt = "<{}, {}>"
      else:
        	coords = self
          outer_fmt = "<{}, {}>"
      components = (format(c, fmt_spec) for c in coords) 
      return outer_fmt.format(*components)
```

### 属性管理
```python
# Private and “protected” attributes
## 名称改写
	私有属性定义： __privatename
  	存储进 __dict__ 属性中 为 _clsname__privatename
    这是一种安全措施，避免意外访问而无法杜绝故意篡改； 基于此可以直接访问修改私有属性  ins._clsname__privatename = new
    _var 不会触发名称改写机制
## __slots__ 类属性    -- 适用于模式固定的列表数据， 超多实例
	__dict__ 存储实例属性（名+值）, slots使用元组
	继承自超类的slots我有效果，各个类中的slots才有效
  
  __slots__ = ("__x", "__y")
  目的在于告诉解释器该类的所有实例属性都在这，python便会使用元组而非字典来存储实例变量，节省大量内存
# 特殊属性
	__dict__ 不应该放入 __slots__ 中
  __weakref__ 如果想把实例作为弱引用目标，则需要添加该属性
# slots注意点
	- 每个类都要定义__slots__属性，解释器会忽略继承而来的
  - 实例只能拥有 __slots__ 中列出的属性（除非将__dict__添加进入，会导致失去节省内存的功效）
  - 实例做为弱引用被指目标时，__weakref__必须添加进__slots__中
# 类属性 和 实例属性 同名时
	类属性的值作为实例属性的默认值存在，不会被替换
  实例属性赋值不会影响到类属性原本的值
  修改类属性值更好的做法是：子类改写
  class SubVector2d(Vector3d):
    	typecode = "f"
# 协议（非正式接口，定义在文档中）
  序列协议： __len__  __getitem__
  关注行为，实现len、getitem的就是分片
  ### Slice 对象
  Attr：start、stop、step
  Method：indices
  slice_ins.indices(lenth)  -> tuple(start, stop, step)   # 自动处理越界、负stride的情况转化成正 
```
### 鸭子行为
```python
# 序列的修改、散列和切片
from array import array
import reprlib
import math
class Vector:
  typecode = "d"
  shortcut_names = "xyzt"

  def __init__(self, components):
    self._components = array(self.typecode, components)
    
  def __iter__(self):
    return iter(self.__components)
  
  def __repr__(self):
    components = reprlib.repr(self._conponents)
    components = components[components.find("["): -1]
    return "Bector({})".format(components)
  
  def __str__(self):
    return str(tuple(self))
  
  def __bytes__(self):
    return (bytes([ord(self.typrcode)]) + bytes(self._components))
  
  def __eq__(self, other):
    # return tuple(self) == tuple(other)
    """ 
    if len(self) != len(other):
      return False
    for i, j in zip(self, other):
      if i != j:
        return False
    return True
    """
    # zip 并行迭代返回生成器；处理不等长的情况
    return len(self) == len(other) and all(a == b for a, b in zip(self, other))
  
  def __hash__(self):
    """
    映射归约 map -> reduce
    """
    # hashes = (hash(x) for x in self._components)
    hashes = functools.map(hash, self._components)
    return functools.reduce(operator.xor, hashes, 0)
  	# reduce(func, iterable, initial_value)  当 iterable 为空时返回 initial_value
  
  def __abs__(self):
    return math.sqrt(x*x for x in self)
  
  def __bool__(self):
    return bool(abs(self))
  
  @classmethod
  def fromnytes(cls, octets):
    typecode = chr(octets[0])
    memv = memoryview(octets[1:]).cast(typecode)
    return cls(memv)
  
  def __len__(self):
    return len(self._compoments)
  
  def __getitrm__(self, index):   # setitem
    cls = type(self)
    if isinstance(index, slice):  # start:stop:step ; indices()
      return cls(self._components[index])
    elif isinstance(index, numbers.Integral):
      return self._components[index]
    else:
      msg = "{cls.__name__} indices must be integers"
      raise TypeError(msg.format(cls=cls))
  def __getattr__(self, name): 
    """
    仅当对象没有指定名称的属性时才会调用这个方法，这是一个备用机制
    >>> v = Vector([1.0, 2.0, 3.0, 4.0])
    >>> v.x
    1.0
    >>> v.x = 10   # 赋值绑定到了 v.x； self._components 里面的值没有变
    >>> v.x    # v.x已经有值了，不会触发getattr
    10
    >>> v
    Vector([1.0, 2.0, 3.0, 4.0])
    """
    cls = type(self)
    if len(name) == 1:
      pos = cls.shortcut_names.find(name)
      if 0 <= pos < len(self._components):
        return self._components[index]
      msg = "{.__name__!r} object has no attribute {!r}"
      raise AttributeError(msg.format(cls, name))
  def __setattr__(self, name, value):
    if len(name) == 1:
			if name in cls.shortcut_names:  # 同名保留属性
				error = 'readonly attribute {attr_name!r}' 
      elif name.islower():  # 小写属性名保留
				error = "can't set attributes 'a' to 'z' in {cls_name!r}" 
      else:
				error = '' 
      if error:
				msg = error.format(cls_name=cls.__name__, attr_name=name)
				raise AttributeError(msg) super().__setattr__(name, value)
    super().__setattr__(name, value)
    
  def angle(self, n):
		r = math.sqrt(sum(x * x for x in self[n:])) 
    a = math.atan2(r, self[n-1])
		if (n == len(self) - 1) and (self[-1] < 0):
			return math.pi * 2 - a 
    else:
			return a 
  
  def angles(self):
		return (self.angle(n) for n in range(1, len(self)))
  
	def __format__(self, fmt_spec=''):
		if fmt_spec.endswith('h'): # hyperspherical coordinates
			fmt_spec = fmt_spec[:-1]
			coords = itertools.chain([abs(self)], self.angles()) # itertools.chain生成生成器表达式
			outer_fmt = '<{}>' 
    else:
			coords = self
			outer_fmt = '({})'
		components = (format(c, fmt_spec) for c in coords) 
    return outer_fmt.format(', '.join(components))
    
```
### 抽象基类
```python
# 协议到抽象基类 （抽象类是可提供具体方法实现的接口声明） 抽象基类会检查子类
# 协议为非正式的接口
# 鸭子类型 - 表征分类：忽略对象本身，转而关注对象有没有实现所需的方法、签名和语义（聚焦表征）
# 支序系统学 - 继承特征：聚焦继承的一致性
接口：实现或继承的公开属性（方法、数据属性）
接口 -> 角色：接口是实现特定角色的方法集合
对象 < 协议 < 接口
序列协议：__getitem__、__contains__、__iter__、__reverse__、index、count
抽象基类｜序列 的本质是几个特殊方法
>>> class Struggle:
... 		def __len__(self): return 23 
...
>>> from collections import abc
>>> isinstance(Struggle(), abc.Sized) 
True
## 鸭子类型的测试
	isinstance(ins, cls)、issubclass(cls, abc.cls)
  class Sized(metaclass=ABCMeta):
    	__slots__ = ()
      
      @abstractmethod
      def __len__(self):
        	return 0
      
      @classmethod
      def __subclasshook__(cls, C):
        	# 方法行为检测
        	if cls is Sized:
            	if any("__len__" in B.__dict__ for B in C.__mro__):
                	return True
          return NotImplemented
## 抽象基类
collections.abc -> collections、numbers、io
### abc
	abc.ABC  原抽象基类，定义新抽象类使用 Lib/abc.py
	collections.abc   Lib/_collections_abc.py
### 16个抽象基类
	Iterable、Container、Sized、Callable、Hashable
  Iterator、Sequence、Mapping、Set、MappingView
  MutableSequence、MutableMapping、MutableSet、ItemsView、KeysView、ValuesView
》Iterable, Container, Sized
	__iter__、__contains__、__len__
》Sequence, Mapping, Set
	不可变集合类型
》MutableMapping、MutableSet
	可变类型
》MappingView
	ItemsView - items()
  KeysView - keys()
  ValuesView - values()
》Callable、Hashable
	调用、散列
》Iterator
	Iterable的子类
### 数字塔 抽象基类 numbers.
	Number
  Complex  复数
  Real  浮点数
  Rational  
  Integral  整型 (int、bool).  bool是int的子类
### 定义抽象基类

 	装饰器：
  	@abc.abstractmethod
    @abc.abstractclassmethod = @abc.abstractmethod + @classmethod
    @abc.abstractstaticmethod = @abc.abstractmethod + @staticmethod
    @abc.abstractproperty = @abc.abstractmethod + @property

import abc

class Tombola(abc.ABC):
  """
  python 2.*
  	class Tombola(object):
  		__metaclass__ = abc.ABCMeta
  
  python 3.*
  	class Tombola(metaclass=abc.ABCMeta):
  		# 
  """

    @abc.abstractmethod
    def load(self, iterable):
        """从迭代对象中添加元素"""

    @abc.abstractmethod
    def pick(self):
        """随机删除元素，然后将其返回，不存在则抛出LookupError"""

    def loaded(self):
        return bool(self.inspect())

    def inspect(self):
        """返回一个有序元组，由当前元素构成"""
        items = []
        while True:
            try:
                items.append(self.pick())
            except LookupError:
                break
        self.load(items)
        return tuple(sorted(items))
      
### 继承实现子类
class BingoCage(Tombola):
  	"""
  	直接继承部分已实现的方法
  	"""
    def __init__(self, items):
        self._randomizer = random.SystemRandom()
        # os.urandom()生成适用于加密的随机字符串
        self._items = []
        self.load(items)

    def load(self, iterable):
        self._items.extend(iterable)
        self._randomizer.shuffle(self._items)

    def pick(self):
        try:
            return self._items.pop()
        except IndexError:
            raise LookupError("pick from empty BingoCage")

    def __call__(self, *args, **kwargs):
        self.pick()

class LotteryBlower(Tombola):
  	"""
  	全部覆盖抽象基类中的方法
  	"""
  
    def __init__(self, iterable):
        self._balls = list(iterable)

    def load(self, iterable):
        self._balls.extend(iterable)

    def pick(self):
        try:
            position = random.randrange(len(self._balls))
        except ValueError:
            raise LookupError('pick from empty BingoCage')
        return self._balls.pop(position)

    def loaded(self):
        return bool(self._balls)

    def inspect(self):
        return tuple(sorted(self._balls))
      
### 注册虚拟子类
在抽象基类上条用register方法； isinstance、issubclass 等函数都能识别；注册的类不会从抽象基类中继承任何方法或属性；故基类不会检查子类

from random import randrange


@Tombola.register    # 装饰器的方式注册
"""
TomboList.register(Tombola)
"""
class TomboList(list):

    def __pick__(self):
        if self:
            position = randrange(len(self))
            return self.pop(position)
        else:
            raise LookupError('pop from empty TomboList')

    load = list.extend

    def loaded(self):
        return bool(self)

    def inspect(self):
        return tuple(sorted(self))
```

```python
### 子类化内置类型
	C语言实现的内置类型不会调用用户定义的类覆盖的特殊方法
  eg：
  		dict.get()  只会调用内置类型的__getitem__()，不会调用子类覆写的方法；sub_dict.get() 但子类的实例仍然会调用当前覆盖的。
	    问题在于子类如果单纯继承内置类型的某些方法，而这些方法又调用了被子类覆写的同名方法，子类覆写的则会被忽略，依旧使用内置类型的
  解决方法：
  		字典类型：集成。UserDict （python编写的类 UserDict、MutableMapping）
### 多重继承与方法解析顺序
	__mro__ : Method Resolution Order 方法查找顺序; 所以只会列出真实的类，不会包含虚拟的超类
  >>> TomboList.__mro__   # 类列表； 定义继承时左优先；基于C3算法
	(<class '__main__.TomboList'>, <class 'list'>, <class 'object'>)
=======菱形冲突
class A:
		def ping(self):
        print('ping:', self)
class B(A):
		def pong(self):
        print('pong:', self)
class C(A):
		def pong(self):
        print('PONG:', self)
class D(B, C):
		def ping(self): super().ping()
				print('post-ping:', self)
		def pingpong(self): 
      	self.ping()
				super().ping() 
        self.pong() 
        super().pong() 
        C.pong(self)   # 类名限定方法调用 d = D(); C.pong(d)
### 处理多重继承
	1. 接口继承 和 实现继承 区分开
  2. 使用抽象基类显示表示接口（接口作用的类定义成抽象类，可以检查子类）
  3. 混入类Mixin Class（打包方法，为多个不相关的子类提供方法） 重用代码
  4. 名称中明确指明是否含有混入类
  5. 抽象基类可以作为混入，反之则不成立（抽象基类可以实现具体方法，且定义类型 - 混入无法定义类型； ）
  6. 不要子类化多个具体类（单具体类 + 多抽象基类 + 多混入类）
  7. 聚合类 = 抽象基类 或 混入类 的组合
  		class Widget(BaseWidget, Pack, Place, Grid):  # 聚合：组合多个类
      		pass
  8. 优先使用对象组合，而不是类继承
```

### 重载 - 运算符
```python
### 运算符重载 - 一元运算符、中缀运算符
	1. 不能新建只能重载
  2. 不能重载内置类型的运算符
  3. is、and、or、not 不能重载；但 &、｜、～ 可以重载 （ ~ 逐位取反，计算机二进制存储的逐位取反 ）
  		"""
  		原码：符号位(0 正、1 负) + 绝对值
  		反码：
  				正数： 反码 = 原码
  				负数：原码基础上 符号位不变，余位 取反
  		补码：
  				正数：补码 = 原码
  				负数：补码基础上 符号位不变，末位 +1
  		######################################
  		反码：
  				解决原码减法的问题 1 - 1 = 1 + (-1)
  				原码 --｜
  				0000 0001 =  1
  				1000 0001 = -1
  				1000 0002 = -2
  		补码：
  				解决反码正负0的问题
          	0000 0000  +0 
          	1000 0000  -0
  				反码 -- ｜
  				0000 0001 =  1
  				1111 1110 = -1
  				1111 1111
  				1000 0000 = -0  (原码)
  		"""

### 一元运算符   -、+、～
	返回新对象
	- (__neg__)
  + (__pos__)
  ~ (__invert__)
  abs() (__abs__)   # 返回标量

### 中缀运算符
	1. + (__add__、__radd__)    # reversed operand
  	def __add__(self, other):
      pairs = itertools.zip_longest(self, other, fillvalue=0.0)
      return Vector(a+b for a,b in pairs)
   	a + b 的方法调用
    	a 有 __add__ 方法且返回值不是NotImplemented，则直接返回 a.__add__(b);
      否则
      b 有 __radd__ 方法且返回值不是NotImplemented，则直接返回 b.__radd__(a)
      否则
      抛出 TypeError: unsupported operand type(s) for +: 'A_Cls' and 'B_Cls'
    tips: NotImplemented 是一个特殊的单例值； NotImplementedError 是一种异常
      		自己实现的时候为兼容的数据类型最好抛出NotImplemented；可以有机会执行 reverse operation 或 交由Python处理
  2. * (__mul__、__rmul__)
  3. // (__floordiv__)
  4. % (__mod__)
  5. divmod() (__divmod__)
  6. **、pow()  (__pow__)
  7. @  (__matmul__)   # 矩阵乘法(点积)   __rmatmul__、__imatmul__
  8. &  (__adn__)
  9. |  (__or__)
  10. ^ (__xor__)   # 异或
  11. << (__lshift__)
  12. >> (__rshift__)
  Comparative Operator   
  	# 次优先级的反向调用  只是将参数的位置调换
    # ==、!= 如果反向调用失败之后不会返回NotImplemented，而是比较对象的ID；不会抛出TypeError
  1. == (__eq__)
  2. != (__ne__)   # 对 __eq__的结果取反
  3. >  (__gt__)
  4. >= (__gte__)
  5. <  (__lt__)
  6. <= (__lte__)
 	Instantial Operator
  	# 基于 基本操作符 的语法糖； 扩展左操作符，右操作符的限制会少一点
  	""" 如果没有定义 += , 执行 a += b 则会 等价于 a = a + b 创建新对象作为结果返回
  			否则便是直接改变左操作数的值，id不变"""
```

### Format 格式

```markdown
# format 格式转换    --四舍五入截断
{字段名:格式说明符}
数字					格式			输出					描述
3.1415926		 {:.2f}	   3.14	    		保留小数点后两位
-1.02315		 {:+.2f}	 -1.02				带符号保留小数点后两位
2.71828			 {:.0f}		 3						不带小数
1000000			 {:,}			 1,000,000		以逗号分隔的数字格式
0.25				 {:.2%}		 25.00%				百分比格式
1000000000	 {:.2e}		 1.00E+09			指数记法
25					 {:b}		 	 11001				转换成二进制
25					 {:d}		 	 25					  转换成十进制
25					 {:o}		 	 31						转换成八进制
25					 {:x}		 	 19						转换成十六进制
5						 {:0>2}		 05						数字补零(填充左边, 宽度为2)
5						 {:x<4}		 5xxx					数字补x (填充右边, 宽度为4)
10					 {:x^4}		 x10x					数字补x (填充两边,优先左边, 宽度为4)
13					 {:10}		 13						右对齐 (默认, 宽度为10)
13					 {:<10}		 13						左对齐 (宽度为10)
13					 {:^10}		 13						中间对齐 (宽度为10)
转换标志 ! 
内容预处理
!s : str()
!r : repr()
!a : ascii()
# format函数  基于格式规范微语言
format(content, spec)  
eg.
	formatted = format(42, "b")  # b 二进制，x 十六进制，f 小数形式的float， .2% 两位小数百分数
# 自定义格式说明符 或 实现对象的format
	format(content, spec)
```



## Control Flow
### 迭代

```python
# 迭代器/生成器
 表示数据流的对象
 内存放不下的数据集，使用这种惰性获取数据的方式
 可迭代对象：实现了 __iter__ 或 __getitem__ 参数0开始的整数索引    #  __iter__ 返回迭代器； 不能实现 __next__，因为需要单独的迭代器来获取元素
 迭代器：取出元素； 生成器：生成元素； it = iter(iterable)、next(it)、StopIteration   #  __iter__ 返回self迭代器本身、__next__
  	迭代器接口：__iter__、__next__   # (单向单次，无元素时抛出异常，无法还原) for、with等上下文关键字会处理StopIteration
 生成器 yield  ( 属于 迭代器 )
# Sentence 类
import re
import reprlib

RE_WORD = re.compile('\w+')

class Sentence:
  	def __init__(self, text):
      self.text = text
      self.words = RE_WORD.findall(text)
    
    def __repr__(self):
      return "Sentence(%s)" % reprlib.repr(self.text)   # repr函数用于生成大型数据结构的简略字符串形式

"""
可迭代依赖于内置iter(), magic函数位 __iter__ 或 __getitem__ 参数开始于0。
此时的Sentence是可迭代的，在于可迭代对get_item的特殊处理
可迭代：
		1. 实现了 __iter__ （白鹅类型 - issubclass； abc.Iterable 实现了一个 __subclasshook__ 方法用于子类校验）
		2. 实现了__getitem__， 且其参数为0开始的整数；则python会创建一个迭代器 （鸭子类型 - 行为）
"""
## 使用 __getitem__ 供内置iter调用
class SentenceV1(Sentence):
  	def __getitem__(self, index):
      return self.words[index]
    
    def __len__(self):
      return len(self.words)

## 实现 __iter__ 返回迭代器
class SentenceV2(Sentence): # 可迭代对象： 内置iter调用可返回迭代器
  	def __iter__(self):
      	return SentenceIterator(self.words)

class SentenceIterator: # 迭代器
  	def __init__(self, words):
      	self.words = words
        self.index = 0
    
    def __next__(self):
      	try:
          word = self.words[self.index]
        except IndexError:
          raise StopIteration:
        self.index += 1
        return word
    
    def __iter__(self):
      return self

## 使用 生成器 代替 迭代器
class SentenceV3(Sentence):
  	def __iter__(self):
      # 等价 return iter(self.words)
      for word in self.words:
         yield word
	"""
	生成器函数：函数定义体中含有yield关键字；调用该函数会返回一个生成器对象
	func -> 函数对象（生成器函数： 制造生成器的工厂）
	func() -> 生成器对象
	next(func()) -> 产出的值
	"""
## Lazy Evaluation惰性求值 -   Eager Evaluaion及早求值
	前几版的 __init__ 方法初始化时即创建文本的单词列表全表，然后绑定到self.words上；当传入的文本数据过大超出内存容量时会出错
  
  
import re
import reprlib

RE_WORD = re.compile('\w+')

class Sentence:
  	def __init__(self, text):
      self.text = text
    
    def __repr__(self):
      return "Sentence(%s)" % reprlib.repr(self.text)   # repr函数用于生成大型数据结构的简略字符串形式
    
    def __iter__(self):
      for match in RE_WORD.finditer(self.text): finditer生成器函数 返回生成器对象
        yield match.group()
    	### 生成器表达式
    	return (match.group() for match in RE_WORD.finditer(self.text))
```

```python
itertools 模块 标准库中的生成器模块

## 自己实现等差数列生成器  itertools.count(start, step)  |. step支持不同的类型 int、float、Fraction、Decimal
class ArithmeticProgression:

    def __init__(self, begin, step, end=None):
        self.begin = begin
        self.step = step
        self.end = end

    def __iter__(self):
        # 可运算类型隐式的会类型转换
        result = type(self.begin + self.step)(self.begin)
        forever = self.end is None
        index = 0
        while forever or result < self.end:
            yield result
            index += 1
            result = self.begin + self.step * index

## itertools.takewhile(Predicator(Callable->bool), Iterator)    
		Selector 返回bool值做筛选, 等价Predicator
		itertools.count(start, step) 	无限制生成
  	条件过滤生成优化：
    	itertools.takewhile(lambda n: n<3, itertools.count(first, step))
    if end is not None:
       return itertools.takewhile(lambda n: n < end, itertools.count(first, step))

## 标准库中的生成器函数
====过滤====
bultin.
			 filter(predicator, it)      # 产出predicator为真的值，如果predicator为None则只产生 bool(item) is True 的 item
itertools.
					compress(it, selector_it)   # 双生成器，list(itertools.compress('Aardvark', (1,0,1,1,0,1))) -> ['A', 'r', 'd', 'a']
  				dropwhile(predicator, it)  # 跳过predicator为真的值
    			takewhile(predicator, it)  # 产出predicator为真的值
      		filterfalse(predicator, it)  # 与bultin.filter 相反
        	islice(it, stop) / islice(it, start, stop, step)  # it[:stop]  it[start:stop:step]
====映射====
bultin.
			 map(func, it1, [it2, ..., itN])  # 产出 func 的返回值， 生成器参数的数量由func的参数决定，并行传入作为func的参数
  		 enumerate(it, start=0)           # ((index, items), (index, items), (index, items), )
itertools.
					starmap(func, it)   # it 的元素为 it, 产出 func(*iit) 的值
  				accumulate(it, [func])  # 当前元素 被替换为 当前元素 和 之前元素的 和 或者 其他 func 运算  (min, max, operator.mul)
    																					sample=[5,4,2,8,7,6,3,0,9,1]
    					  									求总和			  list(itertools.accumulate(sample))  ==>  [5, 9, 11, 19, 26, 32, 35, 35, 44, 45]
      														最小值				list(itertools.accumulate(sample, min)) =>  [5, 4, 2, 2, 2, 2, 2, 0, 0, 0]	
        													最大值				list(itertools.accumulate(sample, max)) =>  [5, 5, 5, 8, 8, 8, 8, 8, 9, 9]
====合并====
bultin.
			 zip(it1, ..., itN)   # enumerate 强化版，只要有一个可迭代的对象没有产出，就静默停止
itertools.
					zip_longest(it1, ..., itN, fillvalue=None)   # zip 最长的可迭代对象，短的缺失值使用 fillvalue 填充
  				chain(it1, ..., itN)   # it1 + ... + itN  产出
    			chain.from_iterable(it)   # it 生成的多个可迭代对象， 两维解开成一维
      		product(it1, ..., itN, repeat=1)   # 笛卡尔积： A×B = {(x,y)|x∈A∧y∈B}
        						list(itertools.product("ABC", repeat=1)) => [('A',), ('B',), ('C',)]
										list(itertools.product("ABC", repeat=2)) => 
            				[('A', 'A'), ('A', 'B'), ('A', 'C'), ('B', 'A'), ('B', 'B'), ('B', 'C'), ('C', 'A'), ('C', 'B'), ('C', 'C')]
              			list(itertools.product("ABC", repeat=3)) => 
                		[('A', 'A', 'A'), ('A', 'A', 'B'), ('A', 'A', 'C'), ...., ('C', 'C', 'A'), ('C', 'C', 'B'), ('C', 'C', 'C')]

====扩展====
itertools.
					cycle(it)   # 循环产出 it 的元素
      				count(start=0, step=1)     # 等差列
      				repeat(item, [times])    # 单值生成器，times指定长度，默认无限
      
					combinations(it, out_len)   # 取it中的out_len个元素按顺序组合成单个元素，返回生成器((out1, ..., outlen), )； 不包含相同元素
  				combinations_with_replacement(it, out_len)  #  包含相同元素的组合 即 自身元素的组合
  				permutations(it, out_len=None)  #  out_len个 元素的所有排列变化
  									product	 加上三个一起被称为 组合学生成器 {com 自身顺序排列组合， product 笛卡尔二维排列组合， permu：所有排列变化}

====重新排列====
builtin.
				reversed(seq)  # 重后向前产出seq中的元素，seq必须是序列 或者 实现了 __reversed__ 特殊方法的对象
itertools.
					groupby(it, key=None)   # 产出 ( (key, group_it), ); key是 Callable(item)   eg.  groupby(it, key=len) 按长度对元素分组			
  				tee(it, n=2)   # 将一个 迭代器 复制创建回多个； 直接赋值无效
```

```
yield from Iterable
	生成器函数需要产出另一个生成器生成的值， 常规使用 for 嵌套
```

```python
可迭代对象作为参数的归约函数
builtin.
				all(it)  # it中所有元素都为真时返回True, 否则返回False。 all([]) 返回 True； 短路特征
				any(it)  # 有元素为真就返回True，否则返回False。 any([]) 返回 False； 短路特征
    		max(it, [key=,] [default=])  # key 是排序函数，当it为空时返回default
      	min(it, [key=,] [default=])  # min(arg1, arg2, ..., [key=,] [default=])
        sum(it, start=0)   # start 为初始值；   浮点数计算时可以使用 math.fsum()
funtiontools.
						 reduce(func, it, [initial])  # 前两个元素作为参数给func归约为一个值， initial指定第一个值
```

```python
iter 内置生成器函数
	iter(Callable, sentinel)   # Callable产生一个值
  当产出的值等于 sentinel 时 会抛出 StopError

GeneratorType: 生成器表达式 或 生成器函数
```

```python
yield 只能把最近的外层函数变成生成函数
yield from Iterator 解决下面的yield嵌套问题(生成器函数嵌套)
生成器： （生成可迭代的数据）
	yield、 next
协程：  （数据的消费者）  -- 后续
	yield、next、send （传递参数复制给 yield arg）

def f():

	def do_yield(n):
		yield n x=0
	
	while True: x+=1
		do_yield(x)
		

def f():

	def do_yield(n):
		yield n x=0
	
	while True: x+=1
		yield from do_yield(x)
```

### 分支 - else

```python
复合语句控制范围（主块、子块else）: return 会跳出
if/else
	pass
for/else   # 迭代器控制
	仅当for循环运行完毕（没有被break语句中止）才运行else块
  eg.
  	for item in my_list:
      # code block
    else:
      # code block
    # code block
while/else
	仅当while循环因False退出（没有被break语句中止）才运行else块
  eg.
  	while(trigger):
      # code block
    else:
      # code block 
    # code block
try/else
  仅当try块中没有异常抛出才运行else，且else中抛出的异常不会由前面的except子句处理
  eg.
  	try:
      # code block
    except Exception:
      # code block
    else:
      # code block
    finally:
      # code block


```

### 上下文 - [with, for, while, try]

```python
with语句会设置一个临时上下文，交由上下文管理器对象控制，并负责清理上下文
# 上下文管理器协议
		__enter__、__exit__  => 上下文管理器对象
  	__enter__ 返回上下文中的操作对象 或 None

## 反向输出上下文
	class LookingGlass:
    	def __enter__(self):
        import sys
        self.original_write = sys.stdout.write
        sys.stdout.write = self.reverse_write
        return "result of with ConteManager()"   # with ConteManager() as enter_result:
	
  		def reversed_write(self, text):
      	return self.original_write(text[::-1])
      
      def __exit__(self, exc_type, exc_value, traceback): # Acceptable return value is None/True
        """
        exc_type: 错误类型
        exc_value: 错误实例， 构造参数获取 exc_value.args
        tracebak: traceback对象
        """
        import sys
        sys.stdout.write = self.original_write
        if exc_type is ZeroDivisionError:
          # handle exc
          return True
        # 如果返回的值不是True，则会向上抛出错误； True表示异常已经正确处理； None表示没有异常

	>>> from mirror import LookingGlass 
	>>> with LookingGlass() as what:
  			print('Alice, Kitty and Snowdrop')
				print(what)
			pordwonS dna yttiK ,ecilA 
      YKCOWREBBAJ
  >>> manager = LookingGlass()
  >>> manager
  		<__main__.LookingGlass object at 0x10fbe6d90>   # 未进入逆序上下文
  >>> manager_enter = manager.__enter__()
  >>> manager_enter
  		')(reganaMetnoC htiw fo tluser'
  >>> manager
			>0a95fe301x0 ta tcejbo ssalGgnikooL.__niam__<
  >>> manager.__exit__(None, None, None)
  >>> manager_enter
  		'result of with ConteManager()'
```

```python
# contextlib 上下文模块包
		closing
  	suppress
    @contextmanager
    ContextDecortor
    ExitStack
## @contextmanager
		把简单的生成器函数变成上下文管理器 -> 协程特性
  	def generator():
    	# code block
      # run in __enter__; which means with
      yield value  #  result of __enter__
      # code block of with
      # code block
      # run in __exit__
    
    """
    封装__enter__: 调用生成器函数并保存生成器对象-gen、next(gen)、返回yield值
    封装__exit__: 检查有没有把异常传给 exc_type, 如果有则调用 gen.throw(exception), 在生成函数yield哪一行抛出异常
    						 否则调用 next(gen)，继续执行yield之后的语句 =>. **优化**： 捕获处理yield代码行的错误，并实现finally逻辑
    异常抛出：自实现的__exit__函数只有在为True或者None时才不会抛出异常； contextmanager相反。认为yield之后的代码将所有异常
    				 都处理了，所有会压制异常； 只能显示的抛出异常才不会被压制
    """
    
    @contextmanager
    def looking_glass():
      	import sys
        original_write = sys.stdout.write
        
        def reversed_write(text):
      		return original_write(text[::-1])
        
        sys.stdout.write = reversed_write   # __enter__
        # 无异常捕获
        # yield "result of with ConteManager()"
        # sys.stdout.write = original_write   # __exit__
        
        # 异常捕获
        msg = ""
        try:
          yield "result of with ConteManager()"
        except ZeroDivisionError:
          msg = "blabla"
        finally:
          sys.stdout.write = original_write
          if msg:
            print(msg)
        
     >>> with looking_glass() as res:
      			print("ABC")
        		print("res")
     >>> 
    		 'CBA'
	       ')(reganaMetnoC htiw fo tluser'
# 第三方
	同时读写； 原地重写文件 # F函数
	inplace(file_name, "mode", newline="") -> (句柄infh, 句柄outfh)
  
  import csv
	with inplace(csvfilename, 'r', newline='') as (infh, outfh): 
    reader = csv.reader(infh)
		writer = csv.writer(outfh)
    
		for row in reader:
		row += ['new', 'columns'] writer.writerow(row)

```

### 协程 Coroutines

```python
yield: 产出、 让步；流程控制工具 (不)产出/接受 数据
- 生成器
  yield item    值，产出一个值提供给next(...), 该作用域代码暂停执行
- 协程    asyncio包的基础
	data = yield   表达式，调用方使用 .send(datum) 传值
  data = yield data    传/接值
```

```python
# 生成器 --> 协程
## 最简单的协程例子 - 表达式生成器
  def simple_coroutines():
       print("-> coroutines started")
       x = yield   # 表达式，隐式的产出None
       print("-> coroutines received", x)
  >>> my_coro = simple_coroutines()    # 调用生成器函数获得生成器对象
  >>> my_coro
  <generator object simple_coroutines at 0x7fa2a8014970>
  >>> next(my_coro)   # 启动生成器
  -> coroutines started    # 等待调用方传入一个值
  >>> my_coro.send(42)
  -> coroutines received 42
  Traceback (most recent call last):
    File "<stdin>", line 1, in <module>
  StopIteration      # 执行到生成器对象的末尾，抛出StopIteration
## 协程的状态  inspect.getgeneratorstate(my_coro)
	GEN_CREATEED       等待开始执行       		 ----- 必须先激活协程（预激）， next() 或者 my_coro.send(None)，执行到第一个yield表达式
  GEN_RUNNING			   解释器正在执行
  GEN_SUSPENDED			 在yield表达式处暂停   	----- send 传值有效时间
  GEN_CLOSED				 执行结束
## 多值协程    --每一次yield语句都会交出解释器权限
	def simple_coro2(a):
     print("-> Started: a = ", a)
     b = yield a  # 产出a的同时接收调用者传值作为b的值
     print("-> Received: b = ", b)
     c = yield a + b
     print("-> Received: c = ", c
## 计算平均值
  def averager():
       total = 0.0
       count = 0
       averager = None
       while True:  # 调用gen.close() 或者被垃圾回收
          term = yield average
          total += term
          count += 1
          average = total/count
## 预激协程的装饰器
  不预激协程，则协程不会启动
  from functools import wraps
  def coroutin(func):
     @wraps(func)
     def premer(*args, **kwargs):
        gen = func(*args, **kwargs)
        next(gen)
        return gen
     return premer
  yield from 不会预激协程，和 asyncio.coroutine 兼容
## 终止协程 和 异常处理
  协程内的异常会上抛给 next 或者 促发协程的对象；如果没有处理异常，协程会终止
  	未处理的普通异常 = 协程终止，上抛异常
  	GeneratorExit = 协程终止
  1. 传递哨符触发
  2. gen.close()    传递 GeneratorExit 异常，此时生成器一定不能产生值（解释器限制）
  3. gen.throw(exc_type[, exc_value[, traceback]])  显示的把异常发给协程
 	优化方式：
        协程定义体中相关代码放入 try/finally ; 选择性的 except/else
## 协程使用 return 返回值
  协程终止是抛出StopIteration
  返回值作为 exc.value 返回； StopIteration 的第一个参数
  yield from Generator  处理StopIteration 并把 Generator的return值赋给 yield from表达式左边的变量
  
  def averager():
       total = 0.0
       count = 0
       averager = None
       while True:  # 调用gen.close() 或者被垃圾回收
          term = yield average
          if term is None:
           	break
          total += term
          count += 1
          average = total/count
       return "Break While"
  >>> coro_avg = averager()
  >>> next(coro_avg)
  >>> try:
  ...			coro_avg.send(None)
  ... except StopIteration as exc:
  ... 		result = exc.valu. # result = "Break While"
      
## yield from  <=>  await
   eg -----------------
   def flatten(items, ignore_types=(str, bytes)):  # 委派生成器/子生成器
    	for x in items:
        if isinstance(x, Iterable) and not isinstance(x, ignore_types):
            yield from flatten(x)  # 子生成器
        else:
            yield x
   # Produces 1 2 3 4 5 6 7 8
	 for x in flatten(items):
    	print(x)
   eg -------------------
   
   子生成器一定要能终止
   yield from x 流程：
           1. iter(x)  # 获取迭代器， for 循环
           2. 协程嵌套， 透传 （管道，委派生成器阻塞时只作为调用方和子生成器之间的通道）
   yield from 协程链的调用：
           1. next()、send()
           2. 隐式 for 循环
   ### group averager
      def averager(): total = 0.0
          count = 0 average = None while True:
          term = yield
          if term is None:
          break
                  total += term
                  count += 1
                  average = total/count
          return Result(count, average)
      
      # the delegating generator
      def grouper(results, key): while True:
          results[key] = yield from averager()   # 委派生成器暂停在 yield from； 之后再赋值
```

```python
# 使用协程做离散事件仿真
	离散事件仿真(Discrete Event Simulation - DES)是一种吧系统建模成一系列事件的仿真类型。
  离散仿真的时间钟向前推进的量不是固定的，协程抽象 - 回合制触发
  连续仿真则是按固定的量推进，多线/进程抽象 - 流式发展
## 单个线程管理多个并发活动
	### 多事件协程
	Event = collections.namedtuple("Event", "time proc action")
  def taxi_process(ident, trips, start_time):  # 计程车事件生成器
      time = yield Event(start_time, ident, "leave garage")
      for i in range(trips):
            time = yield Event(time, ident, "pick up passenger")
             time = yield Event(time, ident, "drop off passenger")
      yield Event(time, ident, "go home")
  
  >>> taxi = taxi_process(12, 2, 0)
  >>> next(taxi)
  Event(time=0, proc=12, action='leave garage')
  >>> taxi.send(_.time + 7)    # 命令交互中 _ 为最近产生的匿名变量； 这里为最新的Event()
  Event(time=7, proc=12, action='pick up passenger')
  >>> taxi.send(_.time + 23)
  Event(time=30, proc=12, action='drop off passenger')
  >>> taxi.send(_.time + 5)
  Event(time=35, proc=12, action='pick up passenger')
  >>> taxi.send(_.time + 48)
  Event(time=83, proc=12, action='drop off passenger')
  >>> taxi.send(_.time + 1)
  Event(time=84, proc=12, action='go home')
  >>> taxi.send(_.time + 10)
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    StopIteration
  
  ### 单驱动主程序
  
  taxis = {
    0: taxi_process(ident=0, trips=2, start_time=0),
    1: taxi_process(ident=1, trips=4, start_time=5),
    2: taxi_process(ident=2, trips=6, start_time=10)
  }
  
  class Simulator:
     def __init__(self, procs_map):
        self.events = queue.PriorityQueue()
        self.procs = dict(procs_map)
     def run(self, end_time):
      	"""排定并显示事件，直到时间结束"""
        
        # 预激事件
        for _, proc in sorted(self.procs.items()):
          	first_event = next(proc)
            self.events.put(first_event)
        
        # 仿真系统主循环
        sim_time = 0
        while sim_time < end_time:
          if self.events.empty():
            print("*** end of events ***")
            break
          current_event = self.events.get()
          sim_time, proc_id, previous_action = current_event
          print("taxi:", proc_id, proc_id * "  ", current_event)
          active_proc = self.procs[proc_id]
          next_time = sim_time + compute_duration(previous_action)
          try:
            next_event = active_proc.send(next_time)
          except StopIteration:
            del self.procs[proc_id]
          else:
            self.events.put(next_event)
        else:
          """非break， 为while条件不满足之后的逻辑"""
          msg = "*** end of simulation time: {} events pending ***"
          print(msg.format(self.events.qsize()))
```

### future处理并发

> concurrent.futures - 并行计算
> GIL (Global Interpreter Lock 全局解释器锁) 对I/O密集型处理几乎没有影响
> 不应该自己管理线程和锁，而应该管理内存分配和释放

```python
## 进度   >>>>>> tqdm包实现动态进度条
	def show(text):
    print(txt, end="")
    sys.stdout.flush()
    # 刷新sys.stdout，能在一行中连续输出，实现进度条
## 保存 
	def save_flag(img, filename):
    path = os.path.join(DEST_DIR, filename)
    with open(path, "wb") as fp:
      fp.write(img)
## 获取
	def get_flag(cc):
    url = ""
    resp = requests.get(url)
    return resp.content
## 主程序
	def main(download_func):
    count = download_func(cc_list)
    
```

```python
# future 对象
	concurrent.futures模块的主要特色是 
  				ThreadPoolExecutor - threading库封装 : 线程池
    			ProcessPoolExecutor - multiprocessing库封装 : 进程池
        	要执行的任务队列
## futures.ThreadPoolExecutor
	from concurrent import futures
  
  MAX_WORKERS = 20
  
  def download_one(country_code):
    image = get_flag(country_code)
    show(country_code)
    save_img(image, f"{country_code.lower()}.gif")
    return country_code
  
  def download_many(cc_list):
    worker_num = min(MAX_WORKERS, len(cc_list))
    with futures.ThreadPoolExecutor(worker_num) as excutor:  # 创建多线程
      res = executor.map(download_one, sorted(cc_list)) 
      # executor返回Future， 迭代器的__next__ 会调用个个Future的result方法
      # futures.as_completed(List[executor.submit()])
    return len(list(res))
## Future类
	concurrent.futures.Future
  asyncio.Future
  都表示可能已经完成或者尚未完成的计算； 等价于 Teisted-Deferred、Tornado-Future、JS-Promise
  
  method:
    	done() -> bool.   指明Future链接的可调用对象是否已经执行
      add_done_callback(callable)    Future运行结束之后调用指定的可调用对象
      result() -> callable()     
      			Future运行结束之后调用，会返回可调用对象的结果 或 调用时抛出的异常
        		Future没有运行结束时调用，con.Future 调用会阻塞调用方的线程，直到有反馈(结果 或 异常)，可以设置											超时时间参数(timeout)，超时抛出TimeoutError； asyncio.Future 不能设置超时时间
## futures.as_completed函数 替代 抽象的 executor.map
	"""
	futures.as_completed(List[Future]) -> Generator(Future)
	接受Future列表，在Future运行结束之后产出Future
	"""
	def download_many(cc_list):
    cc_list = cc_list[:5]
    with futures.ThreadPoolExecutor(max_workers=3) as executor:
      	to_do = []
        for cc in sorted(cc_list):
          	future = executor.submit(download_one, cc)  # 提交可调用对象和参数获得对应的Future对象
            to_do.append(future)
            msg = "Scheduled for {}: {}"
            print(msg.format(cc, future))
            
        results = []
        for future in futures.as_completed(to_do):  # Future结束之后被产出
          	res = future.result()  # 获取Future的对象，此时不会产生阻塞。as_completed
          	msg = "{} result: {!r}"
          	print(msg.format(future, res))
          	results.append(res)
        
    return len(results)    

## GIL
	CPython解释器本身就不是线程安全的，CPython实现的内存管理不是线程安全的，因此有了全局解释器锁，一次只允许一个线程执行python字节码。故一个python进程通常不能同时使用多个CPU核心。
  Python标准库中的所有阻塞型I/O函数都会释放GIL，允许其他线程运行，time.sleep() 也会释放
  支持线程多核并行是有代价的，就是单个线程效率的下降。更多细粒度的锁获取/释放动作；Python则选择了只有一个全局锁

## CPU计算密集型
	通过concurretn.futures模块绕过GIL - 启动多进程 futures.ProcessPoolExecutor
  推荐使用PyPy（RPython）、JPython（JVM）
## Python实现
	确保语言执行的全流程，包含编译/解释、执行
  > 编译-compile：将一种代码转换（transform）为另一种代码的过程
  > 解释执行-Interpreter: 虚拟机运行时负责执行代码，比如JVM(JPython)和PVM(CPython)能看懂的 字节码（byte code）. 与编译执行的区别在 每次解释执行前需要重新读取字节码，以适应动态语言的变化。
  > 编译执行：区别于解释执行，编译执行把代码先编译为CPU可以直接运行的代码执行
  （Python是一门编程语言规范，C/R/JPython是其实现）
## GC垃圾回收-释放内存
		>>> 分配内存给新对象、识别垃圾对象、回收内存
	CPython
  	1. 引用计数 Refrence Counting
    		everything is object每一个对象的核心就是一个结构体PyObject，它的内部有一个引用计数器（ob_refcnt）
      	typedef struct_object {
         int ob_refcnt;
         struct_typeobject *ob_type;
        } PyObject;
        sys.getrefcount(a)   # 获取某对象的引用计数
        情况： +1/-1
        		创建/销毁
          	引用/引用变更
            参数传递/作用域失效
            容器存储/删除
       >>> 无法处理容器对象（列表、字典、用户自定义类的对象、元组等）的循环引用，Python的垃圾回收机制很大一部分					 是为了处理循环引用而延伸 -> 优化
    2. 标记-清除 (Mark and Sweep) 算法  # 不考虑简单类型以及只包含简单类型的元组，内存碎片问题 -> 复制算法 
    		使用副本： gc_ref, 因为当产生循环引用时 ob_refcnt不会为0，所以需要主动减少副本gc_ref来摘环判断
      	摘环 -> 验证 -> 清除
    		需要容器维护两个额外的指针，分别指向前后两个容器双端链表，引用计数的链式减少 - 追踪回收（tracing GC）
      	解释器维护两个额外的对象链表：root object（有向图，根结点为全局变量/调用栈/寄存器）、unreachable
        													需要扫描的																				临时不可达
        A）标记检测垃圾阶段，遍历所有的对象，如果是可达的（reachable），也就是还有对象引用它，那么就为可达；
        	 第一次标记：环摘除，被引用对象的gc_ref追踪减少，划分出临时不可达的子集
        	 第二次标记：不可达对象的救赎，当root_object中存在对不可达子集中对象引用时，则该不可达对象恢复为可达
        B）清除阶段，再次遍历对象，如果发现某个对象没有标记为可达，则就将其回收
        可达的判断标准：gc_ref 是否为0，gc_ref的初始值是ob_refcnt的副本
        垃圾回收的阶段，会**暂停**整个应用程序，等待标记清除结束后才会恢复应用程序的运行
       >>> 清除非活动的对象前必须顺序扫描整个堆内存，回收效率低，应用程序暂停问题
    3. 分代回收 - 空间换时间、分代扫描回收取代全局扫描
    		"""基于统计事实：对于程序，存在一定比例的内存块的生存周期比较短；而剩下的内存块，生存周期会比较长，甚至会从程序开始一直持续到程序结束。生存期较短对象的比例通常在 80%～90% 之间，这种思想简单点说就是：对象存在时间越长，越可能不是垃圾，应该越少去收集。这样在执行标记-清除算法时可以有效减小遍历的对象数，从而提高垃圾回收的效率"""
      	定义三种世代(0,1,2)，初始为0，每过一轮GC回收则加1代。世代的扫描，基于新分配的对象减释放对象的值与每代的阈值做比较，大于则触发
  
  with futures.ProcessPoolExecutor() as excutor:
    	# worker_num是可选的参数
      # 默认值为 os.cpu_count() 返回的CPU核心数
			pass

## Executor.map 方法
	 executor.map 返回的结果顺序和调用callable顺序一样，会阻塞。当第一个需要10s，其余只需要1s；则共需要10s才能获取到数据
   保证顺序更好的方式：executor.submit(Callable, arg) + futures.as_completed(List[Future])
```

#### asyncio包处理并发 - Tulip项目

> 线程/进程 -> 异步
> Concurrency is not Parallelism (It's better)
> 使用事件循环驱动的协程实现并发
> 基于调用方驱动，定义使用 yield from 的协程

```python
# spin character
import threading
import itertools
import time
import sys


class Single:
    go = True

# 退格符覆盖输出
def spin(msg, signal: Single):
    write, flush = sys.stdout.write, sys.stdout.flush
    for char in itertools.cycle("|/-\\"):
        status = char + " " + msg
        write(status)
        flush()
        write("\x08" * len(status))  # \x08 退格符
        time.sleep(1)  # sleep会释放GIL
        if not signal.go:  # 线程关闭的信号，python没有提供关闭线程API
            break

    write(" " * len(status) + "\x08" * len(status))


def slow_function():
    time.sleep(3)
    return 42


def supervisor():
    signal = Single()
    spinner = threading.Thread(target=spin, args=("thinking", signal))
    print("spinner object:", spinner)
    spinner.start()
    result = slow_function()
    signal.go = False
    spinner.join()
    return result


def main():
    result = supervisor()
    print("Answer:", result)


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    main()
```



```python
def main():
    loop = asyncio.get_event_loop()
    result = loop.run_until_complete(supervisor())
    loop.close()
```

### 并发编程

#### 创建多线程

```python

threading.Thread(target=func, args=(a,))
multiprocessing.Process(target=func, args=(a,))
实例方法：
	start()	
# 直接实例化
	thread_ins = threading.Thread(target=func, args=(a,))
  thread.start()
# 覆写类 （init、run）, 再实例化
class MyThread(Thread):
  def __init__(self, *args):  # 收集参数
    super().__init__()
    self.args = args
  
  def run(self):  # 执行逻辑
    # self.args
    target(*self.args)
# 实例方法
	start()  # 启动
  join()  # 阻塞子程，待其执行结束之后再往下执行
  is_alive()/isAlive()
# 实例属性
  daemon = True/False # 子程是否随主程的退出二退出
  name = ""  # 子程名
```

#### 创建线程池

> 使用多线程处理任务时也不是线程越多越好，由于在切换线程的时候，需要切换上下文环境，依然会造成cpu的大量开销。为解决这个问题，线程池的概念被提出来了。预先创建好一个较为优化的数量的线程，让过来的任务立刻能够使用，就形成了线程池

```python
# 第三方 concurrent.futures 模块
	1. ThreadPoolExecutor
	2. ProcessPoolExecutor
  pool = ThreadPoolExecutor(5) 
  for i in range(100):
	 	 	pool.submit(target)  
```



#### 线程的锁机制

```python
lock = threading.Lock/RLock
lock.require()
lock.release()
# require/release必须成对出现，防止死锁  -> 上下文管理器
# 死锁：对资源的不合理竞争导致
with lock:
  pass
# 作用
	1. 顺序执行
  2. 资源访问控制

# 可重入锁RLock/嵌套锁 - 解决统一线程多次获取同一锁
	区别仅在于同一线程可以多次获取该锁

# 防死锁辅助排序函数
import threading
from contextlib import contextmanager

_local = threading.local()

@contextmanager
def acquire(*locks):
    # Sort locks by object identifier
    locks = sorted(locks, key=lambda x: id(x))

    # Make sure lock order of previously acquired locks is not violated
    acquired = getattr(_local,'acquired',[])
    if acquired and max(id(lock) for lock in acquired) >= id(locks[0]):
        raise RuntimeError('Lock Order Violation')

    # Acquire all of the locks
    acquired.extend(locks)
    _local.acquired = acquired

    try:
        for lock in locks:
            lock.acquire()
        yield
    finally:
        # Release locks in reverse order of acquisition
        for lock in reversed(locks):
            lock.release()
        del acquired[-len(locks):]
# GIL(Global Interpreter Lock) 全局解释器锁
	并不是Python的特性。是在实现Python解析器(CPython)时所引入的一个概念。而Python解释器，并不是只有CPython，除它之外，还有PyPy，Psyco，JPython，IronPython。通常认为Python = CPython，所以说python线程的独占锁
```

#### 线程间的消息通信机制/线程执行控制

```python
# threading.Event
  event = threading.Event()  # 将Event传如线程实例，并调用 wait/set
  event.clear()  # 清除Event的状态，所有依赖于该Event的线程都会阻塞
  event.wait()  # 线程依赖的event执行该函数，即表明需要等待该Event的set()触发之后才能执行
  event.set()  # Event状态设置就绪，会触发所有等待该Event的线程

# threading.Condition
  cond = threading.Condition()
  cond.acquire()  # 可以多个同时获取，但是notify/wait进行控制，阻塞自己wait， 触发其他线程执行notify
  cond.release()
  cond.wait()  # 阻塞等待
  cond.notify()  # 触发释放阻塞
# queue 线程安全的队列模块
	>>> queue.Queue 先进先出、queue.LifoQueue 后进先出、queue.PriorityQueue 优先级
  # PriorityQueue -> (value, priority)  1>2>3>4 ASC
	q = Queue(maxsize=10)
  q.get() # 阻塞式，获取队列消息
  q.get(timeout=5.0)  # 等待超时获取，超时未获取到会抛出超时错误
  q.put() # 添加消息至队列
  q.join() # 等待所有消息都被消费/获取完
	-- 不常用
  q.qsize() # 当前队列消息个数
  q.empty() # 是否为空
  q.full() # 是否已满
```

#### 线程域变量隔离

```python
各个线程之间的变量不共享，主/子线程、同级线程之间都有各自的threading.local()存储变量
# threading.local() 类
	保存各个作用域的变量
  默认为当前线程域的变量
# eg
import threading
from functools import partial
from socket import socket, AF_INET, SOCK_STREAM

class LazyConnection:
    def __init__(self, address, family=AF_INET, type=SOCK_STREAM):
        self.address = address
        self.family = AF_INET
        self.type = SOCK_STREAM
        self.local = threading.local()  # 每个线程的local是不一样的

    def __enter__(self):
        if hasattr(self.local, 'sock'):
            raise RuntimeError('Already connected')
        # 把socket连接存入local中
        self.local.sock = socket(self.family, self.type)
        self.local.sock.connect(self.address)
        return self.local.sock

    def __exit__(self, exc_ty, exc_val, tb):
        self.local.sock.close()
        del self.local.sock

def spider(conn, website):
    with conn as s:
        header = 'GET / HTTP/1.1\r\nHost: {}\r\nConnection: close\r\n\r\n'.format(website)
        s.send(header.encode("utf-8"))
        resp = b''.join(iter(partial(s.recv, 100000), b''))
    print('Got {} bytes'.format(len(resp)))

if __name__ == '__main__':
    # 建立一个TCP连接
    conn = LazyConnection(('www.sina.com.cn', 80))

    # 爬取两个页面
    t1 = threading.Thread(target=spider, args=(conn,"news.sina.com.cn"))
    t2 = threading.Thread(target=spider, args=(conn,"blog.sina.com.cn"))
    t1.start()
    t2.start()
    t1.join()
    t2.join()
```

#### 生成器 -> 协程

```python
from collections.abc import Iterable, Iterator, Generator
1. 可迭代对象：实现了 __iter__ 或 __getitem__ 参数0开始的整数索引    #  __iter__ 返回迭代器； 不能实现 __next__，因为需要单独的迭代器来获取元素
2. 迭代器：取出元素； 生成器：生成元素； it = iter(iterable)；next(it)、StopIteration   #  __iter__ 返回self迭代器本身、__next__每次返回一个值直到raise StopIteration
  	迭代器接口：__iter__、__next__   # (单向单次，无元素时抛出异常，无法还原) for、with等上下文关键字会处理StopIteration
3. 生成器 yield  ( 属于 迭代器 ) yield 替换 __next__的return 或 列表生成式
		next(gen)   # 不传入参数
  	gen.send(arg)  # 传入参数。gen.send(None) 等价于 next(gen)
    状态：   # from inspect import getgeneratorstate
    	GEN_CREATED # 等待开始执行
      GEN_RUNNING # 解释器正在执行（只有在多线程应用中才能看到这个状态）
      GEN_SUSPENDED # 在yield表达式处暂停
      GEN_CLOSED  # 执行结束
```

#### yield from

```python
yield from Iterable # Contains Iterable > Iterator > Generator
1. 应用
	1.1 拼接可迭代对象（基于嵌套拆分）
  1.2 生成器嵌套
  	调用方、委托生成器-双向通道、子生成器
    arg = yield from sub_gen()  # 是将sub_gen的return值拦截赋值，对yield返回的值只能透传
  1.3 处理异常（对异常的容错处理、传递）
```

#### asyncio

```python
协程Coroutine：
	可内部中断子程序，主动交出CPU控制权（子程序调用栈）
  任何时候只有一个协程在运行，与多线程比避免了线程创建/切换的消耗，不需要多线程的锁机制（避免了CPython的GIL）
Coroutin的实例检测方法
@classmethod
def __subclasshook__(cls, C):
  if cls is Coroutine:
    return _check_methods(C, '__await__', 'send', 'throw', 'close')
  return NotImplemented
# 相关概念
	1. event_loop 事件循环：程序开启一个无限的循环，程序员会把一些函数（协程）注册到事件循环上。当满足事件发生的时候，调用相应的协程函数。 >>> 驱动协程作用
  		loop.run_xx 都是阻塞的，run_until_complete/run_forevers; 所以同一个线程里面只会有一个event_loop在run，主线程一般只会有一个event_loop，除非手动set
    	工作： 等待触发/调用之前注册进来的处理代码
      事件、事件处理者、事件循环监控调度
      stop: 停止； close：关闭，pending状态的回调会被丢弃，清除所有的队列并关闭执行器，不会等待
	2. coroutine 协程：协程对象，指一个使用async关键字定义的函数，它的调用不会立即执行函数，而是会返回一个协程对象。协程对象需要注册到事件循环，由事件循环调用。
	3. future 对象： 代表将来执行或没有执行的任务的结果。它和task上没有本质的区别
	4. task 任务：一个协程对象就是一个原生可以挂起的函数，任务则是对协程进一步封装，其中包含任务的各种状态。Task 对象是 Future 的子类，它将 coroutine 和 Future 联系在一起，将 coroutine 封装成一个 Future 对象。
	4. async/await 关键字：python3.5 用于定义协程的关键字，async定义一个协程，await用于挂起阻塞的异步调用接口。其作用在一定程度上类似于yield，二者不兼容
  		await 后面必须要接 future对象/协程对象
  		yield from 后面可接 **可迭代对象**，也可接future对象/协程对象； 更底层更通用
# 单任务完整工作流程
	1. 定义/创建协程对象
  		async关键字
    	@asyncio.coroutine 装饰生成器函数，本质仍然是生成器Generator
	2. 将协程转为task任务
	3. 定义事件循环对象容器
	4. 将task任务注册进事件循环对象中（单任务直接注册/多任务封装注册）
  import asyncio
  
  async def hello(name):  # 定义协程
    print("Hello, ", name)
    return "Sayed Hello"
  
  coroutine = hello("AsyncIO")  # 创建协程
  loop = asyncio.get_event_loop()  # 定义事件循环对象容器, asyncio.events.get_evrnt_loop()
  task = loop.create_task(coroutine)  # 协程转化外task任务， 是Future对象的子类
  # task = asyncio.ensure_future(coroutine)  # Future对象
  loop.run_until_complete(task)  # 将task任务注册进事件循环对象中
# 单任务结果回调
	1. 直接获取Task的结果, Task是Future的子类
  	 task.result()  # Sayed Hello
  2. Future作为回调函数参数
  		def callback(future: Future):
      		print("Result: ", future.result())
  	
			task.add_done_callback(callback) # 添加回调函数
    	loop.run_until_complete(task) 
# 多任务协程的并发 - 协程间切换
  coroutine1 = hello(1)
  coroutine2 = hello(2)
  coroutine3 = hello(3)
  
  tasks = [
    asyncio.ensure_future(coroutine1),
    asyncio.ensure_future(coroutine2),
    asyncio.ensure_future(coroutine3),
  ]
  
  loop = asyncio.get_event_loop()  # 定义事件循环对象容器，当前线程。一般创建新线程和新event_loop对象，并在该线程下fun_forever()
  """
  t = Thread(target=lambda loop: asyncio.set_event_loop(loop); loop.run_forever(), args=(asyncio.new_event_loop, ))
  t.setDaemon(True)
  t.start()
  """
  
  loop.run_until_complete(asyncio.wait(tasks))  # await封装， 
  # dones, pendings = await asyncio.wait(tasks)  返回的是Task集合
  loop.run_until_complete(asyncio.gather(*tasks)  # gather封装
  # results = await asyncio.gather(*tasks)  直接返回结果
  
# 多任务协程的嵌套
   async def func():
       # ....
			 await coro()
			 return
   loop.run_until_complete(asyncio.wait(tasks))  # 嵌套
# 多任务协程的状态 - Future/Task的状态
		1.Pending：创建future，还未执行
		2.Running：事件循环正在调用执行任务
		3.Finished：任务执行完毕
		4.Cancelling：Task被取消后的状态
# gather 与 await
  asyncio.await(fs, *, loop=None, timeout=None, return_when=ALL_COMPLETED):
     接收参数 
             fs:   List[Future|Coroutine]   # asyncio.ensure_future(coroutine)
             return_when:  控制返回时间 
                           FIRST_COMPLETED ：第一个任务完全返回，
                           FIRST_EXCEPTION：产生第一个异常返回，
                           ALL_COMPLETED：所有任务完成返回 （默认选项）
     返回结果 Set[Futures]， 需要future.result()手动采集结果；超时的时候未完成的返回到pending set中
             dones, pendings = await asyncio.wait(tasks)
  asyncio.gather:
   	 接收参数 *coros_or_futures  多个可变长参数
     返回结果 List[result] 结果列表
```

#### ayncio简单应用

```python
import time
import asyncio
from queue import Queue
from threading import Thread


def start_loop(loop):
  	# 定义一个后台永远运行的event_loop对象
    asyncio.set_event_loop(loop)
    loop.run_forever()


async def do_sleep(x, q, msg=""):
  	# 协程
    await asyncio.sleep(x)
    q.put(msg)

queue = Queue()

# 创建一个新的event_loop对象
new_loop = asyncio.new_event_loop()

t = Thread(target=start_loop, args=(new_loop,))  # 将线程和新建的event_loop对象关联
t.start()

print(time.ctime())

## 主线程异步注册 6s
asyncio.run_coroutine_threadsafe(do_sleep(6, queue, "第一个"), new_loop)
asyncio.run_coroutine_threadsafe(do_sleep(3, queue, "第二个"), new_loop)

## 主线程同步注册 9s
### new_loop.call_soon_threadsafe(do_sleep, 6, queue, "第一个")
### new_loop.call_soon_threadsafe(do_sleep, 3, queue, "第二个")

while True:
    msg = queue.get()
    print("{}协程运行完...".format(msg))
    print(time.ctime())


################
# 简易redis异步任务框架
import time
import redis
import asyncio
from queue import Queue
from threading import Thread

def start_loop(loop):
    # 设置一个永久运行的event_loop
    asyncio.set_event_loop(loop)
    loop.run_forever()

async def do_sleep(x, rcon):
  	# 异步任务函数
    await asyncio.sleep(x)
    rcon.lpush("result", f"param: {x} Finished...")

def get_redis():
    connection_pool = redis.ConnectionPool(host="127.0.0.1", db=0)
    return redis.Redis(connection_pool=connection_pool)

def consumer(rcon, loop):
    while True:
      	# 监听redis任务信息
        task = rcon.rpop("time_param")
        if not task:
            time.sleep(1)
            continue
        asyncio.run_coroutine_threadsafe(do_sleep(int(task), rcon), loop)

if __name__ == "__main__":
    print(time.ctime())
    new_loop = asyncio.new_event_loop()

     # 创建redis连接
    rcon = get_redis()
    
    # 定义一个线程，运行一个事件循环对象，用于实时接收新任务
    loop_thread = Thread(target=start_loop, args=(new_loop,))
    loop_thread.setDaemon(True)
    loop_thread.start()

    # 子线程：用于消费队列消息，并实时往事件对象容器中添加新任务
    consumer_thread = Thread(target=consumer, args=(rcon, new_loop))
    consumer_thread.setDaemon(True)
    consumer_thread.start()
    # 可以多创建几个消费者线程
    consumer_thread2 = Thread(target=consumer, args=(rcon, new_loop))
    consumer_thread2.setDaemon(True)
    consumer_thread2.start()

    while True:
        msg = rcon.rpop("result")
        if msg:
            print(msg)
            print("当前时间：", time.ctime())

```

## Metaprogramming

```python
属性（attribute）：数据和处理数据的方法
特性（property）：属性化的方法
python提供动态属性的接口（__getattr__、__setattr__），属于元编程
# 类的构造方法 new -> 初始化方法 init， init接收new创建的实例对象然后初始化
# __new__方法是经过特殊处理的类方法，不需要@classmethod装饰器，覆写的时候需要注意
def object_maker(the_class, some_arg): 
  new_object = the_class.__new__(some_arg)   # __new__(cls, *args, **kwargs)
  if isinstance(new_object, the_class):
		the_class.__init__(new_object, some_arg) 
  return new_object
##  the following statements are roughly equivalent
x = Foo('bar')   # ins = super.__new__(cls) 创建实例对象然后调用 __init__(ins, )
x = object_maker(Foo, 'bar')

# 数据属性 转换成 特性  - 只有新式类支持特性，python3中所有的类都是继承自新式类 object
# 基于描述符
## Property特性都是类属性，但是管理的是实例属性 - 对象级的只读属性实现
## 覆盖关系：类特性 > 实例属性 > 类属性； 新添加的同名类property会覆盖obj的同名属性
## cls.pro获取到的是property， obj.pro 是获取到property的读值方法
==> 即obj.attr 寻找顺序： obj.__class__ -> obj.__dict__

property(fget=None, fset=None, fdel=None, doc=None)   
# Property类的构造方法; 同逻辑可重用的取/获值函数时，使用构造函数

@property
def pro_name(self):
  return self.__pro_name

@pro_name.setter
def pro_name(self, value):
  self.__pro_name = value

@pro_name.deleter    # del obj.pro_name

# 函数 和 类 通常可以互换  -函数调用和对象实例化一致
特性工厂函数： 高阶函数
>>> weight = property(get_attr_a, set_value_gt_0)
>>> price = property(get_attr_b, set_value_gt_0)
def quantity(storage_name):
  def qty_getter(instance):
    return instance.__dict__[storage_name]
  
  def qty_setter(instance, value):
    if value > 0:
      instance.__dict__[storage_name] = value
    else:
      raise ValueError("value must be > 0")
  return property(qty_getter, qty_setter)

class LineItem:
  weight = quantity("weight")
  price = quantity("price")
  
  def __init__(self, weight, price):
    self.weight = weight  # 已经触发了特性的读/设值
    self.price = price

  
```

### 属性描述符

> 描述符是对多个属性运用相同存取逻辑的一种方式， 例如 Django ORM 和 SQL Alchemy 等 ORM 中的字段类型
>
> 描述符
> 	是实现特定协议的类（单独、辅助类），包括 __get__、__set__、__delete__等； property完整的实现了描述符协议
> 	用法：创建一个实例，作为另一个类的类属性

```python

# 覆盖型描述符
# 验证属性
	quantity高阶特性工厂函数 ->  Quantity描述符
# 组成部分
	1. 描述符类 - Quantity
  2. 托管类 - LineItem
  3. 描述符实例 - 有限个
  4. 托管实例 - 无限个
  5. 储存属性 - LineItem实例的实例属性，存储在各自托管实例
  6. 托管属性 - LineItem的公开类属性 且 由描述符实例处理
# 数量描述符类
	class Quantity:
    def __init__(self, storage_name):
      self.storage_name = storage_name
    
    def __set__(self, instance, value): # self是描述符实例， instance是托管实例
      if value > 0:
        instance.__dict__[self.storage_name] = value  # 不能使用setattr 回再此触发描述符，导致无限重复
      else:
        raise ValueError("value must be > 0")
 	
  class LineItem： # ORM定义
  	weight = Quantity("weight")  # 创建托管属性
    price = Quantity("price")
    
# 数量属性绑定优化 - 普通 getattr/setattr + 唯一存储属性名
	储存属性自动生成，使用 “_clsname#i”, clsname为描述符类的名称，i为描述符类的__counter递增的当前值，避免重复
  使用这种无效标识符，但是内置的getattr 和 setattr 都可以识别使用
	class Quantity:
    __counter = 0
    
    def __init__(self):
      cls = cls.__name__
      prefix = cls.__name__
      index = cls.__counter
      self.storage_name = "_{}#{}".format(prefix, index)
      cls.__counter += 1
    
    def __get__(self, instance, owner): # owner 是 托管类LineItem，可以借此获取托管类的属性
      if instance is None: # 当使用 LineItem.weight 获取属性时，instance参数为None
        return self
      return getattr(instacen, self.storage_name) # 不会无限循环，因为存储属性和托管属性不同名，不会触发
    
    def __set__(self, instance, value):
      if value > 0:
        setattr(instance, self.storage_name, value)
      else:
        raise ValueError("value must be > 0")
  
  class LineItem:
    weight = Quantity()
    price = Quantity()

# 数量属性绑定优化 - 类装饰器/元类
	def storage_name_unify(cls):
  for key, attr in cls.__dict__.items():
    if isinstance(attr, Validated):  # Validated 是描述符类
      type_name = type(attr).__name__
      attr.storage_name = "_{}#{}".format(type_name, key)
  return cls
	
  创建类时就会触发，会先修改描述符类的storage_name，当触发描述符的get/set时就会设置规范命名的实例属性
	@storage_name_unify
  class Validated:
    pass
  缺点：这里的实现只会影响到当前类，子类不执行super父类方法，则不会受到影响
  >>> 元类实现 - 本质一样  类创建时触发
  class EntityMeta(type):
    def __init__(self, name, bases, attr_dict):
      """
      参数同 type(name: str, bases: Tuple, attr_dict: dict)
      :param self: 元类的实例类, 也有用cls。只是变量名而已
      :param name: 实例类名
      :param bases: 实例类的父类集
      :param attr_dict: 实例类的属性（数据/方法）
      """
      super().__init__(name, bases, attr_dict)
      for key, value in attr_dict.items():
        if isinstance(attr,  Validated):
          type_name = typr(attr).__name__
          attr_storage_name = "_{}#{}".format(type_name, key)
  
  class AutoStoraged(object, metaclass=EntityMeta):
    	pass

# 非空描述符 - 描述符基类的重用
	class AutoStoraged:
    __counter = 0
    
    
    def __init__(self):
      cls = cls.__name__
      prefix = cls.__name__
      index = cls.__counter
      self.storage_name = "_{}#{}".format(prefix, index)
      cls.__counter += 1
    
    def __get__(self, instance, owner): # owner 是 托管类LineItem，可以借此获取托管类的属性
      if instance is None: # 当使用 LineItem.weight 获取属性时，instance参数为None
        return self
      return getattr(instace, self.storage_name) # 不会无限循环，因为存储属性和托管属性不同名，不会触发
    
    def __set__(self, instance, value):
      setattr(instance, self.storage_name, value)

  class Validated(abc.ABC, AutoStorage):   # 抽象类，继承自abc.ABC抽象基类
    def __set__(self, instance, value):
      value = self.validate(instance, value)
      super().__set__(instance, value)
    
    @abc.abstractmethod
    def validate(self, instance, value):
      """return validated value or raise ValueError"""
    
  class Quantity(Validated):
    def validated(self, instance, value):
      if value <= 0:
        raise ValueError("value must be > 0")
      return value
  
  class NoneBlank(Validated):
    def validate(self, instance, value):
      value = value.strip()
      if len(value) == 0:
        raise ValueError("value cannot be empty or blank")
      return value
      
```

#### 覆盖型和非覆盖型 - 针对实例属性

> 类属性的赋值都会覆盖描述符，读类属性可以交由描述符的get方法，但是写类属性不能交由set方法

```python
存取属性方式的不对等，
	通过实例读取属性：实例 -> 类；
  通过赋值属性：实例，不会影响类
是否定义了__set__方法：
	覆盖型: 读取/赋值 都被描述符接管
  非覆盖型: 没有实现__set__, 实例赋值同名属性时直接新建不会被描述符接管
特殊：  --> 定义的类函数都是非覆盖型描述符，python的函数使用了描述符
	Function： 函数 FunctionObject # statucmethod
  Method：方法 PyMethodObject，特殊的Function # staticmethod、classmethod、abstractmethod
  	Bound Method：实例绑定，与实例的同名属性绑定，能够被覆盖
    Unbound Method：类方法，未绑定实例
	cls.fun -> <function >
  ins.fun -> <method >
```

#### 使用建议

```python
1. 内置的property类创建的时覆盖型描述符，即使定义fset也是如此。特性@property的默认set方法会抛出AttributeError，是创建只读属性的最简单方法
2. 只读描述符必须有set方法，手动抛出AttributeError
3. 用于验证的描述符，可以只有set方法
4. 仅有get方法的描述符（即非覆盖型）可以实现高效缓存，第一次get时触发，计算出结果后创建同名实例属性，后续不会触发
5. 非特殊方法可以被实例属性覆盖（只实现了get），对于特殊方法：解释器只会在类中找 ins.__class__.func
```

### 类 元编程

> 类是一等对象，可以使用函数新建而class关键字是非必需的  ==> type、类装饰器
> 元类：可以创建具有某种特质的全新类，例如抽象类
> 区分 导入时/运行时
> 除非开发框架，否则一般不要编写元类

#### 类工厂函数

```python
数据当作简单的记录处理时 
# 常规创建类
	class Dog:
    def __init__(self, name, weight, owner):
      self.name = name
      self.weight = weight
      self.owner = owner. # 重复的名称写了三遍
# collections.namedtuple
	Dog = collections.namedtuple("Dog", "name weight owner")
  namedtuple使用的是exec执行 填充式字符串代码 实现的
  """
  命名空间：dict {"var": value}
  exec(object[, globals[, locals]]) -> None: 
  	执行存储在字符串/文件中的代码块
  	不能做表达式求值并返回出去，可以执行复杂的代码逻辑，相对而言功能更加强大
  	内外的命名空间是相通的
  	eg. 字符串 -> 变量名
      exec(f"{str_name} = {value}")
      globals()[str_name] = value
    		环境变量特列：运行期的局部命名空间不可改变
    		def foo():
    			exec('y = 1 + 1\nprint(y)')
    			print(locals())  # {'y': 2}
    			print(y)   # name 'y' is not defined
    			# 在运行foo时没有y变量，使用eval动态创建了y，但是此时的foo局部命名空间不可改变
    			# locals中却有y，
    			#			可以手动取出来，z = locals()['y']，不能使用 y = locals()['y']，y的声明导致循环引用
    			
    	
  eval(expression, globals=None, locals=None) -> result:
  	expression 只能是单个表达式，不支持复杂的代码逻辑，例如赋值操作、循环语句等等
  	globals 用于指定运行时的全局命名空间，类型是字典，缺省时使用的是当前模块的内置命名空间。
  	locals 指定运行时的局部命名空间，类型是字典，缺省时使用 globals 的值。
  	两者都缺省时，则遵循 eval 函数执行时的作用域。不代表真正的命名空间，只在运算时起作用，运算后则销毁。
  	内外的命名空间bu相通
  	eg. 简单序列化：
  		>>> a = "[[1,2], [3,4], [5,6], [7,8], [9,0]]"
      >>> print(eval(a))
      [[1, 2], [3, 4], [5, 6], [7, 8], [9, 0]]
      >>> c = eval('x + y', {'x': 1, 'y': 2}, {'y': 3, 'z': 4})  # c = 4
      
 	命名空间 - 字典类型：
 		globals() 可读可写，而 locals() 只可读却不可写 - 改变locals无法改变局部变量的命名空间
 		globals获取到的就是全局变量本身存储对象，但是locals获取到的局部变量是一种代理，负责收集局部变量相关数据展示
 		限定eval执行的globals = None 能够限制表达式调用内置模块或属性的能力，默认会隐式的携带__builtins__ = 内置命名空间中的名称
  eval的安全替换：
  	ast 模块的 literal()， 会先检查表达式内容是否有效合法
  	缺点：AST 编译器的栈深（stack depth）有限，解析的字符串内容太多或太复杂时，可能导致程序崩溃
  """
# 类工厂函数
	"""
	类的双线模式：
		object是顶级类，他的子类是类，父子继承关系的最高点
		type是元类，它的实例是类，类实例关系的最高点
			构造类:
				type(o: o_ins) -> cls  函数式
				type(name: str = cls_name, bases: Tuple = (object, ), dict: Dict = cls_attrs) -> cls 类
						name 是新类的名称，可以直接作为构造类名使用
						bases 是新类继承的父类
						dict 是新类的属性（数据/方法）
						
	"""
	def record_factory(cls_name, field_names):
    try:
      field_names = field_names.replace(",", "").split()
    except AttributeError: # 不能调用replace 或 split
      pass
    
    field_names = tuple(field_names)
    
    def __init__(self, *args, **kwargs):
      attrs = dict(zip(self.__slots__, args))  # slots里面的属性名，与初始化的值 映射
      attrs.update(kwargs)
      for name, value in attrs.items():
        setattr(self, name, value)
      
    def __iter__(self):
      for name in self.__slots__:
        yield getattr(self, name)
    
    def __repr__(self):
      calues = ", ".join("{}={!r}".format(*i) for i in zip(self.__slots__, self)
      return "{}({})".format(self.__class__.__name__, values)
    
    cls_attrs = dict(__slots__ = field.names,  # 使用slots能够固定类的属性
                   __init__ = __init__,
                   __iter__ = __iter__,
                    __repr__ = __repr__)
    
    return type(cls_name, (object, ), cls_attrs)
    
```

#### 定制描述符的类装饰器

```python
储存属性名优化 - "_{}#{}".format(prefix, index)，缺乏描述性
# 修改LineItem类中的描述符的 storage_name 名称
def storage_name_unify(cls):
  for key, attr in cls.__dict__.items():
    if isinstance(attr, Validated):  # Validated 是描述符类
      type_name = type(attr).__name__
      attr.storage_name = "_{}#{}".format(type_name, key)
  return cls
```

#### 导入/运行

```python
python源码 .py --解析 编译--> 执行的字节码 .pyc
import 导入时运行顶层代码， 会编译函数的定义体，把函数对象绑定到对应的全局名称上。类的定义体：包含属性和方法

# 导入时
	1. 解释器执行所导入模块的及其依赖中的每个类定义体（全局普通代码，类的第一层定义体）来创建类，会执行元类的init
  2. 解释器先计算类的定义体，然后调用依附其上的装饰器函数。此时是装饰之后的类
  if __name__ == "__main__":
    code
  当包被外部导入时，__name__ = “包名” 所以不会触发该判断下的代码，该全局普通代码不执行是因为条件不满足
# 运行时
	1. 先触发导入
  2. 执行相应代码
  3. 垃圾回收，触发__del__

```

#### 元类

> type，python类型实例关系的顶层。制造类的工厂，用于构建类的类，所以类是元类的实例
> 某个实例的对象 为 ins.__class__ 或  type(ins)

##### 基础知识

```python
type 是 对象实例关系的顶端, type的对象是其本身 __class__
object 是 父子继承关系的顶端, object的父类是其本身  __bases__
某种程度上object更原初
	isinstance(object, type) -> True
  issubclass(type, object) -> True
  
  isinstance(type, object) -> True    # 侵犯了 type 的对象实例权利范围
  issubclass(object, type) -> False
# 内嵌元类
	abc.ABCMeta  抽象类元类
  元类同时是 type 的 实例 和 子类

# 定制类
	元类：__init__ 、__new__
  type构造函数：type(name: str, bases: Tuple, attr_dict: dict)
  接收的都是类的定义体，形式是名字到属性的映射。接收到时原顺序丢失
# __prepare__
	只在元类中且声明为类方法@classmethod有效，会在new之前调用，
  解释器调用元类中的new方法之前会先调用prepare，使用属性创建映射，然后将返回的映射传递给new的最后一个参数，再将创建好的类传递给init
  @classmethod
	def __prepare__(cls, name, bases):
    pass
# 类相关属性
	__bases__: 基类元组
  __qualname__: 类或者函数的规范限定名称 即 模块的全局作用域到类的点分路径
  __mro__: 方法解析基类顺序元组
  __subclasses__: 直接子类列表 
  __class__: 类型
```

##### 元类定制实例 - 实现定制描述符

```python
class EntityMeta(type):
  def __init__(self, name, bases, attr_dict):
    """
    参数同 type(name: str, bases: Tuple, attr_dict: dict)
    :param self: 元类的实例类, 也有用cls。只是变量名而已
    :param name: 实例类名
    :param bases: 实例类的父类/基类集
    :param attr_dict: 实例类的属性（数据/方法）
    """
    super().__init__(name, bases, attr_dict)
    for key, value in attr_dict.items():
      if isinstance(attr,  Validated):
        type_name = typr(attr).__name__
        attr_storage_name = "_{}#{}".format(type_name, key)
```

