#pragma once
/*
 * INTEGRATORS.H
 */
#ifndef DIRECT_FORCE_CALCULATOR_H_
#define DIRECT_FORCE_CALCULATOR_H_

#include "ForceCalculator.h"

class DirectForceCalculator : public ForceCalculator{
    public:
        DirectForceCalculator(GravitationalSystem s);
        valtype getForce (int i, int coordType) override;
};


#endif