# Web Development
----
## 事件驱动模型   --常规线性代码执行, Epoll - linux; ICOP - windows，进程主动中断-阻塞就是卡在某一步，无法同步继续下去
==> 单线程、多线程编程； 异步 优于 同步
	事件 --> 队列 --> 轮训 --> 处理函数 
	单线程里多个任务交错执行，非阻塞I/O方式，回调函数处理事件
	tcp连接和线程进程不再强制产生绑定,当无事件触发的时候代码不会被执行。 主动 - 被动
	后端服务:
		- 业务无关的通信层(I/O行为)，负责socket连接的创建和管理，负责bind/listen/accept/send/recv
		- 业务逻辑层，负责被动响应请求，或主动推送业务消息
			- 优化：异步回调，coroutine
	- 内核态 - 用户态
	- PCB、队列、上下文管理、程序计数器、寄存器
	- 文件描述符   --fd，索引值; 事件状态变化标识
		 0、1、2 -> stdin、stdout、stderr ； 操作文件的标示
		- 描述符{数据、非数据} => ___get___、set、delete
	- 缓存I/O    --cache，页交换，先存储到内核态缓存（网卡操作需要内核态），再拷贝到用户态应用内存
- I/O模型    --同步、异步、阻塞、非阻塞 ==>  购票（排队、付款取票）
		 同步 -> 一个系统调用 recvfrom
		 I/O多路复用 -> 两个系统调用 select+recvfrom  -> 同步阻塞升级版本
	 socket -> 系统缓存 -> 用户态内存
	- 同步模型：拷贝都会阻塞
		 网络I/O： 调用I/O的进程、系统内核（fd） =>  应用系统调用 --> 内核 --> 接收 --> copy --> 用户态内存
		- 信号驱动I/O模型   --实际不常用
		- 阻塞I/O模型    --用户态、内核态的I/O都阻塞，状态卡在内核态无法继续执行
			- 自动拷贝
		- 非阻塞I/O模型    --轮询请求内核态，非请求时段恢复到用户态调用cpu继续执行，但是copy阶段任然是阻塞的
			- 自动拷贝，进程去请求拷贝，拷贝阶段仍然会阻塞
			- 问题：数据的延迟
		- I/O多路复用模型-epoll    --事件驱动I/O，epoll 是优化版的select；（多窗口）；事件循环监听
			- select 发起系统内核态调用    --与上诉的区别在于select可以监听多个连接，归入队列；进程的阻塞原因页变成了被select阻塞
			- systemcall显式拷贝
	- 异步I/O模型    --I/O操作和进程独立，互不影响，进程发送I/O请求，然后I/O独立处理，整个过程不会阻塞，收到请求+拷贝完成时会发送给进程
- I/O多路复用复用模型    --事件驱动模型 ：select、poll、epoll ==> 监听文件描述符
	 对流式对象比如socket和pipe进行多路I/O复用的select模块
	- 水平触发：高电平直接触发；边缘触发：相邻点位变化触发
	- 获取到数据但是没有调用accept函数将数据消化使用，导致数据一直在r里面
	- select    --跨平台，文件符数量限制（32-1024，64-2048）；select低效轮询，无法明确定位数据更新的文件描述符；读写监听
		 实质是死循环监听多个文件描述符 
		- select模块  -- r,w,e = select.select(maxfdnum, [read1,]，[write,], [exce_set,], timeout)  返回监听参数同类型对象
			 read 和 write 对象参数必须有： fileno方法 并 返回一个文件描述父
			 参数实际就是调用对象的该方法获取文件描述符fd  --> 自定义IO模块时使用
	- poll    --文件符数量优化
	- epoll    --文件描述符数据更新时主动触发调用callback()；事件触发思想。拷贝依然会阻塞
- selectors模块    --linux
		sel =	selectors.DefaultSelector()
		sel.register(obj, selectors.EVENT_READ, funname)  #绑定socket - 事件类型 - 处理函数
				sel.unregister(obj)
		events = sel.select()
		for key, mask in events: # 执行处理函数       |
				callback = key.data    # funcname         |
				callback(key.fileobj, mask)   # key.fileobj => sockobj
----
## Socket    --TCP/UDP 协议； C/S架构 ; bytes类型传递
>>抽象tcp/ip协议的具体编程接口
- 使用
# 1 服务器根据地址类型（ipv4,ipv6）、socket类型、协议创建socket
# 2 服务器为socket绑定ip地址和端口号 - bind
# 3 服务器socket监听端口号请求，随时准备接收客户端发来的连接，这时候服务器的socket并没有被打开 - listen
# 4 客户端创建socket
# 5 客户端打开socket，根据服务器ip地址和端口号试图连接服务器socket
# 6 服务器socket接收到客户端socket请求，被动打开，开始接收客户端请求，直到客户端返回连接信息。这时候socket进入阻塞状态，
#   所谓阻塞即 accept() 方法一直等到客户端返回连接信息后才返回，开始接收下一个客户端连接请求
# 7 客户端连接成功，向服务器发送连接状态信息
# 8 服务器accept方法返回，连接成功  =	>	send()/sendall()  <--> recv()   (sendall内部处理成多次发送直到完成数据发送)
# 9 客户端向socket写入信息(或服务端向socket写入信息)
# 10 服务器读取信息(客户端读取信息)
# 11 客户端关闭
# 12 服务器端关闭
import socket
# family type
socket.socket(self, family="", type="")  # 默认tcp、ipv4服务器间
- family
	- AF_INET     --服务器间通信  AF_INET6  IPv6
	- AF_UNIX     --Unix不同进程间
