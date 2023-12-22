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
