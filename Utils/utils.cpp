#include "utils.h"


long double invsqrt(long double number){
    return 1/sqrtl(number);
}

double invsqrt(double number){
    return 1/sqrt(number);
}

valtype distSquare(vector3 const &p1, vector3 const &p2){
    valtype sum = 0;
    for(short int coord = 0;coord<p1.size() ;coord++){
        sum += pow(p1[coord]-p2[coord],2.0);
    }
    return sum;
}

vector3 cross(vector3 const &p1, vector3 const &p2){
    vector3 res = {p1[1]*p2[2] - p1[2]*p2[1], p1[2]*p2[0] - p1[0]*p2[2], p1[0]*p2[1] - p1[1]*p2[0]};
    return res;
}
