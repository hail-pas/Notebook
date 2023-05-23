# Makefile

## 语法
```shell
$<    # 获取第一个依赖的文件名
$^    # 获取所有的依赖文件名，空格隔开
```

## 命令行
```shell
make -nBf Makefile    # 执行 Makefile 中的命令，但不执行命令 make -nB

make -nB \
  | grep -ve '^\(\#\|echo\|mkdir\|make\)' \
  | sed "s#$AM_HOME#\$AM_HOME#g" \
  | sed "s#$PWD#.#g" \
  | vim -     # 处理执行命令的可读性
```
