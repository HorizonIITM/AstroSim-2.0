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

Integrator::Integrator(const force_calulator_t f_t, valtype step):f_t(f_t),step(step){}

valtype Integrator :: dynamictime(GravitationalSystem& oldsystem){
    valtype rmin = 0, m = 0, maxfactor = 5, fact = 0.2;
    valtype stepmin = step/pow(2, maxfactor);
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

    delete forceCalculator;

    valtype omega = sqrt(p.mag_square())/ (rmin * m);
    valtype newstep = 0;

    if(pow(2, llround(log(fact * omega)/log(2))) > pow(2, maxfactor)){
        newstep = step / pow(2, maxfactor);
    }
    else{
        newstep = step / pow(2, llround(log(fact * omega)/log(2)));
    }
    
    //valtype newstep = step / min(pow(2, llround(log(fact * omega)/log(2))), pow(2, maxfactor));
    cout << newstep << endl;

    if(newstep > step)   newstep = step;   
    //step = newstep; 

    return newstep; 
}

ForceCalculator* Integrator::buildForceCalculator(GravitationalSystem& oldsystem) const{
    switch (f_t){
        case Direct : return new DirectForceCalculator(oldsystem); 
        case BarnesHut : return new BarnesHutForceCalculator(oldsystem);
    }
    throw std::invalid_argument("No ForceCalculator of the specified type");
}
