# Linux Command

----
## Directory   --dirname+basename
- /  --root
	- boot  --系统启动引导加载 - kernel
	- etc  --配置相关、静态
		- bash配置   --source 加载
			- profile   --$PATH
				- 全局 /etc/profile ； /etc/profile.d/*.sh
				- 个人 ~/.bash_profile
			- bashrc
				- 全局 /etc/bashrc
				- 个人 ~/.bashrc
	- home  --普通用户目录
	- mnt  --硬盘上手动挂载的文件系统(临时)
	- media  --自动加载的硬盘分区以及类似CD、数码相机等便携式挂载点
	- opt  --附加应用安装位置
	- root  --系统管理员目录
	- bin  --所有用户可用的必要命令、程序
	- sbin  --系统管理员可用的工具命令、程序
	- dev  --设备文件、特殊 「字符-线性、块设备-随机任意访问」
	- lib  --为系统启动或者根文件系统上的应用程序提供库文件
	- usr  --全局共享只读层级目录
		- local  -- 应用程序安装路径
		- include
		- share
		- lib
	- var  --经常发生变化的数据，如 log
	- proc  --内核及进程存储信息，内核参数
	- sys  --proc的扩展，更好管理系统
	- tmp  --临时文件存储，所有用户可写
	- srv  --当前主机为服务提供的数据
- 文件类型
	- - ： 常规文件
	- d ： 目录文件
	- b ： 块文件
	- l ： 符号链接文件（软）
	- p ： 命名管道，pipe
	- s ： socket 套接字文件
- 权限
	- drwxrwxrwx  所属用户  所属用户组  大小
----
## Command
- python里面运行命令：os.system("COMMAND")  ==> subprocess.Popen() 或 subprocess.getout("")
- locale  --查看支持的编码
- 时间
	- date +"%Y %m %d %H:%M:%S"
		- -s ""  --修改时间 “20190815”->默认00:00:00 ；"11:36:11"->日期不变； "11:36:11 2019-08-25"
	- tzselect  --时区选择
	- cal 2019  --查看日历  -y当前年
- passwd username --修改密码，无参为当前
- 关机
	- reboot  -- ==> shutdown -r now
	- shutdown -r/h now/+5/14:14 "Notice text"  ==> shutdown -c 取消
- ls -a/A  --显示/(不显. ..)所有
- cp -rp  --递归复制，保留权限、时间戳信息
- stat filename  --查看文件信息
- wc -w/l/c/m  --统计， c字节、m是字符
- sort -r/n/t/k --排序，n以整体大小排序，-t "指明分隔符" -k int   选取int个以分隔符的分开的字符做排序标准
- uniq -i/c/u   --i 忽略大小写；c进行计数；u 显示不重复行
- cut  --选取每行的特定部分， -d 制定分隔符 -f int，int1-int2 
- alias xx="COMMAND [option]"
- chmod  --权限更改、chown
- 用户  /etc/passwd
	- useradd、userdel、usermod
- 查找
	- locate path/fi   --寻找包含字段的路径，不扫描磁盘，自建缓存索引库
		- -i   --忽略大小写
		- -b   --基名匹配
		- -c   --输出计数
	- find /path/
		- -name "xxx"    --大小写，支持正则匹配
		- -i   --忽略大小写
		- -type f   --f 普通文件/d 目录/l 符号链接/c 字符设备/b 块设备/s 套接字/p fifo管道
		- -size [+|-] #UNIT   --指定大小，大于、小于该大小
		- -perm [/|-] 777    --权限索引， /满足一位即可；-全都要满足
		- -mtime [+|-] int    --多少天发生改变 atime-访问；ctime-属性改变
		- -newer file    --比file新   -newer file1 ! -newer file2 :在file1和file2之间
		- -user UN   --uid
		- group GN   --gid
		- -nouser   --nogroup
		- 查找结果引用
			- find / -perm /002 -exec mv {} {}.danger \;
			- find .... |xargs COMMAND    --find结果过多
		- mount   --umount
			- -o ro    --read only
- crontab    --定时任务，存在指定文件中，以行为单位,不超过64字节，太长的写到文件， /bin/bash引用执行
	- -u user   --设置指定用户的定时任务，默认当前用户
	- -e    --编辑
	- -l    --显示
	- -r    --删除
	- -i    --交互提醒，配合删除使用
	- 任务格式
	- *   *   *   *   *  command to be execute
		|   |   |   |   |
		|   |   |   |   ---- 星期（0 or 7表示星期日）
		|   |   |   -------- 月份 1～12
		|   |   ------------ 日期 1～31
		|   ---------------- 小时 0～23
		-------------------- 分钟 1～59      每n    **/n 表示; 每1 还可以是 '**'
