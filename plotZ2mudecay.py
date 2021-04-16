import pandas as pd
import numpy as np
import matplotlib.pyplot as plt



data = pd.read_csv('datapTZ2mu.txt',sep='\s+',header=None)
data = pd.DataFrame(data)
bins = np.arange(min(data[0]), max(data[0]) + 1, 4)
plt.style.use('classic')
plt.hist(data[0], bins=100, histtype='barstacked', color= "blue")  # density=False would make counts
#plt.title(r"Z0->$\mu_{+}$ + $\mu_{+}$")
plt.ylabel('')
plt.xlabel(r"$pTZ$", size="14")
plt.title(r"$Z0\longrightarrow \mu_+ + \mu_-$ ", size='16')
plt.grid()
plt.xlim(0,5000)
plt.savefig("analysis_decay/pTZ2mudecay.png")
plt.show()
plt.clf()



