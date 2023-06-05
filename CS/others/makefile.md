# Makefile

## 语法
```shell

$@            # 目標名稱
$<            # 获取第一个依赖的文件名
$^            # 获取所有的依赖文件名，u

$(VARNAME)    # 獲取環境變量, export VARNAME="xxx"
$(ALL_OBJS:%.o=%.lo)      # 通配符截取或替換,此為將.o替換為.lo後綴

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
