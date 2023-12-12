#pragma once
/*
 * INTEGRATORS.H
 */
#ifndef FORCE_CALCULATOR_H_
#define FORCE_CALCULATOR_H_

#include "utils.h"
#include "../Body/body.h"

class ForceCalculator{
    protected:
        GravitationalSystem s;
    public:
    
        ForceCalculator(GravitationalSystem s);
        //should make it reference. but then need to change implementation

        virtual valtype getForce(int i, int coordType) = 0;
};


#endif