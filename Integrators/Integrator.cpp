#include "Integrator.h"

// class Integrator{ //abstract class
//     protected:
//         force_calulator_t f;
//         valtype step;
//     public:
//         Integrator(force_calulator_t f, valtype step);
//         virtual GravitationalSystem nextStep(GravitationalSystem oldsystem) = 0;
// };

Integrator::Integrator(force_calulator_t f_t, valtype step):f_t(f_t),step(step){}