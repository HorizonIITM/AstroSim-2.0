#include "DirectForceCalculator.h"

// class DirectForceCalculator : public ForceCalculator{
//     public:
//         DirectForceCalculator(GravitationalSystem& s);
//         valtype getForce (const int i, const int coordType) override;
// };

DirectForceCalculator::DirectForceCalculator(GravitationalSystem& s):ForceCalculator(s){}

vector3 DirectForceCalculator::getForce(const int i){
    GravitationalBody current_body = s[i];
    vector3 der;
    for(auto body : s.bodies){
        if(body.ID == current_body.ID) continue;
        // vector3 position = current_body.position- body.position;
        // valtype distsq = (position).mag_square();
        // der+= (-(G * current_body.mass * body.mass * position) *(pow (Q_rsqrt(distsq),3.0)));
        der += Force(current_body, body);
    }
    return der;
}
