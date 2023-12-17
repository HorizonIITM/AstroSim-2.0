#pragma once
/*
 * INTEGRATORS.H
 */
#ifndef FORCE_CALCULATOR_H_
#define FORCE_CALCULATOR_H_

#include "../Utils/utils.h"
#include "../Body/body.h"

class ForceCalculator{
    protected:
        GravitationalSystem s;
    public:
        ForceCalculator(GravitationalSystem& s);
        virtual valtype getForce(const int i, const int coordType)= 0;
};


#endif