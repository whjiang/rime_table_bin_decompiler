# rime_table_bin_decompiler
decompile a rime xxx.table.bin file

This project is simply used to decompile a RIME xxx.table.bin file to generate a xxx.dict.yaml file. 

The code is mainly copied from RIME source tree as I can't get RIME be compiled on my desktop.

Usage:
```
rime_decode xxx.table.bin >xxx.dict.yaml.
```

NOTE: The header of generated xxx.dict.yaml SHOULD be modified manually as this tool CAN'T read these meta info from xxx.table.bin.
