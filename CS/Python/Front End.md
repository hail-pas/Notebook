# 前端
----
## HTML    --超文本标记语言，web开发中做为模版  => html、tpl、chtml
- 组成    --标签<></>  => 注释 <!--  <></>  -->
	- 根HTML
			|
			|---head （编码、解析）
			|    |
			|    |--meta
			|    |--title
			|    |--link
			|    |--script
			|
			|--- body （显示）
						|
						|--hi
						|--div
						|--p
						|--hr    自闭合结束标签
- 属性
	- 位置-开始或自闭合  => <tag_name attr="value" content="width=device-width, initial-scale=1.0">
	- 键值对形式 attr="value"  => attrname 等于 value 时可只写attrname
	- 特殊属性
		- id    --标签唯一标示
		- name    --服务器识别的标识，将值赋给name的value，相当于变量名，字典键值对
			- 也可以显式用value属性定义name的值，checkbox时存为一个列表
		- title    --鼠标悬停时显示
		- bgcolor    --背景色
		- href    --链接地址， =>  link、a
		- rel     --rel 属性规定当前文档与被链接文档之间的关系
			- stylesheet
			- copyright
			- help
		- span     嵌套在a里面设置span的backgroud可以做图标超链接
- 常用标签
	- <!DOCTYPE html>    --指定w3c文档解析规则，不同浏览器解析问题；
===========head============
- meta
	- content    --服务于前面的属性，赋值作用
	- name
		- keywords  => 配合content，con的值为提供给搜索引擎使用
		- description    => 配合content做为description的值
	- http-equiv    --本质是修改头部信息
		- refresh     =>  content="2;URL=https://www.baidu.com"    刷新之后2s跳转到URL
		- "content-Type" charset=UTF8     --编码
		- X-UA-Compatible    --IE版本兼容，content = "IE=EmulateIE7
- title    --网页标签页文字
- link     --网页标签页图标
	- <link rel="icon" href="url">
- script    --jsonp  伪造请求
	- <script src=""></script>
- iframe    --预留框，内部加载文档html；包含另外一个文档的内联框架（即行内框架
	- <iframe src=""></iframe>     --独立通道，不需要刷新访问其他的url，小窗口
===========body=============
	分类 = {块级元素、内联元素} 
- 块级    --整行占用，宽度(width)、高度(height)、内边距(padding)和外边距(margin)都可控制
	- div    --框选无特殊作用，配合内联css使用，对应的span标签是行内标签
		- <div attr="" >text</div>
	- hi    --多级标题
	- hr    --分割线
	- p    --paragraph段落,换行+隔行  => <br/> 单纯换行
	- pre   --长文本保留格式展示，限定高度后生成滚动条
	- li   列表行，嵌套在有/无序列表块里
		<= ul    --unordered list 
		<= ol    --ordered list
	- dl    --层级显示文本
		=> dt
		=> dd
	- form    --表单，与后端交互，传输数据；里面嵌套input、select、textarea、label； 整体用字典传
		- action    --value为server端的处理文件路径，可缺省服务器地址
		- method    --提交方式
			- get     --url?key=value,对传输的数据进行转码或预处理变成连接；Django后端获取到的是request.GET 字典
			- post     --都不安全, ajax与服务器异步交互、局部刷新, JS处理数据不同于页面提交; req.POST.get("key")
			> form.name值.value 取出提交的字段值，可用于前端判断
		- enctype    -- 请求体将提交数据编码，默认值"application/x-www-form-urlencoded" 
				ajax => xmlhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded")
