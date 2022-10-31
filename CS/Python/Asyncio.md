# 异步IO
	 IO不占用CPU
	 DMADirect Memory Access）芯片负责IO
	  CPU -> DMA -> 总线 -> 进程阻塞 -> DMA回调 -> 进程恢复
	  用户态、内核态
- 基于请求-结果理解
	- 阻塞：等待结果消息过程的状态
	- 同步：结果消息如何通知的机制、 (不)可靠任务序列； 
					异步：独立于主程序流发生的事件，以及处理该事件的方式； 即调用者不关心被调用者的处理方式与处理结果；
								回调并发
				多路复用、信号驱动
				非阻塞 + IO多路复用 - 主进程时间分片执行回调（主进程非阻塞全部发出请求，多路复用监听请求返回结果；抢占主进程）
				tornado异步 = 非阻塞 + IO多路复用 + 请求不断开挂起循环查询处理结果（Future值）
----
- 性能相关
	 并发请求 - 监控组件 - 回调
	 并发仍然会有IO等待
	- 并发请求     submit、shutdown(wait=True)
		- 多线程
		- 多进程
		  pool = ThreadPoolExecutor(10)
		  p = pool.submit()
		 	p.add_done_callback(func)      --回调
	- 选择
		gevent+requests > twisted > tornado > asyncio
