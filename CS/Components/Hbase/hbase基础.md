> 基于Hadoop生态系统，建立在HDFS（二进制流文件形式、高容错性）之上的分布式、面向了列的数据库；适用于实时读写计算、随机访问快速查找

## 数据模型
- 表Table
  - 行Row
  - 列Column =>  CF:CQ （单元格、时间戳）
    - 列族（Column Family）
    - 列限定符（Column Qualifier）



```python
{
  "com.cnn.www": {   # row_key
    contents: {		# column_family
      t6: contents:html: "<html>..."  # t6 -> timestamp;  html -> column_quli
      t5: contents:html: "<html>..."
      t3: contents:html: "<html>..."
    }
    anchor: {
      t9: anchor:cnnsi.com = "CNN"
      t8: anchor:my.look.ca = "CNN.com"
    }
    people: {}
  }
  "com.example.www": {
    contents: {
      t5: contents:html: "<html>..."
    }
    anchor: {}
    people: {
      t5: people:author: "John Doe"
    }
  }
}
```

## Hbase Shell

```shell
hbase shell
quit
# '' => str;  "" => binary
# 创建表
create 't_name', 'columnFamilyName'
enable 't_name'
disable 't_name'
drop 't_name'
# 查看表信息
list [t_name]
# 插入数据
put 't_name', 'row_key', 'columnFamilyName:column_key', 'value'
# 获取数据
get 't_name'
get 't_name', 'row_key', {COLUMN=> 'CF:CQ'}
# 扫描表数据
scan 't_name'
# 插入Non-Ascii数据时
"\xc1".force_encoding("ASCII-8BIT")
# 前缀扫描
scan 't_name',{ROWPREFIXFILTER => 'value'}
```