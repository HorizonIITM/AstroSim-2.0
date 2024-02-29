#pragma once
/*
 * INTEGRATORS.H
 */
#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include "../Body/body.h"
#include "../defs.h"
#include "../ForceCalculators/AllForceCalculators.h"

class Integrator{ //abstract class
    protected:
        const force_calulator_t f_t;
        const valtype orgstep;
        valtype step;
        ForceCalculator* buildForceCalculator(GravitationalSystem& oldsystem) const;
    public:
        Integrator(const force_calulator_t f_t, const valtype oldstep);
        valtype dynamictime(GravitationalSystem& oldsystem);
        virtual ~Integrator() = default;
        virtual GravitationalSystem nextStep(GravitationalSystem oldsystem) const= 0; 
        //should make it reference. but then need to change implementation
};

#endif

