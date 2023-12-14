#include "ForceCalculator.h"

// class ForceCalculator{
//     protected:
//         GravitationalSystem s;
//     public:
//         ForceCalculator(GravitationalSystem& s);
//         virtual valtype getForce(const int i, const int coordType)= 0;
// };


ForceCalculator::ForceCalculator(GravitationalSystem& s):s(s){}

