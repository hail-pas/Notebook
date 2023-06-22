## 操作项
> -ggdb -Wall

### 执行控制
```shell
gdb -x init.gdb     # 从文件中读取命令调试
target remote localhost:1234    # 连接远程调试
set scheduler-locking on        # 多綫程調試下可以暫停其他綫程執行

b *address          # 在指定地址处设置断点
b lineNumber        # 在指定行号处设置断点
b funcname          # 在指定函數名稱設置斷點
watch [address]     # 设置监视点，当监视点的值发生变化时，程序会停下来。并且知道内存是谁改的

start               # 開始調試執行
starti [address]    # 定开始执行指令的地址，默认为程序入口地址。

si [count]          # 执行一条或多条机器指令，可指定执行的条数。默认为 1
ni                  # next instruction（下一条指令） 它会一次性执行完整条指令，而不会进入函数调用

record full         # 記錄全部執行記錄
rsi [COUNT]         # 回退count步

step                # 步进执行，会进入函数调用、系统调用
continue            # 继续执行，直到遇到断点或程序结束

!command            # 执行shell命令, !cat
```


### 查看数据
```shell
layout asm          # 显示反汇编窗口
layout src          # 显示源代码窗口

info registers      # 查看所有寄存器的值
info register [reg] # 查看某个寄存器的值
info threads        # 查看綫程
thread [num]        # 切換到綫程num
info inferiors      # 查看进程
!pmap  processid    # 查看指定进程ID的map
info proc mappings  # 查看进程maps，等价于上面的两句指令

display [address]   # 实时显示某个地址变量的值
print [address]     # 打印某个地址变量的值
p a@n               # 打印数组的前n个元素、缺省则打印全部

x /x [address]      # 以指定格式显示内存中的内容
p /c $register      # 打印寄存器的字符值 char
p /x $register      # 打印寄存器的十六进制值 hex

x/10i $cs * 16 + $rip       # 显示保护模式下当前执行代码额后10行汇编代码
x/10x $cs * 16 + $rip       # 显示保护模式下当前执行代码额后10行机器代码 - 存储内容
```

### strace
> strace - trace system calls and signals

```shell
strace -f gcc hello.c &> strace.log

```

### external tools
- [gdbgui](https://github.com/cs01/gdbgui)