#pragma once
/*
 * INTEGRATORS.H
 */
#ifndef LEAPFROG_INTEGRATOR_H_
#define LEAPFROG_INTEGRATOR_H_

#include "Integrator.h"

class LeapfrogIntegrator: public Integrator{
    public:
        LeapfrogIntegrator(const force_calulator_t f, const valtype step);
        GravitationalSystem nextStep(GravitationalSystem oldsystem) const override;
};

#endif