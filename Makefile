CCFLAGS=-O3 -std=c++17

CCFLAGS_DEBUG=-g -Og -fsanitize=address

build:
	g++ $(CCFLAGS) -fopenmp -c Body/body.cpp     							-o Body/body.o

	g++ $(CCFLAGS) -fopenmp -c Collision/Collision.cpp     					-o Collision/Collision.o

	g++ $(CCFLAGS) -fopenmp -c ForceCalculators/ForceCalculator.cpp  		-o ForceCalculators/ForceCalculator.o
	g++ $(CCFLAGS) -fopenmp -c ForceCalculators/DirectForceCalculator.cpp  	-o ForceCalculators/DirectForceCalculator.o 
	g++ $(CCFLAGS) -fopenmp -c ForceCalculators/BarnesHutForceCalculator.cpp  				-o ForceCalculators/BarnesHutForceCalculator.o  			
	g++ $(CCFLAGS) -fopenmp -c Integrators/Integrator.cpp					-o Integrators/Integrator.o
	g++ $(CCFLAGS) -fopenmp -c Integrators/EulerIntegrator.cpp				-o Integrators/EulerIntegrator.o
	g++ $(CCFLAGS) -fopenmp -c Integrators/RK4Integrator.cpp				    -o Integrators/RK4Integrator.o
	g++ $(CCFLAGS) -fopenmp -c Integrators/LeapfrogIntegrator.cpp		    -o Integrators/LeapfrogIntegrator.o

	
	g++ $(CCFLAGS) -fopenmp -c Simulator/Simulator.cpp						-o Simulator/Simulator.o

	g++ $(CCFLAGS) -fopenmp -c Utils/utils.cpp 								-o Utils/utils.o
	g++ $(CCFLAGS) -fopenmp -c Utils/vector_n.cpp 							-o Utils/vector_n.o
	g++ $(CCFLAGS) -fopenmp -c Utils/vector3.cpp 							-o Utils/vector3.o
	g++ $(CCFLAGS) -fopenmp -c Utils/BarnesHutTree.cpp 							-o Utils/BarnesHutTree.o


	g++ $(CCFLAGS) -fopenmp -c Initializers/AllInitializers.cpp 							-o Initializers/AllInitializers.o
	g++ $(CCFLAGS) -fopenmp -c Initializers/Asteroid.cpp 							-o Initializers/Asteroid.o


	g++ $(CCFLAGS) -fopenmp -o sim.exe main.cpp Simulator/Simulator.o Collision/Collision.o Integrators/LeapfrogIntegrator.o Integrators/EulerIntegrator.o Integrators/RK4Integrator.o Integrators/Integrator.o ForceCalculators/DirectForceCalculator.o ForceCalculators/BarnesHutForceCalculator.o ForceCalculators/ForceCalculator.o  Body/body.o Utils/utils.o Utils/vector_n.o Utils/vector3.o Utils/BarnesHutTree.o

	g++ $(CCFLAGS) -fopenmp -o init.exe Initializers/AllInitializers.o Initializers/Asteroid.o Utils/utils.o Utils/vector_n.o Utils/vector3.o

debug:
	g++ $(CCFLAGS_DEBUG) -fopenmp -c Body/body.cpp     							-o Body/body.o

	g++ $(CCFLAGS_DEBUG) -fopenmp -c Collision/Collision.cpp     					    -o Collision/Collision.o

	g++ $(CCFLAGS_DEBUG) -fopenmp -c ForceCalculators/ForceCalculator.cpp  		-o ForceCalculators/ForceCalculator.o
	g++ $(CCFLAGS_DEBUG) -fopenmp -c ForceCalculators/DirectForceCalculator.cpp 	-o ForceCalculators/DirectForceCalculator.o
	g++ $(CCFLAGS_DEBUG) -fopenmp -c ForceCalculators/BarnesHutForceCalculator.cpp  				-o ForceCalculators/BarnesHutForceCalculator.o  			
	g++ $(CCFLAGS_DEBUG) -fopenmp -c Integrators/Integrator.cpp					-o Integrators/Integrator.o
	g++ $(CCFLAGS_DEBUG) -fopenmp -c Integrators/EulerIntegrator.cpp				-o Integrators/EulerIntegrator.o
	g++ $(CCFLAGS_DEBUG) -fopenmp -c Integrators/RK4Integrator.cpp				-o Integrators/RK4Integrator.o
	g++ $(CCFLAGS_DEBUG) -fopenmp -c Integrators/LeapfrogIntegrator.cpp		    -o Integrators/LeapfrogIntegrator.o
	
	g++ $(CCFLAGS_DEBUG) -fopenmp -c Simulator/Simulator.cpp						-o Simulator/Simulator.o

	g++ $(CCFLAGS_DEBUG) -fopenmp -c Utils/utils.cpp 							-o Utils/utils.o
	g++ $(CCFLAGS_DEBUG) -fopenmp -c Utils/vector_n.cpp 							-o Utils/vector_n.o
	g++ $(CCFLAGS_DEBUG) -fopenmp -c Utils/vector3.cpp 							-o Utils/vector3.o
	g++ $(CCFLAGS_DEBUG) -fopenmp -c Utils/BarnesHutTree.cpp 							-o Utils/BarnesHutTree.o

	g++ $(CCFLAGS) -fopenmp -c Initializers/Asteroid.cpp 							-o Initializers/Asteroid.o


	g++ $(CCFLAGS_DEBUG) -fopenmp -o sim.exe main.cpp Simulator/Simulator.o Collision/Collision.o Integrators/LeapfrogIntegrator.o Integrators/EulerIntegrator.o Integrators/RK4Integrator.o Integrators/Integrator.o ForceCalculators/DirectForceCalculator.o ForceCalculators/BarnesHutForceCalculator.o ForceCalculators/ForceCalculator.o  Body/body.o Utils/utils.o Utils/vector_n.o Utils/vector3.o Utils/BarnesHutTree.o

	g++ $(CCFLAGS_DEBUG) -fopenmp -o init.exe Initializers/AllInitializers.o Initializers/Asteroid.o Utils/utils.o Utils/vector_n.o Utils/vector3.o

run:
	sim.exe "outfile.txt" "infile.txt" 2000 0.01 0 0

conservation_plots: 
	python plotting/conservationplots.py

initialize:
	init.exe 0 1000 "infile.txt"

plot:
	python3 plotting/plot.py "outfile.txt"

3dplot:
	python3 plotting/3Dplot.py "outfile.txt" 10

animate:
	python plotting/animate.py "outfile.txt" 100 10

clean:
	rm -f */*.o
	rm -f outfile.txt
	rm -f sim.exe
	rm -f init.exe

runplot: run plot 

runconservation: run plot conservation_plots

buildrunplot: build run animate

