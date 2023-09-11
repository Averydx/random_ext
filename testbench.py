import rand_old
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import norm 
from time import perf_counter

gen = rand_old.Generator(0)

t1=perf_counter()
arr = gen.standard_normal(100000)
t2=perf_counter()

print(f"{t2-t1}")


gen2 = np.random.default_rng(0)
t3 = perf_counter()
arr2 = gen2.standard_normal(100000)
t4 = perf_counter()

print(f"{t4-t3}")

normed = np.array([norm.pdf(x) for x in arr])
normed2 = np.array([norm.pdf(x) for x in arr2])
plt.scatter(arr,normed,s=0.1)
plt.scatter(arr2,normed2,s=0.1,color="red")
plt.show()



