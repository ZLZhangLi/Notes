[TOC]

## *Swing* 简介
`Swing`是`Java`平台下的传统`GUI`库。  
`Swing`是`Java`标准库的一部分，包含于`Java SE`中。

与上代图形技术`AWT`的比较：

- `AWT`使用各平台原生控件，在各平台上的原生控件上做了基础的封装。
- `Swing`控件完全由`Java`绘制。
- `AWT`控件因平台而异，相同控件在各`OS`中表现不尽相同。
- `Swing`控件在各`OS`下具有统一的外观样式与功能。
- `AWT`使用原生控件，执行效率高。
- `Swing`使用自绘控件，执行效率低下(在现代版本的`Java`中已有较大改善)。

### *Scala Swing*
`Scala`标准库中提供了`Java Swing`对应的`Scala API`封装。

在`sbt`项目中添加`Scala Swing`库：

```scala
libraryDependencies += "org.scala-lang.modules" %% "scala-swing" % "版本号"
```



## 常用控件
`Java Swing`提供的控件位于`javax.swing`包路径下，命名均以字母`J`起始。

`Scala Swing`对`Java Swing`提供的多数控件进行了浅层的封装，使之更符合`Scala`的`API`风格。  
`Scala Swing`控件位于`scala.swing`路径下，名称为对应的`Java Swing`控件去掉首字母`J`。

容器类控件：

| Java Swing 控件名称 | Scala Swing 控件名称 | 控件简介 |
|:-------------------|:-------------------|:--------|
| JFrame | Frame | 顶层窗体控件 |
| JDialog | Dialog | 对话框窗体 |
| JPanel | Panel | 面板 |
| JScrollPane | ScrollPane | 滚动面板 |

`JFrame/Frame`一般做为顶层容器，可以独立做为对话框显示，但`JPanel/Panel`不能独立做为对话框。

文本控件：

| Java Swing 控件名称 | Scala Swing 控件名称 | 控件简介 |
|:-------------------|:-------------------|:--------|
| JLabel | Label | 文本标签 |
| JTextField | TextField | 单行文本框 |
| JTextArea | TextArea | 多行文本框 |
| JPasswordField | PasswordField | 密码文本框(可设定回显字符) |

按钮控件：

| Java Swing 控件名称 | Scala Swing 控件名称 | 控件简介 |
|:-------------------|:-------------------|:--------|
| JButton | Button | 普通按钮 |
| JCheckBox | CheckBox | 复选框 |
| JRadioButton | RadioButton | 单选框 |
| JComboBox | ComboBox | 组合框(下拉列表框) |

多个`JRadioButton/RadioButton`需要添加到同一个`ButtonGroup`中才能实现**单选**效果。

菜单栏：

| Java Swing 控件名称 | Scala Swing 控件名称 | 控件简介 |
|:-------------------|:-------------------|:--------|
| JMenubar | Menubar | 菜单栏 |
| JMenu | Menu | 菜单栏上的按钮 |
| JMenuItem | MenuItem | 点击菜单按钮弹出的菜单项 |

常用的表单组件都有对应的菜单版本，比如`JRadioButtonMenuItem`、`JCheckBoxMenuItem`等。
向`JMenu`中`add()`菜单项时，虽然可以选择普通组件，但普通组件不能触发菜单效果(点按之后菜单不收回)。



## *Border*
`javax.swing.border.Border`类型定义了边框的接口。

### 设置边框
常见**GUI容器**类如`JFrame`、`JPanel`等都可以通过`setBorder()`方法来设置边框：

```java
public void setBorder(Border border);
```

### *BorderFactory*
工厂类`BorderFactory`提供了一系列创建各类常见样式边框的静态方法。

*EmptyBorder*
> `EmptyBorder`为仅占据面板空间的透明边框。  
> 通过使用`EmptyBorder`，可以实现控制控件边界空隙的效果(类似于**CSS**中的`Margin`属性)。
>
> 创建`EmptyBorder`的静态方法：
>
>	```java
>	// 创建默认样式的 EmptyBorder
>	public static Border createEmptyBorder();
>	// 创建指定边距的 EmptyBorder
>	public static Border createEmptyBorder(int top, int left, int bottom, int right);
>	```

*TitledBorder*
> `TitledBorder`为框线上带有标题的边框。  
> `Swing`中并未提供默认的`GroupBox`控件，但可以对`JPanel`等控件设定`TitledBorder`来实现类似效果。
>
> 创建`EmptyBorder`的静态方法：
>
>	```java
>	public static TitledBorder createTitledBorder(Border border, String title,
>			int titleJustification, int titlePosition, Font titleFont, Color titleColor);
>	```



## *JTextArea*
`JTextField`只能用来显示简单的**单行文本**，涉及到**多行文本**的复杂情况，需要使用到`JTextArea`控件：

```java
JTextArea textArea = new JTextArea();
```

可以设置文本域**自动换行**：

```java
textArea.setLineWrap(true);
```

当文本域内容太多无法全部显示时，可以使用`JScrollPane`控件，将文本域添加到其中：

```java
JScrollPane scrollPane = new JScrollPane(textArea);
```

当文本无法全部显示时会出现**滚动条**。



