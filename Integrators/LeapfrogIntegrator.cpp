#include "LeapfrogIntegrator.h"
#include "omp.h"

// class LeapfrogIntegrator: public Integrator{
//     public:
//         LeapfrogIntegrator(const force_calulator_t f, const valtype step);
//         GravitationalSystem nextStep(GravitationalSystem oldsystem) const override;
// };

LeapfrogIntegrator::LeapfrogIntegrator(const force_calulator_t f, const valtype step):Integrator(f,step){}


GravitationalSystem LeapfrogIntegrator::nextStep(GravitationalSystem oldsystem) const{
    ForceCalculator* forceCalculator = buildForceCalculator(oldsystem);
    #pragma omp parallel for
    for(int i=0;i<oldsystem.size();i++){
        vector3 momderiv = forceCalculator->getForce(i);
        oldsystem[i].momentum += momderiv*(step/2);
    }
    delete forceCalculator;

    #pragma omp parallel for
    for(int i=0;i<oldsystem.size();i++){
        vector3 posderiv = oldsystem[i].momentum/oldsystem[i].mass;
        oldsystem[i].position += posderiv*step;
    }

    forceCalculator = buildForceCalculator(oldsystem);
    #pragma omp parallel for
    for(int i=0;i<oldsystem.size();i++){
        vector3 momderiv = forceCalculator->getForce(i);
        oldsystem[i].momentum += momderiv*(step/2);
    }

    delete forceCalculator;
    return oldsystem;
}   