<!-- TOC -->

- [基础类型](#基础类型)
	- [n进制表示](#n进制表示)
	- [2进制数据流](#2进制数据流)
- [容器类型](#容器类型)
	- [*list* (列表)](#list-列表)
	- [*tuple* (元组)](#tuple-元组)
	- [*dict* (字典)](#dict-字典)
	- [*set* (集合)](#set-集合)
	- [生成容器](#生成容器)
	- [切片](#切片)
- [变量类型](#变量类型)
	- [查看变量类型](#查看变量类型)
	- [判断变量是否属于某种类型](#判断变量是否属于某种类型)
- [*decorator* (装饰器)](#decorator-装饰器)
	- [定义装饰器](#定义装饰器)
	- [装饰有参函数](#装饰有参函数)
	- [装饰器参数](#装饰器参数)
- [*OOP*](#oop)
	- [实例类成员](#实例类成员)
	- [静态类成员](#静态类成员)
	- [类方法](#类方法)
	- [属性](#属性)
	- [隐含参数](#隐含参数)
	- [私有成员](#私有成员)
	- [继承](#继承)
	- [一些特殊的内置成员](#一些特殊的内置成员)
- [*range()* 函数](#range-函数)
- [变量作用域](#变量作用域)
	- [*global* 关键字](#global-关键字)
	- [*nonlocal* 关键字](#nonlocal-关键字)
- [*generator* (生成器)](#generator-生成器)
	- [遍历生成器与获取生成器的返回值](#遍历生成器与获取生成器的返回值)
	- [使用 *send()* 与生成器进行交互](#使用-send-与生成器进行交互)
- [与C/C++的基本语法差异](#与cc的基本语法差异)
- [*Socket API*](#socket-api)
	- [*Socket* 创建](#socket-创建)
	- [TCP 服务端](#tcp-服务端)
	- [UDP 服务端](#udp-服务端)
	- [客户端](#客户端)
- [包管理器 *pip*](#包管理器-pip)
	- [安装和配置 *pip*](#安装和配置-pip)
	- [镜像源](#镜像源)
	- [常用操作](#常用操作)
	- [包依赖检查与清理](#包依赖检查与清理)
- [文档浏览](#文档浏览)
- [*PEP8* 编码规范总结](#pep8-编码规范总结)
	- [代码编排](#代码编排)
	- [空格使用](#空格使用)
	- [命名规范](#命名规范)
	- [注释规范](#注释规范)

<!-- /TOC -->



## 基础类型
`Python`为**强类型**语言，不同数据类型之间需要显式转换。

基础类型有：

- `int、float` 数值类型，整数、小数
- `chr、str` 字符、字符串
- `bool` 布尔类型，取值`True/False`

进行强制类型转换的语法类似`C++`，以函数的语法调用类型即可。

转化数字到字符串：

```py
>>> data = str(100)
>>> type(data)
<class 'str'>
>>> data
'100'
```

转化数字到对应`ASCII`码的数值：

```py
>>> data = chr(65)
>>> data
'A'
```

转换数值到布尔类型：

```py
>>> b = bool(100)
>>> b
True
>>> b = bool(0)
>>> b
False
>>> b = bool(-100)
>>> b
True
```

### n进制表示
在`Python`中2进制/8进制/16进制的表示方式：

```py
# 2进制，0b做前缀
>>> 0b1000001
65
# 8进制，0o做前缀
>>> 0o101
65
# 16进制，0x做前缀
>>> 0x41
65
```

使用`chr()`将数值视为`ASCII`码转换为字符，使用`ord()`将字符转换为`ASCII`码：

```py

>>> c = chr(0x41)
>>> c
'A'
>>> ord(c)
65
```

使用`bin()`、`oct()`、`str()`、`hex()`可以分别获取数值对应的2进制、8进制、10进制、16进制文本：

```py
>>> bin(65)
'0b1000001'
>>> oct(65)
'0o101'
>>> str(65)
'65'
>>> hex(65)
'0x41'
```

### 2进制数据流
在Python中，Socket中发送2进制流需要使用`bytes`或`bytearray`格式进行包装。

- `bytes`和`bytearray`使用列表(`list`)或数值构造。
	- 使用数值构造时，表示创建一个字节数为指定数值的空二进制流。
	- 使用列表构造时，用于构造`bytes/bytearray`的列表中每一个成员必须为`0 ~ 255`之间的数值。
- `bytes/bytearray`都支持通过索引读取。
- `bytes/bytearray`区别在于`bytes`内容不可变，`bytearray`内容可被修改。

如下代码所示：

```py
# 以数值创建指定字节数的bytes/bytearray
>>> a = bytes(5)
>>> a
b'\x00\x00\x00\x00\x00'
>>> b = bytearray(5)
>>> b
bytearray(b'\x00\x00\x00\x00\x00')

# 以列表初始化bytes/bytearray
>>> c = bytes([0x41, 0x61])
>>> c
b'Aa'
>>> d = bytearray([0x41, 0x61])
>>> d
bytearray(b'Aa')

# 索引获取
>>> c[0]
65
>>> d[0]
65

# 索引赋值
>>> c[0] = 0x63
Traceback (most recent call last):
	File "<stdin>", line 1, in <module>
TypeError: 'bytes' object does not support item assignment
>>> c
b'Aa'
>>> d[0] = 0x65
>>> d
bytearray(b'ea')
```

`bytes/bytearray`类型可以通过`decode()`成员方法解码成普通字符串：

```py
>>> c.decode()
'Aa'
>>> c.decode()
'Aa'
```



## 容器类型
`Python`中的常见容器类型有：

- `tuple` 元组，不可变有序集合
- `list` 列表，可变有序集合
- `set` 集合，不可变
- `dict` 字典，保存键值对的集合

### *list* (列表)
`list`是一个**有序集合**，可以容纳各类数据，并能随意添加和删除。  
`list`中的数据可以是另一个`list`，访问方式类似**二维数组**。

定义一个`list`：

```py
>>> l = ['first', 'second']
>>> type(l)
<class 'list'>
```

取出`list`中指定下标的内容(下标可以为负数，即逆序取出内容)：

```py
>>> l[0]
'first'
```

计算`list`的长度：

```py
>>> len(l)
2
```

向list尾部添加内容：

```py
>>> l.append('third')
>>> l
['first', 'second', 'third']
```

向指定位置添加内容：

```py
>>> l.insert(0, 'one') # 在list表首添加字符串"one"
['one', 'first', 'second', 'third']
```

删除指定位置的数据：

```py
>>> l.pop(0) # 删除list表首的数据，不写参数时默认删除list最后一个数据
>>> l
['first', 'second', 'third']
```

替换指定位置的数据：

```py
>>> l[0] = [1, 2, 3] # 将list表首的数据替换为另一个list：[1, 2, 3]
>>> l
[[1, 2, 3], 'second', 'third']
```

反转列表：

```py
>>> l.reverse()
>>> l
['third', 'second', [1, 2, 3]]
```

列表可使用`+=`运算符追加新的列表，如下所示：

```py
>>> l = [1, 2, 3]
>>> l += [4]
>>> l
[1, 2, 3, 4]
```

列表不能使用`+=`操作符添加单个元素，会抛出异常：

```py
>>> l = [1, 2, 3]
>>> l += 4
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: 'int' object is not iterable
```

使用`+=`添加`str`类型时，`str`会被拆解为包含多个`char`的列表进行插入，如下所示：

```py
>>> s = []
>>> s += "abc"
>>> s
['a', 'b', 'c']
```

### *tuple* (元组)
`tuple`与`list`类似，但`tuple`中的数据**不可修改**，因此没有`append()`、`insert()`、`pop()`之类的方法。  
`tuple`可以像数组一样通过下标访问，但不能对其赋值：

```py
>>> t = (1, 2, 3)
>>> type(t)
<class 'tuple'>
>>> t[2]
3
>>> t[2] = 10
Traceback (most recent call last):
File "<stdin>", line 1, in <module>
TypeError: 'tuple' object does not support item assignment
```

定义一个至少有一个元素的`tuple`时，需要写成：

```py
>>> t = (1, )
```

逗号**不能省略**，这是为了**消歧义**(防止与数学括号相混淆)。

若`tuple`的成员是一个`list`，则`list`内容依然**可变**(`tuple`只保证对元组成员的引用不变，但成员本身的内容是否可变由成员自身的类型决定)。

### *dict* (字典)
`dict`使用`键-值`(key-value)存储，类似于`Java`中的`Map`，拥有很快的查找速度。  
相对于`list`，`dict`拥有更快的查找删除速度，而且不会随着`dict`内容的增加而减慢查找删除速度，但`dict`内存开销更大(空间换时间)。  
在`dict`中，`key`是**唯一、不能改变**的，`value`则没有此限制。  
`dict`根据`key`的值来计算对应`value`的位置(hash算法)，因此`key`是不能改变的，而可变对象`list`不能作为`key`。

定义`dict`使用大括号：

```py
>>> d = { 'first': 'one', 'second': 2, 'third': 3 }
>>> type(d)
<class 'dict'>
```

取出dict中的某个内容：

```py
>>> d['first']
'one'
```

改变指定key的value：

```py
>>> d['first'] = 1
>>> d
{'first': 1, 'second': 2, 'third': 3}
```

可以判断一个list中是否存在某个key：

```py
>>> 'first' in dict
True
```

向dict中添加数据类似于操作数组：

```py
>>> d['new'] = 4
>>> d
{'first': 1, 'second': 2, 'third': 3, 'new': 4}
```

删除`dict`中的内容使用`pop(key)`成员方法，删除了某个`dict`中的某个`key`，则该`key`的`value`也会随之被删除：

```py
>>> d.pop('new')
>>> d
{'first': 1, 'second': 2, 'third': 3}
```

### *set* (集合)
`set`是一组**没有**`value`的`key`的集合，`set`中的内容是**不可重复**的。
定义一个`set`：

```py
>>> s = { 1, 2, 3, 3 } #即使在定义时输入重复的元素，解释器也会将其自动忽略
>>> s
{1, 2, 3}
```

使用`add(key)`成员函数对给`set`添加`key`：

```py
>>> s.add('test')
>>> s
{1, 2, 3, 'test'}
```

### 生成容器
在定义容器的表达式中，可以直接加入`for`、`if`语句等作为条件生成容器内容。

```py
>>> l = [i for i in range(0, 10) if i > 5]
>>> l
[6, 7, 8, 9]
>>> s = { i for i in range(0, 10) }
>>> s
{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
>>> d = { i: i + 1 for i in range(0, 10) if i % 3 == 0 }
>>> d
{0: 1, 9: 10, 3: 4, 6: 7}
```

### 切片
Python中的`list`、`tuple`、`str`等类型支持**切片**操作。
切片语法：

```py
var[start:end:step]
```

- `start`为起始下标，`end`为结束下标，`step`为步进数(默认为`1`)。
- 范围为`[start, end)`，即获取下标`start`到`end - 1`之间的内容。
- 下标`start`和`end`的值可以超过容器界限，等价于一直取值到容器的边界。

如下所示：

```py
>>> t = (1, 2, 3, 4, 5)
# 获取下标1到3范围之间的内容
>>> t[1:4]
(2, 3, 4)
# 获取下标1及其之后的内容
>>> t[1:]
(2, 3, 4, 5)
# 获取下标4之前的内容
>>> t[:4]
(1, 2, 3, 4)
# 索引超过容器的边界则相当于取到容器结束
>>> t[:100] #等价于 t[:]
(1, 2, 3, 4, 5)
# 逆序索引切片
>>> t[-4:-1]
(2, 3, 4)
# 返回以2为间隔的内容
>>> t[::2]
(1, 3, 5)
# 返回以3为间隔的内容
>>> t[::3]
(1, 4)
# 返回以-1为间隔的内容(倒序输出)
>>> t[::-1]
(5, 4, 3, 2, 1)
```

`Python`中变量皆为**引用**，使用赋值操作符只是复制引用，但使用切片能够实现容器**值复制**：

```py
>>> l0 = [1, 2, 3]
>>> l1 = l0
>>> l1[0] = 100
>>> l1
[100, 2, 3]
>>> l0 # 引用复制，l1内容改变，l0也会随之改变
[100, 2, 3]
>>> l2 = l0[:] # 切片重新生成容器，非引用复制
>>> l2[0] = 1000
>>> l2
[1000, 2, 3]
>>> l0 # l0的值并未发生变化
[100, 2, 3]
```



## 变量类型

### 查看变量类型
使用`type()`函数可以查看变量类型：

```py
>>> a = lambda x: x + 2
>>> type(a)
<class 'function'>
>>> b = {'first': 1, 'second': 2, 'third': 3}
>>> type(b)
<class 'dict'>
```

### 判断变量是否属于某种类型
使用`isinstance()`函数可以判断某个变量是否是某种类型：

```py
>>> isinstance(100, int)
True
```

也可以使用`is`操作符判断类型：

```py
>>> type(100) is int
True
```

比较类实例时，`is`操作符与`isinstance()`函数逻辑不同：

- `isinstance()`只要实例类型是从比较类型中派生出的，返回`True`。
- `is`只有实例类型与比较类型完全匹配才返回`True`。

```py
>>> class A: pass
>>> class B(A): pass
>>> b = B()
>>> type(b) is B
True
>>> type(b) is A
False
>>> type(b) is object
False
>>> isinstance(b, B)
True
>>> isinstance(b, A)
True
>>> isinstance(b, object)
True
```



## *decorator* (装饰器)
装饰器能够为已有的函数附加额外的功能。  
装饰器也是设计模式中的一种，通过组合的方式来复用已有的功能。

### 定义装饰器
在Python中，装饰器本质上就是一个普通的函数，接受一个函数作为输入参数，同时返回一个装饰后的函数。  
装饰器基本的结构如下所示：

```py
def decorator_name(func_name):
	def wrapper(): # 定义一个局部函数作为包装函数
		# code before...
		func_name() # 调用被装饰的函数
		# code after...
	return wrapper # 返回装饰后的函数
```

在函数定义前加上`@装饰器名`即会使用装饰器来包装定义的函数，如下所示：

```py
@decorator_name
def func_name():
	# code...
```

实际上，Python中使用装饰器只是一个**语法糖**，实际相当于调用装饰器函数产出一个新的函数。  
上述代码等价于：

```py
def func_name():
	# code...
func_name = decorator_name(func_name)
```

一个基本的装饰器应用如下所示：

```py
from time import clock

# 打印被装饰的函数运行消耗的时间
def time_cost(func):
	def wrapper():
		start = clock()
		func()
		end = clock()
		print("Time used: %f seconds" % (end - start))
	return wrapper

# 将要使用的装饰器的名称写在函数定义前
@time_cost
def show(): # 装饰器是语法糖，方法show的属性"__name__"返回值为"wrapper"(即装饰器内的包装函数的名字)
	print("Call method:", show.__name__)

show()
```

输出结果：

```
Call method: wrapper
Time used: 0.000052 seconds
```

### 装饰有参函数
对于参数不为空的函数，定义装饰器函数时，需要修改包装函数的参数表，为其添加参数。  
如果能确定被装饰函数的函数原型，可以将包装函数的参数数量设置为与被装饰函数相同，如下所示：

```py
from time import clock

def time_cost(func):
	# 包装函数的参数表与被装饰的show()函数相同
	def wrapper(text):
		start = clock()
		func(text)
		end = clock()
		print("Time used: %f seconds" % (end - start))
	return wrapper

@time_cost
def show(text):
	print("Call show(): ", text)

show("Test arg")
```

输出结果：

```
Call show(): Test arg
Time used: 0.000052 seconds
```

若被装饰的函数是未知的，则需要将包装函数的参数表定义为接收可变参数。  
定义一个输出传入参数种类和内容的装饰器，如下所示：

```py
def decorator(func):

	def wrapper(*args, **kwargs):

		print("Print keyword parameters:")
		for arg in args:
			print("Value:", arg)

		print("Print positional parameters:")
		for key in kwargs:
			print("Key:", key, "Value:", kwargs[key])

		print()
		func(*args, **kwargs) # 即使函数的参数表是确定的，依然可以使用可变参数的形式传入参数

	return wrapper

@decorator
def show(num1, num2, num3, num4):
	print("Call method:", show.__name__)
	print("Num1 is: %d" % num1)
	print("Num2 is: %d" % num2)
	print("Num3 is: %d" % num3)
	print("Num4 is: %d" % num4)

show(1, 2, num3 = 3, num4 = 4)
```

输出结果：

```
Print keyword parameters:
Value: 1
Value: 2
Print positional parameters:
Key: num4 Value: 4
Key: num3 Value: 3

Call method: wrapper
Num1 is: 1
Num2 is: 2
Num3 is: 3
Num4 is: 4
```

### 装饰器参数
装饰器本身也可以带有参数。  
定义带有参数的装饰器需要在包装函数外再封装一层。  
基本样式如下所示：

```py
def decorator_name(decorator_args):
	# code...
	def decorator_wrapper_name(func_name):
		# code...
		def wrapper(*arg, **kwargs):
			# code...
			func_name(*arg, **kwargs)
			# code...
		return wrapper
	return decorator_wrapper_name
```

在实际编码中装饰器可以根据传入的参数来提供不同的装饰功能，如下所示：

```py
from time import clock

# 第一层装饰器函数用于包装装饰器本身的参数，返回真正的装饰器函数
def decorator(decorator_arg = ""):

	# 真正的装饰器函数
	def decorator_wrapper(func):

		# 包装函数
		def wrapper(*args, **kwargs):
			# 判断不同的装饰器参数，实现不同的装饰器功能
			if (decorator_arg == "Args"):
				print("Mode: Print Args", end = "\n\n")
				print("Print keyword parameters:")
				for arg in args:
					print("Value:", arg)
				print("Print positional parameters:")
				for key in kwargs:
					print("Key:", key, "Value:", kwargs[key])
				print()
				func(*args, **kwargs)
			elif (decorator_arg == "Time_cost"):
				print("Mode: Time Cost", end = "\n\n")
				start = clock()
				func(*args, **kwargs)
				end = clock()
				print("Time used: %f" % (end - start))
			else:
				print("Mode: Print Prefix", end = "\n\n")
				print("Use prefix.")
				func(*args, **kwargs)
			print()

		return wrapper

	return decorator_wrapper # decorator_wrapper才是真正接收函数作为参数的装饰器函数

def show(num1, num2, num3, num4):
	print("Call method:", show.__name__)
	print("Num1 is: %d" % num1)
	print("Num2 is: %d" % num2)
	print("Num3 is: %d" % num3)
	print("Num4 is: %d" % num4)

# 使用不同的装饰器参数来装饰同一个函数，实现不同的功能
@decorator()
def show1(num1, num2, num3, num4):
	show(num1, num2, num3, num4)
@decorator("Time_cost")
def show2(num1, num2, num3, num4):
	show(num1, num2, num3, num4)
@decorator("Args")
def show3(num1, num2, num3, num4):
	show(num1, num2, num3, num4)

show1(1, 2, num3 = 3, num4 = 4)
show2(1, 2, num3 = 3, num4 = 4)
show3(1, 2, num3 = 3, num4 = 4)
```

输出结果：

```
Mode: Print Prefix

Use prefix.
Call method: show
Num1 is: 1
Num2 is: 2
Num3 is: 3
Num4 is: 4

Mode: Time Cost

Call method: show
Num1 is: 1
Num2 is: 2
Num3 is: 3
Num4 is: 4
Time used: 0.000020

Mode: Print Args

Print keyword parameters:
Value: 1
Value: 2
Print positional parameters:
Key: num4 Value: 4
Key: num3 Value: 3

Call method: show
Num1 is: 1
Num2 is: 2
Num3 is: 3
Num4 is: 4
```



## *OOP*
与传统的OOP语言类似，Python中的class具有**独立**的**变量作用域**。  
相比传统的OOP语言如Java、C++等，Python对于OOP并没有完整的支持，在Python中**不支持**函数重载、**不支持**定义保护对象。

### 实例类成员
在Python中，类作用域内**不包含**隐式的对象引用(即类作用域中没有类似C++中的`this`指针或是Java中的`this`引用)，而是需要在成员函数的参数中传入对象实例。

- 每个类的实例成员函数的第一个参数必须为当前类的实例，通常使用`self`来命名。
- 通过类实例调用成员函数时，第一个参数(类实例参数)为隐含参数，不用写明。
- 即使在类内部，实例成员变量、实例成员函数也必须通过对象实例来调用。
- 在类内非函数作用域中，直接使用变量名相当于定义类的静态成员变量。
- 在成员函数作用域中，直接使用变量名相当于在函数内部创建了一个局部变量。

如下代码所示：

```py
class Test:

	def __init__(self, num1, num2):
		self.num1 = num2 # 实例变量定义无需单独声明，在构造函数中定义即可在整个类中使用
		self.num2 = num1

	def show(self): # 实例成员函数第一个参数为对象实例
		print(self.num1, self.num2) # 即使在类内部访问类的实例成员变量也需要通过实例对象
		# 直接访问num1、num2如使用语句 print(num1) 则会得到"num1未定义"的错误提示

test = Test(1, 2)
test.show()
```

输出结果：

```
2 1
```

### 静态类成员
在Python中同样可以定义类的静态成员，与传统的OOP语言类似，访问静态成员使用`类名.静态成员名`即可。

定义静态成员函数，需要注意：

- 类的静态成员函数在定义前需要加装饰器`@staticmethod`。
- 静态成员函数**没有**隐含参数，因此**不需要也不能**将第一个参数设定为类的实例。
- 同一个类的静态成员函数**不能**与实例成员函数同名。

定义类的静态成员变量，需要注意：

- 定义类的静态成员变量可以直接将变量名写在**类内非函数作用域**中(不需要也不能使用类名，会报错)。
- Python为动态语言，可以在运行期间创建成员变量，可以在函数作用域或全局作用域使用`类名.静态变量名`创建静态成员变量。
- 即使在类的内部，访问静态成员同样需要使用类名而不能直接调用。
- 静态成员变量可以与实例成员变量同名。
- 静态成员同样可以通过类实例调用。
- 当一个类实例中存在同名的静态成员变量与实例成员变量时，优先调用实例成员变量。

如下代码所示：

```py
class Test:

	num1 = 100
	num2 = 200 # 在类作用域中定义静态成员变量num1，num2

	def __init__(self, num1, num2):
		self.num1 = num2
		self.num2 = num1 # 定义实例成员变量num1，num2
		Test.num3 = num2
		Test.num4 = num1 # 在构造函数中定创建态成员变量num3，num4

	def show(self):
		print(self.num1, self.num2)
		Test.static_show()	# 即使在类内部，访问自身类的静态成员函数也需要加类名

	@staticmethod
	def static_show(): # 静态成员函数的定义前加装饰器@staticmethod
		print(Test.num1, Test.num2, Test.num3, Test.num4)

# print(Test.num3) # 报错，Test类的__init__()一次都没有被调用，此时Test.num3不存在
test = Test(1, 2)
test.show()
test.static_show() # 静态成员函数也能够被实例访问
```

### 类方法
类方法在定义时需要添加装饰器`@classmethod`，类方法在其他主流OOP编程语言(Java、C++、C#等)中没有对应的概念。

- 类方法的隐含参数是类的**类型**，而非类的实例，通常使用`cls`来命名。
- 类方法可以通过类实例或是类名调用。
- 类方法只能访问静态成员(即使通过**实例**调用)。

如下代码所示：

```py
class Test:

	num = 100

	def __init__(self, num):
		self.num = num

	@classmethod
	def show(cls, str):
		print(str, cls.num, Test.num)

t = Test(200)
t.show("Called by t.show()") # 通过实例与通过类名的调用结果完全相同，访问都是静态变量
Test.show("Called by Test.show()")
```

输出结果：

```
Called by t.show() 100 100
Called by Test.show() 100 100
```

### 属性
Python中同样支持`属性`，`属性`的概念与C#中类似。  
Python中的属性实际上是一组特定签名的`getter`、`setter`方法，用以有限制地存取某个私有变量，`getter`、`setter`方法被定义为`属性`之后，便能够以类似访问成员变量的语法来调用。

- 使用 *property()* 函数定义属性

	可以使用`property()`函数来绑定属性。  
	`property()`函数的基本结构如下：

	```py
	property_name = property(fget = None, fset = None, fdel = None, doc = None)
	```

	函数依次接收`getter`、`setter`、`deleter`和属性描述作为参数，返回值赋值的变量名称即为属性的名称。  
	如下所示：

	```py
	class Num:

		def __init__(self, value):
			self.__num = value

		# getter函数
		def get_num(self):
			return self.__num

		# setter函数
		def set_num(self, value):
			self.__num = value

		# deleter函数
		def del_num(self):
			del self.__num

		# 使用property()函数绑定属性读写函数，返回变量num计委属性名称
		num = property(get_num, set_num, del_num, doc = None)

	n = Num(10)
	print(n.num) # 使用用读属性，实际调用get_num()
	n.num = 100 # 使用写属性，实际调用set_num()
	print(n.num)
	del n.num # 删除成员，实际调用del_num()
	```

	若需定义`只读属性`，则调用`property()`函数时`fset`参数取`None`即可。

- 使用**装饰器**定义属性

	在`Python 2.6`之后，支持使用**装饰器**语法定义属性。
	
	- 使用`@property`装饰器装饰`getter`函数，同时该函数的名称即为**属性名**。
	- 使用`@属性名.setter`装饰器装饰`setter`函数。
	- 使用`@属性名.deleter`装饰器装饰`deleter`函数。
	- 使用装饰器语法来定义属性时，`getter`、`setter`、`deleter`函数的函数名都需要与属性名**相同**。
	
	如下所示，上例中的代码等价于：
	
	```py
	class Num:
	
		def __init__(self, value):
			self.__num = value
	
		@property
		def num(self):
			return self.__num
	
		@num.setter
		def num(self, value):
			self.__num = value
	
		@num.deleter
		def num(self):
			del self.__num
	
	n = Num(10)
	print(n.num)
	n.num = 100
	print(n.num)
	del n.num
	```

### 隐含参数
本质上，`Python`对于成员方法的区分实际上是对于隐含参数的处理方式不同。
对于一个实例方法，如下调用：

```py
instance.func_name(args...)
```

实际上等价于：

```py
class_name.func_name(isinstance, args...)
```

`Python`解释器只是将实例本身填充到了实例方法的第一个参数上而已，因而实例方法也可以以静态方法的语法被调用。  
在`C#`中也存在类似的语法转换，被称为**扩展方法**。

添加了装饰器`@staticmethod`或`@classmethod`的方法便不再能够进行这种转换，如下代码所示：

```py
class Test:

	num = 100

	def __init__(self, num):
		self.num = num

	def call(self):
		print("instance_method:", self.num)

	@classmethod
	def cls_call(cls):
		print("class_method:", cls.num)

	@staticmethod
	def static_call(self):
		print("static_method:", self.num)

	def no_arg():
		print("no_arg_method:", Test.num)

t = Test(200)

t.call() # 调用实例成员方法
Test.call(t) # 以静态方法的语法调用实例成员方法，调用成功，输出相同

Test.cls_call() # 通过类名调用类方法
t.cls_call() # 通过调用实例调用类方法，输出与通过类名调用相同
# Test.cls_call(t) # 报错，提式参数过多

# t.static_call() # 报错，提示缺少参数"slef"
t.static_call(t)
Test.static_call(t)

Test.no_arg()
# t.no_arg() # 报错，提示参数过多
```

输出结果：

```
instance_method: 200
instance_method: 200
class_method: 100
class_method: 100
static_method: 200
static_method: 200
no_arg_method: 100
```

通过以上结果可以得出：

- 实例方法的调用语法实际是语法糖，普通的实例方法可以通过类名语法进行调用。
- 通过普通语法调用实例方法时，解释器会将实例作为隐含参数。
- 使用了`@staticmethod`装饰器之后，通过实例调用该静态方法，解释器不再会将实例作为隐含参数。
- 使用了`@classmethod`装饰器之后，通过实例调用该类方法，解释器依然将实例视为类名处理。
- 参数为空的成员方法，即使没有添加任何装饰器，也只能通过类名访问。

### 私有成员
`Python`类中默认成员的访问属性为公有，在`Python`中不能定义保护成员，但可以定义私有成员。

在命名类的成员时，以`__`开头的成员即为**私有成员**，不能在类的外部被访问。  
如下代码所示：

```py
class Test:

	__num = 100

	def __init__(self, num):
		self.__num = num
		Test.__num = num

	def show(self):
		print(self.__num, Test.__num)

test = Test(1)
test.show() # 调用show()成员函数正确打印私有成员内容
print(test.__num, Test.__num) # 直接输出私有成员内容报错，错误提示 " 'Test'对象没有属性__num "
```

在`CPython`的实现中，私有变量并非真正被隐藏，仅仅是解释器对私有变量的名称做了一些改动使得外界无法访问。  
以`__xxx`为名的私有成员的实际名称被修改为`_类名__xxx`，使用改动后的名称可以正常访问私有成员。

上个例子稍作修改即可访问到私有变量：

```py
class Test:

	__num = 100

	def __init__(self, num):
		self.__num = num
		Test.__num = num

	def show(self):
		print(self.__num, Test.__num)

test = Test(1)
test.show()
print(test._Test__num, Test._Test__num) # 需要注意的是，不同的Python解释器重命名的方式可能略有不同
```

输出结果：

```
1 1
1 1 # 正常获得了私有成员变量的内容
```

### 继承
继承一个类时，若自定义构造函数`__init__()`，则需要在构造函数中调用父类构造函数。

调用父类构造函数时，可以使用以下方式：

- `Parent_name.__init__(self, args...)`
- `super(Parent_name, self).__init__(args...)`
- `super().__init__(self, args...)`

如下所示：

```py
class Parent:
	def __init__(self, a, b):
		self.a = a
		self.b = b

class Child(Parent):
	def __init__(self, a, b):
		# 以下三种方式皆可
		# Parent.__init__(self, a, b)
		# super(Parent, self).__init__(a, b)
		super().__init__(a, b)
```

### 一些特殊的内置成员
在Python中，有一类特殊的类成员，命名以`__`开始也以`__`结束，这一类成员并**不是**私有成员，可以直接被访问。
系统定义的属性与方法：

```py
Class.__doc__ # 类型帮助信息 'Class Doc.'
Class.__name__ # 类型名称 'Class'
Class.__module__ # 类型所在模块 '__main__'
Class.__bases__ # 类型所继承的基类 (<type 'object'>,)
Class.__dict__ # 类型字典，存储所有类型成员信息。 <dictproxy object at 0x00D3AD70>
Class().__class__ # 类型 <class '__main__.Class'>
Class().__module__ # 实例类型所在模块 '__main__'
Class().__dict__ # 对象字典，存储所有实例成员信息。 { 'i': 1234 }
```

一些常用的特殊方法：

```py
t = T() # 实际调用 t.__init__() 构造函数
del t # 实际调用 t.__del__() 析构函数
repr(t) # 实际调用 t.__repr__() 将对象转成字符串显示(适合解释器阅读)
str(t) # 实际调用 t.__str__() 将值转化为字符串形式(适合人阅读)，print()打印会调用对象的__str__()函数
format(t, format_spec) # 实际调用 t.__format__(format_spec) 格式化字符串的值
t() # 实际调用 t.__call__() 提供与函数类似的行为
len(t) # 实际调用 t.__len__()
t[key] # 实际调用 t.__getitem__(key) 访问索引值
t[key] = value # 实际调用 t.__setitem__(key, value) 索引赋值
t.member # 实际调用 t.__getattr__(menber) 访问成员
t.member = value # 实际调用 t.__setattr__(member, value) 成员赋值
t < k # 实际调用 t.__it__(k) 小于运算符
t > k # 实际调用 t.__gt__(k) 大于运算符
t + k # 实际调用 t.__add__(k) 加号运算符
```


## *range()* 函数
`range(start, stop, step)`函数接收三个参数，产生`[start, end)`范围的数字，以`step`为步进。

其中`start`、`step`参数参数带有默认值，默认情况下`start`为**0**，`step`为**1**。

`Python 2`中，`range()`返回类型是`list`。  
`Python 3`中，`range()`返回类型是`range`，得到`list`需要使用`list(xxx)`显式地进行强制类型转换。

`range()`函数一般用于`for`循环遍历，例如：

```py
for a in range(5):
	print(a, end = ' ')
```

输出结果：

```
0 1 2 3 4
```



## 变量作用域
在`Python`中，定义变量与赋值变量语法相同，这一设计导致局部作用域下访问外部变量时会有语义冲突。

### *global* 关键字
在局部作用域下，直接对全局变量赋值，解释器会认为你创建了一个与全局变量同名的**局部变量**，该变量在函数结束之后会被释放。
在局部作用域下，访问全局变量需要使用`global`关键字，声明使用全局变量而不是创建新的变量。

如下所示：

```py
num = 0

def set_num():
	num = 1

def set_global_num():
	global num
	num = 1

print("num:", num)
set_num()
print("num after set_num():", num)
set_global_num()
print("num after set_global_num():", num)
```

输出结果：

```
num: 0
num after set_num(): 0
num after set_global_num(): 1
```

### *nonlocal* 关键字
`global`关键字解决了局部作用域访问全局变量的问题，但不能解决闭包函数访问外部局部变量的问题。  
在`Python 3`中，引入了`nonlocal`关键字用于访问外部非全局作用域的变量。

如下所示：

```py
def func():

	num = 0

	def set_num():
		num = 1

	def set_nonlocal_num():
		nonlocal num	# 声明使用外部局部作用域的变量num，而不是创建新的局部变量num
		num = 1

	print("num:", num)
	set_num()
	print("num after set_num():", num)
	set_nonlocal_num()
	print("num after set_nonlocal_num():", num)

func()
```

输出结果：

```
num: 0
num after set_num(): 0
num after set_nonlocal_num(): 1
```

`nonlocal`关键字在上一级局部作用域中未找到变量时会向更外层的局部作用域中查找，如下所示：

```py
def func():

	num = 0

	def set_nonlocal_num():
		def set_num():
			nonlocal num # 会一直查找外部局部作用域中名为num的变量，不仅仅在上一层作用域
			num = 1
		set_num()

	print("num:", num)
	set_nonlocal_num()
	print("num after set_nonlocal_num():", num)

func()
```

输出结果：

```
num: 0
num after set_nonlocal_num(): 1
```



## *generator* (生成器)
使用生成器可以方便的生成一串特定的值。

- 在函数定义中使用关键字`yield`则该函数变成为一个**生成器**。
- 执行生成器函数**不会**得到该函数的返回值，而是得到一个生成器对象。
- 对生成器对象使用`next(生成器对象)`方法会执行一次生成器，执行到`yield`关键字时，方法暂停，并返回`yield`语句的返回值。  
	再次调用`next()`方法会从上次`yield`结束的语句继续开始执行，直到再次运行到`yield`语句。

在`Python 3`之前，可以使用`生成器对象.next()`的方式进行生成器迭代，在`Python 3`中变成了`生成器对象.__next()__`，作用与`next(生成器对象)`相同。

如下代码所示：

```py
def get():
	for i in range(0, 3):
		yield i
	return 100

a = get()
print(type(a))
print(next(a))
print(a.__next__())
print(a.__next__())
```

输出结果：

```py
<class 'generator'>
0
1
Traceback (most recent call last):
File "test.py", line 10, in <module>
	print(a.__next__())
StopIteration: 100
```

### 遍历生成器与获取生成器的返回值
除了使用`next()`函数来进行生成器迭代外，还可以采用**for循环**的形式。  
正常情况下，无法获得生成器函数的返回值，若需要返回值，则可以捕获**StopIteration**异常，通过异常对象获取生成器函数的返回值。

如下代码所示：

```py
def get():
	for i in range(0, 3):
		yield i
	return 100

a = get()
while True:
	try:
		print(next(a))
	except StopIteration as ex:
		print("The return value is:", ex.value)
		break
```

输出结果：

```
0
1
2
The return value is: 100
```

如果需要将生成器生成的内容添加到容器中，可以使用**列表生成式**，如下所示：

```py
def get():
	yield 100
	yield 200
	yield 300

g = get()
print([next(g) for i in range(0, 3)])
```

输出结果：

```
[100, 200, 300]
```

### 使用 *send()* 与生成器进行交互
当使用`next()`生成器启动后，便可以使用`生成器对象.send(内容)`向生成器传递内容，`send()`传递的内容将作为`yield`表达式的**返回值**。  
`next()`相当于`send(None)`，即`None`为`yield`表达式的默认返回值。  
执行了`send()`函数相当于先执行一次`next()`，然后将`send()`中的参数作为`yield`的返回值。  
首次启动生成器必须使用`next()`，因为第一次迭代没有`yield`表达式参与，以后的每一次迭代都可以使用`send()`代替`next()`。

如下代码所示：

```py
def get():
	for i in range(0, 3):
		num = yield i
		print(num)

g = get()
next(g)
print(g.send(10))
print(g.send(20))
```

输出结果：

```
10
1
20
2
```



## 与C/C++的基本语法差异
- Python**没有**自增自减运算符。
- Python中**没有**`switch`关键字。
- Python中的逻辑运算符用直白的英语表示：`and(且)`、`or(或)`、`not(非)`，位运算操作符不变。
- Python比较对象是否相同用`is`、`is not`。
- Python比较是否属于用`in`、`not in`。
- Python乘方用`**`符号，`2 ** 3`的值是`8`，相当于`2 ^ 3`(数学意义上)。
- Python**没有**三目运算符，但可以用类似的语句替代。在C语言中的语句`A ? B : C`，在Python中可写成`A and B or C`或`B if A else C`。需要注意的是，该语句与三目运算符并不完全等价，在运算中，空字符串`''`，数字`0`，空list`[]`，空dict`{}`，空tuple`()`，`None`，在逻辑运算中都被当作假来处理。



## *Socket API*
`Python`中的`sokcet`模块对`BSD`的`Socket API`做了基本的封装，函数调用名称与`BSD Socket`相同，但在参数上有所简化，使之更加易于使用。

### *Socket* 创建
`socket`类的构造函数定义为：

```py
__init__(self, family=<AddressFamily.AF_INET: 2>, type=<SocketKind.SOCK_STREAM: 1>, proto=0, fileno=None)
```

- `family`参数为协议类型，常见的取值有`AF_INET`(`IPv4`)、`AF_INET6`(`IPv6`)。
- `type`参数为socket类型，常见的取值有`SOCK_DGRAM`(`UDP`)、`SOCK_STREAM`(`TCP`)。

在`Python`中，`socket()`创建的是`Socket`对象而非文件描述符。

常见用法如下：

```py
# 创建 UDP Socket 对象
udpSock = socket(AF_INET, SOCK_DGRAM)
# 创建 TCP Socket 对象
tcpSock = socket(AF_INET, SOCK_STREAM)
```

### TCP 服务端
对于`TCP`而言，接收数据前需要绑定并监听端口：

```py
# 绑定端口
tcpSock.bind(("ip地址", 端口号))
# 监听端口
tcpSock.listen(最大连接数)
```

`TCP`需要使用`accept()`方法显式接受连接：

```py
# 使用accept()方法等待客户端连接建立
clientSock, clientAddr = tcpSock.accept()
```

在有用户建立连接之前，`accept()`方法会一直阻塞。  
当成功建立连接后，`accept()`方法返回客户端socket对象以及客户端地址。

使用`accept()`方法返回的客户端socket对象即可接收与发送消息。

### UDP 服务端
`UDP`是无连接的，只需`bind()`绑定端口与主机地址，无需监听与等待连接，如下所示：

```py
udpSock.bind(("ip地址", 端口号))
```

`UDP`直接使用自身对象发送与接收消息。

### 客户端
客户端在socket对象创建完成后，使用`connect()`方法与服务端连接后即可发送与接收消息：

```py
clientSock.connect(("ip地址", 端口))
```

对于无连接的`UDP`通信方式而言，调用`connect()`方法不是必须的，`UDP`下的`connect()`方法并未真正执行连接操作，仅仅设置了默认的发送目标端口和目标IP而已。



## 包管理器 *pip*
`Python`提供了包管理器`pip`用于安装、管理第三方模块。

### 安装和配置 *pip*
在部分Linux发行版中，`pip`并没有随`Python`一并被安装。  
`pip`可以从发行版的软件源中安装，也可以下载安装脚本：

```
$ wget https://bootstrap.pypa.io/get-pip.py
$ sudo python3 get-pip.py //将pip安装到系统目录(Linux下需要root权限)
$ python3 get-pip.py --user //将pip安装到用户目录
```

系统目录下的Python包是所有用户共享的，用户目录下的Python包只有所有者可访问。

- `Linux`下的`pip`相关特性

	安装**pip**到系统目录需要`root`权限，系统`Python`模块安装在路径`/usr/lib/python[version]/site-packages`下，需要`root`权限对其进行写入操作。  
	安装`Python`模块到用户目录下无需`root`权限，用户`Python`模块在路径`~/.local/lib/python[version]/site-packages`下。  
	还会在`~/.local/bin`路径下生成可执行脚本。

	由发行版自身的包管理器(`apt`、`yum`、`dnf`、`pacman`等)安装的`Python`模块也会显示在`pip list`指令的输出中。  
	系统包管理器安装的`Python`模块通常被系统某些组件依赖，尝试删除这些包时会收到`DEPRECATION`(反对)，提示这些包是由`distutils`(发行版工具)安装的，一般情况下，除非必要，不要删除这些由发行版包管理器安装的`Python`模块。

- `macOS`下的`pip`相关特性

	使用**homebrew**安装`Python`时会自动安装`pip`，使用`pip`**无需**`root`权限。  
	系统`Python`模块安装在路径`/usr/local/lib/python[version]/site-packages/`下。  
	用户`Python`模块安装在路径`~/Library/Python/[version]/lib/python/site-packages`下。
	系统`Python`模块会在`/usr/local/bin`路径下生成可执行脚本。  
	用户`Python`模块会在`~/Library/Python/[version]/bin`路径下生成可执行脚本。

### 镜像源
由于`GFW`的存在，`pip`官方源可能无法访问。  
使用国内镜像源替换官方源，推荐使用`USTC`源，在`.pip/pip.conf`文件中添加内容：

```
[global]
index-url = https://mirrors.ustc.edu.cn/pypi/web/simple
format = columns
```

### 常用操作
`pip`包管理器使用方式类似`Linux`发行版的包管理器，常见操作如下：

```
# pip install [package_name] //安装包
# pip uninstall [package_name] //移除包
# pip install --upgrade [package_name] //升级指定包
# pip install -U [package_name] //升级指定包，"-U"参数等价于"--upgrade"
$ pip install --user [package_name] //安装指定包到用户目录
$ pip list //列出已安装的包
$ pip list --outdated //列出可以升级的包
$ pip list --user //列出安装在用户目录的包
$ pip show [package_name] //显示包的详细信息
$ pip show --files [package_name] //列出包安装的文件列表
$ pip help [operate] //查看pip相关操作的帮助信息，如"pip help install"即查看"pip install"指令的所有用法
```

### 包依赖检查与清理
相比Linux各大发行版的包管理器。`pip`是一个非常**原始**、**简陋**的包管理器工具。

`pip`的主要缺陷如下：

- 没有一次性升级所有包的指令。
- 没有依赖清理功能，卸载一个包时不会清理无用依赖。

清理无用的`pip`包可以安装工具`pip-autoremove`：

```
$ pip install pip-autoremove
```

`pip-autoremove`的常见操作如下：

```
$ pip-autoremove -l //列出未被使用的依赖(可以被清理的依赖)
$ pip-autoremove -L //列出不被其它包依赖的包(主动安装的包)
```



## 文档浏览
Python提供了文档工具`pydoc`。

使用`pydoc`可以方便地查看Python标准库以及从pip安装的模块的对应文档：

```
$ pydoc -p [port]
```

指定端口号即可使用浏览器浏览Python文档。  
`port`值取`0`时任意选择一个可以使用的端口。



## *PEP8* 编码规范总结
**PEP**是`Python Enhancement Proposal`的缩写，即`Python增强建议`。

### 代码编排
- 以`80`个字符做为单行界限。
- 优先使用`4`个**空格**做为缩进，但在使用`Tab`做为缩进的代码中，应保持使用`Tab`。
- 代码换行优先在括号内部换行，也可以使用`\`换行符。
- 在括号内换行时，以其它括号内的元素作为对齐标准，或者使用悬挂式缩进。
- 在使用悬挂式缩进时，应使用进一步缩进以便于与其它行区分。
- 类定义和顶层函数定义之间空两行；类中的方法定义之间空一行；函数内逻辑无关段落之间空一行；其他地方尽量不要再空行。
- 不要将多句语句写在同一行，尽管使用`;`允许。

### 空格使用
总体原则，避免不必要的空格。

- 各种右括号前不要加空格。
- 逗号、冒号、分号前不要加空格。
- 函数的左括号前不要加空格。如`Func(1)`。
- 序列的左括号前不要加空格。如`list[2]`。
- `if`、`for`、`while`语句中，即使执行语句只有一句，也必须另起一行。
- 函数默认参数使用的赋值符左右省略空格。
- 赋值操作符(`=`、`+=`等)、比较操作符(`==`、`>`、`<`、`in`、`is`等)、布尔操作符(`and`、`is`、`not`)左右各加一个空格，不要为了对齐增加空格。

### 命名规范
- 类名使用驼峰命名法。
- 成员变量和方法使用全小写下划线风格。
- 常量使用全大写下划线风格。
- 模块名称使用全小写，除了`__init__`这样的特殊模块，不要在自定义的模块名称中加入下划线。
- 使用复数形式命名列表，如`members = ['user1','user2']`。
- 使用显式名称命名字典，如`name_age = {'Peter':18,'Dainslef':24}`。
- 避免使用通用名称，如`list`、`tuple`、`dict`等。
- 避免使用系统中已经存在的名称，如`os`、`sys`等。

### 注释规范
- 块注释，在一段代码前增加注释，注释符号`#`后与注释内容之间应有一个空格。
- 块注释的段落之间以只有`#`符号的行隔开。
- 行注释添加在代码之后，应尽量少用。
- 避免无意义的注释。