- 内联    --h、p、dt只能包含内联元素，li可以嵌套div
	- input   --自闭合，配合form表单使用
		- type
			- text    --输入文本框, value属性值为默认值   palceholder属性值为提示字符串
			- password    --密文输入
			- submit    --提交按钮，一般在最后，替换按钮名 value="new"， 没有name属性与之对应的时候则修饰按钮
			- button    --按钮，配合js触发
			- checkbox   --复选框， name="同名", value="", 选多个时name等于一个value组成的列表
										request.POST.getlist("name值")
			- radio    --加 name="同名" 实现单选框，本质是将选择的值传递给一个键， 可以自定义value，但是最终等于一个
			- file    --文件上传按钮， 需要在form中加属性 enctype="multipart/form-data" ; $("")[0].files[0] 获取文件对象
			- reset    --清空重置输入内容
		- name    --键名
		- value    --值或按钮名
	- select    --下拉框，嵌套option 获取value ; Dom - .selectedOptions 选中的option标签
		=> option， 可在外面加一层分组、分级optgroup
		- name    --键名
		- multiple   --键值相同的属性，多选
		- size    --下拉框显示的条数，默认一条
		- selected
			<select name="keyname">
				<optgroup label="">
					<option value="value1">text</option>
					...
				</optgroup>
			</select>
	- textarea    --文本域
		- name   --键名
		- rows   --行数
		- cols   --列数
	- label    --关联
		- for    --值为关联目标id
	- span    --修饰文本，共用行
	- button    --按钮
	- img    --单开线程加载
		- <img src="" width="200px" alt="" title="">   alt加载失败时显示,title鼠标悬浮时显示
	- a    --功能{ 链接 : 锚 }
		- <a href="url">text</a>    链接， 默认同一页跳转，加 target="_blank" 实现新建也页面跳转
		- <a href="javascript:func()">link</a>    --相当于onclick事件监听， func()为void(0)时则无跳转
		- <a href="#id">para 1</a>    文档内跳转到指定div， 
	- sup / sub   --上/下角标
		- a<sup>b</sup>
	- 字体修饰    --现多用css控制
		- b   --加粗
		- em   --斜体
		- del    --删除线， 另外有strike
- table
	=>thead、tbody、tfoot、
			tr、th、td、caption
	- border     --边界宽度
	- cellspacing    --单元格间距，像素
	- cellpadding    --单元边沿与单元内容之间的空间
	- bordercolor
	=> tr、 td
		- rowspan    --合并行
		- colspan    --合并列
<table border="1">
	<caption><em>a test table with merged cells</em></caption>    --表格标题
  <tr>   --一行
    <th>Month</th>    --标题列
    <th>Savings</th>
  </tr>
  <tr>
    <td>January</td>    --普通列
    <td>$100</td>
  </tr>
</table>
- 特殊符号
	- &lt;  ==> <    用于标签显示
	- &gt;  ==> >
	- &nbsp;
	- &copy;

----
## CSS    --Cascading Stylesheet层叠样式表,描述HTML文档的样式语言
- 引入方式
	- 内联    --优先级最高；层级大的效果会影响到其所有后代元素
		<div style="background: red;color=#cc3399"></div>
	- 嵌入    --head里面用style标签，使用选择器
		<style>
			tagname{  --所有该类标签
				attr: value;
			}
			#id {
				background: red;
			}
		</style>
	- 链接式    --将style标签里的内容单独成文件，head里面link标签定义链接
		- <link href="mystyle.css" rel="stylesheet" type="text/css"/>
	- 导入式    --先加载html再导入，显示问题
			<style type="text/css">
				@import"mystyle.css"; 此处要注意.css文件的路径
			</style>　
