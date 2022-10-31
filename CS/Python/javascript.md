# Javascript    --动态网页制作的需要而诞生的一种新的编程语言。客户机上执行的描述性语言
	JS ==> 主流框架：YUI ,Dojo，Prototype，jQuery
	Ajax是结合了XML以及JavaScript等的交互数据传输技术。 组合技术：Java、JS、CSS、XML
	jQuery 是一个快速、简洁的javascript库，方便的为网站提供Ajax交互；集成了JS和Ajax
----
- 引用
	在html里面使用 一般放到 body 最后，将所有html标签加载完再执行javascript
- 直接标签
	<script> ... 
	</script>
- 文件引用
	<script src="/path/to/file.js"></script>
----
- 组成    --面向对象
	- 核心（ECMAScript）
	- DOM 文档对象模型（Document Object Model，简称DOM）
	- BOM 浏览器对象模型（Browser Object Model，简称BOM）
- 对象    --继承自 object
	- ECMA对象 => { native object-ECMA; host object-DOM、BOM }   本地、宿主
	- DOM对象    --document.write()
	- BOM对象  --window.alert()
	Object 原生类 => ToString()、 ValueOf()

- ECMAScript 核心    --标准
	 "use strict";      代码首句，表示在严格条件下执行即不能使用未声明的变量
	 语法、类型、语句、关键字、保留字、运算符、对象
	 自定义js文件的时候，封装到IIFE立即执行函数表达式中，可以隔绝全局变量的互相影响，函数中的全局变量可以声明为局部形式
	 $.extend(funcname: function(){   调用自定义js中的函数   })
	- 注释   //    /*  */
	- 变量   --不区分类型， 类型+驼峰式命名
		- let a=10,b ;   --var亦可以，不加声明则为全局变量
			const  a    --为常量，有操作函数接口来改变内容，但是直接赋值就会报错；类似封装
			a = value    --不加前缀为全局变量
				 window.a = window["a"]   都是全局变量的声明方法
		- 输出
			- alert()           --弹窗，阻塞式
			- document.write()    --输出到网页，支持html代码
			- console.log()    --浏览器console
	- 函数    --代码编译、加载->执行、同名覆盖；编译装载{声明、调用} 与  边编译边执行  区别；JS函数、变量声明会提升到作用域的顶部， 变量的值为undefined
		- for (let i=1;i<=9;i++){setTimeout(function timer() {console.log(i);},1000);}    
			函数作用域问题，var不能传递进内层函数，但是let可以，用let声明的变量传入到 for循环体的块作用域生效后，不会发生改变，不受外界的影响； 或者直接显式传递进入
			js默认：函数 -> 全局作用域； 添加let实现块级
					js的函数在调用之前，*作用域链就已经存在*；即在声明的时候就存在，js隐式创建变量并赋值undefined
			let - 块级，无变量提升-一定要先声明（暂时性死区）；
		- *function* funcname() { ... }
		- 匿名函数无法直接执行，因为是声明,无法直接调用 ； 加上运算符就可以直接执行
			 在匿名函数前面加上运算符，把一个函数声明语句变成了一个函数表达式，=> 
																										IIFE（Imdiately Invoked Function Expression 立即执行的函数表达式）
			 !function(){alert('iifksp')}()
	- 数据类型
		java和js => 堆、栈内存  -  {基本、引用数据类型}
			- 栈内存 - 基本数据类型 int、str、对象地址
			- 堆内存 - 引用数据类型 对象实际存储、地址指向
		- 基本
			- Number 数字 {整型、浮点型}  => 0 为八进制、0x 为十六进制、b 二进制、NaN
			- String - unicode - \转义 - 运算转换时优先级最高
				- 字符串转换成数字时 --> NaN，属于Number，但是谁都不是，除了!=之外的比较的结果全为false
			- Boolean - true/false - if/while (){}else{}  ==> true=1, false=0 python和js一样
			- Null - 空对象，占一个对象位置 - null ==>false
			- Undefined - 值只有undefind - 系统自动处理声明未赋值的情况
				- 函数
					- parseInt() 截取整数，只要在前面有满足的部分，后面的无所谓如 3.14abhj
					- parseFloat()
					- eval()    --字符串强制转换为表达式并返回结果
					- typeof()
		- 引用    --对象
			- object - new object()
				- null也是对象占位
				- 数据对象=> { "":"", "":""}    --json， 输出为[object Object], 类似字典，
	- 运算符
		- 算数
			- + - * / %
			- x++, ++x; x--, --x
			- =-x = 负运算； =+x => 正不会改变原数据的正负，负数会改变；两个都会转换成number类型
		- 逻辑    --NaN只有!=为true    ==> true=1、false=0; null=undefined
			- ==、!=、>、>=、<、<=
			- ===、!===    --全等于，不同于==的预先数据类型转换，===不做任何转换直接比较
			- &&、||、!    -- True && obj = obj
			- <<、>>    --二进制移位运算
			- &、|    --两值逻辑运算
			- null => false 空
		- 关系
			- 25<"3"  为false，有数字时则全转换为number再比较；字符串比较的是ASCII码，ASCII码中 大写  <  小写
	- 控制语句
		- if(){}else if{}else{}
		- switch     --可以使用列表高效替换
				switch (变量):
					case 值: 语句; break；    --break则直接跳出，无break则在满足条件之后，后面的所有语句都会执行直到break或者结束
					case 值: 语句; break;
					...
					default: 语句;            --无对应case则执行该语句
		- for      --配合写html代码， Hi
				for(初始化;条件;增量){}              --与C++的相同  
				for(let i in a){  alert(a[i]);  }    --与python的有区别
		- while
				while(){  }
	- 异常处理
		-  try { throw new Error("xxx") } catch (e) {} finally {}
	- 对象    --除了null和undefined之外全部属于对象
		- 内置对象类： Array、String、Date、Math、Boolean、Number、Function、Global、Error、RegExp、Object
		- 自定义对象： var = { key:value, key:value, }
		- Function对象    --区分大小写
			- function func_name(){ ...; return  } 
			- var func_name = new Function("arg1", "arg2", "func_code")    --，实例化创建方法，全为字符串
			- var func_name； func_name= function () {  }    --匿名函数赋值
			- (function(args){})("args")    --真正的匿名函数，定义直接执行
			- 属性
				- length    --参数个数
			- 方法
				- void()    --将参数的值置为undefined，不想要某个函数的返回值时，则直接void(func())
				- typeof()    --判断类型，只能判断基本数据类型，对于引用类型，只能显示为object  (new 创建的基本类型也识别不了)
				- instanceof运算 => var instanceof object  => boolean
			- 特性    --定义的时候可以不用写参数，不报错，使用arguments处理
				- 参数不对应的时候不会报错，func_name做为变量指向函数对象地址，可以被覆盖，覆盖之后则变成指向其他的对象
				- 调用函数的不定长参数    --arguments对象，调用函数时传入的参数会存入该对象，列表格式
					arguments[] = 所有的参数
					length  => 返回参数个数
		- String
			- 属性
				- length
				- 遍历-列表格式
			- 方法    --生成新字符串，不影响远原来的
				-------编排
				- italics()
				- bold()
				- anchor("")    --锚
				-------大小写
				- toUpperCase()
				- toLowerCase()
				-------指定字符
				- charAt(int)
				- charCodeAt(int)    --指定字符的ASCII
				- indexOf("")    --第一个
				- lastIndexOf("")    --最后一个
				-------查询字符
				- match()     --所有匹配的索引值，数组Array格式
				- search("")     --第一个索引值
				- replace("ori", "targ")     --完全匹配
					 正则表达式匹配 /pattern/g            --g表示全局
					 分组匹配提取+函数处理
					 "content".replace(/\{(\w+)\}/g, function(m_string, value){})     --m_string表示匹配的字符串，value为分组的值
				- split("")
				- 上面的四个都支持正则  (/reg/gi) 或 reg_obj；返回结果放到数组里
				- concat("")    --s和“”拼接
				-------截取
				- substr(position,len)
				- substring(start,end-1)    --切片
				- slice(start,end-1)     --与上同，但是end-1可为负数，倒着取
				-------自定义方法
				- String.prototype.funcname = function(arg){   this  }     --this为调用该函数的字符串；实现类似python的format
		- Array    --对于python中的列表
			- 创建    --可变长，创建是指定初始长度
				- arr = [1, 2, 3]
				- new Array(1,2,3, "", name)    --参数长度不限制
					- new Array(int)    --表示创建长度为int的Array， 但是其值为undefined；但是仍然可以变长，中间未赋值为undefined
			- 方法
				- arr.join("")    --将数组内的元素使用参数拼接； python - "".join([str1, str2])
				---栈操作   先入后出
				- shift()     
				- unshift()  添加  --操作底端/头部数据
				- pop()
				- push("")    --pop、push 操作入口端/尾部数据
				---排序 改变原数组
				- sort(comparefunc)    --按字符串比较排序
				- reverse()
				---
				- concat()
				- toString()
		- Date
			- 创建
				- let date_obj = new Date()    --无参数，为创建时时间； 
					- 参数     -- /非严格分隔符
						"xxxx/xx/xx xx:xx"    -具体时间
						int    --1970/01/01 
				- 
			- 方法
				- toLocalString()    --格式化返回当地标准时间
				- getxxxx()    --获取指定信息 FullYear、Month、Date 天、Day 周几周日起 、Hours、Minutes、Seconds、MilliSeconds
				- getTimeZoneOffset()    --返回时区差距的分钟数，相邻时区差60分钟
				- setxxxx()    --设定
		- RegExp    --正则，前端验证 + 后端验证
			- 创建
				- var reg_obj = new RegExp("reg", "mode")； reg_obj.test("strings"); 返回True或False
					- mode {g-全局、i-忽略大小写}
				- var reg = /reg/mode   ==> /^/d{3}$/gi
			- 方法
				- test(targ)    --返回true或false
				- 获取结果：配合string的match-所有匹配内容、search-第一个匹配索引值、replace、split
		- Math     --无须实例化
			- 方法
				- Math.random()     --返回0-1的随机数
				- Math.round()     --返回四舍五入的值；  floor()   下舍入
				- pow(x,y)      --x的y次方
				- abs-绝对值、exp-e的指数运算、log-e为底对数、max、min、sin、sqrt-数的平方根、tan
		- BOM     --浏览器相关、窗口
			- window
				- alert()    --窗口弹出方式显示参数内容,只有确认
				- confirm()    --弹出确认窗口，确认 or 取消； 有返回值 True or False
				- prompt()    --文本输入提示框，带确认 or 取消； 返回值为输入的文本 or null
				---------
				- setInterval(func_name, timeinterval毫秒)    --函数周期性执行，该函数返回一个ID，提供给clearInterval()使用
				- clearInterval(ID)    --清空定时器
				- setTimeout(func_name, timeout毫秒)     --设置单次延时运行, 该函数返回一个ID
				- clearTimeout(ID)      --清空，如果在timeout之前取消则不会执行
				- history    --browser的浏览历史相关window子对象，返回前进
					- length
					- forward()    加载 history 列表中的下一个 URL ; history.go(1)
					- back()    加载 history 列表中的前一个 URL ； history.go(-1)  ; 0 为当前页面
					- go()    加载 history 列表中的某个具体页面
			- location
				- href    --链接
				- reload()    --重载，location.reload()  全部刷新
		- DOM      --HTML\XML DOM 尽皆节点； 文档树-节点层级结构；可以在浏览器console中获取节点信息
			- Node of DOM 
				Node节点对象  =>  document文档对象、element标签对象、    text文本对象、attribute属性对象、comment注释对象
					- 自身属性：attributes、nodeType、nodeValue、nodeName、innerHTML-节点的html文本、innerText-纯文本
					- 导航属性：parentNode、firstChild、lastChild、childNodes
											text算作child，如html之中的换行、缩进；实际使用较少； 但parentNode使用方便
					- 推荐导航：parentNode、parentElement
											firstElementChild、lastElementChild、children
											nextElementSibling、previousElementSibling
											===加上element，限制只对element层级导航
				- element对象定位    --调用对象、限定范围
					- 全局    --document.      在文档树中
						- getElementById("")    --获取对应id的标签 tar_tag.value = "" ; 设置属性
						- getElementsByTagName()    --标签类型名
						- getElementsByClassName()    --获取到同class的多个，返回为Array
						- getElementsByName()    --name属性
					- 局部    --全局获取到的element继续调用定位方法
						-	TagName、ClassName
						- ByName  局部查找不可以，也不常用
						- ById 全局和局部没有区别，故局部该方法不可用，只能document.
				- 节点操作    --先定位、再操作
					- 增    --定位、创建、插入
						- document.createElement(tagname)     --创建元素 .属性 - DHTML， 即是直接 标签名.属性 动态绑定设置；
						- 父Node.appendChild();     --将元素添加
					- 删    --找到需要删除的node、其父node
						- 定位需要删除的node
						- 父node.removeChild()
					- 属性修改
						- setAttribute(name, value)
						- getAttribute(name)
						- class属性    --添加删除响应的style对应的class
							- className    --属性
							- classList.  
								- add("")
								- remove("")
			- Event of DOM
				事件，触发-操作系统监听  on...
				- 事件函数参数    -- “函数(event)”   
					- event    --event是系统实例化的，直接使用；调用相关属性
						- keyCode
						- screenX/Y     --鼠标的位置
					- this    --事件绑定的node对象
				- 绑定事件    --标签属性
					- 标签栏 - 属性直接设定
					- 动态绑定-script区域 - 获取标签tag; tag.on.. = function(){}  ;   分离，标准格式化
						- 传参数     tag.onchange = function () { realFunc(this); } 
						- this 在动态绑定里面可以直接使用， 非动态绑定要自己传递并定义接收参数
				- 事件延伸及阻止
					- 子元素会触发其重叠父元素的事件
					- 阻止：子元素触发函数里面添加 e.stopPropagation(); 语句就阻止其触发父元素的事件
				- 常用事件
					- onclick    --单击
					- ondblclick    --双击
					- onfocus     --元素获得焦点，输入框
					- onblur    --元素失去焦点，应用场景：用于表单验证,用户离开某个输入框时,代表已经输入完了,我们可以对它进行验证
					- onchange    --域的内容被改变，应用场景：通常用于表单元素select,当元素内容被改变时触发.（三级联动
													值变化，时区焦点
					- oninput      --input框检测到输入时；输入框的值发生变化之后，立即触发事件 =>html5 ,只能用on绑定
														$("").on( "input" ,)
					- onkeydown    --某个键盘按键被按下，应用场景: 当用户在最后一个输入框按下回车按键时,表单提交
						- event对象属性-keyCode， 事件函数传递实参数为event， 使用event.keyCode来判别按键
					- onkeyup     --某个键盘按键被松开
					- onkeypress    --某个键盘按键被按下并松开
					- onload      --一张页面或一幅图像完成加载时触发
						- window.onload = function(){}; 指定在window加载完之后再执行，可以把script放到加载之前
						- $(function(){ ... })
					- onmousedown     --鼠标按钮被按下
					- onmouseup     --鼠标按钮松开
					- onmousemove    --鼠标被移动
					- onmouseover    --鼠标进入某元素，触发一次   --jQuery  hover(funcin, funcout) = mouseover + leave
					- onmouseout    --鼠标从某元素移开，鼠标指针离开被选元素还是任何子元素，都会触发 mouseout 事件
					- onmouseleave    --鼠标从元素离开，只有在鼠标指针离开被选元素时，才会触发 mouseleave 事件
					- onselect      --标签的文本被选中
					- onsubmit      -- onsubmit="return check()" 只能绑定到form表单，在确认提交的时候触发；用于前端发送前验证； 
																			绑定的check可返回True/False；False 等价于 event.preventDefault() 不提交
																			使用获取标签绑定则可以直接赋值给onsubmit = function(){ return }
					- onscroll    --滑轮滚动, $(window).scroll()
				- 实例
				- 模态对话框
					背景失焦，弹窗聚焦
					三层：背景、蒙版-opacity、弹窗
					- 原理
						蒙版和弹窗共用class属性，默认 .hidden{display:none}；事件绑定函数操作蒙版和弹窗的class属性值，删除hide或添加
				- 二级联动选择框
					- JS动态创建省级select-> option 数据；{创建option、 赋值、添加为子元素}
					- 初始化市级option：provinceBox.options[provinceBox.selectedIndex].innerText 初始省名，provinceData索引
					- 获取省级选中的option：this.options[this.selectedIndex].innerText ；
					- 根据获取到的省级选项修改市级option项， {清空strictBox.options.length = 0、创建添加}
