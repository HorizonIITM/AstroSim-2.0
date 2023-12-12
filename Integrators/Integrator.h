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
        force_calulator_t f_t;
        valtype step;
    public:
        Integrator(force_calulator_t f_t, valtype step);

        virtual GravitationalSystem nextStep(GravitationalSystem oldsystem) = 0; 
        //should make it reference. but then need to change implementation
};

#endif