- type
	- SOCK_STREAM    -- TCP
	- SOCK_DGRAM    --UDP
- 服务端                                               客户端
	mysk = socket.socket()  #实例化                      sk = socket.socket()
	mysk.bind(("127.0.0.1",9102))                        sk.connetct(("127.0.0.1",9102))
	mysk.listen(3)   # 最大连接数												 status_code = sk.connect_ex(address)   #成功返回0，失败返回编码
	conn, addr = mysk.accept()    #等待连接，发送的数据可以是复杂对象，需要先进行dunp
	conn.send(bytes(text,"utf8"))                        data = sk.recv(1024) -> str(text,"utf8")    # repr(obj)转换为str
	conn.recv(1024)																			 sk.send()
	conn.close()                                         sk.close()
server的 conn = accept() 对标 client的实例对象sk（包含连接信息） ，都包含对方ip:端口, server端的socket实例只有自身IP:端口，等待建立连接
server多次创建 conn 连接到不同的client
send 发送空-回车（不含空格）另一端会意志阻塞在recv函数
recv(max) 超过该阈值时会分多次接收
- 传递命令    --subprocess  >>  shell 命令相关模块, subprocess.Popen() 类
	- result = subprocess.Popen(str(rec_data, "utf8"), shell=True, stdout=subprocess.PIPE)
		send_data = result.stdout.read()
	当传递的命令结果大于 recv() 时会出现多次接收结果; 解决如下
		while True:
		rec_data = conn.recv(max)
		print(str(rec_data, "utf8"))
		if len(rec_data) < max:
			break
-	上传文件
	- os.path.join(,)    --目录合并
	- os.path.basename("path")   --文件名
	- os.stat("path").st_size   --文件大小  os.path.getsize()
	- os.path.exists()
	- with open(,"rb") as ff:                 "ab"
				while True:
				data = ff.read(1024)   --最大字节;  ff.write(rec_data)
				sk.sendall(data)
				if len(data) < 1024: break
		先将文件存储到以 md5值 为名字的文件内， 当大小完成的时候再更名为目标文件
- 粘包    --两次发送粘接成一次发送。 recv会阻塞
	- 严格按照一接一发隔断
----
## socketserver    --提供了服务器中心类，可以简化网络服务器的开发； server端调用
- 包含两大类： 
	- 1、请求处理类（事务逻辑数据处理）  --  BaseRequestHandler -> StreamRequestHandler、DatagramRequestHandler
	- 2、Server类（网络连接处理）
+------------+
| BaseServer |    -- 一般不直接调用
+------------+
			|
			v
+-----------+      +------------------+
| TCPServer |----->| UnixStreamServer |
+-----------+      +------------------+
			|
			v
+-----------+      +--------------------+
| UDPServer |----->| UnixDatagramServer |
+-----------+      +--------------------+
	- 3、多进程类    --   ThreadingMixIn 线程、ForkingMixIn 进程
- 创建socketserver过程
	- 自定义请求处理类（继承） --> 重写handle 函数，实现业务逻辑
	- 下面两个可以封装成自定义的类(object): 包含创建、开启
		- 创建server实例（(ip_port), 自定以请求类）-- 内部封装实现绑定、监听
		- 调用server实例的serve_forever() 方法启动
- server端导入socketserver
	class MyServer(socketserver.BaseRequestHandler):  #继承
			def handle(self):      #重写
  #实例化
	server = socketserver.ThreadingTCPServer(ip_port, MyServer)
	server.serve_forever()  #启动
- 类
	- BaseRequestHandler    --自定义请求处理类需要继承该类
- 方法
	- setup    --在handle之前被调用，做一些初始化
	- handle    --参数self.request 等价于server的conn； 重写该方法用于处理请求；self.client_address ，self.server
	- finish    --在handle之后，如果setup报错，则该方法不会被调用
----
## django框架访问
- url对应关系加载
- 配置文件读取
- socket运行

----
## Web API     --接口开发定义
	 互联网软件架构：SOAP -> Rest架构（restful规范接口应用）
	 简单对象访问协议 -> 面向资源架构
- Restful规范    -- 软件+网络 -> 互联网
	 Representational State Transfer 
	- 原则
		- 资源
				 定位资源 -> URI>URL     --避免多级目录，使用参数； URI中尽量不带动词，资源使用名词
				 操作资源 -> GET、POST、PUT、DELETE、PATCH、HEAD、OPTIONS   ｜ GET操作是幂等的，操作无数次数据都不会改变
		- 资源表现形式    --头部信息补充
				 资源的形式，文件格式
		- 资源状态转化
				 基于HTTP无状态协议
				 操作状态方法 -> GET、POST、PUT、DELETE
- Restful接口设计
	- URI/URL 复数名词 - 对应数据库
	- 协议 HTTPS
	- 接口专用域名/服务器
		 api.adieupas.com    或者    .com/api/
	- 版本号放入url
	- 过滤
		 参数传递
	- 状态码标准
	- 出错信息
		 json -> {error_msg: ""; error_code: ""; resolution: ""}
	- API认证    --LDAP协议
		 oAuth
- Django 的 Restful 组件     --api的app； 类似于django的admin
	 django-rest-framework.org
	 默认jason
	- django项目里注册app
		 rest_framework
	- 步骤
		 数据筛选序列化类
		 数据取出并传递的类       --views
				 Serializer、ViewSet、register
		 url路由