## *MessageBox*
与**Qt**类似，`Swing`也提供了弹出`MessageBox`的静态方法，即`JOptionPane.showMessageDialog()`。

```java
// 调出标题为"Message"的信息消息对话框
static void showMessageDialog(Component parentComponent, Object message);
// 调出对话框，显示使用由messageType参数确定的默认图标的message
static void showMessageDialog(Component parentComponent,
		Object message, String title, int messageType);
// 调出一个显示信息的对话框，指定了所有参数
static void showMessageDialog(Component parentComponent,
		Object message, String title, int messageType, Icon icon);
```

- `parentComponent`参数为父对话框。
- `messageType`参数控制对话框的内置按钮，可取值`DEFAULT_OPTION`、`YES_NO_OPTION`等。
- `message`参数为在对话框中显示的消息内容。

使用`showInputDialog()`、`showConfirmDialog()`等方法可以用于显示其他用途的窗口，参数类似。



## 事件机制
`Java`**没有**类似`C#`的语言级别事件机制。

`Java Swing`的事件机制采用`Observer`模式。  
`Scala Swing`在事件处理上采用了`Reactor`模式，与`Java Swing`风格不同。

### *Java Swing* 事件机制
`Java Swing`的事件机制主要包括以下部分：

- 监听器，包含对事件的处理逻辑。
- 事件源，即触发事件的控件。
- 事件，包含特定的事件信息。

监听器
> 所有的的监听源都实现了`java.util.EventListener`接口。  
> `EventListener`接口是空接口，`Java Swing`根据不同的事件类型定义了一系列继承于`EventListener`的子接口。
>
> 不同的监听器接口定义了不同的抽象方法，当对应的监听事件触发时，对应方法会被调用。  
> 通过重写监听器接口的抽象方法来实现事件处理逻辑。

事件源
> 事件源是某个具体的控件对象。  
> 控件对象通过绑定监听器对象在事件触发时调用对应监听器对象的重写方法。
>
> `Java Swing`中的控件都提供了命名类似的方法用于与监听器交互：
>
>	```java
>	// 绑定到指定监听器实例
>	public synchronized void addXxxListener(XxxListener listener);
>	// 移除到指定监听器实例的绑定
>	public synchronized void removeXxxListener(XxxListener listener);
>	// 获取当前控件已绑定的所有监听器实例
>	public synchronized XxxListener[] getXxxListeners();
>	```
>
> 不同的控件类型根据其控件职能会拥有不同类型监听器的交互方法。

事件
> 所有的事件都继承自`java.util.EventObject`。
>
> 事件保存了具体的某一次事件发生时的事件信息。
> 事件做为监听器抽象方法的参数，当事件触发时，对应的事件信息做为参数传入。

以按钮点按事件为例，实现按钮点按事件的处理需要以下步骤：

1. 构建点按事件的监听器，监听器实现`ActionListener`接口，重写抽象方法`actionPerformed()`。
2. 按钮控件对象调用`addActionListener()`方法，将控件绑定监听器。

如下代码所示：

```java
// 构建监听器，ActionListener只有单个抽象方法，为函数式接口
ActionListener act = e -> ...;

JButton btn = new JButton();

// 将控件绑定监听器
btn.addActionListener(act);
```

常见监听器类型应用
> *KeyListener* (键盘按键监听器)  
> 通过键盘监听器可屏蔽指定按键输入。
>
> 实现`KeyListener`接口，重写`keyTyped(KeyEvent)`方法。  
> 通过`KeyEvent`类型的`getKeyChar()`方法获取输入的字符，判断输入内容，对需要屏蔽的输入使用`setKeyChar('\0')`转化为空输入。
>
> 如下所示：(只接受数字输入)
>
>	```java
>	KeyListener keyListener = e -> {
>		if (e.getKeyChar() < '0' || e.getKeyChar() > '9') e.setKeyChar('\0');
>	}
>	```



## *MVC*
`Swing`中的组件采用了`MVC`的设计模式，对于`JList`、`JComboBox`、`JTable`等控件均可通过组装`Model`构建对象并显示内容。

### *ComboBox*
获取目标`Map`的`Key`集合：

```java
Set set = map.keySet();
```

接着将集合转化为对象数组：

```java
Object[] object = set.toArray();
```

接着构造一个用对象数组初始化的`DefaultComboBoxModel`对象，并以此构建`JComoBox`对象：

```java
JComboBox comboBox = new JComboBox(new DefaultComboBoxModel(object));
```

### *JTable*
构建一个`JTable`主要有两种方式：

```java
JTable(Object[][] rowData, Object[] columnNames);
JTable(TableModel dm);
```

即使用`Object数组`确定表格模型或是使用`TableModel`类构建表格模型。  
使用对象数组构建表格模型可以先从数组库中读取对应数据，然后将数据存储在对象数组中。

使用`TableModel`类的基本步骤：

1. 构建`TableMode`对象。
1. 使用`TableMode`类的成员方法`setValueAt(Object aValue, int rowIndex, int columnIndex)`设定表格模型每个位置的数据。
1. 在`JTable`使用构造函数或在已有的`JTable`实例调用`setModel(TableModel dataModel)`成员方法创建表格。