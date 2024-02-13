#include "radiusofcurvature.h"
#include <stdexcept>
#include "../ForceCalculators/AllForceCalculators.h"
#include "../Integrators/AllIntegrators.h"
#include "../Utils/utils.h"

radiusofcurvature::radiusofcurvature(const force_calulator_t f, const valtype& step):Integrator(f,step){}

valtype radiusofcurvature :: dynamictime(GravitationalSystem& oldsystem){
    valtype rmin = 0, m = 0, maxfactor = 5;
    vector3 p = oldsystem[0].momentum, F = {0, 0, 0}; 

    m = oldsystem[0].mass;
    ForceCalculator* forceCalculator = buildForceCalculator(oldsystem);
    F = forceCalculator->getForce(0);

    

    rmin = pow(p.mag_square(), 3/2) / (sqrt(cross(p, F).mag_square()) * m);

    for(int i = 1; i < oldsystem.size(); i++){
        m = oldsystem[i].mass;
        p = oldsystem[0].momentum;
        F = forceCalculator->getForce(i);

        if(rmin > pow(p.mag_square(), 3/2) / (sqrt(cross(p, F).mag_square()) * m))  
            rmin = pow(p.mag_square(), 3/2) / (sqrt(cross(p, F).mag_square()) * m);
    }

    valtype fact = 0.001, omega = pow(p.mag_square(), 1/2) / rmin;
    
    valtype newstep = step / pow(2, llround(log(step * omega)/log(2)));

    cout << newstep << " ";

    if(newstep < step/pow(2, maxfactor))   newstep = step/pow(2, maxfactor);
    if(newstep > step)   newstep = step;

    return newstep; 
}