- jQuery    --简洁、兼容性；是一个快速、简洁的javascript库，方便的为网站提供Ajax交互；集成了JS和Ajax
	中小型企业、DOM是根本
	Dom -> jQuery  : obj = document.getElementById()   ->   $(obj)
	jQuery -> Dom  : $("")  -> 
															$("")[0]
														select应用：$("")[0].selectedOptions[0].innerHTML
	操作html元素以及CSS实现动态
	- jQuery库文件引入    --引入之后正常在<script></script> 标签里写js代码
		<script src="/path/to/file.js"></script>
	- jQuery对象    --通过jQuery包装DOM对象后产生的对象，$变量名 做为标示jQuery对象
		- $(selector).action()     --语法，更好的定位elemnet
		- 循环遍历函数  $.each(targetdata, function(arg1,arg2){  })     ==> return 直接跳出循环
			- 应用于选择器结果为多值数组 $("").each{ 多啦符(this) } ; this为当前element对象
			- arg1 为遍历对象的索引值， arg2 为遍历对象对应的值
	- 选择器 -	$("")   "#menu a[attr="value"]"  定位menu下attr属性值为value的a标签
		$(this)   可以将element直接传入,转换成jQuery对象使用
		- 基本选择器    --css选择器
			- *、#id、.class、element、.class,p,div
		- 层级选择器
			- .outer div、 .outer>div、.outer+div 毗邻、.outer~div 下面的兄弟
		- 属性选择器   [] []  可多个
			- [attr="value"]
		- 表单选择器    
			- [type='text'] = :text = input:checkbox    --只适用于form下的input标签的type属性
	- 筛选器
		- 基本筛选器    ：
			- tag：    -- $("li:")、索引值
				- :even   :odd    索引的奇偶
				-	first、last、even、lt(i) 小于、gt(i) 大于、eq(i) 等于
				 另外冒号后面接的是可以在页面上用鼠标改变的状态值
					input，checked，select，radio
		- 过滤筛选器     --函数调用
			- $("li").eq(2)
			- $("li").first()    last()
			- $("ul li").hasclass("test")
		- 查找筛选器
			- children(".test") 子层、find("") 后代、filter() 遍历
			- sibling
				- siblings()
				- next()、nextAll()、nextUntil()  不包含  
				- prev()、prevAll()、prevUntil()    --获取到的列表索引和查找顺序有关
			- parent()、parents()、parentUntil()  层级回溯-单个
	- 方法
		- 原始方法
			- each  =>  
				- $.each(data, function(){})
				- $("").each(func(){})
		- 自定义方法   -自定义方法使用原始调用
			- $.extend( {funcName:function(arg){},} )    --extend({键：值})   ==>多个  
								$.funcName() 调用
			- $.fn.extend(funcName:function(arg){})    --具体对象调用
								$("").funcName() 调用
			- 实际使用
			(function($){
					$.extend(funcName:function(){});
				})(jQuery)      --匿名函数调用声明扩展函数， 将变量、扩展函数 都封装在匿名函数作用域中，不影响其他的扩展函数
	- 操作元素
		- 属性
			- text()、html()、val()、empty()、remove()   --> 加参数则为修改, value属性
			- attr("name")、attr("", "") 修改、removeAttr("")    --自定义特性、onclick 或 自定义附加属性
			- prop("")、prop("", "")    --固有属性
			- addClass()、removeClass()
		- CSS
			- css("{color:'red',backgroud:'blue'}")   |   css("","")
			- offset().top | left    --标签到文档的距离，滑轮滚动只会改变其与窗口的距离
			- position()     --获取匹配元素相对父元素的偏移，top 和 left
			- scrollTop()、scrollLeft()    --滚轮滚动距离，直接调用，不需要jQery对象
				- $(window).scrollTop()    --浏览器窗口的滑动条，窗口大小不够
					滑轮判断窗口聚焦：  $(this).offset().top - scrollTop() < 0 && 
															$(this).offset().top + this.height() - scrollTop() > 0
			- height()  width()    --自身高、宽度 => window 窗口对象、 "html" 或 $(document) 文档对象
																			窗口 + 滑轮 = 文档
			- innerHeight()
			- outerHeight()    --包含边框，默认false不计算margin， 如果为true则计算margin
		- 文档
			- 内部插入    --子级
				- $("#c1").append("<b>hello</b>")    
				- $("p").appendTo(jQuery对象)    
				- prepend()    prependTo()    --同是子级，默认尾部接上，pre则为首部插入
			- 外部插入     --同级
				- before()  insertBefore()  after()  insertAfter()
				- replaceWith()  empty()-清空内容
				- clone()    remove()-全部删除
		- 事件     --DOM去掉on成函数，加载完html元素才能使用
			- 直接原事件函数绑定    --可多个 $("ul li").click()
				- $(document).ready(function(){}) -->  onload
				=	$(function(){})  --documenr的onload事件
				- $("p").click(function(){})
			- bind函数绑定    --不常用，不能动态委托
				unbind函数
				- $("p").bind("click",function(){})
			- on函数    --委托，父元素对所有后代元素（包括新增）的事件委托，应用于动态新增的子元素事件绑定
				off函数
				- $("ul").on("事件",["li过滤"],[data], function(arg){})      --对ul下的所有满足条件的li
					- data => {key:value,}   传入参数
					- arg.data.key  调用
				- $("ul").delegate("li","click",function(){})    --废弃
		- 动画效果    --display： none
			- show、hide、toggle( int , function)    --参数为加载时间
			- fadeIn、fadeOut、fadeToggle( int ,function)、fadeTo(int, opacity) 会影响其他    --淡入淡出
			- slideDown、slideUp、slideToggle( int, function)     --滑出滑入
			-   (	 int, 回调函数)  => 在动画完成后执行回调函数
	- 实例
		- 拖动面板
			- mouseover - cursor
			- mousedown - 获取鼠标、父元素的位置, on mousemmove
				- mousemove - 父元素终位置 = 原位置 + 鼠标位移
				- mouseup - off mousemove
			- $(this).mouseover(function(){}).mousedown(function(){})    --对象同级复用
		- 动画效果
			- show(int)、 hide(int)    --display:none ； 显示和隐藏，参数为加载时间，动画效果
			- toggle(int)      --reverse 同时具有show和hide
		- 轮播图
			- 图片层叠
			- i = index = $(this).index();    --当前元素的索引值
			- $(".num li").eq(i).addClass("current").siblings().removeClass("current");
			- $(".image li").eq(i).stop().fadeIn(1000).siblings().stop().fadeOut(1000);

