#pragma once
/*
 * INTEGRATORS.H
 */
#ifndef BARNES_HUT_H_
#define BARNES_HUT_H_

#include "ForceCalculator.h"

class BarnesHut : public ForceCalculator{
    private:
        vector<vector3> forces;
    public:
        BarnesHut(GravitationalSystem& s);
        ~BarnesHut(){
            //cout << "Destroyed BanresHut" << endl;
        }
        vector3 getForce (const int i) override;
};


#endif