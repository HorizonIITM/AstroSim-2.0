# AstroSim-2.0
AstroSim code rewritten in a manner such that it is easy to add new integrators and force calculators

# Features:

## - Integrators - RK4, Leapfrog and Euler Integrators
## - Force Calculation - Barnes Hut, and Direct Force Computation
## - Intializers - Asteroid Belt Initializer, and Galaxy Initializer
## - Collisions
## - Plotting and Animation using Python
## - Verification of Results - Total Energy and Total Linear and Angular Momentum Computation

# How to run the code:

## - Choose an Integrator 
    - In "main.cpp" - In Line 34, "Euler" can be changed to "Leapfrog" or "RK4" (RK4 or Leapfrog are recommended).

## - Choose a Force Calculation Method 
    - In "main.cpp" - In Line 34, "BarnesHut" can be changed to "Direct" (BarnesHut recommended when particle_count>1000).
    - The efficieny of the BarnesHut method can be changed by changing the parameter theta found in "BarnesHutTree.h" (recommended value is 0.4-0.5 for large particle counts).

## - Initial Conditions 
    - Initial Conditions can be manually created as per the format mentioned in "Input Instructions.md".
    - It is also possible to create inital conditions for a Galaxy or an Asteroid Belt using the Initializers given.
    - To generate the inital conditions, run "./init.exe <Infile Name> <Initializer Type> <Number of Particles>", where Initializer type is 0 for Asteroids and 1 for Galaxies. 
    - Alternatively, running "make initialize" creates the inital conditions. The input arguments for initializing using "make" can be changed in the Makefile.
    - Additionaly, the initializers can be further customized by varying a few parameters found in the "Asteroid.cpp / gal_int_3d_2.cpp" files.

## - Collisions
    - Inelastic Collisions can be detected and resolved.
    - To enable Collision Detection - In "main.cpp" - In Line 39, "my_solver.CheckCollision" can be set to true and "my_solver.e" (Coefficent of Restitution) can be set to some value between 0 and 1.

## - Verifying Accuracy of the Results
    - The accuracy of the results can be verified by checking if Energy, Linear and Angular Momentum are conserved.
    - By default, the Energy and momentum values are computed every timestep and saved in the "ConservedLogs" folder.
    - To turn of Energy or Momentum computation, comment out lines 103-105 in "Simulator.cpp" using "//".
    - Note that Energy Conservation is O(n^2) which might cause the solver to slow down.
    - The time per iteration can be printed out after every iteration by uncommenting line 117 in "Simulator.cpp".

## - Running the Simulation
    - Build the code using "make build"
    - Run the simulation using "./sim.exe <outfile name> <infile name> <Total time> <Time step>".
    - Alternatively, running "make run" runs the simulation. The input arguments for running the simulation using "make" can be changed in the Makefile.

## - Visualizing the Results
    - Results can be visualized using "make plot", "make 3dplot", and "make animate".
    - The energy and momentum at each timestep can be plotted using "make conservation_plots".