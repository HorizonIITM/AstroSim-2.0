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
    GravitationalSystem step2 = nextMiniStep(step1, 0.5);
    GravitationalSystem step3 = nextMiniStep(step2, 1);
    GravitationalSystem step4 = nextMiniStep(step3, 1);

    // ForceCalculator* forceCalculatorStep1 = buildForceCalculator(oldsystem);
    // GravitationalSystem step1 = oldsystem;

    // for(int i=0;i<step1.size();i++){
    //     for(int j=0;j<3;j++){
    //         valtype posderiv = oldsystem[i].momentum[j]/oldsystem[i].mass;
    //         step1[i].position[j] += 0.5*posderiv*step;

    //         valtype momderiv = forceCalculatorStep1->getForce(i,j);
    //         step1[i].momentum[j] += 0.5*momderiv*step;
    //     }
    // }
    // delete forceCalculatorStep1;

    // ForceCalculator* forceCalculatorStep2 = buildForceCalculator(step1);
    // GravitationalSystem step2 = oldsystem;

    // for(int i=0;i<step2.size();i++){
    //     for(int j=0;j<3;j++){
    //         valtype posderiv = step1[i].momentum[j]/step1[i].mass;
    //         step2[i].position[j] += 0.5*posderiv*step;

    //         valtype momderiv = forceCalculatorStep2->getForce(i,j);
    //         step2[i].momentum[j] += 0.5*momderiv*step;
    //     }
    // }
    // delete forceCalculatorStep2;

    // ForceCalculator* forceCalculatorStep3 = buildForceCalculator(step2);
    // GravitationalSystem step3 = oldsystem;

    // for(int i=0;i<step3.size();i++){
    //     for(int j=0;j<3;j++){
    //         valtype posderiv = step2[i].momentum[j]/step2[i].mass;
    //         step3[i].position[j] += posderiv*step;

    //         valtype momderiv = forceCalculatorStep3->getForce(i,j);
    //         step3[i].momentum[j] += momderiv*step;
    //     }
    // }
    // delete forceCalculatorStep3;

    // ForceCalculator* forceCalculatorStep4 = buildForceCalculator(step3);
    // GravitationalSystem step4 = oldsystem;

    // for(int i=0;i<step4.size();i++){
    //     for(int j=0;j<3;j++){
    //         valtype posderiv = step3[i].momentum[j]/step3[i].mass;
    //         step4[i].position[j] += posderiv*step;

    //         valtype momderiv = forceCalculatorStep4->getForce(i,j);
    //         step4[i].momentum[j] += momderiv*step;
    //     }
    // }
    // delete forceCalculatorStep4;

    for(int i=0;i<oldsystem.size();i++){
        oldsystem[i].position += (2*step1[i].position+ 4*step2[i].position+ 2*step3[i].position+ step4[i].position- 9*oldsystem[i].position)/6.0;
        oldsystem[i].momentum += (2*step1[i].momentum+ 4*step2[i].momentum+ 2*step3[i].momentum+ step4[i].momentum- 9*oldsystem[i].momentum)/6.0;
        // for(int j=0;j<3;j++){
        //     oldsystem[i].position[j] += (2*step1[i].position[j]+ 4*step2[i].position[j]+ 2*step3[i].position[j]+ step4[i].position[j]- 9*oldsystem[i].position[j])/6.0;
        //     oldsystem[i].momentum[j] += (2*step1[i].momentum[j]+ 4*step2[i].momentum[j]+ 2*step3[i].momentum[j]+ step4[i].momentum[j]- 9*oldsystem[i].momentum[j])/6.0;
        // }
    }
    return oldsystem;
}