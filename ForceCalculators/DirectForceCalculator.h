#pragma once
/*
 * INTEGRATORS.H
 */
#ifndef DIRECT_FORCE_CALCULATOR_H_
#define DIRECT_FORCE_CALCULATOR_H_

#include "ForceCalculator.h"

class DirectForceCalculator : public ForceCalculator{
    public:
        DirectForceCalculator(GravitationalSystem& s);
        valtype getForce (const int i, const int coordType) override;
};


#endif