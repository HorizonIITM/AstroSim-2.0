#include "EulerIntegrator.h"
#include "omp.h"

// class EulerIntegrator: public Integrator{
//     public:
//         EulerIntegrator(const force_calulator_t f, const valtype step);
//         GravitationalSystem nextStep(GravitationalSystem oldsystem) const override;
// };

EulerIntegrator::EulerIntegrator(const force_calulator_t f, const valtype step):Integrator(f,step){}


GravitationalSystem EulerIntegrator::nextStep(GravitationalSystem oldsystem) const{
    ForceCalculator* forceCalculator = buildForceCalculator(oldsystem);
    //cout << step << " ";
    #pragma omp parallel for
    for(int i=0;i<oldsystem.size();i++){
        vector3 posderiv = oldsystem[i].momentum/oldsystem[i].mass;
        oldsystem[i].position += posderiv*step;
    }
    #pragma omp parallel for
    for(int i=0;i<oldsystem.size();i++){
        vector3 momderiv = forceCalculator->getForce(i);
        oldsystem[i].momentum += momderiv*step;
    }
    delete forceCalculator;
    return oldsystem;
}
