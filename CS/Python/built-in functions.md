### **数字相关**

#### 数据类型

```
bool、int、float、complex
```

#### 进制转换

```
bin、otc、hex   # 转换成 二进制、八进制、十六进制
```

#### 数学运算

```
abs(x)  # 绝对值
divmmode(x, y)   # (x//y, x%y)
round(x)   # 四舍五入
pow(a, b)   # a**b
sum(iterable)
min/max
```

---

### **数据结构相关**

```python
# 序列
list、tuple、str、bytes、bytearray
# Hash
dict、set、frozenset、
result = reversed(iter)
length = len(iter)
sorted(iter, key=None, reverse=False)
enumerate(iter, start_index: int)
all()、any()   # all/any true
slice(1, 3, 1) = [1: 3: 1]
# 编码
ord(char)  # 字符对应数字编码的位置
chr(code)   # 数字编码找出对应的字符
ascii()   # 是ascii码中的返回该值 不是就返回u
# 格式化
format()
  s = "hello world!"
  print(format(s, "^20"))  #剧中
  print(format(s, "<20"))  #左对齐
  print(format(s, ">20"))  #右对齐
  #     hello world!    
  # hello world!        
  #         hello world!
  print(format(3, 'b' ))    # 二进制:11
  print(format(97, 'c' ))   # 转换成unicode字符:a
  print(format(11, 'd' ))   # ⼗进制:11
  print(format(11, 'o' ))   # 八进制:13 
  print(format(11, 'x' ))   # 十六进制(⼩写字母):b
  print(format(11, 'X' ))   # 十六进制(大写字母):B
  print(format(11, 'n' ))   # 和d⼀样:11
  print(format(11))         # 和d⼀样:11
  print(format(123456789, 'e' ))      # 科学计数法. 默认保留6位小数:1.234568e+08
  print(format(123456789, '0.2e' ))   # 科学计数法. 保留2位小数(小写):1.23e+08
  print(format(123456789, '0.2E' ))   # 科学计数法. 保留2位小数(大写):1.23E+08
  print(format(1.23456789, 'f' ))     # 小数点计数法. 保留6位小数:1.234568
  print(format(1.23456789, '0.2f' ))  # 小数点计数法. 保留2位小数:1.23
  print(format(1.23456789, '0.10f'))  # 小数点计数法. 保留10位小数:1.2345678900
  print(format(1.23456789e+3, 'F'))   # 小数点计数法. 很大的时候输出INF:1234.567890
repr()  # __repr__()、__str__
# 转换处理函数
	zip、map、filter、reduce
```

---

### **作用域相关**

```python
locals()  # 当前作用域中的名字
globals()  # 全局作用域中的名字
```

---

### **迭代器生成器相关**

```python
range()
next()
iter()
```

---

### **字符串类型代码的执行**

```python
eval()   # 执行字符串类型的代码，并返回结果； 
exec()  # 执行字符串类型的代码；
compile(code, "", mode="exec/eval/single")  # 字符串类型的代码编译成代码对象
dis.dis("code")  # disassembler function 反汇编语句查看函数
```

---

### **输入输出**

```python
print()
input()
```

---

### **内存相关**

```python
hash()
```

---

### **文件操作相关**

```python
open()
```

---

### **模块相关**

```python
__import__(module_name)
```

