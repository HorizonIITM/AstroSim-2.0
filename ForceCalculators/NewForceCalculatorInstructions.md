# How to add a new ForceCalculator


* create files **ForceCalculators/MyForceCalculator.h** and **ForceCalculators/MyForceCalculator.cpp**
* declare class **MyForceCalculator** with public inheritance from **ForceCalculator**
---------------------
* make **MyForceCalculator(GravitationalSystem& s)** constructor which takes as input a gravitational system and initialises the corresponding class field
* make **valtype getForce (const int i) override** function which takes as input the index of body whose net force we want to calculate
---------------------
* add **pragma once** and guard statements to .h file with a unique name
* include **"Integrator.h"** and add declarations of the above in the .h file
* include **"MyIntegrator.h"** and add definitions of the above in the .cpp file
* add lines under **build** and **debug** in **MakeFile** so that the files can be compiled

refer to the treatment of **DirectForceCalculator** if confused

---------------------
* add the name of the new **ForceCalculator** in **enum force_calulator_t** in **defs.h**
* add the corresponding case in the switch block of **Integrator::buildForceCalculator** in **Integrators/Integrator.cpp**