----
- 单线程事件驱动异步IO模块       --同步单线程、多线程
	 协程 + 异步IO = 切换功能 + 切换条件 = 一个线程减少等待
	 socket 发送 http 请求数据 b"GET uri HTTP/1.0\r\n | Host:ip_or_domain | \r\n\r\n | body | "
			 请求头和请求体使用 2 回车式换行 分割； 内部使用 1 个分割
	 win 回车式换行\r\n; linux 无\r
	==========================================================================
	- asyncio    --py3 内置协程+异步IO；使用yield标记切换点；需要封装http数据包
		  引用-----
			 tasks = [fetch_async('http://www.google.com/'), fetch_async('http://www.chouti.com/')]    --函数列表,传递参数
						 都是参数已经确定好的任务函数列表
			 event_loop = asyncio.get_event_loop()
			 results = event_loop.run_until_complete(asyncio.gather(*tasks))
			 event_loop.close()
		  任务函数定义---------fetch_async()
		  @asyncio.coroutine      --任务函数需要装饰器标示
		  yield from 切换， 只支持tcp(socket)，不支持http请求; http -> sock.send(http规范数据包)
		  封装了tcp连接支持 asyncio.open_connection(host, port)
		 ------
		 def fetch_async(host, url='/'):
					reader, writer = yield from asyncio.open_connection(host, 80)     --tcp连接
					request_header_content = """GET %s HTTP/1.0\r\nHost: %s\r\nheader\r\nbody""" % (uri, host,)  --http格式字符串
					request_header_content = bytes(request_header_content, encoding='utf-8')           --bytes化
					writer.write(request_header_content)
					yield from writer.drain()
					text = yield from reader.read()
					writer.close(
		
		- aiohttp    --封装http数据包; 简化任务函数中的发送连接请求； asyncio调用相同
			 def fetch_async(url):
					response = yield from aiohttp.request('GET', url)
					# data = yield from response.read()
					# print(url, data)
					print(url, response)
					response.close()
			
		- requests     --封装请求传递，requests 请求方法作为参数封装进任务函数
			 def fetch_async(func, *args):
					loop = asyncio.get_event_loop()
					future = loop.run_in_executor(None, func, *args)
					response = yield from future
					print(response.url, response.content)
			
	
	=======================================================================================
	- gevent     --基于greenlet的协程模块+异步IO； 安装 greenlet、gevent；也是tcp-socket级别
		 使用
		 from gevent import monkey
		 monkey.patch_all()
		  socket默认是阻塞的，该语句将内置的socket封装
		- requests 请求方法作为参数传递
			 def fetch_async(method, url, req_kwargs):
					print(method, url, req_kwargs)
					response = requests.request(method=method, url=url, **req_kwargs)
				print(response.url, response.content)
	
			 gevent.joinall([
					gevent.spawn(fetch_async, method='get', url='https://www.python.org/', req_kwargs={}),
					gevent.spawn(fetch_async, method='get', url='https://www.yahoo.com/', req_kwargs={}),
					gevent.spawn(fetch_async, method='get', url='https://github.com/', req_kwargs={}),
			])
			// 协程池, 控制最大协程数量
			 pool = Pool(int)
			 gevent.joinall([
					pool.spawn(),
			])
		- grequests = gevent+requests 封装
			  request_list = [
						grequests.get('http://httpbin.org/delay/1', timeout=0.001),
						grequests.get('http://fakedomain/'),
						grequests.get('http://httpbin.org/status/500')
			 ]
			  def exception_handler(request, exception):    --异常处理函数
			
	  response_list = grequests.map(request_list, size=int; exception_handler=exception_handler)   --异常处理可选
		 	  ==========================================================
	- twisted      --事件驱动型的网络引擎; IO多路复用 + 同步非阻塞socket；默认使用select
		- 原理浅析
			 事件驱动编程是一种编程范式，这里程序的执行流由外部事件来决定，单线程环境中调度多个事件源产生的事件分别自己处理；
				- 事件循环，当外部事件发生时使用回调机制来触发相应的处理
					Twisted的核心就是reactor事件循环
						 Reactor可以感知网络、文件系统以及定时器事件，等待然后处理这些事件。
						 从特定于平台的行为中抽象出来，并提供统一的接口，使得在网络协议栈的任何位置对事件做出响应都变得简单
			 另外两种常见的编程范式：单线程）同步编程、多线程编程
		- 爬虫简单应用     --twisted自带httpclient
		  fd = func()
			fd.addBoth(callbackfunc)
			dfd = defer.DeferredList([fd, fd])    --相当于select监听对象
			dfd.addBoth(reactor.stop()) 
			reactor.run()
		-------------------
		 from twisted.web.client import getPage, defer
		 from twisted.internet import reactor
		
		 def all_done(arg):
				reactor.stop()
			
		 def callback(contents):

		 task_list = []
	
		 url_list = ['http://www.bing.com', 'http://www.baidu.com', ]
		 for url in url_list:
				task = getPage(bytes(url, encoding='utf8'))       --任务实例，使用twisted自带的异步httpclient
																														使用自定义函数时需要 yield fd 文件描述符 以及 装饰器 标识
			task.addCallback(callback)                     --单个任务完成的回调
				task_list.append(task)
	
		 dlist = defer.DeferredList(task_list)      --Defer对象实例化，将功能任务函数列表传入； 
		 dlist.addBoth(all_done)            --所有任务完成之后的回调
		
	 reactor.run()         --启动事件循环监听，有计数器
		=======================================================================
	- tornado爬虫应用       --自带的AsyncHTTPClient，类似twisted
		异步框架
		 from tornado.httpclient import AsyncHTTPClient
		 from tornado.httpclient import HTTPRequest
		 from tornado import ioloop
		
		 def handle_response(response)：
					回调处理函数
					全局计数器维护，ioloop.IOLoop.current().stop()
		
		 def func(url_list):
				for url in url_list:
						http_client = AsyncHTTPClient()       
						http_client.fetch(HTTPRequest(url), handle_response)      --回调函数参数传递
		
		 ioloop.IOLoop.current().add_callback(func)
		 ioloop.IOLoop.current().start()      --死循环，可以全局变量计数器来stop
----
- 自定义请求异步IO模块
	 利用IO多路复用实现异步IO
		  非阻塞socket + IO多路复用 + 协程触发回调
	- socket
		 C/S、创建、连接、发送
		- 阻塞情况
			 连接 + 接收  => 创建时sk.setblocking(false);连接发送之后会马上去取数据，不会等待，取不到数据就会报错
	- IO多路复用     --同步基础上监听多路；委托式监听
		 select、poll、epoll  -> 文件描述符识别、定位; 只能IO多路复用监听
		 r, w, e = select.select([socket对象], [socket对象], [exception],timeout)
		 r、w、e 为socket对象
		 r --表示接收到数据的socket对象 -> recv()
		 w --表示连接创建成功的socket对象 -> send()
		 e --错误信息
		 自定义类包装socket； 
			 定义 fileno方法 返回 socket的文件描述符； 监听之后反射匹配返回自定义类对象
------------------------------
import socket, select


class HttpResponse(object):
	def __init__(self, recv_data):
		self.recv_data = recv_data
		self.header_dict = {}
		self.body = None

	def initialize(self):
		headers, body = self.recv_data.split(b"\r\n\r\n", 1)
		header_list = headers.spplit(b"\r\n")
		for header in header_list:
			header = str(header, encoding="utf-8")
			temp = header.split(":", 1)
			if len(temp) == 2:
				self.header_dict[temp[0]] = temp[1]


class HttpRequest(object):
	def __init__(self, sk, host, callback):
		self.socket = sk
		self.host = host
		self.callback = callback

	def fileno(self):
		return self.socket.fileno()


class AsyncRequest(object):
	def __init__(self):
		# 计数器功能
		self.rconn = []
		self.wconn = []

	def add_request(self, host, callback):
		try:
			sk = socket.socket()
			sk.setblocking(False)  # 同步非阻塞式
			sk.connect((host, 80))
		except BlockingIOError as block_e:
			pass
		finally:
			cus_sk = HttpRequest(sk, host, callback)
			self.rconn.append(cus_sk)
			self.wconn.append(cus_sk)
	
	def run(self):
		while True:
			read, write, err = select.select(self.rconn, self.wconn, [], 2)
			for w in write:
				print(w.host, "连接成功！！")
				http_send_data = "GET / HTTP/1.0\r\nHost:%s\r\n\r\n" % w.host
				w.socket.send(bytes(http_send_data, encoding="utf-8"))
				self.wconn.remove(w)
			for r in read:
				print(r.host, "开始接收！！！")
				recv_data = bytes()
				while True:  # 确保数据接收完成
					try:
						recv_data += r.socket.recv(8096)
					except Exception:
						break
	
				print(r.host, recv_data)
				r.callback(recv_data)
				#### 服务端
				# response = HttpResponse(recv_data)
				# r.callback(response)
				# r.socket.close()
				##########
	
				self.rconn.remove(r)
			if len(self.rconn) == 0:
				print("结束")
				break


def callback_fun1(*args):
	print(args[0])


def callback_fun2(*args):
	print(args[0])


item_list = [
	{"host": "www.baidu.com", "callback": callback_fun1},
	{"host": "www.163.com", "callback": callback_fun2},
	{"host": "www.cnblogs.com", "callback": callback_fun1}
]

a_req = AsyncRequest()
for item in item_list:
	a_req.add_request(item["host"], item["callback"])
a_req.run()
