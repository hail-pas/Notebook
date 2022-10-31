[#](#) Websocket
	  保持连接，全双工通信 与 消息推送
	  http、websocket 都基于 socket-tcp实现
----
- 请求
	- 请求端js     --基于http单工； 请求-响应； 连接-响应-断开
		- 轮询       --短连接频繁请求
		- 长轮询			--长连接单次持久连接，请求频率降低， 微信web登录25s长连接
	- 服务端    --主动推送
		- websocket    --建立在http协议之上
- 原理
	 magic string = 258EAFA5-E914-47DA-95CA-C5AB0DC85B11
			  Key+magic_string 
			  hashlib.sha1(raw_string.encode("utf-8")).digest()
			  base64.b64encode()
	 更符合socket
	 握手、封包、解包
	- 浏览器创建websocket连接   --script; ajax
		 ws =new WebSocket("ws://ip:port")
		 ws.onopen = function(){ }     --成功握手之后
				 onmessage = function(event){}   --服务端推送的时候
				 onclose - event     --服务器主动断开时
						 event 对象
								  data    封装返回值
		 ws.send()      --发送
	- socket
		- 客户端-浏览器(创建、连接)
		- 服务端(创建、绑定、监听、接受连接)
	- websocket   --基于socket连接完成，多了websocket密钥验证 握手流程
				==================HTTP握手、头部校验=====================
		  客户端  ----------生成Sec-WebSocket-Key并发送-------->  服务端[Key + magic_string；sha1加密再Base64编码]
		  客户端  <----返回处理后生成的Sec-WebSocket-Accept-----  服务端
				客户端接收Sec-WebSocket-Accept后对自己的Sec-WebSocket-Key
							相同处理后对比，值相同则算真正的连接建立成功
				=====================开始收发数据========================
				
		  服务端需要手动封包和解包；JavaScript 封装完成； 与运算 -> 提取部分值
			recv_data[index]  -->  提取第几个字节的位 参照解包
			有框架模块封装
			封包发送：
					import struct      --封包模块；三种方式
					msg_bytes = msg.encode("ytf-8")
					token = b"\x81"           -- 0b10000001        
					length = len(msg_bytes)
					if length < 126:
							token += struct.pack("B", length) 
					elif length <= 0xFFFF:
							token += struct.pack("!BH", 126, length)
					else:
							token += struct.pack("!BQ", 127, length)
 
					msg = token + msg_bytes
					conn.send(msg)			
- tornado+websocket聊天实例
	- websocket请求处理类
		 tornado.websocket.WebSocketHandler 继承
					def open(self, *args, **kwargs):
					def on_message(self, message):
							self.write_message()     --本质是self为ws
					def on_close(self):
	- 保存每个用户ws连接； 消息队列
		- 集合保存ws - 即 self 
					
		
		
		
		
- 8位二进制
		1		1    1	  1		1  1  1  1
	 128  64	 32		16	8	 4  2  1
- 与运算 -> 部分提取
	位运算 
	11110101 >> 2  = 111101   
	11110101 << 2  = 1111010100
	
- 解包-字段参照表
0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-------+-+-------------+-------------------------------+
|F|R|R|R| opcode|M| Payload len |    Extended payload length    |
|I|S|S|S|  (4)  |A|     (7)     |             (16/64)           |
|N|V|V|V|       |S|             |   (if payload len==126/127)   |
| |1|2|3|       |K|             |                               |
+-+-+-+-+-------+-+-------------+ - - - - - - - - - - - - - - - +
|     Extended payload length continued, if payload len == 127  |
+ - - - - - - - - - - - - - - - +-------------------------------+
|                               |Masking-key, if MASK set to 1  |
+-------------------------------+-------------------------------+
| Masking-key (continued)       |          Payload Data         |
+-------------------------------- - - - - - - - - - - - - - - - +
:                     Payload Data continued ...                :
+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - +
|                     Payload Data continued ...                |
+---------------------------------------------------------------+

fin = recv_data[0] >> 7
opcode = recv_data[0] & 15   --后四位
		 上面两个字段应用于长数据分组时
payload_len = recv_data[1] & 127     --头部信息长度
		  <=125   则固定最短长度
		  126                   + 16位
		  127										+ 64位
masking-key ：32位      --数据部分的开头,用于数据解码
数据
		 数据部分解码
		 for i in range(len(data)):
					chunk = data[i] ^ mask_key[i % 4]      --异或运算
					bytes_list.append(chunk)             --获得bytes类型，再统一转换成str，可以正确解中文
