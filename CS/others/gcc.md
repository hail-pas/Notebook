# GCC

## 参数
```shell
-ggdb
-Wall                         # 全部的警告
-fdiagnostics-color=always    # 输出彩色日志
-fsanitize=address            # 動態程序分析, 地址訪問檢查
-fsanitize=thread             # 綫程 data race
-fsanitize=memory             # memory
-fsanitize=ub                 # undefined
-O1                           # 优化 1级， O2 二级优化
-fPIC 和 -shared              # 确保编译输出具有位置无关代码

```

## 其他命令
```sh
# 反汇编
objdump -d xxx

# 动态链接库文件（）
gcc -o lib/memalloc.so -fPIC -shared C/memalloc.c
gcc -o lib/memalloc.dylib -fPIC -dynamiclib C/memalloc.c
```