常用的数据类型 >>

list(列表) >
list是一个有序集合，可以容纳各类数据，并能随意添加和删除。
list中的数据可以是另一个list，访问方式类似二维数组。
定义一个list：
>>> list = ['first', 'second']
取出list中指定下标的内容(下标可以为负数，即逆序取出内容)：
>>> list[0]
'first'
计算list的长度：
>>> len(list)
2
向list尾部添加内容：
>>> list.append('third')
>>> list
['first', 'second', 'third']
向指定位置添加内容：
>>> list.insert(0, 'one')		#在list表首添加字符串"one"
['one', 'first', 'second', 'third']
删除指定位置的数据：
>>> list.pop(0)					#删除list表首的数据，不写参数时默认删除list最后一个数据
>>> list
['first', 'second', 'third']
替换指定位置的数据：
>>> list[0] = [1, 2, 3]			#将list表首的数据替换为另一个list：[1, 2, 3]
>>> list
[[1, 2, 3], 'second', 'third']

----

tuple(元组) >
tuple与list类似，但tuple中的数据不可修改，因此没有append()、insert()、pop()之类的方法。
定义一一个至少有一个元素的tuple时，需要写成：
>>> turple = (1, )
逗号不能省略，这是为了消歧义(防止与数学括号相混淆)。
另外，如果tuple的成员是一个list，则list是可变的(tuple只保证每一个tuple内成员的引用不变，但成员本身依旧是可变的)。

----

dict(字典) >
dict使用键-值(key-value)存储，类似于java中的Map，拥有很快的查找速度。
相对于list，dict拥有更快的查找删除速度，而且不会随着dict内容的增加而减慢查找删除速度，但dict内存开销更大(空间换时间)。
在dict中，key是唯一、不能改变的，value则没有此限制。
dict根据key的值来计算对应value的位置(hash算法)，因此key是不能改变的，而可变对象list不能作为key。
定义dict使用大括号：
>>> dict = {'first': 'one', 'second': 2, 'third': 3}
取出dict中的某个内容：
>>> dict['first']
'one'
改变指定key的value：
>>> dict['first'] = 1
>>> dict
{'first': 1, 'second': 2, 'third': 3}
可以判断一个list中是否存在某个key：
>>> 'first' in dict
True
向dict中添加数据类似于操作数组：
>>> dict['new'] = 4
>>> dict
{'first': 1, 'second': 2, 'third': 3, 'new': 4}
删除dict中的内容使用pop(key)方法，删除了某个dict中的某个key，则该key的value也会随之被删除：
>>> dict.pop('new')
>>> dict
{'first': 1, 'second': 2, 'third': 3}

----

set(集合) >
set是一组没有value的key的集合，set中的内容是不可重复的。
定义一个set：
>>> set = {1, 2, 3, 3}		#即使你在定义时输入重复的元素，解释器也会将其自动忽略
>>> set
{1, 2, 3}
可以使用add(key)函数对给set添加key：
>>> set.add('test')
>>> set
{1, 2, 3, 'test'}

----

