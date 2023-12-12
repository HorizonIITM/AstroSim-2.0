import matplotlib.pyplot as plt
import pandas as pd
import sys

n = len(sys.argv)

filename = "nbodyoutput.txt"
if(n>1):
    filename = sys.argv[1]

data = pd.read_csv(filename);

i = 1
while(True):
    try:
        plt.plot(data["x"+str(i)],data["y"+str(i)])
        i+=1
    except:
        break;
plt.show()



# #from ashwin
# from matplotlib.animation import FuncAnimation
# import matplotlib.animation as animation


# x1 = data["x1"]
# y1 = data["y1"]
# x2 = data["x2"]
# y2 = data["y2"]
# x3 = data["x3"]
# y3 = data["y3"]

# plt.style.use('dark_background')
# fig = plt.figure()
# ax = plt.axes()
# ax.set_ylim(-500,500)
# ax.set_xlim(-500,500)
# ax.set_aspect(1)
# p1 = plt.Circle((0,0), 2e-2, color="blue")
# ax.add_artist(p1)
# p2 = plt.Circle((0,0), 2e-2, color="orange")
# ax.add_artist(p2)
# p3 = plt.Circle((0,0), 2e-2, color="green")
# ax.add_artist(p3)
# def anim_func(i):
#   ax.plot(x1[:i], y1[:i],color="blue")
#   ax.plot(x2[:i], y2[:i],color="orange")
#   ax.plot(x3[:i], y3[:i],color="green")
#   p1.center = x1[i],y1[i]
#   p2.center = x2[i],y2[i]
#   p2.center = x3[i],y3[i]
# anim = FuncAnimation(fig, anim_func, frames =  2000000,interval = 1)

# writervideo = animation.FFMpegWriter(fps=60)
# anim.save('nbody.mp4', writer=writervideo)
# plt.close()