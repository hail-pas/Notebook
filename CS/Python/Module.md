# Module

-- help(functionName)    --获取帮助，使用说明
- 功能性py文件：python标准库、第三方模块、应用程序自定义
- 扩展、管理
----
## 调用
- module    --模块   sys.path 搜索路径 ：优先当前目录
	- import module_name, other_modu    --找到之后便将模块所有代码只编译执行一遍，所以 if ___name___ == ___main___: 这下面的代码不会执行
	- from modu_name import fun_var    --调用指定元素，其他元素不可见
		- from modu_name import *    --调用所有元素，module中的函数名可能和当前文件里的函数同名覆盖问题
		- from modu import func_name as new_fun_name      自定义调用函数的名字
- 字符串反射导入
	- importlib.import_module(".....")
============
- package   --包，所有相关模块的集合
	- ___init___.py    --直接调用包的时候只执行该文件，但是不执行下面的模块
	- import pack_name    --直接调用包
	- 模块：from package_name import modu_name    --多层包使用.解包，pack1.pack2；会编译执行一次包
	- 方法：from pack1.pack2.modu import fun_name   --import 接最终导入目标
- Basedir     --目录结构
	- sys.path.append("")   --新增搜索路径， 新增下面求出的BASE_DIR
	- ___file___     --当前py文件的相对路径
	- os.path.abspath(___file___)     --获取当前文件的绝对路径
	- BASE_DIR = os.path.dirname("")    [](--获取路径的上一层路径)
	- 将项目的主文件夹设为BASE_DIR
	-  Foo     --目录结构
			|--bin {程序入口}
			|   |--
			|--foo
			|   |--main.py
			|   |--
			|--docs
			|   |--conf
			|--package
			|   |--
			|
			|--setup.py {打包、安装、部署}
			|--requirements.md {}
			---README.md {1.软件定位；2.运行方法：安装环境、启动命令；3.简单使用说明；4.代码目录结构说明；5.常见问题}

----
## sys
- sys.argv    --获取命令行参数存为列表， python 命令之后的
-
----
## 发送邮件
- package
	smtplib、email.mime.text.MIMEText、email.utils.formataddr
	---- msg文本定制MIMEText、server配置（login、sendmail、quit）
	def email_sender(send_email, passwd, inbox_list, content, subject):
				msg = MIMEText(content, "plain", "utf-8")    --邮件文本设置
				msg["From"] = formataddr(["name",send_mail])
				msg["subject"] = subject

				server = smtplib.SMTP("domain", port)
				server.login(send_mail, passwd)
				server.sendmail(send_mail, inbox_list, msg.as_string())
				server.quit()
----
## os
- path
	- join
	- abspath
	- dirname
	- exists
	- isdir   判断是否是目录
	- split()[0/1]     --目录和文件
