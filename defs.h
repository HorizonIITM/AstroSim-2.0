#pragma once
/*
 * SIMULATOR.H
 */
#ifndef DEFS_H
#define DEFS_H

using valtype = long double;
const valtype G  = 6.67408e-11;

enum integrator_t{
    Euler
    ,RK4
    ,Leapfrog
};

enum force_calulator_t{
    Direct
    , BarnesHut
};

#endif