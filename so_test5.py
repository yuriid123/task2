from ctypes import *
import numpy as np
import array as arr
import time


so_testing = CDLL('./so_test5.so')

INPUT = c_int * 7
data1 = INPUT(1, 4, 3, 4, 5, 6, 7)

INPUT = c_int * 3
data2 = INPUT(5, 4, 6)

#.array_sum(data1, len(data1))
#.array_sum(data1, len(data1))
'''
so_testing.array_sum(data1, len(data1))
so_testing.array_sum(data1, len(data1))
so_testing.array_sum(data1, len(data1))
so_testing.array_sum(data1, len(data1))

so_testing.array_sum(data1, len(data1))
so_testing.array_sum(data1, len(data1))

so_testing.array_sum(data1, len(data1))
so_testing.array_sum(data1, len(data1))
so_testing.array_sum(data1, len(data1))
'''	
#so_testing.array_sum(data1, len(data1))

so_testing.array_product(data2, len(data2))
#so_testing.add_prime()
#so_testing.add_unif_ver(2)
#so_testing.add_unif_ver(6)
#so_testing.add_unif_ver(6)
#so_testing.add_unif_ver(6)
#so_testing.add_unif_ver(10)
#so_testing.add_timer(10)
#so_testing.all_tasks_ids()


INPUT = c_int * 6
data3 = INPUT()

INPUT = c_int * 6
data4 = INPUT()

for i in range(6):
	data4[i] = 1

for i in range(20):
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
	



