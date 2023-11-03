'''
最终输出文件：output.bin

打包格式：
-------------------------------------------------------------------
|                                                                   
|                   第一个bin文件起始地址(4 byte)                      
|
-------------------------------------------------------------------
|
|                      所有bin文件长度(4 byte)
|
-------------------------------------------------------------------
|
|                         文件个数(4 byte)
|
-------------------------------------------------------------------
|
|                  文件信息表长度len (4 byte)
|
-------------------------------------------------------------------
|
|   文件信息表：
|       1.bin起始地址+bin长度
|       2.bin起始地址+bin长度
|       3.bin起始地址+bin长度
|       ......
|
-------------------------------------------------------------------
|
|   bin文件:
|       1.bin
|       2.bin
|       3.bin
|       ......
|
-------------------------------------------------------------------
'''


import os
import struct

# 获取所有文件并根据文件名排序
files = sorted(os.listdir("IMG"))

# 计算文件总长度及索引表长度
total_length = 0
index_length = 8 + len(files) * 8

# 计算每个文件的起始地址与长度
file_info = []
for file in files:
    file_path = os.path.join("IMG", file)
    file_size = os.path.getsize(file_path)
    total_length += file_size
    file_info.append((0, file_size))  # 初始的起始地址为0，具体的起始地址在后面设置
    print(file)

# 计算起始地址对齐的偏移量
alignment = (4 - (index_length % 4)) % 4

bin_start = index_length + alignment + 8
# 计算各文件的起始地址
current_address = bin_start#4 + 
for i in range(len(file_info)):
    # 针对起始地址进行 4 字节对齐
    current_address = (current_address + 3) & ~3
    file_info[i] = (current_address, file_info[i][1])
    current_address += file_info[i][1]

# 创建bin文件
with open("animal.bin", "wb") as output:
    # 写入索引表头信息
    output.write(struct.pack("I", bin_start))  # bin起始地址
    output.write(struct.pack("I", total_length))  # bin总长度
    output.write(struct.pack("I", len(files)))  # 文件总个数
    output.write(struct.pack("I", 8))  # 表的长度固定为8
    
    # 写入索引表
    for info in file_info:
        output.write(struct.pack("I", info[0]))  # 起始地址
        output.write(struct.pack("I", info[1]))  # 长度
    
    # 写入文件数据
    for file in files:
        file_path = os.path.join("IMG", file)
        with open(file_path, "rb") as input_file:
            temp = input_file.read()
            output.write(temp)
            if len(temp)%4 == 0:
                offset = 0
            else :
                offset = 4-len(temp)%4
            output.write(b'\x00' * offset)  # 向文件写入长度为n的空字节

# 暂停，等待用户按回车继续
input("生成步骤结束 按回车键继续...")
 