#pragma once
/*
 * INTEGRATORS.H
 */
#ifndef EULER_INTEGRATOR_H_
#define EULER_INTEGRATOR_H_

#include "Integrator.h"

class EulerIntegrator: public Integrator{
    public:
        EulerIntegrator(const force_calulator_t f, const valtype step);
        GravitationalSystem nextStep(GravitationalSystem oldsystem) const override;
};

#endif