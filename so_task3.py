from ctypes import *
import numpy as np
import array as arr
import time

so_testing = CDLL('./so_task3.so')

so_testing.foo_(2100000000)

'''
np_array = np.ones(600000000, dtype = np.float64)
#so_testing.foo1()
so_testing.foo2.argtypes = [np.ctypeslib.ndpointer(dtype=np.float64, ndim=1, flags='C_CONTIGUOUS')]
so_testing.foo2(np_array, 600000000)


INPUT = c_int * 1000000000
data100 = INPUT()
for i in range(len(data100)):
	data100[i] = 1
so_testing.foo1(data100, len(data100))	
'''

INPUT = c_int * 7
data1 = INPUT(1, 4, 3, 4, 5, 6, 7)

INPUT = c_int * 3
data2 = INPUT(5, 4, 6)

so_testing.array_sum(data1, len(data1))
so_testing.array_sum(data1, len(data1))
so_testing.array_sum(data1, len(data1))
so_testing.array_sum(data1, len(data1))

so_testing.array_sum(data1, len(data1))

so_testing.array_product(data2, len(data2))

input_size = 6

INPUT = c_int * input_size

data3 = INPUT()

data4 = INPUT()

for i in range(input_size):
	data4[i] = 1

while True:
	so_testing.foo(data3, data4, len(data3))
	print ("\ntask_id_python")
	k = 0
	for j in range(len(data3)):
		if data4[j] == 0:
			print(data3[j], "\t\t\tв очереди/выполняется")
			k += 1
		else:
			print(data3[j], "\t\t\tвыполнено")
	if k == 0:
		break
	time.sleep(10)
	



