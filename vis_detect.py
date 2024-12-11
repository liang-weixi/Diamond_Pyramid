import numpy as np
import matplotlib.pyplot as plt

x_values = []
count = []

with open('val_results_x.txt', 'r') as values:
    line_number = 0
    for value in values:
        x_values.append(float(value))
        count.append(line_number)
        line_number += 1

plt.plot(count, x_values, label='探测范围与最终价值关系')
plt.xlabel('探测范围')
plt.ylabel('最终价值')
plt.title('探测范围与最终价值关系')
plt.legend()
plt.show()