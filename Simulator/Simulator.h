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
        const integrator_t i_t;
        const force_calulator_t f_t;
        GravitationalSystem s;
        const valtype step;
    
    public:
        Simulator(GravitationalSystem s, const integrator_t i_t, const force_calulator_t f_t, const valtype step);
        Simulator(std:: string&& infile, const integrator_t i_t, const force_calulator_t f_t, const valtype step);

        void solve(const valtype totaltime, const string filename);
};


#endif
