# 自习室预约管理系统 - 郑林均负责部分

本目录按设计文档第十条的项目结构整理，包含郑林均负责的链表、哈希表、学生管理、座位管理和基础测试数据。

## 目录结构

```
include/   头文件
src/       C语言源文件
data/      测试数据
docs/      实现说明文档
Makefile   编译脚本
README.md  项目说明
```

## 编译运行

```bash
mingw32-make
study_room_system.exe
```

也可以直接使用：

```bash
gcc -std=c99 -Wall -Wextra -Iinclude src/main.c src/linkedlist.c src/hashtable.c src/student.c src/seat.c src/utils.c -o study_room_system.exe
```
