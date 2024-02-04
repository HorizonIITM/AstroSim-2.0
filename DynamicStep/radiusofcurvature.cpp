#include "radiusofcurvature.h"
#include <stdexcept>

radiusofcurvature :: radiusofcurvature(){};

valtype radiusofcurvature :: dynamictime(GravitationalSystem& oldsystem, valtype step){
    valtype rmin = 0, m = 0, maxfactor = 5;
    vector3 p = oldsystem[0].momentum, F = {0, 0, 0}; 

    m = oldsystem[0].mass;
    ForceCalculator* forceCalculator = buildForceCalculator(oldsystem);
    F = forceCalculator->getForce(0);

    rmin = pow(distSquare(p, {0, 0, 0}), 3/2) / (sqrt(distSquare(cross(p, F), 0)) * m);

    for(int i = 1; i < oldsystem.size(); i++){
        m = oldsystem[i].mass;
        p = oldsystem[0].momentum;
        F = forceCalculator->getForce(i);

        if(rmin > pow(distSquare(p, {0, 0, 0}), 3/2) / (sqrt(distSquare(cross(p, F), 0)) * m))  
            rmin = pow(distSquare(p, {0, 0, 0}), 3/2) / (sqrt(distSquare(cross(p, F), 0)) * m);
    }

    valtype fact = 1, omega = pow(distSquare(p, {0, 0, 0}), 1/2) / rmin;
    
    valtype newstep = step / pow(2, llround(log(step * omega)/log(2)));

    if(newstep < step/pow(2, maxfactor))   newstep = step/pow(2, maxfactor);
    if(newstep > step)   newstep = step;

    return newstep; 
}


