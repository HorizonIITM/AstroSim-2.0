#include "ForceCalculator.h"

// class ForceCalculator{
//     protected:
//         GravitationalSystem s;
//     public:
//         ForceCalculator(GravitationalSystem& s);
//         virtual valtype getForce(const int i, const int coordType)= 0;
// };


ForceCalculator::ForceCalculator(GravitationalSystem& s):s(s){}

vector3 ForceCalculator::Force(const GravitationalBody& body, const GravitationalBody& source){
    //force on body due to source
    valtype r = (body.position - source.position).mag();
    return G * body.mass * source.mass * (source.position - body.position) * pow(r, -3);    
}

vector3 ForceCalculator::Force(const GravitationalBody* body, const GravitationalBody* source){
    //force on body due to source
    valtype r = (body->position - source->position).mag();
    return G * body->mass * source->mass * (source->position - body->position) * pow(r, -3);
}