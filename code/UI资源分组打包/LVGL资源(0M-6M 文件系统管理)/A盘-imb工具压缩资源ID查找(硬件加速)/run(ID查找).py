import os
import re
#from PIL import Image


# 构建文件路径
run_bat_path = os.path.join('imbtools', 'Run.bat')

print(run_bat_path)

# 检查文件是否存在
if os.path.exists(run_bat_path):
    # 进入文件夹路径
    os.chdir("imbtools")
    
    # 执行Run.bat
    os.system('start /wait cmd /c Run.bat')
    
    # 返回上一级目录
    os.chdir('..')

# 读取头文件内容
with open("./imbtools/output/ui_pic_index.h", "r") as file:
    code = file.read()

# 提取常量数值和路径
pattern = r"#define\s+(\w+)\s+(\w+)\s*//\s*(.*)"
matches = re.finditer(pattern, code)

# 构建常量、数值和路径的列表
constants = []
for match in matches:
    constant = match.group(1)
    value = match.group(2)
    path = match.group(3)
    constants.append((constant, value, path))

# 检查路径是否已按大小排序
# is_sorted = all(constants[i][2] <= constants[i+1][2] for i in range(len(constants)-1))
# if not is_sorted:
#     print("文件名没有排序，重新排序")
#     constants = sorted(constants, key=lambda x: x[2])  # 按路径排序

# 暂停并输出常量列表
print("常量列表：")
for (constant, value, path) in constants:
    path = path.replace("\\", "/")
    print(f"Constant: {constant}, Value: {value}, Path: {path}") 

# 定义文件路径
output_path = "output/usr_pic_index.h"



# 创建usr_pic_index.c文件
with open(output_path, "w") as f:
    f.write("#ifndef __usr_pic_index__\n")     
    f.write("#define __usr_pic_index__\n")   
    for (constant, value, path) in constants:
        filename = os.path.basename(path)
        id_name = constant.upper().replace(".", "_").replace("~", "_")
        f.write(f"#define A_{id_name}\t\t\t\"{int(value,16)}\"\n")      
    f.write("#endif")   
        
 
    
    
os.replace("imbtools/output/ui.res", "./output/ui.res")
os.replace("imbtools/output/ui_pic_index.h", "./output/ui_pic_index.h")
    
# 加入暂停
input("按回车键继续执行...")      
    
# 复制imbtools/output/ui_pic_index.h文件到Smartwatch_lvgl/ui/jl_images/
#import shutil
#shutil.copy(imbtools_path, "Smartwatch_lvgl/ui/jl_images/")
