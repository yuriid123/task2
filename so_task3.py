from ctypes import *
import numpy as np
import array as arr
import time

so_testing = CDLL('./so_task3.so')

print(np.sctypeDict)

#so_testing.add_foo__task(2000000000)

'''
np_array = np.ones(1100000000, dtype = np.int32)

so_testing.add_foo2_task.argtypes = [np.ctypeslib.ndpointer(dtype=np.int32, ndim=1, flags='C_CONTIGUOUS')]
so_testing.add_foo2_task(np_array, 1100000000)

np_array1 = np.ones(20, dtype = np.int32)
#so_testing.add_foo2_task.argtypes = [np.ctypeslib.ndpointer(dtype=np.float64, ndim=1, flags='C_CONTIGUOUS')]
so_testing.add_foo2_task(np_array1, 20)

#print(sum(np_array))
'''


np_array = np.ones(5000000000, dtype = np.byte)
#print(sum(np_array))

so_testing.add_foo2_mod_task.argtypes = [np.ctypeslib.ndpointer(dtype=np.byte, ndim=1, flags='C_CONTIGUOUS')]
so_testing.add_foo2_mod_task(np_array, 5, 1)

np_array1 = np.ones(20, dtype = np.byte)
#so_testing.add_foo2_task.argtypes = [np.ctypeslib.ndpointer(dtype=np.float64, ndim=1, flags='C_CONTIGUOUS')]
so_testing.add_foo2_mod_task(np_array1, 20, 0)

np_array1 = np.ones(2000000000, dtype = np.byte)
#so_testing.add_foo2_task.argtypes = [np.ctypeslib.ndpointer(dtype=np.float64, ndim=1, flags='C_CONTIGUOUS')]
so_testing.add_foo2_mod_task(np_array1, 2, 1)


'''
INPUT = c_int * 1100000000
data100 = INPUT()
for i in range(len(data100)):
	data100[i] = 1
so_testing.add_foo1_task(data100, len(data100))	
#so_testing.foo1(data100, len(data100))
'''

input_size = 3

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



