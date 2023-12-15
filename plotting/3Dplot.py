import matplotlib.pyplot as plt
import pandas as pd
import sys

n = len(sys.argv)
filename = "nbodyoutput.txt"
stepsize = 1
if(n>1):
    filename = sys.argv[1]
if n>2:
    stepsize = int(sys.argv[2])
    
data = pd.read_csv(filename,skiprows=lambda x: x%stepsize != 0);
print(data.shape)

plt.style.use('dark_background')
fig = plt.figure()
ax = plt.axes(projection = '3d')
i = 1
while(True):
    try:
        ax.plot3D(data["x"+str(i)], data["y"+str(i)], data["z"+str(i)])
        i+=1
    except:
        break;
# ax.grid(False)
# ax.axis('off')
plt.show()