import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

energy_filename = "./ConservedLogs/energy.txt"
linmom_filename= "./ConservedLogs/linmom.txt"
angmom_filename = "./ConservedLogs/angmom.txt"

data_e = pd.read_csv(energy_filename)
data_p = pd.read_csv(linmom_filename)
data_L = pd.read_csv(angmom_filename)

data_p['p_magnitude'] = np.sqrt(data_p['Px']**2 + data_p['Py']**2 + data_p['Pz']**2)
data_L['L_magnitude'] = np.sqrt(data_L['Lx']**2 + data_L['Ly']**2 + data_L['Lz']**2)


#Energy vs Time
plt.plot(data_e["Time"], data_e["Energy"])
plt.xlabel("Time")
plt.ylabel("Energy")
plt.title("Energy Plot")
plt.show()

#Linear Momentum vs Time
plt.subplot(2,2,1)
plt.plot(data_p["Time"], data_p["Px"])
plt.xlabel("Time")
plt.ylabel("x-Momentum")

plt.subplot(2,2,2)
plt.plot(data_p["Time"], data_p["Py"])
plt.xlabel("Time")
plt.ylabel("y-Momentum")

plt.subplot(2,2,3)
plt.plot(data_p["Time"], data_p["Pz"])
plt.xlabel("Time")
plt.ylabel("z-Momentum")

plt.subplot(2,2,4)
plt.plot(data_p["Time"], data_p["p_magnitude"])
plt.xlabel("Time")
plt.ylabel("Total Linear Momentum")

plt.suptitle("Linaer Momentum Plot")
plt.show()

#Angular Momentum vs Time
plt.subplot(2,2,1)
plt.plot(data_L["Time"], data_L["Lx"])
plt.xlabel("Time")
plt.ylabel("x-Angular Momentum")

plt.subplot(2,2,2)
plt.plot(data_L["Time"], data_L["Ly"])
plt.xlabel("Time")
plt.ylabel("y-Angular Momentum")

plt.subplot(2,2,3)
plt.plot(data_L["Time"], data_L["Lz"])
plt.xlabel("Time")
plt.ylabel("z-Angular Momentum")

plt.subplot(2,2,4)
plt.plot(data_L["Time"], data_L["L_magnitude"])
plt.xlabel("Time")
plt.ylabel("Total Angular Momentum")

plt.suptitle("Angular Momentum Plot")
plt.show()


