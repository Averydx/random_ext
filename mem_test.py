import Rand

gen = Rand.PCG(seed=20)

while(True):
    gen.standard_normal(1000000)