- mkdir() - rmdir()      --单级目录
- makedirs() - removedirs()    --创建多级目录
- getcwd()    --当前目录
- listdir()
- walk()    --for dirpath, dirnames, filenames in os.walk('待分析目录'):
- getpid()    --当前进程id
- getppid()    --父进程id
----
## time    --时间戳、结构化元组、格式化时间
- 时间转换   --数字时间戳 - struct时间元组 - 字符串格式化
	 数字1443424400 --time.gmtime(1443)-->  time.struct_time(tm_year=, tm_month=,) --
									--> time.strftime("%Y-%m-%d %H:%M:%S",structime  --> 2019-10-18 15:22:45

	 2019-10-18 15:22:45 --time.strptime("2019-10-18","%Y-%m-%d")--> time.struct_time(tm_year=2019)  --
									--> time.mktime(structime) --> 1443424400


- time()    --时间戳，float
-	clock()    --时钟时间，cpu执行时间
- gmtime()    --UTC
- localtime()    --当前时区时间  ==> struct_time   元组格式
	- struct_time.tm_year    --同理可以取出其他的
- strftime(format,struct_time)    --"%Y - %m - %d %H:%M:%S"
- strptime("2019-08-19 14:14:14","%Y-%m-%d %H:%M:%S")    --转换为格式化元组
- ctime()    --格式化时间，接收参数为时间戳
	- time.ctime(time.time())    --当前时间
- mktime()    --结构化元组时间转化为时间戳
----
## datetime    --time的进一步封装 -> { datetime、date、time、timedelta、tzinfo }
datetime.datetime(year, month, day, hour=0, minute=0, second=0, microsecond=0, tzinfo=None)
- datetime.datetime.now()    --直接输出“%Y-%m-%d %H:%M:%S %z”
- datetime.datetime.now() + datetime.timedelta(hours=1)    --默认days=7; minutes=30 . seconds=60
- replace(day=1)    --替换函数
	- .replace(tzinfo=utc_tz)   # 时区  utc_tz = timezone('UTC')    from pytz import timezone
	- datetime.datetime.utcnow()
- datetime.datetime.fromtimestamp(timeStamp)   --时间戳转datetime ==》 进一步  .strftime("%Y %m %d %H:%M:%S")
- datetime.datetime.strptime('2018-02-03 15:37:12' , '%Y-%m-%d %H:%M:%S')


## heapq    --堆，随时找出并删除最小的元素比列表方法min更高效
- 方法
	- heapqpush(heap, x)    --x压入
	- heappop(heap)    --弹出
	- heapify(list)    --使列表具有堆特性
	- heapreplace(heap, x)    --弹出最小元素并将x压入
	- nlargest(n, iterable)    --返回可迭代对象中内n个最大元素
	- nsmallest(n, iterable)    --最小
----
----
## subprocess
- Popen   --类, 新开子进程去执行
- insobj = subprocess.Popen("command str", shell = True, stdout = subprocess.PIPE )
- insobj.stdout.read()    --bytes类型， 需要转换 str("", "utf8")
- subprocess.getoutput('ls /bin/ls')    --返回命令执行结果
----
## paramiko
- SSHClient     --命令执行
	 ssh = paramiko.SSHClient()
	 ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())   --信任主机添加策略
	 ssh.connect("host",port,"username","passwd")
	 stdin, stdout, stderr = ssh.exec_command("command")
	 ssh.close()
	 stdout.read().decode()
	 -------
	 private_key_path = '/home/auto/.ssh/id_rsa'
	 key = paramiko.RSAKey.from_private_key_file(private_key_path)
	
	 “passwd” 替换成 key
	 -------
- Transport    --文件传输
	- SFTPClient
		 tran = paramiko.Transport(('host',port))
		 tran.connect(username='name',password="pass")
		 sftp = paramiko.SFTPClient.from_transport(tran)
		 sftp.put('/tmp/test3.py','/tmp/test3.py')        --get
		 tran.close()
		 ------
		 pravie_key_path = '/home/auto/.ssh/id_rsa'
		 key = paramiko.RSAKey.from_private_key_file(pravie_key_path)
		
		 tran.connect(username='name',pkey=key)
		 ------
- 实时交互      --默认单次连接
	基于paramiko源代码的interactive.py修改
----
## random
- random()    --生成随机数，默认 0-1
- randint(int1,int2)    --包括int2
- randrange(int1,int2)    --不包括int2, 默认 0-
- choice(序列)    --随机取序列里的单个元素
- sample(序列,int)    --随机取int个
- shuffle(序列)    --打乱序列顺序
-
- chr(int)  --ASCII码转换成字符   0-9：48-57 ； A-Z : 65-90 ;  a-z：97-122

----
## hashlib     --明文转密文算法
- md5()    --md5算法
	- md5ob = hashlib.md5()
		md5ob.update("Text".encode("utf-8"))   #同一个md5对象只对一个text加密，重复引用的本质是将后续的拼接再加密
		encrypted_text = m.hexdigest()   #十六进制数取出
- sha1()    --sha256  使用方法同上 对象实例化、update、digest
----
## logging
- debug("log message")    #存为message变量
- info()
- warning()      --开始输出到输出设备的优先级；另外还可以写入到文件
- error()        --默认输出到显示设备，basicConfig函数进行配置
- critical()     
- 配置     -- critical > error > warning > info > debug > notset
	- basicConfig(level=logging.DEBUG,     #debug及以后的都能输出或写入文件
								format = "",             # %(变量名)  ==> asctime/filename - 程序名/lineno - 代码行数/levelname/message
								datefmt = "",
								filename = "",           #输出文件
								filemode = "")
		logging.warning("text")   #日志启动
	- format变量
		- %(name)s Logger的名字
		- %(levelno)s 数字形式的日志级别
		- %(levelname)s 文本形式的日志级别
		- %(pathname)s 调用日志输出函数的模块的完整路径名，可能没有
		- %(filename)s 调用日志输出函数的模块的文件名
		- %(module)s 调用日志输出函数的模块名
		- %(funcName)s 调用日志输出函数的函数名
		- %(lineno)d 调用日志输出函数的语句所在的代码行
		- %(created)f 当前时间，用UNIX标准的表示时间的浮 点数表示
		- %(relativeCreated)d 输出日志信息时的，自Logger创建以 来的毫秒数
		- %(asctime)s 字符串形式的当前时间。默认格式是 “2003-07-08 16:49:45,896”。逗号后面的是毫秒
		- %(thread)d 线程ID。可能没有
		- %(threadName)s 线程名。可能没有
		- %(process)d 进程ID。可能没有
		- %(message)s用户输出的消息
