import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

file_path = 'galaxy_data_3d.csv'

# Read data from the CSV file
data = np.loadtxt(file_path, delimiter=',')

# Extract x, y, z, and potential values
x = data[:, 0]
y = data[:, 1]
z = data[:, 2]
potential = data[:, 3]

# Plot the data in 3D
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')

scatter = ax.scatter(x, y, z, c=potential, cmap='viridis', marker='o', s=10)

ax.set_title('Gravitational Potential of Spiral Galaxy (3D)')
ax.set_xlabel('X Position')
ax.set_ylabel('Y Position')
ax.set_zlabel('Z Position')
ax.axes.set_zlim3d(bottom=-10, top =10)
ax.legend()

# Add colorbar
cbar = fig.colorbar(scatter, ax=ax, label='Gravitational Potential')

plt.show()
