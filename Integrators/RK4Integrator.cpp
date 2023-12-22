#include "RK4Integrator.h"

RK4Integrator::RK4Integrator(const force_calulator_t f, const valtype step):Integrator(f,step){}


GravitationalSystem RK4Integrator::nextMiniStep(GravitationalSystem oldsystem, valtype f)const{
    ForceCalculator* forceCalculator = buildForceCalculator(oldsystem);
    GravitationalSystem step1 = oldsystem;

    for(int i=0;i<step1.size();i++){
        vector3 posderiv = oldsystem[i].momentum/oldsystem[i].mass;
        step1[i].position += posderiv*f*step;

        vector3 momderiv = forceCalculator->getForce(i);
        step1[i].momentum += momderiv*f*step;
    }
    delete forceCalculator;
    return step1;
}


GravitationalSystem RK4Integrator::nextStep(GravitationalSystem oldsystem) const{
    GravitationalSystem step1 = nextMiniStep(oldsystem, 0.5);
    GravitationalSystem step2 = nextMiniStep(step1,     0.5);
    GravitationalSystem step3 = nextMiniStep(step2,     1);
    GravitationalSystem step4 = nextMiniStep(step3,     1);

    for(int i=0;i<oldsystem.size();i++){
        oldsystem[i].position += (  2*step1[i].position+ 
                                    4*step2[i].position+ 
                                    2*step3[i].position+ 
                                    1*step4[i].position- 
                                    9*oldsystem[i].position)
                                    /6.0;
        oldsystem[i].momentum += (  2*step1[i].momentum+ 
                                    4*step2[i].momentum+ 
                                    2*step3[i].momentum+ 
                                    1*step4[i].momentum- 
                                    9*oldsystem[i].momentum)
                                    /6.0;
    }
    return oldsystem;
}