# How to add a new Integrator


* create files **Integrators/MyIntegrator.h** and **Integrators/MyIntegrator.cpp**
* declare class **MyIntegrator** with public inheritance from **Integrator**
---------------------
* make **MyIntegrator(force_calulator_t f, valtype step)** constructor which takes as input
  1. the force_calculator to use
  2. step size
and initialises the corresponding class fields
* make **GravitationalSystem nextStep(GravitationalSystem oldsystem)** function which takes as input a gravitational system, and returns a system 1 step ahead in time.
---------------------
* add pragma once and guard statements to .h file with a unique name
* include **"Integrator.h"** and add declarations of the above in the .h file
* include **"MyIntegrator.h"** and add definitions of the above in the .cpp file
* add **#include "EulerIntegrator.h"** to **AllIntegrators.h**
* add lines under **build** and **debug** in MakeFile so that the files can be compiled

refer to the treatement of **EulerIntegrator** if confused

---------------------

* add the name of the new integrator in **enum integrator_t** in **defs.h**
* add the corresponding case in the switch block of **Simulator::solve** in **Simulator/simulator.cpp**