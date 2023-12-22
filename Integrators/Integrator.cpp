#include "Integrator.h"
#include <stdexcept>

// class Integrator{ //abstract class
//     protected:
//         const force_calulator_t f_t;
//         const valtype step;
//         ForceCalculator* buildForceCalculator(GravitationalSystem& oldsystem) const;
//     public:
//         Integrator(const force_calulator_t f_t, const valtype step);

//         virtual GravitationalSystem nextStep(GravitationalSystem oldsystem) const= 0; 
//         //should make it reference. but then need to change implementation
// };

Integrator::Integrator(const force_calulator_t f_t, const valtype step):f_t(f_t),step(step){}

ForceCalculator* Integrator::buildForceCalculator(GravitationalSystem& oldsystem) const{
    switch (f_t){
        case Direct : return new DirectForceCalculator(oldsystem); 
        case BarnesHut : return new BarnesHutForceCalculator(oldsystem);
    }
    throw std::invalid_argument("No ForceCalculator of the specified type");
}