- tar    --压缩
	- -c    --建立一个压缩文件
	- -x    --解开
	- -t    --查看tarfile里的文件
	- -z    --使用gzip压缩
	- -j    --使用bzip2压缩
	- -v    --显示压缩过程
	- -f    --指定压缩文件，最后一个参数，接文件名
	- -r    --向压缩归档文件末尾追加文件
	- 1、*.tar 用 tar –xvf 解压 
　　2、*.gz 用 gzip -d或者gunzip 解压 
　　3、.tar.gz和.tgz 用 tar –xzf 解压 
　　4、*.bz2 用 bzip2 -d或者用bunzip2 解压 
　　5、*.tar.bz2用tar –xjf 解压 
　　6、*.Z 用 uncompress 解压 
　　7、*.tar.Z 用tar –xZf 解压 
　　8、*.rar 用 unrar 解压 
　　9、*.zip 用 unzip 解压
- sed     --行处理
	- -n    --使用安静模式，只输出被sed处理的行
	- -e    --对获取到的行执行命令
	- -f    --sed的动作写到文件
	- -r    --使用扩展正则，默认是基础正则
	- -i    --直接修改文件内容，不输出
	- #d    --指定行执行*动作*，  $= 总行数，#1，#2d   #1至#2行
		- +a   --新增  "#"a"text"
		- +c   --取代  $ 表示最后一行
		- +d   --取代   sed "/rege/,#d"    删除匹配正则行之后的#行
										sed "#1,+#2d"     删除第#1行之后，再删除#2行
										sed "#1,~#2d"     从#1行开始，共删除#2行       
										sed "#1-#2d"      删除第#1行，后面每#2行删一行
		- +i   --插入  "#"i"text"
		- -n #p    --打印，"\$p"打印最后一行
		- +s   --替换    "s/new/old/g"     分组引用  \i;括号需要转义为特殊字符
- awk    --列切片   awk -F":" 'BEGIN{} 判别式 {print $$1,$$2}END{}'
	- -F    --指定分隔符，分成域
	- -f script.awk     --指定文件
	- -varname=value    --创建变量
	- 常量
		- FNR
		- NR
		- NF    --最后一域 $NF
		- FS    --分隔符
		- ARGC    --参数个数
		- ARGV    --list,参数值
		- FILENAME    --文件名
		- awk 'BEGIN{printf "%4s %4s %4s %4s %4s %4s %4s %4s %4s\n",
										"FILENAME","ARGC","FNR","FS","NF","NR","OFS","ORS","RS";
										printf "---------------------------------------------\n"} 
									{printf "%4s %4s %4s %4s %4s %4s %4s %4s %4s\n",
										FILENAME,ARGC,FNR,FS,NF,NR,OFS,ORS,RS}'  log.txt
				FILENAME ARGC  FNR   FS   NF   NR  OFS  ORS   RS
				---------------------------------------------
				log.txt    2    1         5    1
				log.txt    2    2         5    2
				log.txt    2    3         3    3
				log.txt    2    4         4    4
- vim
	- 替换-命令模式下
		- s/old/new            当前行的第一个old匹配项
		- s/old/new/g          当前行的所有匹配项
		- #1，#2s/old/new/     在#1至#2行之间的所有匹配项
		- %s/old/new/g         整个文件范围
		-           /c         每个替换都提示
----
## I/O重定向
- stdin、stdout、stderr
-   0  、  1   、  2   
- > 覆盖    -- <输入
- >> 追加
- &>   --合并正常和错误输出