- AJAX   --技术，Asynchronous Javascript And XML 异步js和XML； 可独立传输到相应url并处理，更新局部html元素内容
	基于 JS/jQuery 的AJAX ； 前端处理数据提交； 某一个输入框的onblur事件绑定，获取value传到后端判断再返回，更新隐藏元素内容
	默认不能跨域请求，通过jsonp实现跨域
	- Django相关
		- 判断 request.is_ajax()
		- @csrf_exempt 处理函数前加 装饰器  禁止数据提交时csrf验证
	- 特点    --搜索未输入完时推荐搜索关键字， 注册时自动检测用户名; 
		- 异步交互传输数据到服务器，无中断 - JSON数据 -> 服务端的请求对象
		- 浏览器页面局部刷新   --某一个元素div数据变化, 用户体验
		缺点： 同步交互配合、服务器压力大、js实现导致浏览器兼容(创建核心对象方式不同)
	- 一个核心类 + 四步操作
		> 核心对象创建
			> 使用核心对象打开与服务器的连接 - open(请求方式, url, 是否同步bool)     --默认异步
			> 发送请求 - send(请求体)
			> 注册监听，监听服务器响应
		- 核心对象创建 
			- xmlhttp = new XMLHttpRequest() 类实例
											ActiveXObject("Msxm12.XMLHTTP") => IE6 ; ActiveXObject("Microsoft.XMLHTTP") => IE5.5 earlier
				- 属性
					-	readyState    --四步准备阶段代码，值为0 - 创建、1 - open、2 - send、3 - 开始读取服务器响应、4 - 读取结束 
					- on            --事件
						 readystatechange      状态监听
						 abort
						 error
						 load
						 loadstart/loadend
						 progress
						 timeout
					- status    --状态码，数字
					- responseText/responseXML    --响应内容
				- 函数
					- open、send
					- setRequestHeader()    --("","") ; {"":"", "":""}
		- 连接
			- xmlhttp.open(请求方式，url，是否同步)
		- 发送
			- xmlhttp.send( 请求体内容 )    --GET请求 send(null)
		- 注册监听对象事件
			- 事件：onreadystatechange
		let xmlhttp = new XMLHttpRequest();
		xmlhttp.onreadystatechange = function () {      --推荐创建之后立即监听
				if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
						let recv_data = xmlhttp.responseText;
						alert(recv_data);
				}
		}
		xmlhttp.open("GET", "/blog/ajax_data/", true);
		xmlhttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");    --默认*/*
		xmlhttp.send(null)      --post请求传递的则在send函数, "var=value"的格式
	- json     --js的原生对象  { "":"", } 格式的字符串即为json对象
		js自创建JSON类
		- 数据类型
			- object   {}    ==> dic["key"]
			- array    []
			- string   ""
			- number   x
			- boolean  true/false
			-          null
		- 方法
			- JSON.parse(data)
			- JSON.stringify(data)
	- 转换
			- JS   -> JSON.parse(data)
			- python -> json模块转换 dumps/loads

	- jQuery 实现ajax
		创建、open、send 封装在一起，返回值直接传递到回调函数
		返回值后端创建class， 使用 对象.__dic__生成字典，再djson.dumps()返回到前端
		location.href = ""   实现页面跳转
		- $.ajax( "url", {} )     --最底层的封装，多参数，参数字典
			- 参数    { : , : }   or  "url", { : , : } obj
			- url
			- type      --交互方式string， GET/POST, PUT/DELETE较少
			- headers:{"":""}    --请求头添加，django-> HTTP_大写名； 本质是xhr.setRequestHeader("","")
				 $.ajaxSetup({     //ajax请求统一整体配置， 不用每次都配置
						beforeSend: function(xhr, settings){ xhr.setRequestHeader() }
					})
			- data: { : , : }    --json对象或字符串 , 返回的数据存在同名变量可以直接传递 $("#id").seralize()
				 配合form表单使用时，获取表单下input标签数据的快捷方式：
					 form表单设置 id 属性 => $("#id").seralize()  生成字典; 当select为多选时，会嵌套列表需要使用tradition: true
			- processData    --声明当前的data数据是否进行转码或预处理，默认为true，即预处理; 如果为false则不处理，转而将数据
												 封装成json对象再调用toString()方法得到一个［object，Object］形式的结果；
												 当data是一个dom结构或者xml数据、二进制文件数据 时，则不需要处理
			- contentType    --告诉浏览器传递过的文件类型，默认"application/x-www-form-urlencoded" ，可使用application/json，
												 则data为JSON.stringify({ a:22, b:33 })；必须是json字符串，不能是json对象
			- datatype       --预期服务器返回的数据类型，根据这个值解析后，传递给回调函数{xml|json|html|jsonp|script|text}
			- dataFilter     --函数，给 Ajax返回的原始数据的进行预处理的函数
			- traditional    --data数据有数组时会用到c:["x","y"], traditional为true则不会深层次取，默认false深层次导致c 为空
				 涉及提交多选select标签的数据时
			- beforeSend     --前处理函数， function(jqXHR, arg2); 发送请求前可修改 XMLHttpRequest 对象的函数，如添加自定义 HTTP 头
			- 回调函数    --第一个参数为后台返回值，可任意命名
				- success        --函数，200成功时的回调函数function(data)
				- error          --函数，失败时；function (jqXHR, status, err)   请求状态
				- complete       --请求完成时，function (jqXHR, Status)
				- statusCode: {     --字典 { '403': function }
									'403': function (jqXHR, textStatus, err) {},
									'400': function () {}
									}
			- jsonp相关   --datdaType必须为相应的jsonp      ?jsonp值=jsonCallback值    与ajax无关，动态创建、删除script标签
				浏览器的同源策略,静态文件的获取不受限，src属性不遵循，script标签去请求并获取到约定好的数据，然后将script标签删除
				- jsonp      --str， 参数，函数名的索引键
				- jsonpCallback      --str， 参数值=函数名
				回调函数名缺省 - 配合success回调函数
				$.ajax({
						url:"http://127.0.0.1:8002/get_byjsonp",
						dataType:"jsonp",            //必须有，告诉server，这次访问要的是一个jsonp的结果。
						jsonp: 'callback',          //jQuery帮助随机生成的：callback="xxxx"
						success:function(data){      // data = xxxx(args)
								...提取出args传递给需要的函数 或 直接处理
						}
				})；
		- $.get(url, [datadict], [callback], [type])  --type是告诉服务器需要返回的数据类型，如果返回不符合视为失败；
			- $.getJSON()   --get:type = Json
			- $.getScript(url, data, callback)    --默认方式加载js文件会全部直接加载，该方式为ajax动态加载
		- $.post()      --参数同上
			- callback回调函数，调用者执行成功后执行， 可使用匿名函数function(data, stateText, object)
				- 参数为
					- data -> server传回的数据；server根据datatype传回 ， HttpResponse(data)
										 打印 arguments 变量查看参数具体信息
					- stateText -> success/Error
					- jqXHR -> jquery包装的XMLHttpRequest对象
		- 跨域    --相对于同源https://ip:port   协议+域名/ip+port
			url中缺省源信息
			- 浏览器的同源策略
				- 不同源的客户端脚本(javascript、ActionScript)在没明确授权的情况下，不能读写对方的资源、信息
			- jsonp       --JSON with Padding，跨域读取数据； 原理相似于 JSON数据填充进回调函数做参数
				<script src="" type="text/javascript"></script>   重要的是获取所需的信息做为参数
				HTML中的src属性可实现跨域；条件 - 提供接口，接口是使用jsonp实现，数据请求为GET
				原理：  创建标签 + 跨域获取{传递函数-异源封装返回}
					 类似于script>src的返回内容， 即前端定义好相应函数cdreq()，然后发起跨站请求获取到响应的内容为cdreq(args);
					 将参数-需要的信息和前端函数名以函数调用方式同时返回。即跨站获取 参数 + 相关本地函数名，存到JS代码块
				- src
					源/uri?callback=      --通过callback传递前端需要执行的函数
				- jQuery框架实现    --在url的后面必须添加一个callback参数，这样getJSON方法才会知道是用JSONP方式去访问服务
					- $.getJSON("源/uri?callback=funcName")
					- $.getJSON("源/uri?callback=?",function(arg){  })    --自动生成函数名并绑定
				- $.ajax()  参数实现 jsonp、jsonpCallback
		- 上传文件    
			 dropzone js插件； request.FILES.get("file")  获取文件对象
			<input type="file" id="filebut" name="xx">    --都需要input 文件标签选择文件
			- form    --上传需要页面刷新 
				添加 <form action="" method="" enctype="multipart/form-data">        enctype不会将文件放到POST中而是FILES
				file_obj = request.FILES.get("xx")    --获取文件对象  .name ; .size ; .chunks()
				with open("", "") as f:
						for chunk in file_obj.chunks():
								f.write(chunk)
			- ajax     xmlHttpRequest;  依赖于FormData对象
				- FormData 对象     --承载字符串 和 文件; 做为ajax传输数据
					dict = new FormData()      --dict.append("k", "v")     { "k":"v", }
					dict.append("fileTag", document.getElementById("filebut").files[0])      --files[0] 
					- xmlHttpRequest  可以成功
					- jQuery 默认不能成功；会对数据预处理，加上
								processData: false,
								contentType: false,
			- 基于form和iframe实现ajax请求    --兼容性，FormData有的不支持; iframe中预览
				jsonp 动态创建script获取参数信息，然后删除。    --返回  函数名(*args)    执行
				- iframe标签配合form    --form提交后，后台的返回数据显示在iframe中
					<form action="" method="POST" target="iframer" enctype="multipart/form-data">
							<iframe name="iframer" src=""></iframe>    --display: none; 内部是文档， 绑定 onload、change 事件
							<input type="file" name="xx"/>
							<input type="submit" />
					</form>
				- 获取iframe内容    --后端返回的内容被包装在 iframe -> document -> html -> body
					$("iframe").contents().find("body").text()    --获取到iframe中文档内的body中的text值
		- 瀑布流ajax  --滚轮到底继续加载图片; 
			 滚动条滑动高度 = 文档高度 - 窗口高度 =>$(window).scrollTop =  (documen).height() - (window).height()
		$(function(){
				initImg()
				---------
				let scrollImgInst = new ScrollImg()
				scrollImgInst.initImg();
				scrollImgInst.scrollEvent; 
				---------
			});
			------------全局变量方式不好，将全局变量封装
			initId = 0
			lastPosition = 3    --解决每次从第一列开始导致排序缺口的问题,列数-1
			------------限定 函数作用域限制 创建类
			function ScrollImg(){
						this.lastPosition = 3;
						this.initId = 0;
						this.initImg = initImg;   --最好直接封装在里面
						this.scrollEvent = scrollEvent;
						//内部函数访问类中的变量需要this重命名，let this = ScrollImgCls； 变量式传递，内部变量找不到往上早
			}
			--------------
			
			function initImg(){
				$.ajax({
						url: "",
						type: GET,
						data: {initId:initId},
						dataType: "JSON",
						success: function(arg){
								let img_list=arg.data;
								$.each(img_list, function(index, value){
										数组记录每一列的高度使用absolute 来便宜图片
										container --> img
								}
						})
			}
			function scrollEvent(){
				$(window).scroll(function(){
						let docuHeight = $(documnet).height();
						let winHeight = $(window).height();
						let scrollHeight = $(window).scrollTop()
						if (winHeight + scrollHeight == docHeight){
								initImg()
						}
						})
			}
			
