## 操作项

### 执行控制
```shell
watch [address]     # 设置监视点，当监视点的值发生变化时，程序会停下来。

starti [address]    # 定开始执行指令的地址，默认为程序入口地址。
si [count]          # 执行一条或多条机器指令，可指定执行的条数。默认为 1

ni                  # next instruction（下一条指令） 它会一次性执行完整条指令，而不会进入函数调用
step                # 步进执行，会进入函数调用、系统调用

```


### 查看数据
```shell
layout asm          # 显示反汇编窗口
info registers      # 查看所有寄存器的值
info register [reg] # 查看某个寄存器的值
display [address]   # 实时显示某个地址变量的值
print [address]     # 打印某个地址变量的值
p /x $register      # 打印寄存器的十六进制值
p a@n               # 打印数组的前n个元素、缺省则打印全部
x /x [address]         # 以指定格式显示内存中的内容
```