import Rand
import numpy as np
from scipy.stats import norm
from time import perf_counter
import matplotlib.pyplot as plt

gen = Rand.PCG(seed=20)
gen2 = np.random.default_rng(5)

times = []
for i in range(100):
    t1 = perf_counter()
    gen.standard_normal(100000)
    t2 = perf_counter()
    gen2.standard_normal(100000)
    t3 = perf_counter()
    times.append([t2-t1,t3-t2])
mean = np.mean(np.array(times),axis=0)
print(f"custom:{mean[0]}\nnumpy:{mean[1]}")


n1= gen.standard_normal(100000)
n2 = gen2.standard_normal(100000)
print("custom: %d bytes" % (n1.size * n1.itemsize))
print("numpy: %d bytes" % (n2.size * n2.itemsize))





