import matplotlib.pyplot as plt
# from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation
import pandas as pd
import sys

n = len(sys.argv)
filename = "nbodyoutput.txt"
stepsize = 100
trail = -1 #-1 is full, otherwise specifies length
if n>1:
    filename = sys.argv[1]
if n>2:
    stepsize = int(sys.argv[2])
if n>3:
    trail = int(sys.argv[3])

    
    

data = pd.read_csv(filename,skiprows=lambda x: x%stepsize != 0);
print(data.shape)

plt.style.use('dark_background')
fig = plt.figure()
ax = plt.axes(projection = '3d')

def update(frame):
    s = frame
    if trail == -1:
        s = 0
    else :
        s = max(0, frame - trail)
        
    
    ax.cla()
    ax.grid(False)
    # ax.axis('off')
    # colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k']
    i = 1
    while(True):
        try:
            x = data["x"+str(i)][s:frame+1]
            y = data["y"+str(i)][s:frame+1]
            z = data["z"+str(i)][s:frame+1]
            p = ax.plot(x,y,z, label=f'Body {i}')
            ax.scatter(x.iloc[-1], y.iloc[-1], z.iloc[-1], s=5, marker='o', c = p[0].get_color())
            i+=1
        except KeyError:
            break;
    ax.legend()

ani = FuncAnimation(fig, update, frames=range(data.shape[0]), interval = 1, repeat = False)


plt.show()