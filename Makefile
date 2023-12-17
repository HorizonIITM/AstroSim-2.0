CCFLAGS=-O3 -std=c++17

CCFLAGS_DEBUG=-g -Og -fsanitize=address

build:
	g++ $(CCFLAGS) -c Body/body.cpp     							-o Body/body.o
	g++ $(CCFLAGS) -c ForceCalculators/ForceCalculator.cpp  		-o ForceCalculators/ForceCalculator.o
	g++ $(CCFLAGS) -c ForceCalculators/DirectForceCalculator.cpp  	-o ForceCalculators/DirectForceCalculator.o  			
	g++ $(CCFLAGS) -c ForceCalculators/utils.cpp       				-o ForceCalculators/utils.o
	g++ $(CCFLAGS) -c Integrators/Integrator.cpp					-o Integrators/Integrator.o
	g++ $(CCFLAGS) -c Integrators/EulerIntegrator.cpp				-o Integrators/EulerIntegrator.o
	g++ $(CCFLAGS) -c Integrators/RK4Integrator.cpp				    -o Integrators/RK4Integrator.o
	g++ $(CCFLAGS) -c Simulator/Simulator.cpp						-o Simulator/Simulator.o

	g++ $(CCFLAGS) -o sim.exe main.cpp Simulator/Simulator.o Integrators/EulerIntegrator.o Integrators/RK4Integrator.o Integrators/Integrator.o ForceCalculators/DirectForceCalculator.o ForceCalculators/ForceCalculator.o  ForceCalculators/utils.o Body/body.o

debug:
	g++ $(CCFLAGS_DEBUG) -c Body/body.cpp     							-o Body/body.o
	g++ $(CCFLAGS_DEBUG) -c ForceCalculators/ForceCalculator.cpp  		-o ForceCalculators/ForceCalculator.o
	g++ $(CCFLAGS_DEBUG) -c ForceCalculators/DirectForceCalculator.cpp  	-o ForceCalculators/DirectForceCalculator.o  			
	g++ $(CCFLAGS_DEBUG) -c ForceCalculators/utils.cpp       				-o ForceCalculators/utils.o
	g++ $(CCFLAGS_DEBUG) -c Integrators/Integrator.cpp					-o Integrators/Integrator.o
	g++ $(CCFLAGS_DEBUG) -c Integrators/EulerIntegrator.cpp				-o Integrators/EulerIntegrator.o
	g++ $(CCFLAGS_DEBUG) -c Integrators/RK4Integrator.cpp				-o Integrators/RK4Integrator.o
	g++ $(CCFLAGS_DEBUG) -c Simulator/Simulator.cpp						-o Simulator/Simulator.o

	g++ $(CCFLAGS_DEBUG) -o sim.exe main.cpp Simulator/Simulator.o Integrators/EulerIntegrator.o Integrators/RK4Integrator.o Integrators/Integrator.o ForceCalculators/DirectForceCalculator.o ForceCalculators/ForceCalculator.o  ForceCalculator/utils.o Body/body.o

run: build
	sim.exe "outfile.txt" "infile.txt" 20000 0.01

plot:
	python plotting/plot.py "outfile.txt"

3dplot:
	python plotting/3Dplot.py "outfile.txt" 10

animate:
	python plotting/animate.py "outfile.txt" 1

clean:
	rm -f */*.o
	rm -f outfile.txt
	rm -f sim.exe

runplot: run plot
