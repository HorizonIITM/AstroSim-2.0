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
        static vector3 Force(const GravitationalBody&, const GravitationalBody&);
        static vector3 Force(const GravitationalBody*, const GravitationalBody*);
    public:
        ForceCalculator(GravitationalSystem& s);
        virtual ~ForceCalculator() = default;
        virtual vector3 getForce(const int i)= 0;
};


#endif