#pragma once
/*
 * SIMULATOR.H
 */
#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include "../defs.h"
#include "../Body/body.h"
#include "../Integrators/AllIntegrators.h"

class Simulator{
    private:
        integrator_t i_t;
        force_calulator_t f_t;
        GravitationalSystem s;
        valtype step;
    
    public:
        Simulator(GravitationalSystem s, integrator_t i_t, force_calulator_t f_t, valtype step);
        Simulator(std:: string&& infile, integrator_t i_t, force_calulator_t f_t, valtype step);

        void solve(valtype totaltime, string filename);
};


#endif
