[TOC]

##五大内存区
C/C++中，内存分为5个区，分别是堆区，栈区，静态区，文字常量区，程序代码区。

- `栈区(stack)`由编译器自动分配释放，存放函数的参数值，局部变量的值等。其操作方式类似于数据结构中的栈，地址由高向低减少。
- `堆区(heap)`由`malloc``new`等分配的空间的地址，地址由低向高增长，需要程序员手动释放(`free``delete`)，若程序员不释放，程序结束时可能由OS回收。注意它与数据结构中的堆是两回事，分配方式类似于链表。
- `全局/静态变量区(static)`全局变量和静态变量的存储是放在一块的，已初始化的全局变量和静态变量在一块区域，未初始化的全局变量和未初始化的静态变量在相邻的另一块区域。程序结束后由系统释放。
- `文字常量区`常量字符串就是放在这里的，程序结束后由系统释放。
- `程序代码区`存放函数体的二进制代码。

举例：

```c
int a = 0;		//全局初始化区
char *p1;		//全局未初始化区
int main()
{
	int b; 						//栈区
	char s[] = "abc"; 			//栈区
	char *p2; 					//栈区
	char *p3 = "123456"; 		//"123456"在常量区，p3在栈区
	static int c = 0； 			//全局/静态已初始化区
	p2 = (char*)malloc(10);		//malloc分配得来得10字节的区域就在堆区
	strcpy(p1, "123456"); 		//"123456"放在常量区，编译器可能会将它与p3所指向的"123456"优化成一个地方
	return 0;
}
```



##C/C++中函数定义的区别
- 在C语言中，函数的定义中，参数**不能**只写参数类型而没有参数名。
- 在C++中，函数的定义里，参数**允许**只写参数类型而没有参数名。
- 在C语言中，`function()`参数表为空代表这个函数可以接收**任意个**参数， 而`function(void)`才代表函数不接收参数，因此，对于任意参数的函数，都可以用空参数表的形式做函数声明(C语言不支持函数重载，一个函数名对应的函数实现只会有一个)。
- 在C++中，`function()`参数表为空与`function(void)`意义相同，都表示该函数**不接收任何参数**。而且C++支持**函数重载**，一个函数名根据参数不同可以有多个实现，因此，在C++中函数声明必须与函数定义的原型**完全相同**。



##C/C++中static关键字的区别

###C语言中的static
- 在C语言中，`static`用在**函数/全局变量**前表示该**函数/全局变量**为当前文件的**内部函数/全局变量**，只能在该文件中被访问，当前文件被`include`到了其他的文件中是**不能被访问**的。
- `static`用在局部变量前，则成为**静态**局部变量，静态局部变量**不在**栈区分配内存而是在**全局变量区**中分配空间，因此保存在静态局部变量中的值不会随着函数运行结束而被**自动释放**，下次执行该函数，该函数内部的静态局部变量不会重新分配空间，因而而是依然使用上次函数执行结束时的值。

###C++中的static
在C++中，除了C语言中的用法之外，还可以用在类的成员前，表示`静态成员`，静态成员只能初始化一次，全局仅有一个实体。

- 静态成员不依赖于类的实例而存在，无需进行类实例化即可直接通过类名进行访问，同时一个类的无论有多少个实例，这些实例的静态成员都指向同一块内存区域(即同一个类的静态成员变量只要有一个变化，其他的也会变化，因为这些类的静态成员变量实际上是同一个)。
- 静态成员之间能够相互访问，没有`this`指针，静态成员函数不能访问非静态成员函数和非静态数据成员。
- 由于没有`this`指针的额外开销，因此静态成员函数与类的普通成员函数相比速度上会有少许的增长。
- 静态成员函数在类内声明时使用`static`关键字，在类外定义时不再使用`static`关键字。
- 静态成员变量必须在类外初始化，在类中的静态成员变量定义仅等同于声明，如果静态成员变量没有在类外进行初始化，引用时会出现`未定义引用`错误。
- 普通静态成员变量不能进行类内初始化，只有**常静态成员变量**(`const static`)才能进行类内初始化。

静态成员变量初始化的格式为：

```cpp
数据类型 类名::静态成员变量名 = 值;		//静态成员变量的初始化需要在全局区域，不能在函数体内
```

类的静态成员变量有两种访问形式：

```cpp
类实例名.静态成员变量名;
类名::静态成员变量名;
```

需要注意的是，类的静态成员变量在逻辑上依然受到类的访问权限的制约，`private``protected`的静态成员变量依然无法在类外访问，但可以在类外赋初值。



##C/C++中const使用的区别

###const变量初始化
在C语言中，`const`变量在定义时可以不初始化，编译器会自动为其初始化为一个默认值。
在c++中，`const`变量在定义的同时必须显式地初始化，定义没有初始化的`const`变量将无法通过编译。
`const`变量在类中定义时，则初始化需要放在构造函数的初始化列表中(`C++98`)。
在`C++11`中，成员变量初始化可以直接在类中进行，`const`成员变量也一样可以在类中初始化。

###const变量作为数组长度
对于以下代码：

```cpp
const int length = 10;
int array[length];
```

在部分C语言编译器中会报错，但在C++中正确。
`C99`开始支持变量作为数组长度定义，但不是所有编译器都支持这个特性(`gcc`能够支持)
`ANSI C`中，数组的长度只能由常量定义，即使`const`变量的值不会发生变化，但仍然**不是**常量。



##关于`sizeof`运算符
`sizeof`运算符并不是函数，因此它在编译时起效而不是运行时。
在使用`sizeof`时需要小心辨别参数是否为指针！
指针与数组的区别之一就是使用`sizeof`返回的大小不同！
对于数组而言，虽然数组名可以代表数组的首地址，但`sizeof`对于指针返回的大小总是8(Linux 64bit)或是4(Windows/Linux 32bit)，而将数组名作为参数返回的是`数组类型 * 元素个数`的大小。
例如：

```cpp
#include <stdio.h>

int main(void)
{
	char *str = "12345";
	char chars[5] = "12345";
	printf("%d %d\n", sizeof(str), sizeof(chars));
	return 0;
}
```

输出结果：(gcc 4.9.1 && ArchLinux x86_64)
8 5

由结果可知，`str`的类型为`char*`，是指针，大小为8，`chars`类型为`char数组`，大小为5*1=5。



##结构体对齐
理论上，结构体的大小等于结构体内的变量大小之和，但实际上由于结构体对齐，结构体的大小与变量大小之和有时并不相等。
在`gcc/clang`等编译器中，结构体是按照结构体内的最大的成员变量的长度来进行对齐的。即使变量长度没达到最大成员的长度，也会占有该大小的空间。多个小长度的成员能够进行在同一片对齐区域内。但如果出现了最大长度的成员变量，则下一个变量就重新对齐。
例如：

```cpp
struct
{
	int a;
	char b;
} A;

struct
{
	int a;
	char b;
	char c;
} B;

struct
{
	char b;
	int a;
	char c;
} C;
```

结构体`A`的大小是8，按照最大的成员变量的类型`int`的长度进行对齐，变量`b`虽然只有1个字节，但结构体的长度为8个字节。
结构体`B`的大小依旧是8,因为变量`b`按照`int`型的4个字节进行对齐，但并未将4个字节的空间完全使用，故变量`c`继续使用这4个字节的空间。
结构体`C`的大小是12,因为变量`b`按照`int`型的4个字节进行对齐，但下一个变量`a`也为`int`型，需要占用4个字节，`b`的剩余空间不够使用，`a`变量便会再占用4个字节的空间，而由于`a`变量是完全使用对齐空间的，下一个变量`c`则需要重新分配对齐空间，又占用4个字节的空间，故结构体`C`的大小为4+4+4=12。



##变长参数函数
C语言不支持**函数重载**，但是依然可以定义变长参数函数，使用`...`符号代表可变参数表。
需要注意的是，不能定义一个参数仅为`...`的函数，一个函数如果接受变长参数，则至少需要有一个确定参数。
典型的变长参数函数定义：

```c
type function(type arg, ...);
```

变长参数函数在标准库里有很多，比如打印输出函数`printf()`就可以接收变长参数。

###自定义变长参数函数
自行编写变长参数函数可以使用`stdarg.h`头文件中提供的宏，如下所示：

```c
#include <stdarg.h>
void va_start(va_list ap, argN);
void va_copy(va_list dest, va_list src);
type va_arg(va_list ap, type);
void va_end(va_list ap);
```

使用方法：

0. 先要创建`va_list`变量用于记录位置，然后使用`va_start()`宏初始化`va_list`变量，参数`argN`为函数第一个参数。
0. 通过`va_arg()`获取当前`va_list`的下一个参数值，`type`为下一个参数的类型。每次运行这个宏，`va_list`会随之下移一个位置。
0. 当所有变量都读出之后可以关闭`va_list`，使用`va_end()`宏。

