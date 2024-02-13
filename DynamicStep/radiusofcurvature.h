#pragma once

#ifndef RADIUSOFCURVATURE_H_
#define RADIUSOFCURVATURE_H_

#include "../Body/body.h"
#include "../ForceCalculators/AllForceCalculators.h"
#include "../Integrators/AllIntegrators.h"
#include "../Utils/utils.h"

class radiusofcurvature : Integrator{
    public:
        radiusofcurvature(const force_calulator_t f, const valtype &step);
        valtype dynamictime(GravitationalSystem& oldsystem);
};


#endif