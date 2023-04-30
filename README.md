# rime-table-decompiler

> fork from <https://github.com/whjiang/rime_table_bin_decompiler>  
> 从 cmake 迁移到 xmake。

反编译 Rime 的`xxx.table.bin`文件。

这个项目可以简单的用于反编译 Rime 的`xxx.table.bin`以生成`xxx.dict.yaml`文本文件。

这个项目中的大部分代码是从 librime 源代码中 copy 过来的。

## Usage

```bash
rime-table-decompiler xxx.table.bin > xxx.dict.yaml.
```

> 注意：因为`xxx.table.bin`没有元数据信息，所以生成的`xxx.dict.yaml`的文件头中的元数据是根据常见的元数据填进去的，可能是错误的。用户需要自己进行修改。

## Build

编译方法：(需要安装 xmake, unzip 等工具)

```bash
git clone https://github.com/flowerime/rime-table-decompiler
cd rime-table-decompiler
xmake
```
