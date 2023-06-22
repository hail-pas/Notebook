# Clang Command
```shell
# 高级语言：预处理 -> 编译 -> 汇编 -> 链接 -> 可执行文件
# main.c

# 1. 预编译/预处理
clang -E main.c -o main.i
# 2. 编译 -> 汇编文件
clang -S main.c -o mian.s
clang -S main.i -o mian.s
# 3. 汇编 -> 目标文件;  汇编代码 --> 机器码， 除去标签、符号； nm -n -m main.o 查看符号表
as main.s -o main.o
# 4. 链接 -> 可执行文件； 符号定位的功能，确定undefine的外部符号
ld -e _main main.o -o main -lSystem  # 默认入口 _main
clang main.s -o main
# 5. 可执行文件的执行阶段的动态链接
# 5.1 生成动态链接库
cc -shared tomato.c -o libfruit.so
# 5.2 链接动态链接库，
# -L. 告诉链接器链接时额外搜索目录为当前目录
# -lfruit  查找静态库名是：libadd.a 或 动态库名是：libadd.so，优先动态链接库
cc test.c -L. -lfruit -o main
# 库函数都放在 *.dylib; -lSystem选项实质上就是链接了动态链接库libSystem.dylib
# 链接器如果遇到动态链接库，那么只会给符号重定位，而不会将代码整合到可执行文件中；执行时动态链接器 dyld 将链接的动态库装载进逻辑地址空间（做映射），解决多个拷贝和动态升级
otool -L test # 查看可执行文件链接的动态链接库
# 查看汇编指令
otool -v -t main
# 查看DATA段
otool -v -s __DATA __data main
```