使用循环生成list、set、dict等 >
在定义容器的表达式中，可以直接加入for、if语句等作为条件生成容器内容。
>>> list = [i for i in range(0, 10) if i > 5]
>>> list
[6, 7, 8, 9]
>>> set = {i for i in range(0, 10)}
>>> set
{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
>>> dict = {i: i + 1 for i in range(0, 10) if i % 3 == 0}
>>> dict
{0: 1, 9: 10, 3: 4, 6: 7}

========


变量类型 >>

查看变量类型 >
使用type()函数可以查看变量类型：
>>> a = lambda x: x + 2
>>> type(a)
<class 'function'>
>>> b = {'first': 1, 'second': 2, 'third': 3}
>>> type(b)
<class 'dict'>

----

判断变量是否属于某种类型 >
使用isinstance()函数可以判断某个变量是否是某种类型：
>>> isinstance(100, int)
True
>>> class List(object): pass
>>> list = List()
>>> isinstance(list, List)
True
如果比较的是类实例，只要这个实例对应的类是从比较的类型中派生出来的，返回值都为True。

========


Python中的OOP >>
与传统的OOP语言类似，Python中的class具有独立的变量作用域。
相比传统的OOP语言如Java、C++等，Python对于OOP并没有完整的支持，在Python中不支持函数重载、不支持定义保护对象。

----

定义类的实例成员 >
在Python中，每个类的实例成员函数的第一个参数必须为当前类的实例(一般命名为self)。
Python中的实例成员变量、实例成员函数也必须通过对象实例来调用。
需要注意的是，即使是在类的内部，访问类的实例成员依然需要通过对象实例而不能直接使用变量名(直接使用变量名相当于是在函数内部创建一个与类成员变量同名的内部变量)。
例如：

class Test:
	def __init__(self, num1, num2):
		self.num1 = num2	#实例变量定义无需单独声明，在构造函数中定义即可在整个类中使用
		self.num2 = num1
	
	def show(self):						#实例成员函数第一个参数为对象实例
		print(self.num1, self.num2)		#即使在类内部访问类的实例成员变量也需要通过实例对象
										#直接访问num1、num2如使用语句 print(num1) 则会得到错误提示 NameError: name 'num1' is not defined
		
test = Test(1, 2)
test.show()

输出结果：
2 1

----

定义类的静态成员 >
在Python中同样可以定义类的静态成员，与传统的OOP语言类似，访问静态成员使用 "类名.静态成员名" 即可。
类的静态成员函数在定义时类似普通函数，不需要将第一个参数设定为当前类的实例，只需注意函数的缩进即可(作用域在类中)。
定义类的静态成员变量有两种方式，可以直接将变量名写在类的非函数作用域中(不需要使用类名)，也可以在构造函数中定义(格式类似与实例变量，需要写类名，否则就会变成局部变量)。
需要注意的是，即使在类的内部，访问静态成员同样需要使用类名而不能直接调用。
Python中同一个类的静态成员函数不能与实例成员函数同名，但静态成员变量可以与实例成员变量同名。
例如：

class Test:

	num1 = 100
	num2 = 200					#在类作用域中定义静态成员变量num1，num2

	def __init__(self, num1, num2):
		self.num1 = num2
		self.num2 = num1		#定义实例成员变量num1，num2
		Test.num3 = num2
		Test.num4 = num1		#在构造函数中定义静态成员变量num3，num4

	def show(self):
		print(self.num1, self.num2)
		Test.static_show()		#即使在类内部，访问自身类的静态成员函数也需要加类名

	def static_show():			#静态成员函数的定义类似于普通函数，只是作用域不同
		print(Test.num1, Test.num2, Test.num3, Test.num4)

test = Test(1, 2)
test.show()

输出结果：
2 1
100 200 2 1

----

私有成员 >
Python的类中默认成员的访问属性为公有，在Python中不能定义保护成员，但可以定义私有成员。
在命名类的成员时，以 "__" 开头的成员都是私有成员，不能在类的外部被访问。
例如：

class Test:

	__num = 100

	def __init__(self, num):
		self.__num = num
		Test.__num = num

	def show(self):
		print(self.__num, Test.__num)

test = Test(1)
test.show()							#调用show()成员函数正确打印私有成员内容
print(test.__num, Test.__num)		#直接输出私有成员内容报错，错误提示 " 'Test'对象没有属性__num "

输出结果：
1 1
Traceback (most recent call last):
  File "test.py", line 14, in <module>
    print(test.__num, Test.__num)
AttributeError: 'Test' object has no attribute '__num'

实际上，Python中的隐藏变量并不是真的把变量隐藏了，仅仅是Python解释器对私有变量的名称做了一些改动使得外界无法访问。
以 "__xxx" 为名的私有成员的实际名称被改成了 "_类名__xxx" ，只要使用改动后的名称，就可以访问私有成员变量了。
上个例子稍作修改即可访问到私有变量：

class Test:

	__num = 100

	def __init__(self, num):
		self.__num = num
		Test.__num = num

	def show(self):
		print(self.__num, Test.__num)

test = Test(1)
test.show()
print(test._Test__num, Test._Test__num)			#需要注意的是，不同的Python解释器重命名的方式可能略有不同

输出结果：
1 1
1 1					#正常获得了私有成员变量的内容

----

一些特殊的内置成员 >
在Python中，有一类特殊的类成员，命名以 "__" 开始也以 "__" 结束，这一类成员并不是私有成员，可以直接被访问。

系统定义的属性与方法：
Class.__doc__ 				# 类型帮助信息 'Class Doc.' 
Class.__name__ 				# 类型名称 'Class' 
Class.__module__ 			# 类型所在模块 '__main__' 
Class.__bases__ 			# 类型所继承的基类 (<type 'object'>,) 
Class.__dict__ 				# 类型字典，存储所有类型成员信息。 <dictproxy object at 0x00D3AD70> 
Class().__class__ 			# 类型 <class '__main__.Class'> 
Class().__module__ 			# 实例类型所在模块 '__main__' 
Class().__dict__ 			# 对象字典，存储所有实例成员信息。 {'i': 1234}

一些常用的特殊方法：
t = T() 实际调用 t.__init__() 构造函数
del t 实际调用 t.__del__() 析构函数
repr(t) 实际调用 t.__repr__() 将对象转成字符串显示(适合解释器阅读)
str(t) 实际调用 t.__str__() 将值转化为字符串形式(适合人阅读)，print()打印会调用对象的__str__()函数
format(t, format_spec) 实际调用 t.__format__(format_spec) 格式化字符串的值
t() 实际调用 t.__call__() 类提供与函数类似的行为

========


关于range()函数 >>
range(start, stop, step)函数接收三个参数，产生[start, end)范围的数字，以step为间隔。
默认值start为0，step为1。
在Python2中，range()的返回类型是一个list。
在Python3中，range()返回的是迭代值，如果想得到list需要用list()显式地进行强制类型转换。
range()函数一般用于for循环遍历，例如：
for a in range(0, 5):
	print(a, end = ' ')
输出结果 0 1 2 3 4

========


关于global关键字 >>
在Python中变量是无类型的，因此定义变量与复制变量语句相同，在函数中，可以直接引用全局变量，但一个作用域只能有一个变量名，如果对全局变量进行赋值，解释器就会认为你创建了一个局部变量，该变量在函数结束之后是会被释放的。
如果想要在函数中对全局变量进行值修改需要使用global关键字将该变量名声明为全局的。

========


关于生成器(generator) >>
使用生成器可以方便的生成一串特定的值。
在函数定义中使用关键字yield则该函数则成为了一个生成。
执行生成器函数不会得到该函数的返回值，而是得到一个生成器对象，对生成器对象使用next()函数便会执行一次生成器，执行到yield关键字时便会停下来，返回yield语句的返回值，再次调用next()便会从上次yield结束的语句继续开始执行，直到一个新的yield语句。
在Python3之前，可以使用 生成器对象.next() 的方式进行生成器迭代，在Python3中变成了 生成器对象.__next()__ ，作用与next()相同。

实例代码：

def get():
	for i in range(0, 3):
		yield i
	return 100

a = get()
print(type(a))
print(next(a))
print(a.__next__())
print(a.__next__())

输出结果：
<class 'generator'>
0
1
Traceback (most recent call last):
  File "test.py", line 10, in <module>
	print(a.__next__())
StopIteration: 100

----

遍历生成器与获取生成器的返回值 >
一般在实际编码中很少直接使用next()函数来进行生成器迭代，而是采用for循环的形式。
正常情况下，是不能获得生成器函数中的返回值的，如果需要返回值，则可以捕获StopIteration异常。

实例代码：

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
		
输出结果：
0
1
2
The return value is: 100

----

使用send()与生成器进行交互 >
当使用next()生成器启动后，便可以使用 生成器对象.send(内容) 向生成器传递内容，send()传递的内容将作为yield表达式的返回值。
next()就相当于send(None)，即默认yield表达式的返回值。
执行了send()函数相当于执行了一次next()，然后将send()中的参数作为yield的返回值。
首次启动生成器必须使用next()，因为第一次迭代没有yield表达式参与，以后的每一次迭代都可以使用send()代替next()

实例代码：

def get():
	m = 0
	for i in range(0, 3):
		m = yield i
		print(m)
	
a= get()
next(a)
print(a.send(10))
print(a.send(20))

输出结果：
10
1
20
2

========


与c/c++的基本语法差异 >>
Python没有自增自减运算符。
Python中没有switch关键字。
Python中的逻辑运算符用直白的英语表示：与 => and 或 => or 非 => not (位运算依然是^、|、~、&)
Python比较对象是否相同用is、is not
Python比较是否属于用in、not in
Python乘方用**符号，2 ** 3的值是8，相当于2 ^ 3(数学意义上)。
Python没有三目运算符，可以用类似的语句替代： A and B or C
需要注意的是，该语句与三目运算符并不完全等价，在运算中，空字符串‘’，数字0，空list[]，空dict{}，空()，None，在逻辑运算中都被当作假来处理。