# 种类

- x86汇编语言：这是应用最广泛的汇编语言之一，用于PC和服务器上的基于Intel或AMD处理器的操作系统和应用程序
- ARM汇编语言：这是应用最广泛的嵌入式处理器架构之一，通常用于移动设备、智能家居、汽车电子等领域
- MIPS汇编语言：这是另一种流行的嵌入式处理器架构，通常用于路由器、交换机和其他网络设备
- PowerPC汇编语言：这是IBM的处理器架构所使用的汇编语言，通常用于高性能计算和服务器领域

# 编译器

- NASM（Netwide Assembler）：NASM是一种广泛使用的x86汇编编译器，可在多个平台上使用，并支持多种输出格式。它具有强大的宏功能和符号处理能力，因此被广泛应用于操作系统和低级软件的开发，并且在Linux内核等开源项目中得到了广泛应用
- MASM（Microsoft Macro Assembler）：MASM是由微软公司开发的一种x86汇编编译器。它是Windows平台上最常用的汇编编译器之一。MASM提供了很多高级功能，例如结构、宏定义和地址计算等，并且同时支持32位和64位的开发。通常用于Windows驱动程序、程序库和DLL等的编写
- FASM（Flat Assembler）：FASM是一种快速、小巧而功能强大的汇编编译器，它支持多种操作系统和CPU体系结构，包括x86和ARM等。它是一个自包含的程序，可以生成可执行文件或二进制文件，不需要任何外部依赖关系。由于其高效性和可移植性，FASM被广泛应用于操作系统、嵌入式设备和游戏引擎等领域

# 进制转换

## 浮点数

```python
# 单精度浮点数采用32位表示，其中1位表示符号位，8位表示指数位，23位表示有效数字，偏移量为 127
# 双精度浮点数采用64位表示，其中1位表示符号位，11位表示指数位，52位表示有效数字，偏移量为 1023
0.1
# 1. 十进制小数转二进制小数: 整数位 / 2 取余; 小数位 * 2 取整
0.00011001100110011...   # 0011 的无限循环
# 2. 规范化处理: (-1)^s * (1 + f) * 2^e
(-1)^0 * (1 + 0.1001100110011...) * 2^(-4)
# s表示符号位、e + 偏移量 表示表示指数位、f的小数部份表示有效位-需要舍入操作
0 01111011 10011001100110011001101

1.1
1.00011001100110011...
(-1)^0 * (1 + 0.00011001100110011...) * 2^(0)
0 01111111 00011001100110011001101
```

# hello

```assembly
; ----------------------------------------------------------------------------------------
; Writes "Hello, World" to the console using only system calls. Runs on 64-bit macOS only.
; To assemble and run:
;
;     nasm -fmacho64 hello.asm && ld hello.o && ./a.out
; ----------------------------------------------------------------------------------------
; label   instruction  operands

          global    start, _main

          section   .text

_main:    call      start

          section   .text
start:    mov       rax, 0x02000004         ; system call for write
          mov       rdi, 1                  ; file handle 1 is stdout
          mov       rsi, message            ; address of string to output
          mov       rdx, 13                 ; number of bytes
          syscall                           ; invoke operating system to do the write
          mov       rax, 0x02000001         ; system call for exit
          xor       rdi, rdi                ; exit code 0
          syscall                           ; invoke operating system to exit

          section   .data
message:  db        "Hello, World", 10      ; note the newline at the end
```

```shell
nasm -fmacho64 hello.asm -o hello.o
# -macosx_version_min 10.13 -lSystem -L $(xcode-select -p)/SDKs/MacOSX.sdk/usr/lib
# macos 系统需要指定链接地址
ld hello.o -o hello -macosx_version_min 10.13 -lSystem -L $(xcode-select -p)/SDKs/MacOSX.sdk/usr/lib -no_pie
```