- 选择器
	- 选择器
		- 标签选择器    --使用 * 通用匹配
			- element {}         单类元素
			- element,element    多类元素
			- element element    后代、<div> 元素内部的所有 <p> 元素（包含子元素和后代元素；可以指定多层级
			- element>element    子元素、父元素为 <div> 元素的所有 <p> 元素，只能从上到下
			- element+element    毗邻的第一个，紧接在 <div> 元素之后的第一个 <p> 元素
		- class属性值选择器 .    --类划分
			- .classname 或 element.classname = element[class="classname"]     calss类属性定位
		- id值选择器 #      --同一页面内唯一标识
			- #id
		- 属性选择 []    --自定义属性，属性多值用空格分开
			- E[att]
			- E[att=val]      指定值
			- E[att~=val]     值包含、att的值包含，匹配所有att属性具有多个空格分隔的值、其中一个值等于“val”的E元素
			- E[attr^=val]    开头、匹配属性值以指定值开头的每个元素
			- E[attr$=val]    结尾、匹配属性值以指定值结尾的每个元素
			- E[attr*=val]    字符包含、匹配属性值中包含指定值的每个元素
		- 伪类	   --可以是.class   或者 #id  来配个 :link/hover/active/visited 
			- a:    --anchor伪类：专用于控制 链接 的显示效果 a:link {color: #FF0000}
				- a:link    --链接的常规状态
				- hover    --鼠标放在元素上的状态
					- 类:hover 选择器    复合使用 =>  实现鼠标悬浮出现子菜单栏
					- 图片鼠标悬浮文字(全覆盖)
							.contaniner .item:hover .text {display:block}
							container{relative}、item{absolute、z-index}、text - opacitybg+text{absoloute、z-index}
					- 鼠标触发下拉框(移位)
							relative -> absolute； 注意鼠标聚焦在 z-index 大的元素上
				- visited    --访问过的链接
				- active    --鼠标按下时状态
				- text-decoration: none      --去除链接的默认下划线
			- before after伪类    --在元素的前后插入内容， 并单独设置CSS
				- element:after { content:text; style    }   --content: attr(属性名) 直接获取element的属性值
- css优先级 10     10        1  ==> 值大的优先
	- 内联 > #id > .class > tagname
- 继承    --对后代元素的影响
	- border, margin, padding, background  不能被继承
	- 优先级低，可以被覆盖
	- ==> color:#ffF!importtant;     --指明该设置不会被覆盖   
- 常用属性
	- 颜色color
		- color:blueviolet    color:#ffee33     color:rgb(255,0,0)    color:rgba(255,0,0,0.5)
	- 字体属性
		- font-size: 20px/50%/larger
		- font-style: italic/oblique
		- font-family: "Times New Roman""
		-	font-weight: lighter/bold/border/
	- 背景属性
		- height、weight
		- mini-width     --设置后在窗口宽度小于该值时，会出现横向滑动条
		- background-color: cornflowerblue
		- background-image: url('1.jpg')      --地址， 默认拼接
		- background-repeat: no-repeat/repeat-x/repeat-y
		- background-size: h w/auto
		- background-position: center center    --上下左右, 起始位置，默认 0 0
		- backgroud: #ffee33 url() no-repeat auto    --简写，取总属性再一起赋值
		- opacity: 0.6    --t透明度
	- 文本属性
		- font-size: 10px
		- text-align: center     -- line-height: height值 ；  配合起来为居正中，即保持全占行;对于脱离文档流的加width: 100%
		- vertical-align     --top\mid\bottom
		- line-height: 200px
		- letter-spacing: 10px     --字母
		- word-spacing: 20px     --单词
		- text-transform: capitalize    --标题使用，每个单词首字母大写
		- text-indent: 150px     --首行缩进
		- vertical-align:－4px  设置元素内容的垂直对齐方式 ,只对行内元素有效，对块级元素无效
	- 边框属性    --一切都是框、盒，布局摆放
		- border-style: solid
		- border-color: chartreuse
		- border-width: 20px
		- border-radius: xx%    --调整边框圆角
		- 属于盒子、框    内-外
			- content    --内部元素
			- padding     --内部元素框 到boder的距离
			- border
			- margin   => -top/right/bottom/left
				- margin: 0, auto    -------居中
				- margin:10px 5px 15px 20px;-----------上 右 下 左   顺时针
				- margin:10px 5px 15px;----------------上 右左 下
				- margin:10px 5px;---------------------上下  右左
				- margin:10px;    ---------------------统一
				- body的margin 是与html的边距， 浏览器边距
			- 坑
				- 父div 子div； 将子div移到父div中间
					- 父div加border: solid; 再子div用margin 计算 （父div无border就会以body为准）
						-	边界塌陷或者说边界重叠  margin collapse
							- 兄弟div：上面div的margin-bottom和下面div的margin-top会塌陷，也就是会取上下两者margin里最大值作为显示值
							-	父子div：如果父级div中没有 border，padding，inline content，子级div的margin会一直向上找，
												 直到找到某个标签包括border，padding，inline content 中的其中一个，然后按此div 进行margin计算
					- 父div在原基础上扩充 padding ， 外部变大
		- 列表属性
			- list-style: decimal-leading-zero;
			- list-style: none;       --去除列表的点 
			- list-style: circle;
			- list-style: upper-alpha;
			- list-style: disc;
		- 鼠标指针属性
			- cursor:
				- default
				- auto
				- none
				- help
				- pointer
				- wait
				- text
				- crosshair
				- move
				- not-allowed     --禁止点击图标
				- grab
				- zoom-in/out
		- display    --块、内联切换
			- none
			- block    --独占一行，默认block元素宽度自动填满其父元素宽度，可以设置width、height、margin、padding属性
			- inline    -- inline元素设置width、height属性无效。inline元素的margin和padding属性：
										水平 方向的padding-left, padding-right, margin-left, margin-right都 产生 边距效果；
										竖直 方向的padding-top, padding-bottom, margin-top, margin-bottom 不会产生 边距效果。
			- inline-block    --可做列表布局，间隙解决 border: 3px dashed;  word-spacing: -5px;
												内联标签，但是可以设置宽高
		- 文档流是元素排版布局过程中，元素会自动从左往右，从上往下的流式排列
			默认文档流，上下左右排列定位；==> 脱离文档流，其他元素定位时当作不存在 ==> 层级覆盖 (float/position)
			如何在一行显示多个div元素
			
		- float --非完全脱离，将其层级置为前一层，则原来的框、盒子没有该元素，当其为空的时候且没设置宽高的则可能CSS不生效
									解决：添加 <div class="visible"></div>  ==> .visible { clear: both; } 使愿容器仍然能够正确的显示
												添加 overflow: hidden/auto/scroll     --益处部分的处理，auto为scroll
			- 设计初衷：文字环绕，文本不会被覆盖，而是环绕在float元素周围 ==>非完全
		- clear    --不允许有浮动元素，否则让位下移动，只会对设置元素有影响 =>     --
			- none | left | right | both                                             一
		CSS清除浮动    --父元素clearfix 类复用； 原始：最后附加子元素清除 - clear: both 
		.clearfix:after {     --只针对于float，还未脱离文件流
				content: "anything";
				display: block;
				clear: both;
				visibility: hidden;
				height: 0;
			}
		- position 定位  => absolute  
			一个元素若设置了 position: absolute | fixed ; 则该元素就不能设置float
			- position:fixed/relative/absolute/static    默认static未脱离
			- bottom/right/top/left    --设置位置，坐标轴右下为正
				- relative   --未脱离文档流，相对原位置，且原位置仍然占位，单独使用的时候无效果
				- absolute   --完全脱离，向上找非position为非static的上级元素，没有则直到最外层html，再相对其进行移动
												top: 50%; margin-top: -1/2height;  达到居中
												top/left:50%  +  transform: translate(-50%,-50%)
												另外：absolute 直接使用可以将div 占满窗口高度； top/bottom/left/right 是相对窗口，overflow:scroll
				- fixed    --脱离文档流，相对于浏览器
				- z-index     --当position为上诉三种时可以设置z-index
----
- 菜单缩放   --子菜单 hide； border-left/right , 初始状态颜色透明，触发时添加颜色
	<div class="item-title">菜单一
		<div class="item-content">
			<a>菜单1-1</a>
			<a>菜单1-2</a>
		</div>
	</div>
	
	选中子菜单样式确定：
		js实现有滞后效果
	后台tag渲染
		

- 瀑布流    --指定列数，每行上接紧密排列
- 静态实现
	<div style="margin:0 auto;">    --里面的内容居中 
						<img src="img1" style="width=100&;"> 
						<img src="img5" style="width:100%%">
						<img src="img2">
						<img src="img3">
						<img src="img4">
	</div>
	relative
	absolute
			left      高度最小列的下标
			top				最小高度
	
- JS实现    --详细代码->js笔记
	- ajax获取全部相关联的对象(img的路径)； 可以设定获取的起始id，监听滚轮滚动事件然后修改起始id
	- success function(arg){}
	- arg.data => i, v; 索引值以及对象
	- 创建相应标签，添加到div内
			$("").children().eq(int).append()