- logger
	- 创建
		- logger = logging.Logger("",level=logging.DEBUG)   #对象实例化
		- logger = logging.getLogger()    #对象生成函数
	- logger.setLevel(logging.DEBUG)    #设置输出优先级
		fh = logging.FileHandler("./test.log")
		sh = logging.StramHandler()
		formatter = logging.Formatter("")   #直接使用上面的format变量定义格式
		fh.setFormatter(formatter)
		sh.setFormatter(formatter)
		looger.addHandler(fh)
		logger.addHandler(sh)
		logger.debug("text")
		logger.info("text")


		流程：logger对象实例化 -> addHandler() <-- FileHandler/StreamHandler对象输出对象实例化
							|																			|
							--->logger.debug("")									----> setFormatter()格式化方法 -> Formatter对象实例化

----
## XML
- 标签对  
	<tagnamr  attribute = value>
		<option attribute = value> text </option>
		<selfclose attribute = value />
		...
	</tagname>
### python解析XML
- xml.etree.ElementTree   --模块 as ET
- 查看
'''
	tree = ET.parse("path/file.xml")
	root = tree.getroot()    # root.tag
	for child in root:
			print(child.tag, child.attrib)
			for i in child:
					print(i.tag, i.text)

'''
- 修改
'''
	node = root.iter("tagname")
	node.text = "new text"
	node.set("attrname", "value")
	tree.write("path/file.xml")

'''
- 创建
'''
	new_xml = ET.Element("roottagname")
	subtag = ET.SubElement(new_xml, "tagname", attrib = {"attribname": "value"})
	subsubtag = ET.SubElement(subtag, "tagname", attrib = {"Attrname": "value"})
	subtag.text = "text"

	xmlobj = ET.ElementTree(new_xml)  #生成文档对象
	xmlobj.write("path/file.xml", encoding="utf-8", xml_declaration = True)
'''
- 删除
'''
	[] = root.findall("tagname")
	node = root.find("tagname")
	root.remove(node)
	tree.write("path/file.xml")
'''

----
## configparser    --用于生成或修改配置文档 ：健值对文档，字典型 -> 字符串 文件
- configer = configparser.ConfigParser()
	configer[" key1 "] = { "key":value, "key":"value"" }   # 块key1 , 可以使用 key in configer 判断
	configer[][key][key] = "value"    # 直接指定到内二层
	configer[" key2 "] = {}
	key2value = configer[" key2 "]
	key2value["key"] = "value"        #中转传递

	with open("path/file","a") as configfile:
			configer.write(configfile)    #写入

	configer.read("path/file")
	print(configer.sections())        #读取除 [Default] 块之外的，configer.defaults()
	configer.remove("")
	for key in configer["othersection"]:
			print(key)                    #会输出default块下的key
- sections()    #取出除defaults的块
	add_section("")    #修改完需要 用write()写入到文件
	has_section("")
- set("key","key","value")
	remove_option()    #删除最后一层的key
----
## json.dumps 扩展JSONEncoder

class JsonCustomEncoder(json.JSONEncoder):
		def default(self, field)     --序列化时每一个值作为field传入执行
				if isinstance(field, datetime)      --比如需要对datetime类型进行处理
						retur field.strftime("%Y-%m-%d %H-%M-%S")
				elif isinstance(field, date)
						return field.strftime("%Y-%m-%d")            --添加需要处理的类型，比如自定义类， 类=> ___dict___
				else:
						return json.JSONEncoder.default(self,field)       --最后需要调用原生类型处理方法

使用 -> dumped_data = json.dumps(data, cls=JsonCustomEncoder)
