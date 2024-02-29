import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

energy_filename = "./ConservedLogs/energy.txt"
linmom_filename= "./ConservedLogs/linmom.txt"
angmom_filename = "./ConservedLogs/angmom.txt"

data_e = pd.read_csv(energy_filename)
data_p = pd.read_csv(linmom_filename)
data_L = pd.read_csv(angmom_filename)

data_p['p_magnitude'] = np.sqrt(data_p['px']**2 + data_p['py']**2 + data_p['pz']**2)
data_L['L_magnitude'] = np.sqrt(data_L['Lx']**2 + data_L['Ly']**2 + data_L['Lz']**2)


#Energy vs Time
plt.plot(data_e["time"], data_e["energy"])
plt.xlabel("Time")
plt.ylabel("Energy")
plt.title("Energy Plot")
plt.show()

#Linear Momentum vs Time
plt.subplot(2,2,1)
plt.plot(data_p["time"], data_p["px"])
plt.xlabel("Time")
plt.ylabel("x-Momentum")

plt.subplot(2,2,2)
plt.plot(data_p["time"], data_p["py"])
plt.xlabel("Time")
plt.ylabel("y-Momentum")

plt.subplot(2,2,3)
plt.plot(data_p["time"], data_p["pz"])
plt.xlabel("Time")
plt.ylabel("z-Momentum")

plt.subplot(2,2,4)
plt.plot(data_p["time"], data_p["p_magnitude"])
plt.xlabel("Time")
plt.ylabel("Total Linear Momentum")

plt.suptitle("Linaer Momentum Plot")
plt.show()

#Angular Momentum vs Time
plt.subplot(2,2,1)
plt.plot(data_L["time"], data_L["Lx"])
plt.xlabel("Time")
plt.ylabel("x-Angular Momentum")

plt.subplot(2,2,2)
plt.plot(data_L["time"], data_L["Ly"])
plt.xlabel("Time")
plt.ylabel("y-Angular Momentum")

plt.subplot(2,2,3)
plt.plot(data_L["time"], data_L["Lz"])
plt.xlabel("Time")
plt.ylabel("z-Angular Momentum")

plt.subplot(2,2,4)
plt.plot(data_L["time"], data_L["L_magnitude"])
plt.xlabel("Time")
plt.ylabel("Total Angular Momentum")

plt.suptitle("Angular Momentum Plot")
plt.show()