例如：

```c
#include <stdio.h>
#include <stdarg.h>

int get(int s, ...)
{
	va_list arg;
	va_start(arg, s);							//初始化arg
	printf("%d ", va_arg(arg, int));			//第一次运行宏得到第二个参数的值
	printf("%d ", va_arg(arg, int));			//第二次运行宏得到第三个参数的值
	va_end(arg);
	return 0;
}

int main(void)
{
	get(5, 30, 40);
	return 0;
}
```

###直接取地址获取变长参数内容
除了使用`stdarg.h`头文件中所提供的宏来获取变长参数内容之外，还可以直接以取地址的方式来获取变长参数的内容。
在C语言中，函数的参数压栈的顺序是从右向左，而栈底为高地址，栈顶低地址，因此靠后的参数先进栈为高地址，靠前的参数后进栈为低地址。与结构体对齐类似，参数在压栈过程中编译器会对其进行内存对齐，因此在计算变长参数的偏移地址时需要考虑参数类型的对齐情况。
在不同平台下，变量类型所占字节数是不同的：

- 在`Windows x86`系统中，`int``char``float``long``指针`以及为未指定类型的整数等，以4个字节对齐。`double``long long`以及未指定类型的小数等以8个字节对齐。
- 在`Unix x86_64`中，除了`long double`之外，大部分类型都以8个字节对齐。

举例：

```c
#include <stdio.h>

void get(float a, ...)
{
	printf("%f %c %d\n", a, *(char*)(&a + 1), *(int*)(&a + 2));
}

int main(void)
{
	get(9.9, 'b', 888);
	return 0;
}
```

输出结果：(VS2013 && Windows 8.1 x86_64)
9.900000 b 888

输出结果：(gcc 5.1.0 && ArchLinux x86_64)
9.900000   98

从结果不难看出，`Unix`环境下输出的参数内容产生了偏差，是由于数据不同平台数据类型长度不同，内存对齐方式不同导致的。
要使`Unix`环境下能够显示参数，修改`printf()`函数中的内容：

```c
printf("%f %c %d\n", a, *(char*)((long*)&a + 1), *((long*)&a + 2));
```

即可在`Unix x86_64`环境下正常输出结果。



##自增自减运算符的优先级
自增自减运算符根据出现位置的不同，可能在语句之前或语句之后执行，且对整个语句生效(部分编译器约定不同，比如`clang`)。
举例：

```c
int a = 0;
printf("%d %d\n", a, ++a);
```

输出结果为：
1 1		(gcc 4.9.2 && ArchLinux amd64)
0 1		(clang 3.5.1 && ArchLinux amd64)

在`clang`中会给出警告，`warning: unsequenced modification and access to 'a' `，即无序地修改和存取变量`a`。

```c
int a[5] = { 1, 2, 3, 4, 5 };
int b[5] = { 0 };
int *c = a;
int *d = b;
while (*d++ = *c++);
for (int i = 0; i < 5; i++)
	printf("%d ", b[i]);
```

输出结果：
1 2 3 4 5

`gcc`与`clang`输出相同，但在`clang`中会给出警告，`warning: using the result of an assignment as a condition without parentheses [-Wparentheses]`，即仅使用了条件任务而没有使用括号(未使用循环体)。
`while (*d++ = *c++);`的作用是复制数组内容，先将指针`c`指向的内容取出即`*c`，复制到指针d指向的内容即`*d`，然后执行自增运算符，左右的指针都自增1位，同时指向数组下一个元素，然后`while`语句判断`*d`的内容，由于在C/C++中，非0数值都被是为是`true`，故循环可继续执行，直到数组结束，指针指向空内容为止。
用`while (*d++ = *c++);`进行复制内容时需要注意，如果复制的内容中含有0，则复制会提前结束。
此类语句还可以用来复制**字符数组**，字符串以`\0`结尾，复制到字符串结尾自动停止。



##编译器自动生成类的成员函数
一个没有任何内容的空类实际上并不是空的，编译器会自动为其增加一个空构造函数，复制构造函数，空析构函数，并重载等号为复制对象，还带有一对取址运算符重载，这些函数只有在第一次被调用时，才会别编译器创建。所有这些函数都是`inline`和`public`的。
在`C++11`中，如果类没有定义自己的复制构造函数，则还会生成默认的移动构造函数和并重载等号为移动赋值运算符。如果自行定义了复制构造函数而没有定义移动构造函数，则使用右值对象做参数实例化时，会调用复制构造函数(`const左值引用`能够绑定在右值对象上，但如果存在移动构造函数则会优先匹配接收右值的移动构造函数)。
默认情况下，由编译器生成的默认复制构造函数以及重载等号都是浅复制，即对于指针变量，只会复制指针中保存的地址，而不会复制指针指向的内存区域。如果需要深复制，则需要自行实现这些函数。
一个空的类：

```cpp
class Empty { };
```

实际上等价于：

```cpp
class Empty
{
public:
	Empty();							//默认的空构造函数
	Empty(const Empty&);				//复制构造函数
	Empty(Empty&&);						//c++11，移动构造函数
	~Empty();							//默认的析构函数
	Empty* operator&();					//重载取地址运算符
	const Empty* operator&() const;		//带const的取址运算符
	Empty& operator=(const Empty&);		//重载等号为对象内容复制
	Empty& operator=(Empty&&);			//c++11，重载等号为移动对象
}
```



