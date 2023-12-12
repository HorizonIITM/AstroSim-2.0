#include "DirectForceCalculator.h"

// class DirectForceCalculator : public ForceCalculator{
//     public:
//         DirectForceCalculator(GravitationalSystem s);
//         valtype getForce(int i);
// };

DirectForceCalculator::DirectForceCalculator(GravitationalSystem s):ForceCalculator(s){}

valtype DirectForceCalculator::getForce(int i, int coordType){
    GravitationalBody current_body = s[i];
    valtype der = 0;
    for(auto body : s.bodies){
        if(body.ID == current_body.ID) continue;
        valtype distsq = distSquare(body.position, current_body.position);
        der+= (-(G * current_body.mass * body.mass * (current_body.position[coordType]-body.position[coordType])) *(pow (Q_rsqrt(distsq),3.0)));
    }
    return der;
}
