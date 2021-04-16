import pandas as pd
import numpy as np
import matplotlib.pyplot as plt



data = pd.read_csv('data23decay.txt',sep='\s+',header=None)
data = pd.DataFrame(data)
bins = np.arange(min(data[0]), max(data[0]) + 1, 2)
plt.style.use('classic')
plt.hist(data[0], bins=100, histtype='barstacked', color= "aqua")  # density=False would make counts
#plt.title(r"Z0->$\mu_{+}$ + $\mu_{+}$")
plt.ylabel('')
plt.xlabel(r"$pTZ$", size="14")
plt.title(r"Decay of Z boson", size='16')
plt.grid()
plt.xlim(0,5000)
plt.savefig("analysis_decay/Hist23decay.png")
plt.show()
plt.clf()


data = pd.read_csv('data25decay.txt',sep='\s+',header=None)
data = pd.DataFrame(data)
bins = np.arange(min(data[0]), max(data[0]) + 1, 2)
plt.style.use('classic')
plt.hist(data[0], bins=100, histtype='barstacked', color = "red")  # density=False would make counts
plt.ylabel('')
plt.xlabel(r"$pTH$",size="14")
plt.title(r"Decay of Higgs", size="16")
plt.grid()
plt.xlim(0,5000)
plt.savefig("analysis_decay/Hist25decay.png")
plt.show()
