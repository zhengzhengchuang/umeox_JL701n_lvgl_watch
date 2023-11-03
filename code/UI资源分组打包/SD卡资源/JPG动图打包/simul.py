import struct
import io
import time




import cv2


# 创建一个窗口
cv2.namedWindow('Image', cv2.WINDOW_NORMAL)


def play_jpg_player(filename):
    # 打开 animal.bin 文件
    with open(filename, 'rb') as file:
        # 读取 default 字节
        file.read(8)
        # 读取 JPG 文件数量
        num_files = struct.unpack('i', file.read(4))[0]
        # 读取索引表偏移量
        index_offset = struct.unpack('i', file.read(4))[0]

        # 创建索引表
        index_table = []
        for _ in range(num_files):
            # 读取 JPG 地址和长度
            jpg_address = struct.unpack('<i', file.read(4))[0]
            jpg_length = struct.unpack('<i', file.read(4))[0]
            print(jpg_address,jpg_length)
            # 添加至索引表
            index_table.append((jpg_address, jpg_length))

        # 遍历索引表，逐个播放 JPG 图片
        for jpg_address, jpg_length in index_table:
            # 定位到 JPG 数据位置
            file.seek(jpg_address)
            # 读取 JPG 数据
            jpg_data = file.read(jpg_length)
                
            jpgfile = open("temp.jpg", 'wb+')
            jpgfile.write(jpg_data)
            jpgfile.close()
            
            # 将 JPG 数据加载为图片
            image = cv2.imread("temp.jpg")
            cv2.imshow('Image', image)
            cv2.waitKey(40)

            
play_jpg_player("animal.bin")
            
            
cv2.destroyAllWindows()





