## 操作项

> -ggdb -Wall

### 执行控制

```shell
-exec [GDB-COMMAND] # 直接执行不生效的时候

gdb -x init.gdb     # 从文件中读取命令调试
target remote localhost:1234    # 连接远程调试
set scheduler-locking on        # 多綫程調試下可以暫停其他綫程執行

b *address          # 在指定地址处设置断点  break
b lineNumber        # 在指定行号处设置断点
b funcname          # 在指定函數名稱設置斷點
b [] if []          # 条件断点 b sum_to if i == 5
watch [address]     # 设置监视点，当监视点的值发生变化时，程序会停下来。并且知道内存是谁改的
delete [bnum]       # 删除断点, 不指定则删除全部
disable/enable [bnum]      # 禁用断点

c                   # 继续执行到下一个断点处 continue

start               # 開始調試執行
starti [address]    # 定开始执行指令的地址，默认为程序入口地址。

si [count]          # 执行一条或多条机器指令，可指定执行的条数。默认为 1        stepi， 会进入函数调用
finish              # 跳出s进入的函数
ni                  # next instruction（下一条指令） 它会一次性执行完整条指令，而不会进入函数调用
n                   # next  next instruction（下一条指令）, 不会进入函数调用

record full         # 記錄全部執行記錄, 然后才能使用回溯调试
rsi [COUNT]         # 回退count步, reverse-stepi
reverse-            # continue/next/finish/nexti/search/step/stepi

step                # 步进执行，会进入函数调用、系统调用
continue            # 继续执行，直到遇到断点或程序结束

!command            # 执行shell命令, !cat
```

### 查看数据

```shell
layout asm          # 显示反汇编窗口
layout src          # 显示源代码窗口
layout split        # 同时显示反汇编和源代码窗口
focus [asm|src|split|regs]      # 聚焦切换窗口

info registers      # 查看所有寄存器的值
info register [reg] # 查看某个寄存器的值
info locals         # 查看当前本地变量
info threads        # 查看綫程
info frame          # 查看当前栈帧Stack Frame信息
backtrace           # 查看从当前调用栈开始的所有Stack Frame
frame [i]           # 定位到序号为 i 的 Stack Frame
thread [num]        # 切換到綫程num
info inferiors      # 查看进程
!pmap  processid    # 查看指定进程ID的map
info proc mappings  # 查看进程maps，等价于上面的两句指令
info breakpoints    # info b

display [address]   # 实时显示某个地址变量的值
print [address]     # 打印某个地址变量的值
p a@n               # 打印数组的前n个元素、缺省则打印全部， p *argv@argc

x /x [address]      # 以指定格式显示内存中的内容
x/ni [addr]         # 输出addr 所在n行 asm
p /c $register      # 打印寄存器的字符值 char
p /x $register      # 打印寄存器的十六进制值 hex

x/10i $cs * 16 + $rip       # 显示保护模式下当前执行代码额后10行汇编代码
x/10x $cs * 16 + $rip       # 显示保护模式下当前执行代码额后10行机器代码 - 存储内容


#### 系统内核中调试 user mode code
1. riscv64-unknown-elf-gdb kernel/kernel    #指定架构的gdb
2. file user/_echo                          # 指定user mode file
```

### strace

> strace - trace system calls and signals

```shell
strace -f gcc hello.c &> strace.log

```

### external tools

- [gdbgui](https://github.com/cs01/gdbgui)


### problem

1.MacOS code sign
```
1. Open Keychain Access.app
2. In menu, open Keychain Access > Certificate Assistant > Create a certificate
3. Give it a name (e.g. gdbc)
    Identity type: Self Signed Root
    Certificate type: Code Signing
    Check: let me override defaults
4. Continue until "specify a location for..."
    Set Keychain location to System
    Create certificate and close Certificate Assistant.
5. Find certificate in System keychain.
6. Double click certificate
7. Expand Trust, set Code signing to always trust
8. Restart taskgated in terminal:
    killall taskgated
9. Create: gdb-entitlement.xml

<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN"
"http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>com.apple.security.cs.allow-jit</key>
    <true/>
    <key>com.apple.security.cs.allow-unsigned-executable-memory</key>
    <true/>
    <key>com.apple.security.cs.allow-dyld-environment-variables</key>
    <true/>
    <key>com.apple.security.cs.disable-library-validation</key>
    <true/>
    <key>com.apple.security.cs.disable-executable-page-protection</key>
    <true/>
    <key>com.apple.security.cs.debugger</key>
    <true/>
    <key>com.apple.security.get-task-allow</key>
    <true/>
</dict>
</plist>

10. Codesign gdb using your certificate:
    codesign -fs gdbc /usr/local/bin/gdb

11. add to ~/.gdbinit
    set startup-with-shell enable
12. terminal enbale debug mode
    sudo DevToolsSecurity -enable
```