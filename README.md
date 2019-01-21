# rime_table_bin_decompiler
反编译 Rime 的`xxx.table.bin`文件。

这个项目可以简单的用于反编译Rime的`xxx.table.bin`以生成`xxx.dict.yaml`文本文件。

这个项目中的大部分代码是从LIBRIME源代码中copy过来的，因为我没法在我的Macbook上编译librime。

编译方法：(需要安装cmake, make等工具和boost库)
```bash
cmake .
make
```

用法:
```
rime_table_bin_decompiler xxx.table.bin >xxx.dict.yaml.
```

注意：因为`xxx.table.bin`没有元数据信息，所以生成的`xxx.dict.yaml`的文件头中的元数据是根据常见的元数据填进去的，可能是错误的。用户需要自己进行修改。
