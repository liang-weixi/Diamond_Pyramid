import numpy as np
import matplotlib.pyplot as plt

# 读取文件
with open('pyramid.txt', 'r') as file:
    lines = file.readlines()

# 将每一行转换为整数列表，并去掉可能存在的换行符
pyramid_data = [list(map(int, line.strip().split(','))) for line in lines]

# 创建一个空的矩阵，用于存放金字塔的数据
max_width = len(pyramid_data[0])
matrix = np.zeros((len(pyramid_data), max_width))

# 填充矩阵
for i, row in enumerate(pyramid_data):
    matrix[i, :len(row)] = row

# 路径数据读取
# with open('path.txt', 'r') as file:
#     lines = file.readlines()
#     path_data = [tuple(map(int, line.strip().split(' '))) for line in lines]

# 创建一个新的矩阵用于标记路径
# path_matrix = np.zeros_like(matrix)

# 标记路径点
# for row, col in path_data:
#     path_matrix[row-1, col] = 1  # 使用1标记路径点
# for row, col in path_data:
#     matrix[row, col] = 110

# 绘制原始金字塔热力图
plt.figure(figsize=(10, 8))
# plt.subplot(1, 2, 1)
plt.imshow(matrix, cmap='Reds', interpolation='nearest')
# plt.imshow(path_matrix, cmap='Reds', interpolation='nearest', alpha=0.7)  # 使用红色半透明覆盖路径
plt.colorbar()
plt.title('Original Pyramid Heatmap')
plt.xlabel('Position in Row')
plt.ylabel('Row Number')

# 绘制带有路径标记的新热力图
# plt.subplot(1, 2, 2)
# plt.colorbar()
# plt.title('Pyramid Heatmap with Path Annotation')
# plt.xlabel('Position in Row')
# plt.ylabel('Row Number')

plt.tight_layout()
plt.show()
