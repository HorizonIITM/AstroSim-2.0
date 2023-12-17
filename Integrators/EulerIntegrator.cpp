#include "EulerIntegrator.h"

// class EulerIntegrator: public Integrator{
//     public:
//         EulerIntegrator(const force_calulator_t f, const valtype step);
//         GravitationalSystem nextStep(GravitationalSystem oldsystem) const override;
// };

EulerIntegrator::EulerIntegrator(const force_calulator_t f, const valtype step):Integrator(f,step){}


GravitationalSystem EulerIntegrator::nextStep(GravitationalSystem oldsystem) const{
    ForceCalculator* forceCalculator = buildForceCalculator(oldsystem);
    for(int i=0;i<oldsystem.size();i++){
        for(int j=0;j<3;j++){
            valtype posderiv = oldsystem[i].momentum[j]/oldsystem[i].mass;
            oldsystem[i].position[j] += posderiv*step;

            valtype momderiv = forceCalculator->getForce(i,j);
            oldsystem[i].momentum[j] += momderiv*step;
        }
    }
    delete forceCalculator;
    return oldsystem;
}