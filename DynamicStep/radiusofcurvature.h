#pragma once

#ifndef RADIUSOFCURVATURE_H_
#define RADIUSOFCURVATURE_H_

#include "../Body/body.h"
#include "../ForceCalculators/AllForceCalculators.h"
#include "../Integrators/AllIntegrators.h"
#include "../Utils/utils.h"

class radiusofcurvature{
    public:
        radiusofcurvature();
        valtype dynamictime(GravitationalSystem& oldsystem, valtype step);
};


#endif