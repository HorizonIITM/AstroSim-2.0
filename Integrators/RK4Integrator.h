#pragma once
/*
 * INTEGRATORS.H
 */
#ifndef RK4_INTEGRATOR_H_
#define RK4_INTEGRATOR_H_

#include "Integrator.h"

class RK4Integrator: public Integrator{
    public:
        RK4Integrator(const force_calulator_t f, const valtype step);
        GravitationalSystem nextStep(GravitationalSystem oldsystem) const override;
};

#endif