import numpy as np
import sys

type = sys.argv[1]

data = list()
for i in range(0,5):
	data.append(np.loadtxt(type+'_metrics_'+str(i)+'_small'))

p_50 = list()
p_99 = list()
for i in range(0,5):
	p_50.append(np.percentile(data[i], 50))
	p_99.append(np.percentile(data[i], 99))

print np.mean(p_50)
print np.mean(p_99)

print np.std(np.array(p_50), axis=0)
print np.std(np.array(p_99), axis=0)