##继承
C++中的继承分为公有继承`public`、保护继承`protected`以及私有继承`private`，不显式指定继承方式时默认为**私有继承**。
公有继承继承父类的可继承成员的同时并不改变这些成员在子类中的访问权限，但保护继承/私有继承会将继承来的成员限制在子类中的访问权限。
其中公有继承类似于其他高级语言(Java/C#)中的继承，只有公有继承能够表达出其他语言中的继承关系(子类来源于父类)。
私有继承与保护继承的类可以正常实现一些`OOP`特性如`override``虚函数`等，但其子类实例不支持**向上转型**。
C++在发生重写行为时，并**不强制**要求子类的重写函数访问权限要大于等于父类，在发生向上转型时，父类的虚函数如果被子类重写，则调用子类的实现，不受子类的重写函数的访问权限影响(即使子类重写函数是私有的，父类实例一样调用子类重写的实现)。
举例：

```cpp
//代码1，私有继承
#include <iostream>

using namesapce std;

class A
{
public:
	virtual int get() { return 100; }
};

class B : A
{
private:
	int get() { return A::get() + 100; }
};

int main(void)
{
	A *a = new B;		//报错，提示 " 'A' is an inaccessible base of 'B' "
	return 0;
}

//代码2，向上转型访问子类私有实现
#include <iostream>

using namesapce std;

class A
{
public:
	virtual int get() { return 100; }
};

class B : public A
{
private:
	int get() { return A::get() + 100; }
};

int main(void)
{
	A *a = new B;
	cout << a->get() << endl;		//正确，调用子类实现，输出200
	cout << B().get() << endl;		//错误，提示 " within this context "
	return 0;
}
```



##指针加减
在C/C++中，对指针进行加减运算时，并不是直接对地址的大小加上数值得到新的地址，而是原地址加上由`操作数 * 指针所指向的内容的类型大小`得到的偏移量计算出的地址。
举例：

```c
#include <stdio.h>

int main(void)
{
	long *a = (long*)0x1;		//内存地址赋值给指针之前需要进行强制类型转换，否则编译器不知道内存的类型
	printf("%p\n", a + 1);		//打印指针使用%p，会以"0x...."的格式输出
	int b[] = { 1, 2, 3 };
	printf("%d, %d", *(b + 1), *((int*)(&b + 1) - 1));
	return 0;
}
```

输出结果：(gcc 4.9.2 && ArchLinux x86_64)
0x9
2, 3

由例子中不难看出，`a + 1`代表的地址不是简单地将`a`的地址`0x1`加上`1`，而是`a`的地址加上指针所指向的数据类型`long`的大小(8个字节)乘以操作数`1`得到的值`0x9`。
对于数组`b`，单独使用数组名称代表的是数组首元素的地址`&b[0]`，`b + 1`代表的是`b[0]`的下一个元素`b[1]`，而`&b`代表的是整个数组的首地址，虽然二者`b == &b`的值相同，但意义完全不同，`&b + 1`代表的是b的整个数组结束后的下一个位置。

###数组名的含义
对于数组名而言，在`sizeof`和**指针加减**两种操作中分别有不同的含义。
使用`sizeof`操作符时，数组名代表**整个数组**，如果用数组名作为参数，则返回的值为`数组包含的类型的大小 * 数组数量`。
进行地址加减操作时，数组名表示的是数组第一个元素的地址，`数组名 + 1`实际上代表数组第二个元素的地址，而`&数组名`才代表整个数组的**起始地址**，`&数组名 + 1`代表数组**结束**之后的下一个位置。



##C++对象模型
在C++中，没有虚函数的情况下，只有非静态数据成员存储在类内，其它的静态数据成员、静态成员函数、非静态成员函数都存储在全局区，增加这些成员并不会引起类大小的变化。
在有虚函数且多重继承的情况下，多个父类按照其声明顺序依次排列，而每个类的区域内部先是一个虚表指针`vptr`，然后是普通成员变量，子类与第一个继承的父类共用一个虚表，子类的普通成员紧跟在最后一个父类的普通成员之后。
类的成员函数和静态成员变量实际是全局的，因此类的实例中并不包含这些内容，使用`sizeof`计算类的大小时也不会把这些内容计算进去，通过地址访问类的成员进行地址计算时需要忽略这些成员的大小。

###成员函数
- C++中，普通成员函数(包括静态成员函数，但虚函数除外)并不是直接存放在类中的，而是像普通的全局函数一样存放。成员函数在经过C++编译器处理后，函数名会被改写，而函数名就指明了该函数的类归属以及参数信息。
- C++中普通成员函数仅仅是逻辑上存在于类中，成员函数的实际实现并不依赖于类。
- C++中空类的大小为1，但向空类中添加任意个普通成员函数类的大小仍然是1。
- 存在虚函数的情况下，类中会保存有一个虚表指针`vptr`，用于保存类中虚函数的地址，向空类中添加一个虚函数，则类的大小变为单倍指针大小(虚表指针大小)，增加虚函数的个数，类大小不改变。

###虚函数
- C++中只有虚函数才能被子类重写`override`，非虚函数会被子类的同名函数隐藏(无论函数原型是否完全相同)。C++中使用`virtual`关键字定义虚函数，虚函数可以只有函数定义而没有函数实现，没有函数实现的虚函数称为纯虚函数，在C++中使用`= 0`来表示一个虚函数为纯虚函数(类似于Java和C#中的`abstract`方法)。拥有一个或以上纯虚函数的类称为抽象类，抽象类是不能被实例化的，也不能在构造函数的内容中使用，但`C++11`之后可以用在构造函数的初始化序列中。
- 一个函数不能既是虚函数又是静态函数(`static`和`virtual`关键字不能共存)，静态函数是全局的，无需实例化就能被调用，不能够被重写，不能实现向上转型调用子类同名方法实现。
- C++中虚函数是通过一张虚函数表来实现的。类实例的最前位置有一个虚表指针`vptr`，指向一张虚函数表，虚函数表中按声明顺序存放了所有该类的虚成员函数的地址，可以通过该表中的地址调用对应的函数实现。虚函数表的最后位置多加了一个节点作为虚函数表的结束标志，在VS中，结束标志是`NULL`，在`gcc`中用0表示虚函数表结束，用1表示接下来的位置还有别的虚函数表。
- 在单继承的情况无`override`下，子类对象和父类对象的虚函数按照声明顺序出现在虚函数表中，子类的虚函数在表中的位置处于父类虚函数之后。
- 在单继承且向上转型的情况下，如果父类虚函数被子类`override`，则父类对象中的虚函数表中存放的虚函数地址会被替换成子类的对应函数地址，以此来实现运行时多态。
- 在多继承的情况下，子类的对象会按照声明中的顺序生成多个父类虚函数表，子类的成员虚函数被放到了第一个父类虚函数表中。多个虚函数表的之间不是直接相连的，而是按照继承顺序下的该类中的成员内容完全结束之后才会开始下一个类的虚函数表。
举例：

```cpp
#include <iostream>

using namespace std;

class A				//类A有两个虚函数和一个成员变量，由于内存对齐，类A的大小为16(虚表大小8，变量对齐到8)
{
	virtual int get(int);
	virtual int get();
	char a = 'A';
};

class B : A					//单一继承的情况
{
	virtual int get1();
};

class C
{
	char c = 'C';
	virtual int get();
};

class D : A, C				//多重继承的情况
{
	char d = 'D';
	virtual int get2();
};

class E : public A			//单一继承并发生override的情况
{
	int get();
};

int A::get(int)
{
	cout << "A::get(int)" << endl;
	return 0;
}

int A::get()
{
	cout << "A::get()" << endl;
	return 0;
}

int B::get1()
{
	cout << "B::get1()" << endl;
	return 0;
}

int C::get()
{
	cout << "C::get()" << endl;
	return 0;
}

int D::get2()
{
	cout << "D::get2()" << endl;
	return 0;
}

int E::get()
{
	cout << "E::get()" << endl;
	return 0;
}

int main(void)
{
	A *a = new E;
	B b;
	D d;

	//在64bit的Linux中，普通指针的大小为8B，故需要转换为一个占有8个字节的类型来保存内容，否则可能会发生截断
	cout << "调用类A的get(int)函数 ";
	((int (*)())*(long*)*(long*)&d)();
	cout << "调用类A的get()函数 ";
	((int (*)())*((long*)*(long*)&d + 1))();
	cout << "调用类D的get2()函数 ";
	((int (*)())*((long*)*(long*)&d + 2))();
	cout << "类A的变量a的值 " << (char)*((long*)&d + 1) << endl;
	cout << "类C的变量a的值 " << *(char*)((long*)&d + 3) << endl;
	cout << "类D的变量a的值 " << *((char*)((long*)&d + 3) + 1) << endl;		//类D继承于类A和C，D的虚函数添加到了类A虚表的末尾，因而类D中的变量a处于类C中的变量a的下一个位置
	cout << "调用类B的get1()函数 ";
	((int (*)())*((long*)*(long*)&b + 2))();
	cout << "调用类C的get()函数 ";
	((int (*)())*(long*)*((long*)&d + 2))();
	cout << "调用类A的get(int)函数 ";
	((int (*)())*((long*)*(long*)&*a))();
	cout << "向上转型使用A类指针调用类E的get()函数 ";
	((int (*)())*((long*)*(long*)&*a + 1))();
	return 0;
}
```

输出结果：(gcc 4.9.2 && ArchLinux x86_64)
调用类A的get(int)函数 A::get(int)
调用类A的get()函数 A::get()
调用类D的get2()函数 D::get2()
类A的变量a的值 A
类C的变量a的值 C
类D的变量a的值 D
调用类B的get1()函数 B::get1()
调用类C的get()函数 C::get()
调用类A的get(int)函数 A::get(int)
向上转型使用A类指针调用类E的get()函数 E::get()

由结果可知，`D`类继承于`A``C`两个类，生成类两张虚表，`D`的虚函数`get2`的地址保存在`A`的虚函数表中，位于虚函数表的最后一个位置。`A`类的大小为16，`A`类的内容结束后就是`C`的内容，因此`C`的虚表指针地址为`类实例起始地址 + 16`即`&d + 16`，用8个字节的`long`型做转换可以写成`(long*)&d + 2`，而`D`类自己的变量`a`地址位于类`C`结束位置的下一个位置(类`D`的虚函数在`A`末尾，故没有单独虚表)，同时又因为类`D`没有单独的虚表，则根据结构体长度对齐的原则，类`D`的变量`a`会紧接着类`C`的变量`a`，即`(char*)((long*)&d + 3) + 1`。
`E`类继承与`A`，只有一张虚表，通过向上转型得到的实例`a`中，`E`的`get()`重写了父类`A`的虚函数`get()`，`(long*)*(long*)&*a`是虚函数表的首地址，存放是`A`类的第一个成员虚函数`get(int)`，`(long*)*(long*)&*a + 1`是虚函数表中的第二个内容的地址，地址中存放的原本是类A的第二个虚函数`get()`，但在向上转型的实例中，被替换成了子类`E`的`get()`函数的地址。
需要注意的是，在多重继承时，如果继承的多个父类中都有符合子类函数签名的虚函数，则子类会将所有符合条件的虚表中的父类虚函数指针替换成子类的函数指针。
在`VS`中运行此段代码，只会输出前两个结果，因为在`VS`中，多个虚表之间不是直接相连的，在类成员结束之后并未直接开始下一个虚表，而是隔着一些特殊的字段并用0进行填充，不能通过直接加减类实例地址来得到下一个虚表地址。



##默认参数
C++允许在定义函数是给函数的参数设定一个默认值，在调用这个函数时，如果没有给出对应参数的值，就会使用默认的参数值。

- 在调用具有默认参数的函数时，如果使用参数了一个参数的默认值，则其它带有默认值的参数也应该使用默认值，如果不准备使用参数的默认值，则所有带默认值的参数的默认值都不应该被使用。
- 带有默认值的函数参数需要连续出现，即一旦有一个参数开始有默认值，后面的参数都需要有默认值(即带有默认值的参数与无默认值的参数不能够交错出现)。
- 参数的默认值只能在函数的声明或定义的其中一处指定，不能两处都指定。
- 参数默认值在定义中指定时，需要注意定义必须写在该函数被调用前默认参数才能生效，否则依然按照声明中的无默认值格式调用。
- 带有默认参数的函数在定义时需要注意不能与重载函数相冲突。
- 函数默认值只在有函数被常规调用时才有效，如果使用函数指针调用函数则函数默认值无效。

举例：

```cpp
int got(int a = 3);
int got(int a = 3)		//编译报错，默认参数只能出现在定义或是声明中的其中一处
{
	return a;
}
int get(int b = 3, int a)		//编译报错，一旦有一个参数带有默认值，后面的参数都应拥有默认值
{
	return b;
}
int get(int b = 3)
{
	return b;
}
int get()
{
	return a;
}
int main(void)
{
	get();		//编译报错，有两个函数都符合要求。
	int (*p)(int) = got;
	p();		//编译报错，参数过少。
	p(100);		//正常。
	return 0;
}
```



##函数定义嵌套
在C/C++标准中，函数定义必须是完全平行、相互独立的，也就是说函数定义的内部不能嵌套另一个函数的定义。
但是`gcc`扩充了C的语法，在`gcc`中嵌套函数定义是**允许**的行为(只有`gcc`！`clang``clang++``g++`并不允许嵌套函数定义！)
以下的代码在`gcc`中可以顺利编译并得到执行结果：

```c
#include <stdio.h>

int got(int num)
{
	int got(int num)
	{
		return num;
	}
	return got(num);
}

int main(void)
{
	printf("%d\n", got(100));
	return 0;
}
```

输出结果：(gcc 5.1.0 && ArchLinux x86_64)
100

给神一样的`gcc`给跪了。。。。



##左值引用(lvalue reference)和右值引用(rvalue reference)
在C++中，`左值(lvalue)`代表**持久性**的对象，`右值(rvalue)`代表**短暂**的对象，左值可以被**取地址**，右值不能被取地址。
在`C++11`中加入了**右值引用**的概念。

###引用绑定规则
- 非`const`左值引用可以绑定到非`const`左值。
- `const`左值引用可以绑定到任意左值和任意右值(无论是否`const`)。
- 非`const`右值引用可以绑定到非`const`右值。
- `const`右值引用可以绑定到任意右值(无论是否`const`)。

###移动语义(move semantics)
在C++11中，加入了`std::move()`函数来获取一个左值对应的右值。
一个类可以定义移动构造函数来定义以对象右值来构建新对象的方式。
在传统C++中，通过原有对象构建新对象只有一种方式，即**复制构造函数**，复制构造函数的参数为`const Type&`类型，即`const`左值引用，可以绑定任意左值和任意右值，对于左值对象，为了实现真正的对象复制(深复制)，目标对象中的指针是不能直接拷贝的，而是需要重新分配内存，并复制目标对象的指针指向的内容；而对于右值对象，由于右值对象不可改动，理论上可以直接移动目标对象的内容无需重新分配内存，但传统C++没有对这两种情况进行区分，导致对象为右值时，往往也要进行不必要的拷贝行为。
在C++11中，可以自行定义移动构造函数，参数类型为`Type &&`，即移动构造函数接收到的都是右值，目标对象的成员可以安全地进行语义移动操作，指针也可以直接拷贝。
当一个右值被传入构造函数时，会**优先匹配**移动构造函数。

###注意事项
需要注意的是，无论左值引用或是右值引用本身都是左值，因此虽然不能直接对右值取地址，但是可以对右值引用取地址。
引用一但绑定就不可更改，因此引用与指针不同，指针分为指向`const`内容的指针`const 类型名 *指针名`和自身保存地址不可变的`const`指针`类型名* const 指针名`，而引用本身一定是不可变的，因此只有绑定`const`值的引用`const 类型名 &引用名`，而没有真正的`const`引用，`类型名& const 引用名`这样的定义是不被编译器允许的。
举例：

```cpp
const int &a = 1;				//正确，const左值引用可以绑定到右值
int &&b = 1;					//正确，非const右值引用可以绑定到右值
int &x = 1;						//错误，非const左值引用不能绑定到右值
int &x = a;						//错误，非const左值引用不能绑定到const左值
int &x = b;						//正确，非const左值引用可以绑定到非const左值
const int &x = std::move(a);	//正确，const左值引用可以绑定到const右值
const int &x = std::move(b);	//正确，const左值引用可以绑定到非const右值
int &&x = std::move(a);			//错误，非const右值引用不能绑定到const右值
int &&x = std::move(b);			//正确，非const右值引用可以绑定到非const右值
const int &&x = std::move(a);	//正确，const右值引用可以绑定到非const右值
const int &&x = std::move(b);	//正确，const右值引用可以绑定到非const右值
```



##绑定指针的引用
C++中，引用同样可以绑定在指针类型上。
语法格式如下：

```cpp
//左值引用绑定指针
类型名 *&引用名 = 变量名;
类型名* const &引用名 = const右值/非const右值/变量名;

//右值引用绑定指针
类型名 *&&引用名 = 非const右值;
类型名* const &&引用名 = const右值/非const右值;
```

一般来说，带`const`限定的变量可以接收非`const`变量的值，反之则不可。
举例：

```cpp
int a = 0;
const int b = 0;
int *c = &a;
//int *d = &b;				//错误，const变量的地址应该有指向const变量的指针保存
const int *d = &b;
const int *e = &a;			//正确，非const变量的地址也可以由指向const变量的指针保存
int* const f = &a;			//正确，const指针
//int *g = f;				//错误，const指针不能传递给非const指针
const int* const g = f;		//正确，const指针可以传递给指向const变量的const指针

int *&x = c;							//非const左值引用绑定非const指针变量(非const左值)
int *&&x = &a;							//右值引用直接绑定到非const地址(非const右值)
int* const &x = &a;						//const左值引用绑定到非const地址(非const右值)
const int* const &x = std::move(d);		//const左值引用绑定到指向const值的指针的右值，第一个const代表引用绑定的指针所指向的值是带有const的
const int* const &&x = std::move(e);	//const右值引用绑定到指向const值的指针的右值
int* const &&x = std::move(f);			//const右值引用绑定到const指针的右值
const int *&&x = std::move(d);			//非const右值引用绑定到指向const值的指针的右值
const int* const &x = std::move(g);
const int* const &&x = std::move(g);	//对于指向const变量的const指针的右值可以使用const左值引用或const右值引用来绑定，第一个const不能省略！
```



##泛型(模版)
泛型在C++中的实现叫做模版`template`。
C++的模版可以用在类和函数中。当模版用在函数中时，调用模版函数时可以不显式指定模版类型，编译器会根据调用函数的参数类型进行自动推导。此外，不能给一个模版类型指定两种不同的类型。
当模板函数在接收特定参数时如果与已有的普通函数的原型相同，则会优先调用普通函数的实现。
举例：

```cpp
template <class T>
T get(T t, T c)
{
	return t;
}

int main(void)
{
	cout << get<int>(123, 123) << endl;		//正确，显式指定模版函数的模版类型为int
	cout << get(123, 123) << endl;			//正确，根据调用函数时传入的参数推导出模版类型为int
	//cout << get(123, 12.3) << endl;		//错误，没有显式指定模版类型时，对于同一个类型传入模版的参数必须类型完全相同，而get(123, 12.3)会让编译器推导为get(int, double)
	cout << get<int>(123, 12.3) << endl;	//正确，如果在调用模版函数时显式指定了模版类型，则对于同一个模版类型可以使用兼容的参数类型(不一定要完全相同)，编译器会自动进行隐式的强制类型转换
	return 0;
}
```

模版还可以用在类或者类的内部的某个函数中。
当模版用在类中时，则该类在实例化时必须显式指定模版的类型。
当模版用在类内部的某个成员函数中时，带有模版函数的类实例化方式与普通类无异，而该类的成员模版函数使用方式类似于普通模版函数，可以不显式地指定模版类型而让编译器来推导。

###模版的高级用法
- C++的模版能够接收类型形参和部分非类型形参，模版的非类型形参只能是整形、指针和引用，比如`int a`可以作为模版的形参，但`double a``string a`则不可以，而`double *a``string *a`则可以，对象的引用和指针是符合要求的。
- 调用非类型模板形参的实参必须是一个常量表达式，即他必须能在编译时计算出结果。需要注意的是，任何局部对象，局部变量，局部对象的地址，局部变量的地址都不是一个常量表达式，都不能用作非类型模板形参的实参。
- 全局指针类型，全局变量，全局对象也不是一个常量表达式，不能用作非类型模板形参的实参。
- 全局变量的地址或引用，全局对象的地址或引用`const`类型变量是常量表达式，可以用作非类型模板形参的实参。
- `sizeof`表达式的结果是一个常量表达式，也能用作非类型模板形参的实参。
- 模版函数如果使用了非类型形参，则在调用该模版函数时必须显式指定模版实参，因为编译器只能推导模版类型，非类型的模版参数需要显式地指定。

###模版形参默认值
- `C++11`之前可以为模版类的类型形参提供默认值，但不能为模板函数的类型形参提供默认值。模板函数和模板类都可以为模板的非类型形参提供默认值。
- `C++11`之后，无论模版函数或是模版类的类型形参和非类型形参都可以拥有默认值(`g++ 4.9.2``vs 2013`测试通过)。
- 模版形参默认值的用法类似于函数参数形参默认值，即从第一个有默认值的形参开始，之后的形参都应拥有默认值，并且形参默认值在声明或定义只需要出现一处即可。
- 即使一个模版类的所有模版形参都拥有默认值，全部采用默认参数来实例化这个模版类时类名之后依然需要有一对空的尖括号`>`来表示实例化的是一个模版类。

###模板与重载
C++中模板是在编译时根据实例化时使用的类型编译成对应的函数，因此，如果一个模板类成员函数(无论是否静态)在确定了类型之后与原有的成员函数原型发生冲突则在编译时就会报错。同样的，即使模板函数在使用某种类型时可能与已有的函数原型发生冲突，但只要没使用该类型，就能通过编译(全局函数不受此限制，即使模板函数原型与某个普通函数完全相同时，依然可以通过编译)。
举例：(需要`C++1y`支持)

```cpp
template <typename T>
class A
{
public:
	auto get(T, T);
	int get(int, int);
};

template <class T>
auto A<T>::get(T, T)
{
	/*函数体*/
}
```

当`A`类使用`int`型作为模板实例化类型时，就会与原有函数原型发生冲突。
C++作为编译性语言，模板是在编译期实现的，属于编译时多态的一种。

###模版特化
C++支持`模版特化`，即对于特定的模版参数类型可以指定其实现。
如有以下模版类，有两个模版参数`T`和`S`：

```cpp
template <class T, class S>
class Template
{
	/* code */
};
```

可以指定其模版类型为某种类型时的类定义，如需要特化模版皆为参数为`int`型时的类定义可以写成：

```cpp
template <>
class Template<int, int>
{
	/* code */
};
```

特化时显式指定`所有`模版参数的类型被称为`完全特化`，类模版还支持`偏特化`，即只指定一部分的模版类型参数：

```cpp
template <class T>
class Template<T, int>
{
	/* code */
};
```

类`Temp`的后一个模版参数的类型被显式指定为`int`，而模版参数`T`依然由用户指定。
除了`模版类`之外，C++中模版函数也同样支持**模版特化**。
如以下模版函数：

```cpp
template <class T, class S>
T func(T t, S s)
{
	/* code */
}
```

假设需要特化其模版参数全为`int`型，则可以写成：

```cpp
template <>
int func<int, int>(int t, int s)
{
	/* code */
}
```

需要注意的是，模版函数**不支持**`偏特化`，即以下的写法是**不能**通过编译的：

```cpp
template <class T>
T func<T, int>(T t, int s)		//error
{
	/* code */
}
```

C++不允许模版函数偏特化，`偏特化`的模版函数在编译时会报错，提示`error: function template partial specialization is not allowed`。



##Lambda表达式
在`C++11`中引入了`Lambda`表达式，语法格式为：

```cpp
[当前作用域变量捕获方式](参数表) { 函数体; };					//标准形式
[当前作用域变量捕获方式] { 函数体; };							//无需参数的形式
[当前作用域变量捕获方式](参数表) -> 返回类型 { 函数体; };		//显式指定返回值的形式
```

需要注意的是，与普通函数相同，如果需要表达式有返回值则需要在函数体中使用`return`语句返回值。
与Java/C#等语言不同，C++中的`Lambda`**不能**省略参数类型，也不能在函数体只有一句的时候省略函数体外的花括号。

###重复使用一个Lambda
如果需要重复使用一个`Lambda`，可将其定义为函数对象`std::function`：

```cpp
std::function<返回类型(参数表)> 函数对象名 = [当前作用域变量引用方式](参数表) { 函数体; };
```

需要注意的是，函数对象是一个类实例，不是函数指针。
在`C++11`中，不能用函数指针来绑定一个`Lambda`，函数对象也**不能**与函数指针相互转化。
在`C++14`之后，如果一个`Lambda`没有捕获任何变量，则可以与函数指针进行转化。

###在Lambda中捕获当前作用域的变量
- `Lambda`可以捕获当前作用域中的变量，`[=]`表示当前作用域的变量全部取值传递，`[&]`表示当前作用域的变量全部取引用传递。
- 可以只设置需要的变量，并设置不同的传递方式，如`[a, &b, c]`表示变量`a`和`c`为值传递，`b`为引用传递。
- 可以在传递所用变量的基础上分别设定指定变量的传递方式，如`[=, &a]`表示除了`a`之外的变量全部为值传递，`a`为引用传递，而`[&, a]`表示除`a`外的所有变量为引用传递，`a`为值传递。
- 设置全局传递方式的操作符要放在设置单个变量的操作符之前，如`[&a, =]``[b, &]`这样的写法是不被编译器所允许的。
- `Lambda`表达式的参数可以是引用类型或是指针，但作为返回值时不能为引用传递，但依然可以为指针类型。
举例：

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main(void)
{
	int a = 1;
	int b = 2;
	function<int(int, int)> test
		= [=, &a](int x, int y) { return a = x + y + b; };			//图省事可以直接使用auto类型推断
	test(1, 1);
	cout << a << endl;
	return 0;
}
```

输出结果(gcc 5.1.0 && ArchLinux x86_64)：
4

###C++14中的Lambda表达式新特性
- 在`C++14`中，加入了泛型`Lambda`，并支持在`Lambda`使用**表达式**捕获作用域中的变量，且没有捕获变量的`Lambda`可以与函数指针进行转化(不是函数对象)。
- 在`C++11`中，`Lambda`中的参数必须显式指定参数的类型，但在`C++14`中，参数的类型可以使用`auto`关键字，编译器会对所有的被使用的该表达式进行参数类型推断，然后根据使用的参数类型编译出对应的`Lambda`实例。
- 在`C++11`中，对变量的捕获包括值捕获和左值引用捕获两种，而在`C++14`中，`Lambda`中支持使用**表达式**捕获，通过简单的表达式进行一些捕获值初始化`lambda capture initializers`，或是对捕获变量重命名(设置全局传递方式的操作符依然要放在最前面)。
- 在`C++11`中，`Lambda`只能转化为函数对象`std::function`，但在`C++14`中，对于没有捕获变量的`Lambda`，是可以直接转化为原生的函数指针的，`Lambda`与普通函数最大的区别在与`Lamdba`可以获取当前作用域中的变量作为初始化内容，而函数不可以，一旦`Lambda`没有捕获当前作用域中的变量，则该`Lambda`便可以转化为一个普通的函数，即可以由原生的函数指针进行表示。
举例：

```cpp
#include <iostream>

using namespace std;

int main(void)
{
	//泛型Lambda表达式
	auto lambda1 = [](auto num) { return num; };
	cout << "Use int as args: " << lambda1(100) << endl;
	cout << "Use string as args: " << lambda1("string") << endl;

	//Lambda表达式支持表达式捕获
	int a = 100, b = 200, c = 300;
	auto lambda2 = [=, num1 = a + 50, &num2 = b]() { num2 = num1 + c; };	//以捕获值的方式捕获变量a，并用a的值加上50并命名为num1，然后将b的引用命名为num2
	lambda2();
	cout << "After run lambda2, the value b is: " << b << endl;

	//未捕获变量的Lambda可以转化为函数指针
	int (*get_num)(int) = [](int num) { return num; };
	cout << "Run lambda function point:" << get_num(100) << endl;

	return 0;
}
```

输出结果(gcc 5.2.0 && ArchLinux x86_64)：
Use int as args: 100
Use string as args: string
After run lambda2, the value b is: 450
Run lambda function point: 100



##STL容器
容器`Containers`是用来存储和管理数据的数据结构。容器一般分为序列式容器`Sequence Containers`和关联式容器`Associative Containers`。
`STL`中常用的**序列式容器**有`vector(向量)`、`list`(双向链表)、`deque`(双向队列)。
`STL`中常用的**关联式容器**有`set`(集合)、`map`(映射)、`multiset`(多重集合)、`multimap`(多重映射)。
以上的7中容器对象都有以下成员方法：

```cpp
bool empty() const;									//判断容器是否为空
size_type max_size();								//返回容器最大能存储的元素个数
size_type size();									//返回容器中当前已经存储的元素的数量
void swap(contain_type &container);					//交换当前容器对象与container容器对象中的内容
void clear();										//清空容器中的内容
iterator erase(iterator position);					//擦除指定迭代器位置的内容
iterator erase(iterator first, iterator last);		//擦除[first, end)位置的内容
```

###迭代器
各类容器中都内置了迭代器，可通过以下函数创建迭代器：

```cpp
iterator begin();			//返回一个指向首元素的迭代器
iterator end();
iterator rbegin();			//返回一个指向首元素的迭代器，逆序遍历
iterator rend();
```

在`C++11`之后，可以使用新的`std::begin()`和`std::end()`函数来创建迭代器。
以`vector`为例，创建和使用迭代器：

```cpp
vector<int> vector_int;						//创建容器对象
vector<int>::iterator iterator_int;			//创建迭代器对象
iterator_int = vector_int.begin();			//初始化迭代器
iterator_int = std::begin(vector_int);		//c++11风格的迭代器初始化
++iterator_int;								//迭代器向下移动一个位置
--iterator_int;								//迭代器返回上一个位置
*iterator_int;								//取出迭代器在当前位置的内容
cin >> *iterator_int;						//向迭代器指代的位置中输入内容
std::advance(iterator_int, num);			//像iterator_int增加指定的偏移量
```

###序列式容器
序列式容器中元素的次序与元素的值无关，只与元素插入的顺序有关。
序列式容器都有以下常用成员函数：

```cpp
void pop_back();					//删除容器尾部的最后一个元素
void push_back(const T &x);			//在容器尾部添加一个元素
reference front();					//返回容器内首个元素的引用(可以通过此函数修改元素的值)
reference back();					//返回容器最末元素的引用
iterator insert(iterator position, const T& x);
void insert(iterator position, size_type n, const T& x);
template <class InputIterator>
void insert(iterator position, InputIterator first, InputIterator last);
```

序列式容器都提供了以下构造函数，以`vector`为例：

```cpp
vector();
vector(size_type num, const TYPE &val);					//使用num个值为val的元素初始化vector
vector(const vector &from);
vector(input_iterator start, input_iterator end);		//使用某个已存在的vector的[start, end)来构建一个新的vector
```

####*vector容器特点*
`vector`容器是数组式的容器类型，`vector`容器中存储的数据元素被放在一块连续的内存中，`vector`容器支持**随机存取**，可以通过数组式的下标(即`[]`操作符)进行元素访问、修改。
`vector`容器虽然支持`insert()`等函数来进行插入操作，但由于内部采用线性结构，因而`insert()`函数在头部或是中间插入元素时需要进行大量复制操作，插入效率很低，在执行头部、中部删除元素操作时也同样效率低。

####*list容器特点*
`list`容器采用**双向链表**实现，`list`容器存储的元素所处的内存空间不连续，由于链表的特性，元素之间是通过指针相连的，因而`list`容器在任意位置插入和删除元素时效率都很高，但`list`容器并**不支持**随机存取，不能使用`[]`操作符访问元素，同时相比`vector`容器消耗的内存更多。
`list`容器有着一些`vector`没有的方法，比如`pop_front()``push_front(const T &x)``remove(const T &value)`等，使用`remove()`方法可以移除容器中所有值为`value`的元素。

####*deque容器特点*
`deque`容器为双向队列，兼顾了`list`和`vector`的优点，能够方便地增加、删除元素，也能够使用`[]`操作符随机存取元素，但缺点是需要消耗较高的内存。

###关联式容器
关联式容器通过键值`key`来存取元素，元素次序与插入顺序**无关**。
关联式容器**不提供**`front()``back()``push_front/push_back(const T&)``pop_front/pop_back()`之类的操作。
关联式容器可以进行比较，需要定义`<`操作符，所有作为关联式容器`key`的类型都必须重载`<`运算符，其它操作符不作要求。
关联式容器提供`clear()`和`erase()`函数，但返回值为`void`而不是下一个元素的迭代器。

####*set/multiset容器特点*
`set/multiset`容器保存键值，对应数学概念中的`集合`。`set/multiset`的实现采用的平衡二叉搜索树，插入、查询、删除等操作时间复杂度均为O(lgN)。`set`不允许重复值，但`multiset`允许重复值。

####*map/multimap容器特点*
`map/multimap`容器同时保存键值和实际值，每一个元素都是一个`pair<key, value>`类型。
`map`容器不允许相同键值`key`的元素，但`multimap`允许。`map`容器可以使用数组下标形式(`[]`操作符)来获取指定键值的元素中的实际值，`multimap`由于键值可以重复，一个键值可以对应多个实际值，因而不能采用下标的形式获取实际值。
`pair`类型中有两个成员，`first`和`second`，分别保存键值和实际数据，通过访问`first`和`second`两个成员可以获取键值和实际数据。
使用`find()`函数可以查找某个键值，返回一个迭代器，通过遍历该迭代器可以获取某个键值的所有对应值。
还可以通过`lower_bound()``upper_bound()`等函数获取迭代器，用于遍历元素，与`STL`的迭代器相同，`lower_bound()`返回指向参数键值的第一个元素位置的迭代器，而`upper_bound()`返回指向参数键值最后一个元素的下一个元素位置的迭代器。

####*注意事项*
- 对于`map`等关联式容器来说，键值如果为指针类型，则将指针的值(指针包含的地址)作为键值，而非指针所指向的内容。因而两个内容相同的不同数组对`map`而言就是两个不同的键值。
- 不是所有的类型都可以作为键值，能够作为键值的类型必须重载了`<`运算符，否则会出现编译错误：
`二进制“<”: 没有找到接受“xxx”类型的左操作数的运算符(或没有可接受的转换)`
一些类型已经默认重载了`<`运算符如`std::string``QString`等，可以直接作为`key`使用。



##智能指针(Smart Pointer)
C++中除了手动使用`new``delete`操作符来进行动态内存管理之外，还可以使用智能指针管理动态内存，使用智能指针管理的动态内存会在不被需要时自动释放。
`boost`库中提供了六种智能指针用来管理动态内存，分别是`shared_ptr``shared_array``scoped_ptr``scoped_array``weak_ptr``intrusive_ptr`，定义在`/usr/include/boost/smart_ptr/`路径下对应名称的头文件中。
在`C++11`中，`boost`库中的`shared_ptr``weak_ptr`被纳入了标准库，定义在`/usr/include/c++/版本号/memory`头文件中。
`C++11`之前，标准库中可以使用`auto_ptr`智能指针，在`C++11`之后，标准库中增添了`shared_ptr``unique_ptr``weak_ptr`等智能指针。原先的`auto_ptr`已经不推荐使用。
需要注意的是，`boost`库与标准库中的同名类是不能相互转换的(即`std::shared_ptr`不能转换为`boost::shared_ptr`)。

###智能指针的一般性用法
智能指针重载了`->`操作符，使开发者可以使用此操作符访问智能指针保存的对象的公有成员，对于智能指针自身的成员，依然使用`.`操作符访问。
以`auto_ptr`为例：

```cpp
auto_ptr<T> point;					//创建一个空的、尚未初始化的动态指针
auto_ptr<T> point(new T(args));		//创建智能指针对象并开辟内存进行初始化，无参数时调用默认的构造函数
auto_ptr<T> point(T *t);			//由指针t所指向的动态内存绑定到智能指针(如果t为空指针，则智能指针绑定空内容)
point->...							//访问智能指针指向的动态内存对象的公有成员
point.reset();						//重置智能指针
point.release();					//释放掉智能指针指向的动态内存
```

###标准库中的各类智能指针特性
`std::auto_ptr`(过时)中一块动态内存只能绑定一个`auto_ptr`，如果将一个绑定了动态内存的`auto_ptr`复制给另一个`auto_ptr`则动态内存的所有权会被转移到新的auto_ptr上，旧的auto_ptr不再指向原先的动态内存。
`std::unique_ptr`来自于`boost::scoped_ptr`，类似于`auto_ptr`，但`unique_ptr`的限制更多，一块动态内存只能绑定一个`unique_ptr`，同时`unique_ptr`不能进行复制。
`std::shared_ptr`来自于`boost::shared_ptr`，基于**引用计数**的共享智能指针。一块动态内存可以被多个`shared_ptr`绑定，每增加一个智能指针的绑定，则引用计数加1，当引用计数为0时释放指向的动态内存，shared_ptr的内存管理完全交由编译器完成，不能手动释放`shared_ptr`管理的动态内存(没有`release()`成员函数)。`shared_ptr`可以使用`make_shared<T>(args)`函数进行构造。使用`reset()`成员函数会将当前智能指针管理的动态内存引用计数减1，如果引用计数为0则释放动态内存。`shared_ptr`的`reset()`成员函数可以带有参数，参数可以是`new`构造函数或是对象指针，作用是将原先的托管对象引用计数减1然后管理新的对象(新对象引用计数加1)。
`std::weak_ptr`来自于`boost::weak_ptr`，为了解决`shared_ptr`中的**循环引用**问题而引入的**弱引用**智能指针，`weak_ptr`不能单独绑定一块动态内存(即不能新建动态内存初始化`weak_ptr`)，而是由`shared_ptr`转化而来。`weak_ptr`可以使用构造函数与`shared_ptr`相互转换(即以已有的`shared_ptr`对象为参数构造`weak_ptr`对象)，一块动态内存被`weak_ptr`智能指针绑定或是绑定该动态内存的`weak_ptr`被销毁不会增加/减少原有的`shared_ptr`的引用计数。
`shared_ptr`和`weak_ptr`都没有`release()`成员函数，即不能手动释放动态内存。`weak_ptr`不能直接调用指向对象的成员函数，调用指向对象的成员函数之前需要先使用`weak_ptr`自身的`lock()`方法将自身转变为`shared_ptr`，然后再调用指向对象的成员函数。

###智能指针的转型
C++的类型转换函数`dynamic_cast<>()``static_cast<>()``const_cast<>()`并**不能**用于智能指针对象的转换，智能指针实际是一个包含了指针的容器对象，并不能简单地转换为普通指针类型。
将智能指针对象进行转型需要使用`dynamic_pointer_cast<>()``static_pointer_cast<>()``const_pointer_cast<>()`，其中的模版参数为目标对象的类型(不是指针类型)。

###改变做为形参传入的智能指针所指向的内容
当智能指针做为形参时，如果需要改变指针指向的内容，则需要像普通指针一样，将新的内容赋值到`*智能指针对象`上(此项操作需要智能指针已被初始化且被分配了足够的内存)。
如果智能指针是`shared_ptr`，则还需要考虑到智能指针保存内容的生命周期。
如果传入的是一个尚未初始化的智能指针，需要在函数内对其进行赋值，而还要保证外部能使用这个指针，此时则需要传递智能指针的引用或地址，保证函数内部能访问到原始的智能指针，否则进行的操作都是对形参复制的智能指针进行的，不会改变外部的智能指针未被初始化的状态。
例如：

```cpp
#include <iostream>
#include <memory>
#include <stdio.h>

using namespace std;

void init(shared_ptr<int> temp)		//如果需要函数改变传入的未初始化的智能指针，正确的方法是传入引用或是传入智能指针的地址(指针)
{
	shared_ptr<int> num(new int);
	*num = 100;
	temp = num;
}

int main(void)
{
	shared_ptr<int> temp;
	init(temp);
	cout << *temp << endl;			//错误，运行init()函数之后，外部的智能指针temp实际上并未发生变化，依然处于未初始化状态，试图访问其内容会报错
	system("pause");
	return 0;
}
```

输出结果(VS 2015 && Windows10 x86_64)：
报错，提示访问空指针(0x0000000)。



##std::bind()
`C++11`中引入该函数，来源于`boost::bind()`，作用是通过设定原有函数的某些参数值为固定值来生成具有新参数表的函数(类似python中的偏函数)，`bind()`本质上是一个`call_adapter`。
`bind()`既可以绑定当前类的成员函数，也可以绑定全局函数/静态函数或是其他类的具有访问权限的成员函数。

###bind()绑定普通函数

```cpp
bind(func_name, args...);
```

`bind()`用于绑定一般的函数(可直接访问的函数，比如全局函数，其他类的可访问静态成员函数)时第一个参数为需要绑定的函数名，后面的参数为绑定函数的参数表，可以向参数表中加入对应类型的常量，不需要绑定常量的参数可以用参数占位符`std::placeholders::_1``std::placeholders::_2`...或者`boost::_1``boost::_2`...)替代。

###bind()绑定非静态成员函数

```cpp
bind(class_name::func_name, 对象实例/对象指针/智能指针, args...);
```

`bind()`用于绑定非静态成员函数时，需要通过类实例进行访问，第二个参数需要为绑定函数所在类的实例、指针或是智能指针。
`bind()`绑定当前类的成员函数可以直接传递`this`指针。
实例代码：

```cpp
#include <iostream>
#include <functional>
#include <memory>

using namespace std;

int get0(int a)
{
	return a;
}

class A
{
public:
	A(int num) : num(num) {};
	int get(int, int);
	int num;
};

int A::get(int a, int b)
{
	return num = a;
}

int main(void)
{
	A a1(888);
	A *a2 = new A(888);
	shared_ptr<A> a3 = make_shared<A>(888);

	function<int()> p0 = bind(get0, 100);
	function<int(int)> p1 = bind(A::get, a1, 1, placeholders::_1);
	function<int(int)> p2 = bind(A::get, a2, 2, placeholders::_1);
	auto p3 = bind(A::get, a3, 3, placeholders::_1);
	auto p4 = bind(A::get, ref(a1), 1, placeholders::_1);

	cout << p0() << endl;
	cout << p1(0) << " p1()调用后num的值：";
	cout << a1.num << endl;
	cout << p2(0) << " p2()调用后num的值：";
	cout << a2->num << endl;
	cout << p3(0) << " p3()调用后num的值：";
	cout << a3->num << endl;
	cout << p4(0) << " p4()调用后num的值：";
	cout << a1.num << endl;

	delete a2;

	return 0;
}
```

输出结果：(gcc 5.1.0 && ArchLinux x86_64)
100
1 p1()调用后num的值：888
2 p2()调用后num的值：2
3 p3()调用后num的值：3
1 p4()调用后num的值：1

可以看到，将类实例作为参数进行绑定的时候，对类实例进行的是值传递，即复制一个类对象，因此调用`bind()`生成之后的函数对象不会对原先的类实例进行修改(但传递类指针、类智能指针的时候，只是复制对象地址，类内存是同一块，因此修改会同步)，如果需要在`bind()`是进行对象引用传递，则可以使用`std::ref()``std::cref()`函数。



##信号/槽(boost::signals2)
使用`boost`库中的`signals2`可以实现近似C#中**委托**的效果，使用`signals2`需要包含头文件`/usr/include/boost/signals2.hpp`。
`boost`库中的`boost::signals2`相比原先的`boost::signals`而言是**线程安全**的，原先的`boost::signals`现在已被废弃。

###定义信号
定义信号使用`boost::signals2::signal<>`，该类是一个模板类，模板参数为需要连接的函数的函数原型。
例如需要连接的函数的原型为`void func(int, int)`，则定义信号时应该写成`boost::signals2::signal<void(int, int)>`。
需要注意的是`boost::signals2::signal`是不可复制的类型。

###连接槽函数
连接槽函数使用`connect()`成员函数，该函数有两个重载，定义如下：

```cpp
connection connect(const slot_type &slot, connect_position position = at_back);
connection connect(const group_type &group, const slot_type &slot, connect_position position = at_back);
```

####*连接槽函数时改变签名*
被连接的槽函数必须要符合信号定义时的模板参数中的函数原型，必须函数原型参数个数完全相同且类型兼容(由于绑定槽函数时是传递槽函数的地址，因此函数默认参数被忽略，因而参数个数必须完全相同)，如果需要绑定的函数参数表与信号定义的参数表数目不同，可以采用`std::bind()`生成具有新参数表的函数进行连接。
如果需要连接的槽函数为一个类的非静态成员函数，则也需要通过`std::bind()`将非静态成员函数绑定一个类实例之后再进行连接，否则会连接失败(没有实例无法访问非静态成员函数)。
如果被连接的槽函数有多个重载，则需要进行强制类型转换来转换为无歧义函数指针才能进行连接。

####*connect组别*
使用`connect()`函数的第二个重载进行槽函数连接时，可以在第一个参数的位置设置槽函数的组别，组别可以是一个整型数值(可以为负数)，不同组别之间的槽函数按照组号由小到大的顺序执行。

####*connect优先级*
`connect()`成员函数的最后一个参数用于设定槽函数的组内优先级，默认情况下取值为`boost::signals2::at_back`，多个槽函数连接时返回值为最后一个连接的槽函数的返回值，需要优先执行的槽函数可以设定为`boost::signals2::at_front`。

###取消连接
取消连接使用`disconnect()`成员函数，该函数有两个重载，定义如下：

```cpp
void disconnect(const group_type &group);		//断开指定组别的所有槽的连接
void disconnect(const T &slot);					//断开指定槽
```

还可以一次性断开所有槽：

```cpp
void disconnect_all_slots();
```

需要注意的是，每次连接槽函数成功之后都会返回一个`boost::signals2::connection`对象，通过调用该对象的`disconnect()`函数也能实现指定槽函数连接的断开。

###获取信号返回值
信号的返回值是由合并器`combiner`管理的，在定义信号对象时，会调用`boost`默认的合并器类管理返回值，如果需要使用自定义合成器类，则定义需要写成`boost::signals2::signal<func(type), combiner<type>>`。
定义完信号之后，可以像调用普通函数一样调用信号对象，所有被信号连接的槽函数都将会被触发(重载`()`操作符)，同时返回的一个合并器类的对象。默认的合并器类只保存最后一次被触发的槽函数的返回值，使用`*`操作符或是`value()`成员函数可以获得合并器中保存的值。
实例代码

```cpp
#include <boost/signals2.hpp>
#include <iostream>

using namespace std;

class A
{
public:
	boost::signals2::signal<int(int)> sig;
};

class B
{
public:
	int slot1(int, char);
	int slot1(int, int, int);
	int slot2(double, int);
};

int B::slot1(int, char)
{
	cout << "This is slot1(int, char)." << endl;
	return 100;
}

int B::slot1(int, int, int)
{
	cout << "This is slot1(int, int, int)." << endl;
	return 200;
}

int B::slot2(double, int)
{
	cout << "This is slot2." << endl;
	return 300;
}

int main(void)
{
	A a;
	B b;
	a.sig.connect(1, boost::bind(&B::slot1, b, _1, 'a'));
	boost::signals2::connection link =
		a.sig.connect(1, boost::bind(&B::slot1, b, _1, 1, 2), boost::signals2::at_front);
	a.sig.connect(2, boost::bind(&B::slot2, b, 1.0, _1));
	cout << *a.sig(0) << endl;
	cout << "\nDisconnect slot1(int, int, int)." << endl;
	link.disconnect();						//取消槽函数slot1(int, int, int)的连接
	cout << a.sig(1).value() << endl;		//调用value()成员函数获取合并器返回值
	return 0;
}
```

输出结果：(gcc 5.1.0 && ArchLinux x86_64)：
This is slot1(int, int, int).
This is slot1(int, char).
This is slot2.
300

Disconnect slot1(int, int, int).
This is slot1(int, char).
This is slot2.
300



##boost时间库
`boost`时间库提供了跨平台的时间解决方案，相关头文件为`/usr/include/boost/date_time/posix_time/posix_time.hpp`。

###获取当前时间
使用`boost::posix_time::second_clock/microsec_clock::universal_time()`可以获取当前`UTC`时间的秒数/微秒数。
使用`boost::posix_time::second_clock/microsec_clock::local_time()`可以获取当前本地时间的秒数/微秒数。
获取的时间使用`boost::posix_time::ptime`类型保存。
使用`boost::posix_time::to_iso_string()`可以以获取的`boost::posix_time::ptime`作为参数，然后输出为标准的字符串`std::string`来表示时间。
获取时间间隔
`boost::posix_time::ptime`类重载了减号，两个`boost::posix_time::ptime`对象可以相减得到类型为`boost::posix_time::time_duration`的时间间隔。
`boost::posix_time::time_duration`可以使用`total_microseconds()``total_milliseconds()``total_nanoseconds()``total_seconds()`分别获取时间间隔对应的微秒/毫秒/纳秒/秒等作为单位的时间表示。



##C/C++中一些编码中遇到的错误

###关于 _multiple definition of"(多重定义)_ 错误
在一个头文件中定义一个全局变量，如果这个头文件被多次包含，就会出现多重定义错误，即使你在头文件的定义中正确地使用了`ifndef``define``endif`宏。
正确的定义全局变量的方法是将定义写在代码文件中，然后在头文件里用`extern`关键字添加声明即可。
`ifndef define endif`宏只能保证编辑阶段代码段不被重复包含，然而变量定义是对每个源文件都有效的，这些源文件编译得到的目标文件里每一个都含有该变量的定义，编译时不会报错，但当这些目标文件连接时，多个目标文件的定义就会产生多重定义冲突。
在C++中，如果全局变量是定义在某个命名空间中的，则在代码文件中的定义和头文件中的带`extern`关键字的声明都要写在名字相同的命名空间中(命名空间不能加`external`关键字！)。
举例：

```cpp
//头文件 xxx.h
namesapce A
{
	extern int a;
}

//代码文件 xxx.cc
namespace A
{
	int a = 0;
}
```

###关于在switch的case语句中定义局部变量
在C语言中，不允许在`switch`的`case`语句内直接定义局部变量，以下语句是错误的：

```cpp
int a = 0;
switch (a)
{
case 0:
	int b = 0;
	break;
}
```

无法通过编译，C语言编译器会提示`crosses initialization of 'int b'`。
以上语句在C++编译器中也会给出同样的错误。
但是C++中允许另一种写法：

```cpp
int a = 0;
switch (a)
{
case 0:
	int b;
	b = 0;
	break;
}
```

将定义与赋值拆开可以通过C++编译器，但依旧会在C编译器中报错。
出现此种情况是因为在C/C++中，`case`标签不具有独立的作用域，同时在不使用`break`语句的情况下，`case`标签中的变量定义语句根据传入值的不同不一定会被执行，变量不一定会被定义，因而在C/C++中不允许这样的行为。
正确的做法是在需要在`case`标签内容中定义变量时使用`{}`来构建一个独立作用域，使变量定义对其它`case`标签不可见，如下所示：

```cpp
int a = 0;
switch (a)
{
case 0:
	{
		int b = 0;
		break;
	}
}
```

以上代码可以在C/C++编译器中编译通过。



##常用的C标准库函数

###memset()
初始化内存块常使用`memset()`函数，函数定义为：

```c
#include <string.h>
void* memset(void *s, int c, size_t n);
```

作用是将指针`s`所指向的区域的前`n`位用`ASC`码值`c`填充。
注意`c`的取值为`ASC`码值，即如果`c`取`0`，则指针`s`所指向的区域的前`n`为全部用空白填充(相当于全是`\0`)，如果`c`取`49`,则相当于用数字`1`来填充，依此类推。

###strcpy()
复制字符数组常用`strcpy()`函数，函数定义为：

```c
#include <string.h>
char *stpcpy(char *restrict s1, const char *restrict s2);
```

将指针`s2`指向的内容复制到`s1`指向的区域。
函数返回指针复制内容后的指针`s1`，返回值的作用是使该函数能够更连贯地用于表达式。



##一些关键字、特殊值的含义/用法

###explicit关键字
C++中的关键字`explicit`作用是防止构造函数隐式转换的发生。
默认情况下，在C++中，使用`类名 实例名 = 参数`的形式创建一个类的实例，当`参数`刚好符合类的构造函数参数要求，此时编译器会隐式的调用这个类的构造函数来创建类的实例。但有些情况下，我们需要避免这种隐式转换的发生，这时，在类的构造函数声明时，在在构造函数名之前加上`explicit`关键字即可避免隐式转换发生。
采用`explicit`关键字声明的构造函数只能够被显式地调用。

###restrict关键字
`C99`中新引入了关键字`restrict`，`restrict`关键字用在指针的定义中，格式为`变量类型* restrict 指针名`，作用是是告知编译器该指针始终指向首次初始化时的内容，不会发生改变。
`restrict`关键字不会改变指针的用法，但会让编译器更加安全高效准确地优化代码，使用`restrict`关键字定义的指针的指向不应进行改动。
`restrict`关键字只在支持`C99`以上的C编译器中使用，C++**没有**引入这个关键字。

###mutable关键字
`mutable`关键字用于定义一个易变的变量，只能用于修饰类的非静态数据成员，语法格式上与`const`类似。
一般成员变量在`const`修饰的成员函数中是不可被更改的，但使用了`mutable`关键字定义的变量，即使是在`const`成员函数中，依然可以被修改。
C语言没有这个关键字。

###using关键字
`using`用于简化处于命名空间中的内容的使用。如：

```cpp
using namespace std;
using std::string;
using namespace 命名空间名称;
using 命名空间名称::类型名称/变量名称;
```

`using`用于定义类型的别名(类似于`typedef`)。如：

```cpp
using List = std::list<int>;			//等价于 typedef class std::list<int> List;
using point = int (*a)(int, int);
```

`using`用于定义模板类型的部分有参别名(`typedef`不能定义部分参数化的泛型类型)。如：

```cpp
template <class T>
using Map = std::map<int, T>;
```

`using`用于在子类隐藏了父类的函数时，使子类能够使用父类原先被隐藏的函数。如：

```cpp
using 父类类名::被隐藏函数的函数名;
```

###移位运算符
移位运算符的作用是将一个数的对应二进制值左移或右移指定的位数。

```cpp
int a = 1;
int b = a << 10;			//b = 1024
int c = b >> 5;				//c = 32
```

`a`的二进制值也是1，将十进制的1的二进制值左移10位则结果为`1 * 2 ^ 10`，即1024。
1024的二进制值右移5位结果为`1 * 2 ^ 5`，即32。

###npos成员
多数C++标准容器都提供了`npos`成员，`npos`用来表示不会被取到的下标，类型为`容器类型::size_type`，一般取值为-1(在不同编译系统中可能不同)。
使用容器提供的`find()`成员函数查找内容时，如果目标内容没有被找到，则返回`容器类型::npos`。